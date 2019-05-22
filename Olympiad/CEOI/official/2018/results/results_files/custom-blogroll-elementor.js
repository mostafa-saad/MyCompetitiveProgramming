//Use Strict Mode
(function ($) {
    "use strict";

    function blogrollCarousel(){
        $(".elpug-blogroll-carousel").owlCarousel({            
            nav: false,
            margin: 20,
            responsive : {
                0 : {
                    items: 1,
                },
                // breakpoint from 768 up
                768 : {
                   items: 2,
                },
                980 : {
                    items: 3,
                }
            }
        }); 
    }

    //Begin - Window Load
    $(window).load(function () {   
        setTimeout(blogrollCarousel, 500);      
    });

    //On MouseUp
    $(document).on('mouseup', function(){
       setTimeout(blogrollCarousel, 1200);   
    });

    //End - Use Strict mode
})(jQuery);