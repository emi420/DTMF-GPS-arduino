#include "dtmfgen.h"

DTMFGenerator DTMF;
const int TONE_BIG = 600;
const int TONE_SMALL = 75;
const int WAIT_DELAY = 75;

void playMessage(String message) {
    char chars[message.length() + 1];
    message.toCharArray(chars, message.length() + 1);
    
    for (int i = 0; i < message.length(); i++) {
        int mark_space_value = TONE_SMALL;
        
        if (i == 0 || i == message.length() - 1) {
            mark_space_value = TONE_BIG;
        }
        
        DTMF.generate(chars[i], mark_space_value);
        delay(WAIT_DELAY);
    }
}