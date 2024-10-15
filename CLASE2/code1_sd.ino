#include "FS.h"
#include "SD_MMC.h"

void setup() {
  Serial.begin(115200);
  
  // Inicializa la tarjeta SD
  if (!SD_MMC.begin()) {
    Serial.println("Error al inicializar la tarjeta SD!");
    return;
  }
  
  Serial.println("Tarjeta SD inicializada.");

  // Abre el archivo para escritura
  File file = SD_MMC.open("/hola.txt", FILE_WRITE);
  if (!file) {
    Serial.println("Error al abrir el archivo para escribir!");
    return;
  }

  // Escribe "Hola" en el archivo
  if (file.print("Hola")) {
    Serial.println("Escrito en el archivo: Hola");
  } else {
    Serial.println("Error al escribir en el archivo!");
  }

  // Cierra el archivo
  file.close();
  Serial.println("Archivo cerrado.");
}

void loop() {
  // No es necesario hacer nada en el loop
}
