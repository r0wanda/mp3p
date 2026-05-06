#ifndef MP3P_INTERFACE_H
#define MP3P_INTERFACE_H
#include <SdFat.h>
#include <mpcommon.h>
#include <Adafruit_SSD1351.h>
#include <GEM_adafruit_gfx.h>

class Interface {
public:
  Interface(Adafruit_SSD1351 *_scr, SdExFat *_fs): scr(_scr), fs(_fs) {
    scr->begin();
    scr->enableDisplay(true);
  }
  void error(const char *err) {
    fs->errorHalt(&Serial, err);
  }
  void setRotation(uint8_t rot) {
    rotation = rot;
    cls();
    scr->setRotation(rotation);
    render();
  }
  void loop() {

  }
private:
  u_long timerSt;
  uint16_t timeout_sec = 45;
  uint8_t rotation;
  SdExFat *fs;
  Adafruit_SSD1351 *scr;
  GEM_adafruit_gfx menu;

  void render() {

  }
  void cls() {
    scr->fillScreen(0);
  }
};

#endif