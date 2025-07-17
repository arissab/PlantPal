#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

#define CMD_PLAY_NEXT 0x01
#define CMD_PLAY_PREV 0x02
#define CMD_PLAY_W_INDEX 0x03
#define CMD_SET_VOLUME 0x06
#define CMD_SEL_DEV 0x09
#define CMD_PLAY_W_VOL 0x22
#define CMD_PLAY 0x0D
#define CMD_PAUSE 0x0E
#define CMD_SINGLE_CYCLE 0x19

#define DEV_TF 0x02
#define SINGLE_CYCLE_ON 0x00
#define SINGLE_CYCLE_OFF 0x01

#define ESP8266_RX D5  // The ESP8266 pin connected to the TX of the Serial MP3 Player module
#define ESP8266_TX D6  // The ESP8266 pin connected to the RX of the Serial MP3 Player module
#define MOTION_SENSOR_PIN  D7  // The ESP8266 pin D7 connected to the OUTPUT pin of motion sensor
#define LED_PIN            D1  // The ESP8266 pin D1 connected to LED's pin
#define AOUT_PIN A0 //For soil moisture sensor 

// Replace with your network credentials
const char* ssid     = "Dojo";
const char* password = "MangoLassi";

// Set web server port number to 80
ESP8266WebServer server(80);

SoftwareSerial mp3(ESP8266_RX, ESP8266_TX);

int motion_state  = LOW; // current state of motion sensor's pin
int prev_motion_state = LOW; // previous state of motion sensor's pin
int value = 0;
String motion_display = "None";
String soil = "Wet";

// Variables to control reading interval
unsigned long previousReadTime = 0;
const long readInterval = 8000; // Read every

void setup() {
  Serial.begin(115200);

  mp3.begin(9600);
  delay(500);  // wait for chip initialization to complete

  mp3_command(CMD_SEL_DEV, DEV_TF);  // select the TF card
  delay(200);                        // wait for 200ms

  // Initialize the output variables as outputs
  pinMode(MOTION_SENSOR_PIN, INPUT); // Configure the ESP8266 pin to the input mode
  //pinMode(LED_PIN, OUTPUT);          // Configure the ESP8266 pin to the output mode
  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi network with SSID and password
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
  
  // Define endpoints
  server.on("/", handleRoot);
  server.on("/data", handleData);
  
  server.begin();
}

void loop() {
  server.handleClient();
  

  prev_motion_state = motion_state;             // store old state
  motion_state  = digitalRead(MOTION_SENSOR_PIN); // read new state
  if (prev_motion_state == LOW && motion_state == HIGH) { // pin state change: LOW -> HIGH
    Serial.println("Motion detected!, turns LED ON and plays sound");
    digitalWrite(LED_PIN, HIGH); // turn on LED
    motion_display = "Detected";
    mp3_command(CMD_PLAY_W_INDEX, 0x0001); // Play track 1
  } 
  else if (prev_motion_state == HIGH && motion_state == LOW) { // pin state change: HIGH -> LOW
    //Serial.println("Motion stopped!, turns LED OFF ");
    digitalWrite(LED_PIN, LOW);  // turn off LED
    motion_display = "None";
  }


  unsigned long currentReadTime = millis();
  if (currentReadTime - previousReadTime >= readInterval) {
    previousReadTime = currentReadTime;
    value = analogRead(AOUT_PIN);
    Serial.println("Analog value read: " + String(value));

    if (value > 260) {
    Serial.println("Soil is dry!, turns LED ON and plays sound");
    digitalWrite(LED_PIN, HIGH); // turn on LED
    soil = "Dry";
    mp3_command(CMD_PLAY_W_INDEX, 0x0002); // Play a different MP3 sound (track 2)
    } 
    else {
      // If soil moisture is not less than 300, ensure LED is off if motion is not detected
      if (motion_state == LOW) {
        soil = "Wet";
        digitalWrite(LED_PIN, LOW); // turn off LED
      }
    }

  }

}

void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  html += "body { background-color: #e5ffe5; color: #006400; margin: 0; padding: 0;}";
  html += "h1 { color: #228B22; font-size: 2.5em; margin-bottom: 0.5em;}";
  html += "p { font-size: 1.2em; margin: 0.5em 0;}";
  html += ".container { padding: 20px; border-radius: 10px; background-color: #f0fff0; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); display: inline-block;}";
  html += ".button { background-color: #32CD32; border: none; color: white; padding: 16px 20px;";
  html += "text-decoration: none; font-size: 30px; margin: 10px; cursor: pointer; border-radius: 10px;}";
  html += ".button2 { background-color: #77878A; }";
  html += ".plant-icon { width: 50px; height: auto; vertical-align: middle;}";
  html += "</style></head>";
  html += "<body><h1>Plant Watering Tracker</h1>";
  html += "<div class='container'>";
  html += "<p>Soil Moisture Level: <span id='plant'>" + String(value) + ", " + soil + "</span></p>";
  html += "<p>Motion: <span id='motion_display'>" + motion_display + "</span></p>";
  html += "</div>";
  html += "<script>setInterval(function() { fetch('/data').then(response => response.json()).then(data => { document.getElementById('plant').innerHTML = data.plant; document.getElementById('motion_display').innerHTML = data.motion_display; }); }, 1000);</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleData() {
  String json = "{";
  json += "\"plant\": \"" + String(value) + ", " + soil + "\",";
  json += "\"motion_display\": \"" + motion_display + "\"";
  json += "}";
  server.send(200, "application/json", json);
}

void mp3_command(int8_t command, int16_t dat) {
  int8_t frame[8] = { 0 };
  frame[0] = 0x7e;                // starting byte
  frame[1] = 0xff;                // version
  frame[2] = 0x06;                // The number of bytes of the command without starting byte and ending byte
  frame[3] = command;             //
  frame[4] = 0x00;                // 0x00 = no feedback, 0x01 = feedback
  frame[5] = (int8_t)(dat >> 8);  // data high byte
  frame[6] = (int8_t)(dat);       // data low byte
  frame[7] = 0xef;                // ending byte
  for (uint8_t i = 0; i < 8; i++) {
    mp3.write(frame[i]);
  }
}
