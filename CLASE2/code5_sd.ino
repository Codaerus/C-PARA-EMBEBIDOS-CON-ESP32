#include "FS.h"
#include "SD_MMC.h"

unsigned long t1 = 0; // Temporizador para la primera línea
unsigned long t2 = 0; // Temporizador para el último valor
const long interval1 = 4000; // Intervalo para leer la primera línea
const long interval2 = 5000; // Intervalo para leer el último valor

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
  // Consultar la primera línea cada 4 segundos
  if (millis() - t1 > interval1) {
    t1 = millis(); // Actualiza el tiempo

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

  // Consultar el último valor cada 5 segundos
  if (millis() - t2 > interval2) {
    t2 = millis(); // Actualiza el tiempo

    // Leer el contenido del archivo
    File file = SD_MMC.open("/valores.txt", FILE_READ);
    if (!file) {
      Serial.println("Error al abrir el archivo para leer!");
      return;
    }

    // Leer el último valor
    String lastLine = "";
    while (file.available()) {
      char c = file.read();
      if (c == '\n') {
        lastLine = ""; // Reiniciar para leer la siguiente línea
      }
      lastLine += c; // Agregar el carácter a la línea
    }

    file.close(); // Cerrar el archivo

    // Mostrar el último valor en el monitor serie
    Serial.print("Último valor: ");
    Serial.println(lastLine);
  }
}
