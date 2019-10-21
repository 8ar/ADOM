#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>




	// const char* ssid     = "ICAPSA";
	// const char* password = "ICA980914F72";
  const char* ssid     = "HOME-8269";
	const char* password = "C7FEA1E0C8CA54EF";
	const char *mqtt_server = "8ardom.ga";
	const int mqtt_port = 1883;
	const char *mqtt_user = "Carlos Ochoa";
	const char *mqtt_pass = "40bd001563085fc35165329ea1ff5c5ecbdbbeef";
  // char device_id="00002-1234";
  // char usertopic="20/#";
	const char *switch_topic="20/airc/00001-88889";
 // string subtopic="switch/"+ device_id;
 // string switch_topic=usertopic.replace(,);
  // #define LED_BUILTIN 4


	WiFiClient espClient;
	PubSubClient client(espClient);
  SoftwareSerial ESP8266W(D8,D3);

	long lastMsg = 0;
	char msg[80];

	int temp1 = 0;
	int temp2 = 1;
	int volts = 2;

	//*****************************
	//*** DECLARACION FUNCIONES ***
	//*****************************
	void setup_wifi();
	void callback(char* switch_topic, byte* payload, unsigned int length);
	void reconnect();

	void setup() {
	pinMode(D0, OUTPUT);
	pinMode(D1, OUTPUT);
	// pinMode(D2, OUTPUT);
	// pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	// pinMode(D5, OUTPUT);
	// pinMode(D6, OUTPUT);
	// pinMode(D7, OUTPUT);


ESP8266W.begin(4800);

	Serial.begin(115200);
	randomSeed(micros());
	setup_wifi();
	client.setServer(mqtt_server, mqtt_port);
	client.setCallback(callback);
}

void loop() {
if (!client.connected()) {
reconnect();
}
client.loop();

}

//*****************************
//***    CONEXION WIFI      ***
//*****************************
void setup_wifi(){
delay(10);
// Nos conectamos a nuestra red Wifi
Serial.println();
Serial.print("Conectando a ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

Serial.println("");
Serial.println("Conectado a red WiFi!");
Serial.println("Dirección IP: ");
Serial.println(WiFi.localIP());
}
//*****************************
//***    CONEXION MQTT      ***
//*****************************
void callback(char* topic, byte* payload, unsigned int length){
String incoming = "";
Serial.print("Mensaje recibido desde -> ");
Serial.print(topic);
Serial.println("");
for (unsigned int i = 0; i < length; i++) {
incoming += (char)payload[i];
}

incoming.trim();
Serial.println("Mensaje -> " + incoming);

ESP8266W.print(incoming);


}
// if ( incoming == "on") {
// digitalWrite(LED_BUILTIN, HIGH);
// } else {
// digitalWrite(LED_BUILTIN, LOW);
// }
// }

void reconnect() {

while (!client.connected()) {
Serial.print("Intentando conexión Mqtt...");
// Creamos un cliente ID
String clientId = "esp32_";
clientId += String(random(0xffff), HEX);
// Intentamos conectar
if (client.connect(clientId.c_str(),mqtt_user,mqtt_pass)) {
Serial.println("Conectado!");
// Nos suscribimos
Serial.println(switch_topic);
client.subscribe(switch_topic);

} else {
Serial.print("falló :( con error -> ");
Serial.print(client.state());
Serial.println(" Intentamos de nuevo en 5 segundos");

delay(5000);
}
}
}
