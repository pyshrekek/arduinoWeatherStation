#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2                // Sensor Pin
#define DHTTYPE DHT11          // define the type of sensor used

DHT dht(DHTPIN, DHTTYPE);     // Initialize DHT sensor.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //DHT begin
  dht.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, Mrs. Fletcher and class! This is a minutes gift from");
  display.setCursor(0,24);
  display.println("November 12th, 2021.");
  

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(3000);
  display.clearDisplay();
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...
  
  display.setCursor(0,0);
  display.println("Code: github.com/pyshrekek/arduinoWeatherStation");
  
  display.display();
  delay(3000);
  display.clearDisplay();
  
  display.setCursor(0,0);
  display.println("I hope you enjoy!~");
  display.setCursor(0,12);
  display.println("-Daniel (Haokun) Xu");

  display.display();
  delay(3000);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  
  float h = dht.readHumidity();      // Read Humidity 
  float t = dht.readTemperature();  //Temp as C
  float f = dht.readTemperature(true);   // Read temperature as Fahrenheit

  String humidity = String(h, 0);
  String celsius = String(t, 2);
  String fahrenheit = String(f, 2);

  //comment and uncomment for Celsius and Fahrenheit

  display.setCursor(0,0);
  display.println("Temperature: " + celsius + "C");
  
  display.setCursor(0,12);
  display.println("For Americans: " + fahrenheit + "F");

  display.setCursor(0,24);
  display.println("Humidity: " + humidity + "%");

  display.display();
  delay(2000);
}
