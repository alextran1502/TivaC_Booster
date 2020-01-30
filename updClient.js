var udp = require('dgram');

// --------------------creating a udp server --------------------

// creating a udp server
var socket = udp.createSocket('udp4');
socket.bind(2283)

socket.on('message',  (msg, rinfo) => {
    console.log(msg.toString('utf8'))
    console.log(msg)
})

socket.on('listening', () => {
    console.log('listening')
    const address = socket.address()
    console.log(`server listening ${address.address}:${address.port}`);
})
    