#if CONFIG_IDF_TARGET_ESP32
typedef enum {
    GPIO_NUM_NC = -1,    /*!< Use to signal not connected to S/W */
    GPIO_NUM_0 = 0,     /*!< GPIO0, input and output */
    GPIO_NUM_1 = 1,     /*!< GPIO1, input and output */
    GPIO_NUM_2 = 2,     /*!< GPIO2, input and output */
    GPIO_NUM_3 = 3,     /*!< GPIO3, input and output */
    GPIO_NUM_4 = 4,     /*!< GPIO4, input and output */
    GPIO_NUM_5 = 5,     /*!< GPIO5, input and output */
    GPIO_NUM_6 = 6,     /*!< GPIO6, input and output */
    GPIO_NUM_7 = 7,     /*!< GPIO7, input and output */
    GPIO_NUM_8 = 8,     /*!< GPIO8, input and output */
    GPIO_NUM_9 = 9,     /*!< GPIO9, input and output */
    GPIO_NUM_10 = 10,   /*!< GPIO10, input and output */
    GPIO_NUM_11 = 11,   /*!< GPIO11, input and output */
    GPIO_NUM_12 = 12,   /*!< GPIO12, input and output */
    GPIO_NUM_13 = 13,   /*!< GPIO13, input and output */
    GPIO_NUM_14 = 14,   /*!< GPIO14, input and output */
    GPIO_NUM_15 = 15,   /*!< GPIO15, input and output */
    GPIO_NUM_16 = 16,   /*!< GPIO16, input and output */
    GPIO_NUM_17 = 17,   /*!< GPIO17, input and output */
    GPIO_NUM_18 = 18,   /*!< GPIO18, input and output */
    GPIO_NUM_19 = 19,   /*!< GPIO19, input and output */
    GPIO_NUM_20 = 20,   /*!< GPIO20, input and output */
    GPIO_NUM_21 = 21,   /*!< GPIO21, input and output */
    GPIO_NUM_22 = 22,   /*!< GPIO22, input and output */
    GPIO_NUM_23 = 23,   /*!< GPIO23, input and output */
    GPIO_NUM_25 = 25,   /*!< GPIO25, input and output */
    GPIO_NUM_26 = 26,   /*!< GPIO26, input and output */
    GPIO_NUM_27 = 27,   /*!< GPIO27, input and output */
    GPIO_NUM_28 = 28,   /*!< GPIO28, input and output */
    GPIO_NUM_29 = 29,   /*!< GPIO29, input and output */
    GPIO_NUM_30 = 30,   /*!< GPIO30, input and output */
    GPIO_NUM_31 = 31,   /*!< GPIO31, input and output */
    GPIO_NUM_32 = 32,   /*!< GPIO32, input and output */
    GPIO_NUM_33 = 33,   /*!< GPIO33, input and output */
    GPIO_NUM_34 = 34,   /*!< GPIO34, input mode only */
    GPIO_NUM_35 = 35,   /*!< GPIO35, input mode only */
    GPIO_NUM_36 = 36,   /*!< GPIO36, input mode only */
    GPIO_NUM_37 = 37,   /*!< GPIO37, input mode only */
    GPIO_NUM_38 = 38,   /*!< GPIO38, input mode only */
    GPIO_NUM_39 = 39,   /*!< GPIO39, input mode only */
    GPIO_NUM_MAX,
/** @endcond */
} gpio_num_t;

typedef enum {
    GPIO_MODE_DISABLE = GPIO_MODE_DEF_DISABLE,                                                         /*!< GPIO mode : disable input and output             */
    GPIO_MODE_INPUT = GPIO_MODE_DEF_INPUT,                                                             /*!< GPIO mode : input only                           */
    GPIO_MODE_OUTPUT = GPIO_MODE_DEF_OUTPUT,                                                           /*!< GPIO mode : output only mode                     */
    GPIO_MODE_OUTPUT_OD = ((GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)),                               /*!< GPIO mode : output only with open-drain mode     */
    GPIO_MODE_INPUT_OUTPUT_OD = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)), /*!< GPIO mode : output and input with open-drain mode*/
    GPIO_MODE_INPUT_OUTPUT = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT)),                         /*!< GPIO mode : output and input mode                */
} gpio_mode_t;

typedef enum {
    GPIO_PULLUP_ONLY,               /*!< Pad pull up            */
    GPIO_PULLDOWN_ONLY,             /*!< Pad pull down          */
    GPIO_PULLUP_PULLDOWN,           /*!< Pad pull up + pull down*/
    GPIO_FLOATING,                  /*!< Pad floating           */
} gpio_pull_mode_t;

void gpio_pad_select_gpio(uint8_t gpio_num);

/**
  * Se utiliza para seleccionar un pin GPIO específico y prepararlo para su uso
  * @return None
  */

esp_err_t gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode)
/**
  * Se utiliza para configurar la dirección (modo) de un pin GPIO específico en el ESP32.
  * @return 
          ESP_OK: La operación se realizó con éxito.
          ESP_ERR_INVALID_ARG: Se pasó un argumento inválido (por ejemplo, un número de GPIO fuera de rango).
  * La función retorna un valor de tipo esp_err_t, que indica el estado de la operación
  * Sin configurar la dirección, el pin no podrá funcionar correctamente ni podrás leer o escribir datos en él.
  */
esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
/**
  * Se utiliza para establecer el estado (nivel lógico) de un pin GPIO específico en el ESP32.
  * @return 
          ESP_OK: La operación se realizó con éxito.
          ESP_ERR_INVALID_ARG: Se pasó un argumento inválido (por ejemplo, un número de GPIO fuera de rango).
  * La función retorna un valor de tipo esp_err_t, que indica el estado de la operación
  */

void vTaskDelay( const TickType_t xTicksToDelay )
/**
  * en FreeRTOS se utiliza para suspender la ejecución de una tarea durante un periodo de tiempo específico.
  * param: const TickType_t xTicksToDelay 
  *       Este parámetro especifica el tiempo de espera en "ticks" del sistema.
  *       ticks = (milisegundos/duración de un tick(milisegundo))
  * Ticks del Sistema: FreeRTOS utiliza ticks como su unidad de tiempo.
  * Duración de un Tick: La macro portTICK_PERIOD_MS representa la duración de un tick en milisegundos.
  * @return None
  */

esp_err_t gpio_set_pull_mode(gpio_num_t gpio_num, gpio_pull_mode_t pull)
/**
  * Se utiliza para configurar la resistencia de pull (pull-up o pull-down) de un pin GPIO en el ESP32.
  * @return 
          ESP_OK: La operación se realizó con éxito.
          ESP_ERR_INVALID_ARG: Se pasó un argumento inválido (por ejemplo, un número de GPIO fuera de rango).
  * La función retorna un valor de tipo esp_err_t, que indica el estado de la operación
  */
int gpio_get_level(gpio_num_t gpio_num)
/**
  * Se utiliza para leer el estado lógico de un GPIO
  * @return: 0 | 1
  */
