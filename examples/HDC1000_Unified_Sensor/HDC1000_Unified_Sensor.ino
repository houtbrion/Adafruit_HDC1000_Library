/*
 * Adafruitの統合センサライブラリに則ったAM232xシリーズライブラリのサンプルプログラム
 * ただし，プログラム冒頭のセンサクラス名等のdefine文を変更すれば，DHTシリーズなど
 * 統合センサライブラリを用いた他のデバイスでもすぐに使えるプログラム構造になっている．
 * (現状は未検証)
 */
#define SENSOR_CLASS Adafruit_HDC1000_Unified
#define SENSOR_TYPE HDC1000

#if SENSOR_TYPE == Adafruit_HDC1000_Unified
#include "Adafruit_HDC1000_U.h"
#endif /* SENSOR_TYPE */

SENSOR_CLASS sensorObj(SENSOR_TYPE);
uint32_t delayMS;

void setup()
{
  Serial.begin(9600);
  sensorObj.begin();
  Serial.println("HDC1000 series I2C sensor Unified library example");
  sensor_t sensor;
  sensorObj.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  sensorObj.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() 
{
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  sensorObj.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  sensorObj.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
  }
}
