#include "HX711.h"

#define calibration_factor 96670.00 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  3
#define CLK  2


const int arraySize = 10;
float weight[arraySize];
float weightReading;
int ringIndex = 0;
int startIndex = 0;
int endIndex = arraySize - 1;

float sum = 0;
float avgArray1 = 0;
int i = 0;


HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("Getting Weight");

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println();
  Serial.println("Readings:");
  Serial.print("1 \t 2 \t 3 \t 4 \t 5 \t 6 \t 7 \t 8 \t 9 \t 10 \t Average");
  Serial.println();
}

void loop() {

  weightReading = scale.get_units();
  weight[ringIndex] = weightReading;
  sum = sum + weightReading;
  ringIndex++;

  if (ringIndex > endIndex) {
    ringIndex = startIndex;
    avgArray1 = sum / arraySize;

    for (int i = 0; i < arraySize; i++) {
      Serial.print(weight[i], 3);
      Serial.print("\t");
    }
    i = 0;
    sum = 0;
    Serial.print(avgArray1, 3);
    Serial.println();
  }
}

//  Serial.print("Reading: ");
//  Serial.print(weightReading, 3); //scale.get_units() returns a float
//  Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
//  Serial.println();
