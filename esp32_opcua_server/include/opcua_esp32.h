#include <Arduino.h>
#include <stdio.h>
#include <stdbool.h>
#include <esp_err.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stddef.h>
#include <sys/param.h>
#include <unistd.h>
#include "esp_log.h"
#include "esp_netif.h"
#include <esp_flash_encrypt.h>
#include <esp_task_wdt.h>
#include <esp_sntp.h>
#include "esp_event.h"
#include "esp_system.h"
#include "esp_task_wdt.h"
#include "nvs_flash.h"
#include "lwip/ip_addr.h"
#include "sdkconfig.h"


extern "C" { 
    #include "model.h" 
    #include "ethernet_connect.h"
    #include "open62541.h"
}

