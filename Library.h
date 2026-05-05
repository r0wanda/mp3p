#include <sys/types.h>
#ifndef MP3P_LIBRARY_H
#define MP3P_LIBRARY_H
#include <string.h>
#include <stdlib.h>
#include <SdFat.h>
#include <sdios.h>
#include <ArduinoJson.h>
#include "Interface.h"

#define MPLIBERR(err) interface->error(F(err))
#define MPLIBFN(fn, err) if (!fn) interface->error(F(err))
#define LLLOOP(type, init, i) (type *i = init; i->next != nullptr; i = i->next)

const char *DEF_CONFIG = F("{}");

struct Artist {
  char *name;
  Album *albums;
  Artist *next = nullptr;
};
struct Album {
  char *name;
  Artist *artist;
  Album *next = nullptr;
};

class Library {
public:
  struct Artist *artists;
  struct Album *albums;
  JsonDocument config;
  
  Library(SdExFat *_fs, Interface *iface):
  fs(_fs), interface(iface),
  artists(nullptr), albums(nullptr) {
    fs->chdir();
    initCfg();
    initDb();
  }
  void initCfg() {
    ExFile file;
    if (fs->exists(".config.json")) {
      file = fs->open(".config.json", O_READ);
      DeserializationError err = deserializeJson(config, file);
      if (!err) return;
    }

  }
  void initDb() {
    if (!artist || !albums) freeDb();
    ExFile root;
    MPLIBFN(root.open("/"), "open root");

    struct Artist *art = (struct Artist*)malloc(sizeof(struct Artist));
    struct Album *alb = (struct Album*)malloc(sizeof(struct Album));
    struct Artist *prev = nullptr;
    artists = cur;
    while (root.openNext(&root, O_RDONLY)) {
      if (!root.isDir()) continue;

      char name[256];
      MLIBFN(root.getName(name, 255), "name read error");
      u_char len = strnlen(name, 255);
      cur->name = (char*)malloc(sizeof(char) * );
      strncpy(cur->name, name, len);

      if (prev) {
        prev->next = cur;
      }
      root.close();
    }
  }
  void freeDb() {
    // iterate then free previous item
    struct Artist *prevA = nullptr;
    for LLLOOP(struct Artist, artists, art) {
      free(prevA);
      free(art->name);
      prevA = art;
    }
    free(prevA);
    artists = nullptr;

    struct Album *prevB;
    for LLLOOP(struct Album, albums, alb) {
      free(prevB);
      free(alb->name);
      prevB = alb;
    }
    free(prevB);
    albums = nullptr;
  }
  ~Library() {
    freeDb();
  }
private:
  SdExFat *fs;
  Interface *interface;
};

#endif