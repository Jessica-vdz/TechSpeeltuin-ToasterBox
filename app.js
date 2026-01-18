const {SerialPort} = require('serialport');
const {ReadlineParser} = require('@serialport/parser-readline');

const port = new SerialPort({
  path: 'COM4',
  baudRate: 9600
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));
parser.on('data', (data) => {
  console.log(`Received data: ${data}`);
});
port.on('open', () => {
  console.log('Serial Port Opened');
});
port.on('error', (err) => {
    console.error('Error: ', err.message);
});