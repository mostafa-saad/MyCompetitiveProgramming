(function ($, app) {
	$(document).ready(function () {
		var firstTableId = '',
			firstTableViewId = '',
			firstTable = '',
			firstTableWrapper = '',
			firstTableFirstRow = '';

		if($(window).width() <= 991) {
			$('div .supsystic-tables-wrap').each(function () {
				ssDiv = $(this);
				var widthMobile = ssDiv.data('table-width-mobile');
				if(typeof(widthMobile) != 'undefined') {
					ssDiv.css('display', (widthMobile == 'auto' ? 'inline-block' : '')).css('width', widthMobile);
				}
			});
		}

		$('.supsystic-table').each(function () {
			app.initializeTable(this, app.showTable, function(table) {
				// This is used when table is hidden in tabs and can't calculate itself width to adjust on small screens
				if (table.is(':visible')) {
					// Fix bug in FF and IE which not supporting max-width 100% for images in td
					calculateImages(table);
				} else {
					table.data('isVisible', setInterval(function(){
						if (table.is(':visible')) {
							clearInterval(table.data('isVisible'));
							calculateImages(table);
						}
					}, 250));
				}
				// Align all tables on page by the columns width depending on the columns width of first table on page
				if(table.data('align-by-first-table')) {
					firstTableId = firstTableId || $('.supsystic-table:first').data('id');
					firstTable = firstTable || $('#supsystic-table-' + firstTableId);
					firstTableViewId = firstTable.data('view-id');
					firstTableWrapper = firstTableWrapper || firstTable.parents('#supsystic-table-' + firstTableViewId);
					firstTableFirstRow = firstTable.data('head') ? firstTable.find('thead tr:first-child th') : firstTable.find('tbody tr:first-child td');

					if(firstTableViewId != table.data('view-id')) {
						var currentTableWrapper = table.parents('#supsystic-table-' + table.data('view-id'));

						currentTableWrapper.css({
							width: firstTableWrapper.get(0).style.width
						});
						table.css({
							width: firstTable.get(0).style.width
						});
						currentTableWrapper.find('.supsystic-table').each(function() {
							var curTable = $(this),
								curTableFirstRow = curTable.data('head') ? curTable.find('thead tr:first-child th') : curTable.find('tbody tr:first-child td');

							$.each(curTableFirstRow, function (index, element) {
								if(firstTableFirstRow[index]) {
									$(this).width($(firstTableFirstRow[index]).get(0).style.width);
								}
							});
						});
					}
				}
				if(typeof app.getTableInstanceById(table.data('id')).fnAdjustColumnSizing == 'function' ) {
					setTimeout(function(){
						app.getTableInstanceById(table.data('id')).fnAdjustColumnSizing(false);
					}, 350);
				}
			});
		});
	});

	function getOriginalImageSizes(img) {
		var tempImage = new Image(),
			width,
			height;
		if ('naturalWidth' in tempImage && 'naturalHeight' in tempImage) {
			width = img.naturalWidth;
			height = img.naturalHeight;
		} else {
			tempImage.src= img.src;
			width = tempImage.width;
			height = tempImage.height;
		}
		return {
			width: width,
			height: height
		};
	}

	function calculateImages($table) {
		var $images = $table.find('img');
		if ($images.length > 0 && /firefox|trident|msie/i.test(navigator.userAgent)) {
			$images.hide();
			$.each($images, function(index, el) {
				var $img = $(this),
					originalSizes = getOriginalImageSizes(this);
				if ($img.closest('td, th').width() < originalSizes.width) {
					$img.css('width', '100%');
				}
			});
			$images.show();

		}
	}
}(window.jQuery, window.supsystic.Tables));
