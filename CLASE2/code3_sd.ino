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
  
  // Comprobar si ha pasado el intervalo de 4000 milisegundos (4 segundos)
  if (millis() - t > 4000) {
    t = millis(); // Actualiza el tiempo

    // Leer el contenido existente del archivo
    String existingContent = "";
    File file = SD_MMC.open("/valores.txt", FILE_READ);
    if (file) {
      while (file.available()) {
        existingContent += String((char)file.read());
      }
      file.close();
    }

    // Abre el archivo para escritura (sobreescribir)
    file = SD_MMC.open("/valores.txt", FILE_WRITE);
    if (!file) {
      Serial.println("Error al abrir el archivo para escribir!");
      return;
    }

    // Incrementa el contador y escribe el nuevo valor al principio
    valueCount++;
    file.print("Valor ");
    file.print(valueCount);
    file.print("\n");
    // Escribe el contenido existente después del nuevo valor
    file.print(existingContent);
    Serial.print("Escrito en el archivo: Valor ");
    Serial.println(valueCount);

    // Cierra el archivo
    file.close();
    Serial.println("Archivo cerrado.");
  }
}

