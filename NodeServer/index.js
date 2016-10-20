var express = require('express');
var app = express();
var url = require('url');
var http = require('http').Server(app);
var io = require('socket.io') (http);
var port = 8080;

io.on('connection', function (socket){
    
    var socketID = socket.id;
    var client = socket.request.connection.remoteAddress;
    console.log('a user connected. Socket ID: ' + socketID + "|| Cliente: " + client );

    app.get('/temp', function(req, res) {
        var getValues = req.url;
        if(getValues.indexOf('/temp') !== -1)
        {
            res.write('|normal|'); 
            var parsedURL = url.parse(getValues, true);
            var params = parsedURL.query;

            var d = new Date();
            
            var arduinoValues = {
                ServerTime : d.toLocaleString(),  
                Temperature : params.value[0], 
                Humidity : params.value[1], 
                Light : params.value[2] 
            };

            console.log(arduinoValues);
            io.emit('data sender', arduinoValues);
        }
        res.end();  
    }
    );

    socket.on('disconnect', function() {
    console.log('user disconnected');

  });

});


app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});

http.listen(port, function() {
    console.log('Server running on port: ' + port);
});
