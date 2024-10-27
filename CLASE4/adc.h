#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_IDF_TARGET_ESP32
/**** `adc1_channel_t` will be deprecated functions, combine into `adc_channel_t` ********/
typedef enum {
    ADC1_CHANNEL_0 = 0, /*!< ADC1 channel 0 is GPIO36 */
    ADC1_CHANNEL_1,     /*!< ADC1 channel 1 is GPIO37 */
    ADC1_CHANNEL_2,     /*!< ADC1 channel 2 is GPIO38 */
    ADC1_CHANNEL_3,     /*!< ADC1 channel 3 is GPIO39 */
    ADC1_CHANNEL_4,     /*!< ADC1 channel 4 is GPIO32 */
    ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO33 */
    ADC1_CHANNEL_6,     /*!< ADC1 channel 6 is GPIO34 */
    ADC1_CHANNEL_7,     /*!< ADC1 channel 7 is GPIO35 */
    ADC1_CHANNEL_MAX,
} adc1_channel_t;

/**
 * @brief ADC attenuation parameter. Different parameters determine the range of the ADC. See ``adc1_config_channel_atten``.
 */
typedef enum {
    ADC_ATTEN_DB_0   = 0,  /*!<No input attenumation, ADC can measure up to approx. 800 mV. */
    ADC_ATTEN_DB_2_5 = 1,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 2.5 dB (1.33 x) */
    ADC_ATTEN_DB_6   = 2,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 6 dB (2 x) */
    ADC_ATTEN_DB_11  = 3,  /*!<The input voltage of ADC will be attenuated extending the range of measurement by about 11 dB (3.55 x) */
    ADC_ATTEN_MAX,
} adc_atten_t;

/**
 * @brief ADC resolution setting option.
 * @note  Only used in single read mode
 */
typedef enum {
    ADC_WIDTH_BIT_9  = 0, /*!< ADC capture width is 9Bit. */
    ADC_WIDTH_BIT_10 = 1, /*!< ADC capture width is 10Bit. */
    ADC_WIDTH_BIT_11 = 2, /*!< ADC capture width is 11Bit. */
    ADC_WIDTH_BIT_12 = 3, /*!< ADC capture width is 12Bit. */
} adc_bits_width_t;
/**
 * @brief ADC rtc controller attenuation option.
 *
 * @note  This definitions are only for being back-compatible
 */
#define ADC_ATTEN_0db   ADC_ATTEN_DB_0
#define ADC_ATTEN_2_5db ADC_ATTEN_DB_2_5
#define ADC_ATTEN_6db   ADC_ATTEN_DB_6
#define ADC_ATTEN_11db  ADC_ATTEN_DB_11

/**
 * The default (max) bit width of the ADC of current version. You can also get the maximum bitwidth
 * by `SOC_ADC_MAX_BITWIDTH` defined in soc_caps.h.
 */
#define ADC_WIDTH_BIT_DEFAULT   (ADC_WIDTH_MAX-1)

//this definitions are only for being back-compatible
#define ADC_WIDTH_9Bit  ADC_WIDTH_BIT_9
#define ADC_WIDTH_10Bit ADC_WIDTH_BIT_10
#define ADC_WIDTH_11Bit ADC_WIDTH_BIT_11
#define ADC_WIDTH_12Bit ADC_WIDTH_BIT_12



/*---------------------------------------------------------------
                    ADC Single Read Setting
---------------------------------------------------------------*/

/**
 * @brief Set the attenuation of a particular channel on ADC1, and configure its associated GPIO pin mux.
 *
 * The default ADC voltage is for attenuation 0 dB and listed in the table below.
 * By setting higher attenuation it is possible to read higher voltages.
 *
 * Due to ADC characteristics, most accurate results are obtained within the "suggested range"
 * shown in the following table.
 *
 *     +----------+-------------+-----------------+
 *     |          | attenuation | suggested range |
 *     |    SoC   |     (dB)    |      (mV)       |
 *     +==========+=============+=================+
 *     |          |       0     |    100 ~  950   |
 *     |          +-------------+-----------------+
 *     |          |       2.5   |    100 ~ 1250   |
 *     |   ESP32  +-------------+-----------------+
 *     |          |       6     |    150 ~ 1750   |
 *     |          +-------------+-----------------+
 *     |          |      11     |    150 ~ 2450   |
 *     +----------+-------------+-----------------+
 *     |          |       0     |      0 ~  750   |
 *     |          +-------------+-----------------+
 *     |          |       2.5   |      0 ~ 1050   |
 *     | ESP32-S2 +-------------+-----------------+
 *     |          |       6     |      0 ~ 1300   |
 *     |          +-------------+-----------------+
 *     |          |      11     |      0 ~ 2500   |
 *     +----------+-------------+-----------------+
 *
 * For maximum accuracy, use the ADC calibration APIs and measure voltages within these recommended ranges.
 *
 * @note For any given channel, this function must be called before the first time ``adc1_get_raw()`` is called for that channel.
 *
 * @note This function can be called multiple times to configure multiple
 *       ADC channels simultaneously. You may call ``adc1_get_raw()`` only after configuring a channel.
 *
 * @param channel ADC1 channel to configure
 * @param atten  Attenuation level
 *
 * @return
 *     - ESP_OK success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t adc1_config_channel_atten(adc1_channel_t channel, adc_atten_t atten);

/**
 * @brief Configure ADC1 capture width, meanwhile enable output invert for ADC1.
 *        The configuration is for all channels of ADC1
 * @param width_bit Bit capture width for ADC1
 *
 * @return
 *     - ESP_OK success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t adc1_config_width(adc_bits_width_t width_bit);

/**
 * @brief Take an ADC1 reading from a single channel.
 * @note ESP32:
 *       When the power switch of SARADC1, SARADC2, HALL sensor and AMP sensor is turned on,
 *       the input of GPIO36 and GPIO39 will be pulled down for about 80ns.
 *       When enabling power for any of these peripherals, ignore input from GPIO36 and GPIO39.
 *       Please refer to section 3.11 of 'ECO_and_Workarounds_for_Bugs_in_ESP32' for the description of this issue.
 *       As a workaround, call adc_power_acquire() in the app. This will result in higher power consumption (by ~1mA),
 *       but will remove the glitches on GPIO36 and GPIO39.
 *
 * @note Call ``adc1_config_width()`` before the first time this
 *       function is called.
 *
 * @note For any given channel, adc1_config_channel_atten(channel)
 *       must be called before the first time this function is called. Configuring
 *       a new channel does not prevent a previously configured channel from being read.
 *
 * @param  channel ADC1 channel to read
 *
 * @return
 *     - -1: Parameter error
 *     -  Other: ADC1 channel reading.
 */
