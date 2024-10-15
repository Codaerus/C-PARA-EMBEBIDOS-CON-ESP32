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
  
  // Leer la primera línea del archivo
  File file = SD_MMC.open("/valores.txt", FILE_READ);
  if (!file) {
    Serial.println("Error al abrir el archivo para leer!");
    return;
  }

  // Leer la primera línea
  String firstLine = "";
  while (file.available()) {
    char c = file.read();
    if (c == '\n') { // Fin de línea
      break;
    }
    firstLine += c; // Agregar el carácter a la línea
  }

  file.close(); // Cerrar el archivo

  // Mostrar la primera línea en el monitor serie
  Serial.print("Primera línea: ");
  Serial.println(firstLine);
}

void loop() {
  // No se requiere hacer nada en el loop
}
