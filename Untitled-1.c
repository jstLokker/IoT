#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "time.h"
#include <HX711.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "RouterName";  //replace
const char* password = "Password"; //replace

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 25200;  // Adjust this to your timezone offset
const int daylightOffset_sec = 0;

AsyncWebServer server(80);

// Pin assignments
#define DOUT  21
#define CLK  22
#define BUZZER_PIN 25
#define LED1_PIN 32  // Changed to avoid conflict
#define LED2_PIN 33  // Changed to avoid conflict
#define SERVO_PIN 13

HX711 scale;
Servo myServo;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Time variables
int h = 0;
int m = 0;
int s = 0;
bool ready = false;
int loadThreshold = 100; // Set weight threshold (e.g., 100 grams)

// Variables for tracking load cell weight and the state of the process
float weight = 0.0;
unsigned long startMillis;
bool onTime = false;

#define SSD1306_I2C_ADDRESS 0x3C  // I2C Address for the OLED display

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  char buf[64];
  strftime(buf, sizeof(buf), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(buf);
}

void setup() {
  Serial.begin(115200);

  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  Serial.println(WiFi.localIP());

  // Initialize HX711 load cell
  scale.begin(DOUT, CLK);
  scale.set_scale(2280.f);  // Calibrate with your load cell
  scale.tare();  // Reset the scale to 0

  // Initialize OLED display
  if (!display.begin(SSD1306_I2C_ADDRESS, SDA, SCL)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Initialize Servo
  myServo.attach(SERVO_PIN);
  myServo.write(0);  // Set servo to 0 degrees initially

  // Set pin modes
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  // Start the web server
  server.on("/statetime", HTTP_GET, [](AsyncWebServerRequest *request) {
    String time = String(h) + ":" + String(m) + ":" + String(s);
    request->send(200, "text/plain", time);
  });

  server.on("/hup", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (h < 24 && h >= 0) {
      h = h + 1;
    } else if (h == 24) {
      h = 0;
    }
    ready = false;
    request->send(200, "text/plain", String(h));
  });

  server.on("/mup", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (m < 60 && m >= 0) {
      m = m + 1;
    } else if (m == 60) {
      m = 0;
    }
    ready = false;
    request->send(200, "text/plain", String(m));
  });

  server.on("/sup", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (s < 60 && s >= 0) {
      s = s + 1;
    } else if (s == 60) {
      s = 0;
    }
    ready = false;
    request->send(200, "text/plain", String(s));
  });

  server.on("/done", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "ok");
    ready = true;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(String(h) + ":" + String(m) + ":" + String(s));
    display.display();
  });

  server.begin();
}

void loop() {
  // Read weight from the load cell
  weight = scale.get_units(10);  // Average of 10 readings
  Serial.print("Weight: ");
  Serial.println(weight);

  // If the process is ready, check the current time
  if (ready) {
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      if (timeinfo.tm_hour == h && timeinfo.tm_min == m && timeinfo.tm_sec == s) {
        onTime = true;
        startMillis = millis();  // Start the timer
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Time to Work!");
        display.display();
      }
    }
  }

  // Check if it's time to start the process
  if (onTime) {
    // Turn on the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    // Move the servo to 90 degrees
    myServo.write(90);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Time to work!");
    display.display();

    // Wait until the weight drops to zero
    while (weight > 10) {
      weight = scale.get_units(10);  // Update weight
      delay(500);  // Wait for a while before reading the load cell again
    }

    // Once weight is zero, stop the process
    digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
    myServo.write(0);  // Move servo back to 0 degrees
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Done");
    display.display();

    // Reset for the next cycle
    onTime = false;
    ready = true;
    delay(100);  // Add missing semicolon
    display.print(String(h) + ":" + String(m) + ":" + String(s));
  }
}
// ready