#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//String message[9];
String buffer = "                ";

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int i = 0;
int strLength;
unsigned long previousMillis = 0;
const long interval = 250;
int messagecount;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.home();
}


void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
//    strLength = buffer.length();
//    lcd.clear();
//    String toshow = buffer.substring(i,i+16);
//    lcd.print(toshow);
//    i += 4;
//    if (i>(strLength-16))
//    {
//      i = 0;
//      messagecount += 1;
//    }
  }
  if (Serial.available() > 0) {
    digitalWrite(LED_BUILTIN, LOW);
    // read the incoming byte:
    char incomingChar = Serial.read();

    // say what you got:
    if (incomingChar != '\n')
    {
      //Serial.print(incomingChar);
      buffer+=incomingChar;
      Serial.println("Adding to buffer...");
    }
    else
    {
      Serial.println("Received message!");
      //Serial.print('\n');
      buffer+="                ";
      //message[0]=buffer;
      strLength = buffer.length();
      Serial.println(buffer+" "+strLength);
      lcd.backlight();
      while (i<(strLength-12))
      {
        lcd.clear();
        String toshow = buffer.substring(i,i+16);
        Serial.println(toshow);
        lcd.print(toshow);
        i += 4;
        delay(250);
      }
      lcd.noBacklight();
      i=0;
      buffer="                "; //clear buffer
    }
  }
}
