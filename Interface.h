#ifndef MP3P_INTERFACE_H
#define MP3P_INTERFACE_H
#include <SdFat.h>

class Interface {
public:
  Interface(SdExFat _fs): fs(_fs) {
  }
  void error(const char *err) {
    fs.errorHalt(&Serial, err);
  }
private:
  SdExFat fs;
};

#endif