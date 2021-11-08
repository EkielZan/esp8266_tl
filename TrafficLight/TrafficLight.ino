#include "TrafficLight.h"
#include <ESP8266WiFi.h>

int redPin = 16;
int yellowPin = 4;
int greenPin = 2;

TrafficLight tl(redPin, yellowPin, greenPin);

// Replace with your network credentials
const char* ssid     = "Teuchteuch";
const char* password = "vajustegi";

String header;

String tlState = "off";

// Set web server port number to 80
WiFiServer server(80);

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello Everyone");
  Serial.println("This is Traffic Light Control 0.1");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  tl.AllUp();
}

void tlrun() {
  tl.Stop();
  delay(5000); //5 seconds
  tl.Go();
  delay(7000); //7 seconds
  tl.Careful();
  delay(2000); //2 seconds
}
void tlstop(){
  tl.Down();  
}

void loop() {
  Serial.println("TL Start a loop");
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /tl/on") >= 0) {
              Serial.println("TL is on");
              tlState = "on";
            } else if (header.indexOf("GET /tl/off") >= 0) {
              Serial.println("TL is off");
              tlState = "off";
            } 

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP8266 Traffic Light Web Server</h1>");

            // Display current state, and ON/OFF for TrafficLight run
            client.println("<p>TL - State " + tlState + "</p>");
            // If the tlState is off, it displays the ON button
            if (tlState == "off") {
              client.println("<p><a href=\"/tl/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/tl/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  if (tlState == "on"){
    tlrun();
  }else{
    tlstop();
  }

  /*
  tl.Stop();
  delay(5000); //5 seconds
  tl.Go();
  delay(5000); //7 seconds
  tl.Careful();
  delay(2000); //2 seconds
  Serial.println("TL Made a loop");
  */
}
