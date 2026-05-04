#include <SdFat.h>
#include <SdFatConfig.h>
#include <ESP_I2S.h>
#include <Adafruit_TLV320DAC3100.h>

#define SD_FAT_TYPE 2
#define SPI_CLOCK SD_SCK_MHZ(50)
#define SD_CS_PIN 7
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)

SdExFat sd;
#define SDERR(s) sd.errorHalt(&Serial, F(s))

void setup() {
	Serial.begin(9600);
	if (!sd.begin(SD_CONFIG)) {
		sd.initErrorHalt(&Serial);
	}
}

void loop() {
}
