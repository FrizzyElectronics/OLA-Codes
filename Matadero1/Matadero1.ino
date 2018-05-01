#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 16
#define CARAS 5
#define DELAY_APAGAR 0
#define DELAY_ENCENDER 0

int pinesCaras[5] = {5, 4, 0, 2, 14};

Adafruit_NeoPixel cubo[CARAS] = {
    Adafruit_NeoPixel(NUMPIXELS, pinesCaras[0], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, pinesCaras[1], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, pinesCaras[2], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, pinesCaras[3], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, pinesCaras[4], NEO_GRB + NEO_KHZ800),
};

void setup() {
  randomSeed(millis());
  for (int i = 0; i < CARAS; i++) {
    cubo[i].begin();
  }
}

void loop() {

  apagado();
  encendido_blanco();
  random_sweep();
  fade_cube();
  // random_led_face();
}

void apagado() {
  for (int i = 0; i < CARAS; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      cubo[i].setPixelColor(j, 0, 0, 0);
      cubo[i].show();
    }
  }
}

void encendido_blanco() {
  for (int i = 0; i < CARAS; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      cubo[i].setPixelColor(j, 255, 255, 255);
      cubo[i].show();
      delay(DELAY_ENCENDER);
    }
  }
}

void random_sweep() {
  for (int i = 0; i < CARAS - 1; i++) {
    for (int j = NUMPIXELS; j > 0; j--) {
      int red = random(255);
      int blue = random(255);
      int green = random(255);
      cubo[i].setPixelColor(j, red, blue, green);
      cubo[i].show();
      delay(DELAY_ENCENDER);
    }
  }
}

void random_sweep_cubo(red, green, blue) {
  for (int f = NUMPIXELS; f >= 0; f -= 4) {
    for (int i = 0; i <= CARAS; i++) {
      if (i == CARAS) {
        int espiral[16] = {0,  1,  2, 3, 7, 11, 15, 14,
                           13, 12, 8, 4, 5, 6,  10, 9};
        dibujar_patron(patron, i, red, green, blue);
      }
      for (int j = f - 4; j <= f; j++) {
        cubo[i].setPixelColor(j, red, blue, green);
        cubo[i].show();
        delay(DELAY_FADE_CUBO);
      }
    }
  }
}

void patron(int patron[], cara, red, green, blue) {
  for (int i = 0; i < sizeof(patron); i++) {
    cubo[cara].setPixelColor(i, red, green, blue);
    cubo[cara].show();
    delay(DELAY_FADE_CUBO);
  }
}

void fade_cube() {
  int red;
  int green;
  int blue;
  for (green = 0; green < 255; green++) {
    for (int i = 0; i < CARAS; i++) {
      for (int j = 0; j < NUMPIXELS; j++) {
        cubo[i].setPixelColor(j, red, blue, green);
        cubo[i].show();
        delay(DELAY_ENCENDER);
      }
    }
  }

  for (red = 255; red > 0; red--) {
    for (int i = 0; i < CARAS; i++) {
      for (int j = 0; j < NUMPIXELS; j++) {
        cubo[i].setPixelColor(j, red, blue, green);
        cubo[i].show();
        delay(DELAY_ENCENDER);
      }
    }
  }

  for (blue = 0; blue < 255; blue++) {
    for (int i = 0; i < CARAS; i++) {
      for (int j = 0; j < NUMPIXELS; j++) {
        cubo[i].setPixelColor(j, red, blue, green);
        cubo[i].show();
        delay(DELAY_ENCENDER);
      }
    }
  }

  for (green = 255; green > 0; green--) {
    for (int i = 0; i < CARAS; i++) {
      for (int j = 0; j < NUMPIXELS; j++) {
        cubo[i].setPixelColor(j, red, blue, green);
        cubo[i].show();
        delay(DELAY_ENCENDER);
      }
    }
  }

  for (red = 0; red < 255; red++) {
    for (int i = 0; i < CARAS; i++) {
      for (int j = 0; j < NUMPIXELS; j++) {
        cubo[i].setPixelColor(j, red, blue, green);
        cubo[i].show();
        delay(DELAY_ENCENDER);
      }
    }
  }

  for (blue = 255; blue > 0; blue--) {
    for (int i = 0; i < CARAS; i++) {
      for (int j = 0; j < NUMPIXELS; j++) {
        cubo[i].setPixelColor(j, red, blue, green);
        cubo[i].show();
        delay(DELAY_ENCENDER);
      }
    }
  }
}

void random_led_face() {
  int leds_on[NUMPIXELS * CARAS] = {};
  int red;
  int green;
  int blue;

  for (int i = 0; i < NUMPIXELS * CARAS; i++) {
    int led = random(NUMPIXELS);
    int cara = random(CARAS);
    int led_en_cara = led * cara;
    bool encendido = true;
    red = random(255);
    green = random(255);
    blue = random(255);
    while (encendido) {
      for (int j = 0; j < sizeof(leds_on); j++) {
        if (leds_on[j] == led_en_cara) {
          encendido = true;
          int led = random(NUMPIXELS);
          int cara = random(CARAS);
        } else {
          encendido = false;
        }
      }
    }
    if (encendido == false) {
      cubo[cara].setPixelColor(led, red, green, blue);
      cubo[cara].show();
      delay(25);
    }
  }
}
