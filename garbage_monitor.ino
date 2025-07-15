#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Garbage Monitor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YourAuthToken"; // from Blynk app
char ssid[] = "YourWiFiName";  // WiFi credentials
char pass[] = "YourWiFiPassword";

#define trigPin D5
#define echoPin D6
#define buzzerPin D7

long duration;
int distance;
int binHeight = 30; // in cm - actual height of your bin
int warningLevel = 5; // warn if bin is less than 5cm from top

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  timer.setInterval(2000L, checkLevel); // every 2 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}

void checkLevel() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  int filled = binHeight - distance;
  if (filled < 0) filled = 0;
  int percentFull = map(filled, 0, binHeight, 0, 100);

  Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
  Serial.print("Full: "); Serial.print(percentFull); Serial.println(" %");

  Blynk.virtualWrite(V0, percentFull); // Send to Blynk app (V0 gauge)

  if (distance <= warningLevel) {
    digitalWrite(buzzerPin, HIGH); // turn on buzzer
    Blynk.logEvent("garbage_alert", "Garbage bin almost full!");
  } else {
    digitalWrite(buzzerPin, LOW); // turn off buzzer
  }
}
