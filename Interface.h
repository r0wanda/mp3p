#ifndef MP3P_INTERFACE_H
#define MP3P_INTERFACE_H
#include <SdFat.h>
#include <mpcommon.h>
#include <Adafruit_SSD1351.h>

class Interface {
public:
  Interface(Adafruit_SSD1351 *_scr, SdExFat *_fs, void *isr): scr(_scr), fs(_fs) {
    scr->begin();
    scr->enableDisplay(true);
    timer = timerBegin(0, 8000, true);
    timerAttachInterrupt(timer, isr, true);
    timerAlarmWrite()
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
  uint8_t rotation;
  SdExFat *fs;
  Adafruit_SSD1351 *scr;
  hw_timer_t *timer;

  void render() {

  }
  void cls() {
    scr->fillScreen(0);
  }
};

#endif