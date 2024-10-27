#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "soc/soc.h"
#include "hal/ledc_types.h"
#include "driver/gpio.h"
#include "driver/periph_ctrl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LEDC_APB_CLK_HZ         (APB_CLK_FREQ)
#define LEDC_REF_CLK_HZ         (REF_CLK_FREQ)
#define LEDC_ERR_DUTY           (0xFFFFFFFF)
#define LEDC_ERR_VAL            (-1)

/**
 * @brief Configuration parameters of LEDC channel for ledc_channel_config function
 */
typedef struct {
    int gpio_num;                   /*!< the LEDC output gpio_num, if you want to use gpio16, gpio_num = 16 */
    ledc_mode_t speed_mode;         /*!< LEDC speed speed_mode, high-speed mode or low-speed mode */
    ledc_channel_t channel;         /*!< LEDC channel (0 - 7) */
    ledc_intr_type_t intr_type;     /*!< configure interrupt, Fade interrupt enable  or Fade interrupt disable */
    ledc_timer_t timer_sel;         /*!< Select the timer source of channel (0 - 3) */
    uint32_t duty;                  /*!< LEDC channel duty, the range of duty setting is [0, (2**duty_resolution)] */
    int hpoint;                     /*!< LEDC channel hpoint value, the max value is 0xfffff */
    struct {
        unsigned int output_invert: 1;/*!< Enable (1) or disable (0) gpio output invert */
    } flags;                        /*!< LEDC flags */

} ledc_channel_config_t;

/**
 * @brief Configuration parameters of LEDC Timer timer for ledc_timer_config function
 */
typedef struct {
    ledc_mode_t speed_mode;                /*!< LEDC speed speed_mode, high-speed mode or low-speed mode */
    union {
        ledc_timer_bit_t duty_resolution;  /*!< LEDC channel duty resolution */
        ledc_timer_bit_t bit_num __attribute__((deprecated)); /*!< Deprecated in ESP-IDF 3.0. This is an alias to 'duty_resolution' for backward compatibility with ESP-IDF 2.1 */
    };
    ledc_timer_t  timer_num;               /*!< The timer source of channel (0 - 3) */
    uint32_t freq_hz;                      /*!< LEDC timer frequency (Hz) */
    ledc_clk_cfg_t clk_cfg;                /*!< Configure LEDC source clock.
                                                For low speed channels and high speed channels, you can specify the source clock using LEDC_USE_REF_TICK, LEDC_USE_APB_CLK or LEDC_AUTO_CLK.
                                                For low speed channels, you can also specify the source clock using LEDC_USE_RTC8M_CLK, in this case, all low speed channel's source clock must be RTC8M_CLK*/
} ledc_timer_config_t;

typedef enum {
#if SOC_LEDC_SUPPORT_HS_MODE
    LEDC_HIGH_SPEED_MODE = 0, /*!< LEDC high speed speed_mode */
#endif
    LEDC_LOW_SPEED_MODE,      /*!< LEDC low speed speed_mode */
    LEDC_SPEED_MODE_MAX,      /*!< LEDC speed limit */
} ledc_mode_t;

typedef enum {
    LEDC_INTR_DISABLE = 0,    /*!< Disable LEDC interrupt */
    LEDC_INTR_FADE_END,       /*!< Enable LEDC interrupt */
    LEDC_INTR_MAX,
} ledc_intr_type_t;

typedef enum {
    LEDC_TIMER_1_BIT = 1,   /*!< LEDC PWM duty resolution of  1 bits */
    LEDC_TIMER_2_BIT,       /*!< LEDC PWM duty resolution of  2 bits */
    LEDC_TIMER_3_BIT,       /*!< LEDC PWM duty resolution of  3 bits */
    LEDC_TIMER_4_BIT,       /*!< LEDC PWM duty resolution of  4 bits */
    LEDC_TIMER_5_BIT,       /*!< LEDC PWM duty resolution of  5 bits */
    LEDC_TIMER_6_BIT,       /*!< LEDC PWM duty resolution of  6 bits */
    LEDC_TIMER_7_BIT,       /*!< LEDC PWM duty resolution of  7 bits */
    LEDC_TIMER_8_BIT,       /*!< LEDC PWM duty resolution of  8 bits */
    LEDC_TIMER_9_BIT,       /*!< LEDC PWM duty resolution of  9 bits */
    LEDC_TIMER_10_BIT,      /*!< LEDC PWM duty resolution of 10 bits */
    LEDC_TIMER_11_BIT,      /*!< LEDC PWM duty resolution of 11 bits */
    LEDC_TIMER_12_BIT,      /*!< LEDC PWM duty resolution of 12 bits */
    LEDC_TIMER_13_BIT,      /*!< LEDC PWM duty resolution of 13 bits */
    LEDC_TIMER_14_BIT,      /*!< LEDC PWM duty resolution of 14 bits */
} ledc_timer_bit_t;

