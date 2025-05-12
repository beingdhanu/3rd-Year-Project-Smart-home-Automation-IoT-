#define BLYNK_TEMPLATE_ID           "TMPL6Z0oE-fCq"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "d5n6NjbC05TxGhG51ZFUMDnxzmBairVb"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WebServer.h>

// WiFi credentials
char ssid[] = "Gandaki-University-Student";   // Replace with your WiFi SSID
char pass[] = "GU@Std2023";    // Replace with your WiFi password

// Relay pins
int relayPin1 = D7;
int relayPin2 = D8;
int relayPin3 = D5;
int relayPin4 = D6;

// Track relay states
bool relayState1 = LOW;
bool relayState2 = LOW;
bool relayState3 = LOW;
bool relayState4 = LOW;

// Web server on port 80
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Configure relay pins as outputs
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);

  // Initialize relay states
  digitalWrite(relayPin1, relayState1);
  digitalWrite(relayPin2, relayState2);
  digitalWrite(relayPin3, relayState3);
  digitalWrite(relayPin4, relayState4);

  // Start the local web server
  server.begin();
  Serial.println("Local server started!");
  Serial.print("Access the server at: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  Blynk.run(); // Process Blynk app commands
  handleClient(); // Process local server requests
}

// Handle requests from the local server
void handleClient()
{
  WiFiClient client = server.available();
  if (!client)
    return;

  String request = client.readStringUntil('\r');
  client.flush();

  // Parse requests for each relay
  if (request.indexOf("/relay1/on") != -1) {
    relayState1 = HIGH;
    digitalWrite(relayPin1, relayState1);
  }
  if (request.indexOf("/relay1/off") != -1) {
    relayState1 = LOW;
    digitalWrite(relayPin1, relayState1);
  }
  if (request.indexOf("/relay2/on") != -1) {
    relayState2 = HIGH;
    digitalWrite(relayPin2, relayState2);
  }
  if (request.indexOf("/relay2/off") != -1) {
    relayState2 = LOW;
    digitalWrite(relayPin2, relayState2);
  }
  if (request.indexOf("/relay3/on") != -1) {
    relayState3 = HIGH;
    digitalWrite(relayPin3, relayState3);
  }
  if (request.indexOf("/relay3/off") != -1) {
    relayState3 = LOW;
    digitalWrite(relayPin3, relayState3);
  }
  if (request.indexOf("/relay4/on") != -1) {
    relayState4 = HIGH;
    digitalWrite(relayPin4, relayState4);
  }
  if (request.indexOf("/relay4/off") != -1) {
    relayState4 = LOW;
    digitalWrite(relayPin4, relayState4);
  }

  // Send an HTML response
  client.print("HTTP/1.1 200 OK\r\n");
  client.print("Content-Type: text/html\r\n");
  client.print("Connection: close\r\n\r\n");

  client.print("<!DOCTYPE HTML>");
  client.print("<html>");
  client.print("<h1> Smart Home Automation</h1>");
  client.print("<p>Relay 1: <a href=\"/relay1/on\">ON</a> | <a href=\"/relay1/off\">OFF</a></p>");
  client.print("<p>Relay 2: <a href=\"/relay2/on\">ON</a> | <a href=\"/relay2/off\">OFF</a></p>");
  client.print("<p>Relay 3: <a href=\"/relay3/on\">ON</a> | <a href=\"/relay3/off\">OFF</a></p>");
  client.print("<p>Relay 4: <a href=\"/relay4/on\">ON</a> | <a href=\"/relay4/off\">OFF</a></p>");

  client.print("</html>");
}

BLYNK_WRITE(V3) {
  int pinValue = param.asInt();
  relayState1 = pinValue;
  digitalWrite(relayPin1, relayState1);
}

BLYNK_WRITE(V4) {
  int pinValue = param.asInt();
  relayState2 = pinValue;
  digitalWrite(relayPin2, relayState2);
}

BLYNK_WRITE(V5) {
  int pinValue = param.asInt();
  relayState3 = pinValue;
  digitalWrite(relayPin3, relayState3);
}

BLYNK_WRITE(V6) {
  int pinValue = param.asInt();
  relayState4 = pinValue;
  digitalWrite(relayPin4, relayState4);
}
