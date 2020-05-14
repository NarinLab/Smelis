/*
 * @brief Fungsi untuk melakukan setup komponen sensor
 * @parameter None
 * @return Void
 */
void sensory_setup(){
  pinMode(PIN_RAIN_SENSOR, INPUT);
  pinMode(PIN_LIGHT_SENSOR, INPUT);
  dht22.setup(PIN_DHT22, DHTesp::DHT22);  
}

/*
 * @brief Fungsi untuk mendapatkan data rain sensor
 * @parameter None
 * @return Byte
 */
byte sensory_get_rain_sensor(){
  int analog = analogRead(PIN_RAIN_SENSOR); // Pending
  byte persen = map(analog, 0, 4095, 0, 100);
  return persen;
}

/*
 * @brief Fungsi untuk mendapatkan data light sensor
 * @parameter None
 * @return Byte
 */
byte sensory_get_light_sensor(){
  int analog = analogRead(PIN_LIGHT_SENSOR); // Pending
  byte persen = map(analog, 0, 4095, 0, 100);
  return persen;
}

/* @brief Fungsi untuk mendapatkan data DHT-22
 * @parameter None
 * @return Bool, DHT22 by Reference
 */
bool sensory_get_dht22(DHT22 &data_dht22){
  ComfortState cf;
  TempAndHumidity data_sensor = dht22.getTempAndHumidity();

  if(dht22.getStatus() != 0){
     Log.error(F("DHT22 bermasalah, kode error: %s" CR), dht22.getStatusString());
     return false;
  }

  data_dht22.suhu = data_sensor.temperature;
  data_dht22.humid = data_sensor.humidity;
  data_dht22.heatIndex = dht22.computeHeatIndex(data_sensor.temperature, data_sensor.humidity);
  data_dht22.dewPoint = dht22.computeDewPoint(data_sensor.temperature, data_sensor.humidity);
  data_dht22.cr = dht22.getComfortRatio(cf, data_sensor.temperature, data_sensor.humidity);

  return true;
}
