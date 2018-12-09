#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <rdm6300.h>

#define RDM6300_RX_PIN 2
#define READ_LED_PIN 13

Rdm6300 rdm6300;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Ready...");

  rdm6300.begin(RDM6300_RX_PIN);

  Serial.begin(9600);
  while (!Serial) {}
}

uint32_t last_tag;

void loop()
{
  if (rdm6300.update()) {
    uint32_t tag = rdm6300.get_tag_id();

    if (tag != last_tag) {
      char out [16];
      sprintf(out, "%8.8lX", tag);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CUR: ");
      lcd.setCursor(5, 0);
      lcd.print(out);
      lcd.setCursor(0, 1);
      lcd.print("REF: 001FFF0D");
    
      Serial.println(out);
      last_tag = tag;
    }
  }

  delay(10);
  /*
  lcd.noBacklight();
  lcd.setCursor(0, 0);
  lcd.print("HELLO");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("WORLD");
  delay(2000);
  lcd.backlight();
  */
}