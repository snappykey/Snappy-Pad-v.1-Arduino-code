// code by Snappy Key made for Snappy Pad v.1
#include "Keyboard.h"
#define led_white 18
#define led_white2 16
#define led_white3 9
#define CLK 21
#define DT 20
#define SW 19
#define LS 10

int currentStateCLK = 5;
int lastStateCLK;
int state;
const int columns[] = { 4, 3, 2 };
const int rows[] = { 7, 8, 6, 5 };
int layer = 0;
bool f13_pressed, f14_pressed, f15_pressed, f16_pressed, f17_pressed, f18_pressed, f19_pressed, f20_pressed, f21_pressed, f22_pressed, f23_pressed, f24_pressed, layer_switch_pressed, left_arrow_pressed, right_arrow_pressed, horizontal_mode_on, re_pressed = false;
void setup() {
  Serial.begin(9600);

  lastStateCLK = digitalRead(CLK);

  Keyboard.begin();
  pinMode(columns[0], OUTPUT);
  pinMode(columns[1], OUTPUT);
  pinMode(columns[2], OUTPUT);



  pinMode(rows[0], INPUT_PULLUP);
  pinMode(rows[1], INPUT_PULLUP);
  pinMode(rows[2], INPUT_PULLUP);
  pinMode(rows[3], INPUT_PULLUP);
  // pinMode(rows[4], INPUT_PULLUP);
  pinMode(LS, INPUT_PULLUP);


  pinMode(led_white, OUTPUT);
  pinMode(led_white2, OUTPUT);
  pinMode(led_white3, OUTPUT);

  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);

  pinMode(SW, INPUT_PULLUP);
  digitalWrite(columns[0], HIGH);
  digitalWrite(columns[1], HIGH);
  digitalWrite(columns[2], HIGH);
}

void loop() {
  rotaryEncoderScan();
  matrixScan();
  LayerSwitch();
}

void matrixScan() {
  row1();
  row2();
  row3();
  // Serial.println()
}

void LayerSwitch() {
  if (digitalRead(LS) == 0 && !layer_switch_pressed) {
    Serial.print("Switched Layer to: ");
    if (layer < 3) {
      layer++;
    } else {
      layer = 0;
    }
    layerLED();
    layer_switch_pressed = true;
    Serial.println(layer);

  } else if (digitalRead(LS) == 1 && layer_switch_pressed) {
    layer_switch_pressed = false;
  }
}
void rotaryEncoderScan() {
  if (!re_pressed && digitalRead(SW) == 0) {
    Serial.println("re switch");
    Keyboard.press(0x81);

    Keyboard.press(0xC2);
    Keyboard.releaseAll();
    horizontal_mode_on = !horizontal_mode_on;
    re_pressed = true;
  } else if (re_pressed && digitalRead(SW) == 1) re_pressed = false;

  while (true) {
    currentStateCLK = digitalRead(CLK);

    state = 0;
    if (currentStateCLK != lastStateCLK) {
      if (digitalRead(DT) != currentStateCLK && (state == 0 || state == 1)) {
        // if (!horizontal_mode_on) {
        Keyboard.press(0x81);

        Keyboard.write(0xD8);
        Keyboard.releaseAll();

        // } else if (horizontal_mode_on) Keyboard.write(0xDA);
        // disableForWhile = true;
      } else if (digitalRead(DT) == currentStateCLK && (state == 0 || state == 2)) {
        // if (!horizontal_mode_on) {
        Keyboard.press(0x81);

        Keyboard.write(0xD7);
        Keyboard.releaseAll();

        // } else if (horizontal_mode_on) Keyboard.write(0xD9);
        state = 2;
        // disableForWhile = true;
      }
    }
    lastStateCLK = currentStateCLK;
    if (digitalRead(rows[0]) != 0) break;
    if (digitalRead(rows[1]) != 0) break;
  }
  // Serial.println("RE ended");
}


