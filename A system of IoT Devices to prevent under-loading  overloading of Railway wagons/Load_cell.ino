#include <HX711_ADC.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

HX711_ADC LoadCell(6, 7); // Parameters: dt pin 6, sck pin 7

void setup() {
  LoadCell.begin(); // Start connection to HX711
  LoadCell.start(2000); // Load cells get 2000ms of time to stabilize
  LoadCell.setCalFactor(1000.0); // Calibration factor for load cell (adjust as needed)

  Serial.begin(9600); // Initialize Serial Monitor

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Set text size and color for the OLED display
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  LoadCell.update(); // Retrieve data from the load cell
  float weight = LoadCell.getData(); // Get the weight value

  // Clear the OLED display
  display.clearDisplay();

  // Display weight on the OLED display
  display.setCursor(0, 0);
  display.print(F("   Weight[g]: "));
  display.print(weight);

  // Check if weight exceeds 7 grams
  if (weight > 7.0) {
    display.setCursor(25, 35);
    display.print(F("Overweight"));
  }
  else if(weight > 2.0){
     display.setCursor(25,35);
     display.print(F("Normal"));
  }
  else{
         display.setCursor(25, 35);
    display.print(F("Underweight"));
  }

  // Display the content on the OLED screen
  display.display();

  // Display weight on the Serial Monitor
  Serial.print("Weight[g]: ");
  Serial.println(weight);

  delay(500); // Delay for half a second (adjust as needed)
}
