/*
 * @brief Fungsi untuk mencetak ke serial setiap
 *  1 menit sekali
 * @param None
 * @return Void
 */
long SCHEDULER_PRINT_TO_SERIAL_LAST_RUN = 0;
void scheduler_print_to_serial(){
  long NOW = millis();
  if(NOW - SCHEDULER_PRINT_TO_SERIAL_LAST_RUN >= 1000){
    
    byte data_hujan = sensory_get_rain_sensor();
    byte data_cahaya = sensory_get_light_sensor();
    DHT22 data_dht22;
    sensory_get_dht22(data_dht22);

    Log.verbose(F("Temp:%F " \ 
    "Humid:%F HeatIndex:%F DewPoint:%F " \ 
    "ComfortRatio:%F Rain:%d Light:%d" CR), data_hujan, data_dht22.suhu, data_dht22.humid, 
    data_dht22.heatIndex, data_dht22.dewPoint, data_dht22.cr, data_hujan, data_cahaya);
    
    SCHEDULER_PRINT_TO_SERIAL_LAST_RUN = NOW;        
  }
}

/*
 * @brief Fungsi untuk mempublish data ke cloud
 *  30 detik sekali
 * @param None
 * @return Void
 */
long SCHEDULER_PUBLISH_TO_CLOUD_LAST_RUN = 0;
void scheduler_publish_to_cloud(){
  long NOW = millis();
  if(NOW - SCHEDULER_PUBLISH_TO_CLOUD_LAST_RUN >= 180000){
    cloud_publish();
        
    SCHEDULER_PUBLISH_TO_CLOUD_LAST_RUN = NOW;        
  }
}

/* 
 *  @brief Fungsi untuk menjalankan setiap fungsi scheduler yang ada
 *  @param None
 *  @return Void
 */
void scheduler_run(){
  scheduler_print_to_serial();
  scheduler_publish_to_cloud();    
}
