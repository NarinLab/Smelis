/*
 * @Brief fungsi untuk setup bagian kode program cloud
 * @parameter None
 * @return Void
 */
void cloud_setup(){
  ThingSpeak.begin(client);
}

void cloud_publish(){
    byte data_hujan = sensory_get_rain_sensor();
    byte data_cahaya = sensory_get_light_sensor();
    DHT22 data_dht22;
    sensory_get_dht22(data_dht22);
    long rssi = WiFi.RSSI();
    
    
    ThingSpeak.setField(1, data_dht22.humid);
    ThingSpeak.setField(2, data_dht22.suhu);
    ThingSpeak.setField(3, data_hujan);
    ThingSpeak.setField(4, data_cahaya);
    ThingSpeak.setField(5, rssi);

    char str_status[128];
    if(data_dht22.humid == 0 && data_dht22.suhu == 0 && data_dht22.dewPoint == 0 &&
      data_dht22.heatIndex == 0 && data_dht22.cr == 0){
      sprintf(str_status, "Kesalahan pada sensor DHT22: %s", data_dht22.err);
    }else{
      sprintf(str_status, "Titik embun adalah %s, indeks panas %s, dan tingkat kenyaman %s", 
      data_dht22.dewPoint, data_dht22.heatIndex, data_dht22.cr);  
    }
   
    ThingSpeak.setStatus(str_status);

    int result = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(result == 200){
      Log.notice(F("Berhasil mengirim ke Cloud." CR));
    }else{
      Log.error(F("Gagal mengirim ke Cloud, error code: %d" CR), result);
    }
}
