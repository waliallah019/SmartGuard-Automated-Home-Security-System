#include <WiFi.h>
#include <PubSubClient.h>   

// WiFi Credentials
const char *ssid = "Welcome Net jazeb";        // Enter your WiFi name
const char *password = "Jazeb786..";    // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "Broker.hivemq.com";
const char *topic = "buzzer/control";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  // Set software serial baud to 9600;
  Serial.begin(9600);

  // Use ESP32 buit-in LED to indicate the state of WiFi and MQTT
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, HIGH); // LED ON while No WiFi
    delay(500);
    //Serial.println("Connecting to WiFi..");
  }
  //Serial.println("Connected to the WiFi network");
  digitalWrite(LED_BUILTIN, LOW); // LED OFF when connected to WiFi
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  while (!client.connected())
  {
    digitalWrite(LED_BUILTIN, HIGH); // LED ON while No MQTT Connection
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    //Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str()))
    {
        //Serial.println("MQTT Broker Connected Successfully");
        digitalWrite(LED_BUILTIN, LOW); // LED OFF when connected to MQTT Server
    }
    else
    {
        //Serial.print("MQTT connection failed with state ");
        //Serial.print(client.state());
        delay(2000);
    }
  }
  // publish and subscribe
  client.publish(topic, "I'm ESP32");   // Testing MQTT publish
  client.subscribe(topic);              // Subscribing to a MQTT topic
}

void callback(char *topic, byte *payload, unsigned int length)
{
 //Serial.print("Message arrived in topic: ");
 //Serial.println(topic);
 //Serial.print("Message:");
 for (int i = 0; i < length; i++)
 {
     Serial.print((char) payload[i]);
 }
 //Serial.println();
 //Serial.println("-----------------------");
}

void loop()
{
 client.loop();
 delay(2000);
}