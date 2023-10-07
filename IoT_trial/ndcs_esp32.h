#ifndef NDCS_ESP32_H
#define NDCS_ESP32_H
#include <Arduino.h>
class NDCS {
  public:
    void begin(char*,char*,char*,char*,char*);
    void send(int,char*);
    void send(int,int);
    void send(int,float);
    int receive(int);
    // void loop();
};

#endif
