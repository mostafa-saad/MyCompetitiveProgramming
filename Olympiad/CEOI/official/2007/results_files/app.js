/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId])
/******/ 			return installedModules[moduleId].exports;
/******/
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			exports: {},
/******/ 			id: moduleId,
/******/ 			loaded: false
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.loaded = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(0);
/******/ })
/************************************************************************/
/******/ ([
/* 0 */
/***/ (function(module, exports, __webpack_require__) {

	if (window.jQuery == null) {
	  window.jQuery = $;
	}
	
	window.App = {
	  doComponents: function(components, method, payload) {
	    var component, i, len;
	    for (i = 0, len = components.length; i < len; i++) {
	      component = components[i];
	      if (typeof component[method] === "function") {
	        component[method]({
	          $target: payload.$target,
	          options: this.options
	        });
	      }
	    }
	    return this;
	  },
	  run: function(options) {
	    this.options = options;
	    this.globalComponents = [__webpack_require__(1), __webpack_require__(3), __webpack_require__(4), __webpack_require__(5), __webpack_require__(6), __webpack_require__(7), __webpack_require__(8), __webpack_require__(9), __webpack_require__(10), __webpack_require__(13), __webpack_require__(14), __webpack_require__(15)];
	    this.components = [__webpack_require__(16), __webpack_require__(18), __webpack_require__(22), __webpack_require__(25), __webpack_require__(27), __webpack_require__(29), __webpack_require__(31)];
	    this.doComponents(this.globalComponents, 'init', {
	      $target: $(document)
	    });
	    this.doComponents(this.components, 'init', {
	      $target: $(document)
	    });
	    $(document).on('ajax-init', (function(_this) {
	      return function(event) {
	        return _this.doComponents(_this.components, 'init', {
	          $target: $(event.target)
	        });
	      };
	    })(this));
	  }
	};


/***/ }),
/* 1 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function() {
	    return $(document).on('click', '.tr-clickable', function(e) {
	      e.preventDefault();
	      return window.location = $(this).find('a').first().attr('href');
	    });
	  }
	};


/***/ }),
/* 2 */
/***/ (function(module, exports) {

	module.exports = jQuery;

/***/ }),
/* 3 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function() {
	    return $(document).on('click', '.share__btn', function(e) {
	      e.preventDefault();
	      return $(this).closest('.share').toggleClass('is-open');
	    });
	  }
	};


/***/ }),
/* 4 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    return $(document).on('click', '.link-slide', function(e) {
	      var $element, $this, id;
	      e.preventDefault();
	      $this = $(this);
	      id = $this.attr('href');
	      $element = $(id);
	      if ($element.hasClass('box-accordion__box')) {
	        if (!$element.closest('.box-accordion__item').hasClass('is-open')) {
	          $('.box-accordion__title__link[href=' + id + ']').trigger('click');
	        }
	      } else if ($element.hasClass('box-tabs__fragment')) {
	        if (!$element.hasClass('is-active')) {
	          $('.box-tabs .js-tab-links[href=' + id + ']').trigger('click');
	        }
	      }
	      return $('body, html').animate({
	        scrollTop: $element.offset().top
	      }, 500);
	    });
	  }
	};


/***/ }),
/* 5 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    return $(document).on('click', '.box-deaf__toggle', function(e) {
	      e.preventDefault();
	      return $(this).parents('.box-deaf').toggleClass('is-open');
	    });
	  }
	};


/***/ }),
/* 6 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    return $(document).on('click', '.menu-side__toggle', function(e) {
	      e.preventDefault();
	      return $(this).closest('.menu-side__item').toggleClass('is-open');
	    });
	  }
	};


/***/ }),
/* 7 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	exports.init = function(options) {
	  var realclick;
	  realclick = true;
	  $(document).on('click', '.box-accordion__title__link', function(e) {
	    var $closest, $item, $itemBox, $itemOther, $this, id;
	    e.preventDefault();
	    $this = $(this);
	    $closest = $this.closest('.box-accordion');
	    $item = $this.closest('.box-accordion__item');
	    $itemBox = $item.find('.box-accordion__box');
	    $itemOther = $item.siblings('.box-accordion__item');
	    id = '#' + $itemBox.attr('id');
	    if ($item.hasClass('is-open') && realclick) {
	      if ($closest.hasClass('with-history') && realclick) {
	        history.pushState(null, null, window.location.pathname);
	      }
	      return $itemBox.slideUp(function() {
	        return $item.removeClass('is-open');
	      });
	    } else {
	      $itemOther.find('.box-accordion__box').slideUp(function() {
	        return $itemOther.removeClass('is-open');
	      });
	      return $itemBox.slideDown(function() {
	        $item.addClass('is-open');
	        if ($item.offset().top < $(window).scrollTop()) {
	          $('body, html').animate({
	            scrollTop: $item.offset().top
	          }, 250);
	        }
	        if ($closest.hasClass('with-history') && realclick) {
	          return history.pushState(null, null, id);
	        }
	      });
	    }
	  });
	  return $(window).on('hashchange', function() {
	    var id;
	    id = '';
	    realclick = false;
	    if (location.hash !== '') {
	      $('.box-accordion.with-history .box-accordion__title__link[href=' + location.hash + ']').click();
	    }
	    return realclick = true;
	  });
	};


/***/ }),
/* 8 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    return $(document).on('click', '.btn-dropdown .btn', function(e) {
	      e.preventDefault();
	      $(this).closest('.btn-dropdown').toggleClass('is-open');
	      return $(this).blur();
	    });
	  }
	};


/***/ }),
/* 9 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function() {
	    return $(document).on('click', '.footer__menu__title__toggle', function(e) {
	      e.preventDefault();
	      return $(this).closest('.footer__menu__toggle').toggleClass('is-open');
	    }).on('click', '.js-toggle-jsHide', function(e) {
	      e.preventDefault();
	      return $($(this).attr('href')).toggleClass('jsHide');
	    }).on('click', '.box-code__title__close', function(e) {
	      e.preventDefault();
	      return $(this).closest('.box-code').addClass('jsHide');
	    }).on('click', '.tooltip', function(event) {
	      return event.preventDefault();
	    });
	  }
	};


/***/ }),
/* 10 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	__webpack_require__(11);
	
	__webpack_require__(12);
	
	module.exports = {
	  init: function(payload) {
	    var $document, $header, $target, header, headroom, isTouch;
	    $target = payload.$target;
	    isTouch = $('html').hasClass('touch');
	    $header = $('.header-fixed-wrap');
	    $document = $(document);
	    if ($header.length) {
	      $(window).on('scroll', function() {
	        if ($document.scrollTop() > 60) {
	          return $header.addClass('is-fixed');
	        } else {
	          return $header.removeClass('is-fixed');
	        }
	      });
	      header = document.querySelector('.header');
	      headroom = new Headroom(document.querySelector('.header'), {
	        tolerance: 10,
	        offset: 200
	      });
	      headroom.init();
	    }
	    return $(document).on('click', '.header__search__label', function(e) {
	      e.preventDefault();
	      return $(this).closest('.header__search').toggleClass('is-open').find('.inp-text').focus();
	    }).on('focus', '.header__lang__selected__link, .header__lang__popup__link', function(e) {
	      var $closest, $this;
	      if (!isTouch) {
	        $this = $(this);
	        $closest = $this.closest('.header__lang');
	        return $closest.addClass('is-hover');
	      }
	    }).on('focusout', '.header__lang__selected__link, .header__lang__popup__link', function(e) {
	      var $closest, $this;
	      if (!isTouch) {
	        if (!$(e.relatedTarget).closest('.header__lang').length) {
	          $this = $(this);
	          $closest = $this.closest('.header__lang');
	          return $closest.removeClass('is-hover');
	        }
	      }
	    }).on('click', '.header__lang--select .header__lang__selected__link', function(e) {
	      var $closest, $this;
	      if (isTouch) {
	        e.preventDefault();
	        $this = $(this);
	        $closest = $this.closest('.header__lang');
	        return $closest.toggleClass('is-hover');
	      }
	    }).on('focusout', '.header__menu__subbox a, .header__menu__submenu__link', function(e) {
	      var $closest, $this;
	      $this = $(this);
	      $closest = $(e.relatedTarget).closest('.header__menu__primary__item');
	      if (e.relatedTarget && (!$closest.length || !$closest.hasClass('is-open'))) {
	        return $this.closest('.header__menu__primary__item').removeClass('is-open');
	      }
	    }).on('click', function(e) {
	      if (!$(e.target).closest('.header__menu').length) {
	        return $('.header__menu__primary__item').removeClass('is-open');
	      }
	    }).on('click', '.with-submenu .header__menu__primary__link, .with-subbox .header__menu__primary__link', function(e) {
	      var $closest, $this;
	      e.preventDefault();
	      $this = $(this);
	      $closest = $this.closest('.header__menu__primary__item');
	      $('.header__menu__primary__item').not($closest).removeClass('is-open');
	      $closest.toggleClass('is-open');
	      if (e.clientX === 0 && e.clientY === 0) {
	        return $.tabNext();
	      }
	    }).on('keydown', function(e) {
	      $target = $(e.target);
	      if ($target.closest('.header__menu').length) {
	        if (e.keyCode === 27) {
	          return $('.header__menu__primary__item').removeClass('is-open');
	        } else if (($target.hasClass('header__menu__primary__link') || $target.hasClass('header__menu__title')) && !$target.closest('.header__menu-toggle').length) {
	          if (e.keyCode === 37) {
	            return $.tabPrev();
	          } else if (e.keyCode === 39) {
	            return $.tabNext();
	          } else if (e.keyCode === 38) {
	            e.preventDefault();
	            $target.trigger('click');
	            return $.tabPrev();
	          } else if (e.keyCode === 40) {
	            e.preventDefault();
	            $target.trigger('click');
	            return $.tabNext();
	          }
	        } else if ($target.closest('.header__menu-toggle').length) {
	          if (e.keyCode === 37) {
	            return $.tabPrev();
	          } else if (e.keyCode === 39) {
	            return $.tabNext();
	          } else if (e.keyCode === 38) {
	            e.preventDefault();
	            return $.tabPrev();
	          } else if (e.keyCode === 40) {
	            e.preventDefault();
	            return $.tabNext();
	          }
	        } else if ($target.closest('.header__menu__primary__item').length) {
	          if (e.keyCode === 37) {
	            $target.closest('.header__menu__primary__item').find('.header__menu__primary__link').focus().trigger('click');
	            return $.tabPrev();
	          } else if (e.keyCode === 39) {
	            $target.closest('.header__menu__primary__item').find('.header__menu__primary__link').focus().trigger('click');
	            return $.tabNext();
	          } else if (e.keyCode === 38) {
	            e.preventDefault();
	            return $.tabPrev();
	          } else if (e.keyCode === 40) {
	            e.preventDefault();
	            return $.tabNext();
	          }
	        }
	      }
	    }).on('click', '.header__menu__title', function(e) {
	      e.preventDefault();
	      $(this).closest('.header__menu').toggleClass('is-open');
	      $('.header__menu__primary__item').removeClass('is-hover');
	      if (e.clientX === 0 && e.clientY === 0) {
	        return $.tabNext();
	      }
	    }).on('click touchstart', function(e) {
	      if (!$(e.target).closest('.header__menu-toggle, .header__menu__title').length) {
	        $('.header__menu').removeClass('is-open');
	      }
	      if (isTouch && !$(e.target).closest('.header__menu-main').length) {
	        return $('.header__menu__primary__item').removeClass('is-hover');
	      }
	    }).on('click', '.header__menu__primary__toggle', function(e) {
	      var $closest;
	      e.preventDefault();
	      $closest = $(this).closest('.header__menu__primary__item');
	      $closest.toggleClass('is-open');
	      if ($closest.hasClass('with-subbox')) {
	        return $(this).closest('.header__menu-toggle').css('min-height', $closest.find('.header__menu__subbox').outerHeight());
	      }
	    }).on('click', '.header__menu__subbox__close', function(e) {
	      e.preventDefault();
	      $(this).closest('.header__menu__primary__item').removeClass('is-open');
	      return $(this).closest('.header__menu-toggle').css('min-height', 0);
	    }).on('click', '.header__menu__subbox__title__toggle', function(e) {
	      var $this;
	      e.preventDefault();
	      $this = $(this);
	      $this.closest('.header__menu__subbox__toggle').toggleClass('is-open');
	      return $this.closest('.header__menu-toggle').css('min-height', 0).css('min-height', $this.closest('.header__menu__subbox').outerHeight());
	    });
	  }
	};


/***/ }),
/* 11 */
/***/ (function(module, exports) {

	/*!
	 * headroom.js v0.7.0 - Give your page some headroom. Hide your header until you need it
	 * Copyright (c) 2014 Nick Williams - http://wicky.nillia.ms/headroom.js
	 * License: MIT
	 */
	
	(function(window, document) {
	
	  'use strict';
	
	  /* exported features */
	
	  var features = {
	    bind : !!(function(){}.bind),
	    classList : 'classList' in document.documentElement,
	    rAF : !!(window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame)
	  };
	  window.requestAnimationFrame = window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame;
	
	  /**
	   * Handles debouncing of events via requestAnimationFrame
	   * @see http://www.html5rocks.com/en/tutorials/speed/animations/
	   * @param {Function} callback The callback to handle whichever event
	   */
	  function Debouncer (callback) {
	    this.callback = callback;
	    this.ticking = false;
	  }
	  Debouncer.prototype = {
	    constructor : Debouncer,
	
	    /**
	     * dispatches the event to the supplied callback
	     * @private
	     */
	    update : function() {
	      this.callback && this.callback();
	      this.ticking = false;
	    },
	
	    /**
	     * ensures events don't get stacked
	     * @private
	     */
	    requestTick : function() {
	      if(!this.ticking) {
	        requestAnimationFrame(this.rafCallback || (this.rafCallback = this.update.bind(this)));
	        this.ticking = true;
	      }
	    },
	
	    /**
	     * Attach this as the event listeners
	     */
	    handleEvent : function() {
	      this.requestTick();
	    }
	  };
	  /**
	   * Check if object is part of the DOM
	   * @constructor
	   * @param {Object} obj element to check
	   */
	  function isDOMElement(obj) {
	    return obj && typeof window !== 'undefined' && (obj === window || obj.nodeType);
	  }
	
	  /**
	   * Helper function for extending objects
	   */
	  function extend (object /*, objectN ... */) {
	    if(arguments.length <= 0) {
	      throw new Error('Missing arguments in extend function');
	    }
	
	    var result = object || {},
	        key,
	        i;
	
	    for (i = 1; i < arguments.length; i++) {
	      var replacement = arguments[i] || {};
	
	      for (key in replacement) {
	        // Recurse into object except if the object is a DOM element
	        if(typeof result[key] === 'object' && ! isDOMElement(result[key])) {
	          result[key] = extend(result[key], replacement[key]);
	        }
	        else {
	          result[key] = result[key] || replacement[key];
	        }
	      }
	    }
	
	    return result;
	  }
	
	  /**
	   * Helper function for normalizing tolerance option to object format
	   */
	  function normalizeTolerance (t) {
	    return t === Object(t) ? t : { down : t, up : t };
	  }
	
	  /**
	   * UI enhancement for fixed headers.
	   * Hides header when scrolling down
	   * Shows header when scrolling up
	   * @constructor
	   * @param {DOMElement} elem the header element
	   * @param {Object} options options for the widget
	   */
	  function Headroom (elem, options) {
	    options = extend(options, Headroom.options);
	
	    this.lastKnownScrollY = 0;
	    this.elem             = elem;
	    this.debouncer        = new Debouncer(this.update.bind(this));
	    this.tolerance        = normalizeTolerance(options.tolerance);
	    this.classes          = options.classes;
	    this.offset           = options.offset;
	    this.scroller         = options.scroller;
	    this.initialised      = false;
	    this.onPin            = options.onPin;
	    this.onUnpin          = options.onUnpin;
	    this.onTop            = options.onTop;
	    this.onNotTop         = options.onNotTop;
	  }
	  Headroom.prototype = {
	    constructor : Headroom,
	
	    /**
	     * Initialises the widget
	     */
	    init : function() {
	      if(!Headroom.cutsTheMustard) {
	        return;
	      }
	
	      this.elem.classList.add(this.classes.initial);
	
	      // defer event registration to handle browser
	      // potentially restoring previous scroll position
	      setTimeout(this.attachEvent.bind(this), 100);
	
	      return this;
	    },
	
	    /**
	     * Unattaches events and removes any classes that were added
	     */
	    destroy : function() {
	      var classes = this.classes;
	
	      this.initialised = false;
	      this.elem.classList.remove(classes.unpinned, classes.pinned, classes.top, classes.initial);
	      this.scroller.removeEventListener('scroll', this.debouncer, false);
	    },
	
	    /**
	     * Attaches the scroll event
	     * @private
	     */
	    attachEvent : function() {
	      if(!this.initialised){
	        this.lastKnownScrollY = this.getScrollY();
	        this.initialised = true;
	        this.scroller.addEventListener('scroll', this.debouncer, false);
	
	        this.debouncer.handleEvent();
	      }
	    },
	
	    /**
	     * Unpins the header if it's currently pinned
	     */
	    unpin : function() {
	      var classList = this.elem.classList,
	        classes = this.classes;
	
	      if(classList.contains(classes.pinned) || !classList.contains(classes.unpinned)) {
	        classList.add(classes.unpinned);
	        classList.remove(classes.pinned);
	        this.onUnpin && this.onUnpin.call(this);
	      }
	    },
	
	    /**
	     * Pins the header if it's currently unpinned
	     */
	    pin : function() {
	      var classList = this.elem.classList,
	        classes = this.classes;
	
	      if(classList.contains(classes.unpinned)) {
	        classList.remove(classes.unpinned);
	        classList.add(classes.pinned);
	        this.onPin && this.onPin.call(this);
	      }
	    },
	
	    /**
	     * Handles the top states
	     */
	    top : function() {
	      var classList = this.elem.classList,
	        classes = this.classes;
	
	      if(!classList.contains(classes.top)) {
	        classList.add(classes.top);
	        classList.remove(classes.notTop);
	        this.onTop && this.onTop.call(this);
	      }
	    },
	
	    /**
	     * Handles the not top state
	     */
	    notTop : function() {
	      var classList = this.elem.classList,
	        classes = this.classes;
	
	      if(!classList.contains(classes.notTop)) {
	        classList.add(classes.notTop);
	        classList.remove(classes.top);
	        this.onNotTop && this.onNotTop.call(this);
	      }
	    },
	
	    /**
	     * Gets the Y scroll position
	     * @see https://developer.mozilla.org/en-US/docs/Web/API/Window.scrollY
	     * @return {Number} pixels the page has scrolled along the Y-axis
	     */
	    getScrollY : function() {
	      return (this.scroller.pageYOffset !== undefined)
	        ? this.scroller.pageYOffset
	        : (this.scroller.scrollTop !== undefined)
	          ? this.scroller.scrollTop
	          : (document.documentElement || document.body.parentNode || document.body).scrollTop;
	    },
	
	    /**
	     * Gets the height of the viewport
	     * @see http://andylangton.co.uk/blog/development/get-viewport-size-width-and-height-javascript
	     * @return {int} the height of the viewport in pixels
	     */
	    getViewportHeight : function () {
	      return window.innerHeight
	        || document.documentElement.clientHeight
	        || document.body.clientHeight;
	    },
	
	    /**
	     * Gets the height of the document
	     * @see http://james.padolsey.com/javascript/get-document-height-cross-browser/
	     * @return {int} the height of the document in pixels
	     */
	    getDocumentHeight : function () {
	      var body = document.body,
	        documentElement = document.documentElement;
	
	      return Math.max(
	        body.scrollHeight, documentElement.scrollHeight,
	        body.offsetHeight, documentElement.offsetHeight,
	        body.clientHeight, documentElement.clientHeight
	      );
	    },
	
	    /**
	     * Gets the height of the DOM element
	     * @param  {Object}  elm the element to calculate the height of which
	     * @return {int}     the height of the element in pixels
	     */
	    getElementHeight : function (elm) {
	      return Math.max(
	        elm.scrollHeight,
	        elm.offsetHeight,
	        elm.clientHeight
	      );
	    },
	
	    /**
	     * Gets the height of the scroller element
	     * @return {int} the height of the scroller element in pixels
	     */
	    getScrollerHeight : function () {
	      return (this.scroller === window || this.scroller === document.body)
	        ? this.getDocumentHeight()
	        : this.getElementHeight(this.scroller);
	    },
	
	    /**
	     * determines if the scroll position is outside of document boundaries
	     * @param  {int}  currentScrollY the current y scroll position
	     * @return {bool} true if out of bounds, false otherwise
	     */
	    isOutOfBounds : function (currentScrollY) {
	      var pastTop  = currentScrollY < 0,
	        pastBottom = currentScrollY + this.getViewportHeight() > this.getScrollerHeight();
	
	      return pastTop || pastBottom;
	    },
	
	    /**
	     * determines if the tolerance has been exceeded
	     * @param  {int} currentScrollY the current scroll y position
	     * @return {bool} true if tolerance exceeded, false otherwise
	     */
	    toleranceExceeded : function (currentScrollY, direction) {
	      return Math.abs(currentScrollY-this.lastKnownScrollY) >= this.tolerance[direction];
	    },
	
	    /**
	     * determine if it is appropriate to unpin
	     * @param  {int} currentScrollY the current y scroll position
	     * @param  {bool} toleranceExceeded has the tolerance been exceeded?
	     * @return {bool} true if should unpin, false otherwise
	     */
	    shouldUnpin : function (currentScrollY, toleranceExceeded) {
	      var scrollingDown = currentScrollY > this.lastKnownScrollY,
	        pastOffset = currentScrollY >= this.offset;
	
	      return scrollingDown && pastOffset && toleranceExceeded;
	    },
	
	    /**
	     * determine if it is appropriate to pin
	     * @param  {int} currentScrollY the current y scroll position
	     * @param  {bool} toleranceExceeded has the tolerance been exceeded?
	     * @return {bool} true if should pin, false otherwise
	     */
	    shouldPin : function (currentScrollY, toleranceExceeded) {
	      var scrollingUp  = currentScrollY < this.lastKnownScrollY,
	        pastOffset = currentScrollY <= this.offset;
	
	      return (scrollingUp && toleranceExceeded) || pastOffset;
	    },
	
	    /**
	     * Handles updating the state of the widget
	     */
	    update : function() {
	      var currentScrollY  = this.getScrollY(),
	        scrollDirection = currentScrollY > this.lastKnownScrollY ? 'down' : 'up',
	        toleranceExceeded = this.toleranceExceeded(currentScrollY, scrollDirection);
	
	      if(this.isOutOfBounds(currentScrollY)) { // Ignore bouncy scrolling in OSX
	        return;
	      }
	
	      if (currentScrollY <= this.offset ) {
	        this.top();
	      } else {
	        this.notTop();
	      }
	
	      if(this.shouldUnpin(currentScrollY, toleranceExceeded)) {
	        this.unpin();
	      }
	      else if(this.shouldPin(currentScrollY, toleranceExceeded)) {
	        this.pin();
	      }
	
	      this.lastKnownScrollY = currentScrollY;
	    }
	  };
	  /**
	   * Default options
	   * @type {Object}
	   */
	  Headroom.options = {
	    tolerance : {
	      up : 0,
	      down : 0
	    },
	    offset : 0,
	    scroller: window,
	    classes : {
	      pinned : 'headroom--pinned',
	      unpinned : 'headroom--unpinned',
	      top : 'headroom--top',
	      notTop : 'headroom--not-top',
	      initial : 'headroom'
	    }
	  };
	  Headroom.cutsTheMustard = typeof features !== 'undefined' && features.rAF && features.bind && features.classList;
	
	  window.Headroom = Headroom;
	
	}(window, document));


/***/ }),
/* 12 */
/***/ (function(module, exports) {

	/*!
	 * jQuery.tabbable 1.0 - Simple utility for selecting the next / previous ':tabbable' element.
	 * https://github.com/marklagendijk/jQuery.tabbable
	 *
	 * Includes ':tabbable' and ':focusable' selectors from jQuery UI Core
	 *
	 * Copyright 2013, Mark Lagendijk
	 * Released under the MIT license
	 *
	 */
	(function($){
		'use strict';
	
		/**
		 * Focusses the next :focusable element. Elements with tabindex=-1 are focusable, but not tabable.
		 * Does not take into account that the taborder might be different as the :tabbable elements order
		 * (which happens when using tabindexes which are greater than 0).
		 */
		$.focusNext = function(){
			selectNextTabbableOrFocusable(':focusable');
		};
	
		/**
		 * Focusses the previous :focusable element. Elements with tabindex=-1 are focusable, but not tabable.
		 * Does not take into account that the taborder might be different as the :tabbable elements order
		 * (which happens when using tabindexes which are greater than 0).
		 */
		$.focusPrev = function(){
			selectPrevTabbableOrFocusable(':focusable');
		};
	
		/**
		 * Focusses the next :tabable element.
		 * Does not take into account that the taborder might be different as the :tabbable elements order
		 * (which happens when using tabindexes which are greater than 0).
		 */
		$.tabNext = function(){
			selectNextTabbableOrFocusable(':tabbable');
		};
	
		/**
		 * Focusses the previous :tabbable element
		 * Does not take into account that the taborder might be different as the :tabbable elements order
		 * (which happens when using tabindexes which are greater than 0).
		 */
		$.tabPrev = function(){
			selectPrevTabbableOrFocusable(':tabbable');
		};
	
		function selectNextTabbableOrFocusable(selector){
			var selectables = $(selector);
			var current = $(':focus');
			var nextIndex = 0;
			if(current.length === 1){
				var currentIndex = selectables.index(current);
				if(currentIndex + 1 < selectables.length){
					nextIndex = currentIndex + 1;
				}
			}
	
			selectables.eq(nextIndex).focus();
		}
	
		function selectPrevTabbableOrFocusable(selector){
			var selectables = $(selector);
			var current = $(':focus');
			var prevIndex = selectables.length - 1;
			if(current.length === 1){
				var currentIndex = selectables.index(current);
				if(currentIndex > 0){
					prevIndex = currentIndex - 1;
				}
			}
	
			selectables.eq(prevIndex).focus();
		}
	
		/**
		 * :focusable and :tabbable, both taken from jQuery UI Core
		 */
		$.extend($.expr[ ':' ], {
			data: $.expr.createPseudo ?
				$.expr.createPseudo(function(dataName){
					return function(elem){
						return !!$.data(elem, dataName);
					};
				}) :
				// support: jQuery <1.8
				function(elem, i, match){
					return !!$.data(elem, match[ 3 ]);
				},
	
			focusable: function(element){
				return focusable(element, !isNaN($.attr(element, 'tabindex')));
			},
	
			tabbable: function(element){
				var tabIndex = $.attr(element, 'tabindex'),
					isTabIndexNaN = isNaN(tabIndex);
				return ( isTabIndexNaN || tabIndex >= 0 ) && focusable(element, !isTabIndexNaN);
			}
		});
	
		/**
		 * focussable function, taken from jQuery UI Core
		 * @param element
		 * @returns {*}
		 */
		function focusable(element){
			var map, mapName, img,
				nodeName = element.nodeName.toLowerCase(),
				isTabIndexNotNaN = !isNaN($.attr(element, 'tabindex'));
			if('area' === nodeName){
				map = element.parentNode;
				mapName = map.name;
				if(!element.href || !mapName || map.nodeName.toLowerCase() !== 'map'){
					return false;
				}
				img = $('img[usemap=#' + mapName + ']')[0];
				return !!img && visible(img);
			}
			return ( /input|select|textarea|button|object/.test(nodeName) ?
				!element.disabled :
				'a' === nodeName ?
					element.href || isTabIndexNotNaN :
					isTabIndexNotNaN) &&
				// the element and all of its ancestors must be visible
				visible(element);
	
			function visible(element){
				return $.expr.filters.visible(element) && !$(element).parents().addBack().filter(function(){
					return $.css(this, 'visibility') === 'hidden';
				}).length;
			}
		}
	})(jQuery);


/***/ }),
/* 13 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function(payload) {
	    var $document, $window, isTouch;
	    isTouch = $('html').hasClass('touch');
	    $window = $(window);
	    $document = $(document);
	    return $('.header__menu').each(function() {
	      var $holder, $items, $main, $mobileItems, $title, $toggle, calc, getIndexGreaterThen, itemsWidths, itemsWidthsSums, prepare, titleWidth;
	      $holder = $(this);
	      $title = $holder.find('> .header__menu__title');
	      $main = $holder.find('> .header__menu-main');
	      $toggle = $holder.find('> .header__menu-toggle');
	      $toggle.html($main.html());
	      $items = $main.find('> ul > li');
	      $mobileItems = $toggle.find('> ul > li');
	      titleWidth = 100;
	      itemsWidths = null;
	      itemsWidthsSums = null;
	      prepare = function() {
	        itemsWidths = $items.map(function() {
	          return $(this).outerWidth(true);
	        }).get();
	        itemsWidthsSums = itemsWidths.reduce(function(acc, cur, index, arr) {
	          var sum;
	          sum = index > 0 ? acc[index - 1] : 0;
	          acc.push(sum + cur);
	          return acc;
	        }, []);
	      };
	      getIndexGreaterThen = function(val, arr) {
	        return arr.filter(function(cur) {
	          return cur < val;
	        }).length;
	      };
	      calc = function() {
	        var currentWidth, index, isToggleMenu;
	        if ($(window).width() < 700) {
	          index = 0;
	          isToggleMenu = true;
	        } else {
	          currentWidth = $main.outerWidth();
	          index = getIndexGreaterThen(currentWidth, itemsWidthsSums);
	          isToggleMenu = index < $items.length;
	          if (isToggleMenu) {
	            index = getIndexGreaterThen(currentWidth - titleWidth, itemsWidthsSums);
	          }
	        }
	        $holder.toggleClass('has-toggle', isToggleMenu);
	        if (!isToggleMenu) {
	          $holder.removeClass('is-open');
	        }
	        $items.slice(0, index).css('display', '');
	        $items.slice(index).css('display', 'none');
	        $mobileItems.slice(0, index).css('display', 'none');
	        return $mobileItems.slice(index).css('display', '');
	      };
	      prepare();
	      calc();
	      $window.on('load', function() {
	        prepare();
	        return calc();
	      }).on('resize', function() {
	        return calc();
	      });
	      return $holder.css('visibility', 'visible');
	    });
	  }
	};


/***/ }),
/* 14 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	exports.init = function(options) {
	  var realclick;
	  realclick = true;
	  $(document).on('click', '.js-tab-links', function(event) {
	    var $link, $otherLinks, $tab, $tabsOther, $tabsWrap, id;
	    event.preventDefault();
	    $link = $(this);
	    if ($link.is('.is-active') || $link.is('.is-disabled')) {
	      return;
	    }
	    id = $link.attr('href');
	    $tab = $(id);
	    $tabsWrap = $tab.closest('.box-tabs');
	    $otherLinks = $tabsWrap.find('.js-tab-links');
	    $tabsOther = $tab.siblings('.box-tabs__fragment');
	    $tab.addClass('is-active');
	    $tabsOther.removeClass('is-active');
	    $otherLinks.removeClass('is-active');
	    $link.addClass('is-active');
	    if ($tabsWrap.hasClass('with-history') && realclick) {
	      history.pushState(null, null, id);
	    }
	    if ($link.hasClass('is-ajax') && !$link.data('ajaxed')) {
	      return $.ajax({
	        url: $link.data('ajax')
	      }).done(function(response) {
	        $tab.find('.box-tabs__content').html(response);
	        return $link.data('ajaxed', true);
	      });
	    }
	  }).on('click', '.box-tabs__responsive-link', function(event) {
	    var $links, $tab, $tabsWrap, $target, $this;
	    event.preventDefault();
	    $this = $(this);
	    $tabsWrap = $this.closest('.box-tabs');
	    $tab = $this.closest('.box-tabs__fragment');
	    $links = $tabsWrap.find('.js-tab-links');
	    $target = $links.filter('[href="#' + $tab.attr('id') + '"]');
	    if ($target.hasClass('is-active')) {
	      return $target.add($tab).removeClass('is-active');
	    } else {
	      $target.trigger('click');
	      if ($tab.offset().top < $(window).scrollTop()) {
	        return $('body, html').animate({
	          scrollTop: $tab.offset().top
	        }, 250);
	      }
	    }
	  });
	  $(window).on('hashchange', function() {
	    var id;
	    id = '';
	    realclick = false;
	    if (location.hash !== '') {
	      $('.box-tabs .js-tab-links[href=' + location.hash + ']').click();
	    } else {
	      $('.box-tabs .box-tabs__menu__item:first-child .js-tab-links').click();
	    }
	    return realclick = true;
	  }).trigger('hashchange');
	  return $('.box-tabs').each(function() {
	    if ($(this).hasClass('mobile-hide') && $(window).width() < 700) {
	      return $(this).find('.is-active').removeClass('is-active');
	    }
	  });
	};


/***/ }),
/* 15 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	module.exports = {
	  init: function(payload) {
	    var $target, isTouch;
	    $target = payload.$target;
	    isTouch = $('html').hasClass('touch');
	    if ($target.find('.menu-secondary__link').length) {
	      if (isTouch) {
	        return $(document).on('touchend', function(e) {
	          var $link, $submenu;
	          if (!$(e.target).closest('.menu-secondary__submenu').length) {
	            $('.menu-secondary__submenu.is-open').removeClass('is-open');
	            $('.menu-secondary__link.is-hover').removeClass('is-hover');
	            $('.menu-secondary__wrap').next('.menu-secondary__submenu').remove();
	          }
	          if ($(e.target).closest('.menu-secondary__link').length) {
	            $link = $(e.target).closest('.menu-secondary__link');
	            if ($link.next('.menu-secondary__submenu').length) {
	              $link.addClass('is-hover');
	              $('.menu-secondary__link').not($link).removeClass('is-prevented');
	              if ($link.hasClass('is-prevented')) {
	                return $link.removeClass('is-prevented');
	              } else {
	                e.preventDefault();
	                $link.addClass('is-prevented');
	                $submenu = $link.next('.menu-secondary__submenu');
	                return $submenu.parents('.menu-secondary__wrap').after($submenu.clone().addClass('is-open'));
	              }
	            }
	          } else {
	            return $('.menu-secondary__link.is-prevented').removeClass('is-prevented');
	          }
	        });
	      } else {
	        return $(document).on('mouseover', function(e) {
	          var $link, $submenu, offset;
	          $('.menu-secondary__submenu.is-open').removeClass('is-open');
	          $('.menu-secondary__link.is-hover').removeClass('is-hover');
	          if ($(e.target).closest('.menu-secondary__link').length) {
	            $target = $(e.target).closest('.menu-secondary__link').addClass('is-hover');
	            offset = $target.position().left;
	            return $target.next('.menu-secondary__submenu').addClass('is-open').css('left', offset);
	          } else if ($(e.target).closest('.menu-secondary__submenu').length) {
	            $submenu = $(e.target).closest('.menu-secondary__submenu');
	            $link = $submenu.prev('.menu-secondary__link');
	            $submenu.addClass('is-open');
	            return $link.addClass('is-hover');
	          }
	        });
	      }
	    }
	  }
	};


/***/ }),
/* 16 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	__webpack_require__(17);
	
	module.exports = {
	  init: function(payload) {
	    var $target, option;
	    $target = payload.$target;
	    option = {
	      byRow: true,
	      property: 'min-height',
	      target: null,
	      remove: false
	    };
	    $target.find('.box-grid__inner').matchHeight(option);
	    $target.find('.box-product__content').matchHeight(option);
	    $target.find('.box-article-grid__content').matchHeight(option);
	    $target.find('.box-event').not('.box-event--side').find('.box-event__content').matchHeight(option);
	    $target.find('.match-height').matchHeight(option);
	    $target.find('.crossroad-std').each(function() {
	      return $(this).find('.box-category, .box-article-grid:not(.grid__cell .grid__cell>.box-article-grid)').matchHeight();
	    });
	    $(window).on('load', function() {
	      return $target.find('.box-slider__item').matchHeight(option);
	    });
	    $target.find('.grid__cell .grid__cell>.box-article-grid').matchHeight();
	    $.fn.matchHeight._beforeUpdate = function(event, groups) {
	      var $gridTopLevel;
	      $gridTopLevel = $target.find('.js-equal-nested-grid>.grid');
	      return $gridTopLevel.find('.box-article-grid').height('auto');
	    };
	    return $.fn.matchHeight._afterUpdate = function(event, groups) {
	      var $articleCell, $articles, $gridCell, $gridNextLevel, $gridTopLevel, addHeight, delta, modulo, rowsCount;
	      if ($(window).width() < 700) {
	        return;
	      }
	      $gridTopLevel = $target.find('.js-equal-nested-grid>.grid');
	      $gridNextLevel = $gridTopLevel.length ? $gridTopLevel.find('.grid') : null;
	      if ($gridNextLevel && $gridNextLevel.length) {
	        $gridCell = $gridNextLevel.closest('.grid__cell');
	        $articleCell = $gridCell.siblings();
	        $gridTopLevel.find('.box-article-grid');
	        if ($articleCell.height() < $gridCell.height()) {
	          $articleCell.find('.box-article-grid').height($gridCell.height());
	        } else if ($articleCell.height() > $gridCell.height()) {
	          delta = $articleCell.height() - $gridCell.height();
	          $articles = $gridCell.find('.box-article-grid');
	          rowsCount = Math.ceil($articles.length / Math.floor($gridCell.width() / $articles.width()));
	          modulo = delta % rowsCount;
	          addHeight = Math.floor(delta / rowsCount);
	          $articles.each(function(i) {
	            if (modulo > 0 && i < modulo) {
	              return $(this).outerHeight($(this).outerHeight() + addHeight + 1);
	            } else {
	              return $(this).outerHeight($(this).outerHeight() + addHeight);
	            }
	          });
	        }
	      }
	      return $target.find('.crossroad-std').each(function() {
	        return $(this).find('.box-article-grid:not(.grid__cell .grid__cell>.box-article-grid)').each(function() {
	          var $box, $content;
	          $box = $(this);
	          $content = $box.find('.box-article-grid__content');
	          if ($box.is('.box-article-grid--noimg')) {
	            $content.height('auto');
	          }
	          if ($box.is('.box-article-grid') && $box.is('.box-article-grid--noimg') && !$box.is('.box-article-grid--noborder') && $content.outerHeight() < $box.height()) {
	            return $content.outerHeight($box.height());
	          }
	        });
	      });
	    };
	  }
	};


/***/ }),
/* 17 */
/***/ (function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;/**
	* jquery-match-height 0.7.2 by @liabru
	* http://brm.io/jquery-match-height/
	* License: MIT
	*/
	
	;(function(factory) { // eslint-disable-line no-extra-semi
	    'use strict';
	    if (true) {
	        // AMD
	        !(__WEBPACK_AMD_DEFINE_ARRAY__ = [__webpack_require__(2)], __WEBPACK_AMD_DEFINE_FACTORY__ = (factory), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
	    } else if (typeof module !== 'undefined' && module.exports) {
	        // CommonJS
	        module.exports = factory(require('jquery'));
	    } else {
	        // Global
	        factory(jQuery);
	    }
	})(function($) {
	    /*
	    *  internal
	    */
	
	    var _previousResizeWidth = -1,
	        _updateTimeout = -1;
	
	    /*
	    *  _parse
	    *  value parse utility function
	    */
	
	    var _parse = function(value) {
	        // parse value and convert NaN to 0
	        return parseFloat(value) || 0;
	    };
	
	    /*
	    *  _rows
	    *  utility function returns array of jQuery selections representing each row
	    *  (as displayed after float wrapping applied by browser)
	    */
	
	    var _rows = function(elements) {
	        var tolerance = 1,
	            $elements = $(elements),
	            lastTop = null,
	            rows = [];
	
	        // group elements by their top position
	        $elements.each(function(){
	            var $that = $(this),
	                top = $that.offset().top - _parse($that.css('margin-top')),
	                lastRow = rows.length > 0 ? rows[rows.length - 1] : null;
	
	            if (lastRow === null) {
	                // first item on the row, so just push it
	                rows.push($that);
	            } else {
	                // if the row top is the same, add to the row group
	                if (Math.floor(Math.abs(lastTop - top)) <= tolerance) {
	                    rows[rows.length - 1] = lastRow.add($that);
	                } else {
	                    // otherwise start a new row group
	                    rows.push($that);
	                }
	            }
	
	            // keep track of the last row top
	            lastTop = top;
	        });
	
	        return rows;
	    };
	
	    /*
	    *  _parseOptions
	    *  handle plugin options
	    */
	
	    var _parseOptions = function(options) {
	        var opts = {
	            byRow: true,
	            property: 'height',
	            target: null,
	            remove: false
	        };
	
	        if (typeof options === 'object') {
	            return $.extend(opts, options);
	        }
	
	        if (typeof options === 'boolean') {
	            opts.byRow = options;
	        } else if (options === 'remove') {
	            opts.remove = true;
	        }
	
	        return opts;
	    };
	
	    /*
	    *  matchHeight
	    *  plugin definition
	    */
	
	    var matchHeight = $.fn.matchHeight = function(options) {
	        var opts = _parseOptions(options);
	
	        // handle remove
	        if (opts.remove) {
	            var that = this;
	
	            // remove fixed height from all selected elements
	            this.css(opts.property, '');
	
	            // remove selected elements from all groups
	            $.each(matchHeight._groups, function(key, group) {
	                group.elements = group.elements.not(that);
	            });
	
	            // TODO: cleanup empty groups
	
	            return this;
	        }
	
	        if (this.length <= 1 && !opts.target) {
	            return this;
	        }
	
	        // keep track of this group so we can re-apply later on load and resize events
	        matchHeight._groups.push({
	            elements: this,
	            options: opts
	        });
	
	        // match each element's height to the tallest element in the selection
	        matchHeight._apply(this, opts);
	
	        return this;
	    };
	
	    /*
	    *  plugin global options
	    */
	
	    matchHeight.version = '0.7.2';
	    matchHeight._groups = [];
	    matchHeight._throttle = 80;
	    matchHeight._maintainScroll = false;
	    matchHeight._beforeUpdate = null;
	    matchHeight._afterUpdate = null;
	    matchHeight._rows = _rows;
	    matchHeight._parse = _parse;
	    matchHeight._parseOptions = _parseOptions;
	
	    /*
	    *  matchHeight._apply
	    *  apply matchHeight to given elements
	    */
	
	    matchHeight._apply = function(elements, options) {
	        var opts = _parseOptions(options),
	            $elements = $(elements),
	            rows = [$elements];
	
	        // take note of scroll position
	        var scrollTop = $(window).scrollTop(),
	            htmlHeight = $('html').outerHeight(true);
	
	        // get hidden parents
	        var $hiddenParents = $elements.parents().filter(':hidden');
	
	        // cache the original inline style
	        $hiddenParents.each(function() {
	            var $that = $(this);
	            $that.data('style-cache', $that.attr('style'));
	        });
	
	        // temporarily must force hidden parents visible
	        $hiddenParents.css('display', 'block');
	
	        // get rows if using byRow, otherwise assume one row
	        if (opts.byRow && !opts.target) {
	
	            // must first force an arbitrary equal height so floating elements break evenly
	            $elements.each(function() {
	                var $that = $(this),
	                    display = $that.css('display');
	
	                // temporarily force a usable display value
	                if (display !== 'inline-block' && display !== 'flex' && display !== 'inline-flex') {
	                    display = 'block';
	                }
	
	                // cache the original inline style
	                $that.data('style-cache', $that.attr('style'));
	
	                $that.css({
	                    'display': display,
	                    'padding-top': '0',
	                    'padding-bottom': '0',
	                    'margin-top': '0',
	                    'margin-bottom': '0',
	                    'border-top-width': '0',
	                    'border-bottom-width': '0',
	                    'height': '100px',
	                    'overflow': 'hidden'
	                });
	            });
	
	            // get the array of rows (based on element top position)
	            rows = _rows($elements);
	
	            // revert original inline styles
	            $elements.each(function() {
	                var $that = $(this);
	                $that.attr('style', $that.data('style-cache') || '');
	            });
	        }
	
	        $.each(rows, function(key, row) {
	            var $row = $(row),
	                targetHeight = 0;
	
	            if (!opts.target) {
	                // skip apply to rows with only one item
	                if (opts.byRow && $row.length <= 1) {
	                    $row.css(opts.property, '');
	                    return;
	                }
	
	                // iterate the row and find the max height
	                $row.each(function(){
	                    var $that = $(this),
	                        style = $that.attr('style'),
	                        display = $that.css('display');
	
	                    // temporarily force a usable display value
	                    if (display !== 'inline-block' && display !== 'flex' && display !== 'inline-flex') {
	                        display = 'block';
	                    }
	
	                    // ensure we get the correct actual height (and not a previously set height value)
	                    var css = { 'display': display };
	                    css[opts.property] = '';
	                    $that.css(css);
	
	                    // find the max height (including padding, but not margin)
	                    if ($that.outerHeight(false) > targetHeight) {
	                        targetHeight = $that.outerHeight(false);
	                    }
	
	                    // revert styles
	                    if (style) {
	                        $that.attr('style', style);
	                    } else {
	                        $that.css('display', '');
	                    }
	                });
	            } else {
	                // if target set, use the height of the target element
	                targetHeight = opts.target.outerHeight(false);
	            }
	
	            // iterate the row and apply the height to all elements
	            $row.each(function(){
	                var $that = $(this),
	                    verticalPadding = 0;
	
	                // don't apply to a target
	                if (opts.target && $that.is(opts.target)) {
	                    return;
	                }
	
	                // handle padding and border correctly (required when not using border-box)
	                if ($that.css('box-sizing') !== 'border-box') {
	                    verticalPadding += _parse($that.css('border-top-width')) + _parse($that.css('border-bottom-width'));
	                    verticalPadding += _parse($that.css('padding-top')) + _parse($that.css('padding-bottom'));
	                }
	
	                // set the height (accounting for padding and border)
	                $that.css(opts.property, (targetHeight - verticalPadding) + 'px');
	            });
	        });
	
	        // revert hidden parents
	        $hiddenParents.each(function() {
	            var $that = $(this);
	            $that.attr('style', $that.data('style-cache') || null);
	        });
	
	        // restore scroll position if enabled
	        if (matchHeight._maintainScroll) {
	            $(window).scrollTop((scrollTop / htmlHeight) * $('html').outerHeight(true));
	        }
	
	        return this;
	    };
	
	    /*
	    *  matchHeight._applyDataApi
	    *  applies matchHeight to all elements with a data-match-height attribute
	    */
	
	    matchHeight._applyDataApi = function() {
	        var groups = {};
	
	        // generate groups by their groupId set by elements using data-match-height
	        $('[data-match-height], [data-mh]').each(function() {
	            var $this = $(this),
	                groupId = $this.attr('data-mh') || $this.attr('data-match-height');
	
	            if (groupId in groups) {
	                groups[groupId] = groups[groupId].add($this);
	            } else {
	                groups[groupId] = $this;
	            }
	        });
	
	        // apply matchHeight to each group
	        $.each(groups, function() {
	            this.matchHeight(true);
	        });
	    };
	
	    /*
	    *  matchHeight._update
	    *  updates matchHeight on all current groups with their correct options
	    */
	
	    var _update = function(event) {
	        if (matchHeight._beforeUpdate) {
	            matchHeight._beforeUpdate(event, matchHeight._groups);
	        }
	
	        $.each(matchHeight._groups, function() {
	            matchHeight._apply(this.elements, this.options);
	        });
	
	        if (matchHeight._afterUpdate) {
	            matchHeight._afterUpdate(event, matchHeight._groups);
	        }
	    };
	
	    matchHeight._update = function(throttle, event) {
	        // prevent update if fired from a resize event
	        // where the viewport width hasn't actually changed
	        // fixes an event looping bug in IE8
	        if (event && event.type === 'resize') {
	            var windowWidth = $(window).width();
	            if (windowWidth === _previousResizeWidth) {
	                return;
	            }
	            _previousResizeWidth = windowWidth;
	        }
	
	        // throttle updates
	        if (!throttle) {
	            _update(event);
	        } else if (_updateTimeout === -1) {
	            _updateTimeout = setTimeout(function() {
	                _update(event);
	                _updateTimeout = -1;
	            }, matchHeight._throttle);
	        }
	    };
	
	    /*
	    *  bind events
	    */
	
	    // apply on DOM ready event
	    $(matchHeight._applyDataApi);
	
	    // use on or bind where supported
	    var on = $.fn.on ? 'on' : 'bind';
	
	    // update heights on load and resize events
	    $(window)[on]('load', function(event) {
	        matchHeight._update(false, event);
	    });
	
	    // throttled update heights on resize events
	    $(window)[on]('resize orientationchange', function(event) {
	        matchHeight._update(true, event);
	    });
	
	});


/***/ }),
/* 18 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	__webpack_require__(19);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    $target.find('.js-select').selectize({
	      copyClassesToDropdown: false,
	      onChange: function(value) {
	        var urlRegex;
	        urlRegex = /[-a-zA-Z0-9@:%._\+~#=]{2,256}\.[a-z]{2,6}\b([-a-zA-Z0-9@:%_\+.~#?&\/\/=]*)/;
	        if (urlRegex.test(value)) {
	          return window.location.href = value;
	        }
	      }
	    });
	    return $target.find('.js-suggest').each(function() {
	      var $suggest, data, defaultOptgroups;
	      $suggest = $(this);
	      data = $suggest.data('suggest');
	      defaultOptgroups = [
	        {
	          name: 'Kategorie',
	          id: 'category'
	        }, {
	          name: 'Textové výsledky',
	          id: 'item'
	        }
	      ];
	      return $suggest.selectize({
	        copyClassesToDropdown: false,
	        plugins: ['restore_on_backspace'],
	        maxItems: 1,
	        valueField: 'value',
	        labelField: 'text',
	        searchField: ['text'],
	        optgroupField: 'field',
	        optgroupValueField: 'id',
	        optgroupLabelField: 'name',
	        preload: true,
	        options: [],
	        optgroups: data.optgroups != null ? data.optgroups : defaultOptgroups,
	        create: true,
	        persist: false,
	        render: {
	          option_create: function(item, escape) {
	            return '<div class="create">Vyhledat <strong>' + escape(item.input) + '</strong>&hellip;</div>';
	          },
	          optgroup: function(item, escape) {
	            return '<div class="optgroup' + (item.id === 'category' ? ' optgroup-category' : '') + '">' + item.html + '</div>';
	          },
	          optgroup_header: function(item, escape) {
	            return '<div class="optgroup-header">' + escape(item.name) + '</div>';
	          },
	          option: function(item, escape) {
	            return '<div>' + escape(item.text) + '</div>';
	          }
	        },
	        load: function(query, callback) {
	          return $.ajax({
	            url: data.url + '?' + encodeURIComponent(query),
	            type: 'GET',
	            success: function(data) {
	              return callback(JSON.parse(data));
	            }
	          });
	        },
	        onChange: function(value) {
	          return $suggest[0].form.submit();
	        }
	      });
	    });
	  }
	};


/***/ }),
/* 19 */
/***/ (function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;/**
	 * selectize.js (v0.12.4)
	 * Copyright (c) 2013–2015 Brian Reavis & contributors
	 *
	 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
	 * file except in compliance with the License. You may obtain a copy of the License at:
	 * http://www.apache.org/licenses/LICENSE-2.0
	 *
	 * Unless required by applicable law or agreed to in writing, software distributed under
	 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF
	 * ANY KIND, either express or implied. See the License for the specific language
	 * governing permissions and limitations under the License.
	 *
	 * @author Brian Reavis <brian@thirdroute.com>
	 */
	
	/*jshint curly:false */
	/*jshint browser:true */
	
	(function(root, factory) {
		if (true) {
			!(__WEBPACK_AMD_DEFINE_ARRAY__ = [__webpack_require__(2),__webpack_require__(20),__webpack_require__(21)], __WEBPACK_AMD_DEFINE_FACTORY__ = (factory), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
		} else if (typeof exports === 'object') {
			module.exports = factory(require('jquery'), require('sifter'), require('microplugin'));
		} else {
			root.Selectize = factory(root.jQuery, root.Sifter, root.MicroPlugin);
		}
	}(this, function($, Sifter, MicroPlugin) {
		'use strict';
	
		var highlight = function($element, pattern) {
			if (typeof pattern === 'string' && !pattern.length) return;
			var regex = (typeof pattern === 'string') ? new RegExp(pattern, 'i') : pattern;
		
			var highlight = function(node) {
				var skip = 0;
				if (node.nodeType === 3) {
					var pos = node.data.search(regex);
					if (pos >= 0 && node.data.length > 0) {
						var match = node.data.match(regex);
						var spannode = document.createElement('span');
						spannode.className = 'highlight';
						var middlebit = node.splitText(pos);
						var endbit = middlebit.splitText(match[0].length);
						var middleclone = middlebit.cloneNode(true);
						spannode.appendChild(middleclone);
						middlebit.parentNode.replaceChild(spannode, middlebit);
						skip = 1;
					}
				} else if (node.nodeType === 1 && node.childNodes && !/(script|style)/i.test(node.tagName)) {
					for (var i = 0; i < node.childNodes.length; ++i) {
						i += highlight(node.childNodes[i]);
					}
				}
				return skip;
			};
		
			return $element.each(function() {
				highlight(this);
			});
		};
		
		/**
		 * removeHighlight fn copied from highlight v5 and
		 * edited to remove with() and pass js strict mode
		 */
		$.fn.removeHighlight = function() {
			return this.find("span.highlight").each(function() {
				this.parentNode.firstChild.nodeName;
				var parent = this.parentNode;
				parent.replaceChild(this.firstChild, this);
				parent.normalize();
			}).end();
		};
		
		
		var MicroEvent = function() {};
		MicroEvent.prototype = {
			on: function(event, fct){
				this._events = this._events || {};
				this._events[event] = this._events[event] || [];
				this._events[event].push(fct);
			},
			off: function(event, fct){
				var n = arguments.length;
				if (n === 0) return delete this._events;
				if (n === 1) return delete this._events[event];
		
				this._events = this._events || {};
				if (event in this._events === false) return;
				this._events[event].splice(this._events[event].indexOf(fct), 1);
			},
			trigger: function(event /* , args... */){
				this._events = this._events || {};
				if (event in this._events === false) return;
				for (var i = 0; i < this._events[event].length; i++){
					this._events[event][i].apply(this, Array.prototype.slice.call(arguments, 1));
				}
			}
		};
		
		/**
		 * Mixin will delegate all MicroEvent.js function in the destination object.
		 *
		 * - MicroEvent.mixin(Foobar) will make Foobar able to use MicroEvent
		 *
		 * @param {object} the object which will support MicroEvent
		 */
		MicroEvent.mixin = function(destObject){
			var props = ['on', 'off', 'trigger'];
			for (var i = 0; i < props.length; i++){
				destObject.prototype[props[i]] = MicroEvent.prototype[props[i]];
			}
		};
		
		var IS_MAC        = /Mac/.test(navigator.userAgent);
		
		var KEY_A         = 65;
		var KEY_COMMA     = 188;
		var KEY_RETURN    = 13;
		var KEY_ESC       = 27;
		var KEY_LEFT      = 37;
		var KEY_UP        = 38;
		var KEY_P         = 80;
		var KEY_RIGHT     = 39;
		var KEY_DOWN      = 40;
		var KEY_N         = 78;
		var KEY_BACKSPACE = 8;
		var KEY_DELETE    = 46;
		var KEY_SHIFT     = 16;
		var KEY_CMD       = IS_MAC ? 91 : 17;
		var KEY_CTRL      = IS_MAC ? 18 : 17;
		var KEY_TAB       = 9;
		
		var TAG_SELECT    = 1;
		var TAG_INPUT     = 2;
		
		// for now, android support in general is too spotty to support validity
		var SUPPORTS_VALIDITY_API = !/android/i.test(window.navigator.userAgent) && !!document.createElement('input').validity;
		
		
		var isset = function(object) {
			return typeof object !== 'undefined';
		};
		
		/**
		 * Converts a scalar to its best string representation
		 * for hash keys and HTML attribute values.
		 *
		 * Transformations:
		 *   'str'     -> 'str'
		 *   null      -> ''
		 *   undefined -> ''
		 *   true      -> '1'
		 *   false     -> '0'
		 *   0         -> '0'
		 *   1         -> '1'
		 *
		 * @param {string} value
		 * @returns {string|null}
		 */
		var hash_key = function(value) {
			if (typeof value === 'undefined' || value === null) return null;
			if (typeof value === 'boolean') return value ? '1' : '0';
			return value + '';
		};
		
		/**
		 * Escapes a string for use within HTML.
		 *
		 * @param {string} str
		 * @returns {string}
		 */
		var escape_html = function(str) {
			return (str + '')
				.replace(/&/g, '&amp;')
				.replace(/</g, '&lt;')
				.replace(/>/g, '&gt;')
				.replace(/"/g, '&quot;');
		};
		
		/**
		 * Escapes "$" characters in replacement strings.
		 *
		 * @param {string} str
		 * @returns {string}
		 */
		var escape_replace = function(str) {
			return (str + '').replace(/\$/g, '$$$$');
		};
		
		var hook = {};
		
		/**
		 * Wraps `method` on `self` so that `fn`
		 * is invoked before the original method.
		 *
		 * @param {object} self
		 * @param {string} method
		 * @param {function} fn
		 */
		hook.before = function(self, method, fn) {
			var original = self[method];
			self[method] = function() {
				fn.apply(self, arguments);
				return original.apply(self, arguments);
			};
		};
		
		/**
		 * Wraps `method` on `self` so that `fn`
		 * is invoked after the original method.
		 *
		 * @param {object} self
		 * @param {string} method
		 * @param {function} fn
		 */
		hook.after = function(self, method, fn) {
			var original = self[method];
			self[method] = function() {
				var result = original.apply(self, arguments);
				fn.apply(self, arguments);
				return result;
			};
		};
		
		/**
		 * Wraps `fn` so that it can only be invoked once.
		 *
		 * @param {function} fn
		 * @returns {function}
		 */
		var once = function(fn) {
			var called = false;
			return function() {
				if (called) return;
				called = true;
				fn.apply(this, arguments);
			};
		};
		
		/**
		 * Wraps `fn` so that it can only be called once
		 * every `delay` milliseconds (invoked on the falling edge).
		 *
		 * @param {function} fn
		 * @param {int} delay
		 * @returns {function}
		 */
		var debounce = function(fn, delay) {
			var timeout;
			return function() {
				var self = this;
				var args = arguments;
				window.clearTimeout(timeout);
				timeout = window.setTimeout(function() {
					fn.apply(self, args);
				}, delay);
			};
		};
		
		/**
		 * Debounce all fired events types listed in `types`
		 * while executing the provided `fn`.
		 *
		 * @param {object} self
		 * @param {array} types
		 * @param {function} fn
		 */
		var debounce_events = function(self, types, fn) {
			var type;
			var trigger = self.trigger;
			var event_args = {};
		
			// override trigger method
			self.trigger = function() {
				var type = arguments[0];
				if (types.indexOf(type) !== -1) {
					event_args[type] = arguments;
				} else {
					return trigger.apply(self, arguments);
				}
			};
		
			// invoke provided function
			fn.apply(self, []);
			self.trigger = trigger;
		
			// trigger queued events
			for (type in event_args) {
				if (event_args.hasOwnProperty(type)) {
					trigger.apply(self, event_args[type]);
				}
			}
		};
		
		/**
		 * A workaround for http://bugs.jquery.com/ticket/6696
		 *
		 * @param {object} $parent - Parent element to listen on.
		 * @param {string} event - Event name.
		 * @param {string} selector - Descendant selector to filter by.
		 * @param {function} fn - Event handler.
		 */
		var watchChildEvent = function($parent, event, selector, fn) {
			$parent.on(event, selector, function(e) {
				var child = e.target;
				while (child && child.parentNode !== $parent[0]) {
					child = child.parentNode;
				}
				e.currentTarget = child;
				return fn.apply(this, [e]);
			});
		};
		
		/**
		 * Determines the current selection within a text input control.
		 * Returns an object containing:
		 *   - start
		 *   - length
		 *
		 * @param {object} input
		 * @returns {object}
		 */
		var getSelection = function(input) {
			var result = {};
			if ('selectionStart' in input) {
				result.start = input.selectionStart;
				result.length = input.selectionEnd - result.start;
			} else if (document.selection) {
				input.focus();
				var sel = document.selection.createRange();
				var selLen = document.selection.createRange().text.length;
				sel.moveStart('character', -input.value.length);
				result.start = sel.text.length - selLen;
				result.length = selLen;
			}
			return result;
		};
		
		/**
		 * Copies CSS properties from one element to another.
		 *
		 * @param {object} $from
		 * @param {object} $to
		 * @param {array} properties
		 */
		var transferStyles = function($from, $to, properties) {
			var i, n, styles = {};
			if (properties) {
				for (i = 0, n = properties.length; i < n; i++) {
					styles[properties[i]] = $from.css(properties[i]);
				}
			} else {
				styles = $from.css();
			}
			$to.css(styles);
		};
		
		/**
		 * Measures the width of a string within a
		 * parent element (in pixels).
		 *
		 * @param {string} str
		 * @param {object} $parent
		 * @returns {int}
		 */
		var measureString = function(str, $parent) {
			if (!str) {
				return 0;
			}
		
			var $test = $('<test>').css({
				position: 'absolute',
				top: -99999,
				left: -99999,
				width: 'auto',
				padding: 0,
				whiteSpace: 'pre'
			}).text(str).appendTo('body');
		
			transferStyles($parent, $test, [
				'letterSpacing',
				'fontSize',
				'fontFamily',
				'fontWeight',
				'textTransform'
			]);
		
			var width = $test.width();
			$test.remove();
		
			return width;
		};
		
		/**
		 * Sets up an input to grow horizontally as the user
		 * types. If the value is changed manually, you can
		 * trigger the "update" handler to resize:
		 *
		 * $input.trigger('update');
		 *
		 * @param {object} $input
		 */
		var autoGrow = function($input) {
			var currentWidth = null;
		
			var update = function(e, options) {
				var value, keyCode, printable, placeholder, width;
				var shift, character, selection;
				e = e || window.event || {};
				options = options || {};
		
				if (e.metaKey || e.altKey) return;
				if (!options.force && $input.data('grow') === false) return;
		
				value = $input.val();
				if (e.type && e.type.toLowerCase() === 'keydown') {
					keyCode = e.keyCode;
					printable = (
						(keyCode >= 97 && keyCode <= 122) || // a-z
						(keyCode >= 65 && keyCode <= 90)  || // A-Z
						(keyCode >= 48 && keyCode <= 57)  || // 0-9
						keyCode === 32 // space
					);
		
					if (keyCode === KEY_DELETE || keyCode === KEY_BACKSPACE) {
						selection = getSelection($input[0]);
						if (selection.length) {
							value = value.substring(0, selection.start) + value.substring(selection.start + selection.length);
						} else if (keyCode === KEY_BACKSPACE && selection.start) {
							value = value.substring(0, selection.start - 1) + value.substring(selection.start + 1);
						} else if (keyCode === KEY_DELETE && typeof selection.start !== 'undefined') {
							value = value.substring(0, selection.start) + value.substring(selection.start + 1);
						}
					} else if (printable) {
						shift = e.shiftKey;
						character = String.fromCharCode(e.keyCode);
						if (shift) character = character.toUpperCase();
						else character = character.toLowerCase();
						value += character;
					}
				}
		
				placeholder = $input.attr('placeholder');
				if (!value && placeholder) {
					value = placeholder;
				}
		
				width = measureString(value, $input) + 4;
				if (width !== currentWidth) {
					currentWidth = width;
					$input.width(width);
					$input.triggerHandler('resize');
				}
			};
		
			$input.on('keydown keyup update blur', update);
			update();
		};
		
		var domToString = function(d) {
			var tmp = document.createElement('div');
		
			tmp.appendChild(d.cloneNode(true));
		
			return tmp.innerHTML;
		};
		
		var logError = function(message, options){
			if(!options) options = {};
			var component = "Selectize";
		
			console.error(component + ": " + message)
		
			if(options.explanation){
				// console.group is undefined in <IE11
				if(console.group) console.group();
				console.error(options.explanation);
				if(console.group) console.groupEnd();
			}
		}
		
		
		var Selectize = function($input, settings) {
			var key, i, n, dir, input, self = this;
			input = $input[0];
			input.selectize = self;
		
			// detect rtl environment
			var computedStyle = window.getComputedStyle && window.getComputedStyle(input, null);
			dir = computedStyle ? computedStyle.getPropertyValue('direction') : input.currentStyle && input.currentStyle.direction;
			dir = dir || $input.parents('[dir]:first').attr('dir') || '';
		
			// setup default state
			$.extend(self, {
				order            : 0,
				settings         : settings,
				$input           : $input,
				tabIndex         : $input.attr('tabindex') || '',
				tagType          : input.tagName.toLowerCase() === 'select' ? TAG_SELECT : TAG_INPUT,
				rtl              : /rtl/i.test(dir),
		
				eventNS          : '.selectize' + (++Selectize.count),
				highlightedValue : null,
				isOpen           : false,
				isDisabled       : false,
				isRequired       : $input.is('[required]'),
				isInvalid        : false,
				isLocked         : false,
				isFocused        : false,
				isInputHidden    : false,
				isSetup          : false,
				isShiftDown      : false,
				isCmdDown        : false,
				isCtrlDown       : false,
				ignoreFocus      : false,
				ignoreBlur       : false,
				ignoreHover      : false,
				hasOptions       : false,
				currentResults   : null,
				lastValue        : '',
				caretPos         : 0,
				loading          : 0,
				loadedSearches   : {},
		
				$activeOption    : null,
				$activeItems     : [],
		
				optgroups        : {},
				options          : {},
				userOptions      : {},
				items            : [],
				renderCache      : {},
				onSearchChange   : settings.loadThrottle === null ? self.onSearchChange : debounce(self.onSearchChange, settings.loadThrottle)
			});
		
			// search system
			self.sifter = new Sifter(this.options, {diacritics: settings.diacritics});
		
			// build options table
			if (self.settings.options) {
				for (i = 0, n = self.settings.options.length; i < n; i++) {
					self.registerOption(self.settings.options[i]);
				}
				delete self.settings.options;
			}
		
			// build optgroup table
			if (self.settings.optgroups) {
				for (i = 0, n = self.settings.optgroups.length; i < n; i++) {
					self.registerOptionGroup(self.settings.optgroups[i]);
				}
				delete self.settings.optgroups;
			}
		
			// option-dependent defaults
			self.settings.mode = self.settings.mode || (self.settings.maxItems === 1 ? 'single' : 'multi');
			if (typeof self.settings.hideSelected !== 'boolean') {
				self.settings.hideSelected = self.settings.mode === 'multi';
			}
		
			self.initializePlugins(self.settings.plugins);
			self.setupCallbacks();
			self.setupTemplates();
			self.setup();
		};
		
		// mixins
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		
		MicroEvent.mixin(Selectize);
		
		if(typeof MicroPlugin !== "undefined"){
			MicroPlugin.mixin(Selectize);
		}else{
			logError("Dependency MicroPlugin is missing",
				{explanation:
					"Make sure you either: (1) are using the \"standalone\" "+
					"version of Selectize, or (2) require MicroPlugin before you "+
					"load Selectize."}
			);
		}
		
		
		// methods
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		
		$.extend(Selectize.prototype, {
		
			/**
			 * Creates all elements and sets up event bindings.
			 */
			setup: function() {
				var self      = this;
				var settings  = self.settings;
				var eventNS   = self.eventNS;
				var $window   = $(window);
				var $document = $(document);
				var $input    = self.$input;
		
				var $wrapper;
				var $control;
				var $control_input;
				var $dropdown;
				var $dropdown_content;
				var $dropdown_parent;
				var inputMode;
				var timeout_blur;
				var timeout_focus;
				var classes;
				var classes_plugins;
				var inputId;
		
				inputMode         = self.settings.mode;
				classes           = $input.attr('class') || '';
		
				$wrapper          = $('<div>').addClass(settings.wrapperClass).addClass(classes).addClass(inputMode);
				$control          = $('<div>').addClass(settings.inputClass).addClass('items').appendTo($wrapper);
				$control_input    = $('<input type="text" autocomplete="off" />').appendTo($control).attr('tabindex', $input.is(':disabled') ? '-1' : self.tabIndex);
				$dropdown_parent  = $(settings.dropdownParent || $wrapper);
				$dropdown         = $('<div>').addClass(settings.dropdownClass).addClass(inputMode).hide().appendTo($dropdown_parent);
				$dropdown_content = $('<div>').addClass(settings.dropdownContentClass).appendTo($dropdown);
		
				if(inputId = $input.attr('id')) {
					$control_input.attr('id', inputId + '-selectized');
					$("label[for='"+inputId+"']").attr('for', inputId + '-selectized');
				}
		
				if(self.settings.copyClassesToDropdown) {
					$dropdown.addClass(classes);
				}
		
				$wrapper.css({
					width: $input[0].style.width
				});
		
				if (self.plugins.names.length) {
					classes_plugins = 'plugin-' + self.plugins.names.join(' plugin-');
					$wrapper.addClass(classes_plugins);
					$dropdown.addClass(classes_plugins);
				}
		
				if ((settings.maxItems === null || settings.maxItems > 1) && self.tagType === TAG_SELECT) {
					$input.attr('multiple', 'multiple');
				}
		
				if (self.settings.placeholder) {
					$control_input.attr('placeholder', settings.placeholder);
				}
		
				// if splitOn was not passed in, construct it from the delimiter to allow pasting universally
				if (!self.settings.splitOn && self.settings.delimiter) {
					var delimiterEscaped = self.settings.delimiter.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&');
					self.settings.splitOn = new RegExp('\\s*' + delimiterEscaped + '+\\s*');
				}
		
				if ($input.attr('autocorrect')) {
					$control_input.attr('autocorrect', $input.attr('autocorrect'));
				}
		
				if ($input.attr('autocapitalize')) {
					$control_input.attr('autocapitalize', $input.attr('autocapitalize'));
				}
		
				self.$wrapper          = $wrapper;
				self.$control          = $control;
				self.$control_input    = $control_input;
				self.$dropdown         = $dropdown;
				self.$dropdown_content = $dropdown_content;
		
				$dropdown.on('mouseenter', '[data-selectable]', function() { return self.onOptionHover.apply(self, arguments); });
				$dropdown.on('mousedown click', '[data-selectable]', function() { return self.onOptionSelect.apply(self, arguments); });
				watchChildEvent($control, 'mousedown', '*:not(input)', function() { return self.onItemSelect.apply(self, arguments); });
				autoGrow($control_input);
		
				$control.on({
					mousedown : function() { return self.onMouseDown.apply(self, arguments); },
					click     : function() { return self.onClick.apply(self, arguments); }
				});
		
				$control_input.on({
					mousedown : function(e) { e.stopPropagation(); },
					keydown   : function() { return self.onKeyDown.apply(self, arguments); },
					keyup     : function() { return self.onKeyUp.apply(self, arguments); },
					keypress  : function() { return self.onKeyPress.apply(self, arguments); },
					resize    : function() { self.positionDropdown.apply(self, []); },
					blur      : function() { return self.onBlur.apply(self, arguments); },
					focus     : function() { self.ignoreBlur = false; return self.onFocus.apply(self, arguments); },
					paste     : function() { return self.onPaste.apply(self, arguments); }
				});
		
				$document.on('keydown' + eventNS, function(e) {
					self.isCmdDown = e[IS_MAC ? 'metaKey' : 'ctrlKey'];
					self.isCtrlDown = e[IS_MAC ? 'altKey' : 'ctrlKey'];
					self.isShiftDown = e.shiftKey;
				});
		
				$document.on('keyup' + eventNS, function(e) {
					if (e.keyCode === KEY_CTRL) self.isCtrlDown = false;
					if (e.keyCode === KEY_SHIFT) self.isShiftDown = false;
					if (e.keyCode === KEY_CMD) self.isCmdDown = false;
				});
		
				$document.on('mousedown' + eventNS, function(e) {
					if (self.isFocused) {
						// prevent events on the dropdown scrollbar from causing the control to blur
						if (e.target === self.$dropdown[0] || e.target.parentNode === self.$dropdown[0]) {
							return false;
						}
						// blur on click outside
						if (!self.$control.has(e.target).length && e.target !== self.$control[0]) {
							self.blur(e.target);
						}
					}
				});
		
				$window.on(['scroll' + eventNS, 'resize' + eventNS].join(' '), function() {
					if (self.isOpen) {
						self.positionDropdown.apply(self, arguments);
					}
				});
				$window.on('mousemove' + eventNS, function() {
					self.ignoreHover = false;
				});
		
				// store original children and tab index so that they can be
				// restored when the destroy() method is called.
				this.revertSettings = {
					$children : $input.children().detach(),
					tabindex  : $input.attr('tabindex')
				};
		
				$input.attr('tabindex', -1).hide().after(self.$wrapper);
		
				if ($.isArray(settings.items)) {
					self.setValue(settings.items);
					delete settings.items;
				}
		
				// feature detect for the validation API
				if (SUPPORTS_VALIDITY_API) {
					$input.on('invalid' + eventNS, function(e) {
						e.preventDefault();
						self.isInvalid = true;
						self.refreshState();
					});
				}
		
				self.updateOriginalInput();
				self.refreshItems();
				self.refreshState();
				self.updatePlaceholder();
				self.isSetup = true;
		
				if ($input.is(':disabled')) {
					self.disable();
				}
		
				self.on('change', this.onChange);
		
				$input.data('selectize', self);
				$input.addClass('selectized');
				self.trigger('initialize');
		
				// preload options
				if (settings.preload === true) {
					self.onSearchChange('');
				}
		
			},
		
			/**
			 * Sets up default rendering functions.
			 */
			setupTemplates: function() {
				var self = this;
				var field_label = self.settings.labelField;
				var field_optgroup = self.settings.optgroupLabelField;
		
				var templates = {
					'optgroup': function(data) {
						return '<div class="optgroup">' + data.html + '</div>';
					},
					'optgroup_header': function(data, escape) {
						return '<div class="optgroup-header">' + escape(data[field_optgroup]) + '</div>';
					},
					'option': function(data, escape) {
						return '<div class="option">' + escape(data[field_label]) + '</div>';
					},
					'item': function(data, escape) {
						return '<div class="item">' + escape(data[field_label]) + '</div>';
					},
					'option_create': function(data, escape) {
						return '<div class="create">Add <strong>' + escape(data.input) + '</strong>&hellip;</div>';
					}
				};
		
				self.settings.render = $.extend({}, templates, self.settings.render);
			},
		
			/**
			 * Maps fired events to callbacks provided
			 * in the settings used when creating the control.
			 */
			setupCallbacks: function() {
				var key, fn, callbacks = {
					'initialize'      : 'onInitialize',
					'change'          : 'onChange',
					'item_add'        : 'onItemAdd',
					'item_remove'     : 'onItemRemove',
					'clear'           : 'onClear',
					'option_add'      : 'onOptionAdd',
					'option_remove'   : 'onOptionRemove',
					'option_clear'    : 'onOptionClear',
					'optgroup_add'    : 'onOptionGroupAdd',
					'optgroup_remove' : 'onOptionGroupRemove',
					'optgroup_clear'  : 'onOptionGroupClear',
					'dropdown_open'   : 'onDropdownOpen',
					'dropdown_close'  : 'onDropdownClose',
					'type'            : 'onType',
					'load'            : 'onLoad',
					'focus'           : 'onFocus',
					'blur'            : 'onBlur'
				};
		
				for (key in callbacks) {
					if (callbacks.hasOwnProperty(key)) {
						fn = this.settings[callbacks[key]];
						if (fn) this.on(key, fn);
					}
				}
			},
		
			/**
			 * Triggered when the main control element
			 * has a click event.
			 *
			 * @param {object} e
			 * @return {boolean}
			 */
			onClick: function(e) {
				var self = this;
		
				// necessary for mobile webkit devices (manual focus triggering
				// is ignored unless invoked within a click event)
				if (!self.isFocused) {
					self.focus();
					e.preventDefault();
				}
			},
		
			/**
			 * Triggered when the main control element
			 * has a mouse down event.
			 *
			 * @param {object} e
			 * @return {boolean}
			 */
			onMouseDown: function(e) {
				var self = this;
				var defaultPrevented = e.isDefaultPrevented();
				var $target = $(e.target);
		
				if (self.isFocused) {
					// retain focus by preventing native handling. if the
					// event target is the input it should not be modified.
					// otherwise, text selection within the input won't work.
					if (e.target !== self.$control_input[0]) {
						if (self.settings.mode === 'single') {
							// toggle dropdown
							self.isOpen ? self.close() : self.open();
						} else if (!defaultPrevented) {
							self.setActiveItem(null);
						}
						return false;
					}
				} else {
					// give control focus
					if (!defaultPrevented) {
						window.setTimeout(function() {
							self.focus();
						}, 0);
					}
				}
			},
		
			/**
			 * Triggered when the value of the control has been changed.
			 * This should propagate the event to the original DOM
			 * input / select element.
			 */
			onChange: function() {
				this.$input.trigger('change');
			},
		
			/**
			 * Triggered on <input> paste.
			 *
			 * @param {object} e
			 * @returns {boolean}
			 */
			onPaste: function(e) {
				var self = this;
		
				if (self.isFull() || self.isInputHidden || self.isLocked) {
					e.preventDefault();
					return;
				}
		
				// If a regex or string is included, this will split the pasted
				// input and create Items for each separate value
				if (self.settings.splitOn) {
		
					// Wait for pasted text to be recognized in value
					setTimeout(function() {
						var pastedText = self.$control_input.val();
						if(!pastedText.match(self.settings.splitOn)){ return }
		
						var splitInput = $.trim(pastedText).split(self.settings.splitOn);
						for (var i = 0, n = splitInput.length; i < n; i++) {
							self.createItem(splitInput[i]);
						}
					}, 0);
				}
			},
		
			/**
			 * Triggered on <input> keypress.
			 *
			 * @param {object} e
			 * @returns {boolean}
			 */
			onKeyPress: function(e) {
				if (this.isLocked) return e && e.preventDefault();
				var character = String.fromCharCode(e.keyCode || e.which);
				if (this.settings.create && this.settings.mode === 'multi' && character === this.settings.delimiter) {
					this.createItem();
					e.preventDefault();
					return false;
				}
			},
		
			/**
			 * Triggered on <input> keydown.
			 *
			 * @param {object} e
			 * @returns {boolean}
			 */
			onKeyDown: function(e) {
				var isInput = e.target === this.$control_input[0];
				var self = this;
		
				if (self.isLocked) {
					if (e.keyCode !== KEY_TAB) {
						e.preventDefault();
					}
					return;
				}
		
				switch (e.keyCode) {
					case KEY_A:
						if (self.isCmdDown) {
							self.selectAll();
							return;
						}
						break;
					case KEY_ESC:
						if (self.isOpen) {
							e.preventDefault();
							e.stopPropagation();
							self.close();
						}
						return;
					case KEY_N:
						if (!e.ctrlKey || e.altKey) break;
					case KEY_DOWN:
						if (!self.isOpen && self.hasOptions) {
							self.open();
						} else if (self.$activeOption) {
							self.ignoreHover = true;
							var $next = self.getAdjacentOption(self.$activeOption, 1);
							if ($next.length) self.setActiveOption($next, true, true);
						}
						e.preventDefault();
						return;
					case KEY_P:
						if (!e.ctrlKey || e.altKey) break;
					case KEY_UP:
						if (self.$activeOption) {
							self.ignoreHover = true;
							var $prev = self.getAdjacentOption(self.$activeOption, -1);
							if ($prev.length) self.setActiveOption($prev, true, true);
						}
						e.preventDefault();
						return;
					case KEY_RETURN:
						if (self.isOpen && self.$activeOption) {
							self.onOptionSelect({currentTarget: self.$activeOption});
							e.preventDefault();
						}
						return;
					case KEY_LEFT:
						self.advanceSelection(-1, e);
						return;
					case KEY_RIGHT:
						self.advanceSelection(1, e);
						return;
					case KEY_TAB:
						if (self.settings.selectOnTab && self.isOpen && self.$activeOption) {
							self.onOptionSelect({currentTarget: self.$activeOption});
		
							// Default behaviour is to jump to the next field, we only want this
							// if the current field doesn't accept any more entries
							if (!self.isFull()) {
								e.preventDefault();
							}
						}
						if (self.settings.create && self.createItem()) {
							e.preventDefault();
						}
						return;
					case KEY_BACKSPACE:
					case KEY_DELETE:
						self.deleteSelection(e);
						return;
				}
		
				if ((self.isFull() || self.isInputHidden) && !(IS_MAC ? e.metaKey : e.ctrlKey)) {
					e.preventDefault();
					return;
				}
			},
		
			/**
			 * Triggered on <input> keyup.
			 *
			 * @param {object} e
			 * @returns {boolean}
			 */
			onKeyUp: function(e) {
				var self = this;
		
				if (self.isLocked) return e && e.preventDefault();
				var value = self.$control_input.val() || '';
				if (self.lastValue !== value) {
					self.lastValue = value;
					self.onSearchChange(value);
					self.refreshOptions();
					self.trigger('type', value);
				}
			},
		
			/**
			 * Invokes the user-provide option provider / loader.
			 *
			 * Note: this function is debounced in the Selectize
			 * constructor (by `settings.loadThrottle` milliseconds)
			 *
			 * @param {string} value
			 */
			onSearchChange: function(value) {
				var self = this;
				var fn = self.settings.load;
				if (!fn) return;
				if (self.loadedSearches.hasOwnProperty(value)) return;
				self.loadedSearches[value] = true;
				self.load(function(callback) {
					fn.apply(self, [value, callback]);
				});
			},
		
			/**
			 * Triggered on <input> focus.
			 *
			 * @param {object} e (optional)
			 * @returns {boolean}
			 */
			onFocus: function(e) {
				var self = this;
				var wasFocused = self.isFocused;
		
				if (self.isDisabled) {
					self.blur();
					e && e.preventDefault();
					return false;
				}
		
				if (self.ignoreFocus) return;
				self.isFocused = true;
				if (self.settings.preload === 'focus') self.onSearchChange('');
		
				if (!wasFocused) self.trigger('focus');
		
				if (!self.$activeItems.length) {
					self.showInput();
					self.setActiveItem(null);
					self.refreshOptions(!!self.settings.openOnFocus);
				}
		
				self.refreshState();
			},
		
			/**
			 * Triggered on <input> blur.
			 *
			 * @param {object} e
			 * @param {Element} dest
			 */
			onBlur: function(e, dest) {
				var self = this;
				if (!self.isFocused) return;
				self.isFocused = false;
		
				if (self.ignoreFocus) {
					return;
				} else if (!self.ignoreBlur && document.activeElement === self.$dropdown_content[0]) {
					// necessary to prevent IE closing the dropdown when the scrollbar is clicked
					self.ignoreBlur = true;
					self.onFocus(e);
					return;
				}
		
				var deactivate = function() {
					self.close();
					self.setTextboxValue('');
					self.setActiveItem(null);
					self.setActiveOption(null);
					self.setCaret(self.items.length);
					self.refreshState();
		
					// IE11 bug: element still marked as active
					dest && dest.focus && dest.focus();
		
					self.ignoreFocus = false;
					self.trigger('blur');
				};
		
				self.ignoreFocus = true;
				if (self.settings.create && self.settings.createOnBlur) {
					self.createItem(null, false, deactivate);
				} else {
					deactivate();
				}
			},
		
			/**
			 * Triggered when the user rolls over
			 * an option in the autocomplete dropdown menu.
			 *
			 * @param {object} e
			 * @returns {boolean}
			 */
			onOptionHover: function(e) {
				if (this.ignoreHover) return;
				this.setActiveOption(e.currentTarget, false);
			},
		
			/**
			 * Triggered when the user clicks on an option
			 * in the autocomplete dropdown menu.
			 *
			 * @param {object} e
			 * @returns {boolean}
			 */
			onOptionSelect: function(e) {
				var value, $target, $option, self = this;
		
				if (e.preventDefault) {
					e.preventDefault();
					e.stopPropagation();
				}
		
				$target = $(e.currentTarget);
				if ($target.hasClass('create')) {
					self.createItem(null, function() {
						if (self.settings.closeAfterSelect) {
							self.close();
						}
					});
				} else {
					value = $target.attr('data-value');
					if (typeof value !== 'undefined') {
						self.lastQuery = null;
						self.setTextboxValue('');
						self.addItem(value);
						if (self.settings.closeAfterSelect) {
							self.close();
						} else if (!self.settings.hideSelected && e.type && /mouse/.test(e.type)) {
							self.setActiveOption(self.getOption(value));
						}
					}
				}
			},
		
			/**
			 * Triggered when the user clicks on an item
			 * that has been selected.
			 *
			 * @param {object} e
			 * @returns {boolean}
			 */
			onItemSelect: function(e) {
				var self = this;
		
				if (self.isLocked) return;
				if (self.settings.mode === 'multi') {
					e.preventDefault();
					self.setActiveItem(e.currentTarget, e);
				}
			},
		
			/**
			 * Invokes the provided method that provides
			 * results to a callback---which are then added
			 * as options to the control.
			 *
			 * @param {function} fn
			 */
			load: function(fn) {
				var self = this;
				var $wrapper = self.$wrapper.addClass(self.settings.loadingClass);
		
				self.loading++;
				fn.apply(self, [function(results) {
					self.loading = Math.max(self.loading - 1, 0);
					if (results && results.length) {
						self.addOption(results);
						self.refreshOptions(self.isFocused && !self.isInputHidden);
					}
					if (!self.loading) {
						$wrapper.removeClass(self.settings.loadingClass);
					}
					self.trigger('load', results);
				}]);
			},
		
			/**
			 * Sets the input field of the control to the specified value.
			 *
			 * @param {string} value
			 */
			setTextboxValue: function(value) {
				var $input = this.$control_input;
				var changed = $input.val() !== value;
				if (changed) {
					$input.val(value).triggerHandler('update');
					this.lastValue = value;
				}
			},
		
			/**
			 * Returns the value of the control. If multiple items
			 * can be selected (e.g. <select multiple>), this returns
			 * an array. If only one item can be selected, this
			 * returns a string.
			 *
			 * @returns {mixed}
			 */
			getValue: function() {
				if (this.tagType === TAG_SELECT && this.$input.attr('multiple')) {
					return this.items;
				} else {
					return this.items.join(this.settings.delimiter);
				}
			},
		
			/**
			 * Resets the selected items to the given value.
			 *
			 * @param {mixed} value
			 */
			setValue: function(value, silent) {
				var events = silent ? [] : ['change'];
		
				debounce_events(this, events, function() {
					this.clear(silent);
					this.addItems(value, silent);
				});
			},
		
			/**
			 * Sets the selected item.
			 *
			 * @param {object} $item
			 * @param {object} e (optional)
			 */
			setActiveItem: function($item, e) {
				var self = this;
				var eventName;
				var i, idx, begin, end, item, swap;
				var $last;
		
				if (self.settings.mode === 'single') return;
				$item = $($item);
		
				// clear the active selection
				if (!$item.length) {
					$(self.$activeItems).removeClass('active');
					self.$activeItems = [];
					if (self.isFocused) {
						self.showInput();
					}
					return;
				}
		
				// modify selection
				eventName = e && e.type.toLowerCase();
		
				if (eventName === 'mousedown' && self.isShiftDown && self.$activeItems.length) {
					$last = self.$control.children('.active:last');
					begin = Array.prototype.indexOf.apply(self.$control[0].childNodes, [$last[0]]);
					end   = Array.prototype.indexOf.apply(self.$control[0].childNodes, [$item[0]]);
					if (begin > end) {
						swap  = begin;
						begin = end;
						end   = swap;
					}
					for (i = begin; i <= end; i++) {
						item = self.$control[0].childNodes[i];
						if (self.$activeItems.indexOf(item) === -1) {
							$(item).addClass('active');
							self.$activeItems.push(item);
						}
					}
					e.preventDefault();
				} else if ((eventName === 'mousedown' && self.isCtrlDown) || (eventName === 'keydown' && this.isShiftDown)) {
					if ($item.hasClass('active')) {
						idx = self.$activeItems.indexOf($item[0]);
						self.$activeItems.splice(idx, 1);
						$item.removeClass('active');
					} else {
						self.$activeItems.push($item.addClass('active')[0]);
					}
				} else {
					$(self.$activeItems).removeClass('active');
					self.$activeItems = [$item.addClass('active')[0]];
				}
		
				// ensure control has focus
				self.hideInput();
				if (!this.isFocused) {
					self.focus();
				}
			},
		
			/**
			 * Sets the selected item in the dropdown menu
			 * of available options.
			 *
			 * @param {object} $object
			 * @param {boolean} scroll
			 * @param {boolean} animate
			 */
			setActiveOption: function($option, scroll, animate) {
				var height_menu, height_item, y;
				var scroll_top, scroll_bottom;
				var self = this;
		
				if (self.$activeOption) self.$activeOption.removeClass('active');
				self.$activeOption = null;
		
				$option = $($option);
				if (!$option.length) return;
		
				self.$activeOption = $option.addClass('active');
		
				if (scroll || !isset(scroll)) {
		
					height_menu   = self.$dropdown_content.height();
					height_item   = self.$activeOption.outerHeight(true);
					scroll        = self.$dropdown_content.scrollTop() || 0;
					y             = self.$activeOption.offset().top - self.$dropdown_content.offset().top + scroll;
					scroll_top    = y;
					scroll_bottom = y - height_menu + height_item;
		
					if (y + height_item > height_menu + scroll) {
						self.$dropdown_content.stop().animate({scrollTop: scroll_bottom}, animate ? self.settings.scrollDuration : 0);
					} else if (y < scroll) {
						self.$dropdown_content.stop().animate({scrollTop: scroll_top}, animate ? self.settings.scrollDuration : 0);
					}
		
				}
			},
		
			/**
			 * Selects all items (CTRL + A).
			 */
			selectAll: function() {
				var self = this;
				if (self.settings.mode === 'single') return;
		
				self.$activeItems = Array.prototype.slice.apply(self.$control.children(':not(input)').addClass('active'));
				if (self.$activeItems.length) {
					self.hideInput();
					self.close();
				}
				self.focus();
			},
		
			/**
			 * Hides the input element out of view, while
			 * retaining its focus.
			 */
			hideInput: function() {
				var self = this;
		
				self.setTextboxValue('');
				self.$control_input.css({opacity: 0, position: 'absolute', left: self.rtl ? 10000 : -10000});
				self.isInputHidden = true;
			},
		
			/**
			 * Restores input visibility.
			 */
			showInput: function() {
				this.$control_input.css({opacity: 1, position: 'relative', left: 0});
				this.isInputHidden = false;
			},
		
			/**
			 * Gives the control focus.
			 */
			focus: function() {
				var self = this;
				if (self.isDisabled) return;
		
				self.ignoreFocus = true;
				self.$control_input[0].focus();
				window.setTimeout(function() {
					self.ignoreFocus = false;
					self.onFocus();
				}, 0);
			},
		
			/**
			 * Forces the control out of focus.
			 *
			 * @param {Element} dest
			 */
			blur: function(dest) {
				this.$control_input[0].blur();
				this.onBlur(null, dest);
			},
		
			/**
			 * Returns a function that scores an object
			 * to show how good of a match it is to the
			 * provided query.
			 *
			 * @param {string} query
			 * @param {object} options
			 * @return {function}
			 */
			getScoreFunction: function(query) {
				return this.sifter.getScoreFunction(query, this.getSearchOptions());
			},
		
			/**
			 * Returns search options for sifter (the system
			 * for scoring and sorting results).
			 *
			 * @see https://github.com/brianreavis/sifter.js
			 * @return {object}
			 */
			getSearchOptions: function() {
				var settings = this.settings;
				var sort = settings.sortField;
				if (typeof sort === 'string') {
					sort = [{field: sort}];
				}
		
				return {
					fields      : settings.searchField,
					conjunction : settings.searchConjunction,
					sort        : sort
				};
			},
		
			/**
			 * Searches through available options and returns
			 * a sorted array of matches.
			 *
			 * Returns an object containing:
			 *
			 *   - query {string}
			 *   - tokens {array}
			 *   - total {int}
			 *   - items {array}
			 *
			 * @param {string} query
			 * @returns {object}
			 */
			search: function(query) {
				var i, value, score, result, calculateScore;
				var self     = this;
				var settings = self.settings;
				var options  = this.getSearchOptions();
		
				// validate user-provided result scoring function
				if (settings.score) {
					calculateScore = self.settings.score.apply(this, [query]);
					if (typeof calculateScore !== 'function') {
						throw new Error('Selectize "score" setting must be a function that returns a function');
					}
				}
		
				// perform search
				if (query !== self.lastQuery) {
					self.lastQuery = query;
					result = self.sifter.search(query, $.extend(options, {score: calculateScore}));
					self.currentResults = result;
				} else {
					result = $.extend(true, {}, self.currentResults);
				}
		
				// filter out selected items
				if (settings.hideSelected) {
					for (i = result.items.length - 1; i >= 0; i--) {
						if (self.items.indexOf(hash_key(result.items[i].id)) !== -1) {
							result.items.splice(i, 1);
						}
					}
				}
		
				return result;
			},
		
			/**
			 * Refreshes the list of available options shown
			 * in the autocomplete dropdown menu.
			 *
			 * @param {boolean} triggerDropdown
			 */
			refreshOptions: function(triggerDropdown) {
				var i, j, k, n, groups, groups_order, option, option_html, optgroup, optgroups, html, html_children, has_create_option;
				var $active, $active_before, $create;
		
				if (typeof triggerDropdown === 'undefined') {
					triggerDropdown = true;
				}
		
				var self              = this;
				var query             = $.trim(self.$control_input.val());
				var results           = self.search(query);
				var $dropdown_content = self.$dropdown_content;
				var active_before     = self.$activeOption && hash_key(self.$activeOption.attr('data-value'));
		
				// build markup
				n = results.items.length;
				if (typeof self.settings.maxOptions === 'number') {
					n = Math.min(n, self.settings.maxOptions);
				}
		
				// render and group available options individually
				groups = {};
				groups_order = [];
		
				for (i = 0; i < n; i++) {
					option      = self.options[results.items[i].id];
					option_html = self.render('option', option);
					optgroup    = option[self.settings.optgroupField] || '';
					optgroups   = $.isArray(optgroup) ? optgroup : [optgroup];
		
					for (j = 0, k = optgroups && optgroups.length; j < k; j++) {
						optgroup = optgroups[j];
						if (!self.optgroups.hasOwnProperty(optgroup)) {
							optgroup = '';
						}
						if (!groups.hasOwnProperty(optgroup)) {
							groups[optgroup] = document.createDocumentFragment();
							groups_order.push(optgroup);
						}
						groups[optgroup].appendChild(option_html);
					}
				}
		
				// sort optgroups
				if (this.settings.lockOptgroupOrder) {
					groups_order.sort(function(a, b) {
						var a_order = self.optgroups[a].$order || 0;
						var b_order = self.optgroups[b].$order || 0;
						return a_order - b_order;
					});
				}
		
				// render optgroup headers & join groups
				html = document.createDocumentFragment();
				for (i = 0, n = groups_order.length; i < n; i++) {
					optgroup = groups_order[i];
					if (self.optgroups.hasOwnProperty(optgroup) && groups[optgroup].childNodes.length) {
						// render the optgroup header and options within it,
						// then pass it to the wrapper template
						html_children = document.createDocumentFragment();
						html_children.appendChild(self.render('optgroup_header', self.optgroups[optgroup]));
						html_children.appendChild(groups[optgroup]);
		
						html.appendChild(self.render('optgroup', $.extend({}, self.optgroups[optgroup], {
							html: domToString(html_children),
							dom:  html_children
						})));
					} else {
						html.appendChild(groups[optgroup]);
					}
				}
		
				$dropdown_content.html(html);
		
				// highlight matching terms inline
				if (self.settings.highlight && results.query.length && results.tokens.length) {
					$dropdown_content.removeHighlight();
					for (i = 0, n = results.tokens.length; i < n; i++) {
						highlight($dropdown_content, results.tokens[i].regex);
					}
				}
		
				// add "selected" class to selected options
				if (!self.settings.hideSelected) {
					for (i = 0, n = self.items.length; i < n; i++) {
						self.getOption(self.items[i]).addClass('selected');
					}
				}
		
				// add create option
				has_create_option = self.canCreate(query);
				if (has_create_option) {
					$dropdown_content.prepend(self.render('option_create', {input: query}));
					$create = $($dropdown_content[0].childNodes[0]);
				}
		
				// activate
				self.hasOptions = results.items.length > 0 || has_create_option;
				if (self.hasOptions) {
					if (results.items.length > 0) {
						$active_before = active_before && self.getOption(active_before);
						if ($active_before && $active_before.length) {
							$active = $active_before;
						} else if (self.settings.mode === 'single' && self.items.length) {
							$active = self.getOption(self.items[0]);
						}
						if (!$active || !$active.length) {
							if ($create && !self.settings.addPrecedence) {
								$active = self.getAdjacentOption($create, 1);
							} else {
								$active = $dropdown_content.find('[data-selectable]:first');
							}
						}
					} else {
						$active = $create;
					}
					self.setActiveOption($active);
					if (triggerDropdown && !self.isOpen) { self.open(); }
				} else {
					self.setActiveOption(null);
					if (triggerDropdown && self.isOpen) { self.close(); }
				}
			},
		
			/**
			 * Adds an available option. If it already exists,
			 * nothing will happen. Note: this does not refresh
			 * the options list dropdown (use `refreshOptions`
			 * for that).
			 *
			 * Usage:
			 *
			 *   this.addOption(data)
			 *
			 * @param {object|array} data
			 */
			addOption: function(data) {
				var i, n, value, self = this;
		
				if ($.isArray(data)) {
					for (i = 0, n = data.length; i < n; i++) {
						self.addOption(data[i]);
					}
					return;
				}
		
				if (value = self.registerOption(data)) {
					self.userOptions[value] = true;
					self.lastQuery = null;
					self.trigger('option_add', value, data);
				}
			},
		
			/**
			 * Registers an option to the pool of options.
			 *
			 * @param {object} data
			 * @return {boolean|string}
			 */
			registerOption: function(data) {
				var key = hash_key(data[this.settings.valueField]);
				if (typeof key === 'undefined' || key === null || this.options.hasOwnProperty(key)) return false;
				data.$order = data.$order || ++this.order;
				this.options[key] = data;
				return key;
			},
		
			/**
			 * Registers an option group to the pool of option groups.
			 *
			 * @param {object} data
			 * @return {boolean|string}
			 */
			registerOptionGroup: function(data) {
				var key = hash_key(data[this.settings.optgroupValueField]);
				if (!key) return false;
		
				data.$order = data.$order || ++this.order;
				this.optgroups[key] = data;
				return key;
			},
		
			/**
			 * Registers a new optgroup for options
			 * to be bucketed into.
			 *
			 * @param {string} id
			 * @param {object} data
			 */
			addOptionGroup: function(id, data) {
				data[this.settings.optgroupValueField] = id;
				if (id = this.registerOptionGroup(data)) {
					this.trigger('optgroup_add', id, data);
				}
			},
		
			/**
			 * Removes an existing option group.
			 *
			 * @param {string} id
			 */
			removeOptionGroup: function(id) {
				if (this.optgroups.hasOwnProperty(id)) {
					delete this.optgroups[id];
					this.renderCache = {};
					this.trigger('optgroup_remove', id);
				}
			},
		
			/**
			 * Clears all existing option groups.
			 */
			clearOptionGroups: function() {
				this.optgroups = {};
				this.renderCache = {};
				this.trigger('optgroup_clear');
			},
		
			/**
			 * Updates an option available for selection. If
			 * it is visible in the selected items or options
			 * dropdown, it will be re-rendered automatically.
			 *
			 * @param {string} value
			 * @param {object} data
			 */
			updateOption: function(value, data) {
				var self = this;
				var $item, $item_new;
				var value_new, index_item, cache_items, cache_options, order_old;
		
				value     = hash_key(value);
				value_new = hash_key(data[self.settings.valueField]);
		
				// sanity checks
				if (value === null) return;
				if (!self.options.hasOwnProperty(value)) return;
				if (typeof value_new !== 'string') throw new Error('Value must be set in option data');
		
				order_old = self.options[value].$order;
		
				// update references
				if (value_new !== value) {
					delete self.options[value];
					index_item = self.items.indexOf(value);
					if (index_item !== -1) {
						self.items.splice(index_item, 1, value_new);
					}
				}
				data.$order = data.$order || order_old;
				self.options[value_new] = data;
		
				// invalidate render cache
				cache_items = self.renderCache['item'];
				cache_options = self.renderCache['option'];
		
				if (cache_items) {
					delete cache_items[value];
					delete cache_items[value_new];
				}
				if (cache_options) {
					delete cache_options[value];
					delete cache_options[value_new];
				}
		
				// update the item if it's selected
				if (self.items.indexOf(value_new) !== -1) {
					$item = self.getItem(value);
					$item_new = $(self.render('item', data));
					if ($item.hasClass('active')) $item_new.addClass('active');
					$item.replaceWith($item_new);
				}
		
				// invalidate last query because we might have updated the sortField
				self.lastQuery = null;
		
				// update dropdown contents
				if (self.isOpen) {
					self.refreshOptions(false);
				}
			},
		
			/**
			 * Removes a single option.
			 *
			 * @param {string} value
			 * @param {boolean} silent
			 */
			removeOption: function(value, silent) {
				var self = this;
				value = hash_key(value);
		
				var cache_items = self.renderCache['item'];
				var cache_options = self.renderCache['option'];
				if (cache_items) delete cache_items[value];
				if (cache_options) delete cache_options[value];
		
				delete self.userOptions[value];
				delete self.options[value];
				self.lastQuery = null;
				self.trigger('option_remove', value);
				self.removeItem(value, silent);
			},
		
			/**
			 * Clears all options.
			 */
			clearOptions: function() {
				var self = this;
		
				self.loadedSearches = {};
				self.userOptions = {};
				self.renderCache = {};
				self.options = self.sifter.items = {};
				self.lastQuery = null;
				self.trigger('option_clear');
				self.clear();
			},
		
			/**
			 * Returns the jQuery element of the option
			 * matching the given value.
			 *
			 * @param {string} value
			 * @returns {object}
			 */
			getOption: function(value) {
				return this.getElementWithValue(value, this.$dropdown_content.find('[data-selectable]'));
			},
		
			/**
			 * Returns the jQuery element of the next or
			 * previous selectable option.
			 *
			 * @param {object} $option
			 * @param {int} direction  can be 1 for next or -1 for previous
			 * @return {object}
			 */
			getAdjacentOption: function($option, direction) {
				var $options = this.$dropdown.find('[data-selectable]');
				var index    = $options.index($option) + direction;
		
				return index >= 0 && index < $options.length ? $options.eq(index) : $();
			},
		
			/**
			 * Finds the first element with a "data-value" attribute
			 * that matches the given value.
			 *
			 * @param {mixed} value
			 * @param {object} $els
			 * @return {object}
			 */
			getElementWithValue: function(value, $els) {
				value = hash_key(value);
		
				if (typeof value !== 'undefined' && value !== null) {
					for (var i = 0, n = $els.length; i < n; i++) {
						if ($els[i].getAttribute('data-value') === value) {
							return $($els[i]);
						}
					}
				}
		
				return $();
			},
		
			/**
			 * Returns the jQuery element of the item
			 * matching the given value.
			 *
			 * @param {string} value
			 * @returns {object}
			 */
			getItem: function(value) {
				return this.getElementWithValue(value, this.$control.children());
			},
		
			/**
			 * "Selects" multiple items at once. Adds them to the list
			 * at the current caret position.
			 *
			 * @param {string} value
			 * @param {boolean} silent
			 */
			addItems: function(values, silent) {
				var items = $.isArray(values) ? values : [values];
				for (var i = 0, n = items.length; i < n; i++) {
					this.isPending = (i < n - 1);
					this.addItem(items[i], silent);
				}
			},
		
			/**
			 * "Selects" an item. Adds it to the list
			 * at the current caret position.
			 *
			 * @param {string} value
			 * @param {boolean} silent
			 */
			addItem: function(value, silent) {
				var events = silent ? [] : ['change'];
		
				debounce_events(this, events, function() {
					var $item, $option, $options;
					var self = this;
					var inputMode = self.settings.mode;
					var i, active, value_next, wasFull;
					value = hash_key(value);
		
					if (self.items.indexOf(value) !== -1) {
						if (inputMode === 'single') self.close();
						return;
					}
		
					if (!self.options.hasOwnProperty(value)) return;
					if (inputMode === 'single') self.clear(silent);
					if (inputMode === 'multi' && self.isFull()) return;
		
					$item = $(self.render('item', self.options[value]));
					wasFull = self.isFull();
					self.items.splice(self.caretPos, 0, value);
					self.insertAtCaret($item);
					if (!self.isPending || (!wasFull && self.isFull())) {
						self.refreshState();
					}
		
					if (self.isSetup) {
						$options = self.$dropdown_content.find('[data-selectable]');
		
						// update menu / remove the option (if this is not one item being added as part of series)
						if (!self.isPending) {
							$option = self.getOption(value);
							value_next = self.getAdjacentOption($option, 1).attr('data-value');
							self.refreshOptions(self.isFocused && inputMode !== 'single');
							if (value_next) {
								self.setActiveOption(self.getOption(value_next));
							}
						}
		
						// hide the menu if the maximum number of items have been selected or no options are left
						if (!$options.length || self.isFull()) {
							self.close();
						} else {
							self.positionDropdown();
						}
		
						self.updatePlaceholder();
						self.trigger('item_add', value, $item);
						self.updateOriginalInput({silent: silent});
					}
				});
			},
		
			/**
			 * Removes the selected item matching
			 * the provided value.
			 *
			 * @param {string} value
			 */
			removeItem: function(value, silent) {
				var self = this;
				var $item, i, idx;
		
				$item = (value instanceof $) ? value : self.getItem(value);
				value = hash_key($item.attr('data-value'));
				i = self.items.indexOf(value);
		
				if (i !== -1) {
					$item.remove();
					if ($item.hasClass('active')) {
						idx = self.$activeItems.indexOf($item[0]);
						self.$activeItems.splice(idx, 1);
					}
		
					self.items.splice(i, 1);
					self.lastQuery = null;
					if (!self.settings.persist && self.userOptions.hasOwnProperty(value)) {
						self.removeOption(value, silent);
					}
		
					if (i < self.caretPos) {
						self.setCaret(self.caretPos - 1);
					}
		
					self.refreshState();
					self.updatePlaceholder();
					self.updateOriginalInput({silent: silent});
					self.positionDropdown();
					self.trigger('item_remove', value, $item);
				}
			},
		
			/**
			 * Invokes the `create` method provided in the
			 * selectize options that should provide the data
			 * for the new item, given the user input.
			 *
			 * Once this completes, it will be added
			 * to the item list.
			 *
			 * @param {string} value
			 * @param {boolean} [triggerDropdown]
			 * @param {function} [callback]
			 * @return {boolean}
			 */
			createItem: function(input, triggerDropdown) {
				var self  = this;
				var caret = self.caretPos;
				input = input || $.trim(self.$control_input.val() || '');
		
				var callback = arguments[arguments.length - 1];
				if (typeof callback !== 'function') callback = function() {};
		
				if (typeof triggerDropdown !== 'boolean') {
					triggerDropdown = true;
				}
		
				if (!self.canCreate(input)) {
					callback();
					return false;
				}
		
				self.lock();
		
				var setup = (typeof self.settings.create === 'function') ? this.settings.create : function(input) {
					var data = {};
					data[self.settings.labelField] = input;
					data[self.settings.valueField] = input;
					return data;
				};
		
				var create = once(function(data) {
					self.unlock();
		
					if (!data || typeof data !== 'object') return callback();
					var value = hash_key(data[self.settings.valueField]);
					if (typeof value !== 'string') return callback();
		
					self.setTextboxValue('');
					self.addOption(data);
					self.setCaret(caret);
					self.addItem(value);
					self.refreshOptions(triggerDropdown && self.settings.mode !== 'single');
					callback(data);
				});
		
				var output = setup.apply(this, [input, create]);
				if (typeof output !== 'undefined') {
					create(output);
				}
		
				return true;
			},
		
			/**
			 * Re-renders the selected item lists.
			 */
			refreshItems: function() {
				this.lastQuery = null;
		
				if (this.isSetup) {
					this.addItem(this.items);
				}
		
				this.refreshState();
				this.updateOriginalInput();
			},
		
			/**
			 * Updates all state-dependent attributes
			 * and CSS classes.
			 */
			refreshState: function() {
				this.refreshValidityState();
				this.refreshClasses();
			},
		
			/**
			 * Update the `required` attribute of both input and control input.
			 *
			 * The `required` property needs to be activated on the control input
			 * for the error to be displayed at the right place. `required` also
			 * needs to be temporarily deactivated on the input since the input is
			 * hidden and can't show errors.
			 */
			refreshValidityState: function() {
				if (!this.isRequired) return false;
		
				var invalid = !this.items.length;
		
				this.isInvalid = invalid;
				this.$control_input.prop('required', invalid);
				this.$input.prop('required', !invalid);
			},
		
			/**
			 * Updates all state-dependent CSS classes.
			 */
			refreshClasses: function() {
				var self     = this;
				var isFull   = self.isFull();
				var isLocked = self.isLocked;
		
				self.$wrapper
					.toggleClass('rtl', self.rtl);
		
				self.$control
					.toggleClass('focus', self.isFocused)
					.toggleClass('disabled', self.isDisabled)
					.toggleClass('required', self.isRequired)
					.toggleClass('invalid', self.isInvalid)
					.toggleClass('locked', isLocked)
					.toggleClass('full', isFull).toggleClass('not-full', !isFull)
					.toggleClass('input-active', self.isFocused && !self.isInputHidden)
					.toggleClass('dropdown-active', self.isOpen)
					.toggleClass('has-options', !$.isEmptyObject(self.options))
					.toggleClass('has-items', self.items.length > 0);
		
				self.$control_input.data('grow', !isFull && !isLocked);
			},
		
			/**
			 * Determines whether or not more items can be added
			 * to the control without exceeding the user-defined maximum.
			 *
			 * @returns {boolean}
			 */
			isFull: function() {
				return this.settings.maxItems !== null && this.items.length >= this.settings.maxItems;
			},
		
			/**
			 * Refreshes the original <select> or <input>
			 * element to reflect the current state.
			 */
			updateOriginalInput: function(opts) {
				var i, n, options, label, self = this;
				opts = opts || {};
		
				if (self.tagType === TAG_SELECT) {
					options = [];
					for (i = 0, n = self.items.length; i < n; i++) {
						label = self.options[self.items[i]][self.settings.labelField] || '';
						options.push('<option value="' + escape_html(self.items[i]) + '" selected="selected">' + escape_html(label) + '</option>');
					}
					if (!options.length && !this.$input.attr('multiple')) {
						options.push('<option value="" selected="selected"></option>');
					}
					self.$input.html(options.join(''));
				} else {
					self.$input.val(self.getValue());
					self.$input.attr('value',self.$input.val());
				}
		
				if (self.isSetup) {
					if (!opts.silent) {
						self.trigger('change', self.$input.val());
					}
				}
			},
		
			/**
			 * Shows/hide the input placeholder depending
			 * on if there items in the list already.
			 */
			updatePlaceholder: function() {
				if (!this.settings.placeholder) return;
				var $input = this.$control_input;
		
				if (this.items.length) {
					$input.removeAttr('placeholder');
				} else {
					$input.attr('placeholder', this.settings.placeholder);
				}
				$input.triggerHandler('update', {force: true});
			},
		
			/**
			 * Shows the autocomplete dropdown containing
			 * the available options.
			 */
			open: function() {
				var self = this;
		
				if (self.isLocked || self.isOpen || (self.settings.mode === 'multi' && self.isFull())) return;
				self.focus();
				self.isOpen = true;
				self.refreshState();
				self.$dropdown.css({visibility: 'hidden', display: 'block'});
				self.positionDropdown();
				self.$dropdown.css({visibility: 'visible'});
				self.trigger('dropdown_open', self.$dropdown);
			},
		
			/**
			 * Closes the autocomplete dropdown menu.
			 */
			close: function() {
				var self = this;
				var trigger = self.isOpen;
		
				if (self.settings.mode === 'single' && self.items.length) {
					self.hideInput();
					self.$control_input.blur(); // close keyboard on iOS
				}
		
				self.isOpen = false;
				self.$dropdown.hide();
				self.setActiveOption(null);
				self.refreshState();
		
				if (trigger) self.trigger('dropdown_close', self.$dropdown);
			},
		
			/**
			 * Calculates and applies the appropriate
			 * position of the dropdown.
			 */
			positionDropdown: function() {
				var $control = this.$control;
				var offset = this.settings.dropdownParent === 'body' ? $control.offset() : $control.position();
				offset.top += $control.outerHeight(true);
		
				this.$dropdown.css({
					width : $control.outerWidth(),
					top   : offset.top,
					left  : offset.left
				});
			},
		
			/**
			 * Resets / clears all selected items
			 * from the control.
			 *
			 * @param {boolean} silent
			 */
			clear: function(silent) {
				var self = this;
		
				if (!self.items.length) return;
				self.$control.children(':not(input)').remove();
				self.items = [];
				self.lastQuery = null;
				self.setCaret(0);
				self.setActiveItem(null);
				self.updatePlaceholder();
				self.updateOriginalInput({silent: silent});
				self.refreshState();
				self.showInput();
				self.trigger('clear');
			},
		
			/**
			 * A helper method for inserting an element
			 * at the current caret position.
			 *
			 * @param {object} $el
			 */
			insertAtCaret: function($el) {
				var caret = Math.min(this.caretPos, this.items.length);
				if (caret === 0) {
					this.$control.prepend($el);
				} else {
					$(this.$control[0].childNodes[caret]).before($el);
				}
				this.setCaret(caret + 1);
			},
		
			/**
			 * Removes the current selected item(s).
			 *
			 * @param {object} e (optional)
			 * @returns {boolean}
			 */
			deleteSelection: function(e) {
				var i, n, direction, selection, values, caret, option_select, $option_select, $tail;
				var self = this;
		
				direction = (e && e.keyCode === KEY_BACKSPACE) ? -1 : 1;
				selection = getSelection(self.$control_input[0]);
		
				if (self.$activeOption && !self.settings.hideSelected) {
					option_select = self.getAdjacentOption(self.$activeOption, -1).attr('data-value');
				}
		
				// determine items that will be removed
				values = [];
		
				if (self.$activeItems.length) {
					$tail = self.$control.children('.active:' + (direction > 0 ? 'last' : 'first'));
					caret = self.$control.children(':not(input)').index($tail);
					if (direction > 0) { caret++; }
		
					for (i = 0, n = self.$activeItems.length; i < n; i++) {
						values.push($(self.$activeItems[i]).attr('data-value'));
					}
					if (e) {
						e.preventDefault();
						e.stopPropagation();
					}
				} else if ((self.isFocused || self.settings.mode === 'single') && self.items.length) {
					if (direction < 0 && selection.start === 0 && selection.length === 0) {
						values.push(self.items[self.caretPos - 1]);
					} else if (direction > 0 && selection.start === self.$control_input.val().length) {
						values.push(self.items[self.caretPos]);
					}
				}
		
				// allow the callback to abort
				if (!values.length || (typeof self.settings.onDelete === 'function' && self.settings.onDelete.apply(self, [values]) === false)) {
					return false;
				}
		
				// perform removal
				if (typeof caret !== 'undefined') {
					self.setCaret(caret);
				}
				while (values.length) {
					self.removeItem(values.pop());
				}
		
				self.showInput();
				self.positionDropdown();
				self.refreshOptions(true);
		
				// select previous option
				if (option_select) {
					$option_select = self.getOption(option_select);
					if ($option_select.length) {
						self.setActiveOption($option_select);
					}
				}
		
				return true;
			},
		
			/**
			 * Selects the previous / next item (depending
			 * on the `direction` argument).
			 *
			 * > 0 - right
			 * < 0 - left
			 *
			 * @param {int} direction
			 * @param {object} e (optional)
			 */
			advanceSelection: function(direction, e) {
				var tail, selection, idx, valueLength, cursorAtEdge, $tail;
				var self = this;
		
				if (direction === 0) return;
				if (self.rtl) direction *= -1;
		
				tail = direction > 0 ? 'last' : 'first';
				selection = getSelection(self.$control_input[0]);
		
				if (self.isFocused && !self.isInputHidden) {
					valueLength = self.$control_input.val().length;
					cursorAtEdge = direction < 0
						? selection.start === 0 && selection.length === 0
						: selection.start === valueLength;
		
					if (cursorAtEdge && !valueLength) {
						self.advanceCaret(direction, e);
					}
				} else {
					$tail = self.$control.children('.active:' + tail);
					if ($tail.length) {
						idx = self.$control.children(':not(input)').index($tail);
						self.setActiveItem(null);
						self.setCaret(direction > 0 ? idx + 1 : idx);
					}
				}
			},
		
			/**
			 * Moves the caret left / right.
			 *
			 * @param {int} direction
			 * @param {object} e (optional)
			 */
			advanceCaret: function(direction, e) {
				var self = this, fn, $adj;
		
				if (direction === 0) return;
		
				fn = direction > 0 ? 'next' : 'prev';
				if (self.isShiftDown) {
					$adj = self.$control_input[fn]();
					if ($adj.length) {
						self.hideInput();
						self.setActiveItem($adj);
						e && e.preventDefault();
					}
				} else {
					self.setCaret(self.caretPos + direction);
				}
			},
		
			/**
			 * Moves the caret to the specified index.
			 *
			 * @param {int} i
			 */
			setCaret: function(i) {
				var self = this;
		
				if (self.settings.mode === 'single') {
					i = self.items.length;
				} else {
					i = Math.max(0, Math.min(self.items.length, i));
				}
		
				if(!self.isPending) {
					// the input must be moved by leaving it in place and moving the
					// siblings, due to the fact that focus cannot be restored once lost
					// on mobile webkit devices
					var j, n, fn, $children, $child;
					$children = self.$control.children(':not(input)');
					for (j = 0, n = $children.length; j < n; j++) {
						$child = $($children[j]).detach();
						if (j <  i) {
							self.$control_input.before($child);
						} else {
							self.$control.append($child);
						}
					}
				}
		
				self.caretPos = i;
			},
		
			/**
			 * Disables user input on the control. Used while
			 * items are being asynchronously created.
			 */
			lock: function() {
				this.close();
				this.isLocked = true;
				this.refreshState();
			},
		
			/**
			 * Re-enables user input on the control.
			 */
			unlock: function() {
				this.isLocked = false;
				this.refreshState();
			},
		
			/**
			 * Disables user input on the control completely.
			 * While disabled, it cannot receive focus.
			 */
			disable: function() {
				var self = this;
				self.$input.prop('disabled', true);
				self.$control_input.prop('disabled', true).prop('tabindex', -1);
				self.isDisabled = true;
				self.lock();
			},
		
			/**
			 * Enables the control so that it can respond
			 * to focus and user input.
			 */
			enable: function() {
				var self = this;
				self.$input.prop('disabled', false);
				self.$control_input.prop('disabled', false).prop('tabindex', self.tabIndex);
				self.isDisabled = false;
				self.unlock();
			},
		
			/**
			 * Completely destroys the control and
			 * unbinds all event listeners so that it can
			 * be garbage collected.
			 */
			destroy: function() {
				var self = this;
				var eventNS = self.eventNS;
				var revertSettings = self.revertSettings;
		
				self.trigger('destroy');
				self.off();
				self.$wrapper.remove();
				self.$dropdown.remove();
		
				self.$input
					.html('')
					.append(revertSettings.$children)
					.removeAttr('tabindex')
					.removeClass('selectized')
					.attr({tabindex: revertSettings.tabindex})
					.show();
		
				self.$control_input.removeData('grow');
				self.$input.removeData('selectize');
		
				$(window).off(eventNS);
				$(document).off(eventNS);
				$(document.body).off(eventNS);
		
				delete self.$input[0].selectize;
			},
		
			/**
			 * A helper method for rendering "item" and
			 * "option" templates, given the data.
			 *
			 * @param {string} templateName
			 * @param {object} data
			 * @returns {string}
			 */
			render: function(templateName, data) {
				var value, id, label;
				var html = '';
				var cache = false;
				var self = this;
				var regex_tag = /^[\t \r\n]*<([a-z][a-z0-9\-_]*(?:\:[a-z][a-z0-9\-_]*)?)/i;
		
				if (templateName === 'option' || templateName === 'item') {
					value = hash_key(data[self.settings.valueField]);
					cache = !!value;
				}
		
				// pull markup from cache if it exists
				if (cache) {
					if (!isset(self.renderCache[templateName])) {
						self.renderCache[templateName] = {};
					}
					if (self.renderCache[templateName].hasOwnProperty(value)) {
						return self.renderCache[templateName][value];
					}
				}
		
				// render markup
				html = $(self.settings.render[templateName].apply(this, [data, escape_html]));
		
				// add mandatory attributes
				if (templateName === 'option' || templateName === 'option_create') {
					html.attr('data-selectable', '');
				}
				else if (templateName === 'optgroup') {
					id = data[self.settings.optgroupValueField] || '';
					html.attr('data-group', id);
				}
				if (templateName === 'option' || templateName === 'item') {
					html.attr('data-value', value || '');
				}
		
				// update cache
				if (cache) {
					self.renderCache[templateName][value] = html[0];
				}
		
				return html[0];
			},
		
			/**
			 * Clears the render cache for a template. If
			 * no template is given, clears all render
			 * caches.
			 *
			 * @param {string} templateName
			 */
			clearCache: function(templateName) {
				var self = this;
				if (typeof templateName === 'undefined') {
					self.renderCache = {};
				} else {
					delete self.renderCache[templateName];
				}
			},
		
			/**
			 * Determines whether or not to display the
			 * create item prompt, given a user input.
			 *
			 * @param {string} input
			 * @return {boolean}
			 */
			canCreate: function(input) {
				var self = this;
				if (!self.settings.create) return false;
				var filter = self.settings.createFilter;
				return input.length
					&& (typeof filter !== 'function' || filter.apply(self, [input]))
					&& (typeof filter !== 'string' || new RegExp(filter).test(input))
					&& (!(filter instanceof RegExp) || filter.test(input));
			}
		
		});
		
		
		Selectize.count = 0;
		Selectize.defaults = {
			options: [],
			optgroups: [],
		
			plugins: [],
			delimiter: ',',
			splitOn: null, // regexp or string for splitting up values from a paste command
			persist: true,
			diacritics: true,
			create: false,
			createOnBlur: false,
			createFilter: null,
			highlight: true,
			openOnFocus: true,
			maxOptions: 1000,
			maxItems: null,
			hideSelected: null,
			addPrecedence: false,
			selectOnTab: false,
			preload: false,
			allowEmptyOption: false,
			closeAfterSelect: false,
		
			scrollDuration: 60,
			loadThrottle: 300,
			loadingClass: 'loading',
		
			dataAttr: 'data-data',
			optgroupField: 'optgroup',
			valueField: 'value',
			labelField: 'text',
			optgroupLabelField: 'label',
			optgroupValueField: 'value',
			lockOptgroupOrder: false,
		
			sortField: '$order',
			searchField: ['text'],
			searchConjunction: 'and',
		
			mode: null,
			wrapperClass: 'selectize-control',
			inputClass: 'selectize-input',
			dropdownClass: 'selectize-dropdown',
			dropdownContentClass: 'selectize-dropdown-content',
		
			dropdownParent: null,
		
			copyClassesToDropdown: true,
		
			/*
			load                 : null, // function(query, callback) { ... }
			score                : null, // function(search) { ... }
			onInitialize         : null, // function() { ... }
			onChange             : null, // function(value) { ... }
			onItemAdd            : null, // function(value, $item) { ... }
			onItemRemove         : null, // function(value) { ... }
			onClear              : null, // function() { ... }
			onOptionAdd          : null, // function(value, data) { ... }
			onOptionRemove       : null, // function(value) { ... }
			onOptionClear        : null, // function() { ... }
			onOptionGroupAdd     : null, // function(id, data) { ... }
			onOptionGroupRemove  : null, // function(id) { ... }
			onOptionGroupClear   : null, // function() { ... }
			onDropdownOpen       : null, // function($dropdown) { ... }
			onDropdownClose      : null, // function($dropdown) { ... }
			onType               : null, // function(str) { ... }
			onDelete             : null, // function(values) { ... }
			*/
		
			render: {
				/*
				item: null,
				optgroup: null,
				optgroup_header: null,
				option: null,
				option_create: null
				*/
			}
		};
		
		
		$.fn.selectize = function(settings_user) {
			var defaults             = $.fn.selectize.defaults;
			var settings             = $.extend({}, defaults, settings_user);
			var attr_data            = settings.dataAttr;
			var field_label          = settings.labelField;
			var field_value          = settings.valueField;
			var field_optgroup       = settings.optgroupField;
			var field_optgroup_label = settings.optgroupLabelField;
			var field_optgroup_value = settings.optgroupValueField;
		
			/**
			 * Initializes selectize from a <input type="text"> element.
			 *
			 * @param {object} $input
			 * @param {object} settings_element
			 */
			var init_textbox = function($input, settings_element) {
				var i, n, values, option;
		
				var data_raw = $input.attr(attr_data);
		
				if (!data_raw) {
					var value = $.trim($input.val() || '');
					if (!settings.allowEmptyOption && !value.length) return;
					values = value.split(settings.delimiter);
					for (i = 0, n = values.length; i < n; i++) {
						option = {};
						option[field_label] = values[i];
						option[field_value] = values[i];
						settings_element.options.push(option);
					}
					settings_element.items = values;
				} else {
					settings_element.options = JSON.parse(data_raw);
					for (i = 0, n = settings_element.options.length; i < n; i++) {
						settings_element.items.push(settings_element.options[i][field_value]);
					}
				}
			};
		
			/**
			 * Initializes selectize from a <select> element.
			 *
			 * @param {object} $input
			 * @param {object} settings_element
			 */
			var init_select = function($input, settings_element) {
				var i, n, tagName, $children, order = 0;
				var options = settings_element.options;
				var optionsMap = {};
		
				var readData = function($el) {
					var data = attr_data && $el.attr(attr_data);
					if (typeof data === 'string' && data.length) {
						return JSON.parse(data);
					}
					return null;
				};
		
				var addOption = function($option, group) {
					$option = $($option);
		
					var value = hash_key($option.val());
					if (!value && !settings.allowEmptyOption) return;
		
					// if the option already exists, it's probably been
					// duplicated in another optgroup. in this case, push
					// the current group to the "optgroup" property on the
					// existing option so that it's rendered in both places.
					if (optionsMap.hasOwnProperty(value)) {
						if (group) {
							var arr = optionsMap[value][field_optgroup];
							if (!arr) {
								optionsMap[value][field_optgroup] = group;
							} else if (!$.isArray(arr)) {
								optionsMap[value][field_optgroup] = [arr, group];
							} else {
								arr.push(group);
							}
						}
						return;
					}
		
					var option             = readData($option) || {};
					option[field_label]    = option[field_label] || $option.text();
					option[field_value]    = option[field_value] || value;
					option[field_optgroup] = option[field_optgroup] || group;
		
					optionsMap[value] = option;
					options.push(option);
		
					if ($option.is(':selected')) {
						settings_element.items.push(value);
					}
				};
		
				var addGroup = function($optgroup) {
					var i, n, id, optgroup, $options;
		
					$optgroup = $($optgroup);
					id = $optgroup.attr('label');
		
					if (id) {
						optgroup = readData($optgroup) || {};
						optgroup[field_optgroup_label] = id;
						optgroup[field_optgroup_value] = id;
						settings_element.optgroups.push(optgroup);
					}
		
					$options = $('option', $optgroup);
					for (i = 0, n = $options.length; i < n; i++) {
						addOption($options[i], id);
					}
				};
		
				settings_element.maxItems = $input.attr('multiple') ? null : 1;
		
				$children = $input.children();
				for (i = 0, n = $children.length; i < n; i++) {
					tagName = $children[i].tagName.toLowerCase();
					if (tagName === 'optgroup') {
						addGroup($children[i]);
					} else if (tagName === 'option') {
						addOption($children[i]);
					}
				}
			};
		
			return this.each(function() {
				if (this.selectize) return;
		
				var instance;
				var $input = $(this);
				var tag_name = this.tagName.toLowerCase();
				var placeholder = $input.attr('placeholder') || $input.attr('data-placeholder');
				if (!placeholder && !settings.allowEmptyOption) {
					placeholder = $input.children('option[value=""]').text();
				}
		
				var settings_element = {
					'placeholder' : placeholder,
					'options'     : [],
					'optgroups'   : [],
					'items'       : []
				};
		
				if (tag_name === 'select') {
					init_select($input, settings_element);
				} else {
					init_textbox($input, settings_element);
				}
		
				instance = new Selectize($input, $.extend(true, {}, defaults, settings_element, settings_user));
			});
		};
		
		$.fn.selectize.defaults = Selectize.defaults;
		$.fn.selectize.support = {
			validity: SUPPORTS_VALIDITY_API
		};
		
		
		Selectize.define('drag_drop', function(options) {
			if (!$.fn.sortable) throw new Error('The "drag_drop" plugin requires jQuery UI "sortable".');
			if (this.settings.mode !== 'multi') return;
			var self = this;
		
			self.lock = (function() {
				var original = self.lock;
				return function() {
					var sortable = self.$control.data('sortable');
					if (sortable) sortable.disable();
					return original.apply(self, arguments);
				};
			})();
		
			self.unlock = (function() {
				var original = self.unlock;
				return function() {
					var sortable = self.$control.data('sortable');
					if (sortable) sortable.enable();
					return original.apply(self, arguments);
				};
			})();
		
			self.setup = (function() {
				var original = self.setup;
				return function() {
					original.apply(this, arguments);
		
					var $control = self.$control.sortable({
						items: '[data-value]',
						forcePlaceholderSize: true,
						disabled: self.isLocked,
						start: function(e, ui) {
							ui.placeholder.css('width', ui.helper.css('width'));
							$control.css({overflow: 'visible'});
						},
						stop: function() {
							$control.css({overflow: 'hidden'});
							var active = self.$activeItems ? self.$activeItems.slice() : null;
							var values = [];
							$control.children('[data-value]').each(function() {
								values.push($(this).attr('data-value'));
							});
							self.setValue(values);
							self.setActiveItem(active);
						}
					});
				};
			})();
		
		});
		
		Selectize.define('dropdown_header', function(options) {
			var self = this;
		
			options = $.extend({
				title         : 'Untitled',
				headerClass   : 'selectize-dropdown-header',
				titleRowClass : 'selectize-dropdown-header-title',
				labelClass    : 'selectize-dropdown-header-label',
				closeClass    : 'selectize-dropdown-header-close',
		
				html: function(data) {
					return (
						'<div class="' + data.headerClass + '">' +
							'<div class="' + data.titleRowClass + '">' +
								'<span class="' + data.labelClass + '">' + data.title + '</span>' +
								'<a href="javascript:void(0)" class="' + data.closeClass + '">&times;</a>' +
							'</div>' +
						'</div>'
					);
				}
			}, options);
		
			self.setup = (function() {
				var original = self.setup;
				return function() {
					original.apply(self, arguments);
					self.$dropdown_header = $(options.html(options));
					self.$dropdown.prepend(self.$dropdown_header);
				};
			})();
		
		});
		
		Selectize.define('optgroup_columns', function(options) {
			var self = this;
		
			options = $.extend({
				equalizeWidth  : true,
				equalizeHeight : true
			}, options);
		
			this.getAdjacentOption = function($option, direction) {
				var $options = $option.closest('[data-group]').find('[data-selectable]');
				var index    = $options.index($option) + direction;
		
				return index >= 0 && index < $options.length ? $options.eq(index) : $();
			};
		
			this.onKeyDown = (function() {
				var original = self.onKeyDown;
				return function(e) {
					var index, $option, $options, $optgroup;
		
					if (this.isOpen && (e.keyCode === KEY_LEFT || e.keyCode === KEY_RIGHT)) {
						self.ignoreHover = true;
						$optgroup = this.$activeOption.closest('[data-group]');
						index = $optgroup.find('[data-selectable]').index(this.$activeOption);
		
						if(e.keyCode === KEY_LEFT) {
							$optgroup = $optgroup.prev('[data-group]');
						} else {
							$optgroup = $optgroup.next('[data-group]');
						}
		
						$options = $optgroup.find('[data-selectable]');
						$option  = $options.eq(Math.min($options.length - 1, index));
						if ($option.length) {
							this.setActiveOption($option);
						}
						return;
					}
		
					return original.apply(this, arguments);
				};
			})();
		
			var getScrollbarWidth = function() {
				var div;
				var width = getScrollbarWidth.width;
				var doc = document;
		
				if (typeof width === 'undefined') {
					div = doc.createElement('div');
					div.innerHTML = '<div style="width:50px;height:50px;position:absolute;left:-50px;top:-50px;overflow:auto;"><div style="width:1px;height:100px;"></div></div>';
					div = div.firstChild;
					doc.body.appendChild(div);
					width = getScrollbarWidth.width = div.offsetWidth - div.clientWidth;
					doc.body.removeChild(div);
				}
				return width;
			};
		
			var equalizeSizes = function() {
				var i, n, height_max, width, width_last, width_parent, $optgroups;
		
				$optgroups = $('[data-group]', self.$dropdown_content);
				n = $optgroups.length;
				if (!n || !self.$dropdown_content.width()) return;
		
				if (options.equalizeHeight) {
					height_max = 0;
					for (i = 0; i < n; i++) {
						height_max = Math.max(height_max, $optgroups.eq(i).height());
					}
					$optgroups.css({height: height_max});
				}
		
				if (options.equalizeWidth) {
					width_parent = self.$dropdown_content.innerWidth() - getScrollbarWidth();
					width = Math.round(width_parent / n);
					$optgroups.css({width: width});
					if (n > 1) {
						width_last = width_parent - width * (n - 1);
						$optgroups.eq(n - 1).css({width: width_last});
					}
				}
			};
		
			if (options.equalizeHeight || options.equalizeWidth) {
				hook.after(this, 'positionDropdown', equalizeSizes);
				hook.after(this, 'refreshOptions', equalizeSizes);
			}
		
		
		});
		
		Selectize.define('remove_button', function(options) {
			options = $.extend({
					label     : '&times;',
					title     : 'Remove',
					className : 'remove',
					append    : true
				}, options);
		
				var singleClose = function(thisRef, options) {
		
					options.className = 'remove-single';
		
					var self = thisRef;
					var html = '<a href="javascript:void(0)" class="' + options.className + '" tabindex="-1" title="' + escape_html(options.title) + '">' + options.label + '</a>';
		
					/**
					 * Appends an element as a child (with raw HTML).
					 *
					 * @param {string} html_container
					 * @param {string} html_element
					 * @return {string}
					 */
					var append = function(html_container, html_element) {
						return html_container + html_element;
					};
		
					thisRef.setup = (function() {
						var original = self.setup;
						return function() {
							// override the item rendering method to add the button to each
							if (options.append) {
								var id = $(self.$input.context).attr('id');
								var selectizer = $('#'+id);
		
								var render_item = self.settings.render.item;
								self.settings.render.item = function(data) {
									return append(render_item.apply(thisRef, arguments), html);
								};
							}
		
							original.apply(thisRef, arguments);
		
							// add event listener
							thisRef.$control.on('click', '.' + options.className, function(e) {
								e.preventDefault();
								if (self.isLocked) return;
		
								self.clear();
							});
		
						};
					})();
				};
		
				var multiClose = function(thisRef, options) {
		
					var self = thisRef;
					var html = '<a href="javascript:void(0)" class="' + options.className + '" tabindex="-1" title="' + escape_html(options.title) + '">' + options.label + '</a>';
		
					/**
					 * Appends an element as a child (with raw HTML).
					 *
					 * @param {string} html_container
					 * @param {string} html_element
					 * @return {string}
					 */
					var append = function(html_container, html_element) {
						var pos = html_container.search(/(<\/[^>]+>\s*)$/);
						return html_container.substring(0, pos) + html_element + html_container.substring(pos);
					};
		
					thisRef.setup = (function() {
						var original = self.setup;
						return function() {
							// override the item rendering method to add the button to each
							if (options.append) {
								var render_item = self.settings.render.item;
								self.settings.render.item = function(data) {
									return append(render_item.apply(thisRef, arguments), html);
								};
							}
		
							original.apply(thisRef, arguments);
		
							// add event listener
							thisRef.$control.on('click', '.' + options.className, function(e) {
								e.preventDefault();
								if (self.isLocked) return;
		
								var $item = $(e.currentTarget).parent();
								self.setActiveItem($item);
								if (self.deleteSelection()) {
									self.setCaret(self.items.length);
								}
							});
		
						};
					})();
				};
		
				if (this.settings.mode === 'single') {
					singleClose(this, options);
					return;
				} else {
					multiClose(this, options);
				}
		});
		
		
		Selectize.define('restore_on_backspace', function(options) {
			var self = this;
		
			options.text = options.text || function(option) {
				return option[this.settings.labelField];
			};
		
			this.onKeyDown = (function() {
				var original = self.onKeyDown;
				return function(e) {
					var index, option;
					if (e.keyCode === KEY_BACKSPACE && this.$control_input.val() === '' && !this.$activeItems.length) {
						index = this.caretPos - 1;
						if (index >= 0 && index < this.items.length) {
							option = this.options[this.items[index]];
							if (this.deleteSelection(e)) {
								this.setTextboxValue(options.text.apply(this, [option]));
								this.refreshOptions(true);
							}
							e.preventDefault();
							return;
						}
					}
					return original.apply(this, arguments);
				};
			})();
		});
		
	
		return Selectize;
	}));

/***/ }),
/* 20 */
/***/ (function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_RESULT__;/**
	 * sifter.js
	 * Copyright (c) 2013 Brian Reavis & contributors
	 *
	 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
	 * file except in compliance with the License. You may obtain a copy of the License at:
	 * http://www.apache.org/licenses/LICENSE-2.0
	 *
	 * Unless required by applicable law or agreed to in writing, software distributed under
	 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF
	 * ANY KIND, either express or implied. See the License for the specific language
	 * governing permissions and limitations under the License.
	 *
	 * @author Brian Reavis <brian@thirdroute.com>
	 */
	
	(function(root, factory) {
		if (true) {
			!(__WEBPACK_AMD_DEFINE_FACTORY__ = (factory), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.call(exports, __webpack_require__, exports, module)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
		} else if (typeof exports === 'object') {
			module.exports = factory();
		} else {
			root.Sifter = factory();
		}
	}(this, function() {
	
		/**
		 * Textually searches arrays and hashes of objects
		 * by property (or multiple properties). Designed
		 * specifically for autocomplete.
		 *
		 * @constructor
		 * @param {array|object} items
		 * @param {object} items
		 */
		var Sifter = function(items, settings) {
			this.items = items;
			this.settings = settings || {diacritics: true};
		};
	
		/**
		 * Splits a search string into an array of individual
		 * regexps to be used to match results.
		 *
		 * @param {string} query
		 * @returns {array}
		 */
		Sifter.prototype.tokenize = function(query) {
			query = trim(String(query || '').toLowerCase());
			if (!query || !query.length) return [];
	
			var i, n, regex, letter;
			var tokens = [];
			var words = query.split(/ +/);
	
			for (i = 0, n = words.length; i < n; i++) {
				regex = escape_regex(words[i]);
				if (this.settings.diacritics) {
					for (letter in DIACRITICS) {
						if (DIACRITICS.hasOwnProperty(letter)) {
							regex = regex.replace(new RegExp(letter, 'g'), DIACRITICS[letter]);
						}
					}
				}
				tokens.push({
					string : words[i],
					regex  : new RegExp(regex, 'i')
				});
			}
	
			return tokens;
		};
	
		/**
		 * Iterates over arrays and hashes.
		 *
		 * ```
		 * this.iterator(this.items, function(item, id) {
		 *    // invoked for each item
		 * });
		 * ```
		 *
		 * @param {array|object} object
		 */
		Sifter.prototype.iterator = function(object, callback) {
			var iterator;
			if (is_array(object)) {
				iterator = Array.prototype.forEach || function(callback) {
					for (var i = 0, n = this.length; i < n; i++) {
						callback(this[i], i, this);
					}
				};
			} else {
				iterator = function(callback) {
					for (var key in this) {
						if (this.hasOwnProperty(key)) {
							callback(this[key], key, this);
						}
					}
				};
			}
	
			iterator.apply(object, [callback]);
		};
	
		/**
		 * Returns a function to be used to score individual results.
		 *
		 * Good matches will have a higher score than poor matches.
		 * If an item is not a match, 0 will be returned by the function.
		 *
		 * @param {object|string} search
		 * @param {object} options (optional)
		 * @returns {function}
		 */
		Sifter.prototype.getScoreFunction = function(search, options) {
			var self, fields, tokens, token_count, nesting;
	
			self        = this;
			search      = self.prepareSearch(search, options);
			tokens      = search.tokens;
			fields      = search.options.fields;
			token_count = tokens.length;
			nesting     = search.options.nesting;
	
			/**
			 * Calculates how close of a match the
			 * given value is against a search token.
			 *
			 * @param {mixed} value
			 * @param {object} token
			 * @return {number}
			 */
			var scoreValue = function(value, token) {
				var score, pos;
	
				if (!value) return 0;
				value = String(value || '');
				pos = value.search(token.regex);
				if (pos === -1) return 0;
				score = token.string.length / value.length;
				if (pos === 0) score += 0.5;
				return score;
			};
	
			/**
			 * Calculates the score of an object
			 * against the search query.
			 *
			 * @param {object} token
			 * @param {object} data
			 * @return {number}
			 */
			var scoreObject = (function() {
				var field_count = fields.length;
				if (!field_count) {
					return function() { return 0; };
				}
				if (field_count === 1) {
					return function(token, data) {
						return scoreValue(getattr(data, fields[0], nesting), token);
					};
				}
				return function(token, data) {
					for (var i = 0, sum = 0; i < field_count; i++) {
						sum += scoreValue(getattr(data, fields[i], nesting), token);
					}
					return sum / field_count;
				};
			})();
	
			if (!token_count) {
				return function() { return 0; };
			}
			if (token_count === 1) {
				return function(data) {
					return scoreObject(tokens[0], data);
				};
			}
	
			if (search.options.conjunction === 'and') {
				return function(data) {
					var score;
					for (var i = 0, sum = 0; i < token_count; i++) {
						score = scoreObject(tokens[i], data);
						if (score <= 0) return 0;
						sum += score;
					}
					return sum / token_count;
				};
			} else {
				return function(data) {
					for (var i = 0, sum = 0; i < token_count; i++) {
						sum += scoreObject(tokens[i], data);
					}
					return sum / token_count;
				};
			}
		};
	
		/**
		 * Returns a function that can be used to compare two
		 * results, for sorting purposes. If no sorting should
		 * be performed, `null` will be returned.
		 *
		 * @param {string|object} search
		 * @param {object} options
		 * @return function(a,b)
		 */
		Sifter.prototype.getSortFunction = function(search, options) {
			var i, n, self, field, fields, fields_count, multiplier, multipliers, get_field, implicit_score, sort;
	
			self   = this;
			search = self.prepareSearch(search, options);
			sort   = (!search.query && options.sort_empty) || options.sort;
	
			/**
			 * Fetches the specified sort field value
			 * from a search result item.
			 *
			 * @param  {string} name
			 * @param  {object} result
			 * @return {mixed}
			 */
			get_field = function(name, result) {
				if (name === '$score') return result.score;
				return getattr(self.items[result.id], name, options.nesting);
			};
	
			// parse options
			fields = [];
			if (sort) {
				for (i = 0, n = sort.length; i < n; i++) {
					if (search.query || sort[i].field !== '$score') {
						fields.push(sort[i]);
					}
				}
			}
	
			// the "$score" field is implied to be the primary
			// sort field, unless it's manually specified
			if (search.query) {
				implicit_score = true;
				for (i = 0, n = fields.length; i < n; i++) {
					if (fields[i].field === '$score') {
						implicit_score = false;
						break;
					}
				}
				if (implicit_score) {
					fields.unshift({field: '$score', direction: 'desc'});
				}
			} else {
				for (i = 0, n = fields.length; i < n; i++) {
					if (fields[i].field === '$score') {
						fields.splice(i, 1);
						break;
					}
				}
			}
	
			multipliers = [];
			for (i = 0, n = fields.length; i < n; i++) {
				multipliers.push(fields[i].direction === 'desc' ? -1 : 1);
			}
	
			// build function
			fields_count = fields.length;
			if (!fields_count) {
				return null;
			} else if (fields_count === 1) {
				field = fields[0].field;
				multiplier = multipliers[0];
				return function(a, b) {
					return multiplier * cmp(
						get_field(field, a),
						get_field(field, b)
					);
				};
			} else {
				return function(a, b) {
					var i, result, a_value, b_value, field;
					for (i = 0; i < fields_count; i++) {
						field = fields[i].field;
						result = multipliers[i] * cmp(
							get_field(field, a),
							get_field(field, b)
						);
						if (result) return result;
					}
					return 0;
				};
			}
		};
	
		/**
		 * Parses a search query and returns an object
		 * with tokens and fields ready to be populated
		 * with results.
		 *
		 * @param {string} query
		 * @param {object} options
		 * @returns {object}
		 */
		Sifter.prototype.prepareSearch = function(query, options) {
			if (typeof query === 'object') return query;
	
			options = extend({}, options);
	
			var option_fields     = options.fields;
			var option_sort       = options.sort;
			var option_sort_empty = options.sort_empty;
	
			if (option_fields && !is_array(option_fields)) options.fields = [option_fields];
			if (option_sort && !is_array(option_sort)) options.sort = [option_sort];
			if (option_sort_empty && !is_array(option_sort_empty)) options.sort_empty = [option_sort_empty];
	
			return {
				options : options,
				query   : String(query || '').toLowerCase(),
				tokens  : this.tokenize(query),
				total   : 0,
				items   : []
			};
		};
	
		/**
		 * Searches through all items and returns a sorted array of matches.
		 *
		 * The `options` parameter can contain:
		 *
		 *   - fields {string|array}
		 *   - sort {array}
		 *   - score {function}
		 *   - filter {bool}
		 *   - limit {integer}
		 *
		 * Returns an object containing:
		 *
		 *   - options {object}
		 *   - query {string}
		 *   - tokens {array}
		 *   - total {int}
		 *   - items {array}
		 *
		 * @param {string} query
		 * @param {object} options
		 * @returns {object}
		 */
		Sifter.prototype.search = function(query, options) {
			var self = this, value, score, search, calculateScore;
			var fn_sort;
			var fn_score;
	
			search  = this.prepareSearch(query, options);
			options = search.options;
			query   = search.query;
	
			// generate result scoring function
			fn_score = options.score || self.getScoreFunction(search);
	
			// perform search and sort
			if (query.length) {
				self.iterator(self.items, function(item, id) {
					score = fn_score(item);
					if (options.filter === false || score > 0) {
						search.items.push({'score': score, 'id': id});
					}
				});
			} else {
				self.iterator(self.items, function(item, id) {
					search.items.push({'score': 1, 'id': id});
				});
			}
	
			fn_sort = self.getSortFunction(search, options);
			if (fn_sort) search.items.sort(fn_sort);
	
			// apply limits
			search.total = search.items.length;
			if (typeof options.limit === 'number') {
				search.items = search.items.slice(0, options.limit);
			}
	
			return search;
		};
	
		// utilities
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
		var cmp = function(a, b) {
			if (typeof a === 'number' && typeof b === 'number') {
				return a > b ? 1 : (a < b ? -1 : 0);
			}
			a = asciifold(String(a || ''));
			b = asciifold(String(b || ''));
			if (a > b) return 1;
			if (b > a) return -1;
			return 0;
		};
	
		var extend = function(a, b) {
			var i, n, k, object;
			for (i = 1, n = arguments.length; i < n; i++) {
				object = arguments[i];
				if (!object) continue;
				for (k in object) {
					if (object.hasOwnProperty(k)) {
						a[k] = object[k];
					}
				}
			}
			return a;
		};
	
		/**
		 * A property getter resolving dot-notation
		 * @param  {Object}  obj     The root object to fetch property on
		 * @param  {String}  name    The optionally dotted property name to fetch
		 * @param  {Boolean} nesting Handle nesting or not
		 * @return {Object}          The resolved property value
		 */
		var getattr = function(obj, name, nesting) {
		    if (!obj || !name) return;
		    if (!nesting) return obj[name];
		    var names = name.split(".");
		    while(names.length && (obj = obj[names.shift()]));
		    return obj;
		};
	
		var trim = function(str) {
			return (str + '').replace(/^\s+|\s+$|/g, '');
		};
	
		var escape_regex = function(str) {
			return (str + '').replace(/([.?*+^$[\]\\(){}|-])/g, '\\$1');
		};
	
		var is_array = Array.isArray || (typeof $ !== 'undefined' && $.isArray) || function(object) {
			return Object.prototype.toString.call(object) === '[object Array]';
		};
	
		var DIACRITICS = {
			'a': '[aḀḁĂăÂâǍǎȺⱥȦȧẠạÄäÀàÁáĀāÃãÅåąĄÃąĄ]',
			'b': '[b␢βΒB฿𐌁ᛒ]',
			'c': '[cĆćĈĉČčĊċC̄c̄ÇçḈḉȻȼƇƈɕᴄＣｃ]',
			'd': '[dĎďḊḋḐḑḌḍḒḓḎḏĐđD̦d̦ƉɖƊɗƋƌᵭᶁᶑȡᴅＤｄð]',
			'e': '[eÉéÈèÊêḘḙĚěĔĕẼẽḚḛẺẻĖėËëĒēȨȩĘęᶒɆɇȄȅẾếỀềỄễỂểḜḝḖḗḔḕȆȇẸẹỆệⱸᴇＥｅɘǝƏƐε]',
			'f': '[fƑƒḞḟ]',
			'g': '[gɢ₲ǤǥĜĝĞğĢģƓɠĠġ]',
			'h': '[hĤĥĦħḨḩẖẖḤḥḢḣɦʰǶƕ]',
			'i': '[iÍíÌìĬĭÎîǏǐÏïḮḯĨĩĮįĪīỈỉȈȉȊȋỊịḬḭƗɨɨ̆ᵻᶖİiIıɪＩｉ]',
			'j': '[jȷĴĵɈɉʝɟʲ]',
			'k': '[kƘƙꝀꝁḰḱǨǩḲḳḴḵκϰ₭]',
			'l': '[lŁłĽľĻļĹĺḶḷḸḹḼḽḺḻĿŀȽƚⱠⱡⱢɫɬᶅɭȴʟＬｌ]',
			'n': '[nŃńǸǹŇňÑñṄṅŅņṆṇṊṋṈṉN̈n̈ƝɲȠƞᵰᶇɳȵɴＮｎŊŋ]',
			'o': '[oØøÖöÓóÒòÔôǑǒŐőŎŏȮȯỌọƟɵƠơỎỏŌōÕõǪǫȌȍՕօ]',
			'p': '[pṔṕṖṗⱣᵽƤƥᵱ]',
			'q': '[qꝖꝗʠɊɋꝘꝙq̃]',
			'r': '[rŔŕɌɍŘřŖŗṘṙȐȑȒȓṚṛⱤɽ]',
			's': '[sŚśṠṡṢṣꞨꞩŜŝŠšŞşȘșS̈s̈]',
			't': '[tŤťṪṫŢţṬṭƮʈȚțṰṱṮṯƬƭ]',
			'u': '[uŬŭɄʉỤụÜüÚúÙùÛûǓǔŰűŬŭƯưỦủŪūŨũŲųȔȕ∪]',
			'v': '[vṼṽṾṿƲʋꝞꝟⱱʋ]',
			'w': '[wẂẃẀẁŴŵẄẅẆẇẈẉ]',
			'x': '[xẌẍẊẋχ]',
			'y': '[yÝýỲỳŶŷŸÿỸỹẎẏỴỵɎɏƳƴ]',
			'z': '[zŹźẐẑŽžŻżẒẓẔẕƵƶ]'
		};
	
		var asciifold = (function() {
			var i, n, k, chunk;
			var foreignletters = '';
			var lookup = {};
			for (k in DIACRITICS) {
				if (DIACRITICS.hasOwnProperty(k)) {
					chunk = DIACRITICS[k].substring(2, DIACRITICS[k].length - 1);
					foreignletters += chunk;
					for (i = 0, n = chunk.length; i < n; i++) {
						lookup[chunk.charAt(i)] = k;
					}
				}
			}
			var regexp = new RegExp('[' +  foreignletters + ']', 'g');
			return function(str) {
				return str.replace(regexp, function(foreignletter) {
					return lookup[foreignletter];
				}).toLowerCase();
			};
		})();
	
	
		// export
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
		return Sifter;
	}));
	


/***/ }),
/* 21 */
/***/ (function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_RESULT__;/**
	 * microplugin.js
	 * Copyright (c) 2013 Brian Reavis & contributors
	 *
	 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
	 * file except in compliance with the License. You may obtain a copy of the License at:
	 * http://www.apache.org/licenses/LICENSE-2.0
	 *
	 * Unless required by applicable law or agreed to in writing, software distributed under
	 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF
	 * ANY KIND, either express or implied. See the License for the specific language
	 * governing permissions and limitations under the License.
	 *
	 * @author Brian Reavis <brian@thirdroute.com>
	 */
	
	(function(root, factory) {
		if (true) {
			!(__WEBPACK_AMD_DEFINE_FACTORY__ = (factory), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.call(exports, __webpack_require__, exports, module)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
		} else if (typeof exports === 'object') {
			module.exports = factory();
		} else {
			root.MicroPlugin = factory();
		}
	}(this, function() {
		var MicroPlugin = {};
	
		MicroPlugin.mixin = function(Interface) {
			Interface.plugins = {};
	
			/**
			 * Initializes the listed plugins (with options).
			 * Acceptable formats:
			 *
			 * List (without options):
			 *   ['a', 'b', 'c']
			 *
			 * List (with options):
			 *   [{'name': 'a', options: {}}, {'name': 'b', options: {}}]
			 *
			 * Hash (with options):
			 *   {'a': { ... }, 'b': { ... }, 'c': { ... }}
			 *
			 * @param {mixed} plugins
			 */
			Interface.prototype.initializePlugins = function(plugins) {
				var i, n, key;
				var self  = this;
				var queue = [];
	
				self.plugins = {
					names     : [],
					settings  : {},
					requested : {},
					loaded    : {}
				};
	
				if (utils.isArray(plugins)) {
					for (i = 0, n = plugins.length; i < n; i++) {
						if (typeof plugins[i] === 'string') {
							queue.push(plugins[i]);
						} else {
							self.plugins.settings[plugins[i].name] = plugins[i].options;
							queue.push(plugins[i].name);
						}
					}
				} else if (plugins) {
					for (key in plugins) {
						if (plugins.hasOwnProperty(key)) {
							self.plugins.settings[key] = plugins[key];
							queue.push(key);
						}
					}
				}
	
				while (queue.length) {
					self.require(queue.shift());
				}
			};
	
			Interface.prototype.loadPlugin = function(name) {
				var self    = this;
				var plugins = self.plugins;
				var plugin  = Interface.plugins[name];
	
				if (!Interface.plugins.hasOwnProperty(name)) {
					throw new Error('Unable to find "' +  name + '" plugin');
				}
	
				plugins.requested[name] = true;
				plugins.loaded[name] = plugin.fn.apply(self, [self.plugins.settings[name] || {}]);
				plugins.names.push(name);
			};
	
			/**
			 * Initializes a plugin.
			 *
			 * @param {string} name
			 */
			Interface.prototype.require = function(name) {
				var self = this;
				var plugins = self.plugins;
	
				if (!self.plugins.loaded.hasOwnProperty(name)) {
					if (plugins.requested[name]) {
						throw new Error('Plugin has circular dependency ("' + name + '")');
					}
					self.loadPlugin(name);
				}
	
				return plugins.loaded[name];
			};
	
			/**
			 * Registers a plugin.
			 *
			 * @param {string} name
			 * @param {function} fn
			 */
			Interface.define = function(name, fn) {
				Interface.plugins[name] = {
					'name' : name,
					'fn'   : fn
				};
			};
		};
	
		var utils = {
			isArray: Array.isArray || function(vArg) {
				return Object.prototype.toString.call(vArg) === '[object Array]';
			}
		};
	
		return MicroPlugin;
	}));

/***/ }),
/* 22 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	__webpack_require__(23);
	
	__webpack_require__(24);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    $('.box-slider--carousel .box-slider__item').each(function(i, obj) {
	      $(this).data('index', $(this).index());
	      return $(this).width($(this).width());
	    });
	    $target.find('.js-slider').each(function() {
	      var $list, $overlay, $thisBox, isCarousel, isPager, makeCycle;
	      $thisBox = $(this);
	      $list = $thisBox.find('.box-slider__list');
	      isCarousel = $thisBox.hasClass('box-slider--carousel');
	      isPager = !!($thisBox.closest('.box-slider-pager').length);
	      $overlay = $thisBox.find('.box-slider__overlay');
	      makeCycle = true;
	      if (isPager && isCarousel) {
	        $list.find('.box-slider__item').first().addClass('is-active');
	      }
	      if ($list.find('> .box-slider__item').length < 4 && isCarousel) {
	        makeCycle = false;
	        $thisBox.find('.box-slider__prev').addClass('is-disabled');
	        $thisBox.find('.box-slider__next').addClass('is-disabled');
	      }
	      if (makeCycle) {
	        $list.cycle({
	          carouselVisible: (function() {
	            if (isPager) {
	              return 3;
	            } else {
	              if (window.matchMedia('(min-width: 1000px)').matches) {
	                return 4;
	              } else if (window.matchMedia('(min-width: 700px)').matches) {
	                return 3;
	              } else {
	                return 1;
	              }
	            }
	          })(),
	          disabledClass: 'is-disabled',
	          fx: isCarousel ? 'carousel' : 'scrollHorz',
	          prev: $thisBox.find('.box-slider__prev'),
	          next: $thisBox.find('.box-slider__next'),
	          pager: $thisBox.find('.box-slider__pager'),
	          pagerActiveClass: 'is-active',
	          pagerTemplate: '<a href="#">{{slideNum}}</a>',
	          slides: '> .box-slider__item',
	          paused: $thisBox.data('timeout') ? false : true,
	          overlayTemplate: '',
	          overlay: $thisBox.find('.box-slider__overlay'),
	          log: false,
	          timeout: $thisBox.data('timeout') ? $thisBox.data('timeout') : 0
	        });
	        $list.on('cycle-update-view', function(event, optionHash, slideOptionsHash, currentSlideEl) {
	          var $currentSlide, overlayTemplate;
	          $currentSlide = $(currentSlideEl);
	          overlayTemplate = '';
	          if ($currentSlide.attr('data-title')) {
	            overlayTemplate = overlayTemplate + '<h2 class="box-slider__title">{{title}}</h2>';
	          }
	          if ($currentSlide.attr('data-desc')) {
	            overlayTemplate = overlayTemplate + '<p>{{desc}}</p>';
	          }
	          if ($currentSlide.is('a')) {
	            $overlay.addClass('is-clickable');
	          } else {
	            $overlay.removeClass('is-clickable');
	          }
	          return slideOptionsHash.overlayTemplate = overlayTemplate;
	        });
	        $overlay.on('click', function() {
	          if ($(this).hasClass('is-clickable')) {
	            return window.location = $thisBox.find('.box-slider__item.cycle-slide-active').attr('href');
	          }
	        });
	      }
	      return $(window).on('load', function() {
	        if ($thisBox.hasClass('box-slider--carousel')) {
	          return $thisBox.find('.box-slider__prev').add($thisBox.find('.box-slider__next')).css('top', $thisBox.find('img').first().height() / 2);
	        }
	      });
	    });
	    return $target.find('.js-slider-pager').each(function() {
	      var $imagesSlider, $pagerItems, $pagerSlider, $sliders, byPager, getActivePagerItem, makeCycle, setActivePager;
	      $sliders = $(this).find('.js-slider');
	      $imagesSlider = $sliders.not('.box-slider--carousel').find('.box-slider__list');
	      $pagerSlider = $sliders.filter('.box-slider--carousel').find('.box-slider__list');
	      makeCycle = true;
	      if ($pagerSlider.find('> .box-slider__item').length < 4) {
	        makeCycle = false;
	      }
	      $pagerItems = $pagerSlider.find('.box-slider__item');
	      byPager = false;
	      getActivePagerItem = function() {
	        return $pagerItems.filter('.is-active');
	      };
	      setActivePager = function(index) {
	        $pagerItems.removeClass('is-active');
	        return $pagerItems.filter(function(i, obj) {
	          return $(obj).data('index') === index;
	        }).addClass('is-active');
	      };
	      $imagesSlider.on('cycle-before', function(event, optionHash, outgoingSlideEl, incomingSlideEl, forwardFlag) {
	        if (byPager) {
	          return byPager = false;
	        } else {
	          setActivePager(optionHash.nextSlide);
	          if (forwardFlag) {
	            return $pagerSlider.cycle('next');
	          } else {
	            return $pagerSlider.cycle('prev');
	          }
	        }
	      });
	      return $pagerItems.on('click', function(event) {
	        var $this;
	        event.preventDefault();
	        $this = $(this);
	        byPager = true;
	        $imagesSlider.cycle('goto', $(this).data('index'));
	        return setActivePager($this.data('index'));
	      });
	    });
	  }
	};


/***/ }),
/* 23 */
/***/ (function(module, exports) {

	/*!
	* jQuery Cycle2; version: 2.1.6 build: 20141007
	* http://jquery.malsup.com/cycle2/
	* Copyright (c) 2014 M. Alsup; Dual licensed: MIT/GPL
	*/
	
	/* Cycle2 core engine */
	;(function($) {
	"use strict";
	
	var version = '2.1.6';
	
	$.fn.cycle = function( options ) {
	    // fix mistakes with the ready state
	    var o;
	    if ( this.length === 0 && !$.isReady ) {
	        o = { s: this.selector, c: this.context };
	        $.fn.cycle.log('requeuing slideshow (dom not ready)');
	        $(function() {
	            $( o.s, o.c ).cycle(options);
	        });
	        return this;
	    }
	
	    return this.each(function() {
	        var data, opts, shortName, val;
	        var container = $(this);
	        var log = $.fn.cycle.log;
	
	        if ( container.data('cycle.opts') )
	            return; // already initialized
	
	        if ( container.data('cycle-log') === false || 
	            ( options && options.log === false ) ||
	            ( opts && opts.log === false) ) {
	            log = $.noop;
	        }
	
	        log('--c2 init--');
	        data = container.data();
	        for (var p in data) {
	            // allow props to be accessed sans 'cycle' prefix and log the overrides
	            if (data.hasOwnProperty(p) && /^cycle[A-Z]+/.test(p) ) {
	                val = data[p];
	                shortName = p.match(/^cycle(.*)/)[1].replace(/^[A-Z]/, lowerCase);
	                log(shortName+':', val, '('+typeof val +')');
	                data[shortName] = val;
	            }
	        }
	
	        opts = $.extend( {}, $.fn.cycle.defaults, data, options || {});
	
	        opts.timeoutId = 0;
	        opts.paused = opts.paused || false; // #57
	        opts.container = container;
	        opts._maxZ = opts.maxZ;
	
	        opts.API = $.extend ( { _container: container }, $.fn.cycle.API );
	        opts.API.log = log;
	        opts.API.trigger = function( eventName, args ) {
	            opts.container.trigger( eventName, args );
	            return opts.API;
	        };
	
	        container.data( 'cycle.opts', opts );
	        container.data( 'cycle.API', opts.API );
	
	        // opportunity for plugins to modify opts and API
	        opts.API.trigger('cycle-bootstrap', [ opts, opts.API ]);
	
	        opts.API.addInitialSlides();
	        opts.API.preInitSlideshow();
	
	        if ( opts.slides.length )
	            opts.API.initSlideshow();
	    });
	};
	
	$.fn.cycle.API = {
	    opts: function() {
	        return this._container.data( 'cycle.opts' );
	    },
	    addInitialSlides: function() {
	        var opts = this.opts();
	        var slides = opts.slides;
	        opts.slideCount = 0;
	        opts.slides = $(); // empty set
	        
	        // add slides that already exist
	        slides = slides.jquery ? slides : opts.container.find( slides );
	
	        if ( opts.random ) {
	            slides.sort(function() {return Math.random() - 0.5;});
	        }
	
	        opts.API.add( slides );
	    },
	
	    preInitSlideshow: function() {
	        var opts = this.opts();
	        opts.API.trigger('cycle-pre-initialize', [ opts ]);
	        var tx = $.fn.cycle.transitions[opts.fx];
	        if (tx && $.isFunction(tx.preInit))
	            tx.preInit( opts );
	        opts._preInitialized = true;
	    },
	
	    postInitSlideshow: function() {
	        var opts = this.opts();
	        opts.API.trigger('cycle-post-initialize', [ opts ]);
	        var tx = $.fn.cycle.transitions[opts.fx];
	        if (tx && $.isFunction(tx.postInit))
	            tx.postInit( opts );
	    },
	
	    initSlideshow: function() {
	        var opts = this.opts();
	        var pauseObj = opts.container;
	        var slideOpts;
	        opts.API.calcFirstSlide();
	
	        if ( opts.container.css('position') == 'static' )
	            opts.container.css('position', 'relative');
	
	        $(opts.slides[opts.currSlide]).css({
	            opacity: 1,
	            display: 'block',
	            visibility: 'visible'
	        });
	        opts.API.stackSlides( opts.slides[opts.currSlide], opts.slides[opts.nextSlide], !opts.reverse );
	
	        if ( opts.pauseOnHover ) {
	            // allow pauseOnHover to specify an element
	            if ( opts.pauseOnHover !== true )
	                pauseObj = $( opts.pauseOnHover );
	
	            pauseObj.hover(
	                function(){ opts.API.pause( true ); }, 
	                function(){ opts.API.resume( true ); }
	            );
	        }
	
	        // stage initial transition
	        if ( opts.timeout ) {
	            slideOpts = opts.API.getSlideOpts( opts.currSlide );
	            opts.API.queueTransition( slideOpts, slideOpts.timeout + opts.delay );
	        }
	
	        opts._initialized = true;
	        opts.API.updateView( true );
	        opts.API.trigger('cycle-initialized', [ opts ]);
	        opts.API.postInitSlideshow();
	    },
	
	    pause: function( hover ) {
	        var opts = this.opts(),
	            slideOpts = opts.API.getSlideOpts(),
	            alreadyPaused = opts.hoverPaused || opts.paused;
	
	        if ( hover )
	            opts.hoverPaused = true; 
	        else
	            opts.paused = true;
	
	        if ( ! alreadyPaused ) {
	            opts.container.addClass('cycle-paused');
	            opts.API.trigger('cycle-paused', [ opts ]).log('cycle-paused');
	
	            if ( slideOpts.timeout ) {
	                clearTimeout( opts.timeoutId );
	                opts.timeoutId = 0;
	                
	                // determine how much time is left for the current slide
	                opts._remainingTimeout -= ( $.now() - opts._lastQueue );
	                if ( opts._remainingTimeout < 0 || isNaN(opts._remainingTimeout) )
	                    opts._remainingTimeout = undefined;
	            }
	        }
	    },
	
	    resume: function( hover ) {
	        var opts = this.opts(),
	            alreadyResumed = !opts.hoverPaused && !opts.paused,
	            remaining;
	
	        if ( hover )
	            opts.hoverPaused = false; 
	        else
	            opts.paused = false;
	
	    
	        if ( ! alreadyResumed ) {
	            opts.container.removeClass('cycle-paused');
	            // #gh-230; if an animation is in progress then don't queue a new transition; it will
	            // happen naturally
	            if ( opts.slides.filter(':animated').length === 0 )
	                opts.API.queueTransition( opts.API.getSlideOpts(), opts._remainingTimeout );
	            opts.API.trigger('cycle-resumed', [ opts, opts._remainingTimeout ] ).log('cycle-resumed');
	        }
	    },
	
	    add: function( slides, prepend ) {
	        var opts = this.opts();
	        var oldSlideCount = opts.slideCount;
	        var startSlideshow = false;
	        var len;
	
	        if ( $.type(slides) == 'string')
	            slides = $.trim( slides );
	
	        $( slides ).each(function(i) {
	            var slideOpts;
	            var slide = $(this);
	
	            if ( prepend )
	                opts.container.prepend( slide );
	            else
	                opts.container.append( slide );
	
	            opts.slideCount++;
	            slideOpts = opts.API.buildSlideOpts( slide );
	
	            if ( prepend )
	                opts.slides = $( slide ).add( opts.slides );
	            else
	                opts.slides = opts.slides.add( slide );
	
	            opts.API.initSlide( slideOpts, slide, --opts._maxZ );
	
	            slide.data('cycle.opts', slideOpts);
	            opts.API.trigger('cycle-slide-added', [ opts, slideOpts, slide ]);
	        });
	
	        opts.API.updateView( true );
	
	        startSlideshow = opts._preInitialized && (oldSlideCount < 2 && opts.slideCount >= 1);
	        if ( startSlideshow ) {
	            if ( !opts._initialized )
	                opts.API.initSlideshow();
	            else if ( opts.timeout ) {
	                len = opts.slides.length;
	                opts.nextSlide = opts.reverse ? len - 1 : 1;
	                if ( !opts.timeoutId ) {
	                    opts.API.queueTransition( opts );
	                }
	            }
	        }
	    },
	
	    calcFirstSlide: function() {
	        var opts = this.opts();
	        var firstSlideIndex;
	        firstSlideIndex = parseInt( opts.startingSlide || 0, 10 );
	        if (firstSlideIndex >= opts.slides.length || firstSlideIndex < 0)
	            firstSlideIndex = 0;
	
	        opts.currSlide = firstSlideIndex;
	        if ( opts.reverse ) {
	            opts.nextSlide = firstSlideIndex - 1;
	            if (opts.nextSlide < 0)
	                opts.nextSlide = opts.slides.length - 1;
	        }
	        else {
	            opts.nextSlide = firstSlideIndex + 1;
	            if (opts.nextSlide == opts.slides.length)
	                opts.nextSlide = 0;
	        }
	    },
	
	    calcNextSlide: function() {
	        var opts = this.opts();
	        var roll;
	        if ( opts.reverse ) {
	            roll = (opts.nextSlide - 1) < 0;
	            opts.nextSlide = roll ? opts.slideCount - 1 : opts.nextSlide-1;
	            opts.currSlide = roll ? 0 : opts.nextSlide+1;
	        }
	        else {
	            roll = (opts.nextSlide + 1) == opts.slides.length;
	            opts.nextSlide = roll ? 0 : opts.nextSlide+1;
	            opts.currSlide = roll ? opts.slides.length-1 : opts.nextSlide-1;
	        }
	    },
	
	    calcTx: function( slideOpts, manual ) {
	        var opts = slideOpts;
	        var tx;
	
	        if ( opts._tempFx )
	            tx = $.fn.cycle.transitions[opts._tempFx];
	        else if ( manual && opts.manualFx )
	            tx = $.fn.cycle.transitions[opts.manualFx];
	
	        if ( !tx )
	            tx = $.fn.cycle.transitions[opts.fx];
	
	        opts._tempFx = null;
	        this.opts()._tempFx = null;
	
	        if (!tx) {
	            tx = $.fn.cycle.transitions.fade;
	            opts.API.log('Transition "' + opts.fx + '" not found.  Using fade.');
	        }
	        return tx;
	    },
	
	    prepareTx: function( manual, fwd ) {
	        var opts = this.opts();
	        var after, curr, next, slideOpts, tx;
	
	        if ( opts.slideCount < 2 ) {
	            opts.timeoutId = 0;
	            return;
	        }
	        if ( manual && ( !opts.busy || opts.manualTrump ) ) {
	            opts.API.stopTransition();
	            opts.busy = false;
	            clearTimeout(opts.timeoutId);
	            opts.timeoutId = 0;
	        }
	        if ( opts.busy )
	            return;
	        if ( opts.timeoutId === 0 && !manual )
	            return;
	
	        curr = opts.slides[opts.currSlide];
	        next = opts.slides[opts.nextSlide];
	        slideOpts = opts.API.getSlideOpts( opts.nextSlide );
	        tx = opts.API.calcTx( slideOpts, manual );
	
	        opts._tx = tx;
	
	        if ( manual && slideOpts.manualSpeed !== undefined )
	            slideOpts.speed = slideOpts.manualSpeed;
	
	        // if ( opts.nextSlide === opts.currSlide )
	        //     opts.API.calcNextSlide();
	
	        // ensure that:
	        //      1. advancing to a different slide
	        //      2. this is either a manual event (prev/next, pager, cmd) or 
	        //              a timer event and slideshow is not paused
	        if ( opts.nextSlide != opts.currSlide && 
	            (manual || (!opts.paused && !opts.hoverPaused && opts.timeout) )) { // #62
	
	            opts.API.trigger('cycle-before', [ slideOpts, curr, next, fwd ]);
	            if ( tx.before )
	                tx.before( slideOpts, curr, next, fwd );
	
	            after = function() {
	                opts.busy = false;
	                // #76; bail if slideshow has been destroyed
	                if (! opts.container.data( 'cycle.opts' ) )
	                    return;
	
	                if (tx.after)
	                    tx.after( slideOpts, curr, next, fwd );
	                opts.API.trigger('cycle-after', [ slideOpts, curr, next, fwd ]);
	                opts.API.queueTransition( slideOpts);
	                opts.API.updateView( true );
	            };
	
	            opts.busy = true;
	            if (tx.transition)
	                tx.transition(slideOpts, curr, next, fwd, after);
	            else
	                opts.API.doTransition( slideOpts, curr, next, fwd, after);
	
	            opts.API.calcNextSlide();
	            opts.API.updateView();
	        } else {
	            opts.API.queueTransition( slideOpts );
	        }
	    },
	
	    // perform the actual animation
	    doTransition: function( slideOpts, currEl, nextEl, fwd, callback) {
	        var opts = slideOpts;
	        var curr = $(currEl), next = $(nextEl);
	        var fn = function() {
	            // make sure animIn has something so that callback doesn't trigger immediately
	            next.animate(opts.animIn || { opacity: 1}, opts.speed, opts.easeIn || opts.easing, callback);
	        };
	
	        next.css(opts.cssBefore || {});
	        curr.animate(opts.animOut || {}, opts.speed, opts.easeOut || opts.easing, function() {
	            curr.css(opts.cssAfter || {});
	            if (!opts.sync) {
	                fn();
	            }
	        });
	        if (opts.sync) {
	            fn();
	        }
	    },
	
	    queueTransition: function( slideOpts, specificTimeout ) {
	        var opts = this.opts();
	        var timeout = specificTimeout !== undefined ? specificTimeout : slideOpts.timeout;
	        if (opts.nextSlide === 0 && --opts.loop === 0) {
	            opts.API.log('terminating; loop=0');
	            opts.timeout = 0;
	            if ( timeout ) {
	                setTimeout(function() {
	                    opts.API.trigger('cycle-finished', [ opts ]);
	                }, timeout);
	            }
	            else {
	                opts.API.trigger('cycle-finished', [ opts ]);
	            }
	            // reset nextSlide
	            opts.nextSlide = opts.currSlide;
	            return;
	        }
	        if ( opts.continueAuto !== undefined ) {
	            if ( opts.continueAuto === false || 
	                ($.isFunction(opts.continueAuto) && opts.continueAuto() === false )) {
	                opts.API.log('terminating automatic transitions');
	                opts.timeout = 0;
	                if ( opts.timeoutId )
	                    clearTimeout(opts.timeoutId);
	                return;
	            }
	        }
	        if ( timeout ) {
	            opts._lastQueue = $.now();
	            if ( specificTimeout === undefined )
	                opts._remainingTimeout = slideOpts.timeout;
	
	            if ( !opts.paused && ! opts.hoverPaused ) {
	                opts.timeoutId = setTimeout(function() { 
	                    opts.API.prepareTx( false, !opts.reverse ); 
	                }, timeout );
	            }
	        }
	    },
	
	    stopTransition: function() {
	        var opts = this.opts();
	        if ( opts.slides.filter(':animated').length ) {
	            opts.slides.stop(false, true);
	            opts.API.trigger('cycle-transition-stopped', [ opts ]);
	        }
	
	        if ( opts._tx && opts._tx.stopTransition )
	            opts._tx.stopTransition( opts );
	    },
	
	    // advance slide forward or back
	    advanceSlide: function( val ) {
	        var opts = this.opts();
	        clearTimeout(opts.timeoutId);
	        opts.timeoutId = 0;
	        opts.nextSlide = opts.currSlide + val;
	        
	        if (opts.nextSlide < 0)
	            opts.nextSlide = opts.slides.length - 1;
	        else if (opts.nextSlide >= opts.slides.length)
	            opts.nextSlide = 0;
	
	        opts.API.prepareTx( true,  val >= 0 );
	        return false;
	    },
	
	    buildSlideOpts: function( slide ) {
	        var opts = this.opts();
	        var val, shortName;
	        var slideOpts = slide.data() || {};
	        for (var p in slideOpts) {
	            // allow props to be accessed sans 'cycle' prefix and log the overrides
	            if (slideOpts.hasOwnProperty(p) && /^cycle[A-Z]+/.test(p) ) {
	                val = slideOpts[p];
	                shortName = p.match(/^cycle(.*)/)[1].replace(/^[A-Z]/, lowerCase);
	                opts.API.log('['+(opts.slideCount-1)+']', shortName+':', val, '('+typeof val +')');
	                slideOpts[shortName] = val;
	            }
	        }
	
	        slideOpts = $.extend( {}, $.fn.cycle.defaults, opts, slideOpts );
	        slideOpts.slideNum = opts.slideCount;
	
	        try {
	            // these props should always be read from the master state object
	            delete slideOpts.API;
	            delete slideOpts.slideCount;
	            delete slideOpts.currSlide;
	            delete slideOpts.nextSlide;
	            delete slideOpts.slides;
	        } catch(e) {
	            // no op
	        }
	        return slideOpts;
	    },
	
	    getSlideOpts: function( index ) {
	        var opts = this.opts();
	        if ( index === undefined )
	            index = opts.currSlide;
	
	        var slide = opts.slides[index];
	        var slideOpts = $(slide).data('cycle.opts');
	        return $.extend( {}, opts, slideOpts );
	    },
	    
	    initSlide: function( slideOpts, slide, suggestedZindex ) {
	        var opts = this.opts();
	        slide.css( slideOpts.slideCss || {} );
	        if ( suggestedZindex > 0 )
	            slide.css( 'zIndex', suggestedZindex );
	
	        // ensure that speed settings are sane
	        if ( isNaN( slideOpts.speed ) )
	            slideOpts.speed = $.fx.speeds[slideOpts.speed] || $.fx.speeds._default;
	        if ( !slideOpts.sync )
	            slideOpts.speed = slideOpts.speed / 2;
	
	        slide.addClass( opts.slideClass );
	    },
	
	    updateView: function( isAfter, isDuring, forceEvent ) {
	        var opts = this.opts();
	        if ( !opts._initialized )
	            return;
	        var slideOpts = opts.API.getSlideOpts();
	        var currSlide = opts.slides[ opts.currSlide ];
	
	        if ( ! isAfter && isDuring !== true ) {
	            opts.API.trigger('cycle-update-view-before', [ opts, slideOpts, currSlide ]);
	            if ( opts.updateView < 0 )
	                return;
	        }
	
	        if ( opts.slideActiveClass ) {
	            opts.slides.removeClass( opts.slideActiveClass )
	                .eq( opts.currSlide ).addClass( opts.slideActiveClass );
	        }
	
	        if ( isAfter && opts.hideNonActive )
	            opts.slides.filter( ':not(.' + opts.slideActiveClass + ')' ).css('visibility', 'hidden');
	
	        if ( opts.updateView === 0 ) {
	            setTimeout(function() {
	                opts.API.trigger('cycle-update-view', [ opts, slideOpts, currSlide, isAfter ]);
	            }, slideOpts.speed / (opts.sync ? 2 : 1) );
	        }
	
	        if ( opts.updateView !== 0 )
	            opts.API.trigger('cycle-update-view', [ opts, slideOpts, currSlide, isAfter ]);
	        
	        if ( isAfter )
	            opts.API.trigger('cycle-update-view-after', [ opts, slideOpts, currSlide ]);
	    },
	
	    getComponent: function( name ) {
	        var opts = this.opts();
	        var selector = opts[name];
	        if (typeof selector === 'string') {
	            // if selector is a child, sibling combinator, adjancent selector then use find, otherwise query full dom
	            return (/^\s*[\>|\+|~]/).test( selector ) ? opts.container.find( selector ) : $( selector );
	        }
	        if (selector.jquery)
	            return selector;
	        
	        return $(selector);
	    },
	
	    stackSlides: function( curr, next, fwd ) {
	        var opts = this.opts();
	        if ( !curr ) {
	            curr = opts.slides[opts.currSlide];
	            next = opts.slides[opts.nextSlide];
	            fwd = !opts.reverse;
	        }
	
	        // reset the zIndex for the common case:
	        // curr slide on top,  next slide beneath, and the rest in order to be shown
	        $(curr).css('zIndex', opts.maxZ);
	
	        var i;
	        var z = opts.maxZ - 2;
	        var len = opts.slideCount;
	        if (fwd) {
	            for ( i = opts.currSlide + 1; i < len; i++ )
	                $( opts.slides[i] ).css( 'zIndex', z-- );
	            for ( i = 0; i < opts.currSlide; i++ )
	                $( opts.slides[i] ).css( 'zIndex', z-- );
	        }
	        else {
	            for ( i = opts.currSlide - 1; i >= 0; i-- )
	                $( opts.slides[i] ).css( 'zIndex', z-- );
	            for ( i = len - 1; i > opts.currSlide; i-- )
	                $( opts.slides[i] ).css( 'zIndex', z-- );
	        }
	
	        $(next).css('zIndex', opts.maxZ - 1);
	    },
	
	    getSlideIndex: function( el ) {
	        return this.opts().slides.index( el );
	    }
	
	}; // API
	
	// default logger
	$.fn.cycle.log = function log() {
	    /*global console:true */
	    if (window.console && console.log)
	        console.log('[cycle2] ' + Array.prototype.join.call(arguments, ' ') );
	};
	
	$.fn.cycle.version = function() { return 'Cycle2: ' + version; };
	
	// helper functions
	
	function lowerCase(s) {
	    return (s || '').toLowerCase();
	}
	
	// expose transition object
	$.fn.cycle.transitions = {
	    custom: {
	    },
	    none: {
	        before: function( opts, curr, next, fwd ) {
	            opts.API.stackSlides( next, curr, fwd );
	            opts.cssBefore = { opacity: 1, visibility: 'visible', display: 'block' };
	        }
	    },
	    fade: {
	        before: function( opts, curr, next, fwd ) {
	            var css = opts.API.getSlideOpts( opts.nextSlide ).slideCss || {};
	            opts.API.stackSlides( curr, next, fwd );
	            opts.cssBefore = $.extend(css, { opacity: 0, visibility: 'visible', display: 'block' });
	            opts.animIn = { opacity: 1 };
	            opts.animOut = { opacity: 0 };
	        }
	    },
	    fadeout: {
	        before: function( opts , curr, next, fwd ) {
	            var css = opts.API.getSlideOpts( opts.nextSlide ).slideCss || {};
	            opts.API.stackSlides( curr, next, fwd );
	            opts.cssBefore = $.extend(css, { opacity: 1, visibility: 'visible', display: 'block' });
	            opts.animOut = { opacity: 0 };
	        }
	    },
	    scrollHorz: {
	        before: function( opts, curr, next, fwd ) {
	            opts.API.stackSlides( curr, next, fwd );
	            var w = opts.container.css('overflow','hidden').width();
	            opts.cssBefore = { left: fwd ? w : - w, top: 0, opacity: 1, visibility: 'visible', display: 'block' };
	            opts.cssAfter = { zIndex: opts._maxZ - 2, left: 0 };
	            opts.animIn = { left: 0 };
	            opts.animOut = { left: fwd ? -w : w };
	        }
	    }
	};
	
	// @see: http://jquery.malsup.com/cycle2/api
	$.fn.cycle.defaults = {
	    allowWrap:        true,
	    autoSelector:     '.cycle-slideshow[data-cycle-auto-init!=false]',
	    delay:            0,
	    easing:           null,
	    fx:              'fade',
	    hideNonActive:    true,
	    loop:             0,
	    manualFx:         undefined,
	    manualSpeed:      undefined,
	    manualTrump:      true,
	    maxZ:             100,
	    pauseOnHover:     false,
	    reverse:          false,
	    slideActiveClass: 'cycle-slide-active',
	    slideClass:       'cycle-slide',
	    slideCss:         { position: 'absolute', top: 0, left: 0 },
	    slides:          '> img',
	    speed:            500,
	    startingSlide:    0,
	    sync:             true,
	    timeout:          4000,
	    updateView:       0
	};
	
	// automatically find and run slideshows
	$(document).ready(function() {
	    $( $.fn.cycle.defaults.autoSelector ).cycle();
	});
	
	})(jQuery);
	
	/*! Cycle2 autoheight plugin; Copyright (c) M.Alsup, 2012; version: 20130913 */
	(function($) {
	"use strict";
	
	$.extend($.fn.cycle.defaults, {
	    autoHeight: 0, // setting this option to false disables autoHeight logic
	    autoHeightSpeed: 250,
	    autoHeightEasing: null
	});    
	
	$(document).on( 'cycle-initialized', function( e, opts ) {
	    var autoHeight = opts.autoHeight;
	    var t = $.type( autoHeight );
	    var resizeThrottle = null;
	    var ratio;
	
	    if ( t !== 'string' && t !== 'number' )
	        return;
	
	    // bind events
	    opts.container.on( 'cycle-slide-added cycle-slide-removed', initAutoHeight );
	    opts.container.on( 'cycle-destroyed', onDestroy );
	
	    if ( autoHeight == 'container' ) {
	        opts.container.on( 'cycle-before', onBefore );
	    }
	    else if ( t === 'string' && /\d+\:\d+/.test( autoHeight ) ) { 
	        // use ratio
	        ratio = autoHeight.match(/(\d+)\:(\d+)/);
	        ratio = ratio[1] / ratio[2];
	        opts._autoHeightRatio = ratio;
	    }
	
	    // if autoHeight is a number then we don't need to recalculate the sentinel
	    // index on resize
	    if ( t !== 'number' ) {
	        // bind unique resize handler per slideshow (so it can be 'off-ed' in onDestroy)
	        opts._autoHeightOnResize = function () {
	            clearTimeout( resizeThrottle );
	            resizeThrottle = setTimeout( onResize, 50 );
	        };
	
	        $(window).on( 'resize orientationchange', opts._autoHeightOnResize );
	    }
	
	    setTimeout( onResize, 30 );
	
	    function onResize() {
	        initAutoHeight( e, opts );
	    }
	});
	
	function initAutoHeight( e, opts ) {
	    var clone, height, sentinelIndex;
	    var autoHeight = opts.autoHeight;
	
	    if ( autoHeight == 'container' ) {
	        height = $( opts.slides[ opts.currSlide ] ).outerHeight();
	        opts.container.height( height );
	    }
	    else if ( opts._autoHeightRatio ) { 
	        opts.container.height( opts.container.width() / opts._autoHeightRatio );
	    }
	    else if ( autoHeight === 'calc' || ( $.type( autoHeight ) == 'number' && autoHeight >= 0 ) ) {
	        if ( autoHeight === 'calc' )
	            sentinelIndex = calcSentinelIndex( e, opts );
	        else if ( autoHeight >= opts.slides.length )
	            sentinelIndex = 0;
	        else 
	            sentinelIndex = autoHeight;
	
	        // only recreate sentinel if index is different
	        if ( sentinelIndex == opts._sentinelIndex )
	            return;
	
	        opts._sentinelIndex = sentinelIndex;
	        if ( opts._sentinel )
	            opts._sentinel.remove();
	
	        // clone existing slide as sentinel
	        clone = $( opts.slides[ sentinelIndex ].cloneNode(true) );
	        
	        // #50; remove special attributes from cloned content
	        clone.removeAttr( 'id name rel' ).find( '[id],[name],[rel]' ).removeAttr( 'id name rel' );
	
	        clone.css({
	            position: 'static',
	            visibility: 'hidden',
	            display: 'block'
	        }).prependTo( opts.container ).addClass('cycle-sentinel cycle-slide').removeClass('cycle-slide-active');
	        clone.find( '*' ).css( 'visibility', 'hidden' );
	
	        opts._sentinel = clone;
	    }
	}    
	
	function calcSentinelIndex( e, opts ) {
	    var index = 0, max = -1;
	
	    // calculate tallest slide index
	    opts.slides.each(function(i) {
	        var h = $(this).height();
	        if ( h > max ) {
	            max = h;
	            index = i;
	        }
	    });
	    return index;
	}
	
	function onBefore( e, opts, outgoing, incoming, forward ) {
	    var h = $(incoming).outerHeight();
	    opts.container.animate( { height: h }, opts.autoHeightSpeed, opts.autoHeightEasing );
	}
	
	function onDestroy( e, opts ) {
	    if ( opts._autoHeightOnResize ) {
	        $(window).off( 'resize orientationchange', opts._autoHeightOnResize );
	        opts._autoHeightOnResize = null;
	    }
	    opts.container.off( 'cycle-slide-added cycle-slide-removed', initAutoHeight );
	    opts.container.off( 'cycle-destroyed', onDestroy );
	    opts.container.off( 'cycle-before', onBefore );
	
	    if ( opts._sentinel ) {
	        opts._sentinel.remove();
	        opts._sentinel = null;
	    }
	}
	
	})(jQuery);
	
	/*! caption plugin for Cycle2;  version: 20130306 */
	(function($) {
	"use strict";
	
	$.extend($.fn.cycle.defaults, {
	    caption:          '> .cycle-caption',
	    captionTemplate:  '{{slideNum}} / {{slideCount}}',
	    overlay:          '> .cycle-overlay',
	    overlayTemplate:  '<div>{{title}}</div><div>{{desc}}</div>',
	    captionModule:    'caption'
	});    
	
	$(document).on( 'cycle-update-view', function( e, opts, slideOpts, currSlide ) {
	    if ( opts.captionModule !== 'caption' )
	        return;
	    var el;
	    $.each(['caption','overlay'], function() {
	        var name = this; 
	        var template = slideOpts[name+'Template'];
	        var el = opts.API.getComponent( name );
	        if( el.length && template ) {
	            el.html( opts.API.tmpl( template, slideOpts, opts, currSlide ) );
	            el.show();
	        }
	        else {
	            el.hide();
	        }
	    });
	});
	
	$(document).on( 'cycle-destroyed', function( e, opts ) {
	    var el;
	    $.each(['caption','overlay'], function() {
	        var name = this, template = opts[name+'Template'];
	        if ( opts[name] && template ) {
	            el = opts.API.getComponent( 'caption' );
	            el.empty();
	        }
	    });
	});
	
	})(jQuery);
	
	/*! command plugin for Cycle2;  version: 20140415 */
	(function($) {
	"use strict";
	
	var c2 = $.fn.cycle;
	
	$.fn.cycle = function( options ) {
	    var cmd, cmdFn, opts;
	    var args = $.makeArray( arguments );
	
	    if ( $.type( options ) == 'number' ) {
	        return this.cycle( 'goto', options );
	    }
	
	    if ( $.type( options ) == 'string' ) {
	        return this.each(function() {
	            var cmdArgs;
	            cmd = options;
	            opts = $(this).data('cycle.opts');
	
	            if ( opts === undefined ) {
	                c2.log('slideshow must be initialized before sending commands; "' + cmd + '" ignored');
	                return;
	            }
	            else {
	                cmd = cmd == 'goto' ? 'jump' : cmd; // issue #3; change 'goto' to 'jump' internally
	                cmdFn = opts.API[ cmd ];
	                if ( $.isFunction( cmdFn )) {
	                    cmdArgs = $.makeArray( args );
	                    cmdArgs.shift();
	                    return cmdFn.apply( opts.API, cmdArgs );
	                }
	                else {
	                    c2.log( 'unknown command: ', cmd );
	                }
	            }
	        });
	    }
	    else {
	        return c2.apply( this, arguments );
	    }
	};
	
	// copy props
	$.extend( $.fn.cycle, c2 );
	
	$.extend( c2.API, {
	    next: function() {
	        var opts = this.opts();
	        if ( opts.busy && ! opts.manualTrump )
	            return;
	
	        var count = opts.reverse ? -1 : 1;
	        if ( opts.allowWrap === false && ( opts.currSlide + count ) >= opts.slideCount )
	            return;
	
	        opts.API.advanceSlide( count );
	        opts.API.trigger('cycle-next', [ opts ]).log('cycle-next');
	    },
	
	    prev: function() {
	        var opts = this.opts();
	        if ( opts.busy && ! opts.manualTrump )
	            return;
	        var count = opts.reverse ? 1 : -1;
	        if ( opts.allowWrap === false && ( opts.currSlide + count ) < 0 )
	            return;
	
	        opts.API.advanceSlide( count );
	        opts.API.trigger('cycle-prev', [ opts ]).log('cycle-prev');
	    },
	
	    destroy: function() {
	        this.stop(); //#204
	
	        var opts = this.opts();
	        var clean = $.isFunction( $._data ) ? $._data : $.noop;  // hack for #184 and #201
	        clearTimeout(opts.timeoutId);
	        opts.timeoutId = 0;
	        opts.API.stop();
	        opts.API.trigger( 'cycle-destroyed', [ opts ] ).log('cycle-destroyed');
	        opts.container.removeData();
	        clean( opts.container[0], 'parsedAttrs', false );
	
	        // #75; remove inline styles
	        if ( ! opts.retainStylesOnDestroy ) {
	            opts.container.removeAttr( 'style' );
	            opts.slides.removeAttr( 'style' );
	            opts.slides.removeClass( opts.slideActiveClass );
	        }
	        opts.slides.each(function() {
	            var slide = $(this);
	            slide.removeData();
	            slide.removeClass( opts.slideClass );
	            clean( this, 'parsedAttrs', false );
	        });
	    },
	
	    jump: function( index, fx ) {
	        // go to the requested slide
	        var fwd;
	        var opts = this.opts();
	        if ( opts.busy && ! opts.manualTrump )
	            return;
	        var num = parseInt( index, 10 );
	        if (isNaN(num) || num < 0 || num >= opts.slides.length) {
	            opts.API.log('goto: invalid slide index: ' + num);
	            return;
	        }
	        if (num == opts.currSlide) {
	            opts.API.log('goto: skipping, already on slide', num);
	            return;
	        }
	        opts.nextSlide = num;
	        clearTimeout(opts.timeoutId);
	        opts.timeoutId = 0;
	        opts.API.log('goto: ', num, ' (zero-index)');
	        fwd = opts.currSlide < opts.nextSlide;
	        opts._tempFx = fx;
	        opts.API.prepareTx( true, fwd );
	    },
	
	    stop: function() {
	        var opts = this.opts();
	        var pauseObj = opts.container;
	        clearTimeout(opts.timeoutId);
	        opts.timeoutId = 0;
	        opts.API.stopTransition();
	        if ( opts.pauseOnHover ) {
	            if ( opts.pauseOnHover !== true )
	                pauseObj = $( opts.pauseOnHover );
	            pauseObj.off('mouseenter mouseleave');
	        }
	        opts.API.trigger('cycle-stopped', [ opts ]).log('cycle-stopped');
	    },
	
	    reinit: function() {
	        var opts = this.opts();
	        opts.API.destroy();
	        opts.container.cycle();
	    },
	
	    remove: function( index ) {
	        var opts = this.opts();
	        var slide, slideToRemove, slides = [], slideNum = 1;
	        for ( var i=0; i < opts.slides.length; i++ ) {
	            slide = opts.slides[i];
	            if ( i == index ) {
	                slideToRemove = slide;
	            }
	            else {
	                slides.push( slide );
	                $( slide ).data('cycle.opts').slideNum = slideNum;
	                slideNum++;
	            }
	        }
	        if ( slideToRemove ) {
	            opts.slides = $( slides );
	            opts.slideCount--;
	            $( slideToRemove ).remove();
	            if (index == opts.currSlide)
	                opts.API.advanceSlide( 1 );
	            else if ( index < opts.currSlide )
	                opts.currSlide--;
	            else
	                opts.currSlide++;
	
	            opts.API.trigger('cycle-slide-removed', [ opts, index, slideToRemove ]).log('cycle-slide-removed');
	            opts.API.updateView();
	        }
	    }
	
	});
	
	// listen for clicks on elements with data-cycle-cmd attribute
	$(document).on('click.cycle', '[data-cycle-cmd]', function(e) {
	    // issue cycle command
	    e.preventDefault();
	    var el = $(this);
	    var command = el.data('cycle-cmd');
	    var context = el.data('cycle-context') || '.cycle-slideshow';
	    $(context).cycle(command, el.data('cycle-arg'));
	});
	
	
	})(jQuery);
	
	/*! hash plugin for Cycle2;  version: 20130905 */
	(function($) {
	"use strict";
	
	$(document).on( 'cycle-pre-initialize', function( e, opts ) {
	    onHashChange( opts, true );
	
	    opts._onHashChange = function() {
	        onHashChange( opts, false );
	    };
	
	    $( window ).on( 'hashchange', opts._onHashChange);
	});
	
	$(document).on( 'cycle-update-view', function( e, opts, slideOpts ) {
	    if ( slideOpts.hash && ( '#' + slideOpts.hash ) != window.location.hash ) {
	        opts._hashFence = true;
	        window.location.hash = slideOpts.hash;
	    }
	});
	
	$(document).on( 'cycle-destroyed', function( e, opts) {
	    if ( opts._onHashChange ) {
	        $( window ).off( 'hashchange', opts._onHashChange );
	    }
	});
	
	function onHashChange( opts, setStartingSlide ) {
	    var hash;
	    if ( opts._hashFence ) {
	        opts._hashFence = false;
	        return;
	    }
	    
	    hash = window.location.hash.substring(1);
	
	    opts.slides.each(function(i) {
	        if ( $(this).data( 'cycle-hash' ) == hash ) {
	            if ( setStartingSlide === true ) {
	                opts.startingSlide = i;
	            }
	            else {
	                var fwd = opts.currSlide < i;
	                opts.nextSlide = i;
	                opts.API.prepareTx( true, fwd );
	            }
	            return false;
	        }
	    });
	}
	
	})(jQuery);
	
	/*! loader plugin for Cycle2;  version: 20131121 */
	(function($) {
	"use strict";
	
	$.extend($.fn.cycle.defaults, {
	    loader: false
	});
	
	$(document).on( 'cycle-bootstrap', function( e, opts ) {
	    var addFn;
	
	    if ( !opts.loader )
	        return;
	
	    // override API.add for this slideshow
	    addFn = opts.API.add;
	    opts.API.add = add;
	
	    function add( slides, prepend ) {
	        var slideArr = [];
	        if ( $.type( slides ) == 'string' )
	            slides = $.trim( slides );
	        else if ( $.type( slides) === 'array' ) {
	            for (var i=0; i < slides.length; i++ )
	                slides[i] = $(slides[i])[0];
	        }
	
	        slides = $( slides );
	        var slideCount = slides.length;
	
	        if ( ! slideCount )
	            return;
	
	        slides.css('visibility','hidden').appendTo('body').each(function(i) { // appendTo fixes #56
	            var count = 0;
	            var slide = $(this);
	            var images = slide.is('img') ? slide : slide.find('img');
	            slide.data('index', i);
	            // allow some images to be marked as unimportant (and filter out images w/o src value)
	            images = images.filter(':not(.cycle-loader-ignore)').filter(':not([src=""])');
	            if ( ! images.length ) {
	                --slideCount;
	                slideArr.push( slide );
	                return;
	            }
	
	            count = images.length;
	            images.each(function() {
	                // add images that are already loaded
	                if ( this.complete ) {
	                    imageLoaded();
	                }
	                else {
	                    $(this).load(function() {
	                        imageLoaded();
	                    }).on("error", function() {
	                        if ( --count === 0 ) {
	                            // ignore this slide
	                            opts.API.log('slide skipped; img not loaded:', this.src);
	                            if ( --slideCount === 0 && opts.loader == 'wait') {
	                                addFn.apply( opts.API, [ slideArr, prepend ] );
	                            }
	                        }
	                    });
	                }
	            });
	
	            function imageLoaded() {
	                if ( --count === 0 ) {
	                    --slideCount;
	                    addSlide( slide );
	                }
	            }
	        });
	
	        if ( slideCount )
	            opts.container.addClass('cycle-loading');
	        
	
	        function addSlide( slide ) {
	            var curr;
	            if ( opts.loader == 'wait' ) {
	                slideArr.push( slide );
	                if ( slideCount === 0 ) {
	                    // #59; sort slides into original markup order
	                    slideArr.sort( sorter );
	                    addFn.apply( opts.API, [ slideArr, prepend ] );
	                    opts.container.removeClass('cycle-loading');
	                }
	            }
	            else {
	                curr = $(opts.slides[opts.currSlide]);
	                addFn.apply( opts.API, [ slide, prepend ] );
	                curr.show();
	                opts.container.removeClass('cycle-loading');
	            }
	        }
	
	        function sorter(a, b) {
	            return a.data('index') - b.data('index');
	        }
	    }
	});
	
	})(jQuery);
	
	/*! pager plugin for Cycle2;  version: 20140415 */
	(function($) {
	"use strict";
	
	$.extend($.fn.cycle.defaults, {
	    pager:            '> .cycle-pager',
	    pagerActiveClass: 'cycle-pager-active',
	    pagerEvent:       'click.cycle',
	    pagerEventBubble: undefined,
	    pagerTemplate:    '<span>&bull;</span>'
	});
	
	$(document).on( 'cycle-bootstrap', function( e, opts, API ) {
	    // add method to API
	    API.buildPagerLink = buildPagerLink;
	});
	
	$(document).on( 'cycle-slide-added', function( e, opts, slideOpts, slideAdded ) {
	    if ( opts.pager ) {
	        opts.API.buildPagerLink ( opts, slideOpts, slideAdded );
	        opts.API.page = page;
	    }
	});
	
	$(document).on( 'cycle-slide-removed', function( e, opts, index, slideRemoved ) {
	    if ( opts.pager ) {
	        var pagers = opts.API.getComponent( 'pager' );
	        pagers.each(function() {
	            var pager = $(this);
	            $( pager.children()[index] ).remove();
	        });
	    }
	});
	
	$(document).on( 'cycle-update-view', function( e, opts, slideOpts ) {
	    var pagers;
	
	    if ( opts.pager ) {
	        pagers = opts.API.getComponent( 'pager' );
	        pagers.each(function() {
	           $(this).children().removeClass( opts.pagerActiveClass )
	            .eq( opts.currSlide ).addClass( opts.pagerActiveClass );
	        });
	    }
	});
	
	$(document).on( 'cycle-destroyed', function( e, opts ) {
	    var pager = opts.API.getComponent( 'pager' );
	
	    if ( pager ) {
	        pager.children().off( opts.pagerEvent ); // #202
	        if ( opts.pagerTemplate )
	            pager.empty();
	    }
	});
	
	function buildPagerLink( opts, slideOpts, slide ) {
	    var pagerLink;
	    var pagers = opts.API.getComponent( 'pager' );
	    pagers.each(function() {
	        var pager = $(this);
	        if ( slideOpts.pagerTemplate ) {
	            var markup = opts.API.tmpl( slideOpts.pagerTemplate, slideOpts, opts, slide[0] );
	            pagerLink = $( markup ).appendTo( pager );
	        }
	        else {
	            pagerLink = pager.children().eq( opts.slideCount - 1 );
	        }
	        pagerLink.on( opts.pagerEvent, function(e) {
	            if ( ! opts.pagerEventBubble )
	                e.preventDefault();
	            opts.API.page( pager, e.currentTarget);
	        });
	    });
	}
	
	function page( pager, target ) {
	    /*jshint validthis:true */
	    var opts = this.opts();
	    if ( opts.busy && ! opts.manualTrump )
	        return;
	
	    var index = pager.children().index( target );
	    var nextSlide = index;
	    var fwd = opts.currSlide < nextSlide;
	    if (opts.currSlide == nextSlide) {
	        return; // no op, clicked pager for the currently displayed slide
	    }
	    opts.nextSlide = nextSlide;
	    opts._tempFx = opts.pagerFx;
	    opts.API.prepareTx( true, fwd );
	    opts.API.trigger('cycle-pager-activated', [opts, pager, target ]);
	}
	
	})(jQuery);
	
	/*! prevnext plugin for Cycle2;  version: 20140408 */
	(function($) {
	"use strict";
	
	$.extend($.fn.cycle.defaults, {
	    next:           '> .cycle-next',
	    nextEvent:      'click.cycle',
	    disabledClass:  'disabled',
	    prev:           '> .cycle-prev',
	    prevEvent:      'click.cycle',
	    swipe:          false
	});
	
	$(document).on( 'cycle-initialized', function( e, opts ) {
	    opts.API.getComponent( 'next' ).on( opts.nextEvent, function(e) {
	        e.preventDefault();
	        opts.API.next();
	    });
	
	    opts.API.getComponent( 'prev' ).on( opts.prevEvent, function(e) {
	        e.preventDefault();
	        opts.API.prev();
	    });
	
	    if ( opts.swipe ) {
	        var nextEvent = opts.swipeVert ? 'swipeUp.cycle' : 'swipeLeft.cycle swipeleft.cycle';
	        var prevEvent = opts.swipeVert ? 'swipeDown.cycle' : 'swipeRight.cycle swiperight.cycle';
	        opts.container.on( nextEvent, function(e) {
	            opts._tempFx = opts.swipeFx;
	            opts.API.next();
	        });
	        opts.container.on( prevEvent, function() {
	            opts._tempFx = opts.swipeFx;
	            opts.API.prev();
	        });
	    }
	});
	
	$(document).on( 'cycle-update-view', function( e, opts, slideOpts, currSlide ) {
	    if ( opts.allowWrap )
	        return;
	
	    var cls = opts.disabledClass;
	    var next = opts.API.getComponent( 'next' );
	    var prev = opts.API.getComponent( 'prev' );
	    var prevBoundry = opts._prevBoundry || 0;
	    var nextBoundry = (opts._nextBoundry !== undefined)?opts._nextBoundry:opts.slideCount - 1;
	
	    if ( opts.currSlide == nextBoundry )
	        next.addClass( cls ).prop( 'disabled', true );
	    else
	        next.removeClass( cls ).prop( 'disabled', false );
	
	    if ( opts.currSlide === prevBoundry )
	        prev.addClass( cls ).prop( 'disabled', true );
	    else
	        prev.removeClass( cls ).prop( 'disabled', false );
	});
	
	
	$(document).on( 'cycle-destroyed', function( e, opts ) {
	    opts.API.getComponent( 'prev' ).off( opts.nextEvent );
	    opts.API.getComponent( 'next' ).off( opts.prevEvent );
	    opts.container.off( 'swipeleft.cycle swiperight.cycle swipeLeft.cycle swipeRight.cycle swipeUp.cycle swipeDown.cycle' );
	});
	
	})(jQuery);
	
	/*! progressive loader plugin for Cycle2;  version: 20130315 */
	(function($) {
	"use strict";
	
	$.extend($.fn.cycle.defaults, {
	    progressive: false
	});
	
	$(document).on( 'cycle-pre-initialize', function( e, opts ) {
	    if ( !opts.progressive )
	        return;
	
	    var API = opts.API;
	    var nextFn = API.next;
	    var prevFn = API.prev;
	    var prepareTxFn = API.prepareTx;
	    var type = $.type( opts.progressive );
	    var slides, scriptEl;
	
	    if ( type == 'array' ) {
	        slides = opts.progressive;
	    }
	    else if ($.isFunction( opts.progressive ) ) {
	        slides = opts.progressive( opts );
	    }
	    else if ( type == 'string' ) {
	        scriptEl = $( opts.progressive );
	        slides = $.trim( scriptEl.html() );
	        if ( !slides )
	            return;
	        // is it json array?
	        if ( /^(\[)/.test( slides ) ) {
	            try {
	                slides = $.parseJSON( slides );
	            }
	            catch(err) {
	                API.log( 'error parsing progressive slides', err );
	                return;
	            }
	        }
	        else {
	            // plain text, split on delimeter
	            slides = slides.split( new RegExp( scriptEl.data('cycle-split') || '\n') );
	            
	            // #95; look for empty slide
	            if ( ! slides[ slides.length - 1 ] )
	                slides.pop();
	        }
	    }
	
	
	
	    if ( prepareTxFn ) {
	        API.prepareTx = function( manual, fwd ) {
	            var index, slide;
	
	            if ( manual || slides.length === 0 ) {
	                prepareTxFn.apply( opts.API, [ manual, fwd ] );
	                return;
	            }
	
	            if ( fwd && opts.currSlide == ( opts.slideCount-1) ) {
	                slide = slides[ 0 ];
	                slides = slides.slice( 1 );
	                opts.container.one('cycle-slide-added', function(e, opts ) {
	                    setTimeout(function() {
	                        opts.API.advanceSlide( 1 );
	                    },50);
	                });
	                opts.API.add( slide );
	            }
	            else if ( !fwd && opts.currSlide === 0 ) {
	                index = slides.length-1;
	                slide = slides[ index ];
	                slides = slides.slice( 0, index );
	                opts.container.one('cycle-slide-added', function(e, opts ) {
	                    setTimeout(function() {
	                        opts.currSlide = 1;
	                        opts.API.advanceSlide( -1 );
	                    },50);
	                });
	                opts.API.add( slide, true );
	            }
	            else {
	                prepareTxFn.apply( opts.API, [ manual, fwd ] );
	            }
	        };
	    }
	
	    if ( nextFn ) {
	        API.next = function() {
	            var opts = this.opts();
	            if ( slides.length && opts.currSlide == ( opts.slideCount - 1 ) ) {
	                var slide = slides[ 0 ];
	                slides = slides.slice( 1 );
	                opts.container.one('cycle-slide-added', function(e, opts ) {
	                    nextFn.apply( opts.API );
	                    opts.container.removeClass('cycle-loading');
	                });
	                opts.container.addClass('cycle-loading');
	                opts.API.add( slide );
	            }
	            else {
	                nextFn.apply( opts.API );    
	            }
	        };
	    }
	    
	    if ( prevFn ) {
	        API.prev = function() {
	            var opts = this.opts();
	            if ( slides.length && opts.currSlide === 0 ) {
	                var index = slides.length-1;
	                var slide = slides[ index ];
	                slides = slides.slice( 0, index );
	                opts.container.one('cycle-slide-added', function(e, opts ) {
	                    opts.currSlide = 1;
	                    opts.API.advanceSlide( -1 );
	                    opts.container.removeClass('cycle-loading');
	                });
	                opts.container.addClass('cycle-loading');
	                opts.API.add( slide, true );
	            }
	            else {
	                prevFn.apply( opts.API );
	            }
	        };
	    }
	});
	
	})(jQuery);
	
	/*! tmpl plugin for Cycle2;  version: 20121227 */
	(function($) {
	"use strict";
	
	$.extend($.fn.cycle.defaults, {
	    tmplRegex: '{{((.)?.*?)}}'
	});
	
	$.extend($.fn.cycle.API, {
	    tmpl: function( str, opts /*, ... */) {
	        var regex = new RegExp( opts.tmplRegex || $.fn.cycle.defaults.tmplRegex, 'g' );
	        var args = $.makeArray( arguments );
	        args.shift();
	        return str.replace(regex, function(_, str) {
	            var i, j, obj, prop, names = str.split('.');
	            for (i=0; i < args.length; i++) {
	                obj = args[i];
	                if ( ! obj )
	                    continue;
	                if (names.length > 1) {
	                    prop = obj;
	                    for (j=0; j < names.length; j++) {
	                        obj = prop;
	                        prop = prop[ names[j] ] || str;
	                    }
	                } else {
	                    prop = obj[str];
	                }
	
	                if ($.isFunction(prop))
	                    return prop.apply(obj, args);
	                if (prop !== undefined && prop !== null && prop != str)
	                    return prop;
	            }
	            return str;
	        });
	    }
	});    
	
	})(jQuery);


/***/ }),
/* 24 */
/***/ (function(module, exports) {

	/* Plugin for Cycle2; Copyright (c) 2012 M. Alsup; v20141007 */
	!function(a){"use strict";a(document).on("cycle-bootstrap",function(a,b,c){"carousel"===b.fx&&(c.getSlideIndex=function(a){var b=this.opts()._carouselWrap.children(),c=b.index(a);return c%b.length},c.next=function(){var a=b.reverse?-1:1;b.allowWrap===!1&&b.currSlide+a>b.slideCount-b.carouselVisible||(b.API.advanceSlide(a),b.API.trigger("cycle-next",[b]).log("cycle-next"))})}),a.fn.cycle.transitions.carousel={preInit:function(b){b.hideNonActive=!1,b.container.on("cycle-destroyed",a.proxy(this.onDestroy,b.API)),b.API.stopTransition=this.stopTransition;for(var c=0;c<b.startingSlide;c++)b.container.append(b.slides[0])},postInit:function(b){var c,d,e,f,g=b.carouselVertical;b.carouselVisible&&b.carouselVisible>b.slideCount&&(b.carouselVisible=b.slideCount-1);var h=b.carouselVisible||b.slides.length,i={display:g?"block":"inline-block",position:"static"};if(b.container.css({position:"relative",overflow:"hidden"}),b.slides.css(i),b._currSlide=b.currSlide,f=a('<div class="cycle-carousel-wrap"></div>').prependTo(b.container).css({margin:0,padding:0,top:0,left:0,position:"absolute"}).append(b.slides),b._carouselWrap=f,g||f.css("white-space","nowrap"),b.allowWrap!==!1){for(d=0;d<(void 0===b.carouselVisible?2:1);d++){for(c=0;c<b.slideCount;c++)f.append(b.slides[c].cloneNode(!0));for(c=b.slideCount;c--;)f.prepend(b.slides[c].cloneNode(!0))}f.find(".cycle-slide-active").removeClass("cycle-slide-active"),b.slides.eq(b.startingSlide).addClass("cycle-slide-active")}b.pager&&b.allowWrap===!1&&(e=b.slideCount-h,a(b.pager).children().filter(":gt("+e+")").hide()),b._nextBoundry=b.slideCount-b.carouselVisible,this.prepareDimensions(b)},prepareDimensions:function(b){var c,d,e,f,g=b.carouselVertical,h=b.carouselVisible||b.slides.length;if(b.carouselFluid&&b.carouselVisible?b._carouselResizeThrottle||this.fluidSlides(b):b.carouselVisible&&b.carouselSlideDimension?(c=h*b.carouselSlideDimension,b.container[g?"height":"width"](c)):b.carouselVisible&&(c=h*a(b.slides[0])[g?"outerHeight":"outerWidth"](!0),b.container[g?"height":"width"](c)),d=b.carouselOffset||0,b.allowWrap!==!1)if(b.carouselSlideDimension)d-=(b.slideCount+b.currSlide)*b.carouselSlideDimension;else for(e=b._carouselWrap.children(),f=0;f<b.slideCount+b.currSlide;f++)d-=a(e[f])[g?"outerHeight":"outerWidth"](!0);b._carouselWrap.css(g?"top":"left",d)},fluidSlides:function(b){function c(){clearTimeout(e),e=setTimeout(d,20)}function d(){b._carouselWrap.stop(!1,!0);var a=b.container.width()/b.carouselVisible;a=Math.ceil(a-g),b._carouselWrap.children().width(a),b._sentinel&&b._sentinel.width(a),h(b)}var e,f=b.slides.eq(0),g=f.outerWidth()-f.width(),h=this.prepareDimensions;a(window).on("resize",c),b._carouselResizeThrottle=c,d()},transition:function(b,c,d,e,f){var g,h={},i=b.nextSlide-b.currSlide,j=b.carouselVertical,k=b.speed;if(b.allowWrap===!1){e=i>0;var l=b._currSlide,m=b.slideCount-b.carouselVisible;i>0&&b.nextSlide>m&&l==m?i=0:i>0&&b.nextSlide>m?i=b.nextSlide-l-(b.nextSlide-m):0>i&&b.currSlide>m&&b.nextSlide>m?i=0:0>i&&b.currSlide>m?i+=b.currSlide-m:l=b.currSlide,g=this.getScroll(b,j,l,i),b.API.opts()._currSlide=b.nextSlide>m?m:b.nextSlide}else e&&0===b.nextSlide?(g=this.getDim(b,b.currSlide,j),f=this.genCallback(b,e,j,f)):e||b.nextSlide!=b.slideCount-1?g=this.getScroll(b,j,b.currSlide,i):(g=this.getDim(b,b.currSlide,j),f=this.genCallback(b,e,j,f));h[j?"top":"left"]=e?"-="+g:"+="+g,b.throttleSpeed&&(k=g/a(b.slides[0])[j?"height":"width"]()*b.speed),b._carouselWrap.animate(h,k,b.easing,f)},getDim:function(b,c,d){var e=a(b.slides[c]);return e[d?"outerHeight":"outerWidth"](!0)},getScroll:function(a,b,c,d){var e,f=0;if(d>0)for(e=c;c+d>e;e++)f+=this.getDim(a,e,b);else for(e=c;e>c+d;e--)f+=this.getDim(a,e,b);return f},genCallback:function(b,c,d,e){return function(){var c=a(b.slides[b.nextSlide]).position(),f=0-c[d?"top":"left"]+(b.carouselOffset||0);b._carouselWrap.css(b.carouselVertical?"top":"left",f),e()}},stopTransition:function(){var a=this.opts();a.slides.stop(!1,!0),a._carouselWrap.stop(!1,!0)},onDestroy:function(){var b=this.opts();b._carouselResizeThrottle&&a(window).off("resize",b._carouselResizeThrottle),b.slides.prependTo(b.container),b._carouselWrap.remove()}}}(jQuery);

/***/ }),
/* 25 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	__webpack_require__(26);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    return $target.find('.tooltip').tipso({
	      position: 'top-right',
	      background: '#fff',
	      color: '#444',
	      useTitle: true,
	      tooltipHover: true
	    });
	  }
	};


/***/ }),
/* 26 */
/***/ (function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;/*!
	 * tipso - A Lightweight Responsive jQuery Tooltip Plugin v1.0.8
	 * Copyright (c) 2014-2015 Bojan Petkovski
	 * http://tipso.object505.com
	 * Licensed under the MIT license
	 * http://object505.mit-license.org/
	 */
	 // CommonJS, AMD or browser globals
	(function (factory) {
	    if (true) {
	        // AMD. Register as an anonymous module.
	        !(__WEBPACK_AMD_DEFINE_ARRAY__ = [__webpack_require__(2)], __WEBPACK_AMD_DEFINE_FACTORY__ = (factory), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
	    } else if (typeof exports === 'object') {
	        // Node/CommonJS
	        module.exports = factory(require('jquery'));
	    } else {
	        // Browser globals
	        factory(jQuery);
	    }
	}(function($) {
	  var pluginName = "tipso",
	    defaults = {
	      speed             : 400,          //Animation speed
	      background        : '#55b555',
	      titleBackground   : '#333333',
	      color             : '#ffffff',
	      titleColor        : '#ffffff',
	      titleContent      : '',           //Content of the title bar
	      showArrow         : true,
	      position          : 'top',
	      width             : 200,
	      maxWidth          : '',
	      delay             : 200,
	      hideDelay         : 0,
	      animationIn       : '',
	      animationOut      : '',
	      offsetX           : 0,
	      offsetY           : 0,
	      arrowWidth        : 8,
	      tooltipHover      : false,
	      content           : null,
	      ajaxContentUrl    : null,
	      ajaxContentBuffer : 0,
	      contentElementId  : null,         //Normally used for picking template scripts
	      useTitle          : false,        //Use the title tag as tooptip or not
	      templateEngineFunc: null,         //A function that compiles and renders the content
	      onBeforeShow      : null,
	      onShow            : null,
	      onHide            : null
	    };
	
	  function Plugin(element, options) {
	    this.element = element;
	    this.$element = $(this.element);
	    this.doc = $(document);
	    this.win = $(window);
	    this.settings = $.extend({}, defaults, options);
	
	    /*
	     * Process and add data-attrs to settings as well for ease of use. Also, if
	     * data-tipso is an object then use it as extra settings and if it's not
	     * then use it as a title.
	     */
	    if (typeof(this.$element.data("tipso")) === "object")
	    {
	      $.extend(this.settings, this.$element.data("tipso"));
	    }
	
	    var data_keys = Object.keys(this.$element.data());
	    var data_attrs = {};
	    for (var i = 0; i < data_keys.length; i++)
	    {
	      var key = data_keys[i].replace(pluginName, "");
	      if (key === "")
	      {
	        continue;
	      }
	      //lowercase first letter
	      key = key.charAt(0).toLowerCase() + key.slice(1);
	      data_attrs[key] = this.$element.data(data_keys[i]);
	
	      //We cannot use extend for data_attrs because they are automatically
	      //lowercased. We need to do this manually and extend this.settings with
	      //data_attrs
	      for (var settings_key in this.settings)
	      {
	        if (settings_key.toLowerCase() == key)
	        {
	          this.settings[settings_key] = data_attrs[key];
	        }
	      }
	    }
	
	    this._defaults = defaults;
	    this._name = pluginName;
	    this._title = this.$element.attr('title');
	    this.mode = 'hide';
	    this.ieFade = !supportsTransitions;
	
	    //By keeping the original prefered position and repositioning by calling
	    //the reposition function we can make for more smart and easier positioning
	    //in complex scenarios!
	    this.settings.preferedPosition = this.settings.position;
	
	    this.init();
	  }
	
	  $.extend(Plugin.prototype, {
	    init: function() {
	      var obj = this,
	        $e = this.$element,
	        $doc = this.doc;
	      $e.addClass('tipso_style').removeAttr('title');
	
	      if (obj.settings.tooltipHover) {
	        var waitForHover = null,
	            hoverHelper = null;
	        $e.on('mouseover' + '.' + pluginName, function() {
	          clearTimeout(waitForHover);
	          clearTimeout(hoverHelper);
	          hoverHelper = setTimeout(function(){
	            obj.show();
	          }, 150);
	        });
	        $e.on('mouseout' + '.' + pluginName, function() {
	          clearTimeout(waitForHover);
	          clearTimeout(hoverHelper);
	          waitForHover = setTimeout(function(){
	            obj.hide();
	          }, 200);
	
	          obj.tooltip()
	            .on('mouseover' + '.' + pluginName, function() {
	              obj.mode = 'tooltipHover';
	            })
	            .on('mouseout' + '.' + pluginName, function() {
	              obj.mode = 'show';
	              clearTimeout(waitForHover);
	              waitForHover = setTimeout(function(){
	                obj.hide();
	              }, 200);
	            })
	        ;
	        });
	      } else {
	        $e.on('mouseover' + '.' + pluginName, function() {
	          obj.show();
	        });
	        $e.on('mouseout' + '.' + pluginName, function() {
	          obj.hide();
	        });
	      }
		  if(obj.settings.ajaxContentUrl)
		  {
			obj.ajaxContent = null;
		  }
	    },
	    tooltip: function() {
	      if (!this.tipso_bubble) {
	        this.tipso_bubble = $(
	          '<div class="tipso_bubble"><div class="tipso_title"></div><div class="tipso_content"></div><div class="tipso_arrow"></div></div>'
	        );
	      }
	      return this.tipso_bubble;
	    },
	    show: function() {
	      var tipso_bubble = this.tooltip(),
	        obj = this,
	        $win = this.win;
	
	      if (obj.settings.showArrow === false) {
	          tipso_bubble.find(".tipso_arrow").hide();
	      }
	      else {
	          tipso_bubble.find(".tipso_arrow").show();
	      }
	
	      if (obj.mode === 'hide') {
	        if ($.isFunction(obj.settings.onBeforeShow)) {
	          obj.settings.onBeforeShow(obj.$element, obj.element, obj);
	        }
	        if (obj.settings.size) {
	            tipso_bubble.addClass(obj.settings.size);
	        }
	        if (obj.settings.width) {
	          tipso_bubble.css({
	            background: obj.settings.background,
	            color: obj.settings.color,
	            width: obj.settings.width
	          }).hide();
	        } else if (obj.settings.maxWidth){
	          tipso_bubble.css({
	            background: obj.settings.background,
	            color: obj.settings.color,
	            maxWidth: obj.settings.maxWidth
	          }).hide();
	        } else {
	          tipso_bubble.css({
	            background: obj.settings.background,
	            color: obj.settings.color,
	            width: 200
	          }).hide();
	        }
	        tipso_bubble.find('.tipso_title').css({
	            background: obj.settings.titleBackground,
	            color: obj.settings.titleColor
	        });
	        tipso_bubble.find('.tipso_content').html(obj.content());
	        tipso_bubble.find('.tipso_title').html(obj.titleContent());
	        reposition(obj);
	
	        $win.on('resize' + '.' + pluginName, function tipsoResizeHandler () {
	            obj.settings.position = obj.settings.preferedPosition;
	            reposition(obj);
	        });
	
	        window.clearTimeout(obj.timeout);
	        obj.timeout = null;
	        obj.timeout = window.setTimeout(function() {
	          if (obj.ieFade || obj.settings.animationIn === '' || obj.settings.animationOut === ''){
	            tipso_bubble.appendTo('body').stop(true, true).fadeIn(obj.settings
	            .speed, function() {
	              obj.mode = 'show';
	              if ($.isFunction(obj.settings.onShow)) {
	                obj.settings.onShow(obj.$element, obj.element, obj);
	              }
	            });
	          } else {
	            tipso_bubble.remove().appendTo('body')
	            .stop(true, true)
	            .removeClass('animated ' + obj.settings.animationOut)
	            .addClass('noAnimation')
	            .removeClass('noAnimation')
	            .addClass('animated ' + obj.settings.animationIn).fadeIn(obj.settings.speed, function() {
	              $(this).one('webkitAnimationEnd mozAnimationEnd MSAnimationEnd oanimationend animationend', function(){
	                $(this).removeClass('animated ' + obj.settings.animationIn);
	              });
	              obj.mode = 'show';
	              if ($.isFunction(obj.settings.onShow)) {
	                obj.settings.onShow(obj.$element, obj.element, obj);
	              }
	              $win.off('resize' + '.' + pluginName, null, 'tipsoResizeHandler');
	            });
	          }
	        }, obj.settings.delay);
	      }
	    },
	    hide: function(force) {
	      var obj = this,
	        $win = this.win,
	        tipso_bubble = this.tooltip(),
	        hideDelay = obj.settings.hideDelay;
	
	      if (force) {
	        hideDelay = 0;
	        obj.mode = 'show';
	      }
	
	      window.clearTimeout(obj.timeout);
	      obj.timeout = null;
	      obj.timeout = window.setTimeout(function() {
	        if (obj.mode !== 'tooltipHover') {
	          if (obj.ieFade || obj.settings.animationIn === '' || obj.settings.animationOut === ''){
	            tipso_bubble.stop(true, true).fadeOut(obj.settings.speed,
	            function() {
	              $(this).remove();
	              if ($.isFunction(obj.settings.onHide) && obj.mode === 'show') {
	                obj.settings.onHide(obj.$element, obj.element, obj);
	              }
	              obj.mode = 'hide';
	              $win.off('resize' + '.' + pluginName, null, 'tipsoResizeHandler');
	            });
	          } else {
	            tipso_bubble.stop(true, true)
	            .removeClass('animated ' + obj.settings.animationIn)
	            .addClass('noAnimation').removeClass('noAnimation')
	            .addClass('animated ' + obj.settings.animationOut)
	            .one('webkitAnimationEnd mozAnimationEnd MSAnimationEnd oanimationend animationend', function(){
	              $(this).removeClass('animated ' + obj.settings.animationOut).remove();
	              if ($.isFunction(obj.settings.onHide) && obj.mode === 'show') {
	                obj.settings.onHide(obj.$element, obj.element, obj);
	              }
	              obj.mode = 'hide';
	              $win.off('resize' + '.' + pluginName, null, 'tipsoResizeHandler');
	            });
	          }
	        }
	      }, hideDelay);
	    },
	    close: function() {
	      this.hide(true);
	    },
	    destroy: function() {
	      var $e = this.$element,
	        $win = this.win,
	        $doc = this.doc;
	      $e.off('.' + pluginName);
	      $win.off('resize' + '.' + pluginName, null, 'tipsoResizeHandler');
	      $e.removeData(pluginName);
	      $e.removeClass('tipso_style').attr('title', this._title);
	    },
	    titleContent: function() {
	        var content,
	          $e = this.$element,
	          obj = this;
	        if (obj.settings.titleContent)
	        {
	            content = obj.settings.titleContent;
	        }
	        else
	        {
	            content = $e.data('tipso-title');
	        }
	        return content;
	    },
	    content: function() {
	      var content,
	        $e = this.$element,
	        obj = this,
	        title = this._title;
	      if (obj.settings.ajaxContentUrl)
	      {
			if(obj._ajaxContent)
			{
				content = obj._ajaxContent;
			}
			else 
			{
				obj._ajaxContent = content = $.ajax({
				  type: "GET",
				  url: obj.settings.ajaxContentUrl,
				  async: false
				}).responseText;
				if(obj.settings.ajaxContentBuffer > 0)
				{
					setTimeout(function(){ 
						obj._ajaxContent = null;
					}, obj.settings.ajaxContentBuffer);
				}
				else 
				{
					obj._ajaxContent = null;
				}
			}
	      }
	      else if (obj.settings.contentElementId)
	      {
	        content = $("#" + obj.settings.contentElementId).text();
	      }
	      else if (obj.settings.content)
	      {
	        content = obj.settings.content;
	      }
	      else
	      {
	        if (obj.settings.useTitle === true)
	        {
	          content = title;
	        }
	        else
	        {
	          // Only use data-tipso as content if it's not being used for settings
	          if (typeof($e.data("tipso")) === "string")
	          {
	            content = $e.data('tipso');
	          }
	        }
	      }
	      if (obj.settings.templateEngineFunc !== null)
	      {
	          content = obj.settings.templateEngineFunc(content);
	      }
	      return content;
	    },
	    update: function(key, value) {
	      var obj = this;
	      if (value) {
	        obj.settings[key] = value;
	      } else {
	        return obj.settings[key];
	      }
	    }
	  });
	
	  function realHeight(obj) {
	    var clone = obj.clone();
	    clone.css("visibility", "hidden");
	    $('body').append(clone);
	    var height = clone.outerHeight();
	    var width = clone.outerWidth();
	    clone.remove();
	    return {
	      'width' : width,
	      'height' : height
	    };
	  }
	
	  var supportsTransitions = (function() {
	    var s = document.createElement('p').style,
	        v = ['ms','O','Moz','Webkit'];
	    if( s['transition'] === '' ) return true;
	    while( v.length )
	        if( v.pop() + 'Transition' in s )
	            return true;
	    return false;
	  })();
	
	  function removeCornerClasses(obj) {
	    obj.removeClass("top_right_corner bottom_right_corner top_left_corner bottom_left_corner");
	    obj.find(".tipso_title").removeClass("top_right_corner bottom_right_corner top_left_corner bottom_left_corner");
	  }
	
	  function reposition(thisthat) {
	    var tipso_bubble = thisthat.tooltip(),
	      $e = thisthat.$element,
	      obj = thisthat,
	      $win = $(window),
	      arrow = 10,
	      pos_top, pos_left, diff;
	
	    var arrow_color = obj.settings.background;
	    var title_content = obj.titleContent();
	    if (title_content !== undefined && title_content !== '') {
	        arrow_color = obj.settings.titleBackground;
	    }
	
	    if ($e.parent().outerWidth() > $win.outerWidth()) {
	      $win = $e.parent();
	    }
	
	    switch (obj.settings.position)
	    {
	      case 'top-right':
	        pos_left = $e.offset().left + ($e.outerWidth());
	        pos_top = $e.offset().top - realHeight(tipso_bubble).height - arrow;
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: -obj.settings.arrowWidth,
	          marginTop: '',
	        });
	        if (pos_top < $win.scrollTop())
	        {
	          pos_top = $e.offset().top + $e.outerHeight() + arrow;
	
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-bottom-color': arrow_color,
	            'border-top-color': 'transparent',
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	
	          /*
	           * Hide and show the appropriate rounded corners
	           */
	          removeCornerClasses(tipso_bubble);
	          tipso_bubble.addClass("bottom_right_corner");
	          tipso_bubble.find(".tipso_title").addClass("bottom_right_corner");
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-left-color': arrow_color,
	          });
	
	          tipso_bubble.removeClass('top-right top bottom left right');
	          tipso_bubble.addClass('bottom');
	        }
	        else
	        {
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-top-color': obj.settings.background,
	            'border-bottom-color': 'transparent ',
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	
	          /*
	           * Hide and show the appropriate rounded corners
	           */
	          removeCornerClasses(tipso_bubble);
	          tipso_bubble.addClass("top_right_corner");
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-left-color': obj.settings.background,
	          });
	
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass('top');
	        }
	        break;
	      case 'top-left':
	        pos_left = $e.offset().left - (realHeight(tipso_bubble).width);
	        pos_top = $e.offset().top - realHeight(tipso_bubble).height - arrow;
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: -obj.settings.arrowWidth,
	          marginTop: '',
	        });
	        if (pos_top < $win.scrollTop())
	        {
	          pos_top = $e.offset().top + $e.outerHeight() + arrow;
	
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-bottom-color': arrow_color,
	            'border-top-color': 'transparent',
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	
	          /*
	           * Hide and show the appropriate rounded corners
	           */
	          removeCornerClasses(tipso_bubble);
	          tipso_bubble.addClass("bottom_left_corner");
	          tipso_bubble.find(".tipso_title").addClass("bottom_left_corner");
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-right-color': arrow_color,
	          });
	
	          tipso_bubble.removeClass('top-right top bottom left right');
	          tipso_bubble.addClass('bottom');
	        }
	        else
	        {
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-top-color': obj.settings.background,
	            'border-bottom-color': 'transparent ',
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	
	          /*
	           * Hide and show the appropriate rounded corners
	           */
	          removeCornerClasses(tipso_bubble);
	          tipso_bubble.addClass("top_left_corner");
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-right-color': obj.settings.background,
	          });
	
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass('top');
	        }
	        break;
	
	      /*
	       * Bottom right position
	       */
	      case 'bottom-right':
	       pos_left = $e.offset().left + ($e.outerWidth());
	       pos_top = $e.offset().top + $e.outerHeight() + arrow;
	       tipso_bubble.find('.tipso_arrow').css({
	         marginLeft: -obj.settings.arrowWidth,
	         marginTop: '',
	       });
	       if (pos_top + realHeight(tipso_bubble).height > $win.scrollTop() + $win.outerHeight())
	       {
	         pos_top = $e.offset().top - realHeight(tipso_bubble).height - arrow;
	
	         tipso_bubble.find('.tipso_arrow').css({
	           'border-bottom-color': 'transparent',
	           'border-top-color': obj.settings.background,
	           'border-left-color': 'transparent',
	           'border-right-color': 'transparent'
	         });
	
	         /*
	          * Hide and show the appropriate rounded corners
	          */
	         removeCornerClasses(tipso_bubble);
	         tipso_bubble.addClass("top_right_corner");
	         tipso_bubble.find(".tipso_title").addClass("top_left_corner");
	         tipso_bubble.find('.tipso_arrow').css({
	           'border-left-color': obj.settings.background,
	         });
	
	         tipso_bubble.removeClass('top-right top bottom left right');
	         tipso_bubble.addClass('top');
	       }
	       else
	       {
	         tipso_bubble.find('.tipso_arrow').css({
	           'border-top-color': 'transparent',
	           'border-bottom-color': arrow_color,
	           'border-left-color': 'transparent',
	           'border-right-color': 'transparent'
	         });
	
	         /*
	          * Hide and show the appropriate rounded corners
	          */
	         removeCornerClasses(tipso_bubble);
	         tipso_bubble.addClass("bottom_right_corner");
	         tipso_bubble.find(".tipso_title").addClass("bottom_right_corner");
	         tipso_bubble.find('.tipso_arrow').css({
	           'border-left-color': arrow_color,
	         });
	
	         tipso_bubble.removeClass('top bottom left right');
	         tipso_bubble.addClass('bottom');
	       }
	       break;
	
	       /*
	        * Bottom left position
	        */
	       case 'bottom-left':
	        pos_left = $e.offset().left - (realHeight(tipso_bubble).width);
	        pos_top = $e.offset().top + $e.outerHeight() + arrow;
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: -obj.settings.arrowWidth,
	          marginTop: '',
	        });
	        if (pos_top + realHeight(tipso_bubble).height > $win.scrollTop() + $win.outerHeight())
	        {
	          pos_top = $e.offset().top - realHeight(tipso_bubble).height - arrow;
	
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-bottom-color': 'transparent',
	            'border-top-color': obj.settings.background,
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	
	          /*
	           * Hide and show the appropriate rounded corners
	           */
	          removeCornerClasses(tipso_bubble);
	          tipso_bubble.addClass("top_left_corner");
	          tipso_bubble.find(".tipso_title").addClass("top_left_corner");
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-right-color': obj.settings.background,
	          });
	
	          tipso_bubble.removeClass('top-right top bottom left right');
	          tipso_bubble.addClass('top');
	        }
	        else
	        {
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-top-color': 'transparent',
	            'border-bottom-color': arrow_color,
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	
	          /*
	           * Hide and show the appropriate rounded corners
	           */
	          removeCornerClasses(tipso_bubble);
	          tipso_bubble.addClass("bottom_left_corner");
	          tipso_bubble.find(".tipso_title").addClass("bottom_left_corner");
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-right-color': arrow_color,
	          });
	
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass('bottom');
	        }
	        break;
	      /*
	       * Top position
	       */
	      case 'top':
	        pos_left = $e.offset().left + ($e.outerWidth() / 2) - (realHeight(tipso_bubble).width / 2);
	        pos_top = $e.offset().top - realHeight(tipso_bubble).height - arrow;
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: -obj.settings.arrowWidth,
	          marginTop: '',
	        });
	        if (pos_top < $win.scrollTop())
	        {
	          pos_top = $e.offset().top + $e.outerHeight() + arrow;
	
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-bottom-color': arrow_color,
	            'border-top-color': 'transparent',
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass('bottom');
	        }
	        else
	        {
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-top-color': obj.settings.background,
	            'border-bottom-color': 'transparent',
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass('top');
	        }
	        break;
	      case 'bottom':
	        pos_left = $e.offset().left + ($e.outerWidth() / 2) - (realHeight(tipso_bubble).width / 2);
	        pos_top = $e.offset().top + $e.outerHeight() + arrow;
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: -obj.settings.arrowWidth,
	          marginTop: '',
	        });
	        if (pos_top + realHeight(tipso_bubble).height > $win.scrollTop() + $win.outerHeight())
	        {
	          pos_top = $e.offset().top - realHeight(tipso_bubble).height - arrow;
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-top-color': obj.settings.background,
	            'border-bottom-color': 'transparent',
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass('top');
	        }
	        else
	        {
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-bottom-color': arrow_color,
	            'border-top-color': 'transparent',
	            'border-left-color': 'transparent',
	            'border-right-color': 'transparent'
	          });
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass(obj.settings.position);
	        }
	        break;
	      case 'left':
	        pos_left = $e.offset().left - realHeight(tipso_bubble).width - arrow;
	        pos_top = $e.offset().top + ($e.outerHeight() / 2) - (realHeight(tipso_bubble).height / 2);
	        tipso_bubble.find('.tipso_arrow').css({
	          marginTop: -obj.settings.arrowWidth,
	          marginLeft: ''
	        });
	        if (pos_left < $win.scrollLeft())
	        {
	          pos_left = $e.offset().left + $e.outerWidth() + arrow;
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-right-color': obj.settings.background,
	            'border-left-color': 'transparent',
	            'border-top-color': 'transparent',
	            'border-bottom-color': 'transparent'
	          });
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass('right');
	        }
	        else
	        {
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-left-color': obj.settings.background,
	            'border-right-color': 'transparent',
	            'border-top-color': 'transparent',
	            'border-bottom-color': 'transparent'
	          });
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass(obj.settings.position);
	        }
	        break;
	      case 'right':
	        pos_left = $e.offset().left + $e.outerWidth() + arrow;
	        pos_top = $e.offset().top + ($e.outerHeight() / 2) - (realHeight(tipso_bubble).height / 2);
	        tipso_bubble.find('.tipso_arrow').css({
	          marginTop: -obj.settings.arrowWidth,
	          marginLeft: ''
	        });
	        if (pos_left + arrow + obj.settings.width > $win.scrollLeft() + $win.outerWidth())
	        {
	          pos_left = $e.offset().left - realHeight(tipso_bubble).width - arrow;
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-left-color': obj.settings.background,
	            'border-right-color': 'transparent',
	            'border-top-color': 'transparent',
	            'border-bottom-color': 'transparent'
	          });
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass('left');
	        }
	        else
	        {
	          tipso_bubble.find('.tipso_arrow').css({
	            'border-right-color': obj.settings.background,
	            'border-left-color': 'transparent',
	            'border-top-color': 'transparent',
	            'border-bottom-color': 'transparent'
	          });
	          tipso_bubble.removeClass('top bottom left right');
	          tipso_bubble.addClass(obj.settings.position);
	        }
	        break;
	    }
	    /*
	     * Set the position of the arrow for the corner positions
	     */
	    if (obj.settings.position === 'top-right')
	    {
	      tipso_bubble.find('.tipso_arrow').css({
	        'margin-left': -obj.settings.width / 2
	      });
	    }
	    if (obj.settings.position === 'top-left')
	    {
	      var tipso_arrow = tipso_bubble.find(".tipso_arrow").eq(0);
	      tipso_arrow.css({
	        'margin-left': obj.settings.width / 2 - 2 * obj.settings.arrowWidth
	      });
	    }
	    if (obj.settings.position === 'bottom-right')
	    {
	      var tipso_arrow = tipso_bubble.find(".tipso_arrow").eq(0);
	      tipso_arrow.css({
	        'margin-left': -obj.settings.width / 2,
	        'margin-top': ''
	      });
	    }
	    if (obj.settings.position === 'bottom-left')
	    {
	      var tipso_arrow = tipso_bubble.find(".tipso_arrow").eq(0);
	      tipso_arrow.css({
	        'margin-left': obj.settings.width / 2 - 2 * obj.settings.arrowWidth,
	        'margin-top': ''
	      });
	    }
	
	    /*
	     * Check out of boundness
	     */
	    if (pos_left < $win.scrollLeft() && (obj.settings.position === 'bottom' || obj.settings.position === 'top'))
	    {
	      tipso_bubble.find('.tipso_arrow').css({
	        marginLeft: pos_left - obj.settings.arrowWidth
	      });
	      pos_left = 0;
	    }
	    if (pos_left + obj.settings.width > $win.outerWidth() && (obj.settings.position === 'bottom' || obj.settings.position === 'top'))
	    {
	      diff = $win.outerWidth() - (pos_left + obj.settings.width);
	      tipso_bubble.find('.tipso_arrow').css({
	        marginLeft: -diff - obj.settings.arrowWidth,
	        marginTop: ''
	      });
	      pos_left = pos_left + diff;
	    }
	    if (pos_left < $win.scrollLeft() &&
	       (obj.settings.position === 'left' ||
	        obj.settings.position === 'right' ||
	        obj.settings.position === 'top-right' ||
	        obj.settings.position === 'top-left' ||
	        obj.settings.position === 'bottom-right' ||
	        obj.settings.position === 'bottom-left'))
	    {
	      pos_left = $e.offset().left + ($e.outerWidth() / 2) - (realHeight(tipso_bubble).width / 2);
	      tipso_bubble.find('.tipso_arrow').css({
	        marginLeft: -obj.settings.arrowWidth,
	        marginTop: ''
	      });
	      pos_top = $e.offset().top - realHeight(tipso_bubble).height - arrow;
	      if (pos_top < $win.scrollTop())
	      {
	        pos_top = $e.offset().top + $e.outerHeight() + arrow;
	        tipso_bubble.find('.tipso_arrow').css({
	          'border-bottom-color': arrow_color,
	          'border-top-color': 'transparent',
	          'border-left-color': 'transparent',
	          'border-right-color': 'transparent'
	        });
	        tipso_bubble.removeClass('top bottom left right');
	        removeCornerClasses(tipso_bubble);
	        tipso_bubble.addClass('bottom');
	      }
	      else
	      {
	        tipso_bubble.find('.tipso_arrow').css({
	          'border-top-color': obj.settings.background,
	          'border-bottom-color': 'transparent',
	          'border-left-color': 'transparent',
	          'border-right-color': 'transparent'
	        });
	        tipso_bubble.removeClass('top bottom left right');
	        removeCornerClasses(tipso_bubble);
	        tipso_bubble.addClass('top');
	      }
	      if (pos_left + obj.settings.width > $win.outerWidth())
	      {
	        diff = $win.outerWidth() - (pos_left + obj.settings.width);
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: -diff - obj.settings.arrowWidth,
	          marginTop: ''
	        });
	        pos_left = pos_left + diff;
	      }
	      if (pos_left < $win.scrollLeft())
	      {
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: pos_left - obj.settings.arrowWidth
	        });
	        pos_left = 0;
	      }
	    }
	
	    /*
	     * If out of bounds from the right hand side
	     */
	    if (pos_left + obj.settings.width > $win.outerWidth() &&
	       (obj.settings.position === 'left' ||
	        obj.settings.position === 'right' ||
	        obj.settings.position === 'top-right' ||
	        obj.settings.position === 'top-left' ||
	        obj.settings.position === 'bottom-right' ||
	        obj.settings.position === 'bottom-right'))
	    {
	      pos_left = $e.offset().left + ($e.outerWidth() / 2) - (realHeight(tipso_bubble).width / 2);
	      tipso_bubble.find('.tipso_arrow').css({
	        marginLeft: -obj.settings.arrowWidth,
	        marginTop: ''
	      });
	      pos_top = $e.offset().top - realHeight(tipso_bubble).height - arrow;
	      if (pos_top < $win.scrollTop())
	      {
	        pos_top = $e.offset().top + $e.outerHeight() + arrow;
	        tipso_bubble.find('.tipso_arrow').css({
	          'border-bottom-color': arrow_color,
	          'border-top-color': 'transparent',
	          'border-left-color': 'transparent',
	          'border-right-color': 'transparent'
	        });
	
	        removeCornerClasses(tipso_bubble);
	        tipso_bubble.removeClass('top bottom left right');
	        tipso_bubble.addClass('bottom');
	      }
	      else
	      {
	        tipso_bubble.find('.tipso_arrow').css({
	          'border-top-color': obj.settings.background,
	          'border-bottom-color': 'transparent',
	          'border-left-color': 'transparent',
	          'border-right-color': 'transparent'
	        });
	
	        /*
	         * Hide and show the appropriate rounded corners
	         */
	        removeCornerClasses(tipso_bubble);
	        tipso_bubble.removeClass('top bottom left right');
	        tipso_bubble.addClass('top');
	      }
	      if (pos_left + obj.settings.width > $win.outerWidth())
	      {
	        diff = $win.outerWidth() - (pos_left + obj.settings.width);
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: -diff - obj.settings.arrowWidth,
	          marginTop: ''
	        });
	        pos_left = pos_left + diff;
	      }
	      if (pos_left < $win.scrollLeft())
	      {
	        tipso_bubble.find('.tipso_arrow').css({
	          marginLeft: pos_left - obj.settings.arrowWidth
	        });
	        pos_left = 0;
	      }
	    }
	    tipso_bubble.css({
	      left: pos_left + obj.settings.offsetX,
	      top: pos_top + obj.settings.offsetY
	    });
	
	    // If positioned right or left and tooltip is out of bounds change position
	    // This position change will be temporary, because preferedPosition is there
	    // to help!!
	    if (pos_top < $win.scrollTop() && (obj.settings.position === 'right' || obj.settings.position === 'left'))
	    {
	      $e.tipso('update', 'position', 'bottom');
	      reposition(obj);
	    }
	    if (pos_top + realHeight(tipso_bubble).height > $win.scrollTop() + $win.outerHeight() &&
	        (obj.settings.position === 'right' || obj.settings.position === 'left'))
	    {
	      $e.tipso('update', 'position', 'top');
	      reposition(obj);
	    }
	
	  }
	  $[pluginName] = $.fn[pluginName] = function(options) {
	    var args = arguments;
	    if (options === undefined || typeof options === 'object') {
	      if (!(this instanceof $)) {
	        $.extend(defaults, options);
	      }
	      return this.each(function() {
	        if (!$.data(this, 'plugin_' + pluginName)) {
	          $.data(this, 'plugin_' + pluginName, new Plugin(this, options));
	        }
	      });
	    } else if (typeof options === 'string' && options[0] !== '_' && options !==
	      'init') {
	      var returns;
	      this.each(function() {
	        var instance = $.data(this, 'plugin_' + pluginName);
	        if (!instance) {
	          instance = $.data(this, 'plugin_' + pluginName, new Plugin(
	            this, options));
	        }
	        if (instance instanceof Plugin && typeof instance[options] ===
	          'function') {
	          returns = instance[options].apply(instance, Array.prototype.slice
	            .call(args, 1));
	        }
	        if (options === 'destroy') {
	          $.data(this, 'plugin_' + pluginName, null);
	        }
	      });
	      return returns !== undefined ? returns : this;
	    }
	  };
	}));


/***/ }),
/* 27 */
/***/ (function(module, exports, __webpack_require__) {

	var $, scrollbarWidth;
	
	$ = __webpack_require__(2);
	
	scrollbarWidth = __webpack_require__(28);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    return $target.find('.js-scroll-nav').each(function() {
	      var $list, $wrap, addArrow, arrowTpl, destroy, handleResize, handleScroll, hasBackground, hasScrollbar, init, isInit, move, recalculate, removeArrow, scrollLeft, scrollWidth;
	      $list = $(this);
	      $wrap = $list.parent();
	      isInit = false;
	      scrollLeft = 0;
	      scrollWidth = $list.get(0).scrollWidth;
	      hasBackground = false;
	      arrowTpl = function(direction) {
	        var className;
	        className = "scroll-nav scroll-nav--" + direction;
	        if (hasBackground) {
	          className = className + " scroll-nav--background";
	        }
	        return "<a href='#' class='" + className + "'><span class='icon icon-chevron-" + direction + "'></span></a>";
	      };
	      hasScrollbar = function() {
	        return Math.abs(scrollWidth - $list.innerWidth()) > 2;
	      };
	      init = function() {
	        var $active, $closest;
	        isInit = true;
	        if ($list.filter('.menu-secondary__list').length) {
	          hasBackground = true;
	        }
	        addArrow('right');
	        $list.css('marginBottom', -scrollbarWidth());
	        $wrap.on('mousedown touchstart', '.scroll-nav', function(event) {
	          event.preventDefault();
	          if ($(this).hasClass('scroll-nav--right')) {
	            return move('right');
	          } else if ($(this).hasClass('scroll-nav--left')) {
	            return move('left');
	          }
	        }).on('mouseup touchend', '.scroll-nav', function() {
	          return $list.stop();
	        }).on('click', '.scroll-nav', function(event) {
	          return event.preventDefault();
	        });
	        $list.on('scroll', function() {
	          return handleScroll();
	        });
	        if ($list.find('.menu-secondary__link.is-active').length) {
	          $active = $list.find('.menu-secondary__link.is-active').parent();
	          $closest = $active.closest('.menu-secondary__wrap');
	          console.log('----');
	          console.log($active);
	          console.log($active.offset().left);
	          console.log($active.outerWidth());
	          console.log($list.width());
	          console.log('----');
	          if ($active.offset().left + $active.outerWidth() > $list.width()) {
	            $list.scrollLeft($active.offset().left + $active.outerWidth());
	            return $wrap.find('.scroll-nav--right').trigger('mousedown');
	          }
	        }
	      };
	      recalculate = function() {
	        scrollWidth = $list.get(0).scrollWidth;
	        return handleScroll();
	      };
	      destroy = function() {
	        isInit = false;
	        scrollLeft = 0;
	        removeArrow('left');
	        removeArrow('right');
	        $list.css('marginBottom', '');
	        $wrap.off('mousedown touchstart mouseup touchend', '.scroll-nav');
	        return $list.off('scroll');
	      };
	      addArrow = function(direction) {
	        var $arrow;
	        $arrow = $wrap.find(".scroll-nav--" + direction);
	        if (!$arrow.length) {
	          return $list.after(arrowTpl(direction));
	        }
	      };
	      removeArrow = function(direction) {
	        var $arrow;
	        $arrow = $wrap.find(".scroll-nav--" + direction);
	        if ($arrow.length) {
	          return $arrow.remove();
	        }
	      };
	      handleScroll = function() {
	        scrollLeft = $list.scrollLeft();
	        if (scrollLeft >= 5) {
	          addArrow('left');
	        } else {
	          removeArrow('left');
	        }
	        if (((scrollWidth - $list.innerWidth()) - scrollLeft) <= 5) {
	          return removeArrow('right');
	        } else {
	          return addArrow('right');
	        }
	      };
	      handleResize = function() {
	        if (hasScrollbar()) {
	          if (isInit) {
	            return recalculate();
	          } else {
	            return init();
	          }
	        } else {
	          if (isInit) {
	            return destroy();
	          }
	        }
	      };
	      move = function(direction) {
	        var distance, duration, scroll, speed;
	        speed = 310 / 1000;
	        duration = 0;
	        distance = 0;
	        if (direction === 'right') {
	          scroll = scrollWidth;
	          distance = scrollWidth - $list.innerWidth();
	        } else if (direction === 'left') {
	          scroll = 0;
	          distance = scrollLeft;
	        }
	        duration = distance / speed;
	        return $list.stop().animate({
	          scrollLeft: scroll
	        }, duration, 'linear');
	      };
	      $(window).on('resize', handleResize);
	      if (hasScrollbar()) {
	        return init();
	      }
	    });
	  }
	};


/***/ }),
/* 28 */
/***/ (function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;/*! scrollbarWidth.js v0.1.3 | felixexter | MIT | https://github.com/felixexter/scrollbarWidth */
	(function (root, factory) {
		if (true) {
			!(__WEBPACK_AMD_DEFINE_ARRAY__ = [], __WEBPACK_AMD_DEFINE_FACTORY__ = (factory), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
		} else if (typeof exports === 'object') {
			module.exports = factory();
		} else {
			(root.jQuery || root).scrollbarWidth = factory();
		}
	}(this, function () {
		'use strict';
	
		function scrollbarWidth() {
			if (typeof document === 'undefined') {
				return 0
			}
	
			var
				body = document.body,
				box = document.createElement('div'),
				boxStyle = box.style,
				width;
	
			boxStyle.position = 'absolute';
			boxStyle.top = boxStyle.left = '-9999px';
			boxStyle.width = boxStyle.height = '100px';
			boxStyle.overflow = 'scroll';
	
			body.appendChild(box);
	
			width = box.offsetWidth - box.clientWidth;
	
			body.removeChild(box);
	
			return width;
		}
	
		return scrollbarWidth;
	}));


/***/ }),
/* 29 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	__webpack_require__(30);
	
	module.exports = {
	  init: function(payload) {
	    var $target;
	    $target = payload.$target;
	    $target.find('.js-scrollbar--y').tinyscrollbar();
	    return $target.find('.js-scrollbar--x').tinyscrollbar({
	      axis: 'x'
	    });
	  }
	};


/***/ }),
/* 30 */
/***/ (function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;;(function(factory) {
	    if (true) {
	        !(__WEBPACK_AMD_DEFINE_ARRAY__ = [__webpack_require__(2)], __WEBPACK_AMD_DEFINE_FACTORY__ = (factory), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
	    }
	    else if (typeof exports === 'object') {
	        module.exports = factory(require("jquery"));
	    }
	    else {
	        factory(jQuery);
	    }
	}
	(function($) {
	    "use strict";
	
	    var pluginName = "tinyscrollbar"
	    ,   defaults = {
	            axis : 'y'
	        ,   wheel : true
	        ,   wheelSpeed : 40
	        ,   wheelLock : true
	        ,   touchLock : true
	        ,   trackSize : false
	        ,   thumbSize : false
	        ,   thumbSizeMin : 20
	        }
	    ;
	
	    function Plugin($container, options) {
	        /**
	         * The options of the carousel extend with the defaults.
	         *
	         * @property options
	         * @type Object
	         */
	        this.options = $.extend({}, defaults, options);
	
	        /**
	         * @property _defaults
	         * @type Object
	         * @private
	         * @default defaults
	         */
	        this._defaults = defaults;
	
	        /**
	         * @property _name
	         * @type String
	         * @private
	         * @final
	         * @default 'tinyscrollbar'
	         */
	        this._name = pluginName;
	
	        var self = this
	        ,   $viewport = $container.find(".viewport")
	        ,   $overview = $container.find(".overview")
	        ,   $scrollbar = $container.find(".scrollbar")
	        ,   $track = $scrollbar.find(".track")
	        ,   $thumb = $scrollbar.find(".thumb")
	
	        ,   hasTouchEvents = ("ontouchstart" in document.documentElement)
	        ,   wheelEvent = "onwheel" in document.createElement("div") ? "wheel" : // Modern browsers support "wheel"
	                         document.onmousewheel !== undefined ? "mousewheel" : // Webkit and IE support at least "mousewheel"
	                         "DOMMouseScroll" // let's assume that remaining browsers are older Firefox
	        ,   isHorizontal = this.options.axis === 'x'
	        ,   sizeLabel = isHorizontal ? "width" : "height"
	        ,   posiLabel = isHorizontal ? "left" : "top"
	
	        ,   mousePosition = 0
	        ;
	
	        /**
	         * The position of the content relative to the viewport.
	         *
	         * @property contentPosition
	         * @type Number
	         */
	        this.contentPosition = 0;
	
	        /**
	         * The height or width of the viewport.
	         *
	         * @property viewportSize
	         * @type Number
	         */
	        this.viewportSize = 0;
	
	        /**
	         * The height or width of the content.
	         *
	         * @property contentSize
	         * @type Number
	         */
	        this.contentSize = 0;
	
	        /**
	         * The ratio of the content size relative to the viewport size.
	         *
	         * @property contentRatio
	         * @type Number
	         */
	        this.contentRatio = 0;
	
	        /**
	         * The height or width of the content.
	         *
	         * @property trackSize
	         * @type Number
	         */
	        this.trackSize = 0;
	
	        /**
	         * The size of the track relative to the size of the content.
	         *
	         * @property trackRatio
	         * @type Number
	         */
	        this.trackRatio = 0;
	
	        /**
	         * The height or width of the thumb.
	         *
	         * @property thumbSize
	         * @type Number
	         */
	        this.thumbSize = 0;
	
	        /**
	         * The position of the thumb relative to the track.
	         *
	         * @property thumbPosition
	         * @type Number
	         */
	        this.thumbPosition = 0;
	
	        /**
	         * Will be true if there is content to scroll.
	         *
	         * @property hasContentToSroll
	         * @type Boolean
	         */
	        this.hasContentToSroll = false;
	
	        /**
	         * @method _initialize
	         * @private
	         */
	        function _initialize() {
	            self.update();
	            _setEvents();
	
	            return self;
	        }
	
	        /**
	         * You can use the update method to adjust the scrollbar to new content or to move the scrollbar to a certain point.
	         *
	         * @method update
	         * @chainable
	         * @param {Number|String} [scrollTo] Number in pixels or the values "relative" or "bottom". If you dont specify a parameter it will default to top
	         */
	        this.update = function(scrollTo) {
	            var sizeLabelCap = sizeLabel.charAt(0).toUpperCase() + sizeLabel.slice(1).toLowerCase();
	            this.viewportSize = $viewport[0]['offset'+ sizeLabelCap];
	            this.contentSize = $overview[0]['scroll'+ sizeLabelCap];
	            this.contentRatio = this.viewportSize / this.contentSize;
	            this.trackSize = this.options.trackSize || this.viewportSize;
	            this.thumbSize = Math.min(this.trackSize, Math.max(this.options.thumbSizeMin, (this.options.thumbSize || (this.trackSize * this.contentRatio))));
	            this.trackRatio = (this.contentSize - this.viewportSize) / (this.trackSize - this.thumbSize);
	            this.hasContentToSroll = this.contentRatio < 1;
	
	            $scrollbar.toggleClass("disable", !this.hasContentToSroll);
	
	            switch (scrollTo) {
	                case "bottom":
	                    this.contentPosition = Math.max(this.contentSize - this.viewportSize, 0);
	                    break;
	
	                case "relative":
	                    this.contentPosition = Math.min(Math.max(this.contentSize - this.viewportSize, 0), Math.max(0, this.contentPosition));
	                    break;
	
	                default:
	                    this.contentPosition = parseInt(scrollTo, 10) || 0;
	            }
	
	            this.thumbPosition = this.contentPosition / this.trackRatio;
	
	            _setCss();
	
	            return self;
	        };
	
	        /**
	         * @method _setCss
	         * @private
	         */
	        function _setCss() {
	            $thumb.css(posiLabel, self.thumbPosition);
	            $overview.css(posiLabel, -self.contentPosition);
	            $scrollbar.css(sizeLabel, self.trackSize);
	            $track.css(sizeLabel, self.trackSize);
	            $thumb.css(sizeLabel, self.thumbSize);
	        }
	
	        /**
	         * @method _setEvents
	         * @private
	         */
	        function _setEvents() {
	            if(hasTouchEvents) {
	                $viewport[0].ontouchstart = function(event) {
	                    if(1 === event.touches.length) {
	                        event.stopPropagation();
	
	                        _start(event.touches[0]);
	                    }
	                };
	            }
	            $thumb.bind("mousedown", function(event){
	                event.stopPropagation();
	                _start(event);
	            });
	            $track.bind("mousedown", function(event){
	                _start(event, true);
	            });
	
	            $(window).resize(function() {
	                self.update("relative");
	            });
	
	            if(self.options.wheel && window.addEventListener) {
	                $container[0].addEventListener(wheelEvent, _wheel, false);
	            }
	            else if(self.options.wheel) {
	                $container[0].onmousewheel = _wheel;
	            }
	        }
	
	        /**
	         * @method _isAtBegin
	         * @private
	         */
	        function _isAtBegin() {
	            return self.contentPosition > 0;
	        }
	
	        /**
	         * @method _isAtEnd
	         * @private
	         */
	        function _isAtEnd() {
	            return self.contentPosition <= (self.contentSize - self.viewportSize) - 5;
	        }
	
	        /**
	         * @method _start
	         * @private
	         */
	        function _start(event, gotoMouse) {
	            if(self.hasContentToSroll) {
	                $("body").addClass("noSelect");
	
	                mousePosition = gotoMouse ? $thumb.offset()[posiLabel] : (isHorizontal ? event.pageX : event.pageY);
	
	                if(hasTouchEvents) {
	                    document.ontouchmove = function(event) {
	                        if(self.options.touchLock || _isAtBegin() && _isAtEnd()) {
	                            event.preventDefault();
	                        }
	                        event.touches[0][pluginName + "Touch"] = 1;
	                        _drag(event.touches[0]);
	                    };
	                    document.ontouchend = _end;
	                }
	                $(document).bind("mousemove", _drag);
	                $(document).bind("mouseup", _end);
	                $thumb.bind("mouseup", _end);
	                $track.bind("mouseup", _end);
	
	                _drag(event);
	            }
	        }
	
	        /**
	         * @method _wheel
	         * @private
	         */
	        function _wheel(event) {
	            if(self.hasContentToSroll) {
	                // Trying to make sense of all the different wheel event implementations..
	                //
	                var evntObj = event || window.event
	                ,   wheelDelta = -(evntObj.deltaY || evntObj.detail || (-1 / 3 * evntObj.wheelDelta)) / 40
	                ,   multiply = (evntObj.deltaMode === 1) ? self.options.wheelSpeed : 1
	                ;
	
	                self.contentPosition -= wheelDelta * multiply * self.options.wheelSpeed;
	                self.contentPosition = Math.min((self.contentSize - self.viewportSize), Math.max(0, self.contentPosition));
	                self.thumbPosition = self.contentPosition / self.trackRatio;
	
	                /**
	                 * The move event will trigger when the carousel slides to a new slide.
	                 *
	                 * @event move
	                 */
	                $container.trigger("move");
	
	                $thumb.css(posiLabel, self.thumbPosition);
	                $overview.css(posiLabel, -self.contentPosition);
	
	                if(self.options.wheelLock || _isAtBegin() && _isAtEnd()) {
	                    evntObj = $.event.fix(evntObj);
	                    evntObj.preventDefault();
	                }
	            }
	            event.stopPropagation();
	        }
	
	        /**
	         * @method _drag
	         * @private
	         */
	        function _drag(event) {
	            if(self.hasContentToSroll) {
	                var mousePositionNew = isHorizontal ? event.pageX : event.pageY
	                ,   thumbPositionDelta = event[pluginName + "Touch"] ? 
	                        (mousePosition - mousePositionNew) : (mousePositionNew - mousePosition)
	                ,   thumbPositionNew = Math.min((self.trackSize - self.thumbSize), Math.max(0, self.thumbPosition + thumbPositionDelta))
	                ;
	
	                self.contentPosition = thumbPositionNew * self.trackRatio;
	
	                $container.trigger("move");
	
	                $thumb.css(posiLabel, thumbPositionNew);
	                $overview.css(posiLabel, -self.contentPosition);
	            }
	        }
	
	        /**
	         * @method _end
	         * @private
	         */
	        function _end() {
	            self.thumbPosition = parseInt($thumb.css(posiLabel), 10) || 0;
	
	            $("body").removeClass("noSelect");
	            $(document).unbind("mousemove", _drag);
	            $(document).unbind("mouseup", _end);
	            $thumb.unbind("mouseup", _end);
	            $track.unbind("mouseup", _end);
	            document.ontouchmove = document.ontouchend = null;
	        }
	
	        return _initialize();
	    }
	
	    /**
	    * @class tinyscrollbar
	    * @constructor
	    * @param {Object} options
	        @param {String} [options.axis='y'] Vertical or horizontal scroller? ( x || y ).
	        @param {Boolean} [options.wheel=true] Enable or disable the mousewheel.
	        @param {Boolean} [options.wheelSpeed=40] How many pixels must the mouswheel scroll at a time.
	        @param {Boolean} [options.wheelLock=true] Lock default window wheel scrolling when there is no more content to scroll.
	        @param {Number} [options.touchLock=true] Lock default window touch scrolling when there is no more content to scroll.
	        @param {Boolean|Number} [options.trackSize=false] Set the size of the scrollbar to auto(false) or a fixed number.
	        @param {Boolean|Number} [options.thumbSize=false] Set the size of the thumb to auto(false) or a fixed number
	        @param {Boolean} [options.thumbSizeMin=20] Minimum thumb size.
	    */
	    $.fn[pluginName] = function(options) {
	        return this.each(function() {
	            if(!$.data(this, "plugin_" + pluginName)) {
	                $.data(this, "plugin_" + pluginName, new Plugin($(this), options));
	            }
	        });
	    };
	}));


/***/ }),
/* 31 */
/***/ (function(module, exports, __webpack_require__) {

	var $;
	
	$ = __webpack_require__(2);
	
	__webpack_require__(32);
	
	__webpack_require__(33);
	
	__webpack_require__(34);
	
	module.exports = {
	  init: function(payload) {
	    var $target, margin;
	    $target = payload.$target;
	    margin = $(window).width() >= 700 ? [70, 70, 0, 70] : [50, 0, 0, 0];
	    return $target.find('.js-lightbox').fancybox({
	      padding: 0,
	      margin: margin,
	      nextEffect: 'none',
	      prevEffect: 'none',
	      scrolling: 'no',
	      helpers: {
	        thumbs: {
	          width: 130,
	          height: 73
	        },
	        overlay: {
	          locked: true
	        }
	      },
	      tpl: {
	        closeBtn: '<a href="javascript:;" class="fancybox-close fancybox-margin" ><span class="vhide">Zavřít</span><span class="icon icon-close"></span></a>',
	        next: '<a href="javascript:;" class="fancybox-nav fancybox-next"><span class="vhide">Další</span><span class="icon icon-angle-right"></span></a>',
	        prev: '<a href="javascript:;" class="fancybox-nav fancybox-prev"><span class="vhide">Předchozí</span><span class="icon icon-angle-left"></span></a>'
	      },
	      afterLoad: function() {
	        var hasGallery, isFullscreen, thumbs;
	        hasGallery = $(this.element).data('gallery');
	        isFullscreen = $(this.element).data('fullscreen');
	        if (hasGallery === false) {
	          return delete this.helpers.thumbs;
	        } else {
	          $('html').addClass('fancybox-gallery');
	          thumbs = {
	            width: this.helpers.thumbs.width,
	            height: this.helpers.thumbs.height
	          };
	          if ((isFullscreen == null) || isFullscreen === true) {
	            return this.helpers.thumbs = {
	              width: 160,
	              height: 90
	            };
	          } else {
	            return this.helpers.thumbs = thumbs;
	          }
	        }
	      },
	      beforeShow: function() {
	        var caption, isFullscreen, title;
	        title = $(this.element).data('title');
	        caption = $(this.element).data('caption');
	        isFullscreen = $(this.element).data('fullscreen');
	        if (title != null) {
	          this.title = "<p class='h5'>" + title + "</p>";
	        }
	        if (caption != null) {
	          this.title += "<p>" + caption + "</p>";
	        }
	        if ((isFullscreen == null) || isFullscreen === true) {
	          return $('html').addClass('fancybox-fullscreen');
	        }
	      },
	      afterShow: function() {
	        return $(document).swipe({
	          swipe: function(event, direction, distance, duration, fingerCount) {
	            switch (direction) {
	              case 'right':
	                return $.fancybox.prev();
	              case 'left':
	                return $.fancybox.next();
	            }
	          }
	        });
	      },
	      afterClose: function() {
	        $(document).swipe('destroy');
	        $('.fancybox-fullscreen').removeClass('fancybox-fullscreen');
	        return $('.fancybox-gallery').removeClass('fancybox-gallery');
	      }
	    });
	  }
	};


/***/ }),
/* 32 */
/***/ (function(module, exports) {

	/*!
	 * fancyBox - jQuery Plugin
	 * version: 2.1.5 (Fri, 14 Jun 2013)
	 * requires jQuery v1.6 or later
	 *
	 * Examples at http://fancyapps.com/fancybox/
	 * License: www.fancyapps.com/fancybox/#license
	 *
	 * Copyright 2012 Janis Skarnelis - janis@fancyapps.com
	 *
	 */
	
	;(function (window, document, $, undefined) {
		"use strict";
	
		var H = $("html"),
			W = $(window),
			D = $(document),
			F = $.fancybox = function () {
				F.open.apply( this, arguments );
			},
			IE =  navigator.userAgent.match(/msie/i),
			didUpdate	= null,
			isTouch		= document.createTouch !== undefined,
	
			isQuery	= function(obj) {
				return obj && obj.hasOwnProperty && obj instanceof $;
			},
			isString = function(str) {
				return str && $.type(str) === "string";
			},
			isPercentage = function(str) {
				return isString(str) && str.indexOf('%') > 0;
			},
			isScrollable = function(el) {
				return (el && !(el.style.overflow && el.style.overflow === 'hidden') && ((el.clientWidth && el.scrollWidth > el.clientWidth) || (el.clientHeight && el.scrollHeight > el.clientHeight)));
			},
			getScalar = function(orig, dim) {
				var value = parseInt(orig, 10) || 0;
	
				if (dim && isPercentage(orig)) {
					value = F.getViewport()[ dim ] / 100 * value;
				}
	
				return Math.ceil(value);
			},
			getValue = function(value, dim) {
				return getScalar(value, dim) + 'px';
			};
	
		$.extend(F, {
			// The current version of fancyBox
			version: '2.1.5',
	
			defaults: {
				padding : 15,
				margin  : 20,
	
				width     : 800,
				height    : 600,
				minWidth  : 100,
				minHeight : 100,
				maxWidth  : 9999,
				maxHeight : 9999,
				pixelRatio: 1, // Set to 2 for retina display support
	
				autoSize   : true,
				autoHeight : false,
				autoWidth  : false,
	
				autoResize  : true,
				autoCenter  : !isTouch,
				fitToView   : true,
				aspectRatio : false,
				topRatio    : 0.5,
				leftRatio   : 0.5,
	
				scrolling : 'auto', // 'auto', 'yes' or 'no'
				wrapCSS   : '',
	
				arrows     : true,
				closeBtn   : true,
				closeClick : false,
				nextClick  : false,
				mouseWheel : true,
				autoPlay   : false,
				playSpeed  : 3000,
				preload    : 3,
				modal      : false,
				loop       : true,
	
				ajax  : {
					dataType : 'html',
					headers  : { 'X-fancyBox': true }
				},
				iframe : {
					scrolling : 'auto',
					preload   : true
				},
				swf : {
					wmode: 'transparent',
					allowfullscreen   : 'true',
					allowscriptaccess : 'always'
				},
	
				keys  : {
					next : {
						13 : 'left', // enter
						34 : 'up',   // page down
						39 : 'left', // right arrow
						40 : 'up'    // down arrow
					},
					prev : {
						8  : 'right',  // backspace
						33 : 'down',   // page up
						37 : 'right',  // left arrow
						38 : 'down'    // up arrow
					},
					close  : [27], // escape key
					play   : [32], // space - start/stop slideshow
					toggle : [70]  // letter "f" - toggle fullscreen
				},
	
				direction : {
					next : 'left',
					prev : 'right'
				},
	
				scrollOutside  : true,
	
				// Override some properties
				index   : 0,
				type    : null,
				href    : null,
				content : null,
				title   : null,
	
				// HTML templates
				tpl: {
					wrap     : '<div class="fancybox-wrap" tabIndex="-1"><div class="fancybox-skin"><div class="fancybox-outer"><div class="fancybox-inner"></div></div></div></div>',
					image    : '<img class="fancybox-image" src="{href}" alt="" />',
					iframe   : '<iframe id="fancybox-frame{rnd}" name="fancybox-frame{rnd}" class="fancybox-iframe" frameborder="0" vspace="0" hspace="0" webkitAllowFullScreen mozallowfullscreen allowFullScreen' + (IE ? ' allowtransparency="true"' : '') + '></iframe>',
					error    : '<p class="fancybox-error">The requested content cannot be loaded.<br/>Please try again later.</p>',
					closeBtn : '<a title="Close" class="fancybox-item fancybox-close" href="javascript:;"></a>',
					next     : '<a title="Next" class="fancybox-nav fancybox-next" href="javascript:;"><span></span></a>',
					prev     : '<a title="Previous" class="fancybox-nav fancybox-prev" href="javascript:;"><span></span></a>',
					loading  : '<div id="fancybox-loading"><div></div></div>'
				},
	
				// Properties for each animation type
				// Opening fancyBox
				openEffect  : 'fade', // 'elastic', 'fade' or 'none'
				openSpeed   : 250,
				openEasing  : 'swing',
				openOpacity : true,
				openMethod  : 'zoomIn',
	
				// Closing fancyBox
				closeEffect  : 'fade', // 'elastic', 'fade' or 'none'
				closeSpeed   : 250,
				closeEasing  : 'swing',
				closeOpacity : true,
				closeMethod  : 'zoomOut',
	
				// Changing next gallery item
				nextEffect : 'elastic', // 'elastic', 'fade' or 'none'
				nextSpeed  : 250,
				nextEasing : 'swing',
				nextMethod : 'changeIn',
	
				// Changing previous gallery item
				prevEffect : 'elastic', // 'elastic', 'fade' or 'none'
				prevSpeed  : 250,
				prevEasing : 'swing',
				prevMethod : 'changeOut',
	
				// Enable default helpers
				helpers : {
					overlay : true,
					title   : true
				},
	
				// Callbacks
				onCancel     : $.noop, // If canceling
				beforeLoad   : $.noop, // Before loading
				afterLoad    : $.noop, // After loading
				beforeShow   : $.noop, // Before changing in current item
				afterShow    : $.noop, // After opening
				beforeChange : $.noop, // Before changing gallery item
				beforeClose  : $.noop, // Before closing
				afterClose   : $.noop  // After closing
			},
	
			//Current state
			group    : {}, // Selected group
			opts     : {}, // Group options
			previous : null,  // Previous element
			coming   : null,  // Element being loaded
			current  : null,  // Currently loaded element
			isActive : false, // Is activated
			isOpen   : false, // Is currently open
			isOpened : false, // Have been fully opened at least once
	
			wrap  : null,
			skin  : null,
			outer : null,
			inner : null,
	
			player : {
				timer    : null,
				isActive : false
			},
	
			// Loaders
			ajaxLoad   : null,
			imgPreload : null,
	
			// Some collections
			transitions : {},
			helpers     : {},
	
			/*
			 *	Static methods
			 */
	
			open: function (group, opts) {
				if (!group) {
					return;
				}
	
				if (!$.isPlainObject(opts)) {
					opts = {};
				}
	
				// Close if already active
				if (false === F.close(true)) {
					return;
				}
	
				// Normalize group
				if (!$.isArray(group)) {
					group = isQuery(group) ? $(group).get() : [group];
				}
	
				// Recheck if the type of each element is `object` and set content type (image, ajax, etc)
				$.each(group, function(i, element) {
					var obj = {},
						href,
						title,
						content,
						type,
						rez,
						hrefParts,
						selector;
	
					if ($.type(element) === "object") {
						// Check if is DOM element
						if (element.nodeType) {
							element = $(element);
						}
	
						if (isQuery(element)) {
							obj = {
								href    : element.data('fancybox-href') || element.attr('href'),
								title   : $('<div/>').text( element.data('fancybox-title') || element.attr('title') || '' ).html(),
								isDom   : true,
								element : element
							};
	
							if ($.metadata) {
								$.extend(true, obj, element.metadata());
							}
	
						} else {
							obj = element;
						}
					}
	
					href  = opts.href  || obj.href || (isString(element) ? element : null);
					title = opts.title !== undefined ? opts.title : obj.title || '';
	
					content = opts.content || obj.content;
					type    = content ? 'html' : (opts.type  || obj.type);
	
					if (!type && obj.isDom) {
						type = element.data('fancybox-type');
	
						if (!type) {
							rez  = element.prop('class').match(/fancybox\.(\w+)/);
							type = rez ? rez[1] : null;
						}
					}
	
					if (isString(href)) {
						// Try to guess the content type
						if (!type) {
							if (F.isImage(href)) {
								type = 'image';
	
							} else if (F.isSWF(href)) {
								type = 'swf';
	
							} else if (href.charAt(0) === '#') {
								type = 'inline';
	
							} else if (isString(element)) {
								type    = 'html';
								content = element;
							}
						}
	
						// Split url into two pieces with source url and content selector, e.g,
						// "/mypage.html #my_id" will load "/mypage.html" and display element having id "my_id"
						if (type === 'ajax') {
							hrefParts = href.split(/\s+/, 2);
							href      = hrefParts.shift();
							selector  = hrefParts.shift();
						}
					}
	
					if (!content) {
						if (type === 'inline') {
							if (href) {
								content = $( isString(href) ? href.replace(/.*(?=#[^\s]+$)/, '') : href ); //strip for ie7
	
							} else if (obj.isDom) {
								content = element;
							}
	
						} else if (type === 'html') {
							content = href;
	
						} else if (!type && !href && obj.isDom) {
							type    = 'inline';
							content = element;
						}
					}
	
					$.extend(obj, {
						href     : href,
						type     : type,
						content  : content,
						title    : title,
						selector : selector
					});
	
					group[ i ] = obj;
				});
	
				// Extend the defaults
				F.opts = $.extend(true, {}, F.defaults, opts);
	
				// All options are merged recursive except keys
				if (opts.keys !== undefined) {
					F.opts.keys = opts.keys ? $.extend({}, F.defaults.keys, opts.keys) : false;
				}
	
				F.group = group;
	
				return F._start(F.opts.index);
			},
	
			// Cancel image loading or abort ajax request
			cancel: function () {
				var coming = F.coming;
	
				if (coming && false === F.trigger('onCancel')) {
					return;
				}
	
				F.hideLoading();
	
				if (!coming) {
					return;
				}
	
				if (F.ajaxLoad) {
					F.ajaxLoad.abort();
				}
	
				F.ajaxLoad = null;
	
				if (F.imgPreload) {
					F.imgPreload.onload = F.imgPreload.onerror = null;
				}
	
				if (coming.wrap) {
					coming.wrap.stop(true, true).trigger('onReset').remove();
				}
	
				F.coming = null;
	
				// If the first item has been canceled, then clear everything
				if (!F.current) {
					F._afterZoomOut( coming );
				}
			},
	
			// Start closing animation if is open; remove immediately if opening/closing
			close: function (event) {
				F.cancel();
	
				if (false === F.trigger('beforeClose')) {
					return;
				}
	
				F.unbindEvents();
	
				if (!F.isActive) {
					return;
				}
	
				if (!F.isOpen || event === true) {
					$('.fancybox-wrap').stop(true).trigger('onReset').remove();
	
					F._afterZoomOut();
	
				} else {
					F.isOpen = F.isOpened = false;
					F.isClosing = true;
	
					$('.fancybox-item, .fancybox-nav').remove();
	
					F.wrap.stop(true, true).removeClass('fancybox-opened');
	
					F.transitions[ F.current.closeMethod ]();
				}
			},
	
			// Manage slideshow:
			//   $.fancybox.play(); - toggle slideshow
			//   $.fancybox.play( true ); - start
			//   $.fancybox.play( false ); - stop
			play: function ( action ) {
				var clear = function () {
						clearTimeout(F.player.timer);
					},
					set = function () {
						clear();
	
						if (F.current && F.player.isActive) {
							F.player.timer = setTimeout(F.next, F.current.playSpeed);
						}
					},
					stop = function () {
						clear();
	
						D.unbind('.player');
	
						F.player.isActive = false;
	
						F.trigger('onPlayEnd');
					},
					start = function () {
						if (F.current && (F.current.loop || F.current.index < F.group.length - 1)) {
							F.player.isActive = true;
	
							D.bind({
								'onCancel.player beforeClose.player' : stop,
								'onUpdate.player'   : set,
								'beforeLoad.player' : clear
							});
	
							set();
	
							F.trigger('onPlayStart');
						}
					};
	
				if (action === true || (!F.player.isActive && action !== false)) {
					start();
				} else {
					stop();
				}
			},
	
			// Navigate to next gallery item
			next: function ( direction ) {
				var current = F.current;
	
				if (current) {
					if (!isString(direction)) {
						direction = current.direction.next;
					}
	
					F.jumpto(current.index + 1, direction, 'next');
				}
			},
	
			// Navigate to previous gallery item
			prev: function ( direction ) {
				var current = F.current;
	
				if (current) {
					if (!isString(direction)) {
						direction = current.direction.prev;
					}
	
					F.jumpto(current.index - 1, direction, 'prev');
				}
			},
	
			// Navigate to gallery item by index
			jumpto: function ( index, direction, router ) {
				var current = F.current;
	
				if (!current) {
					return;
				}
	
				index = getScalar(index);
	
				F.direction = direction || current.direction[ (index >= current.index ? 'next' : 'prev') ];
				F.router    = router || 'jumpto';
	
				if (current.loop) {
					if (index < 0) {
						index = current.group.length + (index % current.group.length);
					}
	
					index = index % current.group.length;
				}
	
				if (current.group[ index ] !== undefined) {
					F.cancel();
	
					F._start(index);
				}
			},
	
			// Center inside viewport and toggle position type to fixed or absolute if needed
			reposition: function (e, onlyAbsolute) {
				var current = F.current,
					wrap    = current ? current.wrap : null,
					pos;
	
				if (wrap) {
					pos = F._getPosition(onlyAbsolute);
	
					if (e && e.type === 'scroll') {
						delete pos.position;
	
						wrap.stop(true, true).animate(pos, 200);
	
					} else {
						wrap.css(pos);
	
						current.pos = $.extend({}, current.dim, pos);
					}
				}
			},
	
			update: function (e) {
				var type = (e && e.originalEvent && e.originalEvent.type),
					anyway = !type || type === 'orientationchange';
	
				if (anyway) {
					clearTimeout(didUpdate);
	
					didUpdate = null;
				}
	
				if (!F.isOpen || didUpdate) {
					return;
				}
	
				didUpdate = setTimeout(function() {
					var current = F.current;
	
					if (!current || F.isClosing) {
						return;
					}
	
					F.wrap.removeClass('fancybox-tmp');
	
					if (anyway || type === 'load' || (type === 'resize' && current.autoResize)) {
						F._setDimension();
					}
	
					if (!(type === 'scroll' && current.canShrink)) {
						F.reposition(e);
					}
	
					F.trigger('onUpdate');
	
					didUpdate = null;
	
				}, (anyway && !isTouch ? 0 : 300));
			},
	
			// Shrink content to fit inside viewport or restore if resized
			toggle: function ( action ) {
				if (F.isOpen) {
					F.current.fitToView = $.type(action) === "boolean" ? action : !F.current.fitToView;
	
					// Help browser to restore document dimensions
					if (isTouch) {
						F.wrap.removeAttr('style').addClass('fancybox-tmp');
	
						F.trigger('onUpdate');
					}
	
					F.update();
				}
			},
	
			hideLoading: function () {
				D.unbind('.loading');
	
				$('#fancybox-loading').remove();
			},
	
			showLoading: function () {
				var el, viewport;
	
				F.hideLoading();
	
				el = $(F.opts.tpl.loading).click(F.cancel).appendTo('body');
	
				// If user will press the escape-button, the request will be canceled
				D.bind('keydown.loading', function(e) {
					if ((e.which || e.keyCode) === 27) {
						e.preventDefault();
	
						F.cancel();
					}
				});
	
				if (!F.defaults.fixed) {
					viewport = F.getViewport();
	
					el.css({
						position : 'absolute',
						top  : (viewport.h * 0.5) + viewport.y,
						left : (viewport.w * 0.5) + viewport.x
					});
				}
	
				F.trigger('onLoading');
			},
	
			getViewport: function () {
				var locked = (F.current && F.current.locked) || false,
					rez    = {
						x: W.scrollLeft(),
						y: W.scrollTop()
					};
	
				if (locked && locked.length) {
					rez.w = locked[0].clientWidth;
					rez.h = locked[0].clientHeight;
	
				} else {
					// See http://bugs.jquery.com/ticket/6724
					rez.w = isTouch && window.innerWidth  ? window.innerWidth  : W.width();
					rez.h = isTouch && window.innerHeight ? window.innerHeight : W.height();
				}
	
				return rez;
			},
	
			// Unbind the keyboard / clicking actions
			unbindEvents: function () {
				if (F.wrap && isQuery(F.wrap)) {
					F.wrap.unbind('.fb');
				}
	
				D.unbind('.fb');
				W.unbind('.fb');
			},
	
			bindEvents: function () {
				var current = F.current,
					keys;
	
				if (!current) {
					return;
				}
	
				// Changing document height on iOS devices triggers a 'resize' event,
				// that can change document height... repeating infinitely
				W.bind('orientationchange.fb' + (isTouch ? '' : ' resize.fb') + (current.autoCenter && !current.locked ? ' scroll.fb' : ''), F.update);
	
				keys = current.keys;
	
				if (keys) {
					D.bind('keydown.fb', function (e) {
						var code   = e.which || e.keyCode,
							target = e.target || e.srcElement;
	
						// Skip esc key if loading, because showLoading will cancel preloading
						if (code === 27 && F.coming) {
							return false;
						}
	
						// Ignore key combinations and key events within form elements
						if (!e.ctrlKey && !e.altKey && !e.shiftKey && !e.metaKey && !(target && (target.type || $(target).is('[contenteditable]')))) {
							$.each(keys, function(i, val) {
								if (current.group.length > 1 && val[ code ] !== undefined) {
									F[ i ]( val[ code ] );
	
									e.preventDefault();
									return false;
								}
	
								if ($.inArray(code, val) > -1) {
									F[ i ] ();
	
									e.preventDefault();
									return false;
								}
							});
						}
					});
				}
	
				if ($.fn.mousewheel && current.mouseWheel) {
					F.wrap.bind('mousewheel.fb', function (e, delta, deltaX, deltaY) {
						var target = e.target || null,
							parent = $(target),
							canScroll = false;
	
						while (parent.length) {
							if (canScroll || parent.is('.fancybox-skin') || parent.is('.fancybox-wrap')) {
								break;
							}
	
							canScroll = isScrollable( parent[0] );
							parent    = $(parent).parent();
						}
	
						if (delta !== 0 && !canScroll) {
							if (F.group.length > 1 && !current.canShrink) {
								if (deltaY > 0 || deltaX > 0) {
									F.prev( deltaY > 0 ? 'down' : 'left' );
	
								} else if (deltaY < 0 || deltaX < 0) {
									F.next( deltaY < 0 ? 'up' : 'right' );
								}
	
								e.preventDefault();
							}
						}
					});
				}
			},
	
			trigger: function (event, o) {
				var ret, obj = o || F.coming || F.current;
	
				if (obj) {
					if ($.isFunction( obj[event] )) {
						ret = obj[event].apply(obj, Array.prototype.slice.call(arguments, 1));
					}
	
					if (ret === false) {
						return false;
					}
	
					if (obj.helpers) {
						$.each(obj.helpers, function (helper, opts) {
							if (opts && F.helpers[helper] && $.isFunction(F.helpers[helper][event])) {
								F.helpers[helper][event]($.extend(true, {}, F.helpers[helper].defaults, opts), obj);
							}
						});
					}
				}
	
				D.trigger(event);
			},
	
			isImage: function (str) {
				return isString(str) && str.match(/(^data:image\/.*,)|(\.(jp(e|g|eg)|gif|png|bmp|webp|svg)((\?|#).*)?$)/i);
			},
	
			isSWF: function (str) {
				return isString(str) && str.match(/\.(swf)((\?|#).*)?$/i);
			},
	
			_start: function (index) {
				var coming = {},
					obj,
					href,
					type,
					margin,
					padding;
	
				index = getScalar( index );
				obj   = F.group[ index ] || null;
	
				if (!obj) {
					return false;
				}
	
				coming = $.extend(true, {}, F.opts, obj);
	
				// Convert margin and padding properties to array - top, right, bottom, left
				margin  = coming.margin;
				padding = coming.padding;
	
				if ($.type(margin) === 'number') {
					coming.margin = [margin, margin, margin, margin];
				}
	
				if ($.type(padding) === 'number') {
					coming.padding = [padding, padding, padding, padding];
				}
	
				// 'modal' propery is just a shortcut
				if (coming.modal) {
					$.extend(true, coming, {
						closeBtn   : false,
						closeClick : false,
						nextClick  : false,
						arrows     : false,
						mouseWheel : false,
						keys       : null,
						helpers: {
							overlay : {
								closeClick : false
							}
						}
					});
				}
	
				// 'autoSize' property is a shortcut, too
				if (coming.autoSize) {
					coming.autoWidth = coming.autoHeight = true;
				}
	
				if (coming.width === 'auto') {
					coming.autoWidth = true;
				}
	
				if (coming.height === 'auto') {
					coming.autoHeight = true;
				}
	
				/*
				 * Add reference to the group, so it`s possible to access from callbacks, example:
				 * afterLoad : function() {
				 *     this.title = 'Image ' + (this.index + 1) + ' of ' + this.group.length + (this.title ? ' - ' + this.title : '');
				 * }
				 */
	
				coming.group  = F.group;
				coming.index  = index;
	
				// Give a chance for callback or helpers to update coming item (type, title, etc)
				F.coming = coming;
	
				if (false === F.trigger('beforeLoad')) {
					F.coming = null;
	
					return;
				}
	
				type = coming.type;
				href = coming.href;
	
				if (!type) {
					F.coming = null;
	
					//If we can not determine content type then drop silently or display next/prev item if looping through gallery
					if (F.current && F.router && F.router !== 'jumpto') {
						F.current.index = index;
	
						return F[ F.router ]( F.direction );
					}
	
					return false;
				}
	
				F.isActive = true;
	
				if (type === 'image' || type === 'swf') {
					coming.autoHeight = coming.autoWidth = false;
					coming.scrolling  = 'visible';
				}
	
				if (type === 'image') {
					coming.aspectRatio = true;
				}
	
				if (type === 'iframe' && isTouch) {
					coming.scrolling = 'scroll';
				}
	
				// Build the neccessary markup
				coming.wrap = $(coming.tpl.wrap).addClass('fancybox-' + (isTouch ? 'mobile' : 'desktop') + ' fancybox-type-' + type + ' fancybox-tmp ' + coming.wrapCSS).appendTo( coming.parent || 'body' );
	
				$.extend(coming, {
					skin  : $('.fancybox-skin',  coming.wrap),
					outer : $('.fancybox-outer', coming.wrap),
					inner : $('.fancybox-inner', coming.wrap)
				});
	
				$.each(["Top", "Right", "Bottom", "Left"], function(i, v) {
					coming.skin.css('padding' + v, getValue(coming.padding[ i ]));
				});
	
				F.trigger('onReady');
	
				// Check before try to load; 'inline' and 'html' types need content, others - href
				if (type === 'inline' || type === 'html') {
					if (!coming.content || !coming.content.length) {
						return F._error( 'content' );
					}
	
				} else if (!href) {
					return F._error( 'href' );
				}
	
				if (type === 'image') {
					F._loadImage();
	
				} else if (type === 'ajax') {
					F._loadAjax();
	
				} else if (type === 'iframe') {
					F._loadIframe();
	
				} else {
					F._afterLoad();
				}
			},
	
			_error: function ( type ) {
				$.extend(F.coming, {
					type       : 'html',
					autoWidth  : true,
					autoHeight : true,
					minWidth   : 0,
					minHeight  : 0,
					scrolling  : 'no',
					hasError   : type,
					content    : F.coming.tpl.error
				});
	
				F._afterLoad();
			},
	
			_loadImage: function () {
				// Reset preload image so it is later possible to check "complete" property
				var img = F.imgPreload = new Image();
	
				img.onload = function () {
					this.onload = this.onerror = null;
	
					F.coming.width  = this.width / F.opts.pixelRatio;
					F.coming.height = this.height / F.opts.pixelRatio;
	
					F._afterLoad();
				};
	
				img.onerror = function () {
					this.onload = this.onerror = null;
	
					F._error( 'image' );
				};
	
				img.src = F.coming.href;
	
				if (img.complete !== true) {
					F.showLoading();
				}
			},
	
			_loadAjax: function () {
				var coming = F.coming;
	
				F.showLoading();
	
				F.ajaxLoad = $.ajax($.extend({}, coming.ajax, {
					url: coming.href,
					error: function (jqXHR, textStatus) {
						if (F.coming && textStatus !== 'abort') {
							F._error( 'ajax', jqXHR );
	
						} else {
							F.hideLoading();
						}
					},
					success: function (data, textStatus) {
						if (textStatus === 'success') {
							coming.content = data;
	
							F._afterLoad();
						}
					}
				}));
			},
	
			_loadIframe: function() {
				var coming = F.coming,
					iframe = $(coming.tpl.iframe.replace(/\{rnd\}/g, new Date().getTime()))
						.attr('scrolling', isTouch ? 'auto' : coming.iframe.scrolling)
						.attr('src', coming.href);
	
				// This helps IE
				$(coming.wrap).bind('onReset', function () {
					try {
						$(this).find('iframe').hide().attr('src', '//about:blank').end().empty();
					} catch (e) {}
				});
	
				if (coming.iframe.preload) {
					F.showLoading();
	
					iframe.one('load', function() {
						$(this).data('ready', 1);
	
						// iOS will lose scrolling if we resize
						if (!isTouch) {
							$(this).bind('load.fb', F.update);
						}
	
						// Without this trick:
						//   - iframe won't scroll on iOS devices
						//   - IE7 sometimes displays empty iframe
						$(this).parents('.fancybox-wrap').width('100%').removeClass('fancybox-tmp').show();
	
						F._afterLoad();
					});
				}
	
				coming.content = iframe.appendTo( coming.inner );
	
				if (!coming.iframe.preload) {
					F._afterLoad();
				}
			},
	
			_preloadImages: function() {
				var group   = F.group,
					current = F.current,
					len     = group.length,
					cnt     = current.preload ? Math.min(current.preload, len - 1) : 0,
					item,
					i;
	
				for (i = 1; i <= cnt; i += 1) {
					item = group[ (current.index + i ) % len ];
	
					if (item.type === 'image' && item.href) {
						new Image().src = item.href;
					}
				}
			},
	
			_afterLoad: function () {
				var coming   = F.coming,
					previous = F.current,
					placeholder = 'fancybox-placeholder',
					current,
					content,
					type,
					scrolling,
					href,
					embed;
	
				F.hideLoading();
	
				if (!coming || F.isActive === false) {
					return;
				}
	
				if (false === F.trigger('afterLoad', coming, previous)) {
					coming.wrap.stop(true).trigger('onReset').remove();
	
					F.coming = null;
	
					return;
				}
	
				if (previous) {
					F.trigger('beforeChange', previous);
	
					previous.wrap.stop(true).removeClass('fancybox-opened')
						.find('.fancybox-item, .fancybox-nav')
						.remove();
				}
	
				F.unbindEvents();
	
				current   = coming;
				content   = coming.content;
				type      = coming.type;
				scrolling = coming.scrolling;
	
				$.extend(F, {
					wrap  : current.wrap,
					skin  : current.skin,
					outer : current.outer,
					inner : current.inner,
					current  : current,
					previous : previous
				});
	
				href = current.href;
	
				switch (type) {
					case 'inline':
					case 'ajax':
					case 'html':
						if (current.selector) {
							content = $('<div>').html(content).find(current.selector);
	
						} else if (isQuery(content)) {
							if (!content.data(placeholder)) {
								content.data(placeholder, $('<div class="' + placeholder + '"></div>').insertAfter( content ).hide() );
							}
	
							content = content.show().detach();
	
							current.wrap.bind('onReset', function () {
								if ($(this).find(content).length) {
									content.hide().replaceAll( content.data(placeholder) ).data(placeholder, false);
								}
							});
						}
					break;
	
					case 'image':
						content = current.tpl.image.replace(/\{href\}/g, href);
					break;
	
					case 'swf':
						content = '<object id="fancybox-swf" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="100%" height="100%"><param name="movie" value="' + href + '"></param>';
						embed   = '';
	
						$.each(current.swf, function(name, val) {
							content += '<param name="' + name + '" value="' + val + '"></param>';
							embed   += ' ' + name + '="' + val + '"';
						});
	
						content += '<embed src="' + href + '" type="application/x-shockwave-flash" width="100%" height="100%"' + embed + '></embed></object>';
					break;
				}
	
				if (!(isQuery(content) && content.parent().is(current.inner))) {
					current.inner.append( content );
				}
	
				// Give a chance for helpers or callbacks to update elements
				F.trigger('beforeShow');
	
				// Set scrolling before calculating dimensions
				current.inner.css('overflow', scrolling === 'yes' ? 'scroll' : (scrolling === 'no' ? 'hidden' : scrolling));
	
				// Set initial dimensions and start position
				F._setDimension();
	
				F.reposition();
	
				F.isOpen = false;
				F.coming = null;
	
				F.bindEvents();
	
				if (!F.isOpened) {
					$('.fancybox-wrap').not( current.wrap ).stop(true).trigger('onReset').remove();
	
				} else if (previous.prevMethod) {
					F.transitions[ previous.prevMethod ]();
				}
	
				F.transitions[ F.isOpened ? current.nextMethod : current.openMethod ]();
	
				F._preloadImages();
			},
	
			_setDimension: function () {
				var viewport   = F.getViewport(),
					steps      = 0,
					canShrink  = false,
					canExpand  = false,
					wrap       = F.wrap,
					skin       = F.skin,
					inner      = F.inner,
					current    = F.current,
					width      = current.width,
					height     = current.height,
					minWidth   = current.minWidth,
					minHeight  = current.minHeight,
					maxWidth   = current.maxWidth,
					maxHeight  = current.maxHeight,
					scrolling  = current.scrolling,
					scrollOut  = current.scrollOutside ? current.scrollbarWidth : 0,
					margin     = current.margin,
					wMargin    = getScalar(margin[1] + margin[3]),
					hMargin    = getScalar(margin[0] + margin[2]),
					wPadding,
					hPadding,
					wSpace,
					hSpace,
					origWidth,
					origHeight,
					origMaxWidth,
					origMaxHeight,
					ratio,
					width_,
					height_,
					maxWidth_,
					maxHeight_,
					iframe,
					body;
	
				// Reset dimensions so we could re-check actual size
				wrap.add(skin).add(inner).width('auto').height('auto').removeClass('fancybox-tmp');
	
				wPadding = getScalar(skin.outerWidth(true)  - skin.width());
				hPadding = getScalar(skin.outerHeight(true) - skin.height());
	
				// Any space between content and viewport (margin, padding, border, title)
				wSpace = wMargin + wPadding;
				hSpace = hMargin + hPadding;
	
				origWidth  = isPercentage(width)  ? (viewport.w - wSpace) * getScalar(width)  / 100 : width;
				origHeight = isPercentage(height) ? (viewport.h - hSpace) * getScalar(height) / 100 : height;
	
				if (current.type === 'iframe') {
					iframe = current.content;
	
					if (current.autoHeight && iframe && iframe.data('ready') === 1) {
						try {
							if (iframe[0].contentWindow.document.location) {
								inner.width( origWidth ).height(9999);
	
								body = iframe.contents().find('body');
	
								if (scrollOut) {
									body.css('overflow-x', 'hidden');
								}
	
								origHeight = body.outerHeight(true);
							}
	
						} catch (e) {}
					}
	
				} else if (current.autoWidth || current.autoHeight) {
					inner.addClass( 'fancybox-tmp' );
	
					// Set width or height in case we need to calculate only one dimension
					if (!current.autoWidth) {
						inner.width( origWidth );
					}
	
					if (!current.autoHeight) {
						inner.height( origHeight );
					}
	
					if (current.autoWidth) {
						origWidth = inner.width();
					}
	
					if (current.autoHeight) {
						origHeight = inner.height();
					}
	
					inner.removeClass( 'fancybox-tmp' );
				}
	
				width  = getScalar( origWidth );
				height = getScalar( origHeight );
	
				ratio  = origWidth / origHeight;
	
				// Calculations for the content
				minWidth  = getScalar(isPercentage(minWidth) ? getScalar(minWidth, 'w') - wSpace : minWidth);
				maxWidth  = getScalar(isPercentage(maxWidth) ? getScalar(maxWidth, 'w') - wSpace : maxWidth);
	
				minHeight = getScalar(isPercentage(minHeight) ? getScalar(minHeight, 'h') - hSpace : minHeight);
				maxHeight = getScalar(isPercentage(maxHeight) ? getScalar(maxHeight, 'h') - hSpace : maxHeight);
	
				// These will be used to determine if wrap can fit in the viewport
				origMaxWidth  = maxWidth;
				origMaxHeight = maxHeight;
	
				if (current.fitToView) {
					maxWidth  = Math.min(viewport.w - wSpace, maxWidth);
					maxHeight = Math.min(viewport.h - hSpace, maxHeight);
				}
	
				maxWidth_  = viewport.w - wMargin;
				maxHeight_ = viewport.h - hMargin;
	
				if (current.aspectRatio) {
					if (width > maxWidth) {
						width  = maxWidth;
						height = getScalar(width / ratio);
					}
	
					if (height > maxHeight) {
						height = maxHeight;
						width  = getScalar(height * ratio);
					}
	
					if (width < minWidth) {
						width  = minWidth;
						height = getScalar(width / ratio);
					}
	
					if (height < minHeight) {
						height = minHeight;
						width  = getScalar(height * ratio);
					}
	
				} else {
					width = Math.max(minWidth, Math.min(width, maxWidth));
	
					if (current.autoHeight && current.type !== 'iframe') {
						inner.width( width );
	
						height = inner.height();
					}
	
					height = Math.max(minHeight, Math.min(height, maxHeight));
				}
	
				// Try to fit inside viewport (including the title)
				if (current.fitToView) {
					inner.width( width ).height( height );
	
					wrap.width( width + wPadding );
	
					// Real wrap dimensions
					width_  = wrap.width();
					height_ = wrap.height();
	
					if (current.aspectRatio) {
						while ((width_ > maxWidth_ || height_ > maxHeight_) && width > minWidth && height > minHeight) {
							if (steps++ > 19) {
								break;
							}
	
							height = Math.max(minHeight, Math.min(maxHeight, height - 10));
							width  = getScalar(height * ratio);
	
							if (width < minWidth) {
								width  = minWidth;
								height = getScalar(width / ratio);
							}
	
							if (width > maxWidth) {
								width  = maxWidth;
								height = getScalar(width / ratio);
							}
	
							inner.width( width ).height( height );
	
							wrap.width( width + wPadding );
	
							width_  = wrap.width();
							height_ = wrap.height();
						}
	
					} else {
						width  = Math.max(minWidth,  Math.min(width,  width  - (width_  - maxWidth_)));
						height = Math.max(minHeight, Math.min(height, height - (height_ - maxHeight_)));
					}
				}
	
				if (scrollOut && scrolling === 'auto' && height < origHeight && (width + wPadding + scrollOut) < maxWidth_) {
					width += scrollOut;
				}
	
				inner.width( width ).height( height );
	
				wrap.width( width + wPadding );
	
				width_  = wrap.width();
				height_ = wrap.height();
	
				canShrink = (width_ > maxWidth_ || height_ > maxHeight_) && width > minWidth && height > minHeight;
				canExpand = current.aspectRatio ? (width < origMaxWidth && height < origMaxHeight && width < origWidth && height < origHeight) : ((width < origMaxWidth || height < origMaxHeight) && (width < origWidth || height < origHeight));
	
				$.extend(current, {
					dim : {
						width	: getValue( width_ ),
						height	: getValue( height_ )
					},
					origWidth  : origWidth,
					origHeight : origHeight,
					canShrink  : canShrink,
					canExpand  : canExpand,
					wPadding   : wPadding,
					hPadding   : hPadding,
					wrapSpace  : height_ - skin.outerHeight(true),
					skinSpace  : skin.height() - height
				});
	
				if (!iframe && current.autoHeight && height > minHeight && height < maxHeight && !canExpand) {
					inner.height('auto');
				}
			},
	
			_getPosition: function (onlyAbsolute) {
				var current  = F.current,
					viewport = F.getViewport(),
					margin   = current.margin,
					width    = F.wrap.width()  + margin[1] + margin[3],
					height   = F.wrap.height() + margin[0] + margin[2],
					rez      = {
						position: 'absolute',
						top  : margin[0],
						left : margin[3]
					};
	
				if (current.autoCenter && current.fixed && !onlyAbsolute && height <= viewport.h && width <= viewport.w) {
					rez.position = 'fixed';
	
				} else if (!current.locked) {
					rez.top  += viewport.y;
					rez.left += viewport.x;
				}
	
				rez.top  = getValue(Math.max(rez.top,  rez.top  + ((viewport.h - height) * current.topRatio)));
				rez.left = getValue(Math.max(rez.left, rez.left + ((viewport.w - width)  * current.leftRatio)));
	
				return rez;
			},
	
			_afterZoomIn: function () {
				var current = F.current;
	
				if (!current) {
					return;
				}
	
				F.isOpen = F.isOpened = true;
	
				F.wrap.css('overflow', 'visible').addClass('fancybox-opened').hide().show(0);
	
				F.update();
	
				// Assign a click event
				if ( current.closeClick || (current.nextClick && F.group.length > 1) ) {
					F.inner.css('cursor', 'pointer').bind('click.fb', function(e) {
						if (!$(e.target).is('a') && !$(e.target).parent().is('a')) {
							e.preventDefault();
	
							F[ current.closeClick ? 'close' : 'next' ]();
						}
					});
				}
	
				// Create a close button
				if (current.closeBtn) {
					$(current.tpl.closeBtn).appendTo(F.skin).bind('click.fb', function(e) {
						e.preventDefault();
	
						F.close();
					});
				}
	
				// Create navigation arrows
				if (current.arrows && F.group.length > 1) {
					if (current.loop || current.index > 0) {
						$(current.tpl.prev).appendTo(F.outer).bind('click.fb', F.prev);
					}
	
					if (current.loop || current.index < F.group.length - 1) {
						$(current.tpl.next).appendTo(F.outer).bind('click.fb', F.next);
					}
				}
	
				F.trigger('afterShow');
	
				// Stop the slideshow if this is the last item
				if (!current.loop && current.index === current.group.length - 1) {
	
					F.play( false );
	
				} else if (F.opts.autoPlay && !F.player.isActive) {
					F.opts.autoPlay = false;
	
					F.play(true);
				}
			},
	
			_afterZoomOut: function ( obj ) {
				obj = obj || F.current;
	
				$('.fancybox-wrap').trigger('onReset').remove();
	
				$.extend(F, {
					group  : {},
					opts   : {},
					router : false,
					current   : null,
					isActive  : false,
					isOpened  : false,
					isOpen    : false,
					isClosing : false,
					wrap   : null,
					skin   : null,
					outer  : null,
					inner  : null
				});
	
				F.trigger('afterClose', obj);
			}
		});
	
		/*
		 *	Default transitions
		 */
	
		F.transitions = {
			getOrigPosition: function () {
				var current  = F.current,
					element  = current.element,
					orig     = current.orig,
					pos      = {},
					width    = 50,
					height   = 50,
					hPadding = current.hPadding,
					wPadding = current.wPadding,
					viewport = F.getViewport();
	
				if (!orig && current.isDom && element.is(':visible')) {
					orig = element.find('img:first');
	
					if (!orig.length) {
						orig = element;
					}
				}
	
				if (isQuery(orig)) {
					pos = orig.offset();
	
					if (orig.is('img')) {
						width  = orig.outerWidth();
						height = orig.outerHeight();
					}
	
				} else {
					pos.top  = viewport.y + (viewport.h - height) * current.topRatio;
					pos.left = viewport.x + (viewport.w - width)  * current.leftRatio;
				}
	
				if (F.wrap.css('position') === 'fixed' || current.locked) {
					pos.top  -= viewport.y;
					pos.left -= viewport.x;
				}
	
				pos = {
					top     : getValue(pos.top  - hPadding * current.topRatio),
					left    : getValue(pos.left - wPadding * current.leftRatio),
					width   : getValue(width  + wPadding),
					height  : getValue(height + hPadding)
				};
	
				return pos;
			},
	
			step: function (now, fx) {
				var ratio,
					padding,
					value,
					prop       = fx.prop,
					current    = F.current,
					wrapSpace  = current.wrapSpace,
					skinSpace  = current.skinSpace;
	
				if (prop === 'width' || prop === 'height') {
					ratio = fx.end === fx.start ? 1 : (now - fx.start) / (fx.end - fx.start);
	
					if (F.isClosing) {
						ratio = 1 - ratio;
					}
	
					padding = prop === 'width' ? current.wPadding : current.hPadding;
					value   = now - padding;
	
					F.skin[ prop ](  getScalar( prop === 'width' ?  value : value - (wrapSpace * ratio) ) );
					F.inner[ prop ]( getScalar( prop === 'width' ?  value : value - (wrapSpace * ratio) - (skinSpace * ratio) ) );
				}
			},
	
			zoomIn: function () {
				var current  = F.current,
					startPos = current.pos,
					effect   = current.openEffect,
					elastic  = effect === 'elastic',
					endPos   = $.extend({opacity : 1}, startPos);
	
				// Remove "position" property that breaks older IE
				delete endPos.position;
	
				if (elastic) {
					startPos = this.getOrigPosition();
	
					if (current.openOpacity) {
						startPos.opacity = 0.1;
					}
	
				} else if (effect === 'fade') {
					startPos.opacity = 0.1;
				}
	
				F.wrap.css(startPos).animate(endPos, {
					duration : effect === 'none' ? 0 : current.openSpeed,
					easing   : current.openEasing,
					step     : elastic ? this.step : null,
					complete : F._afterZoomIn
				});
			},
	
			zoomOut: function () {
				var current  = F.current,
					effect   = current.closeEffect,
					elastic  = effect === 'elastic',
					endPos   = {opacity : 0.1};
	
				if (elastic) {
					endPos = this.getOrigPosition();
	
					if (current.closeOpacity) {
						endPos.opacity = 0.1;
					}
				}
	
				F.wrap.animate(endPos, {
					duration : effect === 'none' ? 0 : current.closeSpeed,
					easing   : current.closeEasing,
					step     : elastic ? this.step : null,
					complete : F._afterZoomOut
				});
			},
	
			changeIn: function () {
				var current   = F.current,
					effect    = current.nextEffect,
					startPos  = current.pos,
					endPos    = { opacity : 1 },
					direction = F.direction,
					distance  = 200,
					field;
	
				startPos.opacity = 0.1;
	
				if (effect === 'elastic') {
					field = direction === 'down' || direction === 'up' ? 'top' : 'left';
	
					if (direction === 'down' || direction === 'right') {
						startPos[ field ] = getValue(getScalar(startPos[ field ]) - distance);
						endPos[ field ]   = '+=' + distance + 'px';
	
					} else {
						startPos[ field ] = getValue(getScalar(startPos[ field ]) + distance);
						endPos[ field ]   = '-=' + distance + 'px';
					}
				}
	
				// Workaround for http://bugs.jquery.com/ticket/12273
				if (effect === 'none') {
					F._afterZoomIn();
	
				} else {
					F.wrap.css(startPos).animate(endPos, {
						duration : current.nextSpeed,
						easing   : current.nextEasing,
						complete : F._afterZoomIn
					});
				}
			},
	
			changeOut: function () {
				var previous  = F.previous,
					effect    = previous.prevEffect,
					endPos    = { opacity : 0.1 },
					direction = F.direction,
					distance  = 200;
	
				if (effect === 'elastic') {
					endPos[ direction === 'down' || direction === 'up' ? 'top' : 'left' ] = ( direction === 'up' || direction === 'left' ? '-' : '+' ) + '=' + distance + 'px';
				}
	
				previous.wrap.animate(endPos, {
					duration : effect === 'none' ? 0 : previous.prevSpeed,
					easing   : previous.prevEasing,
					complete : function () {
						$(this).trigger('onReset').remove();
					}
				});
			}
		};
	
		/*
		 *	Overlay helper
		 */
	
		F.helpers.overlay = {
			defaults : {
				closeClick : true,      // if true, fancyBox will be closed when user clicks on the overlay
				speedOut   : 200,       // duration of fadeOut animation
				showEarly  : true,      // indicates if should be opened immediately or wait until the content is ready
				css        : {},        // custom CSS properties
				locked     : !isTouch,  // if true, the content will be locked into overlay
				fixed      : true       // if false, the overlay CSS position property will not be set to "fixed"
			},
	
			overlay : null,      // current handle
			fixed   : false,     // indicates if the overlay has position "fixed"
			el      : $('html'), // element that contains "the lock"
	
			// Public methods
			create : function(opts) {
				var parent;
	
				opts = $.extend({}, this.defaults, opts);
	
				if (this.overlay) {
					this.close();
				}
	
				parent = F.coming ? F.coming.parent : opts.parent;
	
				this.overlay = $('<div class="fancybox-overlay"></div>').appendTo( parent && parent.length ? parent : 'body' );
				this.fixed   = false;
	
				if (opts.fixed && F.defaults.fixed) {
					this.overlay.addClass('fancybox-overlay-fixed');
	
					this.fixed = true;
				}
			},
	
			open : function(opts) {
				var that = this;
	
				opts = $.extend({}, this.defaults, opts);
	
				if (this.overlay) {
					this.overlay.unbind('.overlay').width('auto').height('auto');
	
				} else {
					this.create(opts);
				}
	
				if (!this.fixed) {
					W.bind('resize.overlay', $.proxy( this.update, this) );
	
					this.update();
				}
	
				if (opts.closeClick) {
					this.overlay.bind('click.overlay', function(e) {
						if ($(e.target).hasClass('fancybox-overlay')) {
							if (F.isActive) {
								F.close();
							} else {
								that.close();
							}
	
							return false;
						}
					});
				}
	
				this.overlay.css( opts.css ).show();
			},
	
			close : function() {
				W.unbind('resize.overlay');
	
				if (this.el.hasClass('fancybox-lock')) {
					$('.fancybox-margin').removeClass('fancybox-margin');
	
					this.el.removeClass('fancybox-lock');
	
					W.scrollTop( this.scrollV ).scrollLeft( this.scrollH );
				}
	
				$('.fancybox-overlay').remove().hide();
	
				$.extend(this, {
					overlay : null,
					fixed   : false
				});
			},
	
			// Private, callbacks
	
			update : function () {
				var width = '100%', offsetWidth;
	
				// Reset width/height so it will not mess
				this.overlay.width(width).height('100%');
	
				// jQuery does not return reliable result for IE
				if (IE) {
					offsetWidth = Math.max(document.documentElement.offsetWidth, document.body.offsetWidth);
	
					if (D.width() > offsetWidth) {
						width = D.width();
					}
	
				} else if (D.width() > W.width()) {
					width = D.width();
				}
	
				this.overlay.width(width).height(D.height());
			},
	
			// This is where we can manipulate DOM, because later it would cause iframes to reload
			onReady : function (opts, obj) {
				var overlay = this.overlay;
	
				$('.fancybox-overlay').stop(true, true);
	
				if (!overlay) {
					this.create(opts);
				}
	
				if (opts.locked && this.fixed && obj.fixed) {
					obj.locked = this.overlay.append( obj.wrap );
					obj.fixed  = false;
				}
	
				if (opts.showEarly === true) {
					this.beforeShow.apply(this, arguments);
				}
			},
	
			beforeShow : function(opts, obj) {
				if (obj.locked && !this.el.hasClass('fancybox-lock')) {
					if (this.fixPosition !== false) {
						$('*:not(object)').filter(function(){
							return ($(this).css('position') === 'fixed' && !$(this).hasClass("fancybox-overlay") && !$(this).hasClass("fancybox-wrap") );
						}).addClass('fancybox-margin');
					}
	
					this.el.addClass('fancybox-margin');
	
					this.scrollV = W.scrollTop();
					this.scrollH = W.scrollLeft();
	
					this.el.addClass('fancybox-lock');
	
					W.scrollTop( this.scrollV ).scrollLeft( this.scrollH );
				}
	
				this.open(opts);
			},
	
			onUpdate : function() {
				if (!this.fixed) {
					this.update();
				}
			},
	
			afterClose: function (opts) {
				// Remove overlay if exists and fancyBox is not opening
				// (e.g., it is not being open using afterClose callback)
				if (this.overlay && !F.coming) {
					this.overlay.fadeOut(opts.speedOut, $.proxy( this.close, this ));
				}
			}
		};
	
		/*
		 *	Title helper
		 */
	
		F.helpers.title = {
			defaults : {
				type     : 'float', // 'float', 'inside', 'outside' or 'over',
				position : 'bottom' // 'top' or 'bottom'
			},
	
			beforeShow: function (opts) {
				var current = F.current,
					text    = current.title,
					type    = opts.type,
					title,
					target;
	
				if ($.isFunction(text)) {
					text = text.call(current.element, current);
				}
	
				if (!isString(text) || $.trim(text) === '') {
					return;
				}
	
				title = $('<div class="fancybox-title fancybox-title-' + type + '-wrap">' + text + '</div>');
	
				switch (type) {
					case 'inside':
						target = F.skin;
					break;
	
					case 'outside':
						target = F.wrap;
					break;
	
					case 'over':
						target = F.inner;
					break;
	
					default: // 'float'
						target = F.skin;
	
						title.appendTo('body');
	
						if (IE) {
							title.width( title.width() );
						}
	
						title.wrapInner('<span class="child"></span>');
	
						//Increase bottom margin so this title will also fit into viewport
						F.current.margin[2] += Math.abs( getScalar(title.css('margin-bottom')) );
					break;
				}
	
				title[ (opts.position === 'top' ? 'prependTo'  : 'appendTo') ](target);
			}
		};
	
		// jQuery plugin initialization
		$.fn.fancybox = function (options) {
			var index,
				that     = $(this),
				selector = this.selector || '',
				run      = function(e) {
					var what = $(this).blur(), idx = index, relType, relVal;
	
					if (!(e.ctrlKey || e.altKey || e.shiftKey || e.metaKey) && !what.is('.fancybox-wrap')) {
						relType = options.groupAttr || 'data-fancybox-group';
						relVal  = what.attr(relType);
	
						if (!relVal) {
							relType = 'rel';
							relVal  = what.get(0)[ relType ];
						}
	
						if (relVal && relVal !== '' && relVal !== 'nofollow') {
							what = selector.length ? $(selector) : that;
							what = what.filter('[' + relType + '="' + relVal + '"]');
							idx  = what.index(this);
						}
	
						options.index = idx;
	
						// Stop an event from bubbling if everything is fine
						if (F.open(what, options) !== false) {
							e.preventDefault();
						}
					}
				};
	
			options = options || {};
			index   = options.index || 0;
	
			if (!selector || options.live === false) {
				that.unbind('click.fb-start').bind('click.fb-start', run);
	
			} else {
				D.undelegate(selector, 'click.fb-start').delegate(selector + ":not('.fancybox-item, .fancybox-nav')", 'click.fb-start', run);
			}
	
			this.filter('[data-fancybox-start=1]').trigger('click');
	
			return this;
		};
	
		// Tests that need a body at doc ready
		D.ready(function() {
			var w1, w2;
	
			if ( $.scrollbarWidth === undefined ) {
				// http://benalman.com/projects/jquery-misc-plugins/#scrollbarwidth
				$.scrollbarWidth = function() {
					var parent = $('<div style="width:50px;height:50px;overflow:auto"><div/></div>').appendTo('body'),
						child  = parent.children(),
						width  = child.innerWidth() - child.height( 99 ).innerWidth();
	
					parent.remove();
	
					return width;
				};
			}
	
			if ( $.support.fixedPosition === undefined ) {
				$.support.fixedPosition = (function() {
					var elem  = $('<div style="position:fixed;top:20px;"></div>').appendTo('body'),
						fixed = ( elem[0].offsetTop === 20 || elem[0].offsetTop === 15 );
	
					elem.remove();
	
					return fixed;
				}());
			}
	
			$.extend(F.defaults, {
				scrollbarWidth : $.scrollbarWidth(),
				fixed  : $.support.fixedPosition,
				parent : $('body')
			});
	
			//Get real width of page scroll-bar
			w1 = $(window).width();
	
			H.addClass('fancybox-lock-test');
	
			w2 = $(window).width();
	
			H.removeClass('fancybox-lock-test');
	
			$("<style type='text/css'>.fancybox-margin{margin-right:" + (w2 - w1) + "px;}</style>").appendTo("head");
		});
	
	}(window, document, jQuery));


/***/ }),
/* 33 */
/***/ (function(module, exports) {

	 /*!
	 * Thumbnail helper for fancyBox
	 * version: 1.0.7 (Mon, 01 Oct 2012)
	 * @requires fancyBox v2.0 or later
	 *
	 * Usage:
	 *     $(".fancybox").fancybox({
	 *         helpers : {
	 *             thumbs: {
	 *                 width  : 50,
	 *                 height : 50
	 *             }
	 *         }
	 *     });
	 *
	 */
	;(function ($) {
		//Shortcut for fancyBox object
		var F = $.fancybox;
	
		//Add helper object
		F.helpers.thumbs = {
			defaults : {
				width    : 50,       // thumbnail width
				height   : 50,       // thumbnail height
				position : 'bottom', // 'top' or 'bottom'
				source   : function ( item ) {  // function to obtain the URL of the thumbnail image
					var href;
	
					if (item.element) {
						href = $(item.element).find('img').attr('src');
					}
	
					if (!href && item.type === 'image' && item.href) {
						href = item.href;
					}
	
					return href;
				}
			},
	
			wrap  : null,
			list  : null,
			width : 0,
	
			init: function (opts, obj) {
				var that = this,
					list,
					thumbWidth  = opts.width,
					thumbHeight = opts.height,
					thumbSource = opts.source;
	
				//Build list structure
				list = '';
	
				for (var n = 0; n < obj.group.length; n++) {
					list += '<li><a style="width:' + thumbWidth + 'px;height:' + thumbHeight + 'px;" href="javascript:jQuery.fancybox.jumpto(' + n + ');"></a></li>';
				}
	
				this.wrap = $('<div id="fancybox-thumbs"></div>').addClass(opts.position).appendTo('body');
				this.list = $('<ul>' + list + '</ul>').appendTo(this.wrap);
	
				//Load each thumbnail
				$.each(obj.group, function (i) {
					var el   = obj.group[ i ],
						href = thumbSource( el );
	
					if (!href) {
						return;
					}
	
					$("<img />").on("load", function () {
						var width  = this.width,
							height = this.height,
							widthRatio, heightRatio, parent;
	
						if (!that.list || !width || !height) {
							return;
						}
	
						//Calculate thumbnail width/height and center it
						widthRatio  = width / thumbWidth;
						heightRatio = height / thumbHeight;
	
						parent = that.list.children().eq(i).find('a');
	
						if (widthRatio >= 1 && heightRatio >= 1) {
							if (widthRatio > heightRatio) {
								width  = Math.floor(width / heightRatio);
								height = thumbHeight;
	
							} else {
								width  = thumbWidth;
								height = Math.floor(height / widthRatio);
							}
						}
	
						$(this).css({
							width  : width,
							height : height,
							top    : Math.floor(thumbHeight / 2 - height / 2),
							left   : Math.floor(thumbWidth / 2 - width / 2)
						});
	
						parent.width(thumbWidth).height(thumbHeight);
	
						$(this).hide().appendTo(parent).fadeIn(300);
	
					})
					.attr('src',   href)
					.attr('title', el.title);
				});
	
				//Set initial width
				this.width = this.list.children().eq(0).outerWidth(true);
	
				this.list.width(this.width * (obj.group.length + 1)).css('left', Math.floor($(window).width() * 0.5 - (obj.index * this.width + this.width * 0.5)));
			},
	
			beforeLoad: function (opts, obj) {
				//Remove self if gallery do not have at least two items
				if (obj.group.length < 2) {
					obj.helpers.thumbs = false;
	
					return;
				}
	
				//Increase bottom margin to give space for thumbs
				obj.margin[ opts.position === 'top' ? 0 : 2 ] += ((opts.height) + 15);
			},
	
			afterShow: function (opts, obj) {
				//Check if exists and create or update list
				if (this.list) {
					this.onUpdate(opts, obj);
	
				} else {
					this.init(opts, obj);
				}
	
				//Set active element
				this.list.children().removeClass('active').eq(obj.index).addClass('active');
			},
	
			//Center list
			onUpdate: function (opts, obj) {
				if (this.list) {
					this.list.stop(true).animate({
						'left': Math.floor($(window).width() * 0.5 - (obj.index * this.width + this.width * 0.5))
					}, 150);
				}
			},
	
			beforeClose: function () {
				if (this.wrap) {
					this.wrap.remove();
				}
	
				this.wrap  = null;
				this.list  = null;
				this.width = 0;
			}
		}
	
	}(jQuery));


/***/ }),
/* 34 */
/***/ (function(module, exports, __webpack_require__) {

	var __WEBPACK_AMD_DEFINE_FACTORY__, __WEBPACK_AMD_DEFINE_ARRAY__, __WEBPACK_AMD_DEFINE_RESULT__;/*!
	 * @fileOverview TouchSwipe - jQuery Plugin
	 * @version 1.6.18
	 *
	 * @author Matt Bryson http://www.github.com/mattbryson
	 * @see https://github.com/mattbryson/TouchSwipe-Jquery-Plugin
	 * @see http://labs.rampinteractive.co.uk/touchSwipe/
	 * @see http://plugins.jquery.com/project/touchSwipe
	 * @license
	 * Copyright (c) 2010-2015 Matt Bryson
	 * Dual licensed under the MIT or GPL Version 2 licenses.
	 *
	 */
	
	/*
	 *
	 * Changelog
	 * $Date: 2010-12-12 (Wed, 12 Dec 2010) $
	 * $version: 1.0.0
	 * $version: 1.0.1 - removed multibyte comments
	 *
	 * $Date: 2011-21-02 (Mon, 21 Feb 2011) $
	 * $version: 1.1.0 	- added allowPageScroll property to allow swiping and scrolling of page
	 *					- changed handler signatures so one handler can be used for multiple events
	 * $Date: 2011-23-02 (Wed, 23 Feb 2011) $
	 * $version: 1.2.0 	- added click handler. This is fired if the user simply clicks and does not swipe. The event object and click target are passed to handler.
	 *					- If you use the http://code.google.com/p/jquery-ui-for-ipad-and-iphone/ plugin, you can also assign jQuery mouse events to children of a touchSwipe object.
	 * $version: 1.2.1 	- removed console log!
	 *
	 * $version: 1.2.2 	- Fixed bug where scope was not preserved in callback methods.
	 *
	 * $Date: 2011-28-04 (Thurs, 28 April 2011) $
	 * $version: 1.2.4 	- Changed licence terms to be MIT or GPL inline with jQuery. Added check for support of touch events to stop non compatible browsers erroring.
	 *
	 * $Date: 2011-27-09 (Tues, 27 September 2011) $
	 * $version: 1.2.5 	- Added support for testing swipes with mouse on desktop browser (thanks to https://github.com/joelhy)
	 *
	 * $Date: 2012-14-05 (Mon, 14 May 2012) $
	 * $version: 1.2.6 	- Added timeThreshold between start and end touch, so user can ignore slow swipes (thanks to Mark Chase). Default is null, all swipes are detected
	 *
	 * $Date: 2012-05-06 (Tues, 05 June 2012) $
	 * $version: 1.2.7 	- Changed time threshold to have null default for backwards compatibility. Added duration param passed back in events, and refactored how time is handled.
	 *
	 * $Date: 2012-05-06 (Tues, 05 June 2012) $
	 * $version: 1.2.8 	- Added the possibility to return a value like null or false in the trigger callback. In that way we can control when the touch start/move should take effect or not (simply by returning in some cases return null; or return false;) This effects the ontouchstart/ontouchmove event.
	 *
	 * $Date: 2012-06-06 (Wed, 06 June 2012) $
	 * $version: 1.3.0 	- Refactored whole plugin to allow for methods to be executed, as well as exposed defaults for user override. Added 'enable', 'disable', and 'destroy' methods
	 *
	 * $Date: 2012-05-06 (Fri, 05 June 2012) $
	 * $version: 1.3.1 	- Bug fixes  - bind() with false as last argument is no longer supported in jQuery 1.6, also, if you just click, the duration is now returned correctly.
	 *
	 * $Date: 2012-29-07 (Sun, 29 July 2012) $
	 * $version: 1.3.2	- Added fallbackToMouseEvents option to NOT capture mouse events on non touch devices.
	 * 			- Added "all" fingers value to the fingers property, so any combination of fingers triggers the swipe, allowing event handlers to check the finger count
	 *
	 * $Date: 2012-09-08 (Thurs, 9 Aug 2012) $
	 * $version: 1.3.3	- Code tidy prep for minefied version
	 *
	 * $Date: 2012-04-10 (wed, 4 Oct 2012) $
	 * $version: 1.4.0	- Added pinch support, pinchIn and pinchOut
	 *
	 * $Date: 2012-11-10 (Thurs, 11 Oct 2012) $
	 * $version: 1.5.0	- Added excludedElements, a jquery selector that specifies child elements that do NOT trigger swipes. By default, this is .noSwipe
	 *
	 * $Date: 2012-22-10 (Mon, 22 Oct 2012) $
	 * $version: 1.5.1	- Fixed bug with jQuery 1.8 and trailing comma in excludedElements
	 *					- Fixed bug with IE and eventPreventDefault()
	 * $Date: 2013-01-12 (Fri, 12 Jan 2013) $
	 * $version: 1.6.0	- Fixed bugs with pinching, mainly when both pinch and swipe enabled, as well as adding time threshold for multifinger gestures, so releasing one finger beofre the other doesnt trigger as single finger gesture.
	 *					- made the demo site all static local HTML pages so they can be run locally by a developer
	 *					- added jsDoc comments and added documentation for the plugin
	 *					- code tidy
	 *					- added triggerOnTouchLeave property that will end the event when the user swipes off the element.
	 * $Date: 2013-03-23 (Sat, 23 Mar 2013) $
	 * $version: 1.6.1	- Added support for ie8 touch events
	 * $version: 1.6.2	- Added support for events binding with on / off / bind in jQ for all callback names.
	 *                   - Deprecated the 'click' handler in favour of tap.
	 *                   - added cancelThreshold property
	 *                   - added option method to update init options at runtime
	 * $version 1.6.3    - added doubletap, longtap events and longTapThreshold, doubleTapThreshold property
	 *
	 * $Date: 2013-04-04 (Thurs, 04 April 2013) $
	 * $version 1.6.4    - Fixed bug with cancelThreshold introduced in 1.6.3, where swipe status no longer fired start event, and stopped once swiping back.
	 *
	 * $Date: 2013-08-24 (Sat, 24 Aug 2013) $
	 * $version 1.6.5    - Merged a few pull requests fixing various bugs, added AMD support.
	 *
	 * $Date: 2014-06-04 (Wed, 04 June 2014) $
	 * $version 1.6.6 	- Merge of pull requests.
	 *    				- IE10 touch support
	 *    				- Only prevent default event handling on valid swipe
	 *    				- Separate license/changelog comment
	 *    				- Detect if the swipe is valid at the end of the touch event.
	 *    				- Pass fingerdata to event handlers.
	 *    				- Add 'hold' gesture
	 *    				- Be more tolerant about the tap distance
	 *    				- Typos and minor fixes
	 *
	 * $Date: 2015-22-01 (Thurs, 22 Jan 2015) $
	 * $version 1.6.7    - Added patch from https://github.com/mattbryson/TouchSwipe-Jquery-Plugin/issues/206 to fix memory leak
	 *
	 * $Date: 2015-2-2 (Mon, 2 Feb 2015) $
	 * $version 1.6.8    - Added preventDefaultEvents option to proxy events regardless.
	 *					- Fixed issue with swipe and pinch not triggering at the same time
	 *
	 * $Date: 2015-9-6 (Tues, 9 June 2015) $
	 * $version 1.6.9    - Added PR from jdalton/hybrid to fix pointer events
	 *					- Added scrolling demo
	 *					- Added version property to plugin
	 *
	 * $Date: 2015-1-10 (Wed, 1 October 2015) $
	 * $version 1.6.10    - Added PR from beatspace to fix tap events
	 * $version 1.6.11    - Added PRs from indri-indri ( Doc tidyup), kkirsche ( Bower tidy up ), UziTech (preventDefaultEvents fixes )
	 *					 - Allowed setting multiple options via .swipe("options", options_hash) and more simply .swipe(options_hash) or exisitng instances
	 * $version 1.6.12    - Fixed bug with multi finger releases above 2 not triggering events
	 *
	 * $Date: 2015-12-18 (Fri, 18 December 2015) $
	 * $version 1.6.13    - Added PRs
	 *                    - Fixed #267 allowPageScroll not working correctly
	 * $version 1.6.14    - Fixed #220 / #248 doubletap not firing with swipes, #223 commonJS compatible
	 * $version 1.6.15    - More bug fixes
	 *
	 * $Date: 2016-04-29 (Fri, 29 April 2016) $
	 * $version 1.6.16    - Swipes with 0 distance now allow default events to trigger.  So tapping any form elements or A tags will allow default interaction, but swiping will trigger a swipe.
	                        Removed the a, input, select etc from the excluded Children list as the 0 distance tap solves that issue.
	* $Date: 2016-05-19  (Fri, 29 April 2016) $
	* $version 1.6.17     - Fixed context issue when calling instance methods via $("selector").swipe("method");
	* $version 1.6.18     - now honors fallbackToMouseEvents=false for MS Pointer events when a Mouse is used.
	
	 */
	
	/**
	 * See (http://jquery.com/).
	 * @name $
	 * @class
	 * See the jQuery Library  (http://jquery.com/) for full details.  This just
	 * documents the function and classes that are added to jQuery by this plug-in.
	 */
	
	/**
	 * See (http://jquery.com/)
	 * @name fn
	 * @class
	 * See the jQuery Library  (http://jquery.com/) for full details.  This just
	 * documents the function and classes that are added to jQuery by this plug-in.
	 * @memberOf $
	 */
	
	
	(function(factory) {
	  if ("function" === 'function' && __webpack_require__(35) && __webpack_require__(35).jQuery) {
	    // AMD. Register as anonymous module.
	    !(__WEBPACK_AMD_DEFINE_ARRAY__ = [__webpack_require__(2)], __WEBPACK_AMD_DEFINE_FACTORY__ = (factory), __WEBPACK_AMD_DEFINE_RESULT__ = (typeof __WEBPACK_AMD_DEFINE_FACTORY__ === 'function' ? (__WEBPACK_AMD_DEFINE_FACTORY__.apply(exports, __WEBPACK_AMD_DEFINE_ARRAY__)) : __WEBPACK_AMD_DEFINE_FACTORY__), __WEBPACK_AMD_DEFINE_RESULT__ !== undefined && (module.exports = __WEBPACK_AMD_DEFINE_RESULT__));
	  } else if (typeof module !== 'undefined' && module.exports) {
	    // CommonJS Module
	    factory(__webpack_require__(2));
	  } else {
	    // Browser globals.
	    factory(jQuery);
	  }
	}(function($) {
	  "use strict";
	
	  //Constants
	  var VERSION = "1.6.18",
	    LEFT = "left",
	    RIGHT = "right",
	    UP = "up",
	    DOWN = "down",
	    IN = "in",
	    OUT = "out",
	
	    NONE = "none",
	    AUTO = "auto",
	
	    SWIPE = "swipe",
	    PINCH = "pinch",
	    TAP = "tap",
	    DOUBLE_TAP = "doubletap",
	    LONG_TAP = "longtap",
	    HOLD = "hold",
	
	    HORIZONTAL = "horizontal",
	    VERTICAL = "vertical",
	
	    ALL_FINGERS = "all",
	
	    DOUBLE_TAP_THRESHOLD = 10,
	
	    PHASE_START = "start",
	    PHASE_MOVE = "move",
	    PHASE_END = "end",
	    PHASE_CANCEL = "cancel",
	
	    SUPPORTS_TOUCH = 'ontouchstart' in window,
	
	    SUPPORTS_POINTER_IE10 = window.navigator.msPointerEnabled && !window.navigator.pointerEnabled && !SUPPORTS_TOUCH,
	
	    SUPPORTS_POINTER = (window.navigator.pointerEnabled || window.navigator.msPointerEnabled) && !SUPPORTS_TOUCH,
	
	    PLUGIN_NS = 'TouchSwipe';
	
	
	
	  /**
	  * The default configuration, and available options to configure touch swipe with.
	  * You can set the default values by updating any of the properties prior to instantiation.
	  * @name $.fn.swipe.defaults
	  * @namespace
	  * @property {int} [fingers=1] The number of fingers to detect in a swipe. Any swipes that do not meet this requirement will NOT trigger swipe handlers.
	  * @property {int} [threshold=75] The number of pixels that the user must move their finger by before it is considered a swipe.
	  * @property {int} [cancelThreshold=null] The number of pixels that the user must move their finger back from the original swipe direction to cancel the gesture.
	  * @property {int} [pinchThreshold=20] The number of pixels that the user must pinch their finger by before it is considered a pinch.
	  * @property {int} [maxTimeThreshold=null] Time, in milliseconds, between touchStart and touchEnd must NOT exceed in order to be considered a swipe.
	  * @property {int} [fingerReleaseThreshold=250] Time in milliseconds between releasing multiple fingers.  If 2 fingers are down, and are released one after the other, if they are within this threshold, it counts as a simultaneous release.
	  * @property {int} [longTapThreshold=500] Time in milliseconds between tap and release for a long tap
	  * @property {int} [doubleTapThreshold=200] Time in milliseconds between 2 taps to count as a double tap
	  * @property {function} [swipe=null] A handler to catch all swipes. See {@link $.fn.swipe#event:swipe}
	  * @property {function} [swipeLeft=null] A handler that is triggered for "left" swipes. See {@link $.fn.swipe#event:swipeLeft}
	  * @property {function} [swipeRight=null] A handler that is triggered for "right" swipes. See {@link $.fn.swipe#event:swipeRight}
	  * @property {function} [swipeUp=null] A handler that is triggered for "up" swipes. See {@link $.fn.swipe#event:swipeUp}
	  * @property {function} [swipeDown=null] A handler that is triggered for "down" swipes. See {@link $.fn.swipe#event:swipeDown}
	  * @property {function} [swipeStatus=null] A handler triggered for every phase of the swipe. See {@link $.fn.swipe#event:swipeStatus}
	  * @property {function} [pinchIn=null] A handler triggered for pinch in events. See {@link $.fn.swipe#event:pinchIn}
	  * @property {function} [pinchOut=null] A handler triggered for pinch out events. See {@link $.fn.swipe#event:pinchOut}
	  * @property {function} [pinchStatus=null] A handler triggered for every phase of a pinch. See {@link $.fn.swipe#event:pinchStatus}
	  * @property {function} [tap=null] A handler triggered when a user just taps on the item, rather than swipes it. If they do not move, tap is triggered, if they do move, it is not.
	  * @property {function} [doubleTap=null] A handler triggered when a user double taps on the item. The delay between taps can be set with the doubleTapThreshold property. See {@link $.fn.swipe.defaults#doubleTapThreshold}
	  * @property {function} [longTap=null] A handler triggered when a user long taps on the item. The delay between start and end can be set with the longTapThreshold property. See {@link $.fn.swipe.defaults#longTapThreshold}
	  * @property (function) [hold=null] A handler triggered when a user reaches longTapThreshold on the item. See {@link $.fn.swipe.defaults#longTapThreshold}
	  * @property {boolean} [triggerOnTouchEnd=true] If true, the swipe events are triggered when the touch end event is received (user releases finger).  If false, it will be triggered on reaching the threshold, and then cancel the touch event automatically.
	  * @property {boolean} [triggerOnTouchLeave=false] If true, then when the user leaves the swipe object, the swipe will end and trigger appropriate handlers.
	  * @property {string|undefined} [allowPageScroll='auto'] How the browser handles page scrolls when the user is swiping on a touchSwipe object. See {@link $.fn.swipe.pageScroll}.  <br/><br/>
	  									<code>"auto"</code> : all undefined swipes will cause the page to scroll in that direction. <br/>
	  									<code>"none"</code> : the page will not scroll when user swipes. <br/>
	  									<code>"horizontal"</code> : will force page to scroll on horizontal swipes. <br/>
	  									<code>"vertical"</code> : will force page to scroll on vertical swipes. <br/>
	  * @property {boolean} [fallbackToMouseEvents=true] If true mouse events are used when run on a non touch device, false will stop swipes being triggered by mouse events on non tocuh devices.
	  * @property {string} [excludedElements=".noSwipe"] A jquery selector that specifies child elements that do NOT trigger swipes. By default this excludes elements with the class .noSwipe .
	  * @property {boolean} [preventDefaultEvents=true] by default default events are cancelled, so the page doesn't move.  You can dissable this so both native events fire as well as your handlers.
	
	  */
	  var defaults = {
	    fingers: 1,
	    threshold: 75,
	    cancelThreshold: null,
	    pinchThreshold: 20,
	    maxTimeThreshold: null,
	    fingerReleaseThreshold: 250,
	    longTapThreshold: 500,
	    doubleTapThreshold: 200,
	    swipe: null,
	    swipeLeft: null,
	    swipeRight: null,
	    swipeUp: null,
	    swipeDown: null,
	    swipeStatus: null,
	    pinchIn: null,
	    pinchOut: null,
	    pinchStatus: null,
	    click: null, //Deprecated since 1.6.2
	    tap: null,
	    doubleTap: null,
	    longTap: null,
	    hold: null,
	    triggerOnTouchEnd: true,
	    triggerOnTouchLeave: false,
	    allowPageScroll: "auto",
	    fallbackToMouseEvents: true,
	    excludedElements: ".noSwipe",
	    preventDefaultEvents: true
	  };
	
	
	
	  /**
	   * Applies TouchSwipe behaviour to one or more jQuery objects.
	   * The TouchSwipe plugin can be instantiated via this method, or methods within
	   * TouchSwipe can be executed via this method as per jQuery plugin architecture.
	   * An existing plugin can have its options changed simply by re calling .swipe(options)
	   * @see TouchSwipe
	   * @class
	   * @param {Mixed} method If the current DOMNode is a TouchSwipe object, and <code>method</code> is a TouchSwipe method, then
	   * the <code>method</code> is executed, and any following arguments are passed to the TouchSwipe method.
	   * If <code>method</code> is an object, then the TouchSwipe class is instantiated on the current DOMNode, passing the
	   * configuration properties defined in the object. See TouchSwipe
	   *
	   */
	  $.fn.swipe = function(method) {
	    var $this = $(this),
	      plugin = $this.data(PLUGIN_NS);
	
	    //Check if we are already instantiated and trying to execute a method
	    if (plugin && typeof method === 'string') {
	      if (plugin[method]) {
	        return plugin[method].apply(plugin, Array.prototype.slice.call(arguments, 1));
	      } else {
	        $.error('Method ' + method + ' does not exist on jQuery.swipe');
	      }
	    }
	
	    //Else update existing plugin with new options hash
	    else if (plugin && typeof method === 'object') {
	      plugin['option'].apply(plugin, arguments);
	    }
	
	    //Else not instantiated and trying to pass init object (or nothing)
	    else if (!plugin && (typeof method === 'object' || !method)) {
	      return init.apply(this, arguments);
	    }
	
	    return $this;
	  };
	
	  /**
	   * The version of the plugin
	   * @readonly
	   */
	  $.fn.swipe.version = VERSION;
	
	
	
	  //Expose our defaults so a user could override the plugin defaults
	  $.fn.swipe.defaults = defaults;
	
	  /**
	   * The phases that a touch event goes through.  The <code>phase</code> is passed to the event handlers.
	   * These properties are read only, attempting to change them will not alter the values passed to the event handlers.
	   * @namespace
	   * @readonly
	   * @property {string} PHASE_START Constant indicating the start phase of the touch event. Value is <code>"start"</code>.
	   * @property {string} PHASE_MOVE Constant indicating the move phase of the touch event. Value is <code>"move"</code>.
	   * @property {string} PHASE_END Constant indicating the end phase of the touch event. Value is <code>"end"</code>.
	   * @property {string} PHASE_CANCEL Constant indicating the cancel phase of the touch event. Value is <code>"cancel"</code>.
	   */
	  $.fn.swipe.phases = {
	    PHASE_START: PHASE_START,
	    PHASE_MOVE: PHASE_MOVE,
	    PHASE_END: PHASE_END,
	    PHASE_CANCEL: PHASE_CANCEL
	  };
	
	  /**
	   * The direction constants that are passed to the event handlers.
	   * These properties are read only, attempting to change them will not alter the values passed to the event handlers.
	   * @namespace
	   * @readonly
	   * @property {string} LEFT Constant indicating the left direction. Value is <code>"left"</code>.
	   * @property {string} RIGHT Constant indicating the right direction. Value is <code>"right"</code>.
	   * @property {string} UP Constant indicating the up direction. Value is <code>"up"</code>.
	   * @property {string} DOWN Constant indicating the down direction. Value is <code>"cancel"</code>.
	   * @property {string} IN Constant indicating the in direction. Value is <code>"in"</code>.
	   * @property {string} OUT Constant indicating the out direction. Value is <code>"out"</code>.
	   */
	  $.fn.swipe.directions = {
	    LEFT: LEFT,
	    RIGHT: RIGHT,
	    UP: UP,
	    DOWN: DOWN,
	    IN: IN,
	    OUT: OUT
	  };
	
	  /**
	   * The page scroll constants that can be used to set the value of <code>allowPageScroll</code> option
	   * These properties are read only
	   * @namespace
	   * @readonly
	   * @see $.fn.swipe.defaults#allowPageScroll
	   * @property {string} NONE Constant indicating no page scrolling is allowed. Value is <code>"none"</code>.
	   * @property {string} HORIZONTAL Constant indicating horizontal page scrolling is allowed. Value is <code>"horizontal"</code>.
	   * @property {string} VERTICAL Constant indicating vertical page scrolling is allowed. Value is <code>"vertical"</code>.
	   * @property {string} AUTO Constant indicating either horizontal or vertical will be allowed, depending on the swipe handlers registered. Value is <code>"auto"</code>.
	   */
	  $.fn.swipe.pageScroll = {
	    NONE: NONE,
	    HORIZONTAL: HORIZONTAL,
	    VERTICAL: VERTICAL,
	    AUTO: AUTO
	  };
	
	  /**
	   * Constants representing the number of fingers used in a swipe.  These are used to set both the value of <code>fingers</code> in the
	   * options object, as well as the value of the <code>fingers</code> event property.
	   * These properties are read only, attempting to change them will not alter the values passed to the event handlers.
	   * @namespace
	   * @readonly
	   * @see $.fn.swipe.defaults#fingers
	   * @property {string} ONE Constant indicating 1 finger is to be detected / was detected. Value is <code>1</code>.
	   * @property {string} TWO Constant indicating 2 fingers are to be detected / were detected. Value is <code>2</code>.
	   * @property {string} THREE Constant indicating 3 finger are to be detected / were detected. Value is <code>3</code>.
	   * @property {string} FOUR Constant indicating 4 finger are to be detected / were detected. Not all devices support this. Value is <code>4</code>.
	   * @property {string} FIVE Constant indicating 5 finger are to be detected / were detected. Not all devices support this. Value is <code>5</code>.
	   * @property {string} ALL Constant indicating any combination of finger are to be detected.  Value is <code>"all"</code>.
	   */
	  $.fn.swipe.fingers = {
	    ONE: 1,
	    TWO: 2,
	    THREE: 3,
	    FOUR: 4,
	    FIVE: 5,
	    ALL: ALL_FINGERS
	  };
	
	  /**
	   * Initialise the plugin for each DOM element matched
	   * This creates a new instance of the main TouchSwipe class for each DOM element, and then
	   * saves a reference to that instance in the elements data property.
	   * @internal
	   */
	  function init(options) {
	    //Prep and extend the options
	    if (options && (options.allowPageScroll === undefined && (options.swipe !== undefined || options.swipeStatus !== undefined))) {
	      options.allowPageScroll = NONE;
	    }
	
	    //Check for deprecated options
	    //Ensure that any old click handlers are assigned to the new tap, unless we have a tap
	    if (options.click !== undefined && options.tap === undefined) {
	      options.tap = options.click;
	    }
	
	    if (!options) {
	      options = {};
	    }
	
	    //pass empty object so we dont modify the defaults
	    options = $.extend({}, $.fn.swipe.defaults, options);
	
	    //For each element instantiate the plugin
	    return this.each(function() {
	      var $this = $(this);
	
	      //Check we havent already initialised the plugin
	      var plugin = $this.data(PLUGIN_NS);
	
	      if (!plugin) {
	        plugin = new TouchSwipe(this, options);
	        $this.data(PLUGIN_NS, plugin);
	      }
	    });
	  }
	
	  /**
	   * Main TouchSwipe Plugin Class.
	   * Do not use this to construct your TouchSwipe object, use the jQuery plugin method $.fn.swipe(); {@link $.fn.swipe}
	   * @private
	   * @name TouchSwipe
	   * @param {DOMNode} element The HTML DOM object to apply to plugin to
	   * @param {Object} options The options to configure the plugin with.  @link {$.fn.swipe.defaults}
	   * @see $.fh.swipe.defaults
	   * @see $.fh.swipe
	   * @class
	   */
	  function TouchSwipe(element, options) {
	
	    //take a local/instacne level copy of the options - should make it this.options really...
	    var options = $.extend({}, options);
	
	    var useTouchEvents = (SUPPORTS_TOUCH || SUPPORTS_POINTER || !options.fallbackToMouseEvents),
	      START_EV = useTouchEvents ? (SUPPORTS_POINTER ? (SUPPORTS_POINTER_IE10 ? 'MSPointerDown' : 'pointerdown') : 'touchstart') : 'mousedown',
	      MOVE_EV = useTouchEvents ? (SUPPORTS_POINTER ? (SUPPORTS_POINTER_IE10 ? 'MSPointerMove' : 'pointermove') : 'touchmove') : 'mousemove',
	      END_EV = useTouchEvents ? (SUPPORTS_POINTER ? (SUPPORTS_POINTER_IE10 ? 'MSPointerUp' : 'pointerup') : 'touchend') : 'mouseup',
	      LEAVE_EV = useTouchEvents ? (SUPPORTS_POINTER ? 'mouseleave' : null) : 'mouseleave', //we manually detect leave on touch devices, so null event here
	      CANCEL_EV = (SUPPORTS_POINTER ? (SUPPORTS_POINTER_IE10 ? 'MSPointerCancel' : 'pointercancel') : 'touchcancel');
	
	
	
	    //touch properties
	    var distance = 0,
	      direction = null,
	      currentDirection = null,
	      duration = 0,
	      startTouchesDistance = 0,
	      endTouchesDistance = 0,
	      pinchZoom = 1,
	      pinchDistance = 0,
	      pinchDirection = 0,
	      maximumsMap = null;
	
	
	
	    //jQuery wrapped element for this instance
	    var $element = $(element);
	
	    //Current phase of th touch cycle
	    var phase = "start";
	
	    // the current number of fingers being used.
	    var fingerCount = 0;
	
	    //track mouse points / delta
	    var fingerData = {};
	
	    //track times
	    var startTime = 0,
	      endTime = 0,
	      previousTouchEndTime = 0,
	      fingerCountAtRelease = 0,
	      doubleTapStartTime = 0;
	
	    //Timeouts
	    var singleTapTimeout = null,
	      holdTimeout = null;
	
	    // Add gestures to all swipable areas if supported
	    try {
	      $element.bind(START_EV, touchStart);
	      $element.bind(CANCEL_EV, touchCancel);
	    } catch (e) {
	      $.error('events not supported ' + START_EV + ',' + CANCEL_EV + ' on jQuery.swipe');
	    }
	
	    //
	    //Public methods
	    //
	
	    /**
	     * re-enables the swipe plugin with the previous configuration
	     * @function
	     * @name $.fn.swipe#enable
	     * @return {DOMNode} The Dom element that was registered with TouchSwipe
	     * @example $("#element").swipe("enable");
	     */
	    this.enable = function() {
	      //Incase we are already enabled, clean up...
	      this.disable();
	      $element.bind(START_EV, touchStart);
	      $element.bind(CANCEL_EV, touchCancel);
	      return $element;
	    };
	
	    /**
	     * disables the swipe plugin
	     * @function
	     * @name $.fn.swipe#disable
	     * @return {DOMNode} The Dom element that is now registered with TouchSwipe
	     * @example $("#element").swipe("disable");
	     */
	    this.disable = function() {
	      removeListeners();
	      return $element;
	    };
	
	    /**
	     * Destroy the swipe plugin completely. To use any swipe methods, you must re initialise the plugin.
	     * @function
	     * @name $.fn.swipe#destroy
	     * @example $("#element").swipe("destroy");
	     */
	    this.destroy = function() {
	      removeListeners();
	      $element.data(PLUGIN_NS, null);
	      $element = null;
	    };
	
	
	    /**
	     * Allows run time updating of the swipe configuration options.
	     * @function
	     * @name $.fn.swipe#option
	     * @param {String} property The option property to get or set, or a has of multiple options to set
	     * @param {Object} [value] The value to set the property to
	     * @return {Object} If only a property name is passed, then that property value is returned. If nothing is passed the current options hash is returned.
	     * @example $("#element").swipe("option", "threshold"); // return the threshold
	     * @example $("#element").swipe("option", "threshold", 100); // set the threshold after init
	     * @example $("#element").swipe("option", {threshold:100, fingers:3} ); // set multiple properties after init
	     * @example $("#element").swipe({threshold:100, fingers:3} ); // set multiple properties after init - the "option" method is optional!
	     * @example $("#element").swipe("option"); // Return the current options hash
	     * @see $.fn.swipe.defaults
	     *
	     */
	    this.option = function(property, value) {
	
	      if (typeof property === 'object') {
	        options = $.extend(options, property);
	      } else if (options[property] !== undefined) {
	        if (value === undefined) {
	          return options[property];
	        } else {
	          options[property] = value;
	        }
	      } else if (!property) {
	        return options;
	      } else {
	        $.error('Option ' + property + ' does not exist on jQuery.swipe.options');
	      }
	
	      return null;
	    }
	
	
	
	    //
	    // Private methods
	    //
	
	    //
	    // EVENTS
	    //
	    /**
	     * Event handler for a touch start event.
	     * Stops the default click event from triggering and stores where we touched
	     * @inner
	     * @param {object} jqEvent The normalised jQuery event object.
	     */
	    function touchStart(jqEvent) {
	
	      //If we already in a touch event (a finger already in use) then ignore subsequent ones..
	      if (getTouchInProgress()) {
	        return;
	      }
	
	      //Check if this element matches any in the excluded elements selectors,  or its parent is excluded, if so, DON'T swipe
	      if ($(jqEvent.target).closest(options.excludedElements, $element).length > 0) {
	        return;
	      }
	
	      //As we use Jquery bind for events, we need to target the original event object
	      //If these events are being programmatically triggered, we don't have an original event object, so use the Jq one.
	      var event = jqEvent.originalEvent ? jqEvent.originalEvent : jqEvent;
	
	
	      //If we have a pointer event, whoes type is 'mouse' and we have said NO mouse events, then dont do anything.
	      if(event.pointerType && event.pointerType=="mouse" && options.fallbackToMouseEvents==false) {
	        return;
	      };
	
	      var ret,
	        touches = event.touches,
	        evt = touches ? touches[0] : event;
	
	      phase = PHASE_START;
	
	      //If we support touches, get the finger count
	      if (touches) {
	        // get the total number of fingers touching the screen
	        fingerCount = touches.length;
	      }
	      //Else this is the desktop, so stop the browser from dragging content
	      else if (options.preventDefaultEvents !== false) {
	        jqEvent.preventDefault(); //call this on jq event so we are cross browser
	      }
	
	      //clear vars..
	      distance = 0;
	      direction = null;
	      currentDirection=null;
	      pinchDirection = null;
	      duration = 0;
	      startTouchesDistance = 0;
	      endTouchesDistance = 0;
	      pinchZoom = 1;
	      pinchDistance = 0;
	      maximumsMap = createMaximumsData();
	      cancelMultiFingerRelease();
	
	      //Create the default finger data
	      createFingerData(0, evt);
	
	      // check the number of fingers is what we are looking for, or we are capturing pinches
	      if (!touches || (fingerCount === options.fingers || options.fingers === ALL_FINGERS) || hasPinches()) {
	        // get the coordinates of the touch
	        startTime = getTimeStamp();
	
	        if (fingerCount == 2) {
	          //Keep track of the initial pinch distance, so we can calculate the diff later
	          //Store second finger data as start
	          createFingerData(1, touches[1]);
	          startTouchesDistance = endTouchesDistance = calculateTouchesDistance(fingerData[0].start, fingerData[1].start);
	        }
	
	        if (options.swipeStatus || options.pinchStatus) {
	          ret = triggerHandler(event, phase);
	        }
	      } else {
	        //A touch with more or less than the fingers we are looking for, so cancel
	        ret = false;
	      }
	
	      //If we have a return value from the users handler, then return and cancel
	      if (ret === false) {
	        phase = PHASE_CANCEL;
	        triggerHandler(event, phase);
	        return ret;
	      } else {
	        if (options.hold) {
	          holdTimeout = setTimeout($.proxy(function() {
	            //Trigger the event
	            $element.trigger('hold', [event.target]);
	            //Fire the callback
	            if (options.hold) {
	              ret = options.hold.call($element, event, event.target);
	            }
	          }, this), options.longTapThreshold);
	        }
	
	        setTouchInProgress(true);
	      }
	
	      return null;
	    };
	
	
	
	    /**
	     * Event handler for a touch move event.
	     * If we change fingers during move, then cancel the event
	     * @inner
	     * @param {object} jqEvent The normalised jQuery event object.
	     */
	    function touchMove(jqEvent) {
	
	      //As we use Jquery bind for events, we need to target the original event object
	      //If these events are being programmatically triggered, we don't have an original event object, so use the Jq one.
	      var event = jqEvent.originalEvent ? jqEvent.originalEvent : jqEvent;
	
	      //If we are ending, cancelling, or within the threshold of 2 fingers being released, don't track anything..
	      if (phase === PHASE_END || phase === PHASE_CANCEL || inMultiFingerRelease())
	        return;
	
	      var ret,
	        touches = event.touches,
	        evt = touches ? touches[0] : event;
	
	
	      //Update the  finger data
	      var currentFinger = updateFingerData(evt);
	      endTime = getTimeStamp();
	
	      if (touches) {
	        fingerCount = touches.length;
	      }
	
	      if (options.hold) {
	        clearTimeout(holdTimeout);
	      }
	
	      phase = PHASE_MOVE;
	
	      //If we have 2 fingers get Touches distance as well
	      if (fingerCount == 2) {
	
	        //Keep track of the initial pinch distance, so we can calculate the diff later
	        //We do this here as well as the start event, in case they start with 1 finger, and the press 2 fingers
	        if (startTouchesDistance == 0) {
	          //Create second finger if this is the first time...
	          createFingerData(1, touches[1]);
	
	          startTouchesDistance = endTouchesDistance = calculateTouchesDistance(fingerData[0].start, fingerData[1].start);
	        } else {
	          //Else just update the second finger
	          updateFingerData(touches[1]);
	
	          endTouchesDistance = calculateTouchesDistance(fingerData[0].end, fingerData[1].end);
	          pinchDirection = calculatePinchDirection(fingerData[0].end, fingerData[1].end);
	        }
	
	        pinchZoom = calculatePinchZoom(startTouchesDistance, endTouchesDistance);
	        pinchDistance = Math.abs(startTouchesDistance - endTouchesDistance);
	      }
	
	      if ((fingerCount === options.fingers || options.fingers === ALL_FINGERS) || !touches || hasPinches()) {
	
	        //The overall direction of the swipe. From start to now.
	        direction = calculateDirection(currentFinger.start, currentFinger.end);
	
	        //The immediate direction of the swipe, direction between the last movement and this one.
	        currentDirection = calculateDirection(currentFinger.last, currentFinger.end);
	
	        //Check if we need to prevent default event (page scroll / pinch zoom) or not
	        validateDefaultEvent(jqEvent, currentDirection);
	
	        //Distance and duration are all off the main finger
	        distance = calculateDistance(currentFinger.start, currentFinger.end);
	        duration = calculateDuration();
	
	        //Cache the maximum distance we made in this direction
	        setMaxDistance(direction, distance);
	
	        //Trigger status handler
	        ret = triggerHandler(event, phase);
	
	
	        //If we trigger end events when threshold are met, or trigger events when touch leaves element
	        if (!options.triggerOnTouchEnd || options.triggerOnTouchLeave) {
	
	          var inBounds = true;
	
	          //If checking if we leave the element, run the bounds check (we can use touchleave as its not supported on webkit)
	          if (options.triggerOnTouchLeave) {
	            var bounds = getbounds(this);
	            inBounds = isInBounds(currentFinger.end, bounds);
	          }
	
	          //Trigger end handles as we swipe if thresholds met or if we have left the element if the user has asked to check these..
	          if (!options.triggerOnTouchEnd && inBounds) {
	            phase = getNextPhase(PHASE_MOVE);
	          }
	          //We end if out of bounds here, so set current phase to END, and check if its modified
	          else if (options.triggerOnTouchLeave && !inBounds) {
	            phase = getNextPhase(PHASE_END);
	          }
	
	          if (phase == PHASE_CANCEL || phase == PHASE_END) {
	            triggerHandler(event, phase);
	          }
	        }
	      } else {
	        phase = PHASE_CANCEL;
	        triggerHandler(event, phase);
	      }
	
	      if (ret === false) {
	        phase = PHASE_CANCEL;
	        triggerHandler(event, phase);
	      }
	    }
	
	
	
	
	    /**
	     * Event handler for a touch end event.
	     * Calculate the direction and trigger events
	     * @inner
	     * @param {object} jqEvent The normalised jQuery event object.
	     */
	    function touchEnd(jqEvent) {
	      //As we use Jquery bind for events, we need to target the original event object
	      //If these events are being programmatically triggered, we don't have an original event object, so use the Jq one.
	      var event = jqEvent.originalEvent ? jqEvent.originalEvent : jqEvent,
	        touches = event.touches;
	
	      //If we are still in a touch with the device wait a fraction and see if the other finger comes up
	      //if it does within the threshold, then we treat it as a multi release, not a single release and end the touch / swipe
	      if (touches) {
	        if (touches.length && !inMultiFingerRelease()) {
	          startMultiFingerRelease(event);
	          return true;
	        } else if (touches.length && inMultiFingerRelease()) {
	          return true;
	        }
	      }
	
	      //If a previous finger has been released, check how long ago, if within the threshold, then assume it was a multifinger release.
	      //This is used to allow 2 fingers to release fractionally after each other, whilst maintaining the event as containing 2 fingers, not 1
	      if (inMultiFingerRelease()) {
	        fingerCount = fingerCountAtRelease;
	      }
	
	      //Set end of swipe
	      endTime = getTimeStamp();
	
	      //Get duration incase move was never fired
	      duration = calculateDuration();
	
	      //If we trigger handlers at end of swipe OR, we trigger during, but they didnt trigger and we are still in the move phase
	      if (didSwipeBackToCancel() || !validateSwipeDistance()) {
	        phase = PHASE_CANCEL;
	        triggerHandler(event, phase);
	      } else if (options.triggerOnTouchEnd || (options.triggerOnTouchEnd === false && phase === PHASE_MOVE)) {
	        //call this on jq event so we are cross browser
	        if (options.preventDefaultEvents !== false) {
	          jqEvent.preventDefault();
	        }
	        phase = PHASE_END;
	        triggerHandler(event, phase);
	      }
	      //Special cases - A tap should always fire on touch end regardless,
	      //So here we manually trigger the tap end handler by itself
	      //We dont run trigger handler as it will re-trigger events that may have fired already
	      else if (!options.triggerOnTouchEnd && hasTap()) {
	        //Trigger the pinch events...
	        phase = PHASE_END;
	        triggerHandlerForGesture(event, phase, TAP);
	      } else if (phase === PHASE_MOVE) {
	        phase = PHASE_CANCEL;
	        triggerHandler(event, phase);
	      }
	
	      setTouchInProgress(false);
	
	      return null;
	    }
	
	
	
	    /**
	     * Event handler for a touch cancel event.
	     * Clears current vars
	     * @inner
	     */
	    function touchCancel() {
	      // reset the variables back to default values
	      fingerCount = 0;
	      endTime = 0;
	      startTime = 0;
	      startTouchesDistance = 0;
	      endTouchesDistance = 0;
	      pinchZoom = 1;
	
	      //If we were in progress of tracking a possible multi touch end, then re set it.
	      cancelMultiFingerRelease();
	
	      setTouchInProgress(false);
	    }
	
	
	    /**
	     * Event handler for a touch leave event.
	     * This is only triggered on desktops, in touch we work this out manually
	     * as the touchleave event is not supported in webkit
	     * @inner
	     */
	    function touchLeave(jqEvent) {
	      //If these events are being programmatically triggered, we don't have an original event object, so use the Jq one.
	      var event = jqEvent.originalEvent ? jqEvent.originalEvent : jqEvent;
	
	      //If we have the trigger on leave property set....
	      if (options.triggerOnTouchLeave) {
	        phase = getNextPhase(PHASE_END);
	        triggerHandler(event, phase);
	      }
	    }
	
	    /**
	     * Removes all listeners that were associated with the plugin
	     * @inner
	     */
	    function removeListeners() {
	      $element.unbind(START_EV, touchStart);
	      $element.unbind(CANCEL_EV, touchCancel);
	      $element.unbind(MOVE_EV, touchMove);
	      $element.unbind(END_EV, touchEnd);
	
	      //we only have leave events on desktop, we manually calculate leave on touch as its not supported in webkit
	      if (LEAVE_EV) {
	        $element.unbind(LEAVE_EV, touchLeave);
	      }
	
	      setTouchInProgress(false);
	    }
	
	
	    /**
	     * Checks if the time and distance thresholds have been met, and if so then the appropriate handlers are fired.
	     */
	    function getNextPhase(currentPhase) {
	
	      var nextPhase = currentPhase;
	
	      // Ensure we have valid swipe (under time and over distance  and check if we are out of bound...)
	      var validTime = validateSwipeTime();
	      var validDistance = validateSwipeDistance();
	      var didCancel = didSwipeBackToCancel();
	
	      //If we have exceeded our time, then cancel
	      if (!validTime || didCancel) {
	        nextPhase = PHASE_CANCEL;
	      }
	      //Else if we are moving, and have reached distance then end
	      else if (validDistance && currentPhase == PHASE_MOVE && (!options.triggerOnTouchEnd || options.triggerOnTouchLeave)) {
	        nextPhase = PHASE_END;
	      }
	      //Else if we have ended by leaving and didn't reach distance, then cancel
	      else if (!validDistance && currentPhase == PHASE_END && options.triggerOnTouchLeave) {
	        nextPhase = PHASE_CANCEL;
	      }
	
	      return nextPhase;
	    }
	
	
	    /**
	     * Trigger the relevant event handler
	     * The handlers are passed the original event, the element that was swiped, and in the case of the catch all handler, the direction that was swiped, "left", "right", "up", or "down"
	     * @param {object} event the original event object
	     * @param {string} phase the phase of the swipe (start, end cancel etc) {@link $.fn.swipe.phases}
	     * @inner
	     */
	    function triggerHandler(event, phase) {
	
	
	
	      var ret,
	        touches = event.touches;
	
	      // SWIPE GESTURES
	      if (didSwipe() || hasSwipes()) {
	          ret = triggerHandlerForGesture(event, phase, SWIPE);
	      }
	
	      // PINCH GESTURES (if the above didn't cancel)
	      if ((didPinch() || hasPinches()) && ret !== false) {
	          ret = triggerHandlerForGesture(event, phase, PINCH);
	      }
	
	      // CLICK / TAP (if the above didn't cancel)
	      if (didDoubleTap() && ret !== false) {
	        //Trigger the tap events...
	        ret = triggerHandlerForGesture(event, phase, DOUBLE_TAP);
	      }
	
	      // CLICK / TAP (if the above didn't cancel)
	      else if (didLongTap() && ret !== false) {
	        //Trigger the tap events...
	        ret = triggerHandlerForGesture(event, phase, LONG_TAP);
	      }
	
	      // CLICK / TAP (if the above didn't cancel)
	      else if (didTap() && ret !== false) {
	        //Trigger the tap event..
	        ret = triggerHandlerForGesture(event, phase, TAP);
	      }
	
	
	
	      // If we are cancelling the gesture, then manually trigger the reset handler
	      if (phase === PHASE_CANCEL) {
	
	        touchCancel(event);
	      }
	
	
	
	
	      // If we are ending the gesture, then manually trigger the reset handler IF all fingers are off
	      if (phase === PHASE_END) {
	        //If we support touch, then check that all fingers are off before we cancel
	        if (touches) {
	          if (!touches.length) {
	            touchCancel(event);
	          }
	        } else {
	          touchCancel(event);
	        }
	      }
	
	      return ret;
	    }
	
	
	
	    /**
	     * Trigger the relevant event handler
	     * The handlers are passed the original event, the element that was swiped, and in the case of the catch all handler, the direction that was swiped, "left", "right", "up", or "down"
	     * @param {object} event the original event object
	     * @param {string} phase the phase of the swipe (start, end cancel etc) {@link $.fn.swipe.phases}
	     * @param {string} gesture the gesture to trigger a handler for : PINCH or SWIPE {@link $.fn.swipe.gestures}
	     * @return Boolean False, to indicate that the event should stop propagation, or void.
	     * @inner
	     */
	    function triggerHandlerForGesture(event, phase, gesture) {
	
	      var ret;
	
	      //SWIPES....
	      if (gesture == SWIPE) {
	        //Trigger status every time..
	        $element.trigger('swipeStatus', [phase, direction || null, distance || 0, duration || 0, fingerCount, fingerData, currentDirection]);
	
	        if (options.swipeStatus) {
	          ret = options.swipeStatus.call($element, event, phase, direction || null, distance || 0, duration || 0, fingerCount, fingerData, currentDirection);
	          //If the status cancels, then dont run the subsequent event handlers..
	          if (ret === false) return false;
	        }
	
	        if (phase == PHASE_END && validateSwipe()) {
	
	          //Cancel any taps that were in progress...
	          clearTimeout(singleTapTimeout);
	          clearTimeout(holdTimeout);
	
	          $element.trigger('swipe', [direction, distance, duration, fingerCount, fingerData, currentDirection]);
	
	          if (options.swipe) {
	            ret = options.swipe.call($element, event, direction, distance, duration, fingerCount, fingerData, currentDirection);
	            //If the status cancels, then dont run the subsequent event handlers..
	            if (ret === false) return false;
	          }
	
	          //trigger direction specific event handlers
	          switch (direction) {
	            case LEFT:
	              $element.trigger('swipeLeft', [direction, distance, duration, fingerCount, fingerData, currentDirection]);
	
	              if (options.swipeLeft) {
	                ret = options.swipeLeft.call($element, event, direction, distance, duration, fingerCount, fingerData, currentDirection);
	              }
	              break;
	
	            case RIGHT:
	              $element.trigger('swipeRight', [direction, distance, duration, fingerCount, fingerData, currentDirection]);
	
	              if (options.swipeRight) {
	                ret = options.swipeRight.call($element, event, direction, distance, duration, fingerCount, fingerData, currentDirection);
	              }
	              break;
	
	            case UP:
	              $element.trigger('swipeUp', [direction, distance, duration, fingerCount, fingerData, currentDirection]);
	
	              if (options.swipeUp) {
	                ret = options.swipeUp.call($element, event, direction, distance, duration, fingerCount, fingerData, currentDirection);
	              }
	              break;
	
	            case DOWN:
	              $element.trigger('swipeDown', [direction, distance, duration, fingerCount, fingerData, currentDirection]);
	
	              if (options.swipeDown) {
	                ret = options.swipeDown.call($element, event, direction, distance, duration, fingerCount, fingerData, currentDirection);
	              }
	              break;
	          }
	        }
	      }
	
	
	      //PINCHES....
	      if (gesture == PINCH) {
	        $element.trigger('pinchStatus', [phase, pinchDirection || null, pinchDistance || 0, duration || 0, fingerCount, pinchZoom, fingerData]);
	
	        if (options.pinchStatus) {
	          ret = options.pinchStatus.call($element, event, phase, pinchDirection || null, pinchDistance || 0, duration || 0, fingerCount, pinchZoom, fingerData);
	          //If the status cancels, then dont run the subsequent event handlers..
	          if (ret === false) return false;
	        }
	
	        if (phase == PHASE_END && validatePinch()) {
	
	          switch (pinchDirection) {
	            case IN:
	              $element.trigger('pinchIn', [pinchDirection || null, pinchDistance || 0, duration || 0, fingerCount, pinchZoom, fingerData]);
	
	              if (options.pinchIn) {
	                ret = options.pinchIn.call($element, event, pinchDirection || null, pinchDistance || 0, duration || 0, fingerCount, pinchZoom, fingerData);
	              }
	              break;
	
	            case OUT:
	              $element.trigger('pinchOut', [pinchDirection || null, pinchDistance || 0, duration || 0, fingerCount, pinchZoom, fingerData]);
	
	              if (options.pinchOut) {
	                ret = options.pinchOut.call($element, event, pinchDirection || null, pinchDistance || 0, duration || 0, fingerCount, pinchZoom, fingerData);
	              }
	              break;
	          }
	        }
	      }
	
	      if (gesture == TAP) {
	        if (phase === PHASE_CANCEL || phase === PHASE_END) {
	
	          clearTimeout(singleTapTimeout);
	          clearTimeout(holdTimeout);
	
	          //If we are also looking for doubelTaps, wait incase this is one...
	          if (hasDoubleTap() && !inDoubleTap()) {
	            doubleTapStartTime = getTimeStamp();
	
	            //Now wait for the double tap timeout, and trigger this single tap
	            //if its not cancelled by a double tap
	            singleTapTimeout = setTimeout($.proxy(function() {
	              doubleTapStartTime = null;
	              $element.trigger('tap', [event.target]);
	
	              if (options.tap) {
	                ret = options.tap.call($element, event, event.target);
	              }
	            }, this), options.doubleTapThreshold);
	
	          } else {
	            doubleTapStartTime = null;
	            $element.trigger('tap', [event.target]);
	            if (options.tap) {
	              ret = options.tap.call($element, event, event.target);
	            }
	          }
	        }
	      } else if (gesture == DOUBLE_TAP) {
	        if (phase === PHASE_CANCEL || phase === PHASE_END) {
	          clearTimeout(singleTapTimeout);
	          clearTimeout(holdTimeout);
	          doubleTapStartTime = null;
	          $element.trigger('doubletap', [event.target]);
	
	          if (options.doubleTap) {
	            ret = options.doubleTap.call($element, event, event.target);
	          }
	        }
	      } else if (gesture == LONG_TAP) {
	        if (phase === PHASE_CANCEL || phase === PHASE_END) {
	          clearTimeout(singleTapTimeout);
	          doubleTapStartTime = null;
	
	          $element.trigger('longtap', [event.target]);
	          if (options.longTap) {
	            ret = options.longTap.call($element, event, event.target);
	          }
	        }
	      }
	
	      return ret;
	    }
	
	
	    //
	    // GESTURE VALIDATION
	    //
	
	    /**
	     * Checks the user has swipe far enough
	     * @return Boolean if <code>threshold</code> has been set, return true if the threshold was met, else false.
	     * If no threshold was set, then we return true.
	     * @inner
	     */
	    function validateSwipeDistance() {
	      var valid = true;
	      //If we made it past the min swipe distance..
	      if (options.threshold !== null) {
	        valid = distance >= options.threshold;
	      }
	
	      return valid;
	    }
	
	    /**
	     * Checks the user has swiped back to cancel.
	     * @return Boolean if <code>cancelThreshold</code> has been set, return true if the cancelThreshold was met, else false.
	     * If no cancelThreshold was set, then we return true.
	     * @inner
	     */
	    function didSwipeBackToCancel() {
	      var cancelled = false;
	      if (options.cancelThreshold !== null && direction !== null) {
	        cancelled = (getMaxDistance(direction) - distance) >= options.cancelThreshold;
	      }
	
	      return cancelled;
	    }
	
	    /**
	     * Checks the user has pinched far enough
	     * @return Boolean if <code>pinchThreshold</code> has been set, return true if the threshold was met, else false.
	     * If no threshold was set, then we return true.
	     * @inner
	     */
	    function validatePinchDistance() {
	      if (options.pinchThreshold !== null) {
	        return pinchDistance >= options.pinchThreshold;
	      }
	      return true;
	    }
	
	    /**
	     * Checks that the time taken to swipe meets the minimum / maximum requirements
	     * @return Boolean
	     * @inner
	     */
	    function validateSwipeTime() {
	      var result;
	      //If no time set, then return true
	      if (options.maxTimeThreshold) {
	        if (duration >= options.maxTimeThreshold) {
	          result = false;
	        } else {
	          result = true;
	        }
	      } else {
	        result = true;
	      }
	
	      return result;
	    }
	
	
	    /**
	     * Checks direction of the swipe and the value allowPageScroll to see if we should allow or prevent the default behaviour from occurring.
	     * This will essentially allow page scrolling or not when the user is swiping on a touchSwipe object.
	     * @param {object} jqEvent The normalised jQuery representation of the event object.
	     * @param {string} direction The direction of the event. See {@link $.fn.swipe.directions}
	     * @see $.fn.swipe.directions
	     * @inner
	     */
	    function validateDefaultEvent(jqEvent, direction) {
	
	      //If the option is set, allways allow the event to bubble up (let user handle weirdness)
	      if (options.preventDefaultEvents === false) {
	        return;
	      }
	
	      if (options.allowPageScroll === NONE) {
	        jqEvent.preventDefault();
	      } else {
	        var auto = options.allowPageScroll === AUTO;
	
	        switch (direction) {
	          case LEFT:
	            if ((options.swipeLeft && auto) || (!auto && options.allowPageScroll != HORIZONTAL)) {
	              jqEvent.preventDefault();
	            }
	            break;
	
	          case RIGHT:
	            if ((options.swipeRight && auto) || (!auto && options.allowPageScroll != HORIZONTAL)) {
	              jqEvent.preventDefault();
	            }
	            break;
	
	          case UP:
	            if ((options.swipeUp && auto) || (!auto && options.allowPageScroll != VERTICAL)) {
	              jqEvent.preventDefault();
	            }
	            break;
	
	          case DOWN:
	            if ((options.swipeDown && auto) || (!auto && options.allowPageScroll != VERTICAL)) {
	              jqEvent.preventDefault();
	            }
	            break;
	
	          case NONE:
	
	            break;
	        }
	      }
	    }
	
	
	    // PINCHES
	    /**
	     * Returns true of the current pinch meets the thresholds
	     * @return Boolean
	     * @inner
	     */
	    function validatePinch() {
	      var hasCorrectFingerCount = validateFingers();
	      var hasEndPoint = validateEndPoint();
	      var hasCorrectDistance = validatePinchDistance();
	      return hasCorrectFingerCount && hasEndPoint && hasCorrectDistance;
	
	    }
	
	    /**
	     * Returns true if any Pinch events have been registered
	     * @return Boolean
	     * @inner
	     */
	    function hasPinches() {
	      //Enure we dont return 0 or null for false values
	      return !!(options.pinchStatus || options.pinchIn || options.pinchOut);
	    }
	
	    /**
	     * Returns true if we are detecting pinches, and have one
	     * @return Boolean
	     * @inner
	     */
	    function didPinch() {
	      //Enure we dont return 0 or null for false values
	      return !!(validatePinch() && hasPinches());
	    }
	
	
	
	
	    // SWIPES
	    /**
	     * Returns true if the current swipe meets the thresholds
	     * @return Boolean
	     * @inner
	     */
	    function validateSwipe() {
	      //Check validity of swipe
	      var hasValidTime = validateSwipeTime();
	      var hasValidDistance = validateSwipeDistance();
	      var hasCorrectFingerCount = validateFingers();
	      var hasEndPoint = validateEndPoint();
	      var didCancel = didSwipeBackToCancel();
	
	      // if the user swiped more than the minimum length, perform the appropriate action
	      // hasValidDistance is null when no distance is set
	      var valid = !didCancel && hasEndPoint && hasCorrectFingerCount && hasValidDistance && hasValidTime;
	
	      return valid;
	    }
	
	    /**
	     * Returns true if any Swipe events have been registered
	     * @return Boolean
	     * @inner
	     */
	    function hasSwipes() {
	      //Enure we dont return 0 or null for false values
	      return !!(options.swipe || options.swipeStatus || options.swipeLeft || options.swipeRight || options.swipeUp || options.swipeDown);
	    }
	
	
	    /**
	     * Returns true if we are detecting swipes and have one
	     * @return Boolean
	     * @inner
	     */
	    function didSwipe() {
	      //Enure we dont return 0 or null for false values
	      return !!(validateSwipe() && hasSwipes());
	    }
	
	    /**
	     * Returns true if we have matched the number of fingers we are looking for
	     * @return Boolean
	     * @inner
	     */
	    function validateFingers() {
	      //The number of fingers we want were matched, or on desktop we ignore
	      return ((fingerCount === options.fingers || options.fingers === ALL_FINGERS) || !SUPPORTS_TOUCH);
	    }
	
	    /**
	     * Returns true if we have an end point for the swipe
	     * @return Boolean
	     * @inner
	     */
	    function validateEndPoint() {
	      //We have an end value for the finger
	      return fingerData[0].end.x !== 0;
	    }
	
	    // TAP / CLICK
	    /**
	     * Returns true if a click / tap events have been registered
	     * @return Boolean
	     * @inner
	     */
	    function hasTap() {
	      //Enure we dont return 0 or null for false values
	      return !!(options.tap);
	    }
	
	    /**
	     * Returns true if a double tap events have been registered
	     * @return Boolean
	     * @inner
	     */
	    function hasDoubleTap() {
	      //Enure we dont return 0 or null for false values
	      return !!(options.doubleTap);
	    }
	
	    /**
	     * Returns true if any long tap events have been registered
	     * @return Boolean
	     * @inner
	     */
	    function hasLongTap() {
	      //Enure we dont return 0 or null for false values
	      return !!(options.longTap);
	    }
	
	    /**
	     * Returns true if we could be in the process of a double tap (one tap has occurred, we are listening for double taps, and the threshold hasn't past.
	     * @return Boolean
	     * @inner
	     */
	    function validateDoubleTap() {
	      if (doubleTapStartTime == null) {
	        return false;
	      }
	      var now = getTimeStamp();
	      return (hasDoubleTap() && ((now - doubleTapStartTime) <= options.doubleTapThreshold));
	    }
	
	    /**
	     * Returns true if we could be in the process of a double tap (one tap has occurred, we are listening for double taps, and the threshold hasn't past.
	     * @return Boolean
	     * @inner
	     */
	    function inDoubleTap() {
	      return validateDoubleTap();
	    }
	
	
	    /**
	     * Returns true if we have a valid tap
	     * @return Boolean
	     * @inner
	     */
	    function validateTap() {
	      return ((fingerCount === 1 || !SUPPORTS_TOUCH) && (isNaN(distance) || distance < options.threshold));
	    }
	
	    /**
	     * Returns true if we have a valid long tap
	     * @return Boolean
	     * @inner
	     */
	    function validateLongTap() {
	      //slight threshold on moving finger
	      return ((duration > options.longTapThreshold) && (distance < DOUBLE_TAP_THRESHOLD));
	    }
	
	    /**
	     * Returns true if we are detecting taps and have one
	     * @return Boolean
	     * @inner
	     */
	    function didTap() {
	      //Enure we dont return 0 or null for false values
	      return !!(validateTap() && hasTap());
	    }
	
	
	    /**
	     * Returns true if we are detecting double taps and have one
	     * @return Boolean
	     * @inner
	     */
	    function didDoubleTap() {
	      //Enure we dont return 0 or null for false values
	      return !!(validateDoubleTap() && hasDoubleTap());
	    }
	
	    /**
	     * Returns true if we are detecting long taps and have one
	     * @return Boolean
	     * @inner
	     */
	    function didLongTap() {
	      //Enure we dont return 0 or null for false values
	      return !!(validateLongTap() && hasLongTap());
	    }
	
	
	
	
	    // MULTI FINGER TOUCH
	    /**
	     * Starts tracking the time between 2 finger releases, and keeps track of how many fingers we initially had up
	     * @inner
	     */
	    function startMultiFingerRelease(event) {
	      previousTouchEndTime = getTimeStamp();
	      fingerCountAtRelease = event.touches.length + 1;
	    }
	
	    /**
	     * Cancels the tracking of time between 2 finger releases, and resets counters
	     * @inner
	     */
	    function cancelMultiFingerRelease() {
	      previousTouchEndTime = 0;
	      fingerCountAtRelease = 0;
	    }
	
	    /**
	     * Checks if we are in the threshold between 2 fingers being released
	     * @return Boolean
	     * @inner
	     */
	    function inMultiFingerRelease() {
	
	      var withinThreshold = false;
	
	      if (previousTouchEndTime) {
	        var diff = getTimeStamp() - previousTouchEndTime
	        if (diff <= options.fingerReleaseThreshold) {
	          withinThreshold = true;
	        }
	      }
	
	      return withinThreshold;
	    }
	
	
	    /**
	     * gets a data flag to indicate that a touch is in progress
	     * @return Boolean
	     * @inner
	     */
	    function getTouchInProgress() {
	      //strict equality to ensure only true and false are returned
	      return !!($element.data(PLUGIN_NS + '_intouch') === true);
	    }
	
	    /**
	     * Sets a data flag to indicate that a touch is in progress
	     * @param {boolean} val The value to set the property to
	     * @inner
	     */
	    function setTouchInProgress(val) {
	
	      //If destroy is called in an event handler, we have no el, and we have already cleaned up, so return.
	      if(!$element) { return; }
	
	      //Add or remove event listeners depending on touch status
	      if (val === true) {
	        $element.bind(MOVE_EV, touchMove);
	        $element.bind(END_EV, touchEnd);
	
	        //we only have leave events on desktop, we manually calcuate leave on touch as its not supported in webkit
	        if (LEAVE_EV) {
	          $element.bind(LEAVE_EV, touchLeave);
	        }
	      } else {
	
	        $element.unbind(MOVE_EV, touchMove, false);
	        $element.unbind(END_EV, touchEnd, false);
	
	        //we only have leave events on desktop, we manually calcuate leave on touch as its not supported in webkit
	        if (LEAVE_EV) {
	          $element.unbind(LEAVE_EV, touchLeave, false);
	        }
	      }
	
	
	      //strict equality to ensure only true and false can update the value
	      $element.data(PLUGIN_NS + '_intouch', val === true);
	    }
	
	
	    /**
	     * Creates the finger data for the touch/finger in the event object.
	     * @param {int} id The id to store the finger data under (usually the order the fingers were pressed)
	     * @param {object} evt The event object containing finger data
	     * @return finger data object
	     * @inner
	     */
	    function createFingerData(id, evt) {
	      var f = {
	        start: {
	          x: 0,
	          y: 0
	        },
	        last: {
	          x: 0,
	          y: 0
	        },
	        end: {
	          x: 0,
	          y: 0
	        }
	      };
	      f.start.x = f.last.x = f.end.x = evt.pageX || evt.clientX;
	      f.start.y = f.last.y = f.end.y = evt.pageY || evt.clientY;
	      fingerData[id] = f;
	      return f;
	    }
	
	    /**
	     * Updates the finger data for a particular event object
	     * @param {object} evt The event object containing the touch/finger data to upadte
	     * @return a finger data object.
	     * @inner
	     */
	    function updateFingerData(evt) {
	      var id = evt.identifier !== undefined ? evt.identifier : 0;
	      var f = getFingerData(id);
	
	      if (f === null) {
	        f = createFingerData(id, evt);
	      }
	
	      f.last.x = f.end.x;
	      f.last.y = f.end.y;
	
	      f.end.x = evt.pageX || evt.clientX;
	      f.end.y = evt.pageY || evt.clientY;
	
	      return f;
	    }
	
	    /**
	     * Returns a finger data object by its event ID.
	     * Each touch event has an identifier property, which is used
	     * to track repeat touches
	     * @param {int} id The unique id of the finger in the sequence of touch events.
	     * @return a finger data object.
	     * @inner
	     */
	    function getFingerData(id) {
	      return fingerData[id] || null;
	    }
	
	
	    /**
	     * Sets the maximum distance swiped in the given direction.
	     * If the new value is lower than the current value, the max value is not changed.
	     * @param {string}  direction The direction of the swipe
	     * @param {int}  distance The distance of the swipe
	     * @inner
	     */
	    function setMaxDistance(direction, distance) {
	      if(direction==NONE) return;
	      distance = Math.max(distance, getMaxDistance(direction));
	      maximumsMap[direction].distance = distance;
	    }
	
	    /**
	     * gets the maximum distance swiped in the given direction.
	     * @param {string}  direction The direction of the swipe
	     * @return int  The distance of the swipe
	     * @inner
	     */
	    function getMaxDistance(direction) {
	      if (maximumsMap[direction]) return maximumsMap[direction].distance;
	      return undefined;
	    }
	
	    /**
	     * Creats a map of directions to maximum swiped values.
	     * @return Object A dictionary of maximum values, indexed by direction.
	     * @inner
	     */
	    function createMaximumsData() {
	      var maxData = {};
	      maxData[LEFT] = createMaximumVO(LEFT);
	      maxData[RIGHT] = createMaximumVO(RIGHT);
	      maxData[UP] = createMaximumVO(UP);
	      maxData[DOWN] = createMaximumVO(DOWN);
	
	      return maxData;
	    }
	
	    /**
	     * Creates a map maximum swiped values for a given swipe direction
	     * @param {string} The direction that these values will be associated with
	     * @return Object Maximum values
	     * @inner
	     */
	    function createMaximumVO(dir) {
	      return {
	        direction: dir,
	        distance: 0
	      }
	    }
	
	
	    //
	    // MATHS / UTILS
	    //
	
	    /**
	     * Calculate the duration of the swipe
	     * @return int
	     * @inner
	     */
	    function calculateDuration() {
	      return endTime - startTime;
	    }
	
	    /**
	     * Calculate the distance between 2 touches (pinch)
	     * @param {point} startPoint A point object containing x and y co-ordinates
	     * @param {point} endPoint A point object containing x and y co-ordinates
	     * @return int;
	     * @inner
	     */
	    function calculateTouchesDistance(startPoint, endPoint) {
	      var diffX = Math.abs(startPoint.x - endPoint.x);
	      var diffY = Math.abs(startPoint.y - endPoint.y);
	
	      return Math.round(Math.sqrt(diffX * diffX + diffY * diffY));
	    }
	
	    /**
	     * Calculate the zoom factor between the start and end distances
	     * @param {int} startDistance Distance (between 2 fingers) the user started pinching at
	     * @param {int} endDistance Distance (between 2 fingers) the user ended pinching at
	     * @return float The zoom value from 0 to 1.
	     * @inner
	     */
	    function calculatePinchZoom(startDistance, endDistance) {
	      var percent = (endDistance / startDistance) * 1;
	      return percent.toFixed(2);
	    }
	
	
	    /**
	     * Returns the pinch direction, either IN or OUT for the given points
	     * @return string Either {@link $.fn.swipe.directions.IN} or {@link $.fn.swipe.directions.OUT}
	     * @see $.fn.swipe.directions
	     * @inner
	     */
	    function calculatePinchDirection() {
	      if (pinchZoom < 1) {
	        return OUT;
	      } else {
	        return IN;
	      }
	    }
	
	
	    /**
	     * Calculate the length / distance of the swipe
	     * @param {point} startPoint A point object containing x and y co-ordinates
	     * @param {point} endPoint A point object containing x and y co-ordinates
	     * @return int
	     * @inner
	     */
	    function calculateDistance(startPoint, endPoint) {
	      return Math.round(Math.sqrt(Math.pow(endPoint.x - startPoint.x, 2) + Math.pow(endPoint.y - startPoint.y, 2)));
	    }
	
	    /**
	     * Calculate the angle of the swipe
	     * @param {point} startPoint A point object containing x and y co-ordinates
	     * @param {point} endPoint A point object containing x and y co-ordinates
	     * @return int
	     * @inner
	     */
	    function calculateAngle(startPoint, endPoint) {
	      var x = startPoint.x - endPoint.x;
	      var y = endPoint.y - startPoint.y;
	      var r = Math.atan2(y, x); //radians
	      var angle = Math.round(r * 180 / Math.PI); //degrees
	
	      //ensure value is positive
	      if (angle < 0) {
	        angle = 360 - Math.abs(angle);
	      }
	
	      return angle;
	    }
	
	    /**
	     * Calculate the direction of the swipe
	     * This will also call calculateAngle to get the latest angle of swipe
	     * @param {point} startPoint A point object containing x and y co-ordinates
	     * @param {point} endPoint A point object containing x and y co-ordinates
	     * @return string Either {@link $.fn.swipe.directions.LEFT} / {@link $.fn.swipe.directions.RIGHT} / {@link $.fn.swipe.directions.DOWN} / {@link $.fn.swipe.directions.UP}
	     * @see $.fn.swipe.directions
	     * @inner
	     */
	    function calculateDirection(startPoint, endPoint) {
	
	      if( comparePoints(startPoint, endPoint) ) {
	        return NONE;
	      }
	
	      var angle = calculateAngle(startPoint, endPoint);
	
	      if ((angle <= 45) && (angle >= 0)) {
	        return LEFT;
	      } else if ((angle <= 360) && (angle >= 315)) {
	        return LEFT;
	      } else if ((angle >= 135) && (angle <= 225)) {
	        return RIGHT;
	      } else if ((angle > 45) && (angle < 135)) {
	        return DOWN;
	      } else {
	        return UP;
	      }
	    }
	
	
	    /**
	     * Returns a MS time stamp of the current time
	     * @return int
	     * @inner
	     */
	    function getTimeStamp() {
	      var now = new Date();
	      return now.getTime();
	    }
	
	
	
	    /**
	     * Returns a bounds object with left, right, top and bottom properties for the element specified.
	     * @param {DomNode} The DOM node to get the bounds for.
	     */
	    function getbounds(el) {
	      el = $(el);
	      var offset = el.offset();
	
	      var bounds = {
	        left: offset.left,
	        right: offset.left + el.outerWidth(),
	        top: offset.top,
	        bottom: offset.top + el.outerHeight()
	      }
	
	      return bounds;
	    }
	
	
	    /**
	     * Checks if the point object is in the bounds object.
	     * @param {object} point A point object.
	     * @param {int} point.x The x value of the point.
	     * @param {int} point.y The x value of the point.
	     * @param {object} bounds The bounds object to test
	     * @param {int} bounds.left The leftmost value
	     * @param {int} bounds.right The righttmost value
	     * @param {int} bounds.top The topmost value
	     * @param {int} bounds.bottom The bottommost value
	     */
	    function isInBounds(point, bounds) {
	      return (point.x > bounds.left && point.x < bounds.right && point.y > bounds.top && point.y < bounds.bottom);
	    };
	
	    /**
	     * Checks if the two points are equal
	     * @param {object} point A point object.
	     * @param {object} point B point object.
	     * @return true of the points match
	     */
	    function comparePoints(pointA, pointB) {
	      return (pointA.x == pointB.x && pointA.y == pointB.y);
	    }
	
	
	  }
	
	
	
	
	  /**
	   * A catch all handler that is triggered for all swipe directions.
	   * @name $.fn.swipe#swipe
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {int} direction The direction the user swiped in. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user swiped
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {object} fingerData The coordinates of fingers in event
	   * @param {string} currentDirection The current direction the user is swiping.
	   */
	
	
	
	
	  /**
	   * A handler that is triggered for "left" swipes.
	   * @name $.fn.swipe#swipeLeft
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {int} direction The direction the user swiped in. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user swiped
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {object} fingerData The coordinates of fingers in event
	   * @param {string} currentDirection The current direction the user is swiping.
	   */
	
	  /**
	   * A handler that is triggered for "right" swipes.
	   * @name $.fn.swipe#swipeRight
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {int} direction The direction the user swiped in. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user swiped
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {object} fingerData The coordinates of fingers in event
	   * @param {string} currentDirection The current direction the user is swiping.
	   */
	
	  /**
	   * A handler that is triggered for "up" swipes.
	   * @name $.fn.swipe#swipeUp
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {int} direction The direction the user swiped in. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user swiped
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {object} fingerData The coordinates of fingers in event
	   * @param {string} currentDirection The current direction the user is swiping.
	   */
	
	  /**
	   * A handler that is triggered for "down" swipes.
	   * @name $.fn.swipe#swipeDown
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {int} direction The direction the user swiped in. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user swiped
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {object} fingerData The coordinates of fingers in event
	   * @param {string} currentDirection The current direction the user is swiping.
	   */
	
	  /**
	   * A handler triggered for every phase of the swipe. This handler is constantly fired for the duration of the pinch.
	   * This is triggered regardless of swipe thresholds.
	   * @name $.fn.swipe#swipeStatus
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {string} phase The phase of the swipe event. See {@link $.fn.swipe.phases}
	   * @param {string} direction The direction the user swiped in. This is null if the user has yet to move. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user swiped. This is 0 if the user has yet to move.
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {object} fingerData The coordinates of fingers in event
	   * @param {string} currentDirection The current direction the user is swiping.
	   */
	
	  /**
	   * A handler triggered for pinch in events.
	   * @name $.fn.swipe#pinchIn
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {int} direction The direction the user pinched in. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user pinched
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {int} zoom The zoom/scale level the user pinched too, 0-1.
	   * @param {object} fingerData The coordinates of fingers in event
	   */
	
	  /**
	   * A handler triggered for pinch out events.
	   * @name $.fn.swipe#pinchOut
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {int} direction The direction the user pinched in. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user pinched
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {int} zoom The zoom/scale level the user pinched too, 0-1.
	   * @param {object} fingerData The coordinates of fingers in event
	   */
	
	  /**
	   * A handler triggered for all pinch events. This handler is constantly fired for the duration of the pinch. This is triggered regardless of thresholds.
	   * @name $.fn.swipe#pinchStatus
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {int} direction The direction the user pinched in. See {@link $.fn.swipe.directions}
	   * @param {int} distance The distance the user pinched
	   * @param {int} duration The duration of the swipe in milliseconds
	   * @param {int} fingerCount The number of fingers used. See {@link $.fn.swipe.fingers}
	   * @param {int} zoom The zoom/scale level the user pinched too, 0-1.
	   * @param {object} fingerData The coordinates of fingers in event
	   */
	
	  /**
	   * A click handler triggered when a user simply clicks, rather than swipes on an element.
	   * This is deprecated since version 1.6.2, any assignment to click will be assigned to the tap handler.
	   * You cannot use <code>on</code> to bind to this event as the default jQ <code>click</code> event will be triggered.
	   * Use the <code>tap</code> event instead.
	   * @name $.fn.swipe#click
	   * @event
	   * @deprecated since version 1.6.2, please use {@link $.fn.swipe#tap} instead
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {DomObject} target The element clicked on.
	   */
	
	  /**
	   * A click / tap handler triggered when a user simply clicks or taps, rather than swipes on an element.
	   * @name $.fn.swipe#tap
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {DomObject} target The element clicked on.
	   */
	
	  /**
	   * A double tap handler triggered when a user double clicks or taps on an element.
	   * You can set the time delay for a double tap with the {@link $.fn.swipe.defaults#doubleTapThreshold} property.
	   * Note: If you set both <code>doubleTap</code> and <code>tap</code> handlers, the <code>tap</code> event will be delayed by the <code>doubleTapThreshold</code>
	   * as the script needs to check if its a double tap.
	   * @name $.fn.swipe#doubleTap
	   * @see  $.fn.swipe.defaults#doubleTapThreshold
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {DomObject} target The element clicked on.
	   */
	
	  /**
	   * A long tap handler triggered once a tap has been release if the tap was longer than the longTapThreshold.
	   * You can set the time delay for a long tap with the {@link $.fn.swipe.defaults#longTapThreshold} property.
	   * @name $.fn.swipe#longTap
	   * @see  $.fn.swipe.defaults#longTapThreshold
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {DomObject} target The element clicked on.
	   */
	
	  /**
	   * A hold tap handler triggered as soon as the longTapThreshold is reached
	   * You can set the time delay for a long tap with the {@link $.fn.swipe.defaults#longTapThreshold} property.
	   * @name $.fn.swipe#hold
	   * @see  $.fn.swipe.defaults#longTapThreshold
	   * @event
	   * @default null
	   * @param {EventObject} event The original event object
	   * @param {DomObject} target The element clicked on.
	   */
	
	}));


/***/ }),
/* 35 */
/***/ (function(module, exports) {

	/* WEBPACK VAR INJECTION */(function(__webpack_amd_options__) {module.exports = __webpack_amd_options__;
	
	/* WEBPACK VAR INJECTION */}.call(exports, {}))

/***/ })
/******/ ]);
//# sourceMappingURL=app.js.map