// const dgram = require('dgram');
// const server = dgram.createSocket('udp4');
// let package_count = 0;
// let is_ack;
// server.on('error', (err) => {
//     console.log(`server error:\n${err.stack}`);
//     server.close();
// });

// server.on('message', (msg, rinfo) => {
    
//     console.log(`=== New Packakge [${package_count++}]`);
//     console.log(`HEADER [${msg[0]}], NUM OF SENSOR [${msg[1]}]`);
//     console.log(`Content[${msg.length}]:${msg.slice(2)} from ${rinfo.address}:${rinfo.port}\n`);
// });

// server.on('listening', () => {
//     const address = server.address();
//     console.log(`server listening ${address.address}:${address.port}`);
// });


// server.on('close', () => {
//     const address = server.address();
//     console.log(`server Closed ${address.address}:${address.port}`);
// });



// server.bind(2283);



/* TCP */
var net = require('net');
var buffer = new Buffer.from([0xDE, 0xAB, 0xAA, 0xA1, 0xA2])
var client = new net.Socket();
client.connect(1824, '192.168.15.25', function() {
    console.log('Connected');
    client.write(buffer);
});

client.on('data', function(data) {
	console.log('Received: ' + parseInt(data, 16));
	client.destroy(); // kill client after server's response
});

client.on('close', function() {
	console.log('Connection closed');
});


// var net = require('net');

// var server = net.createServer(function(socket) {
// 	socket.write('Echo server\r\n');
// 	socket.pipe(socket);
// });

// server.listen(7, '192.168.15.2');