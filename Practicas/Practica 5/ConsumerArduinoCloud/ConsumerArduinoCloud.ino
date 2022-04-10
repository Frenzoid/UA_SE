// ArduinoMqttClient - Version: Latest 
#include <ArduinoMqttClient.h>
#include "thingProperties.h";

const char brokerMosq[] = "test.mosquitto.org";
int        portMosq     = 1883;
const char topicMosq[]  = "SE/practicaUA2022/murcia";

MqttClient mqttClient = NULL;

void setup() {
  Serial.begin(9600);
  delay(1500); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  mqttClient = new MqttClient(ArduinoIoTPreferredConnection.getClient());

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(brokerMosq);

   if (!mqttClient.connect(brokerMosq, portMosq)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topicMosq);
  Serial.println();

  mqttClient.subscribe(topicMosq);
  Serial.print("Waiting for messages on topic: ");
  Serial.println(topicMosq);
  Serial.println();
}



void loop() {
  ArduinoCloud.update();

  while (mqttClient.available()) {
    Serial.print((float)mqttClient.read());
    ejercicio = (float)mqttClient.read();
  }
}


void onDataChange()  {}
void onEjercicioChange()  {}
