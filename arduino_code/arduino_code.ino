#include <Adafruit_NeoPixel.h>
#include <stdlib.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN 6     // LED 스트랩을 제어하는 핀 번호
#define LED_COUNT 43  // LED 스트랩의 LED 개수

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

String inputString = "";
char Buffer[10];
int check = 0;
bool stringComplete = false;



void setup() {
// put your setup code here, to run once:
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();       // LED 스트랩 초기화
  Serial.begin(9600);  // 시리얼 통신 초기화
}

void loop() {
  if (stringComplete) {
    //Serial.println(inputString);
    // clear the string:
    // CString str = inputString;
    //int index = parseInt(inputString.c_str());
    int index;
    int status;

    sscanf(Buffer, "%d,%d", &index, &status);

    int red = 0;
    int green = 0;
    int blue = 0;

    if (status == 1) {
      red = 0;
      green = 255;
      blue = 0;

    } else if (status == 2) {
      red = 255;
      green = 255;
      blue = 0;
    } else if (status == 3) {
      red = 255;
      green = 0;
      blue = 0;
    }

    strip.setPixelColor(index, strip.Color(red, green, blue));
    strip.show();

    inputString = "";
    stringComplete = false;
  }
  if(check == LED_COUNT){
    delay(1000);
    check = 0;
    strip.clear();
  }
  /*
  delay(1);
  if (Serial.available() > 0) {

    int index = Serial.parseInt();
    int status = Serial.parseInt();
    //String a = Serial.readString();
    //Serial.println(a);
    //int b= a.toInt();

    int red = 0;
    int green = 0;
    int blue = 0;

    if (status == 1) {
      red = 0;
      green = 255;
      blue = 0;

    } else if (status == 2) {
      red = 255;
      green = 255;
      blue = 0;
    } else if (status == 3) {
      red = 255;
      green = 0;
      blue = 0;
    }

    strip.setPixelColor(index, strip.Color(red, green, blue));
    strip.show();

    //strip.setPixelColor(0, strip.Color(0, 255, 0));
    // Iterate over the array of colors
    /*
      for (int i = 1; i < LED_PIN; i++) {
        // Get the current color as a string
        // String color = doc[i];
        //String a = Serial.readString();
        //Serial.println(a);
        //int color= a.toInt();
        // Check if the current color is "red"
        if (color == 1) {
          // Set the Neopixel LED to red
          strip.setPixelColor(i, strip.Color(255, 0, 0));
          strip.show();
        }

        // Check if the current color is "green"
        else if (color == 2) {
          // Set the Neopixel LED to green
          strip.setPixelColor(i, strip.Color(0, 255, 0));
          strip.show();
        }
        else if (color == 3){
          // Set the Neopixel LED to yellow
          strip.setPixelColor(i, strip.Color(255, 255, 0));
          strip.show();
        }
      }
  }*/
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      //Serial.println(inputString);
      inputString.toCharArray(Buffer, 10);
      check +=1;
      
    }
  }
}