#include <DHT.h>

#define DHTPIN 2       // DATA pin
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  dht.begin();

  delay(1000);
 
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "PING") {
      Serial.println("PONG");
    }

    else if (cmd == "PING_B") {
      Serial.println("B_OK");
    }

    else if (cmd == "LED_ON_B") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("OK");
    }

    else if (cmd == "LED_OFF_B") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("OK");
    }

    else if (cmd == "GET_TEMP") {
      float temp = dht.readTemperature();

      if (isnan(temp)) {
        Serial.println("TEMP_ERROR");
      } else {
        Serial.print("TEMP:");
        Serial.println(temp,1);// decimal
      }
    }

    else if (cmd == "FAULT_SENSOR") {
     Serial.println("TEMP:999.0");  // Invalid temperature value
    }

    else if (cmd == "FAULT_NOISE") {
      Serial.println("T#MP:2@.4");   // Corrupted message
    }

    else if (cmd == "FAULT_NO_RESPONSE") {
      delay(3000);                  // Simulate timeout / no response
    } 

    else {
      Serial.println("ERROR");
    }
  }
}