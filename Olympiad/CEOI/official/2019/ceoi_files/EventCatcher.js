function EventCatcher(host, channels) {
    var eventCatcher = this;

    eventCatcher.host = window.standaloneContest ? undefined : host;
    eventCatcher.channels = [];
    eventCatcher.eventBusSubscriptions = [];
    eventCatcher.pushstream = null;

    eventCatcher.addChannel = function (channel) {
        if (channel && channel.length > 4 && eventCatcher.channels.indexOf(channel) < 0) {
            // info("Adding the channel '" + channel.substr(0, 4) + "'.");
            eventCatcher.channels.push(channel);
            eventCatcher.pushstream.addChannel(channel);
        }
    };

    eventCatcher.onMessageReceived = function (text, id, channel) {
        // info("Got '" + text + "' by " + eventCatcher.host + "@" + channel + ".");
        if (text && eventCatcher.eventBusSubscriptions[channel]) {
            var json = JSON.parse(text);
            for (var h in eventCatcher.eventBusSubscriptions[channel]) {
                if (eventCatcher.eventBusSubscriptions[channel].hasOwnProperty(h)) {
                    eventCatcher.eventBusSubscriptions[channel][h](json);
                }
            }
        }
    };

    eventCatcher.onStatusChanged = function (state) {
        if (state === PushStream.OPEN) {
            // info("Connected!")
        } else {
            // info("Disconnected :(")
        }
    };

    eventCatcher.subscribe = function (channel, handler) {
        if (eventCatcher.eventBusSubscriptions[channel] === undefined) {
            eventCatcher.eventBusSubscriptions[channel] = [];
        }
        eventCatcher.eventBusSubscriptions[channel].push(handler);
    };

    eventCatcher.disconnect = function () {
        eventCatcher.pushstream.disconnect();
    };

    var useSSL = window.location.href.indexOf("https://") === 0;
    eventCatcher.pushstream = new PushStream({
        useSSL: useSSL,
        host: host,
        port: useSSL ? 443 : 80,
        modes: "websocket|eventsource|longpolling",
        autoReconnect: true,
        reconnectOnChannelUnavailableInterval: 1000,
        reconnectOnTimeoutInterval: 1000
    });

    eventCatcher.pushstream.onmessage = eventCatcher.onMessageReceived;
    eventCatcher.pushstream.onstatuschange = eventCatcher.onStatusChanged;

    channels.forEach(function(channel) {
        eventCatcher.addChannel(channel);
    });

    if (eventCatcher.channels.length > 0) {
        eventCatcher.pushstream.connect();
    }
}
