//include the necessary libraries to compile!
// By Alexandros Panagiotakopoulos - alexandrospanag.github.io
//

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main(void) //void main
{
    printf("Hello world from ESP-IDF!\n"); //print hello world from ESP-IDF
    fflush(stdout); //code to output the message
    vTaskDelay(1000 / portTICK_PERIOD_MS); //delay for 1 second before running again
    esp_restart(); //restart your module
}