typedef enum {
    LEDC_TIMER_0 = 0, /*!< LEDC timer 0 */
    LEDC_TIMER_1,     /*!< LEDC timer 1 */
    LEDC_TIMER_2,     /*!< LEDC timer 2 */
    LEDC_TIMER_3,     /*!< LEDC timer 3 */
    LEDC_TIMER_MAX,
} ledc_timer_t;

typedef enum {
    LEDC_CHANNEL_0 = 0, /*!< LEDC channel 0 */
    LEDC_CHANNEL_1,     /*!< LEDC channel 1 */
    LEDC_CHANNEL_2,     /*!< LEDC channel 2 */
    LEDC_CHANNEL_3,     /*!< LEDC channel 3 */
    LEDC_CHANNEL_4,     /*!< LEDC channel 4 */
    LEDC_CHANNEL_5,     /*!< LEDC channel 5 */
} ledc_channel_t;

typedef enum {
    LEDC_AUTO_CLK = 0,    /*!< The driver will automatically select the source clock(REF_TICK or APB) based on the giving resolution and duty parameter when init the timer*/
    LEDC_USE_APB_CLK,     /*!< LEDC timer select APB clock as source clock*/
    LEDC_USE_RTC8M_CLK,   /*!< LEDC timer select RTC8M_CLK as source clock. Only for low speed channels and this parameter must be the same for all low speed channels*/
} ledc_clk_cfg_t;

/**
 * @brief LEDC callback parameter
 */
typedef struct {
    ledc_cb_event_t event;              /**< Event name */
    uint32_t speed_mode;                /**< Speed mode of the LEDC channel group */
    uint32_t channel;                   /**< LEDC channel (0 - LEDC_CHANNEL_MAX-1) */
    uint32_t duty;                      /**< LEDC current duty of the channel, the range of duty is [0, (2**duty_resolution) - 1] */
} ledc_cb_param_t;


/**
 * @brief LEDC channel configuration
 *        Configure LEDC channel with the given channel/output gpio_num/interrupt/source timer/frequency(Hz)/LEDC duty resolution
 *
 * @param ledc_conf Pointer of LEDC channel configure struct
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t ledc_channel_config(const ledc_channel_config_t *ledc_conf);

/**
 * @brief LEDC timer configuration
 *        Configure LEDC timer with the given source timer/frequency(Hz)/duty_resolution
 *
 * @param  timer_conf Pointer of LEDC timer configure struct
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 *     - ESP_FAIL Can not find a proper pre-divider number base on the given frequency and the current duty_resolution.
 */
esp_err_t ledc_timer_config(const ledc_timer_config_t *timer_conf);



/**
 * @brief LEDC set duty
 *        This function do not change the hpoint value of this channel. if needed, please call ledc_set_duty_with_hpoint.
 *        only after calling ledc_update_duty will the duty update.
 * @note  ledc_set_duty, ledc_set_duty_with_hpoint and ledc_update_duty are not thread-safe, do not call these functions to
 *        control one LEDC channel in different tasks at the same time.
 *        A thread-safe version of API is ledc_set_duty_and_update.
 * @note  If a fade operation is running in progress on that channel, the driver would not allow it to be stopped.
 *        Other duty operations will have to wait until the fade operation has finished.
 * @param speed_mode Select the LEDC channel group with specified speed mode. Note that not all targets support high speed mode.
 * @param channel LEDC channel (0 - LEDC_CHANNEL_MAX-1), select from ledc_channel_t
 * @param duty Set the LEDC duty, the range of duty setting is [0, (2**duty_resolution) - 1]
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t ledc_set_duty(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t duty);

/**
 * @brief LEDC update channel parameters
 * @note  Call this function to activate the LEDC updated parameters.
 *        After ledc_set_duty, we need to call this function to update the settings.
 *        And the new LEDC parameters don't take effect until the next PWM cycle.
 * @note  ledc_set_duty, ledc_set_duty_with_hpoint and ledc_update_duty are not thread-safe, do not call these functions to
 *        control one LEDC channel in different tasks at the same time.
 *        A thread-safe version of API is ledc_set_duty_and_update
 * @param speed_mode Select the LEDC channel group with specified speed mode. Note that not all targets support high speed mode.
 * @param channel LEDC channel (0 - LEDC_CHANNEL_MAX-1), select from ledc_channel_t
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 *
 */
esp_err_t ledc_update_duty(ledc_mode_t speed_mode, ledc_channel_t channel);
/**
 * @brief Configure LEDC settings
 *
 * @param speed_mode Select the LEDC channel group with specified speed mode. Note that not all targets support high speed mode.
 * @param timer_sel  Timer index (0-3), there are 4 timers in LEDC module
 * @param clock_divider Timer clock divide value, the timer clock is divided from the selected clock source
 * @param duty_resolution Resolution of duty setting in number of bits. The range of duty values is [0, (2**duty_resolution)]
 * @param clk_src Select LEDC source clock.
 *
 * @return
 *     - (-1) Parameter error
 *     - Other Current LEDC duty
 */
esp_err_t ledc_timer_set(ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t clock_divider, uint32_t duty_resolution, ledc_clk_src_t clk_src);


#ifdef __cplusplus
}
#endif
