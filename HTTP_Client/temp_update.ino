void temp_update() {
  humidity = dht.readHumidity();
  d_temp = dht.readTemperature();
}

void probe_temp_update() {
  probe.requestTemperatures();
  p_temp = probe.getTempCByIndex(0);
}
