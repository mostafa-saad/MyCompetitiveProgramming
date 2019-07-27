/**
 * Controls: Table plugin
 * 
 * Depends on jWYSIWYG
 */
(function ($) {
	if (undefined === $.wysiwyg) {
		throw "wysiwyg.table.js depends on $.wysiwyg";
	}

	if (!$.wysiwyg.controls) {
		$.wysiwyg.controls = {};
	}

	var insertTable = function (colCount, rowCount, filler) {
		if (isNaN(rowCount) || isNaN(colCount) || rowCount === null || colCount === null) {
			return;
		}

		var i, j, html = ['<table border="1" style="width: 100%;"><tbody>'];

		colCount = parseInt(colCount, 10);
		rowCount = parseInt(rowCount, 10);

		if (filler === null) {
			filler = "&nbsp;";
		}
		filler = "<td>" + filler + "</td>";

		for (i = rowCount; i > 0; i -= 1) {
			html.push("<tr>");
			for (j = colCount; j > 0; j -= 1) {
				html.push(filler);
			}
			html.push("</tr>");
		}
		html.push("</tbody></table>");

		return this.insertHtml(html.join(""));
	};

	/*
	 * Wysiwyg namespace: public properties and methods
	 */
	$.wysiwyg.controls.table = function (Wysiwyg) {
		var dialog, colCount, rowCount, formTableHtml,
			formTextLegend = "Insert table",
			formTextCols   = "Count of columns",
			formTextRows   = "Count of rows",
			formTextSubmit = "Insert table",
			formTextReset  = "Cancel";

		if ($.wysiwyg.i18n) {
			formTextLegend = $.wysiwyg.i18n.t(formTextLegend, "dialogs.table");
			formTextCols = $.wysiwyg.i18n.t(formTextCols, "dialogs.table");
			formTextRows = $.wysiwyg.i18n.t(formTextRows, "dialogs.table");
			formTextSubmit = $.wysiwyg.i18n.t(formTextSubmit, "dialogs.table");
			formTextReset = $.wysiwyg.i18n.t(formTextReset, "dialogs");
		}

		formTableHtml = '<form class="wysiwyg"><fieldset><legend>' + formTextLegend + '</legend>' +
			'<label>' + formTextCols + ': <input type="text" name="colCount" value="3" /></label>' +
			'<label>' + formTextRows + ': <input type="text" name="rowCount" value="3" /></label>' +
			'<input type="submit" class="button" value="' + formTextSubmit + '"/> ' +
			'<input type="reset" value="' + formTextReset + '"/></fieldset></form>';

		if (!Wysiwyg.insertTable) {
			Wysiwyg.insertTable = insertTable;
		}

		if ($.fn.modal) {
			$.modal(formTableHtml, {
				onShow: function (dialog) {
					$("input:submit", dialog.data).click(function (e) {
						e.preventDefault();
						rowCount = $('input[name="rowCount"]', dialog.data).val();
						colCount = $('input[name="colCount"]', dialog.data).val();

						Wysiwyg.insertTable(colCount, rowCount, Wysiwyg.defaults.tableFiller);
						$.modal.close();
					});
					$("input:reset", dialog.data).click(function (e) {
						e.preventDefault();
						$.modal.close();
					});
				},
				maxWidth: Wysiwyg.defaults.formWidth,
				maxHeight: Wysiwyg.defaults.formHeight,
				overlayClose: true
			});
		} else if ($.fn.dialog) {
			dialog = $(formTableHtml).appendTo("body");
			dialog.dialog({
				modal: true,
				open: function (event, ui) {
					$("input:submit", dialog).click(function (e) {
						e.preventDefault();
						rowCount = $('input[name="rowCount"]', dialog).val();
						colCount = $('input[name="colCount"]', dialog).val();

						Wysiwyg.insertTable(colCount, rowCount, Wysiwyg.defaults.tableFiller);
						$(dialog).dialog("close");
					});
					$("input:reset", dialog).click(function (e) {
						e.preventDefault();
						$(dialog).dialog("close");
					});
				},
				close: function (event, ui) {
					dialog.dialog("destroy");
				}
			});
		} else {
			colCount = prompt(formTextCols, "3");
			rowCount = prompt(formTextRows, "3");

			Wysiwyg.insertTable(colCount, rowCount, Wysiwyg.defaults.tableFiller);
		}

		$(Wysiwyg.editorDoc).trigger("editorRefresh.wysiwyg");
	};

	$.wysiwyg.insertTable = function (object, colCount, rowCount, filler) {
		return object.each(function () {
			var Wysiwyg = $(this).data("wysiwyg");

			if (!Wysiwyg.insertTable) {
				Wysiwyg.insertTable = insertTable;
			}

			if (!Wysiwyg) {
				return this;
			}

			Wysiwyg.insertTable(colCount, rowCount, filler);
			$(Wysiwyg.editorDoc).trigger("editorRefresh.wysiwyg");

			return this;
		});
	};
})(jQuery);