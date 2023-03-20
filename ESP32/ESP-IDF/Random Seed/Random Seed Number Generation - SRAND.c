/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_flash.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void app_main(void)
{
    printf("Random Generator example! \nGenerating a random number:\n");
    int i, n;
    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t)); //generate the random number
    printf("%d\n", rand() % 100); //set the generator number range

    fflush(stdout);
    vTaskDelay(10000 / portTICK_PERIOD_MS); //delay for 10 seconds before taking another value
    printf("Restarting now.\n"); //print a message before the microcontroller resets
    esp_restart(); //restart now
}