int adc1_get_raw(adc1_channel_t channel);

/**
 * @brief Configure ADC capture width.
 *
 * @param adc_unit ADC unit index
 * @param width_bit Bit capture width for ADC unit.
 *
 * @return
 *     - ESP_OK success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t adc_set_data_width(adc_unit_t adc_unit, adc_bits_width_t width_bit);

/**
 * @brief Configure the ADC2 channel, including setting attenuation.
 *
 * The default ADC voltage is for attenuation 0 dB and listed in the table below.
 * By setting higher attenuation it is possible to read higher voltages.
 *
 * Due to ADC characteristics, most accurate results are obtained within the "suggested range"
 * shown in the following table.
 *
 *     +----------+-------------+-----------------+
 *     |          | attenuation | suggested range |
 *     |    SoC   |     (dB)    |      (mV)       |
 *     +==========+=============+=================+
 *     |          |       0     |    100 ~  950   |
 *     |          +-------------+-----------------+
 *     |          |       2.5   |    100 ~ 1250   |
 *     |   ESP32  +-------------+-----------------+
 *     |          |       6     |    150 ~ 1750   |
 *     |          +-------------+-----------------+
 *     |          |      11     |    150 ~ 2450   |
 *     +----------+-------------+-----------------+
 *     |          |       0     |      0 ~  750   |
 *     |          +-------------+-----------------+
 *     |          |       2.5   |      0 ~ 1050   |
 *     | ESP32-S2 +-------------+-----------------+
 *     |          |       6     |      0 ~ 1300   |
 *     |          +-------------+-----------------+
 *     |          |      11     |      0 ~ 2500   |
 *     +----------+-------------+-----------------+
 *
 * For maximum accuracy, use the ADC calibration APIs and measure voltages within these recommended ranges.
 *
 * @note This function also configures the input GPIO pin mux to
 *       connect it to the ADC2 channel. It must be called before calling
 *       ``adc2_get_raw()`` for this channel.
 *
 * @note For any given channel, this function must be called before the first time ``adc2_get_raw()`` is called for that channel.
 *
 * @param channel ADC2 channel to configure
 * @param atten  Attenuation level
 *
 * @return
 *     - ESP_OK success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t adc2_config_channel_atten(adc2_channel_t channel, adc_atten_t atten);

/**
 * @brief Take an ADC2 reading on a single channel
 *
 * @note ESP32:
 *       When the power switch of SARADC1, SARADC2, HALL sensor and AMP sensor is turned on,
 *       the input of GPIO36 and GPIO39 will be pulled down for about 80ns.
 *       When enabling power for any of these peripherals, ignore input from GPIO36 and GPIO39.
 *       Please refer to section 3.11 of 'ECO_and_Workarounds_for_Bugs_in_ESP32' for the description of this issue.
 *       As a workaround, call adc_power_acquire() in the app. This will result in higher power consumption (by ~1mA),
 *       but will remove the glitches on GPIO36 and GPIO39.
 *
 *
 * @note ESP32:
 *       For a given channel, ``adc2_config_channel_atten()``
 *       must be called before the first time this function is called. If Wi-Fi is started via ``esp_wifi_start()``, this
 *       function will always fail with ``ESP_ERR_TIMEOUT``.
 *
 * @note ESP32-S2:
 *       ADC2 support hardware arbiter. The arbiter is to improve the use efficiency of ADC2. After the control right is robbed by the high priority,
 *       the low priority controller will read the invalid ADC2 data. Default priority: Wi-Fi > RTC > Digital;
 *
 * @param channel ADC2 channel to read
 * @param width_bit Bit capture width for ADC2
 * @param raw_out the variable to hold the output data.
 *
 * @return
 *     - ESP_OK if success
 *     - ESP_ERR_TIMEOUT ADC2 is being used by other controller and the request timed out.
 *     - ESP_ERR_INVALID_STATE The controller status is invalid. Please try again.
 */
esp_err_t adc2_get_raw(adc2_channel_t channel, adc_bits_width_t width_bit, int *raw_out);


#ifdef __cplusplus
}
#endif
