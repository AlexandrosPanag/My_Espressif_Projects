/*********
 Created By Alexandros Panagiotakopoulos - alexandrospanag.github.io
 Based on the work of the official ESP-IDF Hello World Example
*********/

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

void app_main(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ", //print a message with the ESP module
           CONFIG_IDF_TARGET, //find the ESP module target
           chip_info.cores, //display the cores
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "", //display if it has BT Feature
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : ""); //display if it has BLE Feature

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev); //find the silicon revision
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) { ///check if the flash size can be discovered
        printf("Get flash size failed"); //if it can't be discovered then return with an error
        return;
    }

    printf("%uMB %s flash\n", flash_size / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external"); //find the chip features

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size()); //find the maximum heap size


    vTaskDelay(10000 / portTICK_PERIOD_MS); //wait 10 seconds
    printf("Restarting now.\n"); //before restarting
    fflush(stdout); //This function returns a zero value on success. If an error occurs, EOF is returned and the error indicator is set (i.e. feof).
    esp_restart(); //restart
}