var express = require('express');
var app = express();
var url = require('url');
var http = require('http').Server(app);
var io = require('socket.io')(http);
var TEMP_LIMIT = 28;

var port = 8080;

var temp;

io.on('connection', function(socket) {
    
    app.get('/temp', function(req, res) {
        var getValues = req.url;
        if(getValues.indexOf('/temp') !== -1)
        {
            var parsedURL = url.parse(getValues, true);
            var params = parsedURL.query || {};
            var d = new Date();
            console.log(params.value[2]);
            temp = params.value || null;
            
            var arduinoValues = {
                ServerTime : d.toLocaleString(),  
                Temperature : params.value[0], 
                Humidity : params.value[1], 
                Light : params.value[2] 
            };
            console.log(arduinoValues);
            var message = '['+d.toLocaleString()+'] Temperatura: '+ arduinoValues.ServerTime +'';
            io.emit('data sender', arduinoValues);
            if (temp) {
                if (temp > TEMP_LIMIT) {
                    console.log('|warning| '+ message);
                    res.write('|warning|');
                } else {
                    console.log('|normal|'+ message);
                    res.write('|normal|');
                }
            } 
        }
        res.end();  
    });
});


io.on('connection', function(socket){
    var socketID = socket.id;
var client = socket.request.connection.remoteAddress;
  console.log('a user connected. Socket ID: ' + socketID + "|| Cliente: " + client );
  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
});



app.get('/', function(req, res) {
    res.sendFile(__dirname + '/public/index.html');
});

http.listen(port, function() {
    console.log('Server running on port: ' + port);
});
