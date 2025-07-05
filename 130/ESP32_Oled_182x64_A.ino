#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// pantalla 0.93inches
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// pantalla 1.3inches
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


// Simulación de valores para el gráfico
int barras[] = {10, 25, 18, 35, 20};
int num_barras = sizeof(barras)/sizeof(barras[0]);

void setup() {
  Wire.begin();
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();

  // Título
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(20, 10, "Monitor OLED");

  // Texto en distintas ubicaciones
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0, 25, "Temperatura:");
  u8g2.drawStr(90, 25, "23.5 C");

  // Línea divisoria
  u8g2.drawLine(0, 28, 127, 28);

  // Gráfico de barras
  int x = 10;
  for (int i = 0; i < num_barras; i++) {
    u8g2.drawBox(x, 60 - barras[i], 10, barras[i]);
    x += 15;
  }

  // Marco animado (cambia de tamaño cada loop)
  static int marco_size = 0;
  u8g2.drawFrame(marco_size, marco_size, 128 - 2*marco_size, 64 - 2*marco_size);
  marco_size = (marco_size + 1) % 10;

  u8g2.sendBuffer();
  delay(300);
}
