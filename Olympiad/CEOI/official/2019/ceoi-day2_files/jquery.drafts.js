(function ($) {
    var textareasToListen = [];
    var buttonsToListen = [];
    var alertedOnFail = false;
    var consecutiveFailCount = 0;
    var textById = {};

    var updateButtonsPosition = function () {
        $.each(textareasToListen, function (index, textarea) {
            var button = buttonsToListen[index];
            var buttonContainer = textarea;

            var buttonContainerSelector = button.attr("buttonContainerSelector");
            if (buttonContainerSelector && buttonContainerSelector.length > 0) {
                buttonContainer = $($(buttonContainerSelector)[0]);
            }

            var xOffset = buttonContainer.get(0).clientWidth - button.outerWidth() - 6;
            var yOffset = 8;

            var buttonXOffset = button.attr("buttonXOffset");
            if (buttonXOffset) {
                xOffset += parseInt(buttonXOffset);
            }

            var buttonYOffset = button.attr("buttonYOffset");
            if (buttonYOffset) {
                yOffset += parseInt(buttonYOffset);
            }

            button.css("top", buttonContainer.position().top + yOffset);
            button.css("left", buttonContainer.position().left + xOffset);
        });
    };

    setInterval(updateButtonsPosition, 200);

    function showDraftsPopup(textarea, settings) {
        var popup = $(".drafts-popup");
        var entries = popup.find(".drafts-entries");
        entries.find(".drafts-button").click(function () {
            settings["useItHandler"](textarea, $(this).parent().prev().text());
            $(".drafts-popup").fadeOut();
        });
        popup.show();
        popup.css("top", pageYOffset);
    }

    function addDraftEntry(item, settings) {
        var popup = $(".drafts-popup");
        var entries = popup.find(".drafts-entries");
        var hasSame = false;
        entries.find(".drafts-entry-body").each(function() {
            if ($(this).text() == item) {
                hasSame = true;
                return false;
            }
        });
        if (!hasSame) {
            $("<pre class='drafts-entry-body'></pre>").text(item).appendTo(entries);
            $("<div class='drafts-entry-actions'><span class='drafts-button'>" + settings["textUseIt"] + "</span></div>").appendTo(entries);
        }
    }

    function addFromLocalStorage(publicKey, key, settings) {
        if (publicKey && key) {
            var text = window.localStorage["draft-" + publicKey];
            if (text) {
                try {
                    text = sjcl.decrypt(key, text);
                    addDraftEntry(text, settings);
                } catch (e) {
                    window.localStorage.removeItem("draft-" + publicKey);
                }
            }
        }
    }

    function putToLocalStorage(publicKey, key, text) {
        if (publicKey && key && text) {
            if (window.localStorage) {
                window.localStorage["draft-" + publicKey] = sjcl.encrypt(key, text);
            }
        }
    }

    $.fn.drafts = function (options) {
        var settings = $.extend({
            textDrafts: 'Drafts',
            textUseIt: 'Use it',
            url: '/data/drafts.php',
            pollDelay: 5000,
            showDelay: 2500,
            saveErrorMessage: "Can't save draft. Possibly connection is lost or session is expired. Stay on the page (cancel to reload)?",
            useItHandler: function (textarea, text) {
                textarea.val(text);
            }
        });
    
        $.extend(settings, {
            saveErrorHandler: function () {
                if (!confirm(settings["saveErrorMessage"])) {
                    location.reload();
                }
            }
        });
        
        $.extend(settings, options);

        var textareas = this;
        var hasDraftsPrototype = false;
        var hasDraftsPopup = false;

        setTimeout(function () {
            textareas.each(function () {
                var textarea = $(this);
                if (textarea.parent()[0].tagName.toLowerCase() === "arclones") {
                    return;
                }

                if (!hasDraftsPrototype && $(".drafts-prototype").length === 0) {
                    $("<div class=\"drafts-prototype drafts-show-drafts\"><span class=\"drafts-button drafts-online\">"
                        + settings["textDrafts"]
                        + "</span></div>").appendTo($("body"));
                    hasDraftsPrototype = true;
                }

                if (!hasDraftsPopup && $(".drafts-popup").length === 0) {
                    $("<div class=\"drafts-popup\"><div class=\"drafts-close\">&times;</div><h1>"
                        + settings["textDrafts"]
                        + "</h1><div class=\"drafts-entries\"></div></div>").appendTo($("body"));
                    hasDraftsPopup = true;
                }

                if (textarea.prop("tagName").toLowerCase() !== "textarea") {
                    $.error("jquery.drafts.js can be used only for textareas, but " + textarea.prop("tagName").toLowerCase() + " found.");
                }

                if (!textarea.attr("data-drafts-id")) {
                    $.error("jquery.drafts.js requires textarea to have attribute data-drafts-id.");
                }

                var id = textarea.attr("data-drafts-id");
                var publicKey;
                var key;

                var textChanged = false;
                window.setTimeout(function() {
                    textarea.change(function() {
                        textChanged = true;
                    });
                    textarea.bind('input propertychange', function() {
                        textChanged = true;
                    });
                }, 60000);

                window.setInterval(function() {
                    if (!key) {
                        $.post(settings["url"], {action: 'getKey', id: id}, function (result) {
                            publicKey = result["publicKey"];
                            key = result["key"];
                        }, "json");
                    }
                    if (key && textChanged) {
                        putToLocalStorage(publicKey, key, textarea.val());
                        textChanged = false;
                    }
                }, 1000);

                var button = $(".drafts-prototype").clone()
                    .removeClass("drafts-prototype")
                    .css("opacity", "0.2");

                button.mouseover(function () {
                    button.css("opacity", "1.0");
                });

                button.mouseleave(function () {
                    button.css("opacity", "0.2");
                });

                button.click(function () {
                    var popup = $(".drafts-popup");
                    var entries = popup.find(".drafts-entries");
                    //entries.empty();
                    //addFromLocalStorage(id, settings);
                    //showDraftsPopup(settings);

                    $.post(settings["url"], {action: 'get', id: id}, function (items) {
                        entries.empty();
                        addFromLocalStorage(publicKey, key, settings);
                        $.each(items, function (index, item) {
                            addDraftEntry(item, settings);
                        });
                        showDraftsPopup(textarea, settings);
                    }, "json");
                });

                var buttonXOffset = settings["buttonXOffset"];
                if (buttonXOffset) {
                    button.attr("buttonXOffset", buttonXOffset);
                }

                var buttonYOffset = settings["buttonYOffset"];
                if (buttonYOffset) {
                    button.attr("buttonYOffset", buttonYOffset);
                }

                var buttonContainerSelector = settings["buttonContainerSelector"];
                if (buttonContainerSelector && buttonContainerSelector.length > 0) {
                    button.attr("buttonContainerSelector", buttonContainerSelector);
                    $($(buttonContainerSelector)[0]).append(button);
                } else {
                    $(textarea.parent()).append(button);
                }

                button.css("position", "absolute");

                textareasToListen.push(textarea);
                buttonsToListen.push(button);
                updateButtonsPosition();

                $(".drafts-popup .drafts-close").click(function () {
                    $(".drafts-popup").fadeOut();
                });

                window.setInterval(function () {
                    var text = textarea.val();
                    var innerButton = button.find(".drafts-button");
                    if (textById[id] === text) {
                        return;
                    }
                    textById[id] = text;
                    $.post(settings["url"], {action: 'put', id: id, text: text}, function (response) {
                        if (response === "OK") {
                            consecutiveFailCount = 0;
                            if (!innerButton.hasClass("drafts-online")) {
                                innerButton.removeClass("drafts-offline");
                                innerButton.addClass("drafts-online");
                            }
                        } else {
                            ++consecutiveFailCount;
                            if (!innerButton.hasClass("drafts-offline")) {
                                innerButton.removeClass("drafts-online");
                                innerButton.addClass("drafts-offline");
                            }
                            if (consecutiveFailCount >= 5 * textareasToListen.length && !alertedOnFail) {
                                alertedOnFail = true;
                                settings["saveErrorHandler"]();
                            }
                        }
                    }, "json").fail(function () {
                            ++consecutiveFailCount;
                            if (!innerButton.hasClass("drafts-offline")) {
                                innerButton.removeClass("drafts-online");
                                innerButton.addClass("drafts-offline");
                            }
                            if (consecutiveFailCount >= 5 * textareasToListen.length && !alertedOnFail) {
                                alertedOnFail = true;
                                settings["saveErrorHandler"]();
                            }
                        });
                }, settings["pollDelay"]);
            });
        }, settings["showDelay"]);

        return this;
    };
})(jQuery);
