if (!Date.now) {
    Date.now = function () {
        return new Date().getTime();
    }
}

(function ($) {
    $.fn.swipe = function (settings) {
        var config = {
            minMove: 150,
            left: function () {
            },
            right: function () {
            }
        };

        if (settings) {
            $.extend(config, settings);
        }

        this.each(function () {
            var x0;
            var y0;
            var moving = false;
            var movingStartTimeMillis;
            var that;

            function stopTouch() {
                that.removeEventListener('touchmove', onTouchMove);
                moving = false;
                movingStartTimeMillis = 0;
            }

            function onTouchMove(e) {
                if (moving) {
                    var touches = e.touches.length === 0 ? e.changedTouches : e.touches;
                    var dx = x0 - touches[0].clientX;
                    var dy = y0 - touches[0].clientY;
                    var durationTimeMillis = Date.now() - movingStartTimeMillis;

                    if (Math.abs(dx) < 10 && Math.abs(dy) < 10 && e.touches.length === 0) {
                        stopTouch();
                        if (config.touch) {
                            if (config.touch(that, touches[0].target) === false) {
                                e.preventDefault();
                            }
                        }
                    }

                    if (Math.abs(dx) >= config.minMove && Math.abs(dy) < config.minMove && durationTimeMillis < 200) {
                        stopTouch();
                        if (dx > 0) {
                            config.left();
                        } else {
                            config.right();
                        }
                    }
                }
            }

            function onTouchStart(e) {
                if (e.touches && e.touches.length == 1) {
                    x0 = e.touches[0].clientX;
                    y0 = e.touches[0].clientY;
                    moving = true;
                    movingStartTimeMillis = Date.now();
                    that.addEventListener('touchmove', onTouchMove, true);
                    that.addEventListener('touchend', onTouchMove, true);
                }
            }

            if ('ontouchstart' in document.documentElement) {
                that = this;
                that.addEventListener('touchstart', onTouchStart, true);
            }
        });
        return this;
    };
})(jQuery);
