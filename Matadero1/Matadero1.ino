#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 16
#define CARAS 5
#define DELAY_APAGAR 0
#define DELAY_ENCENDER 0
#define DELAY_FADE_CUBO 100

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
  random_sweep_cubo(100, 0, 0);
  apagado();
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

void random_sweep_cubo(int red, int green, int blue) {
  for (int f = NUMPIXELS; f > 0; f -= 4) {
    for (int i = 0; i < CARAS - 1; i++) {
      for (int j = f - 4; j <= f; j++) {
        cubo[i].setPixelColor(j, red, blue, green);
        cubo[i].show();
        delay(DELAY_FADE_CUBO);
      }
    }
  }
  int espiral[16] = {0, 4, 8, 12, 13, 14, 15, 11, 7, 3, 2, 1, 5, 9, 10, 6};
  dibujar_patron(espiral, 4, red, green, blue);
}

void dibujar_patron(int patron[], int cara, int red, int green, int blue) {
  for (int i = 0; i < NUMPIXELS; i++) {
    cubo[cara].setPixelColor(patron[i], red, green, blue);
    cubo[cara].show();
    delay(DELAY_FADE_CUBO);
  }
}

void fade_cube() {
  int red = 255;
  int green = 0;
  int blue = 0;
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

void alternos(int red, int green, int blue) {
  for (int i = 0; i < CARAS; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      if (j % 2) {
        cubo[i].setPixelColor(j, red, green, blue);
      } else {
        cubo[i].setPixelColor(j, 255, 255, 255);
      }
    }
  }
}
