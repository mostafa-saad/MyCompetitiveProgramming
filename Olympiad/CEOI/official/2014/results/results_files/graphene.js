jQuery(document).ready(function($) {
	
	/* Comments */
	if ( grapheneJS.shouldShowComments ) {
		$('li.comment .comment-permalink').hide();
		$('.comment-wrap').hover( function(){ $('.comment-permalink', this).fadeIn(200); }, function(){ $('.comment-permalink:eq(0)', this).fadeOut(200); });
		$('.comment-form-jump a').click(function(){ $('html,body').animate({scrollTop: $("#respond").offset().top - 200},'slow'); return false;});
		// Tabbed comments
		$("div#comments h4.comments a").click(function(){
			$("div#comments .comments").addClass( 'current' );
			$("div#comments .pings").removeClass( 'current' );
			$("div#comments #pings_list").hide();
			$("div#comments .comments-list-wrapper").fadeIn(300);
			return false;
		});
		$("div#comments h4.pings a").click(function(){
			$("div#comments .pings").addClass( 'current' );
			$("div#comments .comments").removeClass( 'current' );
			$("div#comments .comments-list-wrapper").hide();
			$("div#comments #pings_list").fadeIn(300);
			return false;
		});
	}
	
	
	/* Graphene Slider */
	if ( ! grapheneJS.sliderDisable ) {
		grapheneJS.sliderTransSpeed = parseInt(grapheneJS.sliderTransSpeed);
		grapheneJS.sliderInterval = parseInt(grapheneJS.sliderInterval);
		if ( grapheneJS.sliderAnimation == 'horizontal-slide' ) {
			$("#slider_root")
				.scrollable({
					circular: true,
					clickable: false,
					speed: grapheneJS.sliderTransSpeed
				})
				.navigator({	  
					navi: '.slider_nav',
					naviItem: 'a',
					activeClass: 'active'                                                               
				})
				.autoscroll({
					interval: grapheneJS.sliderInterval,
					steps: 1, 
					api: 'true'
				});
			$.graphene_slider = $("#slider_root").data("scrollable");
			
		} else {
			if ( grapheneJS.sliderAnimation == 'vertical-slide' ) 	grapheneSliderEffect = 'slide';
			else if ( grapheneJS.sliderAnimation == 'fade' )		grapheneSliderEffect = 'fade';
			else if ( grapheneJS.sliderAnimation == 'none' )		grapheneSliderEffect = 'default';
			
			$( ".slider_nav" )
					.jtTabs( ".slider_items > .slider_post", {
						effect: grapheneSliderEffect,
						fadeOutSpeed: grapheneJS.sliderTransSpeed,
						fadeInSpeed: grapheneJS.sliderTransSpeed,
						rotate: true,
						current: 'active'
					})
					.slideshow({
						autoplay: true,
						clickable: false,
						interval: grapheneJS.sliderInterval,
						api: true
					});
			$.graphene_slider = $(".slider_nav").data("tabs");
		}
		// Preload slider background images
		if ( grapheneJS.sliderDisplay == 'bgimage-excerpt' ) {
			$('.slider_items .slider_post').each(function(){
				var src = $(this).css('background-image').replace('url(', '').replace(')','');
				if ( src.indexOf('http') == 0 ){
					(new Image()).src = this;
				}
				src = null;
			});
		}
	}
				
	
	/* Infinite scroll for posts */
	if ( grapheneJS.infScroll && ! grapheneJS.isSingular ) {
		
		window.grapheneInfScrollItemsLeft = grapheneJS.totalPosts - grapheneJS.postsPerPage;
		var infScrollOptions = {
					navSelector : ".post-nav",
					nextSelector: ".post-nav .previous a",
					itemSelector: ".entries-wrapper .hentry",
					loading		: {
										msgText		: grapheneGetInfScrollMessage('post',grapheneJS.postsPerPage,window.grapheneInfScrollItemsLeft),
										finishedMsg	: grapheneJS.infScrollFinishedText,
										img			: grapheneJS.templateUrl + '/images/inf-scroll-loader.gif',
										speed		: 400
									}
			};
		if ( grapheneJS.isPageNavi ) infScrollOptions.nextSelector = '.post-nav .nextpostslink';
		if ( grapheneJS.infScrollClick ) infScrollOptions.animate = true;
		else infScrollOptions.bufferPx = 400;
		
		$('.entries-wrapper').infinitescroll(infScrollOptions, function(newElems){
			window.grapheneInfScrollItemsLeft -= parseInt(newElems.length);
			if ( window.grapheneInfScrollItemsLeft == 0 ) {
				if ( grapheneJS.infScrollClick ) {
					$('.fetch-more').html(grapheneJS.infScrollFinishedText).addClass('fetch-more-disabled').removeAttr('href');
				} else {
					setTimeout(function(){
						$('#infscr-loading').remove();
						$('.entries-wrapper').append('<p id="infscr-loading-finished">' + grapheneJS.infScrollFinishedText + '</p>');
					},400);
				}
				$('.entries-wrapper').infinitescroll('destroy');
			} else {
				setTimeout(function(){$('#infscr-loading div').html(grapheneGetInfScrollMessage('post',grapheneJS.postsPerPage,window.grapheneInfScrollItemsLeft))},400);
			}
		});
		$('.post-nav').css('display','none');
		
		if ( grapheneJS.infScrollClick ) {
			$('.entries-wrapper').infinitescroll('pause');
			$('.fetch-more').click(function(e){
				e.preventDefault();
				$('.entries-wrapper').infinitescroll('retrieve');
			});
		}
		
	}
	
	
	/* Infinite scroll for comments */
	if ( grapheneJS.infScrollComments && grapheneJS.isSingular ) {
		window.grapheneInfScrollCommentsLeft = grapheneJS.totalComments - grapheneJS.commentsPerPage;
		var infScrollCommentsOptions = {
				navSelector : ".comment-nav",
				nextSelector: ".comment-nav .next",
				itemSelector: "#comments_list > .comment",
				loading		: {
								msgText		: grapheneGetInfScrollMessage('comment',grapheneJS.commentsPerPage,window.grapheneInfScrollCommentsLeft),
								finishedMsg	: grapheneJS.infScrollCommentsFinishedMsg,
								img			: grapheneJS.templateUrl + '/images/inf-scroll-loader.gif',
								speed		: 400
							},
				animate		: true,
			};
		if ( grapheneJS.commentsOrder == 'newest' ) {
			infScrollCommentsOptions.direction = 'reverse';
			infScrollCommentsOptions.nextSelector = ".comment-nav .prev";
			
			var currentPage = parseInt( $(infScrollCommentsOptions.navSelector+' .current').html() );
			infScrollCommentsOptions.state = { currPage: currentPage };
			
			if ($(infScrollCommentsOptions.nextSelector).length > 0) {
				var nextURI = $(infScrollCommentsOptions.nextSelector).attr('href');
				var nextIndex = (currentPage-1).toString();
				
				var suffix = nextURI.slice(-(nextURI.length - nextURI.indexOf(nextIndex)-nextIndex.length));
				var pathURI = nextURI.replace(nextIndex,'').replace(suffix,'');
	
				infScrollCommentsOptions.pathParse = function(path,nextPage){
														path = [pathURI,suffix];
														return path;
													};
			}
		}
		$('#comments_list').infinitescroll(infScrollCommentsOptions,
			function(newElems){
				window.grapheneInfScrollCommentsLeft -= parseInt(newElems.length);
				if ( window.grapheneInfScrollCommentsLeft <= 0 ) {
					$('.fetch-more').html(grapheneJS.infScrollCommentsFinishedMsg).addClass('fetch-more-disabled').removeAttr('href');
						setTimeout(function(){
							$('#infscr-loading').remove();
							$('.entries-wrapper').append('<p id="infscr-loading-finished">' + grapheneJS.infScrollCommentsFinishedMsg + '</p>');
						},400);
					$('#comments_list').infinitescroll('destroy');
				} else {
					setTimeout(function(){$('#infscr-loading div').html(grapheneGetInfScrollMessage('comment',grapheneJS.commentsPerPage,window.grapheneInfScrollCommentsLeft))},400);
				}
			}
		);
		$('.comment-nav').css('display','none');
		
		$('#comments_list').infinitescroll('pause');
		$('.fetch-more').click(function(e){
			e.preventDefault();
			$('#comments_list').infinitescroll('retrieve');
		});
	}
});

