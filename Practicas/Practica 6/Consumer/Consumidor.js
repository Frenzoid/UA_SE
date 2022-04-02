const mqtt = require('mqtt');
const client = mqtt.connect('mqtt://oldbox.cloud');

let arduinos = [Array(31), Array(31), Array(31)];

client.on('connect', () => {
    client.subscribe('SE/practicaUA2022/murcia');
});

client.on('message', (topic, message) => {
    let msg = message.toString();
    let msg_split = msg.split(':');

    switch (msg_split[0]) {
        case 'alex': if (arduinos[0].length != 31) arduinos[0].push(msg_split[1]); break;
        case 'fran': if (arduinos[1].length != 31) arduinos[1].push(msg_split[1]); break;
        case 'javi': if (arduinos[2].length != 31) arduinos[2].push(msg_split[1]); break;
    }

    if (arduinos.every(arduino => arduino.length == 31)) {
        let a = median(arduinos[0]);
        let b = median(arduinos[1]);
        let c = median(arduinos[2]);

        let [x, y] = trilateration(a, b, c);
        let arduinos = [Array(31), Array(31), Array(31)];

        client.publish('SE/practicaUA2022/murcia', [x, y].toString());
    }
});

// function de trilateracion en dos dimensiones
function trilateration(a, b, c) {
    let x = (Math.pow(b, 2) - Math.pow(c, 2) + Math.pow(a, 2)) / (2 * a);
    let y = Math.sqrt(Math.pow(b, 2) - Math.pow(x, 2));
    return [x, y];
}

// obten la mediana de un array de valores
function median(values) {
    values.sort(function (a, b) { return a - b; });
    let half = Math.floor(values.length / 2);
    if (values.length % 2)
        return values[half];
    else
        return (values[half - 1] + values[half]) / 2.0;
}
