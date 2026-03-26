/*
 * Detalles completos del proyecto en https://RandomNerdTutorials.com/esp32-load-cell-hx711/
 *
 * Librería HX711 para Arduino - archivo de ejemplo
 * https://github.com/bogde/HX711
 *
 * Licencia MIT
 * (c) 2018 Bogdan Necula
 *

  Corregido por JTOOBE para repositorio UA

**/
#include <Arduino.h>
#include "HX711.h"
#include "soc/rtc.h"

// Cableado del circuito HX711
const int LOADCELL_DOUT_PIN = 5;
const int LOADCELL_SCK_PIN = 18;

HX711 scale;

void setup() {
  Serial.begin(115200);

  Serial.println("Demostración HX711");

  Serial.println("Inicializando la balanza");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Antes de configurar la balanza:");
  Serial.print("lectura: \t\t");
  Serial.println(scale.read());      // imprime una lectura cruda del ADC

  Serial.print("lectura promedio: \t\t");
  Serial.println(scale.read_average(20));   // imprime el promedio de 20 lecturas del ADC

  Serial.print("obtener valor: \t\t");
  Serial.println(scale.get_value(5));   // imprime el promedio de 5 lecturas del ADC menos el peso de tara (aún no configurado)

  Serial.print("obtener unidades: \t\t");
  Serial.println(scale.get_units(5), 1);  // imprime el promedio de 5 lecturas del ADC menos la tara (no configurada) dividido
            // por el parámetro SCALE (aún no configurado)
            
 scale.set_scale(INSERTA TU FACTOR DE CALIBRACIÓN EN LA SIGUIENTE LINEA);
 // scale.set_scale(-471.497);                      // este valor se obtiene calibrando la balanza con pesos conocidos; ver el README para más detalles
  scale.tare();               // reinicia la balanza a 0

  Serial.println("Después de configurar la balanza:");

  Serial.print("lectura: \t\t");
  Serial.println(scale.read());                 // imprime una lectura cruda del ADC

  Serial.print("lectura promedio: \t\t");
  Serial.println(scale.read_average(20));       // imprime el promedio de 20 lecturas del ADC

  Serial.print("obtener valor: \t\t");
  Serial.println(scale.get_value(5));   // imprime el promedio de 5 lecturas del ADC menos el peso de tara, configurado con tare()

  Serial.print("obtener unidades: \t\t");
  Serial.println(scale.get_units(5), 1);        // imprime el promedio de 5 lecturas del ADC menos la tara, dividido
            // por el parámetro SCALE configurado con set_scale

  Serial.println("Lecturas:");
}

void loop() {
  Serial.print("una lectura:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| promedio:\t");
  Serial.println(scale.get_units(10), 5);

  scale.power_down();             // pone el ADC en modo de suspensión
  delay(5000);
  scale.power_up();
}
