#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
#include <MD_MAX72xx.h>

// =====================================================
// WIFI
// =====================================================

const char* ssid = "vivo Y300 5G";
const char* password = "ajikumar1";

WebServer server(80);


// =====================================================
// PIR SENSORS
// =====================================================

#define PIR1 34
#define PIR2 35


// =====================================================
// MAX7219 MATRIX
// =====================================================

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

#define DATA_PIN 23
#define CLK_PIN 22
#define CS_PIN 21

MD_MAX72XX matrix(
  HARDWARE_TYPE,
  DATA_PIN,
  CLK_PIN,
  CS_PIN,
  MAX_DEVICES
);


// =====================================================
// SENSOR VARIABLES
// =====================================================

int pir1 = 0;
int pir2 = 0;


// =====================================================
// WEBPAGE
// =====================================================

void handleRoot()
{
  // Read PIR sensors
  pir1 = digitalRead(PIR1);
  pir2 = digitalRead(PIR2);

  String message;

  if (pir1 == HIGH || pir2 == HIGH)
  {
    message = "WELCOME!";
  }
  else
  {
    message = "Waiting for Visitor...";
  }


  // ===================================================
  // HTML PAGE
  // ===================================================

  String page = R"rawliteral(
<!DOCTYPE html>

<html>

<head>

<meta name="viewport"
content="width=device-width, initial-scale=1">

<meta http-equiv="refresh" content="1">

<style>

body
{
  background:#111;
  color:white;
  font-family:Arial;
  text-align:center;
  padding-top:40px;
}

h1
{
  color:#00ff99;
  font-size:48px;
}

h2
{
  color:white;
  font-size:34px;
  margin-top:30px;
}

p
{
  font-size:24px;
  margin:15px;
}

.status
{
  margin:30px auto;
  padding:20px;
  max-width:500px;
  border-radius:15px;
  background:#222;
}

</style>

</head>

<body>

<h1>🤖 Welcome Robot</h1>

<div class="status">

<h2>)rawliteral";

  page += message;

  page += R"rawliteral(</h2>

<p>PIR 1 : )rawliteral";

  page += String(pir1);

  page += R"rawliteral(</p>

<p>PIR 2 : )rawliteral";

  page += String(pir2);

  page += R"rawliteral(</p>

</div>

</body>

</html>
)rawliteral";


  server.send(200, "text/html", page);
}


// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);


  // ===================================================
  // PIR
  // ===================================================

  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);


  // ===================================================
  // MATRIX
  // ===================================================

  matrix.begin();

  matrix.control(
    MD_MAX72XX::INTENSITY,
    5
  );

  matrix.clear();


  // ===================================================
  // WIFI
  // ===================================================

  Serial.println();
  Serial.println("==============================");
  Serial.println(" ESP32 BOARD 1");
  Serial.println(" WEB SERVER MODE");
  Serial.println("==============================");

  WiFi.mode(WIFI_STA);

  WiFi.begin(
    ssid,
    password
  );

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println();

  Serial.print("Open on phone: http://");
  Serial.println(WiFi.localIP());


  // ===================================================
  // WEB SERVER
  // ===================================================

  server.on("/", handleRoot);

  server.begin();

  Serial.println();
  Serial.println("Web Server Started!");
  Serial.println("==============================");
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
  // Handle phone requests
  server.handleClient();

  // Continuously read PIR
  pir1 = digitalRead(PIR1);
  pir2 = digitalRead(PIR2);
}