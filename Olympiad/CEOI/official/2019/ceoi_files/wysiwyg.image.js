/**
 * Controls: Image plugin
 *
 * Depends on jWYSIWYG
 */
(function ($) {
	if (undefined === $.wysiwyg) {
		throw "wysiwyg.image.js depends on $.wysiwyg";
	}

	if (!$.wysiwyg.controls) {
		$.wysiwyg.controls = {};
	}

	/*
	 * Wysiwyg namespace: public properties and methods
	 */
	$.wysiwyg.controls.image = {
		init: function (Wysiwyg) {
			var self = this, elements, dialog, formImageHtml, dialogReplacements, key, translation,
				img = {
					alt: "",
					self: Wysiwyg.dom.getElement("img"), // link to element node
					src: "http://",
					title: ""
				};

			dialogReplacements = {
				legend	: "Insert Image",
				preview : "Preview",
				url     : "URL",
				title   : "Title",
				description : "Description",
				width   : "Width",
				height  : "Height",
				original : "Original W x H",
				float	: "Float",
				floatNone : "None",
				floatLeft : "Left",
				floatRight : "Right",
				submit  : "Insert Image",
				reset   : "Cancel"
			};

			formImageHtml = '<form class="wysiwyg"><fieldset><legend>{legend}</legend>' +
				'<label>{preview}: <img src="" alt="{preview}" style="float: left; margin: 5px; width: 80px; height: 60px; border: 1px solid rgb(192, 192, 192);"/></label>' +
				'<label>{url}: <input type="text" name="src" value=""/></label>' +
				'<label>{title}: <input type="text" name="imgtitle" value=""/></label>' +
				'<label>{description}: <input type="text" name="description" value=""/></label>' +
				'<label>{width} x {height}: <input type="text" name="width" value="" class="width"/> x <input type="text" name="height" value="" class="height"/></label>' +
				'<label>{original}: <input type="text" name="naturalWidth" value="" class="width" disabled="disabled"/> x ' +
				'<input type="text" name="naturalHeight" value="" class="height" disabled="disabled"/></label>' +
				'<label>{float}: <select name="float">' + 
				'<option value="">{floatNone}</option>' +
				'<option value="left">{floatLeft}</option>' +
				'<option value="right">{floatRight}</option></select></label>' +
				'<input type="submit" class="button" value="{submit}"/> ' +
				'<input type="reset" value="{reset}"/></fieldset></form>';

			for (key in dialogReplacements) {
				if ($.wysiwyg.i18n) {
					translation = $.wysiwyg.i18n.t(dialogReplacements[key], "dialogs.image");

					if (translation === dialogReplacements[key]) { // if not translated search in dialogs 
						translation = $.wysiwyg.i18n.t(dialogReplacements[key], "dialogs");
					}

					dialogReplacements[key] = translation;
				}

				formImageHtml = formImageHtml.replace("{" + key + "}", dialogReplacements[key]);
			}

			if (img.self) {
				img.src = img.self.src ? img.self.src : "";
				img.alt = img.self.alt ? img.self.alt : "";
				img.title = img.self.title ? img.self.title : "";
				img.width = img.self.width ? img.self.width : "";
				img.height = img.self.height ? img.self.height : "";
			}

			if (true /*mshipko: replaced default JWysiwyg dialog with standard browser prompt*/) {
                var defaultValue = "http://";
                var imageUrl = prompt("Insert image", defaultValue);
                if (imageUrl && imageUrl !== "" && imageUrl !== defaultValue) {
                    Wysiwyg.insertHtml('<img src=\"' + imageUrl + '\">');
                }
            } else if ($.modal) {
				elements = $(formImageHtml);
				elements = self.makeForm(elements, img);

				$.modal(elements, {
					onShow: function (dialog) {
						$("input:submit", dialog.data).click(function (e) {
							self.processInsert(dialog.container, Wysiwyg, img);

							$.modal.close();
							return false;
						});
						$("input:reset", dialog.data).click(function (e) {
							$.modal.close();
							return false;
						});
						$("fieldset", dialog.data).click(function (e) {
							e.stopPropagation();
						});
					},
					maxWidth: Wysiwyg.defaults.formWidth,
					maxHeight: Wysiwyg.defaults.formHeight,
					overlayClose: true
				});
			} else if ($.fn.dialog) {
				elements = $(formImageHtml);
				elements = self.makeForm(elements, img);

				dialog = elements.appendTo("body");
				dialog.dialog({
					modal: true,
					open: function (ev, ui) {
						$("input:submit", dialog).click(function (e) {
							self.processInsert(dialog.container, Wysiwyg, img);

							$(dialog).dialog("close");
							return false;
						});
						$("input:reset", dialog).click(function (e) {
							$(dialog).dialog("close");
							return false;
						});
						$('fieldset', dialog).click(function (e) {
							e.stopPropagation();
						});
					},
					close: function (ev, ui) {
						dialog.dialog("destroy");
					}
				});
			} else {
				if ($.browser.msie) {
					Wysiwyg.ui.focus();
					Wysiwyg.editorDoc.execCommand("insertImage", true, null);
				} else {
					elements = $("<div/>")
						.css({"position": "fixed",
							"z-index": 2000,
							"left": "50%", "top": "50%", "background": "rgb(0, 0, 0)",
							"margin-top": -1 * Math.round(Wysiwyg.defaults.formHeight / 2),
							"margin-left": -1 * Math.round(Wysiwyg.defaults.formWidth / 2)})
						.html(formImageHtml);
					elements = self.makeForm(elements, img);

					$("input:submit", elements).click(function (event) {
						self.processInsert(elements, Wysiwyg, img);

						$(elements).remove();
						return false;
					});
					$("input:reset", elements).click(function (event) {
						if ($.browser.msie) {
							Wysiwyg.ui.returnRange();
						}

						$(elements).remove();
						return false;
					});

					$("body").append(elements);
					elements.click(function(e) {
						e.stopPropagation();
					});
				}
			}

			$(Wysiwyg.editorDoc).trigger("editorRefresh.wysiwyg");
		},

		processInsert: function (context, Wysiwyg, img) {
			var image,
				url = $('input[name="src"]', context).val(),
				title = $('input[name="imgtitle"]', context).val(),
				description = $('input[name="description"]', context).val(),
				width = $('input[name="width"]', context).val(),
				height = $('input[name="height"]', context).val(),
				styleFloat = $('select[name="float"]', context).val(),
				style = [],
				found,
				baseUrl;

			if (Wysiwyg.options.controlImage.forceRelativeUrls) {
				baseUrl = window.location.protocol + "//" + window.location.hostname;
				if (0 === url.indexOf(baseUrl)) {
					url = url.substr(baseUrl.length);
				}
			}

			if (img.self) {
				// to preserve all img attributes
				$(img.self).attr("src", url)
					.attr("title", title)
					.attr("alt", description)
					.css("float", styleFloat);

				if (width.toString().match(/^[0-9]+(px|%)?$/)) {
					$(img.self).css("width", width);
				} else {
					$(img.self).css("width", "");
				}

				if (height.toString().match(/^[0-9]+(px|%)?$/)) {
					$(img.self).css("height", height);
				} else {
					$(img.self).css("height", "");
				}
			} else {
				found = width.toString().match(/^[0-9]+(px|%)?$/);
				if (found) {
					if (found[1]) {
						style.push("width: " + width + ";");
					} else {
						style.push("width: " + width + "px;");
					}
				}

				found = height.toString().match(/^[0-9]+(px|%)?$/);
				if (found) {
					if (found[1]) {
						style.push("height: " + height + ";");
					} else {
						style.push("height: " + height + "px;");
					}
				}

				if (styleFloat.length > 0) {
					style.push("float: " + styleFloat + ";");
				}

				if (style.length > 0) {
					style = ' style="' + style.join(" ") + '"';
				}

				image = "<img src='" + url + "' title='" + title + "' alt='" + description + "'" + style + "/>";
				Wysiwyg.insertHtml(image);
			}
		},

		makeForm: function (form, img) {
			form.find("input[name=src]").val(img.src);
			form.find("input[name=imgtitle]").val(img.title);
			form.find("input[name=description]").val(img.alt);
			form.find('input[name="width"]').val(img.width);
			form.find('input[name="height"]').val(img.height);
			form.find('img').attr("src", img.src);

			form.find('img').bind("load", function () {
				if (form.find('img').attr("naturalWidth")) {
					form.find('input[name="naturalWidth"]').val(form.find('img').attr("naturalWidth"));
					form.find('input[name="naturalHeight"]').val(form.find('img').attr("naturalHeight"));
				}
			});

			form.find("input[name=src]").bind("change", function () {
				form.find('img').attr("src", this.value);
			});

			return form;
		}
	};

	$.wysiwyg.insertImage = function (object, url, attributes) {
		return object.each(function () {
			var self = $(this).data("wysiwyg"),
				image,
				attribute;

			if (!self) {
				return this;
			}

			if (!url || url.length === 0) {
				return this;
			}

			if ($.browser.msie) {
				self.ui.focus();
			}

			if (attributes) {
				self.editorDoc.execCommand("insertImage", false, "#jwysiwyg#");
				image = self.getElementByAttributeValue("img", "src", "#jwysiwyg#");

				if (image) {
					image.src = url;

					for (attribute in attributes) {
						if (attributes.hasOwnProperty(attribute)) {
							image.setAttribute(attribute, attributes[attribute]);
						}
					}
				}
			} else {
				self.editorDoc.execCommand("insertImage", false, url);
			}

			$(self.editorDoc).trigger("editorRefresh.wysiwyg");

			return this;
		});
	};
})(jQuery);
