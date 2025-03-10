// Sensorial Data Collection from all four types of sensors
// This file needs to be configured and fine tuned when we start collecting data.

#include <SD.h> // Include the SD library
#include <DHT.h> // Include the DHT library

// SHARP IR Sensor will be at analog pin:       A0
// Songhe Light Sensors will be at analog pin:  A1
// Daoki Microphone will be at analog pin:      A2
// DHT22 Sensor will be at digital pin:         2
// SD Card will be at output pin:               10

const int IR_PIN = A0; // Connect the SHARP IR distance sensor
const int LDR_PIN = A1; // Connect the light sensor
const int MIC_PIN = A2; // Connect the microphone sensor

const int DHT_PIN = 2; // Connect the DHT22 sensor to digital pin 2

const int chipSelect = 10; // Chip select pin for the SD card

DHT dht(DHT_PIN, DHT22); // Initialize the DHT object
File dataFile; // Create a File object

void setup() {

  Serial.begin(9600); // Initialize serial communication at 9600 baud rate, we can configure this later
  dht.begin(); // Initialize the DHT sensor

  // Initialize the SD card
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed"); // We need to know if SD card is not being initialized
    return;
  }

  // Create a new file on the SD card
  dataFile = SD.open("Sensor_Data.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error creating file"); // We need to know if the file is not storing properly
    return;
  }

  dataFile.print("Distance,Light,Microphone,Temperature,Humidity"); // Column headers for the .csv file
  dataFile.println();
}

void loop() { 

  // Now we can configure the individual sensors to do collect the data properly.

  int distance = analogRead(IR_PIN); // Read the value from the SHARP IR distance sensor
  distance = map(distance, 0, 1023, 0, 80); //Convert the analog reading to a distance in cm

  int light = analogRead(LDR_PIN); // Read the value from the light sensor

  int microphone = analogRead(MIC_PIN); // Read the value from the microphone sensor

  float temperature = dht.readTemperature(); // Read the temperature from the DHT22 sensor
  float humidity = dht.readHumidity(); // Read the humidity from the DHT22 sensor

  Serial.print("Distance: ");
  Serial.print(distance);

  Serial.print(" Light: ");
  Serial.print(light);

  Serial.print(" Microphone: ");
  Serial.print(microphone);

  Serial.print(" Temperature: ");
  Serial.print(temperature);

  Serial.print(" Humidity: ");
  Serial.println(humidity);

  // Write the values to the .csv file
  dataFile.print(distance);
  dataFile.print(",");

  dataFile.print(light);
  dataFile.print(",");

  dataFile.print(microphone);
  dataFile.print(",");

  dataFile.print(temperature);
  dataFile.print(",");

  dataFile.println(humidity);
  delay(2000); // Wait for 2 seconds
}

void exit() {
  dataFile.close(); // Close the file when the program exits
}