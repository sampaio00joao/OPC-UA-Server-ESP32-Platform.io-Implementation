#include "opcua_esp32.h"
#include "sensors.h"
#include <Wire.h>
#include <open62541.h>

#define EXAMPLE_ESP_MAXIMUM_RETRY 10

#define TAG "OPCUA_ESP32"
#define SNTP_TAG "SNTP"
#define MEMORY_TAG "MEMORY"

static UA_Boolean running = true;
static UA_Boolean isServerCreated = false;
RTC_DATA_ATTR static int boot_count = 0;

static UA_StatusCode
UA_ServerConfig_setUriName(UA_ServerConfig *uaServerConfig, const char *uri, const char *name)
{
    // delete pre-initialized values
    UA_String_clear(&uaServerConfig->applicationDescription.applicationUri);
    UA_LocalizedText_clear(&uaServerConfig->applicationDescription.applicationName);

    uaServerConfig->applicationDescription.applicationUri = UA_String_fromChars(uri);
    uaServerConfig->applicationDescription.applicationName.locale = UA_STRING_NULL;
    uaServerConfig->applicationDescription.applicationName.text = UA_String_fromChars(name);

    for (int i = 0; i < uaServerConfig->endpointsSize; i++)
    {
        UA_String_clear(&uaServerConfig->endpoints[i].server.applicationUri);
        UA_LocalizedText_clear(
            &uaServerConfig->endpoints[i].server.applicationName);

        UA_String_copy(&uaServerConfig->applicationDescription.applicationUri,
                       &uaServerConfig->endpoints[i].server.applicationUri);

        UA_LocalizedText_copy(&uaServerConfig->applicationDescription.applicationName,
                              &uaServerConfig->endpoints[i].server.applicationName);
    }

    return UA_STATUSCODE_GOOD;
}

static void opcua_task(void *arg)
{
    // BufferSize's got to be decreased due to latest refactorings in open62541 v1.2rc.
    UA_Int32 sendBufferSize = 10000; // 16384;
    UA_Int32 recvBufferSize = 10000; //16384;

    ESP_ERROR_CHECK(esp_task_wdt_add(NULL));

    ESP_LOGI(TAG, "Fire up OPC UA Server.");
    UA_Server *server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setMinimalCustomBuffer(config, 4840, 0, sendBufferSize, recvBufferSize);

    const char *appUri = "open62541.esp32.server";
    UA_String hostName = UA_STRING("opcua-esp32");
  
    UA_ServerConfig_setUriName(config, appUri, "OPC_UA_Server_ESP32");
    UA_ServerConfig_setCustomHostname(config, hostName);

    /* Add Information Model Objects Here */
    addCurrentAccelXDataSourceVariable(server);
    addCurrentAccelYDataSourceVariable(server);
    addCurrentAccelZDataSourceVariable(server);

    ESP_LOGI(TAG, "Heap Left : %d", xPortGetFreeHeapSize());
    UA_StatusCode retval = UA_Server_run_startup(server);
    if (retval == UA_STATUSCODE_GOOD)
    {
        while (running)
        {
            UA_Server_run_iterate(server, false);
            vTaskDelay(500 / portTICK_PERIOD_MS); // data write/read delay
            ESP_ERROR_CHECK(esp_task_wdt_reset());
            taskYIELD();
        }
        UA_Server_run_shutdown(server);
    }
    ESP_ERROR_CHECK(esp_task_wdt_delete(NULL));
}

static void opc_event_handler(void *arg, esp_event_base_t event_base,
                              int32_t event_id, void *event_data)
{
    if (!isServerCreated)
    {
        xTaskCreatePinnedToCore(opcua_task, "opcua_task", 24000, NULL, 10, NULL, 1);
        ESP_LOGI(MEMORY_TAG, "Heap size after OPC UA Task : %d", esp_get_free_heap_size());
        isServerCreated = true;
    }
}

static void disconnect_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
}

static void connection_scan(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, GOT_IP_EVENT, &opc_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(BASE_IP_EVENT, DISCONNECT_EVENT, &disconnect_handler, NULL));
    ESP_ERROR_CHECK(example_connect());
}


extern "C" void app_main(void)
{   
    ++boot_count;
    // Workaround for CVE-2019-15894
    nvs_flash_init();
    if (esp_flash_encryption_enabled())
    {
        esp_flash_write_protect_crypt_cnt();
    }

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }
    connection_scan();

    if (isServerCreated == true){ // inititialization of the sensor reading
    /*Add setup code here*/
        Serial.begin(115200);
        setupmsa311();
    }
}
