#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp32/rom/ets_sys.h"

/*
   The code is for the assignment1 of embedded software
   My name is Wenbin Lin, my surname is Lin. 
   For the parameter a, the value maps to 12; 
   For the parameter b, the value maps to 9;
   For the parameter c, the value maps to 13;
   For the parameter d, the value maps to 13;
   For the alternative data output bahavior, the option is 2. The style is gnerating a reversed form of the data waveform (from the largest pulse to the shortest) until the Output Select push button is pressed again.
*/

//Define a debug mode, if in the production mode, the line can be commented out
#define _DEBUG_MODE
//Define different timing values and some other parameters in the debug mode
#ifdef _DEBUG_MODE
  #define SYNC_ON (50*1000)
  #define A (12*100*1000)
  #define ON_INCREMENT (50*1000)
  #define B (9*100*1000)
  #define C (13+4)
  #define D (13*500*1000)
//Define different timing values and some other parameters in the production mode
#else
  #define SYNC_ON 50
  #define A (12*100)
  #define ON_INCREMENT (50)
  #define B (9*100)
  #define C (13+4)
  #define D (13*500)
#endif

// Define pin assignments
#define ENABLE_PIN 16
#define SELECT_PIN 17
#define ENABLE_LED_PIN 27
#define SELECT_LED_PIN 26
// Debounce delay in milliseconds
#define DEBOUNCE_DELAY 100  

//set the logging tag
static const char *TAG = "MAIN";
//set the initial state of the enable and select signal
volatile bool enable_state = true;
volatile bool select_state = true;
//set the initial last interrupt time for enable and select button
volatile uint64_t lastEnableInterruptTime = 0;
volatile uint64_t lastSelectInterruptTime = 0;

// Interrupt handler for enable and select button press
static void IRAM_ATTR enable_pressed_handle(void* arg);
static void IRAM_ATTR select_pressed_handle(void* arg);


static void IRAM_ATTR enable_pressed_handle(void* arg) {
    uint64_t currentTime = esp_timer_get_time() / 1000;
    //set button debouncing delay
    if (currentTime - lastEnableInterruptTime > DEBOUNCE_DELAY) {
        //toggle the enable state when pressing the enable button
        enable_state = !enable_state;
        //update the last interrupt time of enable button
        lastEnableInterruptTime = currentTime;
    }
}

static void IRAM_ATTR select_pressed_handle(void* arg) {
    uint64_t currentTime = esp_timer_get_time() / 1000;
    //set button debouncing delay
    if (currentTime - lastSelectInterruptTime > DEBOUNCE_DELAY) {
        //toggle the select signal state when pressing the select button
        select_state = !select_state;
        //update the last interrupt time of select button
        lastSelectInterruptTime = currentTime;
    }
}

void app_main() {
    //set the enable and select button pin config
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << ENABLE_PIN) | (1ULL << SELECT_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        //interrupt function triggered in the rising edge
        .intr_type = GPIO_INTR_POSEDGE
    };
    gpio_config(&io_conf);

    //set the enable signal and select signal led pin config
    gpio_config_t led_conf = {
        .pin_bit_mask = (1ULL << ENABLE_LED_PIN) | (1ULL << SELECT_LED_PIN),
        .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&led_conf);

    //enable the interrup service 
    gpio_install_isr_service(0);
    //set the interrupt handler for the enable button
    gpio_isr_handler_add(ENABLE_PIN, enable_pressed_handle, NULL);
    //set the interrupt handler for the select button
    gpio_isr_handler_add(SELECT_PIN, select_pressed_handle, NULL);

    //setting the inital level of the select and enable led pin 0
    gpio_set_level(ENABLE_LED_PIN, 0);
    gpio_set_level(SELECT_LED_PIN, 0);

    while (1) {
        // condition 1: select signal and enable signal state is on
        if (select_state && enable_state) {
            ESP_LOGI(TAG, "into condition 1");
            gpio_set_level(SELECT_LED_PIN, 1);
            ets_delay_us(SYNC_ON); 
            gpio_set_level(SELECT_LED_PIN, 0);
            for (int i = C; i > 0; i--) {
                gpio_set_level(ENABLE_LED_PIN, 1);
                ets_delay_us(A + ((i - 1) * ON_INCREMENT));
                gpio_set_level(ENABLE_LED_PIN, 0);
                ets_delay_us(B);
            }
            ets_delay_us(D);
        } 
        // condition 2: select signal state is on while enable signal state is off
        else if (select_state && !enable_state) {
            ESP_LOGI(TAG, "into condition 2");
            gpio_set_level(SELECT_LED_PIN, 1);
            ets_delay_us(SYNC_ON); 
            gpio_set_level(SELECT_LED_PIN, 0);
            for (int i = 0; i < C; i++) {
                ets_delay_us(A + (i * ON_INCREMENT));
                ets_delay_us(B);
            }
            ets_delay_us(D);
        } 
        // condition 3: select signal state and enable signal state is off
        else if (!select_state && !enable_state) {
            ESP_LOGI(TAG, "into condition 3");
            gpio_set_level(SELECT_LED_PIN, 0);
            gpio_set_level(ENABLE_LED_PIN, 0);
            ets_delay_us(D);
        } 
        // condition 4: select signal state is off while enable signal state is on
        else if (!select_state && enable_state) {
            ESP_LOGI(TAG, "into condition 4");
            gpio_set_level(SELECT_LED_PIN, 0);
            for (int i = 0; i < C; i++) {
                gpio_set_level(ENABLE_LED_PIN, 1);
                ets_delay_us(A + (i * ON_INCREMENT));
                gpio_set_level(ENABLE_LED_PIN, 0);
                ets_delay_us(B);
            }
            ets_delay_us(D);
        }
    }
}
