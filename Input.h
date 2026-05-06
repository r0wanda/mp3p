#ifndef MP3P_INPUT_H
#define MP3P_INPUT_H
#include <stdint.h>
#include <Encoder.h>
#include <ezButton.h>
#define BTN_DEBOUNCE 50

class Input : public Encoder, public ezButton {
public:
    template<typename Toggle>
    Input(uint8_t pin1, uint8_t pin2, uint8_t btn, Toggle &&toggle): Encoder(pin1, pin2), ezButton(btn) {
        setDebounceTime(BTN_DEBOUNCE);
    }
private:
};

#endif