function grapheneGetInfScrollMessage(type,itemsPerLoad,itemsLeft){
	type = typeof type !== 'undefined' ? type : 'post';
	
	if (itemsLeft < itemsPerLoad) itemsPerLoad = itemsLeft;
	var message = '';
	
	if ( type == 'post' ) {
		if (itemsLeft > 1)
			message = grapheneJS.infScrollMsgTextPlural.replace('window.grapheneInfScrollItemsPerPage',itemsPerLoad).replace('window.grapheneInfScrollItemsLeft',itemsLeft);
		else
			message = grapheneJS.infScrollMsgText.replace('window.grapheneInfScrollItemsPerPage',itemsPerLoad).replace('window.grapheneInfScrollItemsLeft',itemsLeft);
	}
	
	if ( type == 'comment' ) {
		if (itemsLeft > 1)
			message = grapheneJS.infScrollCommentsMsgPlural.replace('window.grapheneInfScrollCommentsPerPage',itemsPerLoad).replace('window.grapheneInfScrollCommentsLeft',itemsLeft);
		else
			message = grapheneJS.infScrollCommentsMsg.replace('window.grapheneInfScrollCommentsPerPage',itemsPerLoad).replace('window.grapheneInfScrollCommentsLeft',itemsLeft);
	}
	
	return message;
}