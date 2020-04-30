/*
 * @brief Fungsi untuk mencetak ke serial setiap
 *  1 menit sekali
 * @param None
 * @return Void
 */
long SCHEDULER_PRINT_TO_SERIAL_LAST_RUN = 0;
void scheduler_print_to_serial(){
  long NOW = millis();
  if(NOW - SCHEDULER_PRINT_TO_SERIAL_LAST_RUN >= 10000){
    
    byte data_hujan = sensory_get_rain_sensor();
    DHT22 data_dht22;
    sensory_get_dht22(data_dht22);

    Log.verbose(F("Data sensor --> Hujan = %d, DHT22 = Suhu: %F" \ 
    " | Humid: %F | Heat Index: %F | Dew Point: %F" \ 
    " | Comfort Ratio: %F" CR), data_hujan, data_dht22.suhu, data_dht22.humid, 
    data_dht22.heatIndex, data_dht22.dewPoint, data_dht22.cr);
    
    SCHEDULER_PRINT_TO_SERIAL_LAST_RUN = NOW;        
  }
}

/* 
 *  @brief Fungsi untuk menjalankan setiap fungsi scheduler yang ada
 *  @param None
 *  @return Void
 */
void scheduler_run(){
  scheduler_print_to_serial();    
}
