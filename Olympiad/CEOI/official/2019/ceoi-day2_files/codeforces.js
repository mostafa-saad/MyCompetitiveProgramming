function info(message) {
    if (console) {
        console.log("INFO: " + message);
    }
}

function debug(message) {
    if (console) {
        console.log("DEBUG: " + message);
    }
}

function error(message) {
    if (console) {
        console.error("DEBUG: " + message);
    }
    window.alert("ERROR: " + message);
}

$.fn.hasAttr = function (name) {
    var attr = $(this).attr(name);
    return typeof attr !== 'undefined' && attr !== false;
};

$.fn.submitOnce = function (callback, alwaysDisable) {
    $(this).each(function () {
        var button = $(this).find("input[type=submit]");
        var img = $(this).find(".ajax-loading-gif");
        $(this).submit(function () {
            if ($(this).hasAttr("data-submitting")) {
                return true;
            }
            if (button.prop("disabled")) {
                return false;
            }
            var result = callback.call(this);
            if (result || alwaysDisable) {
                img.show();
                button.prop("disabled", true);
                setTimeout(function () {
                    img.hide();
                    button.prop("disabled", false);
                }, alwaysDisable ? 1000 : 10000);
            }
            return result;
        });
    });
};

$.fn.doSubmit = function () {
    $(this).attr("data-submitting", "true");
    $(this).submit();
    $(this).removeAttr("data-submitting");
};

