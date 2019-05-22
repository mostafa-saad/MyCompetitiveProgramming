if(typeof(SDT_DATA) == 'undefined') {
    var SDT_DATA = {};
}
var g_stbServerSideProcessing = false;

(function (vendor, $, window) {

    var appName = 'Tables';
    var dataTableInstances = [];
    var ruleJSInstances = [];

    if (!(appName in vendor)) {
        vendor[appName] = {};

        vendor[appName].getAppName = (function() {
            return appName;
        });

        vendor[appName].getParameterByName = (function(name) {
            name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");

            var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
                results = regex.exec(location.search);

            return results === null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
        });

        vendor[appName].replaceParameterByName = (function(url, paramName, paramValue) {
            var pattern = new RegExp('\\b('+paramName+'=).*?(&|$)');
            if (url.search(pattern) >= 0) {
                return url.replace(pattern,'$1' + paramValue + '$2');
            }
            return url + (url.indexOf('?')>0 ? '&' : '?') + paramName + '=' + paramValue;
        });

        vendor[appName].getAllTableInstances = (function() {
            return dataTableInstances;
        });

		vendor[appName].removeAllTableInstances = (function() {
			dataTableInstances = [];
		});

        vendor[appName].setTableInstance = (function(instance) {
            dataTableInstances.push(instance);
        });

        vendor[appName].getTableInstanceById = (function(id) {
            var allTables = this.getAllTableInstances();

            for(var i = 0; i < allTables.length; i++) {
                if(allTables[i].table_id == id) {
                    return allTables[i];
                }
            }
            return false;
        });

        vendor[appName].getTableInstanceByViewId = (function(viewId) {
            var allTables = this.getAllTableInstances();

            for(var i = 0; i < allTables.length; i++) {
                if(allTables[i].table_view_id == viewId) {
                    return allTables[i];
                }
            }
            return false;
        });

        vendor[appName].removeTableInstanceByViewId = (function(viewId) {
            var allTables = this.getAllTableInstances();

            for(var i = 0; i < allTables.length; i++) {
                if(allTables[i].table_view_id == viewId) {
                    allTables.splice(i, 1);
                    return true;
                }
            }
            return false;
        });

        vendor[appName].getAllRuleJSInstances = (function() {
            return ruleJSInstances;
        });

        vendor[appName].setRuleJSInstance = (function(table) {
            var rootElem = table.closest('.supsystic-tables-wrap'),
                viewId = table.data('view-id');

            ruleJSInstances[viewId] = new ruleJS(rootElem.attr('id'));
            return ruleJSInstances[viewId];
        });

        vendor[appName].getRuleJSInstance = (function(table) {
            var allRuleJS = this.getAllRuleJSInstances(),
                viewId = table.data('view-id');

            if(!allRuleJS[viewId]) {
				this.setRuleJSInstance(table);
            }
            return allRuleJS[viewId];
        });

        vendor[appName].request = (function(route, data) {
			if (!$.isPlainObject(route) || !('module' in route) || !('action' in route)) {
				throw new Error('Request route is not specified.');
			}
            if (!$.isPlainObject(data)) {
                data = {};
            }
            if ('action' in data) {
                throw new Error('Reserved field "action" used.');
            }
            data.action = 'supsystic-tables';

			var url = window.ajaxurl ? window.ajaxurl : ajax_obj.ajaxurl,
				deferred = $.Deferred();

			$.post(url, $.extend({}, { route: route }, data))
				.done(function (response, textStatus, jqXHR) {
					if (response.success) {
						deferred.resolve(response, textStatus, jqXHR);
					} else {
						if(data._maxIter) {
							retryAjax(deferred, url, route, data, 1, data._maxIter);
						} else {
							var message = typeof response.message !== 'undefined' ? response.message : 'There are errors during the request.';

							deferred.reject(message, textStatus, jqXHR);
						}
					}
				}).fail(function (jqXHR, textStatus, errorThrown) {
					if(data._maxIter) {
						retryAjax(deferred, url, route, data, 1, data._maxIter);
					} else {
						deferred.reject(errorThrown, textStatus, jqXHR);
					}
				});

			function retryAjax(def, url, route, data, curIter, maxIter) {
				$.post(url, $.extend({}, { route: route }, data))
					.done(function (response, textStatus, jqXHR) {
						if (response.success) {
							def.resolve(response, textStatus, jqXHR);
						} else {
							var message = typeof response.message !== 'undefined' ? response.message : 'There are errors during the request.';

							retryErrorHandler(def, url, route, data, curIter, maxIter, message, textStatus, jqXHR);
						}
					}).fail(function (jqXHR, textStatus, errorThrown) {
						retryErrorHandler(def, url, route, data, curIter, maxIter, errorThrown, textStatus, jqXHR);
					});
			}

			function retryErrorHandler(def, url, route, data, curIter, maxIter, errorThrown, textStatus, jqXHR) {
				curIter++;
				if(curIter < maxIter) {
					retryAjax(def, url, route, data, curIter, maxIter);
				} else {
					def.reject(errorThrown, textStatus, jqXHR);
				}
			}

            return deferred.promise();
        });

        vendor[appName].createSpinner = (function(elem) {
            elem = typeof(elem) != 'undefined' ? elem : false;

            if(elem) {
                var icon = elem.attr('disabled', true).find('.fa');

                if(icon) {
                    icon.data('icon', icon.attr('class'));
                    icon.attr('class', 'fa fa-spinner fa-spin');
                }
            } else {
                return $('<i/>', { class: 'fa fa-spinner fa-spin' });
            }
        });

        vendor[appName].deleteSpinner = (function(elem) {
            var icon = elem.attr('disabled', false).find('.fa');

            if(icon) {
                icon.attr('class', icon.data('icon'));
                icon.data('icon', '');
            }
        });

        vendor[appName].initializeTable = (function(table, callback, finalCallback, reinit, addInstance) {
            reinit = typeof reinit != 'undefined' ? reinit : {};
            addInstance = typeof addInstance != 'undefined' ? addInstance : true;

            var self = this,
				$table = (table instanceof $ ? table : $(table)),
                features = $table.data('features'),
                config = {},
                responsiveMode = $table.data('responsive-mode'),
                searchingSettings = $table.data('searching-settings'),
                tableInstance = {},
                defaultFeatures = {
                    autoWidth:  false,
                    info:       false,
                    ordering:   false,
                    paging:     false,
                    responsive: false,
                    searching:  false,
                    stateSave:  false,
                    api: 		true,
                    retrieve:   true,  
                    initComplete: callback,
                    headerCallback: function( thead, data, start, end, display ) {
                        $(thead).closest('thead').find('th').each(function() {
							self.setStylesToCell(this);
                        });
                    },
                    footerCallback: function( tfoot, data, start, end, display ) {
                        $(tfoot).closest('tfoot').find('th').each(function() {
							self.setStylesToCell(this);
                        });
                    }
                };
            if($table.data('server-side-processing') && $table.data('server-side-processing') == 'on') {
                g_stbServerSideProcessing = true;
            }

			// Fix of correct displaying of tables with hidden rows / columns for tables without headers.
			if (!$table.data('head')) {
				$table.find('thead th').each(function(iter, item) {
					var th = $(this),
						itemIndex = iter + 1,
						hidden = true;

					$table.find('tbody td:nth-child(' + itemIndex + ')').each(function() {
						if(!$(this).hasClass('invisibleCell')) {
							hidden = false;
							return false; // stop current .each() iteration
						}
					});
					if(hidden) {
						th.addClass('invisibleCell');
					}
				});
			}

			// Fix for searching by merged cells
			$table.find('tbody td[data-colspan], tbody td[data-rowspan]').each(function(index, item) {
				var cell = $(item),
					cellData = cell.html();

				// prevent of copy cell data if it contains tags with id attribute - it must be unique on page
				if(!cellData.toString().match(/<.*?id=['|"].*?['|"].*?>/g)) {
					var cellOrValue = cell.data('original-value'),
						cellFormula = cell.data('formula'),
						cellOrder = cell.data('order'),
						table = cell.parents('table:first'),
						colIndex = cell.index(),
						rowIndex = cell.parents('tr:first').index(),
						colspan = cell.data('colspan'),
						rowspan = cell.data('rowspan');

					for(var i = rowIndex + 1; i <= rowIndex + rowspan; i++) {
						for(var j = colIndex + 1; j <= colIndex + colspan; j++) {
							var hiddenCell = table.find('tbody tr:nth-child(' + i + ') td:nth-child(' + j + ')');

							if(hiddenCell.data('hide')) {
								hiddenCell.html(cellData);
								hiddenCell.data('original-value', cellOrValue);
								hiddenCell.attr('data-original-value', cellOrValue);
								hiddenCell.data('order', cellOrder);
								hiddenCell.attr('data-order', cellOrder);
								if(cellFormula) {
									hiddenCell.data('formula', cellFormula);
									hiddenCell.attr('data-formula', cellFormula);
								}
							}
						}
					}
				}
			});

			// Set features
            $.each(features, function () {
                var featureName = this.replace(/[-_]([a-z])/g, function (g) { return g[1].toUpperCase(); });
                config[featureName] = true;
            });
            if (toeInArray('searching', features) != -1 && searchingSettings) {
                if (searchingSettings.minChars > 0 ||
                    searchingSettings.resultOnly ||
                    searchingSettings.strictMatching
                ) {

                    $.fn.dataTable.ext.search.push(function(settings, data) {
                        var $searchInput = $(settings.nTableWrapper).find('.dataTables_filter input'),
                            searchValue = $searchInput.val();

                        if (searchingSettings.resultOnly && searchValue.length === 0) {
                            if (searchingSettings.showTable) {
                                return false;
                            }
                            return false;
                        }
                        if (searchingSettings.strictMatching) {
                            searchValue = $.fn.dataTable.util.escapeRegex(searchValue);
                            var regExp = new RegExp('^' + searchValue, 'i');

                            for (var i = 0; i < data.length; i++) {
                                var words = data[i].replace(/\s\s+/g, ' ').split(' ');

                                for (var j = 0; j < words.length; j++) {
                                    if (words[j].match(regExp)) {
                                        return true;
                                    }
                                }
                            }
                            return false;
                        } else {
                            return data.join(' ').toLowerCase().indexOf(searchValue.toLowerCase()) !== -1
                        }
                    });
                    $table.on('init.dt', function (event, settings)  {
                        if (!settings) {
                            return;
                        }

                        var $tableWrapper = $(settings.nTableWrapper),
                            $tableSearchInput = $tableWrapper.find('.dataTables_filter input'),
                            $customInput = $tableSearchInput.clone();

                        $tableSearchInput.replaceWith($customInput);

                        $customInput.on('input change', function() {
                            if (!searchingSettings.showTable) {
                                if (searchingSettings.resultOnly && searchingSettings.minChars && (this.value.length < searchingSettings.minChars || !this.value.length)) {
                                    $table.hide();
                                    $table.parent().find('.dataTables_paginate').hide();
                                } else {
                                    $table.show();
                                    $table.parent().find('.dataTables_paginate').show();
                                }
                            }
                            if (searchingSettings.minChars && (this.value.length < searchingSettings.minChars && this.value.length !== 0)) {
                                event.preventDefault();
                                return false;
                            }
                            $table.api().draw();
                        });

                        if (searchingSettings.resultOnly && !searchingSettings.showTable) {
                            $table.hide();
                            $table.parent().find('.dataTables_paginate').hide();
                        }
                    });
                }
				if (searchingSettings.columnSearch && $table.find('tfoot').find('input').length == 0) {
					var tds = $table.find('thead tr:first').find('th'),
						ths = '';

					for (var i = 0; i < tds.length; i++) {
                        ths += '<th><input type="text" /></th>';
					}
					if (ths.length > 0) {
						if($table.find('tfoot').length == 0) {
							$table.append($('<tfoot>'));
						}
						$table.find('tfoot').append('<tr>' + ths + '</tr>');
					}
				}
            }
            if (toeInArray('ordering', features) != -1) {
                var sortingEnable = ['_all'],
                    sortingDisable = [],
                    aaSorting = [],
                    multipleSorting = $table.data('multiple-sorting'),
                    disableSorting = $table.data('disable-sorting');

                if (!$table.data('head')) {
                    sortingDisable = ['_all'];
                }
                if(disableSorting && disableSorting.length) {
                    sortingDisable = disableSorting;
                }
                if (multipleSorting && multipleSorting.length) {
                    aaSorting = multipleSorting;
                } else {
                    var columnsCount = $table.find('tr:first th').length,
                        sortColumn = $table.data('sort-column') || 0,
                        sortOrder = $table.data('sort-order') || 'asc',
                        columnNumber = sortColumn - 1;

                    if(columnNumber >= 0 && columnNumber < columnsCount) {
                        aaSorting.push([columnNumber, sortOrder]);
                    }
                }
                config.aoColumnDefs = [
                    { type: 'natural-nohtml-ci', targets: '_all' },
                    { "sortable": false, "targets": sortingDisable },
                    { "sortable": true, "targets": sortingEnable }
                ];
                config.aaSorting = aaSorting;
            }
            if ($table.data('pagination-length')) {
                var paginationLength = String($table.data('pagination-length'));

				config.aLengthMenu = [];
				config.aLengthMenu.push(paginationLength.replace('All', -1).split(',').map(Number));
				config.aLengthMenu.push(paginationLength.split(','));
            }
            if ($table.data('auto-index') && $table.data('auto-index') !== 'off') {
                $table.on('draw.dt', function() {
                    $table.api().column(0).nodes().each(function (cell, i) {
                        cell.innerHTML = i + 1;
                    });
                });
            }

			// Set responsive mode
            if (responsiveMode == 0) {
                // Responsive Mode: Standart Responsive Mode
                var labelStyles = '<style>',
                    id = '#' + $table.attr('id');

                // Add header data to each response row
                $table.find('thead th').each(function(index, el) {
                    labelStyles += id + '.oneColumnWithLabels td:nth-of-type(' + (index + 1) + '):before { content: "' + $(this).text() + '"; }';
                });
                labelStyles += '</style>';
                $table.append(labelStyles);

                $(window).on('resize', $table, function(event) {
                    event.preventDefault();
                    clearTimeout($table.data('resizeTimer'));

                    $table.data('resizeTimer', setTimeout(function() {
                        $table.removeClass('oneColumn oneColumnWithLabels');
                        var tableWidth = $table.width(),
                            wrapperWidth = $table.closest('.supsystic-tables-wrap').width();
                        if (tableWidth > wrapperWidth) {
                            $table.addClass('oneColumn');

                            if ($table.data('head') == 'on') {
                                $table.addClass('oneColumnWithLabels');
                            }
                        }
                    }, 150));
                    if(g_stbServerSideProcessing) {
                        $table.find('td').each(function() {
                            $(this).css({'width': '','min-width': ''});
                        });
                    }
                }).trigger('resize');
            } else if (responsiveMode === 1) {
                // Responsive Mode: Automatic Column Hiding
                config.responsive = {
                    details: {
                        renderer: function (api, rowIdx, columns) {
                            var $table = $(api.table().node()),
                                $subTable = $('<table/>');

                            $.each(columns, function (i, col) {
                                if (col.hidden) {
                                    var $cell = $(api.cell(col.rowIndex, col.columnIndex).node()).clone(),
                                        markup = '<tr data-dt-row="'+col.rowIndex+'" data-dt-column="'+col.columnIndex+'">';
                                    if ($table.data('head') == 'on') {
                                        var $headerContent = $(api.table().header()).find('th').eq(col.columnIndex).html();
                                        markup += '<td>';
                                        if ($headerContent) {
                                            markup += $headerContent;
                                        }
                                        markup += '</td>';
                                    }
                                    markup += '</tr>';
                                    $cell.after(
                                        $('<td>')
                                            .addClass('collapsed-cell-holder')
                                            .attr('data-cell-row', col.rowIndex)
                                            .attr('data-cell-column', col.columnIndex)
                                            .hide()
                                    );
                                    $subTable.append($(markup).append($cell.addClass('collapsed').show()));
                                }
                            });
                            return $subTable.is(':empty') ? false : $subTable;
                        }
                    }
                };
                $table.on('responsive-resize.dt', function(event, api, columns) {
					if(typeof api == 'undefined' || typeof columns == 'undefined') {
						var tbl = $(this),
							instance = vendor[appName].getTableInstanceById(tbl.data('id'));

						if(instance) {
							api = typeof api != 'undefined' ? api : instance.api();
							columns = typeof columns != 'undefined' ? columns : instance.api().columns();
						}
					}
                    if ($table.width() > $table.parent().width()) {
                        api.responsive.recalc();
                        return;
                    }
                    for (var i = 0, len = columns.length; i < len; i++) {
                        if (columns[i]) {
							$table.find('tr > td.collapsed-cell-holder[data-cell-column="' + i + '"]').each(function(index, el) {
                                var $this = $(this);
                                var $cell = $(api.cell(
                                    $this.data('cell-row'),
                                    $this.data('cell-column')
                                ).node());

                                if ($cell.hasClass('collapsed')) {
                                    $cell.removeClass('collapsed');
                                    $this.replaceWith($cell);
                                }
                            });
                        }
                    }
                });
            } else if (responsiveMode === 2) {
                // Responsive Mode: Horizontal Scroll
                config.scrollX = true;
            }
            if(responsiveMode === 2 || responsiveMode === 3) {
                // Responsive Mode: 2 - Horizontal Scroll, 3 - Disable Responsivity
                var fixedHead = $table.data('head') && $table.data('fixed-head'),
                    fixedFoot = $table.data('foot') && $table.data('fixed-foot'),
                    fixedLeft = $table.data('fixed-left'),
                    fixedRight = $table.data('fixed-right');

                // TODO: correct the code to set fixed header and fixed footer in the standard way
                // TODO: https://datatables.net/extensions/fixedheader/#Features
                //config.fixedHeader = {
                //	header: false,
                //	footer: false
                //};
                //if (fixedHead) {
                //	config.fixedHeader.header = true;
                //}
                //if (fixedFoot) {
                //	config.fixedHeader.footer = true;
                //}
                if(fixedHead || fixedFoot) {
                    config.scrollY = $table.data('fixed-height');
                    config.scrollCollapse = true;
                }
                if ($table.data('fixed-cols')) {
                    config.fixedColumns = {
                        leftColumns: fixedLeft ? parseInt(fixedLeft) : 0,
                        rightColumns: fixedRight ? parseInt(fixedRight) : 0
                    };
                    config.scrollX = true;
                }
            }

            // Add translation
            var langData = typeof g_stbTblLangData != 'undefined' ? JSON.parse(g_stbTblLangData) : $table.data('translation'),
                translation = langData || {},
                override = $table.data('override');

            if(typeof translation != 'object') {
                translation = {};	// for just to be sure that it is object
            }
            $.each(override, function(key, value) {
                if(value.length) {
                    translation[key] = value;
                    // We need to support old DT format, cuz some languages use it
                    translation['s' + key.charAt(0).toUpperCase() + key.substr(1)] = value;
                }
            });
            config.language = translation;

            var ajaxSource = {};

            if(g_stbServerSideProcessing) {
                var route = {"action" : "getPageRows", "module": "tables"},
                    loadedRows = [],
                    loadedCells = [],
                    headerRowsCount = ($table.data('head') == 'on' ? $table.data('head-rows-count') : 0),
                    footerRowsCount = ($table.data('foot') == 'on' ? $table.data('foot-custom-rows-count') : 0);
                ajaxSource = {
                    processing: true,
                    serverSide: true,
                    ajax: {
                        url: window.ajaxurl ? window.ajaxurl : ajax_obj.ajaxurl,
                        type: 'POST',
                        data: {
                            action: "supsystic-tables",
                            route: route,
                            id: $table.data('id'),
                            searchParams: searchingSettings,
                            searchValue: function () {
                                var input = $('#' + $table.attr('id') + '_filter.dataTables_filter').find('input');
                                return (input.length ? input.val() : '');
                            },
                            header: headerRowsCount,
                            footer: footerRowsCount},
                        dataFilter: function(data){
                            var json = jQuery.parseJSON(data),
                                rows = $(json.rows).find('tr'),
                                aData = [];

                            loadedRows = [];
                            loadedCells = [];
                            for(var i = 0; i < rows.length; i++) {
                                var row = rows[i];
                                loadedRows.push(row.attributes);
                                var cells = $(row).find('td'),
                                    attrs = [],
                                    vals = [];
                                for(var j = 0; j < cells.length; j++) {
                                    var cell = cells[j];
                                    attrs.push(cell.attributes);
                                    vals.push(cell.innerHTML);
                                }
                                loadedCells.push(attrs);
                                aData.push(vals);
                            }
                            json.rows = '';
                            json.data = aData;
                            return JSON.stringify(json);
                        }
                    },
                    createdRow: function (row, data, dataIndex) {
                        if(typeof(loadedRows[dataIndex]) != 'undefined') {
                            $(loadedRows[dataIndex]).each(function () {
                                $(row).attr(this.name, this.value);
                            });
                        }
                    }
                }
                if(typeof(config.aoColumnDefs) == 'undefined') {
                    config.aoColumnDefs = [];
                }
                config.aoColumnDefs.push({
                    targets: '_all',
                    cellType: 'td',
                    createdCell: function (td, cellData, rowData, row, col) {
                        if(typeof(loadedCells[row][col]) != 'undefined') {
                            var rowspan = 1,
                                colspan = 1;
                            $(loadedCells[row][col]).each(function () {
                                if (this.name == 'data-rowspan' && this.value > 1) {
                                    rowspan = this.value;
                                }
                                if(this.name == 'data-colspan' && this.value > 1) {
                                    colspan = this.value;
                                }
                            });
                            if(rowspan > 1 || colspan > 1) {
                                var stopRow = row + parseInt(rowspan),
                                    stopCol = col + parseInt(colspan),
                                    startRow = colspan > 1 ? row : row + 1,
                                    hide;
                                if(stopRow >= loadedCells.length) {
                                    stopRow = loadedCells.length;
                                }
                                if(stopCol >= loadedCells[row].length) {
                                    stopCol = loadedCells[row].length;
                                }

                                for(i = startRow; i < stopRow; i++) {
                                    if(i > row) {
                                        hide = document.createAttribute('data-hide');
                                        hide.value = 'true';
                                        loadedCells[i][col].setNamedItem(hide);
                                    }
                                    for(j = col + 1; j < stopCol; j++) {
                                        hide = document.createAttribute('data-hide');
                                        hide.value = 'true';
                                        loadedCells[i][j].setNamedItem(hide);
                                    }
                                }
                            }
                            $(loadedCells[row][col]).each(function () {
                                if(this.name != 'data-formula') {
                                    $(td).attr(this.name, this.value);
                                }
                            });
                        }
                    } 
                });
            }

			$table.trigger('beforeInitializeTable', $table);
            tableInstance = $table.dataTable($.extend({}, defaultFeatures, config, ajaxSource, reinit));
            tableInstance.table_id = $table.data('id');
            tableInstance.table_view_id = $table.data('view-id');
			tableInstance.fnFakeRowspan();
			self._checkOnClickPopups($table);

            if(g_stbServerSideProcessing) {
                $('.dataTables_processing').css('z-index', '10');
            } else {
                self.setColumnSearch($table);
            }  

            if(addInstance) {
               this.setTableInstance(tableInstance);
            }
			return typeof finalCallback  == "function" ? finalCallback(tableInstance) : tableInstance;
        });

        /** Callback for displaying table after initializing
         * @param {object} settings - DataTables settings object
         * @param {object} json - JSON data retrieved from the server if the ajax option was set. Otherwise undefined.
         */
        vendor[appName].showTable = (function(settings, json) {
            var self = vendor[appName],	// it is callback so "this" does not equal vendor[appName] object
				$table = this instanceof $ ? this : settings,	// for compatibility with old pro versions
                $tableWrap = $table.closest('.supsystic-tables-wrap'),
                afterTableLoadedScriptString = $table.attr('data-after-table-loaded-script'),
                _ruleJS = self.setRuleJSInstance($table),
                responsiveMode = $table.data('responsive-mode'),
                fixedHeader = $table.data('fixed-head') == 'on',
                fixedFooter = $table.data('fixed-foot') == 'on',
                fixedColumns = $table.data('fixed-right') > 0 || $table.data('fixed-left') > 0,
                viewId = $table.data('view-id');

			// Apply custom CSS styles, which have been set through the table editor
			$table.find('th, td').each(function () {
				self.setStylesToCell(this);
			});
			$table.bind('column-visibility.dt draw.dt', function (e) {
				$(this).find('th, td').each(function () {
					self.setStylesToCell(this);
				});
			});

			// Remove sorting visual elements from the tags if there is no header on table
            if (!$table.data('head')) {
                $table.find('th').removeClass('sorting sorting_asc sorting_desc sorting_disabled');
            }

            // Calculate formulas
            _ruleJS.init();

            // Set formats
			self.formatDataAtTable($table, true);

            $(document).on('click', '.paginate_button', function () {
				setTimeout(function() {
                    _ruleJS.init();
					self.formatDataAtTable($table, true);
				}, 50);
            });

            // Show comments on tap
            if ('ontouchstart' in window || navigator.msMaxTouchPoints) {
                $table.find('td, th').on('click', function(e) {
                    var title = $(this).attr('title');

                    if (title) {
                        var div = $('<div style="' +
                            'display:none;' +
                            'position:absolute;' +
                            'border-radius:6px;' +
                            'background-color:#999;' +
                            'color:white;' +
                            'padding:7px;"/>');

                        div.text(title)
                            .appendTo('body')
                            .css('top', (e.pageY - 70) + 'px')
                            .css('left', (e.pageX + 20) + 'px')
                            .fadeIn('slow');

                        setTimeout(function() {
                            div.fadeOut();
                        }, 1200);
                    }
                });
            }

            // Frontend fields
            if (typeof(self.createEditableFields) == 'function') {	// for compatibility with old pro versions
                var $editableFields = $tableWrap.find('.editable'),
                    $selectableFields = $tableWrap.find('.selectable'),
                    $tableId = $table.data('id'),
                    useEditableFields = typeof(useEdit) != 'undefined' && typeof(useEdit[$tableId]) != 'undefined'
                        ? useEdit[$tableId]
                        : false;

                if(useEditableFields || (SDT_DATA.isAdmin && SDT_DATA.isPro)) {
                    if (typeof(self.setFrontendFields) == 'function') {
						self.setFrontendFields($table);
                    } else if (typeof(self.setAllFields) == 'function') {
                        self.setAllFields($table, $editableFields, $selectableFields);
                    } else {
                        self.createEditableFields($table, $editableFields);
                    }
                    if(typeof(self.setImgLightbox) == 'function'){
                        self.setImgLightbox($table);
                    }
					$table.on('init.dt', function() {
						$table.on('responsive-resize.dt responsive-display.dt draw.dt', function() {
							$editableFields.off('click.sup');	// for compatibility with old pro versions
							self.updateAfterRedraw($table);
						});
					});
                }
            }

			// apply page.dt event by change table pagination via select
			var paginationSelect = $tableWrap.find('.dataTables_length select');
			if(paginationSelect.length) {
				paginationSelect.on('change', function() {
					$table.trigger('page.dt');
				});
			}

			$table.trigger('beforeShowTable', $table);

            // Show table
            $tableWrap.prev('.supsystic-table-loader').hide();
            $tableWrap.css('visibility', 'visible');

            self.fixSortingForMultipleHeader($table);

            if(responsiveMode === 2 || fixedHeader || fixedFooter) {
                // Responsive Mode: Horizontal Scroll
                $(window).on('resize', $table, function(event) {
                    var tBody = $tableWrap.find('.dataTables_scrollBody'),
                        tBodyTable = tBody.find('.supsystic-table');

                    if(tBody.width() > tBodyTable.width() || $tableWrap.width() > tBodyTable.width()) {
						tBody.width(tBodyTable.width());
						$tableWrap.find('.dataTables_scrollHead, .dataTables_scrollFoot, .dataTables_scrollBody').width(tBodyTable.width() + 1);
					}
                    if( tBodyTable.isHorizontallyScrollable ){
                        tBody.css({'border-bottom' : 'none'});
                    }else{
                        tBody.removeStyle('border-bottom');
                    }
                    if(g_stbServerSideProcessing) {
                        self.getTableInstanceByViewId(viewId).fnAdjustColumnSizing(false);
                    }
                }).trigger('resize');

                // need resize twice to get better frontend view
                var tBody = $tableWrap.find('.dataTables_scrollBody'),
					tBodyTable = tBody.find('.supsystic-table');

                if(tBodyTable.is(":visible")){
                    setTimeout(function() {
                        $(window).trigger('resize');
                    }, 200);
                }
            }
            // Correct width of fixed header / footer
            if(fixedHeader || fixedFooter) {
                $table.api().fixedHeader.adjust();

				var i = 1;
                setTimeout(function() {
					var flag = fixedHeader,
						el = fixedHeader
							? $tableWrap.find('.dataTables_scrollHead table thead tr:first-child th')
							: $tableWrap.find('.dataTables_scrollFoot table tfoot tr:first-child th');

                    el.each(function() {
						var thWidth = $tableWrap.find('.dataTables_scrollBody table tbody tr:first-child td:nth-child('+ i + ')');

						$(this).css({
							'width': thWidth.outerWidth(),
							'min-width': thWidth.outerWidth(),
							'box-sizing': 'border-box'
						});
						if(fixedFooter && flag){
							var footerEl = $tableWrap.find('.dataTables_scrollFoot table tfoot tr:first-child th:nth-child('+ i + ')');
							footerEl.css({
								'width': thWidth.outerWidth(),
								'min-width': thWidth.outerWidth(),
								'box-sizing': 'border-box'
							});
						}
						i++;
					});
				}, 200);
            }

            // Correct width of fixed columns
            if(fixedColumns) {
                $table.api().fixedColumns().relayout();

                var tableCaption = $('.dataTables_scrollHead caption');

                if(tableCaption.length) {
					self._fixTableCaption(tableCaption.height(), viewId, 10);
                }
            }
            /* Fix for Horizontal scroll responsive mode if table has different width for one column in header and body */
            if(!fixedHeader && !fixedFooter && responsiveMode === 2 && toeInArray('auto_width', $table.data('features')) == -1) {
                $tableWrap.find('.dataTables_scrollBody table thead tr:first-child th').each(function() {
                    var tableWidth = $table.width(),
                        tableWrapWidth = $tableWrap.width();

                    if(tableWrapWidth > tableWidth){
                        $tableWrap
                            .find('.dataTables_scrollHeadInner, .dataTables_scrollBody, .dataTables_scrollFootInner')
                            .addClass('fit-content');
                    }
                });
            }

            // Load user custom scripts
            if (afterTableLoadedScriptString !== undefined) {
                afterTableLoadedScriptString = afterTableLoadedScriptString.substring(1, afterTableLoadedScriptString.length - 1);

                var afterTableLoadedScript = b64DecodeUnicode(afterTableLoadedScriptString).replace(/"/g, "'"),
                    executeScript = new Function(afterTableLoadedScript);

                if (typeof executeScript === "function") {
                    setTimeout(function() {
                        executeScript();
                    }, 1000);
                }
            }

            if(g_stbServerSideProcessing) {
                $table.on('draw.dt', function (e) {
                    var searching = $table.data('searching-settings');
                    if(searching && ('columnSearch' in searching) && searching.columnSearch == 'on') {
                        self.setColumnSearch($table);
                    }
                    self.getTableInstanceByViewId(viewId).fnFakeRowspan();
                    if(responsiveMode === 0 || responsiveMode === 2) {
                        $(window).trigger('resize');
                    }
                }).trigger('draw.dt'); 
            }

            function b64DecodeUnicode(str) {
                return decodeURIComponent(Array.prototype.map.call(atob(str), function(c) {
                    return '%' + ('00' + c.charCodeAt(0).toString(16)).slice(-2);
                }).join(''));
            }
        });

        vendor[appName].setColumnSearch = (function(table) {
            var dtable = $('#supsystic-table-' + table.data('id') + '[data-view-id="' + table.data('view-id') + '"]'),
                tfoot = $('#supsystic-table-' + table.data('view-id')).find('div .dataTables_scrollFootInner table '),
                inputs = (tfoot.length == 0 ? dtable.find('tfoot tr:last input') : tfoot.eq(0).find('tfoot tr:last input'));

            if(inputs.length == 0) {
                return;
            }
            dtable.DataTable().columns().every( function (colIdx) {
                var that = this;
                inputs.eq(colIdx).off('keyup.dtg change.dtg').on('keyup.dtg change.dtg', function () {
                    if ( that.search() !== this.value ) {
                        that
                            .search (this.value.replace(/;/g, "|"), true, false)
                            .draw ();
                    }
                });
            });
            var div = $('#supsystic-table-' + table.data('view-id')),
                leftTable = div.find('.DTFC_LeftBodyWrapper').find('table'),
                rightTable = div.find('.DTFC_RightBodyWrapper').find('table'),
                self = vendor[appName];

            if(leftTable.length) {
                var leftFoot = div.find('.DTFC_LeftFootWrapper').find('table'),
                    leftInputs = (leftFoot.length == 0 ? leftTable.find('tfoot tr:last input') : leftFoot.eq(0).find('tfoot tr:last input'));
            
                leftInputs.each( function (colIdx) {
                    self.setCopyEvents(this, inputs.eq(colIdx).data('events'));
                });
            }
            if(rightTable.length) {
                var rightFoot = div.find('.DTFC_RightFootWrapper').find('table'),
                    rightInputs = (rightFoot.length == 0 ? rightTable.find('tfoot tr:last input') : rightFoot.eq(0).find('tfoot tr:last input')),
                    cntRight = rightInputs.length,
                    cntInputs = inputs.length;

                rightInputs.each( function (colIdx) {
                    self.setCopyEvents(this, inputs.eq(cntInputs - cntRight + colIdx).data('events'));
                });
            }
        });

        vendor[appName].setCopyEvents = (function(obj, events) {
            $.each(events, function (event, handlers) {
                $.each(handlers, function (j, handler) {
                    $(obj).unbind(event).bind(event, handler);
                });
            });
        });

        // Callback for executing script after table is initialized
        vendor[appName].executeScript = (function(table) {
            var $table = (table instanceof $ ? table : $(table)),
                $tableWrap = $table.closest('.supsystic-tables-wrap');

			this.getRuleJSInstance($table).init();
            $tableWrap.prev('.supsystic-table-loader').hide();
            $tableWrap.css('visibility', 'visible');
        });

        vendor[appName].fixSortingForMultipleHeader = (function(table) {
            if(table.data('head-rows-count') > 1 && table.data('sort-order')) {
                var thead = table.find('thead tr').get().reverse();

                // Fix of sorting for table with multiple header (when header has more than 1 row)
                if(table.data('head')) {
                    $.each(table.find('thead tr:last-child th'), function (index, element) {
                        var th = $(element),
                            nthChild = index + 1;

                        if(th.data('hide')) {
                            $(thead).each(function() {
                                var item = $(this).find('th:nth-child(' + nthChild + ')');

                                if(!item.data('hide')) {
                                    item.addClass('sorting');
                                    item.click(function() {
                                        th.trigger('click');
                                        if(th.hasClass('sorting')) {
                                            item.removeClass('sorting_asc');
                                            item.removeClass('sorting_desc');
                                            item.addClass('sorting');
                                        } else if(th.hasClass('sorting_asc')) {
                                            item.removeClass('sorting');
                                            item.removeClass('sorting_desc');
                                            item.addClass('sorting_asc');
                                        } else if(th.hasClass('sorting_desc')) {
                                            item.removeClass('sorting');
                                            item.removeClass('sorting_asc');
                                            item.addClass('sorting_desc');
                                        }
                                    });
                                    return false; // stop .each() function
                                }
                            });
                        }
                    });
                }
            }
        });

        vendor[appName].formatDataAtTable = (function(table, correctSorting) {
			correctSorting = correctSorting ? correctSorting : false;

            var self = this,
				numberFormat = table.data('number-format'),
                generalCurrencyFormat = table.data('currency-format'),
                generalPercentFormat = table.data('percent-format'),
                generalDateFormat = table.data('date-format'),
                generalTimeFormat = table.data('time-format'),
                skipFirstCol = table.data('auto-index') != 'off',
                hasCollapsedCells = table.data('responsive-mode') == 1 && table.hasClass('collapsed');

            table.find('th, td').each(function(index, el) {
                var $this = $(this);

                if((skipFirstCol && $this.is(':first-child')) || (hasCollapsedCells && $this.hasClass('child'))) {
                    // Break current .each iteration
                    return;
                }

                var languageData = numeral.languageData(),
                    format = $this.data('cell-format'),
                    formatType = $this.data('cell-format-type'),
                    preparedFormat,
                    delimiters,
                    value = $.trim($this.html()),
                    noFormat = false;

				// Fix data params for cells which use formulas, which depended on cells with shortcodes inside
				if(correctSorting && toeInArray(formatType, ['date', 'time_duration']) == -1) {
					var dataTableInstance = typeof table.api == 'function' ? table : self.getTableInstanceById(table.data('id'));

					if($this.data('original-value') != value) {
						$this.data('original-value',value);
						$this.attr('data-original-value',value);
					}
					if($this.data('data-order') != value) {
						$this.data('order');
						$this.attr('data-order',value);
						if(dataTableInstance) {
							dataTableInstance.api().cell($this).invalidate();
						}
					}
				}
				if(value) {
					if($this.data('cell-reformat')) {
						switch(formatType) {
							case 'date':
								var newDate = moment(value,format);
								if(newDate.isValid()) {
									value = newDate.format(generalDateFormat);

									$this.data('cell-format',generalDateFormat);
									$this.attr('data-cell-format',generalDateFormat);

									$this.data('original-value',value);
									$this.attr('data-original-value',value);

									$this.data('order',value);
									$this.attr('data-order',value);

									$this.data('cell-reformat',false);
									$this.attr('data-cell-reformat',value);
								}
								break;
							case 'time_duration':
								var newTime = moment(value,format),
									isValid = false;
								// console.log(newTime);

								if(newTime.isValid()) {
									value = newTime.format(generalTimeFormat);
									isValid = true;
								} else {
									newTime = moment.duration(value);
									if(newTime._milliseconds || value == 0) {
										value = newTime.format(generalTimeFormat);
										isValid = true;
									}
								}
								if(isValid) {
									$this.data('cell-format',generalTimeFormat);
									$this.attr('data-cell-format',generalTimeFormat);

									$this.data('original-value',value);
									$this.attr('data-original-value',value);

									$this.data('order',value);
									$this.attr('data-order',value);

									$this.data('cell-reformat',false);
									$this.attr('data-cell-reformat',value);
								}
								break;
							default:
								break;
						}
					} else if(self.isNumber(value) && !isNaN(value)) {
						numberFormat = numberFormat ? numberFormat.toString() : '';

						switch(formatType) {
							case 'percent':
								format = format ? format : generalPercentFormat;

								if(format) {
									format = format.toString();

									var clearFormat = format.indexOf('%') > -1 ? format.replace('%','') : format;

									value = value.indexOf('%') > -1 ? $this.data('original-value') : value;
									delimiters = (clearFormat.match(/[^\d]/g) || [',','.']).reverse();
									languageData.delimiters = {
										decimal: delimiters[0],thousands: delimiters[1]
									};

									// We need to use dafault delimiters for format string
									preparedFormat = format.replace(clearFormat,clearFormat.replace(delimiters[0],'.').replace(delimiters[1],','));
								} else {
									noFormat = true;
								}
								break;
							case 'currency':
								format = format ? format : generalCurrencyFormat;

								if(format) {
									format = format.toString();

									var formatWithoutCurrency = format.match(/\d.?\d*.?\d*/)[0],
										currencySymbol = format.replace(formatWithoutCurrency,'') || '$';	// We need to set currency symbol in any case for normal work of numeraljs

									delimiters = (formatWithoutCurrency.match(/[^\d]/g) || [',','.']).reverse();

									languageData.delimiters = {
										decimal: delimiters[0],
										thousands: delimiters[1]
									};
									languageData.currency.symbol = currencySymbol;
									// We need to use dafault delimiters for format string
									preparedFormat = format
										.replace(formatWithoutCurrency, formatWithoutCurrency
											.replace(delimiters[0],'.')
											.replace(delimiters[1],','))
										.replace(currencySymbol,'$');
								} else {
									noFormat = true;
								}
								break;
							case 'date':case 'time_duration':
								noFormat = true;
								break;
							default:
								if(numberFormat) {
									format = numberFormat;
									delimiters = (format.match(/[^\d]/g) || [',','.']).reverse();
									languageData.delimiters = {
										decimal: delimiters[0],
										thousands: delimiters[1]
									};

									// We need to use dafault delimiters for format string
									preparedFormat = format.replace(format,format.replace(delimiters[0],'.').replace(delimiters[1],','));
									break;
								} else {
									noFormat = true;
								}
								break;
						}
						if(noFormat) {
							noFormat = false;
						} else {
							numeral.language('en',languageData);
							value = numeral(value).format(preparedFormat);
						}
					}
				}
                $this.html(value);
            });
        });

        vendor[appName].isNumber = (function(value) {
            if (value) {
                if (value.toString().match(/^-{0,1}\d+\.{0,1}\d*$/)) {
                    return true;
                }
            }
            return false;
        });

        vendor[appName].prepareFormulaToParse = (function (value) {
			var stringsInFormula = value.match(/".+?"|'.+?'/g);

			if(stringsInFormula && stringsInFormula.length) {
				var clearValue = value.replace(/".+?"|'.+?'/g, '%STR%'),
					index = 0;

				clearValue = clearValue.toUpperCase();
				value = clearValue.replace(/%STR%/g, function(match) {
					var val = match;

					if(index < stringsInFormula.length) {
						val = stringsInFormula[index];
						index++;
					}
					return val;
				});
			} else {
				value = value.toUpperCase();
			}
			return value;
		});

        vendor[appName].Base64 = {
            _keyStr : "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",
            encode : function (input) {
                var self = vendor[appName].Base64,
					output = "",
					i = 0,
					chr1, chr2, chr3, enc1, enc2, enc3, enc4;

                input = self._utf8_encode(input);

                while (i < input.length) {
                    chr1 = input.charCodeAt(i++);
                    chr2 = input.charCodeAt(i++);
                    chr3 = input.charCodeAt(i++);

                    enc1 = chr1 >> 2;
                    enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
                    enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
                    enc4 = chr3 & 63;

                    if (isNaN(chr2)) {
                        enc3 = enc4 = 64;
                    } else if (isNaN(chr3)) {
                        enc4 = 64;
                    }
                    output = output +
					self._keyStr.charAt(enc1) + self._keyStr.charAt(enc2) +
					self._keyStr.charAt(enc3) + self._keyStr.charAt(enc4);
                }

                return output;
            },
            // private method for UTF-8 encoding
            _utf8_encode : function (string) {
                string = string.replace(/\r\n/g,"\n");
                var utftext = "";

                for (var n = 0; n < string.length; n++) {

                    var c = string.charCodeAt(n);

                    if (c < 128) {
                        utftext += String.fromCharCode(c);
                    }
                    else if((c > 127) && (c < 2048)) {
                        utftext += String.fromCharCode((c >> 6) | 192);
                        utftext += String.fromCharCode((c & 63) | 128);
                    }
                    else {
                        utftext += String.fromCharCode((c >> 12) | 224);
                        utftext += String.fromCharCode(((c >> 6) & 63) | 128);
                        utftext += String.fromCharCode((c & 63) | 128);
                    }

                }

                return utftext;
            }
        };

		vendor[appName].getClassesRegexp = (function() {
			return {
				color: /color\-([0-9a-f]{6})/,
				background: /bg\-([0-9a-f]{6})/,
				fontFamily: /ffamily\-([a-z_]+)/i,
				fontSize: /fsize\-([0-9]+)/
			}
		});

		vendor[appName].setStylesToCell = (function(cell) {
			var $cell = cell instanceof jQuery ? cell : $(cell),
				viewId = $cell.parents('.supsystic-table:first').data('view-id'),
				classes = this.getClassesRegexp(),
				cellClassNames = $cell.get(0).className,
				color = classes.color.exec(cellClassNames),
				background = classes.background.exec(cellClassNames),
				fontFamily = classes.fontFamily.exec(cellClassNames),
				fontSize = classes.fontSize.exec(cellClassNames);

			if (null !== color) {
				$cell.css({color: '#' + color[1]});
			}
			if (null !== background) {
				$cell.css({backgroundColor: '#' + background[1]});
			}
			if (null !== fontFamily) {
				var family = fontFamily[1].replace(/_/g, ' '),
					familyName = fontFamily[1].replace(/_/g, '+'),
					familyString = '@import url("//fonts.googleapis.com/css?family=' + familyName + '");';

				if(g_stbStandartFontsList && toeInArray(family, g_stbStandartFontsList) == -1) {
					var style = this.getFrontendCellStylesElem(viewId);

					if(style.text().indexOf(familyString) == -1) {
						style.text(familyString + '\n' + style.text());
					}
				}
				$cell.css({fontFamily: family});
			}
			if (null !== fontSize) {
				var lineHeight = +fontSize[1] + 6;
				$cell.css({fontSize: fontSize[1] + 'px', lineHeight: lineHeight + 'px'});
			}
		});

		vendor[appName].getAdminCellStylesElem = (function() {
			var $style = $('#supsystic-tables-style');

			if (!$style.length) {
				$style = $('<style/>', { id: 'supsystic-tables-style' });
				$('head').append($style);
			}
			return $style;
		});

		vendor[appName].getFrontendCellStylesElem = (function(viewId) {
			var $style = $('#supsystic-table-' + viewId + '-css');

			if (!$style.length) {
				$style = $('<style/>', { id: 'supsystic-table-' + viewId + '-css' });
				$('head').append($style);
			}
			return $style;
		});

		vendor[appName]._fixTableCaption = (function(captionHeight, viewId, counter) {
			if(counter < 0) return false;

			// Fix for displaying of caption for tables with fixed columns
			var self = this,
				tableViewHtmlId = '#supsystic-table-' + viewId,
				fixedColumnsWrapper = $(tableViewHtmlId + ' .DTFC_LeftWrapper, ' + tableViewHtmlId + ' .DTFC_RightWrapper');

			if(fixedColumnsWrapper.length) {
				fixedColumnsWrapper.find('caption').css({ display: 'none' });
				fixedColumnsWrapper.css({ top: captionHeight + 'px' });
			} else {
				counter--;
				setTimeout(function() {
					self._fixTableCaption(captionHeight, viewId, counter);
				}, 50);
			}
		});

		vendor[appName]._getChunksArray = (function(arr, len) {
			var chunks = [],
				i = 0,
				n = arr.length;

			while (i < n) {
				chunks.push(arr.slice(i, i += len));
			}

			return chunks;
		});

		vendor[appName]._checkOnClickPopups = (function( $table ) {
			// Integration with our PopUp plugin
			// Only after table was inited - we can do this, and only in that way it will work
			if(typeof(_ppsBindOnElementClickPopups) !== 'undefined' && $table && $table.size()) {
				var $bindedLinks = $table.find('[href*="#ppsShowPopUp_"].ppsClickBinded');
				if($bindedLinks && $bindedLinks.size()) {
					$bindedLinks.removeClass('ppsClickBinded').unbind('click');
				}
				_ppsBindOnElementClickPopups();
			}
		});
    }

}(window.supsystic = window.supsystic || {}, window.jQuery, window));

// For compatibility to old PRO versions
function classesRegexp() {
	return window.supsystic.Tables.getClassesRegexp();
}
function getAdminCellStylesElem() {
	return window.supsystic.Tables.getAdminCellStylesElem();
}

/**
 * We will not use just jQUery.inArray because it is work incorrect for objects
 * @return mixed - key that was found element or -1 if not
 */
function toeInArray(needle, haystack) {
    if(typeof(haystack) == 'object') {
        for(var k in haystack) {
            if(haystack[ k ] == needle)
                return k;
        }
    } else if(typeof(haystack) == 'array') {
        return jQuery.inArray(needle, haystack);
    }
    return -1;
}

(function($) {
    /**
     * Detects whether element can be scrolled vertically.
     * @this jQuery
     * @return {boolean}
     */
    $.fn.isVerticallyScrollable = function() {
        if (this.scrollTop()) {
            // Element is already scrolled, so it is scrollable
            return true;
        } else {
            // Test by actually scrolling
            this.scrollTop(1);

            if (this.scrollTop()) {
                // Scroll back
                this.scrollTop(0);
                return true;
            }
        }
        return false;
    };

    /**
     * Detects whether element can be scrolled horizontally.
     * @this jQuery
     * @return {boolean}
     */
    $.fn.isHorizontallyScrollable = function() {
        if (this.scrollLeft()) {
            // Element is already scrolled, so it is scrollable
            return true;
        } else {
            // Test by actually scrolling
            this.scrollLeft(1);

            if (this.scrollLeft()) {
                // Scroll back
                this.scrollLeft(0);
                return true;
            }
        }
        return false;
    };

    $.extend($.expr.pseudos || $.expr[ ":" ], {
        "vertically-scrollable": function(a, i, m) {
            return $(a).isVerticallyScrollable();
        },
        "horizontally-scrollable": function(a, i, m) {
            return $(a).isHorizontallyScrollable();
        }
    });

    $.fn.removeStyle = function(style)
    {
        var search = new RegExp(style + '[^;]+;?', 'g');

        return this.each(function()
        {
            $(this).attr('style', function(i, style)
            {
                return style && style.replace(search, '');
            });
        });
    };
}(jQuery));
