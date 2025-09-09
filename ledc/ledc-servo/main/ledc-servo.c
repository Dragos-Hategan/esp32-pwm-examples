#include "freertos/FreeRTOS.h"

#include "driver/ledc.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "example";

#define SERVO_PIN       14
#define SERVO_MIN_US    650
#define SERVO_MAX_US    2620
#define SERVO_MAX_DEG   180
#define SERVO_FREQ_HZ   50

static inline uint32_t angle_to_duty(int angle, int timer_res_bits) {
    uint32_t max_duty = (1 << timer_res_bits) - 1;
    uint32_t us = SERVO_MIN_US + (SERVO_MAX_US - SERVO_MIN_US) * angle / SERVO_MAX_DEG;
    return (us * max_duty) / (1000000 / SERVO_FREQ_HZ);
}

void app_main(void) {
    ledc_timer_config_t timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_16_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = SERVO_FREQ_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer);

    ledc_channel_config_t channel = {
        .gpio_num       = SERVO_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&channel);

    int angle = 0;

    while (1) {
        ESP_LOGI(TAG, "Angle of rotation: %d", angle);
        uint32_t duty = angle_to_duty(angle, 16);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

        switch (angle){
            case 0: angle = 90; break;
            case 90: angle = 180; break;
            case 180: angle = 0; break;
        }

        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}
