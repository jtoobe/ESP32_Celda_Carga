/*
  Rui Santos
  Detalles completos del proyecto en https://RandomNerdTutorials.com/esp32-load-cell-hx711/
  
  Se concede permiso, libre de cargos, a cualquier persona que obtenga una copia
  de este software y la documentación asociada.
  
  El aviso de copyright anterior y este permiso deberán incluirse en todas
  las copias o partes sustanciales del software.

  Corregido por JTOOBE para repositorio UA

*/

// Calibrando la celda de carga
#include <Arduino.h>
#include "soc/rtc.h"
#include "HX711.h"

// Cableado del circuito HX711
const int LOADCELL_DOUT_PIN = 5;
const int LOADCELL_SCK_PIN = 18;

HX711 scale;

void setup() {
  Serial.begin(115200);
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    scale.set_scale();    
    Serial.println("Tara... retire cualquier peso de la balanza.");
    delay(5000);
    scale.tare();
    Serial.println("Tara realizada...");
    Serial.print("Coloque un peso conocido en la balanza...");
    delay(5000);
    long reading = scale.get_units(10);
    Serial.print("Resultado: ");
    Serial.println(reading);
  } 
  else {
    Serial.println("HX711 no encontrado.");
  }
  delay(1000);
}

//El factor de calibración será (lectura)/(peso conocido)
