
#include <SPI.h>
#include <MD_MAX72xx.h>
#include<WiFi.h>
#include <WebServer.h>
const char* ssid = "vivo Y300 5G";
const char* password = "ajikumar1";
WebServer server(80);
// ==================== PIR Sensors ===================
#define PIR1 34
#define PIR2 35

// ==================== Ultrasonic Sensor 1 ===========
#define TRIG1 4
#define ECHO1 19


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

#define DATA_PIN 23
#define CLK_PIN 22
#define CS_PIN 21

MD_MAX72XX matrix = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


long getDistance1()
{
  digitalWrite(TRIG1, LOW);
  delay(20000);

  digitalWrite(TRIG1, HIGH);
  delay(10000);

  digitalWrite(TRIG1, LOW);

  long duration = pulseIn(ECHO1, HIGH);

  long distance = duration * 0.034 / 2;

  return distance;
}

void handleRoot()
{
  int pir1 = digitalRead(PIR1);
  int pir2 = digitalRead(PIR2);
  delay(20000);
  long distance = getDistance1();

  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="refresh" content="1">
<style>
body{
font-family:Arial;
background:#111;
color:white;
text-align:center;
}
.box{
margin-top:40px;
    padding:20px;
}

h1{
    color:#00ff99;
    font-size:48px;      /* Increased from default */
    margin-bottom:20px;
}

h2{
    font-size:36px;      /* Welcome/Waiting message */
    color:#ffffff;
    margin-bottom:20px;
}

p{
    font-size:26px;      /* Sensor values */
    margin:12px 0;
}
</style>
</head>
<body>

<div class="box">
<h1>🤖 Welcome Robot</h1>
)rawliteral";

  if (pir1 == HIGH || pir2 == HIGH)
    page += "<h2>Welcome Guest!</h2>";
  else
    page += "<h2>Waiting for Visitor...</h2>";

  page += "<p>Front Distance : " + String(distance) + " cm</p>";
  page += "<p>PIR1 : " + String(pir1) + "</p>";
  page += "<p>PIR2 : " + String(pir2) + "</p>";

  page += "</div></body></html>";

  server.send(200, "text/html", page);
}
void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid,password);
  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
Serial.println();
Serial.println("================================");
Serial.println("WiFi Connected Successfully!");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());

Serial.print("Open this on your phone: http://");
Serial.println(WiFi.localIP());

Serial.print("Signal Strength (RSSI): ");
Serial.print(WiFi.RSSI());
Serial.println(" dBm");

Serial.println("================================");

server.on("/", handleRoot);
server.begin();

Serial.println("Web Server Started");


  matrix.begin();
matrix.control(MD_MAX72XX::INTENSITY, 5);   // Brightness (0-15)
matrix.clear();

// Turn ON every LED
for (uint8_t row = 0; row < 8; row++)
{
    for (uint8_t col = 0; col < 8; col++)
    {
        matrix.setPoint(row, col, true);
    }
}

matrix.update();


  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);


  

  
}
void loop()
{
  // Read Sensors
 server.handleClient();
  int pir1 = digitalRead(PIR1);
  int pir2 = digitalRead(PIR2);

  long distance1 = getDistance1();

  // ===== Serial Monitor =====
  Serial.println("-------------------------");


  Serial.print("PIR1 : ");
  Serial.println(pir1);

  Serial.print("PIR2 : ");
  Serial.println(pir2);

  Serial.print("Front Distance : ");
  Serial.print(distance1);
  Serial.println(" cm");


  // ===== PIR Detection =====
  if (pir1 == HIGH || pir2 == HIGH)
  {
    Serial.println("Human Detected");



    


    delay(500);



    delay(600);


    delay(500);

  

    return;
  } }







