#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <SPI.h>

// Wi-Fi credentials
const char* ssid = "Ritik";           // Your Wi-Fi SSID
const char* password = "8291189618";  // Your Wi-Fi Password

// Telegram bot credentials
#define BOTtoken "7975714129:AAEQswLc6QGrxxzq4eqb_xNS5HrhdMQLdZU"  // Your Bot Token
String CHAT_ID = "1189260508";                                     // Your Chat ID
String ALLOWED_CHAT_IDS = "1189260508";  

// Sensor pins and constants
#define DHTPIN 19        // Pin for DHT11 sensor
#define DHTTYPE DHT11    // DHT 11
#define MQ2_PIN 34       // Analog pin for MQ2 gas sensor
#define FIRE_PIN 5       // Digital pin for fire sensor
#define BUZZER_PIN 2     // Digital pin for active-low buzzer
#define ALERT_THRESHOLD 2500  // Threshold for gas sensor alert

LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD address 0x27, 16 chars, 2 lines
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastReadTime = 0;
const unsigned long readInterval = 2000;   // 2 seconds for reading sensors

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 500;
unsigned long lastTimeBotRan;

void setup() {
  pinMode(MQ2_PIN, INPUT);
  pinMode(FIRE_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(115200);

  lcd.begin();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("System Starting");
  delay(2000);  // Initial delay for startup
  lcd.clear();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000) {  // 30 seconds timeout
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi. Please check your credentials.");
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connect Fail");
    return;  // Exit setup or implement a retry mechanism
  }

  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!");
  delay(1000);
  lcd.clear();
}

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (ALLOWED_CHAT_IDS.indexOf(chat_id) == -1) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    String text = bot.messages[i].text;
    Serial.println(text);
    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      bot.sendMessage(chat_id, "Welcome, " + from_name + ".\nUse /menu to see options.", "");
    } else if (text == "/menu") {
      String menu = "Select an option:\n";
      menu += "/sensor - Check Sensor Readings\n";
      menu += "/stop_buzzer - Stop Buzzer\n";
      bot.sendMessage(chat_id, menu, "");
    } else if (text == "/sensor") {
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      int smokeValue = analogRead(MQ2_PIN); 
      int flameState = digitalRead(FIRE_PIN);

      // Check if readings failed
      if (isnan(h) || isnan(t)) {
        bot.sendMessage(chat_id, "Failed to read from DHT sensor!", "");
      } else {
        String sensorReport = "Humidity: " + String(h) + "%\n";
        sensorReport += "Temperature: " + String(t) + "C\n";
        sensorReport += "Smoke Value: " + String(smokeValue) + "\n";
        sensorReport += (flameState == HIGH) ? "Flame: No\n" : "Flame: Yes\n";
        bot.sendMessage(chat_id, sensorReport, "");
      }
    } else if (text == "/stop_buzzer") {
      digitalWrite(BUZZER_PIN, LOW);  // Stop buzzer
      bot.sendMessage(chat_id, "Buzzer stopped.", "");
    }
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Handle Telegram bot messages
  if (currentMillis > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    if (numNewMessages > 0) {
      handleNewMessages(numNewMessages);
    }
    lastTimeBotRan = millis();
  }

  // Read sensors at intervals using millis()
  if (currentMillis - lastReadTime >= readInterval) {
    lastReadTime = currentMillis;

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int gasValue = analogRead(MQ2_PIN); 
    int fireValue = digitalRead(FIRE_PIN);  // Check fire sensor state

    Serial.print("Gas Sensor Value: ");
    Serial.println(gasValue);

    // Display temperature and humidity
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(humidity);
    lcd.print(" %");
    delay(1000);

    // Display gas and fire sensor values
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas: ");
    lcd.print(gasValue);

    lcd.setCursor(0, 1);
    lcd.print("Fire: ");
    lcd.print(fireValue ? "No" : "Yes");
    delay(1000);

    // Trigger alert based on sensor readings
    if (gasValue > ALERT_THRESHOLD || fireValue == LOW) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ALERT! Danger!");

      digitalWrite(BUZZER_PIN, HIGH);  // Turn buzzer ON

      String alertMessage = "Dangerous conditions detected!\n";
      alertMessage += "Gas Sensor Value: " + String(gasValue) + "\n";
      alertMessage += (fireValue == LOW) ? "Fire Detected!\n" : "No Fire Detected\n";
      bot.sendMessage(CHAT_ID, alertMessage, "");

    } else {
      digitalWrite(BUZZER_PIN, LOW);  // Turn buzzer OFF
    }
  }
}
