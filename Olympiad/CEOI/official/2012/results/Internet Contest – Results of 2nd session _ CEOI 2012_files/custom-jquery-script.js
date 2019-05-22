
// Drop down menu style
$(document).ready(function() {
	$('.headerMenu ul ul').parent().hover(function() {
		$(this).children('ul').fadeIn('fast');  
		$(this).addClass('activeParent');
	},
	function() {
		$(this).children('ul').fadeOut('fast');
		$(this).removeClass('activeParent');
	});
});
