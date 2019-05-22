//Use Strict Mode
(function ($) {
    "use strict";

    //Begin - Window Load
    function elpugTeam(){

        $(".elpug-team-carousel").owlCarousel({
            nav: false,
            margin: 10,
            responsive : {
                0 : {
                    items: 1,
                },
                // breakpoint from 768 up
                768 : {
                   items: 2,
                },
                980 : {
                    items: 4,
                }
            }
        });

    }

    $(window).load(function () {    
        elpugTeam();   
        setTimeout(elpugTeam, 500);        
    });

    $(document).on('mouseup', function(){
       setTimeout(elpugTeam, 1200);   
    });

    //End - Use Strict mode
})(jQuery);