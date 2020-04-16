/*
 * @brief Fungsi untuk setup jaringan
 * @parameter None
 * @return Void
 */
void networking_setup(){
  WiFi.begin(SSID, PWD);

  int counter = 0;
  while(WiFi.status() != WL_CONNECTED) {  
    delay(1000);
    Log.notice(F("Menghubungkan ke WiFi (%s) %d" CR), SSID, counter);    
    counter++;
  }

  IPAddress ip = WiFi.localIP();
  char ipa[20];
  sprintf(ipa, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  Log.notice(F("WiFi Terhubung, IP: %s" CR), ipa);
}