void activateLayer(int key) {
  if (layer == 1) {
    Keyboard.press(0x81);
  } else if (layer == 2) {
    Keyboard.press(0x81);
    Keyboard.press(0x82);
  } else if (layer == 3) {
    Keyboard.press(0x80);
    Keyboard.press(0x81);
    Keyboard.press(0x82);
  }
  Keyboard.write(key);
  Keyboard.releaseAll();
}
void row1() {
  digitalWrite(columns[2], HIGH);

  digitalWrite(columns[0], LOW);
  if (!f13_pressed && digitalRead(rows[0]) == 0 && digitalRead(columns[0]) == 0) {
    Serial.println("f13");
    activateLayer(0xF0);
    f13_pressed = true;
  } else if (f13_pressed && digitalRead(rows[0]) == 1 && digitalRead(columns[0]) == 0) {
    f13_pressed = false;
  }

  if (!f14_pressed && digitalRead(rows[1]) == 0 && digitalRead(columns[0]) == 0) {
    Serial.println("f14");
    activateLayer(0xF1);
    f14_pressed = true;
  } else if (f14_pressed && digitalRead(rows[1]) == 1 && digitalRead(columns[0]) == 0) {
    f14_pressed = false;
  }

  if (!f15_pressed && digitalRead(rows[2]) == 0 && digitalRead(columns[0]) == 0) {
    Serial.println("f15");
    activateLayer(0xF2);
    f15_pressed = true;
  } else if (f15_pressed && digitalRead(rows[2]) == 1 && digitalRead(columns[0]) == 0) {
    f15_pressed = false;
  }

  if (!f16_pressed && digitalRead(rows[3]) == 0 && digitalRead(columns[0]) == 0) {
    Serial.println("f16");
    activateLayer(0xF3);
    f16_pressed = true;
  } else if (f16_pressed && digitalRead(rows[3]) == 1 && digitalRead(columns[0]) == 0) {
    f16_pressed = false;
  }
}

void row2() {
  digitalWrite(columns[0], HIGH);

  digitalWrite(columns[1], LOW);

  if (!f17_pressed && digitalRead(rows[0]) == 0 && digitalRead(columns[1]) == 0) {
    Serial.println("f17");
    activateLayer(0xF4);
    f17_pressed = true;
  } else if (f17_pressed && digitalRead(rows[0]) == 1 && digitalRead(columns[1]) == 0) {
    f17_pressed = false;
  }

  if (!f18_pressed && digitalRead(rows[1]) == 0 && digitalRead(columns[1]) == 0) {
    Serial.println("f18");
    activateLayer(0xF5);
    f18_pressed = true;
  } else if (f18_pressed && digitalRead(rows[1]) == 1 && digitalRead(columns[1]) == 0) {
    f18_pressed = false;
  }

  if (!f19_pressed && digitalRead(rows[2]) == 0 && digitalRead(columns[1]) == 0) {
    Serial.println("f19");
    activateLayer(0xF6);
    f19_pressed = true;
  } else if (f19_pressed && digitalRead(rows[2]) == 1 && digitalRead(columns[1]) == 0) {
    f19_pressed = false;
  }

  if (!f20_pressed && digitalRead(rows[3]) == 0 && digitalRead(columns[1]) == 0) {
    Serial.println("f20");
    activateLayer(0xF7);
    f20_pressed = true;
  } else if (f20_pressed && digitalRead(rows[3]) == 1 && digitalRead(columns[1]) == 0) {
    f20_pressed = false;
  }
}

void row3() {
  // // delay(0.5);
  digitalWrite(columns[1], HIGH);

  digitalWrite(columns[2], LOW);

  if (!f21_pressed && digitalRead(rows[0]) == 0 && digitalRead(columns[2]) == 0) {
    Serial.println("f21");
    activateLayer(0xF8);
    f21_pressed = true;
  } else if (f21_pressed && digitalRead(rows[0]) == 1 && digitalRead(columns[2]) == 0) {
    f21_pressed = false;
  }

  if (!f22_pressed && digitalRead(rows[1]) == 0 && digitalRead(columns[2]) == 0) {
    Serial.println("f22");
    activateLayer(0xF9);
    f22_pressed = true;
  } else if (f22_pressed && digitalRead(rows[1]) == 1 && digitalRead(columns[2]) == 0) {
    f22_pressed = false;
  }

  if (!f23_pressed && digitalRead(rows[2]) == 0 && digitalRead(columns[2]) == 0) {
    Serial.println("f23");
    activateLayer(0xFA);
    f23_pressed = true;
  } else if (f23_pressed && digitalRead(rows[2]) == 1 && digitalRead(columns[2]) == 0) {
    f23_pressed = false;
  }

  if (!f24_pressed && digitalRead(rows[3]) == 0 && digitalRead(columns[2]) == 0) {
    Serial.println("f24");
    activateLayer(0xFB);
    f24_pressed = true;
  } else if (f24_pressed && digitalRead(rows[3]) == 1 && digitalRead(columns[2]) == 0) {
    f24_pressed = false;
  }
}

void layerLED() {
  if (layer == 1) {
    digitalWrite(led_white, HIGH);
  } else if (layer == 2) {
    digitalWrite(led_white2, HIGH);
  } else if (layer == 3) {
    digitalWrite(led_white3, HIGH);

  } else {
    digitalWrite(led_white, LOW);
    digitalWrite(led_white2, LOW);
    digitalWrite(led_white3, LOW);
  }
}
