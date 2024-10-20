void vTaskDelay( const TickType_t xTicksToDelay )
/**
  * En FreeRTOS se utiliza para suspender la ejecución de una tarea durante un periodo de tiempo específico.
  * param: const TickType_t xTicksToDelay 
  *       Este parámetro especifica el tiempo de espera en "ticks" del sistema.
  *       ticks = (milisegundos/duración de un tick(milisegundo))
  * Ticks del Sistema: FreeRTOS utiliza ticks como su unidad de tiempo.
  * Duración de un Tick: La macro portTICK_PERIOD_MS representa la duración de un tick en milisegundos.
  * @return None
  */


static inline IRAM_ATTR BaseType_t xTaskCreate(
                            TaskFunction_t pvTaskCode,
                            const char * const pcName,     /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                            const uint32_t usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask) PRIVILEGED_FUNCTION
    {
        return xTaskCreatePinnedToCore( pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, tskNO_AFFINITY );
    }
/*
 *static: Limita la visibilidad de la función al archivo en el que se define.
 *inline: Sugerencia al compilador para que intente inyectar el cuerpo de la función en las llamadas.
 *IRAM_ATTR: Indica que la función debe estar en la memoria IRAM para un acceso rápido.
 *BaseType_t: Tipo de retorno de la función, que indica el éxito o fallo al crear la tarea.
 *
 *Parametros:
 *            TaskFunction_t pvTaskCode: Es un puntero a la función que implementa la tarea.
 *                                       typedef void (* TaskFunction_t)( void * );
 *                                       Esta función debe tener el siguiente prototipo: 
 *                                       void vTaskFunction(void *pvParameters), 
 *                                       donde pvParameters es un puntero que se puede usar para pasar parámetros a la tarea.
 *            const char * const pcName: Es un nombre descriptivo para la tarea. Este nombre es 
                                         útil para el seguimiento y la depuración, ya que puede 
                                        aparecer en herramientas de monitoreo. No es obligatorio que 
                                        sea único, pero es recomendable para facilitar la identificación.
                                        Tipo: Un puntero constante a una cadena de caracteres.
              const uint32_t usStackDepth:Es la cantidad de espacio de pila (stack) que se asignará a la 
                                        tarea, medida en palabras (no en bytes). Este valor depende de la 
                                        complejidad de la tarea; tareas más complejas requieren más espacio de pila.
                                        Tipo: Un entero sin signo de 32 bits (uint32_t).
              void * const pvParameters:Es un puntero a los parámetros que se pasarán a la tarea. Puede 
                                        ser cualquier tipo de dato. Si no se necesitan parámetros, se puede pasar NULL.
                                        Tipo: Un puntero genérico.
              UBaseType_t uxPriority:   Es la prioridad de la tarea. Las prioridades más altas se ejecutan 
                                        antes que las más bajas. FreeRTOS permite establecer prioridades que van desde 
                                        0 (baja) hasta un máximo definido por el usuario.
                                        Tipo: Un entero de tipo base (UBaseType_t).
              TaskHandle_t * const pxCreatedTask:Es un puntero a una variable que se utilizará para almacenar el 
                                        "handle" (identificador) de la tarea recién creada. Esto puede ser útil si 
                                        deseas manipular la tarea más adelante (por ejemplo, suspenderla o eliminarla). 
                                        Si no necesitas el handle, puedes pasar NULL.
                                        Tipo: Un puntero a TaskHandle_t, que es un tipo definido por FreeRTOS.
 */
