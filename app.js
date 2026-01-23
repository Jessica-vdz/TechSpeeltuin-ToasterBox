const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const json = require('./data.json');

const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

const port = new SerialPort({ path: 'COM4', baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

parser.on('data', (incoming) => {
  incoming = incoming.trim().toLowerCase();
  console.log('SERIAL:', incoming);

  if (!incoming.includes(',')) return;

  const parts = incoming.split(',');

  if (parts.length !== 2) return;

  const kleur = parts[0];
  const nummer = parseInt(parts[1], 10);

  if (!['red', 'yellow'].includes(kleur)) return;
  if (isNaN(nummer) || nummer < 1 || nummer > 3) return;

  const index = nummer - 1;

  io.emit('discData', {
    kleur,
    nummer,
    videoDescription: json.videoDescription[kleur][index],
    videoTitle: json.videoTitle[kleur][index],
    discInfo: json.discInfo[kleur],
    discImg: json.discImg[kleur],
    discVideoLink: json.videoLink[kleur][index]

  });
});

app.use(express.static('site'));

server.listen(3000, () => {
  console.log('Server is running on http://localhost:3000');
});
