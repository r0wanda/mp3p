#include <SdFat.h>
#include <SdFatConfig.h>
#include <ESP_I2S.h>
#include <Adafruit_SSD1351.h>
#include <Adafruit_TLV320DAC3100.h>

/*
		TX			5V
		RX			GND
		1			3v3
		2			13	encoder 2
		3			12	encoder 1
		4			11	SCLK
		5			10	MOSI
		6			9	SCR DC
SDCS	7			8	SCR CS
*/

#define ENCODER_1 12
#define ENCODER_2 13

#define SD_MOSI 10
#define SD_SCLK 11
// miso/ss not used (rn)
#define SD_MISO 40
#define SD_SS 41

#define SD_FAT_TYPE 2
#define SPI_CLOCK SD_SCK_MHZ(50)
#define SD_CS_PIN 7
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)

SdExFat stdsd;
#define SDERR(s) stdsd.errorHalt(&Serial, F(s))

#define SCR_CS_PIN 8
#define SCR_DC_PIN 9
Adafruit_SSD1351 stdscr(
	128, 128,
	SCR_CS_PIN, SCR_DC_PIN,
	-1
);

Interface stdiface;
Library stdlibrary;

void setup() {
	Serial.begin(9600);
	if (!stdsd.begin(SD_CONFIG)) {
		stdsd.initErrorHalt(&Serial);
	}
	stdiface = Interface(stdscr, stdsd);
	stdlibrary = Library(stdsd, stdiface);
}

void loop() {
	stdiface.loop();
}
