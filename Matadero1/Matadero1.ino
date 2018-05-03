#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 16
#define CARAS 5
#define DELAY_ENCENDER 0
#define DELAY_SWEEP_CUBO 75
#define DELAY_PISOS 150
#define DELAY_FADE_CUBO 20

int pinesCaras[5] = {5, 4, 0, 2, 14};
int modo=0;
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

  
  if(modo>5)
    modo=0;
  modo++;
  
  switch(modo){
    case 0:
    //RED GREEN BLUE ESPERA(en segundos)
      encendido(255,0,0,5);
      encendido(255,255,0,5);
      encendido(255,0,255,5);
      encendido(0,255,0,5);
      encendido(0,0,255,5);
      encendido(0,255,255,5);
      encendido(255,255,255,5);
      encendido(0,0,0,0.5);
    break;
    case 1:
      random_sweep_cubo(255,0,0);
      random_sweep_cubo(255,255,0);
      random_sweep_cubo(255,0,255);
      random_sweep_cubo(0,255,0);
      random_sweep_cubo(0,0,255);
      random_sweep_cubo(0,255,255);
      random_sweep_cubo(255,255,255);
      random_sweep_cubo(0,0,0);
    break;
    case 2:
      pisos(255,0,0);
      pisos(255,255,0);
      pisos(255,0,255);
      pisos(0,255,0);
      pisos(0,0,255);
      pisos(0,255,255);
      pisos(255,255,255);
      pisos(0,0,0);
    break;
    case 3:
      fade_cube();
    break;
    case 4:
      ola();
      delay(7000);
    break;
    case 5:
      alternos(255,0,0);
      delay(5000);
      alternos(255,255,0);
      delay(5000);
      alternos(255,0,255);
      delay(5000);
      alternos(0,255,0);
      delay(5000);
      alternos(0,0,255);
      delay(5000);
      alternos(0,255,255);
      delay(5000);
      alternos(0,0,0);
      delay(5000);
    break;
    default:
    apagado();
  }

}

void apagado() {
  for (int i = 0; i < CARAS; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      cubo[i].setPixelColor(j, 0, 0, 0);
      cubo[i].show();
    }
  }
}

void encendido(int red,int green, int blue, int espera) {
  for (int i = 0; i < CARAS; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      cubo[i].setPixelColor(j, red, green, blue);
      cubo[i].show();
      delay(DELAY_ENCENDER);
    }
  }
  delay(espera*1000);
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

void pisos(int red, int green, int blue) {
  for (int f = NUMPIXELS - 1; f >= 0; f -= 4) { //15 11 7 3
    for (int k = 0; k <= 3; k++) {
      for (int i = f; i >= f - 3; i--) {
        cubo[k].setPixelColor(i, red, green, blue);
      }
      cubo[k].show();
    }
    delay(DELAY_PISOS);
  }
  int espiral[16] = {0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10, 9};
  dibujar_patron_pisos(espiral, 4,  red, green, blue);
}

void dibujar_patron_pisos(int patron[], int cara, int red, int green, int blue) {
  int test_patron[] = {0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  for (int i = 0; i < NUMPIXELS; i++) {
    cubo[cara].setPixelColor(patron[i], red, green, blue);
    cubo[cara].show();
    delay(DELAY_PISOS-100);
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

void ola(){

    uint32_t c=cubo[0].Color(0, 0, 255);
    delay(500);
    cubo[0].setPixelColor(1, c);
    cubo[0].setPixelColor(2, c);

    cubo[0].setPixelColor(4, c);
    
    cubo[0].setPixelColor(7, c);

    cubo[0].setPixelColor(8, c);

    cubo[0].setPixelColor(9, c);

    cubo[0].setPixelColor(10, c);

    cubo[0].setPixelColor(11, c);

    cubo[0].setPixelColor(12, c);

    cubo[0].setPixelColor(15, c);
    cubo[0].show();

    
    c=cubo[3].Color(0, 255, 0);

    cubo[3].setPixelColor(0, c);

    cubo[3].setPixelColor(1, c);

    cubo[3].setPixelColor(2, c);

    cubo[3].setPixelColor(3, c);

    cubo[3].setPixelColor(4, c);

    cubo[3].setPixelColor(7, c);
    cubo[3].setPixelColor(8, c);
    cubo[3].setPixelColor(11, c);
    cubo[3].setPixelColor(12, c);
    cubo[3].setPixelColor(13, c);
    cubo[3].setPixelColor(14, c);
    cubo[3].setPixelColor(15, c);
    cubo[3].show();


   c=cubo[4].Color(250, 0, 0);
    cubo[4].setPixelColor(0, c);
    cubo[4].setPixelColor(1, c);
    cubo[4].setPixelColor(2, c);
    cubo[4].setPixelColor(3, c);
    cubo[4].setPixelColor(4, c);
    cubo[4].setPixelColor(8, c);
    cubo[4].setPixelColor(12, c);
    cubo[4].show();
 
    for(int i=0;i<16;i++){
      cubo[1].setPixelColor(i,40,40,40);
      cubo[1].show();
      cubo[2].setPixelColor(i,40,40,40);
      cubo[2].show();

    }

delay(200);

  
}
/*
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
}*/


void alternos(int red, int green, int blue) {
  bool alt = false;
  int color[8] = {1, 3, 4, 6, 9, 11, 12, 14};
  int white[8] = {0, 2, 5, 7, 8, 10, 13, 15};

  for (int i = 0; i < CARAS; i++) {
    for (int j = 0; j < NUMPIXELS / 2; j++) {
      cubo[i].setPixelColor(color[j], red, green, blue);
      cubo[i].show();
    }
    for (int j = 0; j < NUMPIXELS / 2; j++) {
      cubo[i].setPixelColor(white[j], 150, 150, 150);
      cubo[i].show();
    }
    cubo[i].show();
  }
}
