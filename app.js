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
  console.log('SERIAL:', incoming); // prints incomming data to the terminal

  // first data send from arduino (color)
  if (!discKleur) {
    discKleur = incoming.toLowerCase();
    return;
  }

  // second data send from arduino (number)
  const nummer = parseInt(incoming, 10);

  if (isNaN(nummer)) {
    discKleur = null;
    return;
  }

  const index = nummer - 1;

  // Validatie
  if (
    !json.discVideoInfo[discKleur] ||
    !json.discVideoLink[discKleur] ||
    !json.discInfo[discKleur] ||
    index < 0 ||
    index > 4
  ) {
    discKleur = null;
    return;
  }

  const description = json.discVideoInfo[discKleur][index]; //gets data from discVideoInfo out of json
  const videoLink = json.discVideoLink[discKleur][index];
  const discInfo = json.discInfo[discKleur];

io.emit('discData', {
    kleur: discKleur,
    nummer: nummer,
    description: description,
    videoLink: videoLink,
    discInfo: discInfo
  });

  discKleur = null;
});

app.use(express.static('site'));

server.listen(3000, () => {
  console.log('Server is running on http://localhost:3000');
});