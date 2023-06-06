void reading() {
  if (millis() - timer > 5000) {
    temp = dht.readTemperature();
    humidity = dht.readHumidity();
    status_check();
    timer = millis();
  }
}