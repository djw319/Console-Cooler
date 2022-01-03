//DJ Walsh
//Automatic Fan Control Program
//12/31/2021

#include <Wire.h>
#include <Adafruit_MPL115A2.h>

//Initialize temperature sensor
Adafruit_MPL115A2 mpl115a2;

//Initialize pins
const int fan_control_pin = 2;
const int led_pin = 13;

//Global Variables
bool fanStatus = false;


void setup() {
  //Initial IO states
  digitalWrite(led_pin, LOW);
  pinMode(fan_control_pin, OUTPUT);
  digitalWrite(fan_control_pin, LOW);

  //Initialize Serial
  Serial.begin(9600);
  if (! mpl115a2.begin()) {
    Serial.println("Sensor not found! Check wiring");
    while (1);
  }
  Serial.println("ready");
}


void loop() {
  //Initialize local variables
  float temperatureC = 0;

  //get temperature
  temperatureC = mpl115a2.getTemperature();

  //Control logic
  if(temperatureC >= 30 && fanStatus == false){
    enableFan();
  } else if(temperatureC <23 && fanStatus == true) {
    disableFan();
  } else if(fanStatus == true){
    Serial.print("Fan On\t\tTemp(C): ");
    Serial.println(temperatureC);
    delay(3000);
  } else{
    Serial.print("Fan Off\t\tTemp(C): ");
    Serial.println(temperatureC);
    delay(3000);
  }

}


void enableFan()  {
  fanStatus = true;
  digitalWrite(fan_control_pin, HIGH);
  digitalWrite(led_pin, HIGH);
}


void disableFan()  {
  fanStatus = false;
  digitalWrite(fan_control_pin, LOW);
  digitalWrite(led_pin, LOW);
}
