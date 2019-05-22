function fixEmailAddresses() {
    $("span[data-type='ZS1tYWls']").each(function (ix, e) {
        var elem = $(e);
        var json = window.atob(elem.attr("data-mail"));

        if (json === undefined || json === "")
            return;

        var data = JSON.parse(json);
        var text = data.to;
        var first = true;

        ["cc", "bcc", "subject", "body"].forEach(function (field, ix) {
            if (field in data) {
                text += (first ? "?" : "&") + field + "=" + escape(data[field]);
                first = false;
            }
        });

        var ref = $("<a></a>").attr("href", "mailto:" + text).addClass("fi-no-icon").append(elem.children());
        ref.find("b[data-random='aGlkZGVu']").remove();
        ref.get(0).normalize();

        elem.replaceWith(ref.get(0));
    });
}

function createCookie(name, value, age) {
    if (age === undefined)
        age = 30;

    var date = new Date();
    date.setDate(date.getDate() + age);

    document.cookie = name + "=" + value + ";path=/;expires=" + date.toUTCString();
}

$(document).ready(function () {
    fixEmailAddresses();

    // sledovanie interakcii s videami cez Piwik
    const video = document.getElementsByTagName('video')[0];
    if (video) {
        const filename = video.src.replace(/^.*[\\\/]/, '');

        video.addEventListener('play', function() {
            _paq.push(['trackEvent', 'Video', 'Play', filename]);
        }, true);
        video.addEventListener('ended', function() {
            _paq.push(['trackEvent', 'Video', 'Ended', filename]);
        }, true);
    }
});
