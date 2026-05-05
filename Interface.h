#ifndef MP3P_INTERFACE_H
#define MP3P_INTERFACE_H
#include <SdFat.h>
#include <Adafruit_SSD1351.h>

class Interface {
public:
  Interface(Adafruit_SSD1351 _scr, SdExFat _fs): scr(_scr), fs(_fs) {
  }
  void error(const char *err) {
    fs.errorHalt(&Serial, err);
  }
private:
  SdExFat fs;
  Adafruit_SSD1351 scr;
};

#endif