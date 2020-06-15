const int button1 = 0;
const int button2 = 1;
const int button3 = 21;
const int button4 = 20;
const int button5 = 19;
const int button6 = 18;
const int button7 = 17;
const int button8 = 16;
const int button9 = 15;
const int buttona = 14;

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
const int led6 = 7;
const int led7 = 8;
const int led8 = 9;
const int led9 = 10;
const int leda = 11;

const int signalPin = 13;

const int arrSize = 10;

int state = 0;
unsigned long debounceDelay = 20;
unsigned long lastDebounceTime [arrSize];
int buttonState [arrSize];
int lastButtonState [arrSize];
int ledState [arrSize];
int reading [arrSize];
int key [arrSize] = {1, 0, 1, 0, 0, 1, 1, 0};
int leds [arrSize] = {
    led1,
    led2,
    led3,
    led4,
    led5,
    led6,
    led7,
    led8,
    led9,
    leda,
};
int buttons [arrSize] = {
    button1,
    button2,
    button3,
    button4,
    button5,
    button6,
    button7,
    button8,
    button9,
    buttona,
};

void setup() {
    pinMode(signalPin, OUTPUT);
    digitalWrite(signalPin, HIGH);

    for (int i = 0; i < arrSize; i++) {
        pinMode(buttons[i], INPUT_PULLUP);
        pinMode(leds[i], OUTPUT);
        digitalWrite(leds[i], HIGH);
    }
}

void loop() {

    button_debounce(buttons[0], leds[0], 0);
    button_debounce(buttons[1], leds[1], 1);
    button_debounce(buttons[2], leds[2], 2);
    button_debounce(buttons[3], leds[3], 3);
    button_debounce(buttons[4], leds[4], 4);
    button_debounce(buttons[5], leds[5], 5);
    button_debounce(buttons[6], leds[6], 6);
    button_debounce(buttons[7], leds[7], 7);

    if (key_check()) {
        led_loop();
        digitalWrite(signalPin, LOW);
        delay(1000);
    } else {
        digitalWrite(signalPin, HIGH);
    }

}

void button_debounce(int button, int led, int pos) {
    reading[pos] = buttonRead(button);

    if (reading[pos] != lastButtonState[pos]) {
        lastDebounceTime[pos] = millis();
        reading[pos] = buttonRead(button);
    }

    if ((millis() - lastDebounceTime[pos]) > debounceDelay) {
        if (reading[pos] != buttonState[pos]) {
            buttonState[pos] = reading[pos];
            if (buttonState[pos] == LOW) {
                ledState[pos] = !ledState[pos];
             }
        }
        digitalWrite(led, ledState[pos]);
    }
    lastButtonState[pos] = reading[pos];
}

bool buttonRead(int button) {
    if (button > 19) {
        return analogRead(button) > 100 ? 0 : 1; 
    } else {
        return digitalRead(button);
    }
}


bool key_check() {
    bool check = true;
    for (int i = 0; i < arrSize; i++) {
        // Serial.print(ledState[i]);
        // Serial.print("=");
        // Serial.print(key[i]);
        // Serial.print("-");
        if (ledState[i] != key[i]) {
            // Serial.print("F");
            check = false;
        } else {
            // Serial.print("T");
        }
        // Serial.print(" | ");
    }
    // Serial.print(check);
    // Serial.println();
    return check;
}

void led_loop() {
    for (int i = 0; i < arrSize; i++) {
        digitalWrite(leds[i], LOW);
    }
    delay(200);
    for (int i = 0; i < arrSize; i++) {
        digitalWrite(leds[i], HIGH);
        // digitalWrite(leds[i + arrSize / 2], HIGH);
        delay(200);
    }
    delay(750);
}