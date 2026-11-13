/*
  Smart Room Climate & Ventilation Assistant
  Board: ESP32 (Wokwi)
 Components: ESP32, DHT22, Servo motor, LED, Buzzer

Logic: When temperature or humidity exceeds the
configured threshold, the system activates visual
and audible alerts and rotates the servo motor
to represent opening a ventilation flap.
*/

#include <DHT.h>
#include <ESP32Servo.h>

// ---------- Pin configuration ----------
#define DHT_PIN     15
#define DHT_TYPE    DHT22
#define LED_PIN     26
#define BUZZER_PIN  27
#define SERVO_PIN   18

// ---------- Safe thresholds ----------
const float TEMP_THRESHOLD = 30.0;   // deg C
const float HUM_THRESHOLD  = 70.0;   // %

// ---------- Servo positions ----------
const int FAN_OFF_ANGLE = 0;
const int FAN_ON_ANGLE  = 90;

DHT dht(DHT_PIN, DHT_TYPE);
Servo exhaustFan;

// Beep without tone() so the buzzer does not interfere with the servo PWM
void beep(int frequency, int durationMs) {
  long halfPeriod = 1000000L / frequency / 2;          // microseconds
  long cycles = (long)frequency * durationMs / 1000;
  for (long i = 0; i < cycles; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(halfPeriod);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  exhaustFan.setPeriodHertz(50);            // standard servo frequency
  exhaustFan.attach(SERVO_PIN, 500, 2400);  // min/max pulse width (us)
  exhaustFan.write(FAN_OFF_ANGLE);
  delay(500);                               // let the servo settle at 0 deg

  Serial.println("Smart Room Climate & Ventilation Assistant started");
  Serial.printf("Thresholds -> Temp: %.1f C | Humidity: %.1f %%\n",
                TEMP_THRESHOLD, HUM_THRESHOLD);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  // Check for sensor errors
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error: Failed to read from DHT22 sensor!");
    delay(2000);
    return;
  }

  bool tempHigh = temperature > TEMP_THRESHOLD;
  bool humHigh  = humidity > HUM_THRESHOLD;
  bool alert    = tempHigh || humHigh;

  Serial.printf("Temp: %.1f C | Humidity: %.1f %% | ", temperature, humidity);

  if (alert) {
    digitalWrite(LED_PIN, HIGH);          // Visual alert
    exhaustFan.write(FAN_ON_ANGLE);       // Ventilation ON

    Serial.print("ALERT: ");
    if (tempHigh) Serial.print("ALERT: High Temperature ");
    if (humHigh)  Serial.print("ALERT: High Humidity ");
    Serial.println("-> Ventilation ON");

    beep(1000, 500);                      // Audible alert
    delay(1500);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    exhaustFan.write(FAN_OFF_ANGLE);      // Ventilation OFF

    Serial.println("Status: Normal -> Ventilation OFF");
    delay(2000);
  }
}
