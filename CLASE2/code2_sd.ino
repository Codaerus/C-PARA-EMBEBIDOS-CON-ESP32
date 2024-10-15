#include "FS.h"
#include "SD_MMC.h"

int valueCount = 0;                 // Contador para los valores
unsigned long t = 0;
void setup() {
  Serial.begin(115200);
  
  // Inicializa la tarjeta SD
  if (!SD_MMC.begin()) {
    Serial.println("Error al inicializar la tarjeta SD!");
    return;
  }
  
  Serial.println("Tarjeta SD inicializada.");
}

void loop() {
  
  // Comprobar si ha pasado el intervalo de 60 segundos
  if (millis()-t>4000) {
    // Abre el archivo para escritura (agregar contenido)
    File file = SD_MMC.open("/valores.txt", FILE_APPEND);
    if (!file) {
      Serial.println("Error al abrir el archivo para escribir!");
      return;
    }
    // Incrementa el contador y escribe en el archivo
    valueCount++;
    file.print("Valor ");
    file.print(valueCount);
    file.print("\n");
    Serial.print("Escrito en el archivo: Valor ");
    Serial.println(valueCount);

    // Cierra el archivo
    file.close();
    Serial.println("Archivo cerrado.");
    t = millis();
  }
}
