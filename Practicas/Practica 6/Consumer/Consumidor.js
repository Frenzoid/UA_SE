const mqtt = require('mqtt');
const trilateration = require('trilateration');
const client = mqtt.connect('mqtt://oldbox.cloud');

// CAOS
let distance = [];
let intensity = [];

distance.push(0);  
distance.push(25);
distance.push(50);
distance.push(75);
distance.push(100);
distance.push(125);
distance.push(150);
distance.push(175);
distance.push(200);
distance.push(225);
distance.push(250);

intensity.push(-43);
intensity.push(-52);
intensity.push(-74);
intensity.push(-77);
intensity.push(-83);
intensity.push(-85);
intensity.push(-87);
intensity.push(-85);
intensity.push(-93);
intensity.push(-97);
intensity.push(-99);


let arduinos = [Array(), Array(), Array()];

client.on('connect', () => {
    client.subscribe('SE/practicaUA2022/murcia');
});

// El mensaje recibido serla del formato nombre:valor
client.on('message', (topic, message) => {
    let msg = message.toString();
    let [arduino, inte] = msg.split(':');

    switch (arduino) {
        case 'alex': if (arduinos[0].length <= 31) arduinos[0].push(inte); break;
        case 'fran': if (arduinos[1].length <= 31) arduinos[1].push(inte); break;
        case 'javi': if (arduinos[2].length <= 31) arduinos[2].push(inte); break;
    }

    if (arduinos.every(arduino => arduino.length == 31)) {
        let a = median(arduinos[0]);
        let b = median(arduinos[1]);
        let c = median(arduinos[2]);

        a = obtenDistancia(a);
        b = obtenDistancia(b);
        c = obtenDistancia(c);

        let pos = trilateration(a, b, c);
        let arduinos = [Array(), Array(), Array()];

        client.publish('SE/practicaUA2022/arduinocloud', [pos.x, pos.y].toString());
    }
});

// function de trilateracion en dos dimensiones
function trilateration(a, b, c) {
    
    // Adding three beacons
    trilateration.addBeacon(0, trilateration.vector(2, 4));
    trilateration.addBeacon(1, trilateration.vector(5.5, 13));
    trilateration.addBeacon(2, trilateration.vector(11.5, 2));
    
    // Setting the beacons distances
    trilateration.setDistance(0, a);
    trilateration.setDistance(1, b);
    trilateration.setDistance(2, c);
    
    // Start Calculation
    return trilateration.calculatePosition();
    
}

// obten la mediana de un array de valores
function median(values) {
    values.sort((a, b) => a - b);
    let half = Math.floor(values.length / 2);
    if (values.length % 2)
        return values[half];
    else
        return (values[half - 1] + values[half]) / 2.0;
}


// Obtiene la distancia basada en la intensitynsidad
function obtenDistancia(ints) {
    let pos = intensity.findIndex((element) => ints >= element );
    console.log(pos, distance[pos], distance[pos - 1], intensity[pos], intensity[pos - 1]);
    return distance[pos - 1] + (ints - intensity[pos - 1]) * ((distance[pos] - distance[pos - 1]) / (intensity[pos] - intensity[pos - 1]));
}