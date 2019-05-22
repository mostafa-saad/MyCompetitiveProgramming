var ruleJS = (function (root) {
  'use strict';

  /**
   * object instance
   */
  var instance = this;

  /**
   * root element
   */
  var rootElement = document.getElementById(root) || null;

  /**
   * current version
   * @type {string}
   */
  var version = '0.0.3';

  /**
   * parser object delivered by jison library
   * @type {Parser|*|{}}
   */
  var parser = {};

  var FormulaParser = function(handler) {
    var formulaLexer = function () {};
    formulaLexer.prototype = Parser.lexer;

    var formulaParser = function () {
      this.lexer = new formulaLexer();
      this.yy = {};
    };

    formulaParser.prototype = Parser;
    var newParser = new formulaParser;
    newParser.setObj = function(obj) {
      newParser.yy.obj = obj;
    };

    newParser.yy.parseError = function (str, hash) {
    //      if (!((hash.expected && hash.expected.indexOf("';'") >= 0) &&
    //        (hash.token === "}" || hash.token === "EOF" ||
    //          parser.newLine || parser.wasNewLine)))
    //      {
    //        throw new SyntaxError(hash);
    //      }
          throw {
            name: 'Parser error',
            message: str,
            prop: hash
          };
    };
        newParser.yy.handler = handler;

        return newParser;
  };

  /**
   * Exception object
   * @type {{errors: {type: string, output: string}[], get: get}}
   */
  var Exception = {
    /**
     * error types
     */
    errors: [
      {type: 'NULL', output: '#NULL'},
      {type: 'DIV_ZERO', output: '#DIV/0!'},
      {type: 'VALUE', output: '#VALUE!'},
      {type: 'REF', output: '#REF!'},
      {type: 'NAME', output: '#NAME?'},
      {type: 'NUM', output: '#NUM!'},
      {type: 'NOT_AVAILABLE', output: '#N/A!'},
      {type: 'ERROR', output: '#ERROR'},
      {type: 'NEED_UPDATE', output: '#NEED_UPDATE'}
    ],
    /**
     * get error by type
     * @param {String} type
     * @returns {*}
     */
    get: function (type) {
      var error = Exception.errors.filter(function (item) {
        return item.type === type || item.output === type;
      })[0];

      return error ? error.output : null;
    }
  };

  /**
   * matrix collection for each form, contains cache of all form element
   */
  var Matrix = function () {

    /**
     * single item (cell) object
     * @type {{id: string, formula: string, value: string, error: string, deps: Array, formulaEdit: boolean}}
     */
    var item = {
      id: '',
      formula: '',
      value: '',
      error: '',
      deps: [],
      formulaEdit: false
    };

    /**
     * array of items
     * @type {Array}
     */
    this.data = [];

    /**
     * form elements, which can be parsed
     * @type {string[]}
     */
    var formElements = ['input[type=text]', '[data-formula]'];

    var listen = function () {
      if (document.activeElement && document.activeElement !== document.body) {
        document.activeElement.blur();
      }
      else if (!document.activeElement) { //IE
        document.body.focus();
      }
    };

    /**
     * get item from data array
     * @param {String} id
     * @returns {*}
     */
    this.getItem = function (id) {
      return instance.matrix.data.filter(function (item) {
        return item.id === id;
      })[0];
    };

    /**
     * remove item from data array
     * @param {String} id
     */
    this.removeItem = function (id) {
      instance.matrix.data = instance.matrix.data.filter(function (item) {
        return item.id !== id;
      });
    };

    /**
     * remove items from data array in col
     * @param {Number} col
     */
    this.removeItemsInCol = function (col) {
      instance.matrix.data = instance.matrix.data.filter(function (item) {
        return item.col !== col;
      });
    };

    /**
     * remove items from data array in row
     * @param {Number} row
     */
    this.removeItemsInRow = function (row) {
      instance.matrix.data = instance.matrix.data.filter(function (item) {
        return item.row !== row;
      })
    };

    /**
     * remove items from data array below col
     * @param col
     */
    this.removeItemsBelowCol = function (col) {
      instance.matrix.data = instance.matrix.data.filter(function (item) {
        return item.col < col;
      });
    };

    /**
     * remove items from data array below row
     * @param row
     */
    this.removeItemsBelowRow = function (row) {
      instance.matrix.data = instance.matrix.data.filter(function (item) {
        return item.row < row;
      })
    };

    /**
     * update item properties
     * @param {Object|String} item or id
     * @param {Object} props
     */
    this.updateItem = function (item, props) {
      if (instance.utils.isString(item)) {
        item = instance.matrix.getItem(item);
      }

      if (item && props) {
        for (var p in props) {
          if (item[p] && instance.utils.isArray(item[p])) {
            if (instance.utils.isArray(props[p])) {
              props[p].forEach(function (i) {
                if (item[p].indexOf(i) === -1) {
                  item[p].push(i);
                }
              });
            } else {

              if (item[p].indexOf(props[p]) === -1) {
                item[p].push(props[p]);
              }
            }
          } else {
            item[p] = props[p];
          }
        }
      }
    };

    /**
     * add item to data array
     * @param {Object} item
     */
    this.addItem = function (item) {
      var cellId = item.id,
          coords = instance.utils.cellCoords(cellId);

      item.row = coords.row;
      item.col = coords.col;

      var cellExist = instance.matrix.data.filter(function (cell) {
        return cell.id === cellId;
      })[0];

      if (!cellExist) {
        instance.matrix.data.push(item);
      } else {
        instance.matrix.updateItem(cellExist, item);
      }

      return instance.matrix.getItem(cellId);
    };

    /**
     * get references items to column
     * @param {Number} col
     * @returns {Array}
     */
    this.getRefItemsToColumn = function (col) {
      var result = [];

      if (!instance.matrix.data.length) {
        return result;
      }

      instance.matrix.data.forEach(function (item) {
        if (item.deps) {
          var deps = item.deps.filter(function (cell) {

            var alpha = instance.utils.getCellAlphaNum(cell).alpha,
              num = instance.utils.toNum(alpha);

            return num >= col;
          });

          if (deps.length > 0 && result.indexOf(item.id) === -1) {
            result.push(item.id);
          }
        }
      });

      return result;
    };

    this.getRefItemsToRow = function (row) {
      var result = [];

      if (!instance.matrix.data.length) {
        return result;
      }

      instance.matrix.data.forEach(function (item) {
        if (item.deps) {
          var deps = item.deps.filter(function (cell) {
            var num = instance.utils.getCellAlphaNum(cell).num;
            return num > row;
          });

          if (deps.length > 0 && result.indexOf(item.id) === -1) {
            result.push(item.id);
          }
        }
      });

      return result;
    };

    /**
     * update element item properties in data array
     * @param {Element} element
     * @param {Object} props
     */
    this.updateElementItem = function (element, props) {
      var id = element.getAttribute('data-cell-id'),
          item = instance.matrix.getItem(id);
      instance.matrix.updateItem(item, props);
    };

    /**
     * get cell dependencies
     * @param {String} id
     * @returns {Array}
     */
    this.getDependencies = function (id) {
      /**
       * get dependencies by element
       * @param {String} id
       * @returns {Array}
       */
      var getDependencies = function (id) {
        var filtered = instance.matrix.data.filter(function (cell) {
          if (cell.deps) {
            return cell.deps.indexOf(id) > -1;
          }
        });

        var deps = [];
        filtered.forEach(function (cell) {
          if (deps.indexOf(cell.id) === -1) {
            deps.push(cell.id);
          }
        });

        return deps;
      };

      var allDependencies = [];

      /**
       * get total dependencies
       * @param {String} id
       */
      var getTotalDependencies = function (id) {
        var deps = getDependencies(id);

        if (deps.length) {
          deps.forEach(function (refId) {
            if (allDependencies.indexOf(refId) === -1) {
              allDependencies.push(refId);

              var item = instance.matrix.getItem(refId);
              if (item.deps.length) {
                getTotalDependencies(refId);
              }
            }
          });
        }
      };

      getTotalDependencies(id);

      return allDependencies;
    };

    /**
     * get total element cell dependencies
     * @param {Element} element
     * @returns {Array}
     */
    this.getElementDependencies = function (element) {
      return instance.matrix.getDependencies(element.getAttribute('id'));
    };

    /**
     * recalculate refs cell
     * @param {Element} element
     */
    var recalculateElementDependencies = function (element) {
      var allDependencies = instance.matrix.getElementDependencies(element),
          id = element.getAttribute('id');

      allDependencies.forEach(function (refId) {
        var item = instance.matrix.getItem(refId);
        if (item && item.formula) {
          var refElement = document.getElementById(refId);
          calculateElementFormula(item.formula, refElement);
        }
      });
    };

    /**
     * calculate element formula
     * @param {String} formula
     * @param {Element} element
     * @returns {Object}
     */
    var calculateElementFormula = function (formula, element) {
      // to avoid double translate formulas, update item data in parser
      var parsed = parse(formula, element),
          value = parsed.result,
          error = parsed.error,
          nodeName = element.nodeName.toUpperCase();

      if (parsed.error && formula.indexOf('IFERROR') > -1) {
        var matches = formula.match(/\((\(*.*\)*),(\(*.*\)*)\)$/);
        if (matches) {
          var secondParse = parse(matches[2], element);
          if (!secondParse.error) {
            error = null;
            value = secondParse.result;
          }
        }
      }

      instance.matrix.updateElementItem(element, {value: value, error: error});

      if (error === '#VALUE!') {
        error = 0;
      }

      var renderedValue = value;

      if (['INPUT'].indexOf(nodeName) === -1) {
        /*SUPSYSTIC  Originaly here was element.innerText and this didn't work in FF browser */

        if (value !== '0' && value !== 0 && value % 1 !== 0) {
          // round float
          var floatValue = parseFloat(value);
          if (floatValue.toString().indexOf('.') !== -1) {
            var afterPointSybolsLength = floatValue.toString().split('.')[1].length;
            if (afterPointSybolsLength > 4) {
              renderedValue = floatValue.toFixed(4);
            }
          }
        }
        if (element.innerText) {
          element.innerText = renderedValue || error;
        } else {
          element.textContent = renderedValue || error;
        }
        /* */
      }


      element.value = value || error;

      return parsed;
    };

    /**
     * register new found element to matrix
     * @param {Element} element
     * @returns {Object}
     */
    var registerElementInMatrix = function (element) {
      var id = element.getAttribute('data-cell-id'),
          formula = element.getAttribute('data-formula');

      if (formula) {
        // add item with basic properties to data array
        instance.matrix.addItem({
          id: id,
          formula: formula
        });

        calculateElementFormula(formula, element);
      }

    };

    /**
     * register events for elements
     * @param element
     */
    var registerElementEvents = function (element) {
      var id = element.getAttribute('id');

      // on db click show formula
      element.addEventListener('dblclick', function () {
        var item = instance.matrix.getItem(id);

        if (item && item.formula) {
          item.formulaEdit = true;
          element.value = '=' + item.formula;
        }
      });

      element.addEventListener('blur', function () {
        var item = instance.matrix.getItem(id);

        if (item) {
          if (item.formulaEdit) {
            element.value = item.value || item.error;
          }

          item.formulaEdit = false;
        }
      });

      // if pressed ESC restore original value
      element.addEventListener('keyup', function (event) {
        switch (event.keyCode) {
          case 13: // ENTER
          case 27: // ESC
            // leave cell
            listen();
            break;
        }
      });

      // re-calculate formula if ref cells value changed
      element.addEventListener('change', function () {
        // reset and remove item
        instance.matrix.removeItem(id);

        // check if inserted text could be the formula
        var value = element.value;

        if (value[0] === '=') {
          element.setAttribute('data-formula', value.substr(1));
          registerElementInMatrix(element);
        }

        // get ref cells and re-calculate formulas
        recalculateElementDependencies(element);
      });
    };

    this.depsInFormula = function (item) {

      var formula = item.formula,
          deps = item.deps;

      if (deps) {
        deps = deps.filter(function (id) {
          return formula.indexOf(id) !== -1;
        });

        return deps.length > 0;
      }

      return false;
    };

    /**
     * scan the form and build the calculation matrix
     */
    this.scan = function () {
      var $totalElements = rootElement.querySelectorAll(formElements);
      // iterate through elements contains specified attributes
      [].slice.call($totalElements).forEach(function ($item) {
        registerElementInMatrix($item);
        registerElementEvents($item);
      });
    };
  };

  /**
   * utils methods
   * @type {{isArray: isArray, toNum: toNum, toChar: toChar, cellCoords: cellCoords}}
   */
  var utils = {
    /**
     * check if value is array
     * @param value
     * @returns {boolean}
     */
    isArray: function (value) {
      return Object.prototype.toString.call(value) === '[object Array]';
    },

    /**
     * check if value is number
     * @param value
     * @returns {boolean}
     */
    isNumber: function (value) {
      return Object.prototype.toString.call(value) === '[object Number]';
    },

    /**
     * check if value is string
     * @param value
     * @returns {boolean}
     */
    isString: function (value) {
      return Object.prototype.toString.call(value) === '[object String]';
    },

    /**
     * check if value is function
     * @param value
     * @returns {boolean}
     */
    isFunction: function (value) {
      return Object.prototype.toString.call(value) === '[object Function]';
    },

    /**
     * check if value is undefined
     * @param value
     * @returns {boolean}
     */
    isUndefined: function (value) {
      return Object.prototype.toString.call(value) === '[object Undefined]';
    },

    /**
     * check if value is null
     * @param value
     * @returns {boolean}
     */
    isNull: function (value) {
      return Object.prototype.toString.call(value) === '[object Null]';
    },

    /**
     * check if value is set
     * @param value
     * @returns {boolean}
     */
    isSet: function (value) {
      return !instance.utils.isUndefined(value) && !instance.utils.isNull(value);
    },

    /**
     * check if value is cell
     * @param {String} value
     * @returns {Boolean}
     */
    isCell: function (value) {
      return value.match(/^[A-Za-z]+[0-9]+/) ? true : false;
    },

    /**
     * get row name and column number
     * @param cell
     * @returns {{alpha: string, num: number}}
     */
    getCellAlphaNum: function (cell) {
      var num = cell.match(/\d+$/),
          alpha = cell.replace(num, '');

      return {
        alpha: alpha,
        num: parseInt(num[0], 10)
      }
    },

    /**
     * change row cell index A1 -> A2
     * @param {String} cell
     * @param {Number} counter
     * @returns {String}
     */
    changeRowIndex: function (cell, counter) {
      var alphaNum = instance.utils.getCellAlphaNum(cell),
          alpha = alphaNum.alpha,
          col = alpha,
          row = parseInt(alphaNum.num + counter, 10);

      if (row < 1) {
        row = 1;
      }

      return col + '' + row;
    },

    /**
     * change col cell index A1 -> B1 Z1 -> AA1
     * @param {String} cell
     * @param {Number} counter
     * @returns {String}
     */
    changeColIndex: function (cell, counter) {
      var alphaNum = instance.utils.getCellAlphaNum(cell),
          alpha = alphaNum.alpha,
          col = instance.utils.toChar(parseInt(instance.utils.toNum(alpha) + counter, 10)),
          row = alphaNum.num;

      if (!col || col.length === 0) {
        col = 'A';
      }

      var fixedCol = alpha[0] === '$' || false,
          fixedRow = alpha[alpha.length - 1] === '$' || false;

      col = (fixedCol ? '$' : '') + col;
      row = (fixedRow ? '$' : '') + row;

      return col + '' + row;
    },


    changeFormula: function (formula, delta, change) {
      if (!delta) {
        delta = 1;
      }

      return formula.replace(/(\$?[A-Za-z]+\$?[0-9]+)/g, function (match) {
        var alphaNum = instance.utils.getCellAlphaNum(match),
            alpha = alphaNum.alpha,
            num = alphaNum.num;

        if (instance.utils.isNumber(change.col)) {
          num = instance.utils.toNum(alpha);

          if (change.col <= num) {
            return instance.utils.changeColIndex(match, delta);
          }
        }

        if (instance.utils.isNumber(change.row)) {
          if (change.row < num) {
            return instance.utils.changeRowIndex(match, delta);
          }
        }

        return match;
      });
    },

    /**
     * update formula cells
     * @param {String} formula
     * @param {String} direction
     * @param {Number} delta
     * @returns {String}
     */
    updateFormula: function (formula, direction, delta) {
      var type,
          counter;

      // left, right -> col
      if (['left', 'right'].indexOf(direction) !== -1) {
        type = 'col';
      } else if (['up', 'down'].indexOf(direction) !== -1) {
        type = 'row'
      }

      // down, up -> row
      if (['down', 'right'].indexOf(direction) !== -1) {
        counter = delta * 1;
      } else if(['up', 'left'].indexOf(direction) !== -1) {
        counter = delta * (-1);
      }

      if (type && counter) {
        return formula.replace(/(\$?[A-Za-z]+\$?[0-9]+)/g, function (match) {

          var alpha = instance.utils.getCellAlphaNum(match).alpha;

          var fixedCol = alpha[0] === '$' || false,
              fixedRow = alpha[alpha.length - 1] === '$' || false;

          if (type === 'row' && fixedRow) {
            return match;
          }

          if (type === 'col' && fixedCol) {
            return match;
          }

          return (type === 'row' ? instance.utils.changeRowIndex(match, counter) : instance.utils.changeColIndex(match, counter));
        });
      }

      return formula;
    },

    /**
     * convert string char to number e.g A => 0, Z => 25, AA => 27
     * @param {String} chr
     * @returns {Number}
     */
    toNum: function (chr) {
//      chr = instance.utils.clearFormula(chr).split('');
//
//      var base = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"],
//          i, j, result = 0;
//
//      for (i = 0, j = chr.length - 1; i < chr.length; i += 1, j -= 1) {
//        result += Math.pow(base.length, j) * (base.indexOf(chr[i]));
//      }
//
//      return result;

      chr = instance.utils.clearFormula(chr);
      var baseUppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', baseLowercase = baseUppercase.toLowerCase(), base, i, j, result = 0;

      for (i = 0, j = chr.length - 1; i < chr.length; i += 1, j -= 1) {
		  // Fix for using lovercase cell coords in formulas - supsystic
		  if(baseLowercase.indexOf(chr[i]) === -1) {
			  base = baseUppercase;
		  } else {
			  base = baseLowercase;
		  }
		  result += Math.pow(base.length, j) * (base.indexOf(chr[i]) + 1);
      }

      if (result) {
        --result;
      }

      return result;
    },

    /**
     * convert number to string char, e.g 0 => A, 25 => Z, 26 => AA
     * @param {Number} num
     * @returns {String}
     */
    toChar: function (num) {
      var s = '';

      while (num >= 0) {
        s = String.fromCharCode(num % 26 + 97) + s;
        num = Math.floor(num / 26) - 1;
      }

      return s.toUpperCase();
    },

    /**
     * get cell coordinates
     * @param {String} cell A1
     * @returns {{row: Number, col: number}}
     */
    cellCoords: function (cell) {
      var num = cell.match(/\d+$/),
          alpha = cell.replace(num, '');

      return {
        row: parseInt(num[0], 10) - 1,
        col: instance.utils.toNum(alpha)
      };
    },

    /**
     * remove $ from formula
     * @param {String} formula
     * @returns {String|void}
     */
    clearFormula: function (formula) {
      return formula.replace(/\$/g, '');
    },

    /**
     * translate cell coordinates to merged form {row:0, col:0} -> A1
     * @param coords
     * @returns {string}
     */
    translateCellCoords: function (coords) {
      return instance.utils.toChar(coords.col) + '' + parseInt(coords.row + 1, 10);
    },

    /**
     * iterate cell range and get theirs indexes and values
     * @param {Object} startCell ex.: {row:1, col: 1}
     * @param {Object} endCell ex.: {row:10, col: 1}
     * @param {Function=} callback
     * @returns {{index: Array, value: Array}}
     */
    iterateCells: function (startCell, endCell, callback) {
      var result = {
        index: [], // list of cell index: A1, A2, A3
        value: []  // list of cell value
      };

      var cols = {
        start: 0,
        end: 0
      };

      if (endCell.col >= startCell.col) {
        cols = {
          start: startCell.col,
          end: endCell.col
        };
      } else {
        cols = {
          start: endCell.col,
          end: startCell.col
        };
      }

      var rows = {
        start: 0,
        end: 0
      };

      if (endCell.row >= startCell.row) {
        rows = {
          start: startCell.row,
          end: endCell.row
        };
      } else {
        rows = {
          start: endCell.row,
          end: startCell.row
        };
      }

      for (var column = cols.start; column <= cols.end; column++) {
        for (var row = rows.start; row <= rows.end; row++) {
          var cellIndex = instance.utils.toChar(column) + (row + 1),
              cellValue = instance.helper.cellValue.call(this, cellIndex);

          result.index.push(cellIndex);
          result.value.push(cellValue);
        }
      }

      if (instance.utils.isFunction(callback)) {
        return callback.apply(callback, [result]);
      } else {
        return result;
      }
    },

    sort: function (rev) {
      return function (a, b) {
        return ((a < b) ? -1 : ((a > b) ? 1 : 0)) * (rev ? -1 : 1);
      }
    }
  };

  /**
   * helper with methods using by parser
   * @type {{number: number, numberInverted: numberInverted, mathMatch: mathMatch, callFunction: callFunction}}
   */
  var helper = {
    /**
     * list of supported formulas
     */
    SUPPORTED_FORMULAS: [
		"UNIQUE",
		"FLATTEN", "FUNCTION",
		"MOMENT", "MOMENTADD", "MOMENTDIFF", "MOMENTSUB", "MOMENTUTC", "MOMENTUTCADD", "MOMENTUTCDIFF", "MOMENTUTCSUB", "MOMENTUNIX", "MOMENTFORMAT", "MOMENTISLEAPYEAR", "MOMENTISDST", "MOMENTSTARTOF", "MOMENTENDOF", "MOMENTISAFTER", "MOMENTISBEFORE",
		"INDEX", "INTERVAL",
		"ARGSCONCAT", "ARGSTOARRAY",
		"CLEANFLOAT", "COUNTIN",
		"FINDFIELD", "FINDRESULTINDEX",
		"DAVERAGE", "DCOUNT", "DCOUNTA", "DGET", "DMAX", "DMIN", "DPRODUCT", "DSTDEV", "DSTDEVP", "DSUM", "DVAR", "DVARP", "GETJSON", "DATE", "DATEVALUE", "DAY", "DAYS", "DAYS360",
		"EDATE", "EOMONTH",
		"FROMNOW",
		"HOUR",
		"MINUTE", "MATCH",
		"ISOWEEKNUM",
		"MONTH",
		"NETWORKDAYS", "NETWORKDAYSINTL", "NOW",
		"SECOND",
		"TIME", "TIMEVALUE", "TODAY",
		"WEEKDAY", "WEEKNUM", "WORKDAY", "WORKDAYINTL",
		"YEAR", "YEARFRAC",
		"BESSELI", "BESSELJ", "BESSELK", "BESSELY", "VALIDBIN", "BIN2DEC", "BIN2HEX", "BIN2OCT", "BITAND", "BITLSHIFT", "BITOR", "BITRSHIFT", "BITXOR",
		"COMPLEX", "CONVERT",
		"DEC2BIN", "DEC2HEX", "DEC2OCT", "DELTA",
		"ERF", "ERFC", /*"ERFCPRECISE",*/ /*"ERFPRECISE",*/
		"GESTEP",
		"HEX2BIN", "HEX2DEC", "HEX2OCT",
		"IMABS", "IMAGINARY", "IMARGUMENT", "IMCONJUGATE", "IMCOS", "IMCOSH", "IMCOT", "IMCSC", "IMCSCH", "IMDIV", "IMEXP", "IMLN", "IMLOG10", "IMLOG2", "IMPOWER", "IMPRODUCT", "IMREAL", "IMSEC", "IMSECH", "IMSIN", "IMSINH", "IMSQRT", "IMSUB", "IMSUM", "IMTAN",
		"OCT2BIN", "OCT2DEC", "OCT2HEX",
		"ACCRINT", /*"ACCRINTM", "AMORDEGRC", "AMORLINC",
		"COUPDAYBS", "COUPDAYS", "COUPDAYSNC", "COUPNCD", "COUPNUM", "COUPPCD",*/ "CUMIPMT", "CUMPRINC",
		"DB", "DDB", /*"DISC",*/ "DOLLARDE", "DOLLARFR", /*"DURATION",*/
		"EFFECT",
		"FV", "FVSCHEDULE",
		/*"INTRATE",*/ "IPMT", "IRR", "ISPMT",
		/*"MDURATION",*/ "MIRR",
		"NOMINAL", "NPER", "NPV",
		/*"ODDFPRICE", "ODDFYIELD", "ODDLPRICE", "ODDLYIELD",*/
		"PDURATION", "PMT", "PPMT", /*"PRICE", "PRICEDISC", "PRICEMAT",*/ "PV",
		"RATE", /*"RECEIVED",*/ "RRI",
		"SLN", "SYD",
		"TBILLEQ", "TBILLPRICE", "TBILLYIELD",
		/*"VDB",*/
		"XIRR", "XNPV",
		/*"YIELD", "YIELDDISC", "YIELDMAT",*/
		"ISNUMBER",
		"AND",
		"FALSE",
		"SWITCH",
		"IF", "IFNA",
		"NOT",
		"OR",
		"TRUE",
		"XOR",
		"REFERENCE",
		"ABS", "ACOS", "ACOSH", "ACOT", "ACOTH", "AGGREGATE", "ARABIC", "ASIN", "ASINH", "ATAN", "ATAN2", "ATANH",
		"BASE",
		"CEILING", "CEILINGMATH", "CEILINGPRECISE", "COMBIN", "COMBINA", "COS", "COSH", "COT", "COTH", "CSC", "CSCH",
		"DECIMAL", "DEGREES",
		"EVEN", "EXP",
		"FACT", "FACTDOUBLE", "FLOOR", "FLOORMATH", "FLOORPRECISE",
		"GCD",
		"INT", "ISEVEN", "ISOCEILING", "ISODD",
		"LCM", "LN", "LOG", "LOG10", "MOD", "MROUND", "MULTINOMIAL",
		"ODD",
		"E",
		"PI", "POWER", "PRODUCT",
		"QUOTIENT",
		"RADIANS", "RAND", "RANDBETWEEN", "ROUND", "ROUNDDOWN", "ROUNDUP",
		"SERIESSUM", "SEC", "SECH", "SIGN", "SIN", "SINH", "SQRT", "SQRTPI", "SUBTOTAL", "SUM", "SUMIF", "SUMIFS", "SUMPRODUCT", "SUMSQ", "SUMX2MY2", "SUMX2PY2", "SUMXMY2",
		"TAN", "TANH", "TRUNC",
		"AVEDEV", "AVERAGE", "AVERAGEA", "AVERAGEIF", "AVERAGEIFS",
		"BETADIST", "BETAINV", "BINOMDIST", "BINOMDISTRANGE", "BINOMINV",
		"CHISQDIST", /*"CHISQDISTRT", "CHISQINV", "CHISQINVRT", "CHISQTEST",*/ "CONFIDENCENORM", "CONFIDENCET", "CORREL", "COUNT", "COUNTA", "COUNTBLANK", "COUNTIF", "COUNTIFS", "COUNTUNIQUE", "COVARIANCEP", "COVARIANCES",
		"DEVSQ",
		"EXPONDIST",
		"FDIST", /*"FDISTRT",*/ "FINV", /*"FINVRT", "FTEST",*/ "FISHER", "FISHERINV", "FORECAST", "FREQUENCY",
		"GAMMA", /*"GAMMADIST", "GAMMAINV",*/ "GAMMALN", /*"GAMMALNPRECISE",*/ "GAUSS", "GEOMEAN", "GROWTH", "HARMEAN", "HYPGEOMDIST",
		"INTERCEPT",
		"KURT",
		"LARGE", "LINEST", /*"LOGEST",*/ "LOGNORMDIST", "LOGNORMINV",
		"MAX", "MAXA", "MEDIAN", "MIN", "MINA", "MODEMULT", "MODESNGL",
		"NEGBINOMDIST", "NORMDIST", "NORMINV", "NORMSDIST", "NORMSINV",
		"PEARSON", "PERCENTILEEXC", "PERCENTILEINC", "PERCENTRANKEXC", "PERCENTRANKINC", "PERMUT", "PERMUTATIONA", "PHI", "POISSONDIST", "PROB",
		"QUARTILEEXC", "QUARTILEINC",
		"RANK", "RANKAVG", "RANKEQ", "RSQ",
		"SKEW", "SKEWP", "SLOPE", "SMALL", "STANDARDIZE", "STDEVA", "STDEVP", "STDEVPA", "STDEVS", "STEYX",
		"TDIST", /*"TDIST2T", "TDISTRT",*/ "TINV", /*"TINV2T", "TTEST", "TREND",*/ "TRIMMEAN",
		"VARA", "VARP", "VARPA", "VARS",
		"WEIBULLDIST",
		"ZTEST",
		"CHAR", "CLEAN", "CODE", "CONCATENATE",
		"DOLLAR",
		"EXACT",
		"FIND", "FIXED",
		"HTML2TEXT", "HUMANIZE",
		"JOIN",
		"LEFT", "LEN", "LOWER",
		"MID",
		"NUMBERVALUE", "NUMBERS",
		"PROPER",
		"REGEXEXTRACT", "REGEXMATCH", "REGEXREPLACE",
		"REPLACE", "REPT", "RIGHT", "ROMAN",
		"SEARCH", "SPLIT", "SUBSTITUTE",
		"T", "TEXT", "TRIM",
		"UNICHAR", "UNICODE", "UPPER",
		"VALUE",
		"MD5",
		"NUMERAL",
		"ISERR", "ISERROR", "IFERROR",
		"POISSON",
		"LOOKUP",
		"VLOOKUP"
    ],

    /**
     * get number
     * @param  {Number|String} num
     * @returns {Number}
     */
    number: function (num) {
      switch (typeof num) {
        case 'number':
          return num;
        case 'string':
          if (!isNaN(num)) {
            return num.indexOf('.') > -1 ? parseFloat(num) : parseInt(num, 10);
          }
		  if (!num) {
			return 0;
		  }
      }

      return num;
    },

    /**
     * get string
     * @param {Number|String} str
     * @returns {string}
     */
    string: function (str) {
      return str.substring(1, str.length - 1);
    },

    /**
     * invert number
     * @param num
     * @returns {Number}
     */
    numberInverted: function (num) {
      return this.number(num) * (-1);
    },

    /**
     * match special operation
     * @param {String} type
     * @param {String} exp1
     * @param {String} exp2
     * @returns {*}
     */
    specialMatch: function (type, exp1, exp2) {
      var result;

      switch (type) {
        case '&':
          result = exp1.toString() + exp2.toString();
          break;
      }
      return result;
    },

    /**
     * match logic operation
     * @param {String} type
     * @param {String|Number} exp1
     * @param {String|Number} exp2
     * @returns {Boolean} result
     */
    logicMatch: function (type, exp1, exp2) {
      var result;

      switch (type) {
        case '=':
          result = (exp1 === exp2);
          break;

        case '>':
          result = (exp1 > exp2);
          break;

        case '<':
          result = (exp1 < exp2);
          break;

        case '>=':
          result = (exp1 >= exp2);
          break;

        case '<=':
          result = (exp1 === exp2);
          break;

        case '<>':
          result = (exp1 != exp2);
          break;

        case 'NOT':
          result = (exp1 != exp2);
          break;
      }

      return result;
    },

    /**
     * match math operation
     * @param {String} type
     * @param {Number} number1
     * @param {Number} number2
     * @returns {*}
     */
    mathMatch: function (type, number1, number2) {
      var result;
	  var moment1 = null;
	  var moment2 = null;

      number1 = helper.number(number1);
      number2 = helper.number(number2);
      if (isNaN(number1) || isNaN(number2)) {

        if (number1[0] === '=' || number2[0] === '=') {
          throw Error('NEED_UPDATE');
        }

		if (isNaN(number1)) {
			moment1 = moment(number1, window.supsystic.Tables._dateFormat);
			if(moment1 && moment1._pf && moment1._pf.empty) {
				moment1 = null;
				number1 = 0;
			}
        }
        if (isNaN(number2)) {
			moment2 = moment(number2, window.supsystic.Tables._dateFormat);
			if(moment2 && moment2._pf && moment2._pf.empty) {
				moment2 = null;
				number2 = 0;
			}
        }
      }
      switch (type) {
        case '+':
			if(moment1 || moment2) {
				if(moment1 && moment2) {
					throw Error('VALUE');
				} else if(moment1 && !moment2) {
					result = moment1.add(number2, 'days').format(window.supsystic.Tables._dateFormat);
				} else if(!moment1 && moment2) {
					result = moment2.add(number1, 'days').format(window.supsystic.Tables._dateFormat);
				}
			} else {
				result = number1 + number2;
			}
          break;
        case '-':
			if(moment1 || moment2) {
				if(moment1 && moment2) {
					result = moment1.diff(moment2, 'days');
				} else if(moment1 && !moment2) {
					result = moment1.add(-number2, 'days').format(window.supsystic.Tables._dateFormat);
				} else if(!moment1 && moment2) {
					throw Error('VALUE');
				}
			} else {
				result = number1 - number2;
			}
          break;
        case '/':
			if(moment1 || moment2) {
				throw Error('VALUE');
			} else {
				result = number1 / number2;
				if (result == Infinity) {
					throw Error('DIV_ZERO');
				} else if (isNaN(result)) {
					throw Error('VALUE');
				}
			}
          break;
        case '*':
			if(moment1 || moment2) {
				throw Error('VALUE');
			} else {
				result = number1 * number2;
			}
          break;
        case '^':
			if(moment1 || moment2) {
				throw Error('VALUE');
			} else {
				result = Math.pow(number1, number2);
			}
          break;
      }

      return result;
    },

    /**
     * call function from formula
     * @param {String} fn
     * @param {Array} args
     * @returns {*}
     */
    callFunction: function (fn, args) {
      fn = fn.toUpperCase();
      args = args || [];

      if (instance.helper.SUPPORTED_FORMULAS.indexOf(fn) > -1) {
        if (instance.formulas[fn]) {
          return instance.formulas[fn].apply(this, args);
        }
      }

      throw Error('NAME');
    },

    /**
     * get variable from formula
     * @param {Array} args
     * @returns {*}
     */
    callVariable: function (args) {
      args = args || [];
      var str = args[0];

      if (str) {
        str = str.toUpperCase();
        if (instance.formulas[str]) {
          return ((typeof instance.formulas[str] === 'function') ? instance.formulas[str].apply(this, args) : instance.formulas[str]);
        }
      }

      throw Error('NAME');
    },

    /**
     * Get cell value
     * @param {String} cell => A1 AA1
     * @returns {*}
     */
    cellValue: function (cell) {
      var isEditorPagination = typeof g_stbPagination != 'undefined' && g_stbPagination && !(this instanceof HTMLElement),
		  value,
          fnCellValue = instance.custom.cellValue,
          element = this,
		  cellCoords = instance.utils.cellCoords(cell),
		  item = instance.matrix.getItem(isEditorPagination ? instance.utils.translateCellCoords({row: cellCoords.row - window.editor.pageStart, col: cellCoords.col}) : cell);

      // check if custom cellValue fn exists
      if (instance.utils.isFunction(fnCellValue)) {

        var cellId = instance.utils.translateCellCoords({row: element.row, col: element.col});

        // get value
        value = item ? item.value : (isEditorPagination ? window.editor.bufferData[cellCoords.row][cellCoords.col] : fnCellValue(cellCoords.row, cellCoords.col));

        if (instance.utils.isNull(value)) {
          value = 0;
        }

        if (cellId) {
          //update dependencies
          instance.matrix.updateItem(cellId, {deps: [cell]});
        }

      } else {
        // get value
        if (item) {
          value = item.value;
        } else {
          element = document.getElementById(cell);
          if (element) {
            value = element.value;
          }
        }

        // Get custom value
        if (!value) {
          element = rootElement.querySelector('[data-cell-id=' + cell + ']');

          var originalValue = element.getAttribute('data-original-value');
          if (originalValue !== undefined) {
            value = originalValue;
          } else {
            value = element.innerText || element.textContent;
          }
        }

        //update dependencies
        instance.matrix.updateElementItem(element, {deps: [cell]});
      }

      // check references error
      if (item && item.deps) {
        if (item.deps.indexOf(cellId) !== -1) {
          throw Error('REF');
        }
      }

      // check if any error occurs
      if (item && item.error) {
        throw Error(item.error);
      }

      // return value if is set
      if (instance.utils.isSet(value)) {
        var result = instance.helper.number(value);

        return !isNaN(result) ? result : value;
      }

      // cell is not available
      throw Error('NOT_AVAILABLE');
    },

    /**
     * Get cell range values
     * @param {String} start cell A1
     * @param {String} end cell B3
     * @returns {Array}
     */
    cellRangeValue: function (start, end) {
      var fnCellValue = instance.custom.cellValue,
          coordsStart = instance.utils.cellCoords(start),
          coordsEnd = instance.utils.cellCoords(end),
          element = this;

      // iterate cells to get values and indexes
      var cells = instance.utils.iterateCells.call(this, coordsStart, coordsEnd),
          result = [];

      // check if custom cellValue fn exists
      if (instance.utils.isFunction(fnCellValue)) {

        var cellId = instance.utils.translateCellCoords({row: element.row, col: element.col});

        //update dependencies
        instance.matrix.updateItem(cellId, {deps: cells.index});

      } else {

        //update dependencies
        instance.matrix.updateElementItem(element, {deps: cells.index});
      }

      result.push(cells.value);
      return result;
    },

    /**
     * Get fixed cell value
     * @param {String} id
     * @returns {*}
     */
    fixedCellValue: function (id) {
      id = id.replace(/\$/g, '');
      return instance.helper.cellValue.call(this, id);
    },

    /**
     * Get fixed cell range values
     * @param {String} start
     * @param {String} end
     * @returns {Array}
     */
    fixedCellRangeValue: function (start, end) {
      start = start.replace(/\$/g, '');
      end = end.replace(/\$/g, '');

      return instance.helper.cellRangeValue.call(this, start, end);
    },

	/**
	 * Unescape HTML in the selectsd cells for formulas result.
	 * @param $table
	 */
	unescapeHTML: function($table) {
		$table = $table instanceof jQuery ? $table : jQuery($table);
		$table.find('.unescapeHTML').each(function() {
			var cell = jQuery(this),
				cellContent = cell.html().replace(/&lt;/g, '<').replace(/&gt;/g, '>').replace(/&quot;/g, '"').replace(/&amp;/g, '&');

			cell.html(cellContent);
		});
	}
  };

  /**
   * parse input string using parser
   * @returns {Object} {{error: *, result: *}}
   * @param formula
   * @param element
   */
  var parse = function (formula, element) {
	formula = window.supsystic.Tables.prepareFormulaToParse(formula);	// fix of case sensitive for cells' indexes and formulas' names
	window.supsystic.Tables._currentFormula = formula;					// to calculate custom supsystic formulas
	window.supsystic.Tables._dateFormat = '';
	window.supsystic.Tables._timeFormat = '';

	if(SDT_DATA && SDT_DATA.isAdmin && typeof element.row != 'undefined' && typeof element.col != 'undefined') {
		var cellMeta = window.editor.getCellMeta(element.row, element.col);

		window.supsystic.Tables._dateFormat = cellMeta && cellMeta.dateFormat
			? cellMeta.dateFormat
			: jQuery('#editor-set-date-format').val();
		window.supsystic.Tables._timeFormat = cellMeta && cellMeta.formatType == "time_duration"
			? cellMeta.format
			: jQuery('#editor-set-time-duration-format').val();
	} else {
		var elem = jQuery(element);

		window.supsystic.Tables._dateFormat = elem.data('cell-format') || elem.parents('.supsystic-table:first').data('date-format');
		window.supsystic.Tables._timeFormat = elem.data('cell-format') || elem.parents('.supsystic-table:first').data('time-format');
	}

    var result = null,
        error = null;

    try {

      parser.setObj(element);
      result = parser.parse(formula);
      var id;

      if (element instanceof HTMLElement) {
        id = element.getAttribute('data-cell-id');
      } else if (element && element.id) {
        id = element.id;
      }

      var deps = instance.matrix.getDependencies(id);

      if (deps.indexOf(id) !== -1) {
        result = null;

        deps.forEach(function (id) {
          instance.matrix.updateItem(id, {value: null, error: Exception.get('REF')});
        });

        throw Error('REF');
      }

      if(!error && result === 0) {
        result = "0";
      }

    } catch (ex) {
	  // Formulas errors!!!
	  //console.log(ex);
	  var message = Exception.get(ex.message);

      if (message) {
        error = message;
      } else {
        error = Exception.get('ERROR');
      }

      //console.debug(ex.prop);
      //debugger;
      //error = ex.message;
      //error = Exception.get('ERROR');
    }

    return {
      error: error,
      result: result
    }
  };

  /**
   * initial method, create formulas, parser and matrix objects
   */
  var init = function () {
    instance = this;
    parser = new FormulaParser(instance);

    instance.formulas = Formula;
	instance.formulas.POISSON = function(x, mean, cumulative) {
		return instance.formulas.POISSONDIST(x, mean, cumulative);
	};
	instance.formulas.LOOKUP = function(lookup_value, lookup_vector, result_vector) {
		var lookupRows, lookupColumns, l,r,k, resultRows, resultColumns, key1, key2, dataValue1, dataValue2;

		result_vector = (typeof(result_vector[0]) == 'object' ? result_vector[0] : result_vector) || null;
		lookup_vector = typeof(lookup_vector[0]) == 'object' ? lookup_vector[0] : lookup_vector;
		lookup_value = supsysticFlattenSingleValue(lookup_value);

		if (typeof(lookup_vector) != 'object') {
			return Exception.get('NOT_AVAILABLE');
		}

		lookupRows = lookup_vector.length;
		l = Object.keys(lookup_vector);
		l = l.shift();
		lookupColumns = lookup_vector[l].length;

		if (((lookupRows == 1) && (lookupColumns > 1)) || ((lookupRows == 2) && (lookupColumns != 2))) {
			lookup_vector = supsysticTranspose(lookup_vector);
			lookupRows = lookup_vector.length;
			l = Object.keys(lookup_vector);
			lookupColumns = lookup_vector[l.shift()].length;
		}
		if (result_vector == null) {
			result_vector = lookup_vector;
		}

		resultRows = result_vector.length;
		l = Object.keys(result_vector);
		l = l.shift();
		resultColumns = result_vector[l].length;

		if (((resultRows == 1) && (resultColumns > 1)) || ((resultRows == 2) && (resultColumns != 2))) {
			result_vector = supsysticTranspose(result_vector);
			resultRows = result_vector.length;
			r = Object.keys(result_vector);
			resultColumns = result_vector[r.shift()].length;
		}
		if (lookupRows == 2) {
			result_vector = lookup_vector.pop();
			lookup_vector = lookup_vector.shift();
		}
		if (lookupColumns != 2) {
			for(var v in lookup_vector) {
				if (typeof(lookup_vector[v]) == 'object') {
					k = Object.keys(lookup_vector[v]);
					key1 = key2 = k.shift();
					key2++;
					dataValue1 = lookup_vector[v][key1];
				} else {
					key1 = 0;
					key2 = 1;
					dataValue1 = lookup_vector[v];
				}
				dataValue2 = result_vector.shift();

				if (typeof(dataValue2) == 'object') {
					dataValue2 = dataValue2.shift();
				}
				lookup_vector[v] = {};
				lookup_vector[v][key1] = dataValue1;
				lookup_vector[v][key2] = dataValue2;
			}
		}

		return instance.formulas.VLOOKUP(lookup_value, lookup_vector, 2, false);
	};
	instance.formulas.VLOOKUP = function(lookup_value, lookup_array, index_number, not_exact_match) {
		var f, firstRow, firstColumn, returnColumn, columnKeys, rowNumber = false, rowValue = false;

		not_exact_match = typeof(not_exact_match) != 'undefined' ? not_exact_match : true;
		lookup_value = supsysticFlattenSingleValue(lookup_value);
		index_number = supsysticFlattenSingleValue(index_number);
		not_exact_match = supsysticFlattenSingleValue(not_exact_match);

		// index_number must be greater than or equal to 1
		if (index_number < 1) {
			return Exception.get('VALUE');
		}

		// index_number must be less than or equal to the number of columns in lookup_array
		if (typeof(lookup_array) != 'object' || !lookup_array.length) {
			return Exception.get('REF');
		} else {
			f = Object.keys(lookup_array);
			firstRow = f.pop();

			if (typeof(lookup_array[firstRow]) != 'object' || index_number > lookup_array[firstRow].length) {
				return Exception.get('REF');
			} else {
				columnKeys = Object.keys(lookup_array[firstRow]);
				returnColumn = columnKeys[--index_number];
				firstColumn = columnKeys.shift();
			}
		}
		if (!not_exact_match) {
			lookup_array.sort(supsysticVlookupSort);
		}
		for(var i in lookup_array) {
			if ((!isNaN(lookup_value) && !isNaN(lookup_array[i][firstColumn]) && lookup_array[i][firstColumn] > lookup_value)
				|| (isNaN(lookup_value) && isNaN(lookup_array[i][firstColumn]) && lookup_array[i][firstColumn].toLowerCase() > lookup_value.toLowerCase())
			) {
				break;
			}
			rowNumber = i;
			rowValue = lookup_array[i][firstColumn];
		}
		if (rowNumber !== false) {
			if (!not_exact_match && rowValue != lookup_value) {
				// if an exact match is required, we have what we need to return an appropriate response
				return Exception.get('NOT_AVAILABLE');
			} else {
				// otherwise return the appropriate value
				return lookup_array[rowNumber][returnColumn];
			}
		}

		return Exception.get('NOT_AVAILABLE');
	};
    instance.matrix = new Matrix();

    instance.custom = {};

    if (rootElement) {
      instance.matrix.scan();
	  helper.unescapeHTML(rootElement);
    }
  };

  return {
    init: init,
    version: version,
    utils: utils,
    helper: helper,
    parse: parse
  };

});

// Transpose the matrix
function supsysticTranspose(matrixData) {
	var returnMatrix = [],
		column = 0;

	if (typeof(matrixData) != 'object') {
		matrixData = [[matrixData]];
	}

	for(var i in matrixData) {
		var row = 0;

		for(var j in matrixData[i]) {
			returnMatrix[row] = returnMatrix[row] ? returnMatrix[row] : [];
			returnMatrix[row][column] = matrixData[i][j];
			++row;
		}
		++column;
	}
	return returnMatrix;
}

function supsysticFlattenSingleValue(value) {
	value = value ? value : '';

	while(typeof(value) == 'object') {
		value = value.pop();
	}

	return value;
}

function supsysticVlookupSort(a, b) {
	var aLower, bLower;

	if ((aLower = a[0].toString().toLowerCase()) == (bLower = b[0].toString().toLowerCase())) {
		return 0;
	}
	return (aLower < bLower) ? -1 : 1;
}
