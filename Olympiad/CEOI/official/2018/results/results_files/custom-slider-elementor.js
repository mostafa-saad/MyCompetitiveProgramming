//Use Strict Mode
(function ($) {
    "use strict";

    var mainSlider = $(".elpug-slider-carousel");

    function sliderCarousel(){

        var mainSlider = $(".elpug-slider-carousel");

        mainSlider.on('initialized.owl.carousel', function(e){
            $('.elpug-slide-title').addClass('active');
            $('.elpug-slide-icon').addClass('active');
            $('.elpug-slide-text').addClass('active');
            $('.elpug-slide-extra').removeClass('active');
            $('.elpug-slide-btn').addClass('active');
            var slideVideo = $(this).find('video');
            if ( $( slideVideo ).length ) {
                slideVideo.get(0).play();
            }     
        }); 
        
        mainSlider.owlCarousel({
            items: 1,
            nav: true,
            loop: false,
            autoplay:true,
            autoplayTimeout:8000,
            //navText: ['&#xf053;','&#xf054;']  
        });

        mainSlider.on('changed.owl.carousel', function(e){          
            $('.elpug-slide-title').removeClass('active');
            $('.elpug-slide-icon').removeClass('active');
            $('.elpug-slide-text').removeClass('active');
            $('.elpug-slide-btn').removeClass('active'); 
            $('.elpug-slide-extra').removeClass('active');                        
            return false;
        });
         

        mainSlider.on('translated.owl.carousel', function(e){
            $('.elpug-slide-title').addClass('active');
            $('.elpug-slide-icon').addClass('active');
            $('.elpug-slide-text').addClass('active');
            $('.elpug-slide-extra').addClass('active');
            $('.elpug-slide-btn').addClass('active');
            var slideVideo = $(this).find('video');
            if ( $( slideVideo ).length ) {
                slideVideo.get(0).play();
            }            
            return false;
        });       
    }

    sliderCarousel();

    //Begin - Window Load
    $(window).load(function () {        

        setTimeout(sliderCarousel, 500);     	

    });

    $(document).on('mouseup', function(){
       setTimeout(sliderCarousel, 1200);   
    });

    //End - Use Strict mode
})(jQuery);