const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const json = require('./data.json');

const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

const port = new SerialPort({ path: 'COM3', baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

let discKleur = null;

parser.on('data', (incoming) => {
  incoming = incoming.trim();

  if (!discKleur) {
    discKleur = incoming;
    return;
  }

  const nummer = parseInt(incoming);
  const index = nummer - 1;

  if (!json.disc[discKleur] || index < 0 || index > 4) {
    discKleur = null;
    return;
  }

  const description = json.disc[discKleur][index];

  // Stuur data naar browser via WebSocket
  io.emit('discData', {
    kleur: discKleur,
    nummer: nummer,
    description: description
  });

  discKleur = null;
});


app.use(express.static('site'));

server.listen(3000, () => {
  console.log('Server is running on http://localhost:3000');
});