Codeforces = new function () {
    //noinspection JSUnusedGlobalSymbols

    this.queryString = function () {
        // This function is anonymous, is executed immediately and
        // the return value is assigned to QueryString!
        var query_string = {};
        var query = window.location.search.substring(1);
        var vars = query.split("&");
        for (var i = 0; i < vars.length; i++) {
            var pair = vars[i].split("=");
            // If first entry with this name
            if (typeof query_string[pair[0]] === "undefined") {
                query_string[pair[0]] = decodeURIComponent(pair[1]);
                // If second entry with this name
            } else if (typeof query_string[pair[0]] === "string") {
                query_string[pair[0]] = [query_string[pair[0]], decodeURIComponent(pair[1])];
                // If third or later entry with this name
            } else {
                query_string[pair[0]].push(decodeURIComponent(pair[1]));
            }
        }
        return query_string;
    }();

    this.updateUrlParameter = function (url, param, paramVal) {
        var TheAnchor = null;
        var newAdditionalURL = "";
        var tempArray = url.split("?");
        var baseURL = tempArray[0];
        var additionalURL = tempArray[1];
        var temp = "";
        var tmpAnchor;
        var TheParams;

        if (additionalURL) {
            tmpAnchor = additionalURL.split("#");
            TheParams = tmpAnchor[0];
            TheAnchor = tmpAnchor[1];
            if (TheAnchor)
                additionalURL = TheParams;

            tempArray = additionalURL.split("&");
            for (var i = 0; i < tempArray.length; i++) {
                if (tempArray[i].split('=')[0] != param) {
                    newAdditionalURL += temp + tempArray[i];
                    temp = "&";
                }
            }
        } else {
            tmpAnchor = baseURL.split("#");
            TheParams = tmpAnchor[0];
            TheAnchor = tmpAnchor[1];

            if (TheParams)
                baseURL = TheParams;
        }

        if (TheAnchor)
            paramVal += "#" + TheAnchor;

        var rows_txt = temp + "" + param + "=" + paramVal;
        return baseURL + "?" + newAdditionalURL + rows_txt;
    };

    this.showAnnouncements = function (json, locale) {
        var div = document.createElement("div");

        var messages = [];

        for (var i = 0; i < json.length; ++i) {
            if (Codeforces.getFromStorage("Announcement-" + json[i].id, false)) {
                console.log("Skipped announcement " + json[i].id);
                continue;
            }
            Codeforces.putToStorage("Announcement-" + json[i].id, true);
            //noinspection InnerHTMLJS
            var announcementText = json[i].text;
            if (!announcementText) {
                if (locale == "ru") {
                    announcementText = json[i].russianText;
                } else {
                    announcementText = json[i].englishText;
                }
                if (!announcementText) {
                    announcementText = json[i].russianText;
                }
                if (!announcementText) {
                    announcementText = json[i].englishText;
                }
            }
            div.innerHTML = announcementText;

            var name = json[i].name;
            if (!name) {
                if (locale == "ru") {
                    name = json[i].russianName;
                } else {
                    name = json[i].englishName;
                }
            }
            var text = div.innerText || div.textContent || div.text;

            if (window.Notification) {
                if (Notification.permission === "default") {
                    Notification.requestPermission();
                }

                if (Notification.permission === "granted") {
                    //noinspection ObjectAllocationIgnored
                    new Notification(name, {
                        body: text,
                        icon: "../favicon.png"
                    });
                }
            }

            messages.push({name: name, text: text});
        }

        setTimeout(function () {
            for (var messageIndex = 0; messageIndex < messages.length; ++messageIndex) {
                var message = messages[messageIndex];
                alert(message.name + "\n----------\n\n" + message.text);
            }
        }, 1);
    };

    this.ping = function (pingUrl) {
        var millis = new Date().getTime();
        Codeforces.putToStorage("LastOnlineTimeUpdaterMillis", millis);
        Codeforces.setCookie("lastOnlineTimeUpdaterInvocation", millis);
        //info("ping: " + (millis / 1000));
        $.post(pingUrl, {
                ftaa: window._ftaa, bfaa: window._bfaa,
                clientUtcOffsetMinutes: Codeforces.getLocalUtcOffset(),
                clientUtcOffsetString: Codeforces.formatTimezone(moment(), false, true)
            },
            function (result) {
                Codeforces.showAnnouncements(result);
            }, "json");
    };

    this.parseSeconds = function (seconds) {
        var ap = 0;
        if (seconds.length == 9) {
            ap = seconds.charAt(0) - '0';
            seconds = seconds.substring(1);
        }
        if (seconds.length == 8 && seconds.charAt(2) == ':' && seconds.charAt(5) == ':') {
            var s = (seconds.charAt(7) - '0') + 10 * (seconds.charAt(6) - '0');
            var m = (seconds.charAt(4) - '0') + 10 * (seconds.charAt(3) - '0');
            var h = (seconds.charAt(1) - '0') + 10 * (seconds.charAt(0) - '0') + 100 * ap;
            return s + 60 * m + 60 * 60 * h;
        } else {
            return 0;
        }
    };

    this.formatSS = function (seconds) {
        if (seconds <= 9) {
            return "0" + seconds;
        } else {
            return seconds;
        }
    };

    this.formatSeconds = function (seconds) {
        var s = seconds % 60;
        seconds = (seconds - s) / 60;
        var m = seconds % 60;
        var h = (seconds - m) / 60;
        return Codeforces.formatSS(h) + ":" + Codeforces.formatSS(m) + ":" + Codeforces.formatSS(s);
    };

    this.getUtcOffset = function () {
        if (Codeforces.utc_offset == undefined) {
            Codeforces.utc_offset = $("meta[name=\"utc_offset\"]").attr("content");
        }
        return Codeforces.utc_offset;
    };

    this.getLocalUtcOffset = function () {
        if (Codeforces.local_utc_offset == undefined) {
            Codeforces.local_utc_offset = moment().local().utcOffset();
        }
        return Codeforces.local_utc_offset;
    };

    this.addTimeZoneNotice = function ($lastDatetimePickerInput) {
        var offsetString = "";
        var m = moment().utcOffset(Codeforces.getLocalUtcOffset());
        if (m.utcOffset() != 0) {
            offsetString += " " + moment().format("Z");
        }
        var notice = "(" + window.codeforcesOptions.timeZoneNoticeCaption + offsetString + ")";
        $lastDatetimePickerInput.after($("<span style=\"margin-left: 1em;\" class=\"notice smaller\"></span>").text(notice));
    };

    var ruTime = "DD.MM.YYYY HH:mm";
    var enTime = "MMM/DD/YYYY HH:mm";
    var ruTimeWithDow = "dddd, LL [в] HH:mm";//"dddd, DD.MMMM.YYYY HH:mm";
    var enTimeWithDow = "dddd, LL [at] HH:mm";//"dddd, MMM/DD/YYYY HH:mm";
    var ruTimeOnly = "HH:mm";
    var enTimeOnly = "HH:mm";
    var systemTimeWithSeconds = "YYYY-MM-DD HH:mm:ss";
    var ruTimeWithSeconds = "DD.MM.YYYY HH:mm:ss";
    var enTimeWithSeconds = "MMM/DD/YYYY HH:mm:ss";
    var ruDate = "DD.MM.YYYY";
    var enDate = "MMM/DD/YYYY";

    this.reformatTime = function (timeString) {
        var dateString = timeString + " " + Codeforces.getUtcOffset();
        var m = moment(dateString, ruTime + " Z");
        var timeFormat = ruTime;
        if (!m.isValid()) {
            m = moment(dateString, enTime + " Z");
            timeFormat = enTime;
        }
        m = m.utcOffset(Codeforces.getLocalUtcOffset());
        return m.format(timeFormat);
    };

    this.formatTimezone = function (m, wrapInHtml, returnCodeforcesOffset) {
        if (!returnCodeforcesOffset && m.format("Z") == Codeforces.getUtcOffset()) {
            return "";
        }
        var off = m.utcOffset();
        var offset = "UTC";
        if (off != 0) {
            if (off > 0)
                offset += "+";
            else
                offset += "-";
            off = Math.round(Math.abs(off));
            offset += Math.floor(off / 60);
            if (off % 60 != 0) {
                if (off % 60 == 30) {
                    offset += ".5";
                } else {
                    offset += ":";
                    if (off % 60 < 10)
                        offset += "0";
                    offset += off % 60;
                }
            }
        }
        if (wrapInHtml) {
            return "<sup title=\"" + window.codeforcesOptions.timeZoneTitleCaption + "\" style=\"font-size:8px;\">" + offset + "</sup>";
        } else {
            return " " + offset;
        }
    };

    this.reformatTimes = function () {
        $(".format-time-with-dow").each(function () {
            var dateString = $(this).text();
            if (dateString.indexOf("(") != -1) {
                dateString = dateString.substr(0, dateString.indexOf("("));
            }
            dateString = dateString + " " + Codeforces.getUtcOffset();
            var m = moment(dateString, ruTime + " Z");
            var timeFormat = ruTimeWithDow;
            if (!m.isValid()) {
                m = moment(dateString, enTime + " Z");
                timeFormat = enTimeWithDow;
            } else {
                m.locale("ru");
            }
            m = m.utcOffset(Codeforces.getLocalUtcOffset());
            $(this).replaceWith(m.format(timeFormat) + Codeforces.formatTimezone(m, true));
        });
        $(".format-time").each(function () {
            var dateString = $(this).text() + " " + Codeforces.getUtcOffset();
            var m = moment(dateString, ruTime + " Z");
            var timeFormat = ruTime;
            if (!m.isValid()) {
                m = moment(dateString, enTime + " Z");
                timeFormat = enTime;
            }
            m = m.utcOffset(Codeforces.getLocalUtcOffset());
            $(this).replaceWith(m.format(timeFormat) + Codeforces.formatTimezone(m, true));
        });
        $(".format-time-only").each(function () {
            var dateString = $(this).text() + " " + Codeforces.getUtcOffset();
            var m = moment(dateString, ruTime + " Z");
            var timeFormat = ruTimeOnly;
            if (!m.isValid()) {
                m = moment(dateString, enTime + " Z");
                timeFormat = enTimeOnly;
            }
            m = m.utcOffset(Codeforces.getLocalUtcOffset());
            $(this).replaceWith(m.format(timeFormat) + Codeforces.formatTimezone(m, true));
        });
        $(".format-systemtimewithseconds").each(function () {
            var dateString = $(this).text() + " " + Codeforces.getUtcOffset();
            var m = moment(dateString, systemTimeWithSeconds + " Z");
            m = m.utcOffset(Codeforces.getLocalUtcOffset());
            $(this).replaceWith(m.format(systemTimeWithSeconds) + Codeforces.formatTimezone(m, true));
        });
        $(".format-timewithseconds").each(function () {
            var dateString = $(this).text() + " " + Codeforces.getUtcOffset();
            var m = moment(dateString, ruTimeWithSeconds + " Z");
            var timeFormat = ruTimeWithSeconds;
            if (!m.isValid()) {
                m = moment(dateString, enTimeWithSeconds + " Z");
                timeFormat = enTimeWithSeconds;
            }
            m = m.utcOffset(Codeforces.getLocalUtcOffset());
            $(this).replaceWith(m.format(timeFormat) + Codeforces.formatTimezone(m, true));
        });
        $(".format-humantime").each(function () {
            var dateString = $(this).attr("title") + " " + Codeforces.getUtcOffset();
            var m = moment(dateString, ruTime + " Z");
            var timeFormat = ruTime;
            if (!m.isValid()) {
                m = moment(dateString, enTime + " Z");
                timeFormat = enTime;
            }
            m = m.utcOffset(Codeforces.getLocalUtcOffset());
            $(this).attr("title", m.format(timeFormat) + Codeforces.formatTimezone(m, false));
        });
        $(".format-date").each(function () {
            var dateString = $(this).text() + " " + Codeforces.getUtcOffset();
            var m = moment(dateString, ruTime + " Z");
            var dateFormat = ruDate;
            if (!m.isValid()) {
                m = moment(dateString, enTime + " Z");
                dateFormat = enDate;
            }
            m = m.utcOffset(Codeforces.getLocalUtcOffset());
            $(this).replaceWith(m.format(dateFormat));
        });
    };

    this.setupFormDatetimePicker = function ($initialDatetimeInput, $dayInput, $timeInput, $clientTimezoneOffsetInput) {
        $clientTimezoneOffsetInput.val(moment().utcOffset(Codeforces.getLocalUtcOffset()).utcOffset());

        var timeText = $initialDatetimeInput.val();
        if (!timeText || $dayInput.val() || $timeInput.val()) {
            return;
        }

        timeText = Codeforces.reformatTime(timeText);
        var tokens = timeText.split(' ');
        $dayInput.val(tokens[0]);
        $timeInput.val(tokens[1]);
    };

    this.countdown = function () {
        var now = new Date().getTime();
        var countdownElements = $(".countdown");
        var starts = [];

        var index = 0;
        countdownElements.each(function () {
            ++index;
            $(this).attr("cdid", "i" + index);
        });

        var callback = function () {
            countdownElements.each(function () {
                var countdownElement = $(this);
                var textBeforeRedirect = countdownElement.attr("textBeforeRedirect");
                var redirectUrl = countdownElement.attr("redirectUrl");
                var home = countdownElement.attr("home");
                var noRedirection = countdownElement.attr("noRedirection");
                var hideOnCountdownFinish = countdownElement.attr("hideOnCountdownFinish");
                var showAnotherOnCountdownFinish = countdownElement.attr("showAnotherOnCountdownFinish");
                var showAnotherClass = countdownElement.attr("showAnotherClass");
                var hideAnotherOnCountdownFinish = countdownElement.attr("hideAnotherOnCountdownFinish");
                var hideAnotherClass = countdownElement.attr("hideAnotherClass");

                var id = countdownElement.attr("cdid");
                var txt = countdownElement.text();
                var s = Codeforces.parseSeconds(txt);
                if (s > 0) {
                    if (starts[id] == undefined) {
                        starts[id] = s;
                    }
                    var passed = Math.floor((new Date().getTime() - now) / 1000);
                    var val = Math.max(0, starts[id] - passed);
                    countdownElement.text(Codeforces.formatSeconds(val));
                    if (val <= 0) {
                        if (hideOnCountdownFinish == "true" || hideOnCountdownFinish == "yes"
                            || hideOnCountdownFinish == "y" || hideOnCountdownFinish == "1") {
                            countdownElement.hide();
                        }

                        if (showAnotherOnCountdownFinish == "true" || showAnotherOnCountdownFinish == "yes"
                            || showAnotherOnCountdownFinish == "y" || showAnotherOnCountdownFinish == "1") {
                            $("." + showAnotherClass).show();
                        }

                        if (hideAnotherOnCountdownFinish == "true" || hideAnotherOnCountdownFinish == "yes"
                            || hideAnotherOnCountdownFinish == "y" || hideAnotherOnCountdownFinish == "1") {
                            $("." + hideAnotherClass).hide();
                        }

                        if (noRedirection != "true" && noRedirection != "yes"
                            && noRedirection != "y" && noRedirection != "1") {
                            if (textBeforeRedirect) {
                                Codeforces.alert(textBeforeRedirect, function () {
                                    if (redirectUrl) {
                                        window.setTimeout(Codeforces.redirect(redirectUrl), Math.floor(Math.random() * 2000));
                                    } else {
                                        window.setTimeout(Codeforces.reload, Math.floor(Math.random() * 2000));
                                    }
                                });
                            } else {
                                if (redirectUrl) {
                                    window.setTimeout(Codeforces.redirect(redirectUrl), Math.floor(Math.random() * 5000));
                                } else {
                                    window.setTimeout(Codeforces.reload, Math.floor(Math.random() * 5000));
                                }
                            }
                        } else {
                            if (textBeforeRedirect) {
                                Codeforces.alert(textBeforeRedirect);
                            }
                        }
                    }
                }
            });
            window.setTimeout(callback, 1000);
        };
        window.setTimeout(callback, 0);
    };

    this.facebox = function (target, home) {
        $("facebox").facebox(/*{
         closeImage    : (home != undefined ? home + "/" : "") + 'images/facebox/closelabel.gif',
         splitterImage : (home != undefined ? home + "/" : "") + 'images/facebox/splitter.png'
         }*/);
        $.facebox.loading();
        var clone = $(target).clone();
        $.facebox.reveal(clone.show(), null);

        CodeforcesIframe.updatePopups();
    };

    this.alert = function (messageHtml, okHandler, okText) {
        Codeforces.confirm(messageHtml, okHandler, null, okText, null);
    };

    this.confirm = function (messageHtml, okHandler, cancelHandler, okText, cancelText, noClose) {
        if (typeof(noClose) === 'undefined') {
            noClose = false;
        }

        var dialogHtml = "<div class='confirm-proto'><div class='text'>&nbsp;<\/div><div><hr\/><div style='text-align:center;'><input class='ok' name='codeforces-dialog-ok-button' type='button' value='%OK%'\/><input class='cancel' name='codeforces-dialog-cancel-button' type='button' value='%Cancel%'\/><\/div><\/div><\/div>"
            .replace("%OK%", okText ? okText : "OK")
            .replace("%Cancel%", cancelText ? cancelText : "Cancel");
        var p = $(dialogHtml).css('display', 'none');
        $(".text", p).html(messageHtml);

        var defaultButtonName = null;

        var cancelButton = $(".cancel", p);
        if (cancelHandler) {
            cancelButton.click(function () {
                if (noClose) {
                    cancelHandler();
                } else {
                    $(document).bind('afterClose.facebox', function () {
                        $(document).unbind('afterClose.facebox');
                        cancelHandler();
                    });
                    $.facebox.close();
                }
            });

            defaultButtonName = cancelButton.attr("name");
        } else {
            cancelButton.css("display", "none");
        }

        var okButton = $(".ok", p);
        if (okHandler) {
            okButton.click(function () {
                if (noClose) {
                    okHandler();
                } else {
                    $(document).bind('afterClose.facebox', function () {
                        $(document).unbind('afterClose.facebox');
                        okHandler();
                    });
                    $.facebox.close();
                }
            });

            defaultButtonName = okButton.attr("name");
        } else {
            okButton.css("display", "none");
        }

        if (!okHandler && !cancelHandler) {
            $(".ok", p).parent().parent().css("display", "none");
        }

        $("facebox").facebox(/*{
         closeImage    : (home != undefined ? home + "/" : "") + 'images/facebox/closelabel.gif',
         splitterImage : (home != undefined ? home + "/" : "") + 'images/facebox/splitter.png'
         }*/);
        $.facebox.loading();
        $.facebox.reveal(p.show(), null);

        CodeforcesIframe.updatePopups();

        if (defaultButtonName) {
            $("input[name=" + defaultButtonName + "]").focus();
        }
    };

    //noinspection JSUnusedGlobalSymbols
    this.confirmWithoutClose = function (messageHtml, okHandler, cancelHandler, okText, cancelText) {
        Codeforces.confirm(messageHtml, okHandler, cancelHandler, okText, cancelText, true);
    };

    this.showMessage = function (message) {
        $.jGrowl(message, {position: 'bottom-right', life: 10000});
        CodeforcesIframe.updatePopups();
    };

    //noinspection JSUnusedGlobalSymbols
    this.focusOnError = function () {
        var found = false;

        $(".table-form .error").each(function () {
            if (!found) {
                var val = $.trim($(this).text());
                if (val.length > 0) {
                    var classes = this.className.split(" ");
                    for (var i in classes) {
                        if (classes[i].match(/for__.*/)) {
                            var name = classes[i].substring(5);
                            found = true;

                            $(".table-form input[name=" + name + "]").focus();
                            return;
                        }
                    }
                }
            }
        });

        if (!found) {
            var focusInput = null;
            $("input.focus, select.focus, textarea.focus").each(function () {
                if (focusInput === null) {
                    focusInput = $(this);
                }
            });
            $(".table-form input, .table-form select, .table-form textarea").each(function () {
                if (focusInput === null) {
                    var elem = $(this);
                    if (elem.val() === "" && elem.attr("type") != "hidden" && !elem.hasAttr("readonly")) {
                        focusInput = elem;
                    }
                }
            });
            if (focusInput !== null) {
                focusInput.focus();
            }
        }
    };

    this.reload = function () {
        window.location.reload();
    };

    this.redirect = function (link) {
        window.location = link;
    };

    this.clearAjaxFormErrors = function (selector) {
        var form = $(selector);
        form.find("*").each(function () {
            var classes = this.className.split(" ");
            var found = false;
            for (var i in classes) {
                if (classes[i].indexOf("error__") === 0) {
                    found = true;
                }
            }
            if (found) {
                $(this).find(".error").hide();
                $(this).find(".notice").show();
            }
        });
    };

    this.setAjaxFormError = function (selector, key, value) {
        $(selector).find("." + key).each(function () {
            $(".notice", this).hide();
            $(".error", this).html(value).show();
        });
    };

    this.setAjaxFormErrors = function (selector, data) {
        var result = false;
        this.clearAjaxFormErrors(selector);
        for (var i in data) {
            if (i.indexOf("error__") == 0) {
                this.setAjaxFormError(selector, i, data[i]);
                result = true;
            }
        }
        return result;
    };

    //noinspection JSUnusedGlobalSymbols
    this.isEnglishText = function (s) {
        var latinLetterCount = 0;
        for (var i = 0; i < s.length; i++) {
            var c = s.charAt(i);
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                latinLetterCount++;
            }
        }
        return latinLetterCount > s.length / 2;
    };

    //noinspection JSUnusedGlobalSymbols
    this.replaceDataForRoundTable = function (selector, titles, data, widths) {
        var rt = $(selector);
        var table = $(".rtable", rt);
        table.fadeOut(250, function () {
            var content = "";

            content += "<tr>";
            for (var j = 0; j < titles.length; j++) {
                var attr = "";
                if (j === 0) {
                    attr += " class=\"left\"";
                }
                if (widths != undefined && widths[j] != undefined) {
                    attr += " style=\"width:" + widths[j] + ";\"";
                }
                content += "<th" + attr + ">";
                content += titles[j] + "</th>";
            }
            content += "</tr>";

            for (var i = 0; i < data.length; i++) {
                var row = data[i];
                content += "<tr>";
                for (var j = 0; j < row.length; j++) {
                    var clazz = "";
                    if (j === 0) {
                        clazz += "left ";
                    }
                    if (i + 1 == data.length) {
                        clazz += "bottom ";
                    }
                    if (i % 2 === 0) {
                        clazz += "dark ";
                    }
                    content += "<td class=\"" + clazz + "\">" + row[j] + "</td>";
                }
                content += "</tr>";
            }
            table.html(content);
            table.fadeIn(250);
        });
    };

    /*
     this.changeRowIndex = function(selector, from, to) {
     if (from != to) {
     var init = $(selector + " tr:nth-child(" + from + ")");
     var target = $(selector + " tr:nth-child(" + to + ")");
     var duration = 250 + 50 * Math.abs(from - to);
     if (init != undefined && target != undefined) {
     var tr = init.clone();
     $(selector).append(tr);
     tr.css("display", "block").css("position", "absolute")
     .css("top", init.position().top).css("background", "#FFF7DB !important")
     .css("border", "3px solid #e1e1e1").css("font-size", "1.25em")
     .css("left", (target.position().left-10) + "px");
     tr.find("td").css("background", "#FFF7DB !important");
     tr.show();
     init.animate({
     opacity: "hide"
     }, {
     queue: false,
     duration: duration
     });
     tr.animate({
     "top": target.position().top
     }, duration, function() {
     tr.hide();
     init.detach();
     init.show();
     if (from > to)
     target.before(init);
     else
     target.after(init);
     $(".datatable").each(function() {
     $(this).find("td").removeClass("bottom").removeClass("dark");
     $(this).find("tr:first th").addClass("top");
     $(this).find("tr:last td").addClass("bottom");
     $(this).find("tr:odd td").addClass("dark");
     $(this).find("tr td:first-child, tr th:first-child").addClass("left");
     $(this).find("tr td:last-child, tr th:last-child").addClass("right");
     });
     });
     }
     }
     }
     */

    this.updateDatatables = function () {
        var tds = $(".datatable tr td");
        tds.removeClass("top");
        tds.removeClass("bottom");
        tds.removeClass("dark");
        tds.removeClass("left");
        tds.removeClass("right");
        $(".datatable").each(function () {
            $(this).find("tr:first th").addClass("top");
            $(this).find("tr:last td").addClass("bottom");
            $(this).find("tr:odd td").addClass("dark");
            $(this).find("tr td:first-child, tr th:first-child").addClass("left");
            $(this).find("tr td:last-child, tr th:last-child").addClass("right");
        });
    };

    this.isGym = function (contestId) {
        return contestId >= 100000;
    };

    //noinspection JSUnusedGlobalSymbols
    this.parentForm = function (elem) {
        while (elem && elem.tagName != "FORM") {
            elem = elem.parentNode;
        }
        return elem;
    };

    this.setCookie = function (name, value) {
        document.cookie = name + "=" + escape(value);
    };

    this.getCookie = function (name) {
        var prefix = name + "=";
        var from = document.cookie.indexOf(prefix);
        if (from < 0) {
            return null;
        } else {
            var to = document.cookie.indexOf(";", from + prefix.length);
            if (to < 0) {
                to = document.cookie.length;
            }
            return unescape(document.cookie.substring(from + prefix.length, to));
        }
    };

    var _0xca4e = ["\x6C\x65\x6E\x67\x74\x68", "\x63\x68\x61\x72\x43\x6F\x64\x65\x41\x74", "\x66\x6C\x6F\x6F\x72"];

    function ca76fd64a80cdc35(_0x87ebx2) {
        var _0x87ebx3 = 0;
        for (var _0x87ebx4 = 0; _0x87ebx4 < _0x87ebx2[_0xca4e[0]]; _0x87ebx4++) {
            _0x87ebx3 = (_0x87ebx3 + (_0x87ebx4 + 1) * (_0x87ebx4 + 2) * _0x87ebx2[_0xca4e[1]](_0x87ebx4)) % 1009;
            if (_0x87ebx4 % 3 === 0) {
                _0x87ebx3++;
            }
            if (_0x87ebx4 % 2 === 0) {
                _0x87ebx3 *= 2;
            }
            if (_0x87ebx4 > 0) {
                _0x87ebx3 -= Math[_0xca4e[2]](_0x87ebx2[_0xca4e[1]](Math[_0xca4e[2]](_0x87ebx4 / 2)) / 2) * (_0x87ebx3 % 5);
            }
            while (_0x87ebx3 < 0) {
                _0x87ebx3 += 1009;
            }
            while (_0x87ebx3 >= 1009) {
                _0x87ebx3 -= 1009;
            }
        }
        return _0x87ebx3;
    }

    //noinspection JSUnusedGlobalSymbols
    this.signForms = function () {
        var etc = Codeforces.tta();
        if (etc) {
            $("form:not([method=get])").each(function () {
                var f = $(this);
                var upd = 0;
                f.find("input[name='_tta']").each(function () {
                    ++upd;
                    $(this).val(etc);
                });
                if (upd === 0) {
                    f.append("<input type='hidden' name='_tta' value='" + etc + "'/>");
                }
            });
        }
    };

    this.tta = function () {
        return ca76fd64a80cdc35(Codeforces.getCookie("39ce7"));
    };

    function isNumber(n) {
        return !isNaN(parseFloat(n)) && isFinite(n);
    }

    this.getFromStorage = function (key) {
        return window.localStorage[key];
    };

    this.getFromStorage = function (key, defaultValue) {
        if (!window.localStorage) {
            return defaultValue;
        }

        if (window.localStorage[key] == null || window.localStorage[key] == "null"
            || window.localStorage[key] == NaN || window.localStorage[key] == "NaN"
            || window.localStorage[key] == undefined || window.localStorage[key] == "undefined") {
//            window.localStorage[key] = defaultValue;
            return defaultValue;
        }

        var result = window.localStorage[key];

        if (isNumber(result)) {
            return parseFloat(result);
        }

        if (result == "true") {
            return true;
        }

        if (result == "false") {
            return false;
        }

        return result;
    };

    this.putToStorage = function (key, value) {
        if (window.localStorage) {
            window.localStorage[key] = value;
        }
    };

    this.eventBusSubscriptions = [];
    this.pushstream = null;
    this.channelCount = 0;

    this.onMessageReceived = function (text, id, channel) {
        //info(text);
        if (text && Codeforces.eventBusSubscriptions[channel]) {
            var json = JSON.parse(text);
            for (var h in Codeforces.eventBusSubscriptions[channel]) {
                if (Codeforces.eventBusSubscriptions[channel].hasOwnProperty(h)) {
                    Codeforces.eventBusSubscriptions[channel][h](json);
                }
            }
        }
    };

    this.addChannel = function (channel) {
        if (channel && channel.length > 4) {
            //info("Adding the channel '" + channel.substr(0, 4) + "'.");
            this.channelCount++;
            this.pushstream.addChannel(channel);
        }
    };

    this.onStatusChanged = function (state) {
        if (state == PushStream.OPEN) {
            //info("Connected!")
        } else {
            //info("Disconnected :(")
        }
    };

    this.initializePubSub = function () {
        var that = this;
        if (that.pushstream == null && window.codeforcesOptions.subscribeServerUrl) {
            //info("Connecting to the pubsub server...");
            var host = window.codeforcesOptions.subscribeServerUrl;
            if (window.standaloneContest) {
                host = undefined;
            }
            var useSSL = window.location.href.indexOf("https://") === 0;
            that.pushstream = new PushStream({
                useSSL: useSSL,
                host: host,
                port: useSSL ? 443 : 80,
                modes: "websocket|eventsource|longpolling",
                autoReconnect: true,
                reconnectOnChannelUnavailableInterval: 1000,
                reconnectOnTimeoutInterval: 1000
            });
            that.pushstream.onmessage = Codeforces.onMessageReceived;
            that.pushstream.onstatuschange = Codeforces.onStatusChanged;
            Codeforces.addChannel(Codeforces.getGlobalChannel());
            Codeforces.addChannel(Codeforces.getUserChannel());
            Codeforces.addChannel(Codeforces.getContestChannel());
            Codeforces.addChannel(Codeforces.getParticipantChannel());
            Codeforces.addChannel(Codeforces.getTalkChannel());
            if (that.channelCount > 0) {
                that.pushstream.connect();
            }
        }
    };

    window.performance = window.performance || {};
    window.performance.timing = window.performance.timing || {};
    window.performance.timing.navigationStart = window.performance.timing.navigationStart ||
        (function () {
            var startTimeMillis = Date.now();
            return function () {
                return startTimeMillis;
            }
        })()();

    this.getRandomTokenSeed = window.performance.timing.navigationStart / 100000.00;
    this.getRandomToken = function () {
        return Math.random().toString(36).substring(2)
            + Math.sin(Codeforces.getRandomTokenSeed++).toString(36).substring(3);
    };

    //noinspection JSUnusedGlobalSymbols
    this.subscribe = function (channel, handler) {
        if (window.codeforcesOptions && window.codeforcesOptions.subscribeServerUrl) {
            if (this.eventBusSubscriptions[channel] == undefined) {
                this.eventBusSubscriptions[channel] = [];
            }
            this.eventBusSubscriptions[channel].push(handler);
        }
    };

    //noinspection JSUnusedGlobalSymbols
    this.getGlobalChannel = function () {
        return $("meta[name=\"gc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getUserChannel = function () {
        return $("meta[name=\"uc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getUserShowMessageChannel = function () {
        return $("meta[name=\"usmc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getContestChannel = function () {
        return $("meta[name=\"cc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getParticipantChannel = function () {
        return $("meta[name=\"pc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getTalkChannel = function () {
        return $("meta[name=\"tc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getCsrfToken = function () {
        var meta = $("meta[name='X-Csrf-Token']").attr("content");
        if (meta && meta.length === 32) {
            return meta;
        }

        var span = $("span.csrf-token").attr("data-csrf");
        if (span && span.length === 32) {
            return span;
        }

        return undefined;
    };

    this.getDimensionPx = function (wrappedElement, cssPropertyName) {
        var dimension = wrappedElement.css(cssPropertyName);

        if (dimension) {
            var pxIndex = dimension.indexOf("px");
            if (pxIndex > 0) {
                return parseInt(dimension.substr(0, pxIndex))
            }
        }

        return -1;
    };

    this.getWidthPx = function (wrappedElement) {
        var width = this.getDimensionPx(wrappedElement, "width");

        if (width === -1) {
            var clientWidth = wrappedElement.get(0).clientWidth;
            if (clientWidth > 0) {
                width = clientWidth;
            }
        }

        return width;
    };

    this.getHeightPx = function (wrappedElement) {
        var height = this.getDimensionPx(wrappedElement, "height");

        if (height === -1 || true) {
            var clientHeight = wrappedElement.get(0).clientHeight;
            if (clientHeight > 0) {
                height = clientHeight;
            }
        }

        return height;
    };

    this.equalizeElements = function (jquerySelectorOrElements, equalizeWidth, equalizeHeight) {
        if (typeof(equalizeWidth) === 'undefined') {
            equalizeWidth = true;
        }

        if (typeof(equalizeHeight) === 'undefined') {
            equalizeHeight = true;
        }

        var elements = $(jquerySelectorOrElements);
        var maxWidth = 0;
        var maxHeight = 0;

        elements.each(function () {
            if (equalizeWidth) {
                var width = $(this).width();

                var currentWidth = Math.max(
                    width ? width : 0,
                    this.offsetWidth ? this.offsetWidth : 0,
                    (this.clientLeft ? this.clientLeft : 0) + (this.clientWidth ? this.clientWidth : 0)
                );

                if (currentWidth > maxWidth) {
                    maxWidth = currentWidth;
                }
            }

            if (equalizeHeight) {
                var height = $(this).height();

                var currentHeight = Math.max(
                    height ? height : 0,
                    this.offsetHeight ? this.offsetHeight : 0,
                    (this.clientTop ? this.clientTop : 0) + (this.clientHeight ? this.clientHeight : 0)
                );


                if (currentHeight > maxHeight) {
                    maxHeight = currentHeight;
                }
            }
        });

        elements.each(function () {
            if (equalizeWidth) {
                this.style.width = maxWidth + "px";
            }

            if (equalizeHeight) {
                this.style.height = maxHeight + "px";
            }
        });
    };

    this.setupContestTimes = function(contestDataPageUrl, elem) {
        if (!elem) {
            elem = $("html");
        }
        elem.find(".contest-time").each(function() {
            var $this = $(this);
            var contestId = $(this).attr("contestId");
            $.post(contestDataPageUrl, {
                action: "getContestTime",
                contestId: contestId
            }, function (result) {
                if (result["success"] == "true") {
                    var href = result["contestTimeHref"];
                    var html = result["contestTimeHtml"];
                    $this.attr("href", href);
                    $this.html(html);
                    Codeforces.reformatTimes();
                }
            }, "json");
        });
    };

    this.setupSpoilers = function (elem) {
        if (!elem) {
            elem = $("html");
        }
        elem.find(".spoiler-title").click(function () {
            var $spoiler = $(this).closest(".spoiler");
            if ($spoiler.hasClass("spoiler-open")) {
                $spoiler.removeClass("spoiler-open");
                $(this).parent().children(".spoiler-content").slideUp();
            } else {
                $spoiler.addClass("spoiler-open");
                var $content = $(this).parent().children(".spoiler-content");
                $content.slideDown();
            }
            return false;
        });
    };

    this.setupTutorials = function (tutorialDataPageUrl, elem) {
        if (!elem) {
            elem = $("html");
        }
        elem.find(".problemTutorial").each(function () {
            var problemCode = $(this).attr("problemCode");
            var tutorialPlaceholder = $(this);
            $.post(tutorialDataPageUrl, {
                problemCode: problemCode
            }, function (result) {
                var replacement = $("<div></div>").html(result["html"]);
                if (result["success"] === "true" && result["public"] === "false") {
                    var title = replacement.find("h3:first");
                    if (title) {
                        title.html(title.html() + " <span style='color:red' class='info'>(" +
                            window.codeforcesOptions.notPublicCaption + ")</span>");
                    }
                }
                tutorialPlaceholder.replaceWith(replacement);
                if (MathJax) {
                    MathJax.Hub.Queue(["Typeset", MathJax.Hub]);
                }
                prettyPrint();
            }, "json");
        });
    };

    this.combineBackgroundColor = function (jqueryElement, red, green, blue) {
        var backgroundColor = jqueryElement.css("background-color");
        var colorComponents;

        if (/^rgb\([0-9]{1,3}(,[ ]?[0-9]{1,3}){2}\)$/.test(backgroundColor)) {
            colorComponents = backgroundColor.substring("rgb(".length, backgroundColor.length - 1)
                .replace(" ", "").split(",");

            red = red >= 0 ? Math.floor((parseInt(colorComponents[0]) + red) / 2) : parseInt(colorComponents[0]);
            green = green >= 0 ? Math.floor((parseInt(colorComponents[1]) + green) / 2) : parseInt(colorComponents[1]);
            blue = blue >= 0 ? Math.floor((parseInt(colorComponents[2]) + blue) / 2) : parseInt(colorComponents[2]);
        } else if (/^rgba\([0-9]{1,3}(,[ ]?[0-9]{1,3}){2},[ ]?[1-9][0-9]{0,2}\)$/.test(backgroundColor)) {
            colorComponents = backgroundColor.substring("rgba(".length, backgroundColor.length - 1)
                .replace(" ", "").split(",");

            red = red >= 0 ? Math.floor((parseInt(colorComponents[0]) + red) / 2) : parseInt(colorComponents[0]);
            green = green >= 0 ? Math.floor((parseInt(colorComponents[1]) + green) / 2) : parseInt(colorComponents[1]);
            blue = blue >= 0 ? Math.floor((parseInt(colorComponents[2]) + blue) / 2) : parseInt(colorComponents[2]);
        } else if (/#[0-9a-fA-F]{6}/.test(backgroundColor)) {
            red = red >= 0
                ? Math.floor((parseInt(backgroundColor.substr(1, 2)) + red) / 2)
                : parseInt(backgroundColor.substr(1, 2));

            green = green >= 0
                ? Math.floor((parseInt(backgroundColor.substr(3, 2)) + green) / 2)
                : parseInt(backgroundColor.substr(3, 2));

            blue = blue >= 0
                ? Math.floor((parseInt(backgroundColor.substr(5, 2)) + blue) / 2)
                : parseInt(backgroundColor.substr(5, 2));
        } else {
            red = red >= 0 ? Math.floor((255 + red) / 2) : 255;
            green = green >= 0 ? Math.floor((255 + green) / 2) : 255;
            blue = blue >= 0 ? Math.floor((255 + blue) / 2) : 255;
        }

        jqueryElement.css("background-color", "rgb(" + red + ", " + green + ", " + blue + ")");
    };
};

CodeforcesIframe = new function () {
    this.updatePopupDimensions = function () {
        //noinspection JSUnresolvedVariable
        var parentDimensions = window.parentDimensions;
        if (!parentDimensions) {
            return;
        }

        var parentWindow = parentDimensions.window;
        var container = parentDimensions.container;

        $("#facebox").find(".popup .content > div").each(function () {
            var facebox = $(this);

            var width = Codeforces.getWidthPx(facebox);
            if (width !== -1) {
                var maxWidth = Math.max(350, container.offsetWidth - 100);
                if (width > maxWidth) {
                    facebox.css("width", maxWidth + "px");
                }
            }

            var height = Codeforces.getHeightPx(facebox);
            if (height !== -1) {
                var maxHeight = Math.max(250, Math.min(container.offsetHeight - 100, parentWindow.innerHeight - 200));
                if (height > maxHeight) {
                    facebox.css("height", maxHeight + "px");
                }
            }
        });
    };

    this.updatePopupLocations = function () {
        //noinspection JSUnresolvedVariable
        var parentDimensions = window.parentDimensions;
        if (!parentDimensions) {
            return;
        }

        var parentWindow = parentDimensions.window;
        var container = parentDimensions.container;

        /* Offset of the visible area top from the top of IFrame. */
        var top = parentWindow.scrollY - container.offsetTop;
        top = Math.max(top, 0);

        /* Offset of the visible area bottom from the bottom of IFrame. */
        var bottom = container.offsetHeight + container.offsetTop - parentWindow.scrollY - parentWindow.innerHeight;
        bottom = Math.max(bottom, 0);

        $("#jGrowl").each(function () {
            var element = $(this);
            var offset = 0;
            var elementBottom = bottom + offset;
            var elementHeight = Codeforces.getHeightPx(element);

            if (elementHeight !== -1) {
                elementBottom = Math.min(elementBottom, Math.max(offset, window.innerHeight - elementHeight - offset));
            }

            if (elementBottom !== Codeforces.getDimensionPx(element, "bottom")) {
                element.css("bottom", elementBottom + "px");
            }
        });

        $("#facebox").each(function () {
            var element = $(this);
            var offset = 50;
            var elementTop = top + offset;
            var elementHeight = Codeforces.getHeightPx(element);

            if (elementHeight !== -1) {
                elementTop = Math.min(elementTop, Math.max(offset, window.innerHeight - elementHeight - offset));
            }

            if (elementTop !== Codeforces.getDimensionPx(element, "top")) {
                element.css("top", elementTop + "px");
            }

            var elementWidth = Codeforces.getWidthPx(element);
            if (elementWidth !== -1) {
                var elementLeft = Codeforces.getDimensionPx(element, "left");
                if (elementLeft !== -1) {
                    var centeredElementLeft = (container.offsetWidth - elementWidth) / 2;
                    if (elementLeft !== centeredElementLeft) {
                        element.css("left", centeredElementLeft + "px");
                    }
                }
            }
        });
    };

    this.updatePopups = function () {
        this.updatePopupDimensions();
        this.updatePopupLocations();
    };
};
