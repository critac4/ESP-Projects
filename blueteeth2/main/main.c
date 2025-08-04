#include <stdio.h>
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"

/*
Flow of BT use in ESP:
    init and enable the controller (handles the hardware and low level)
    init and enable bluedroid (handles the bluetooth stack (APIs for connection and discovery) and profiles (audio/fileshare etc))

*/


esp_bt_controller_status_t init_and_en_btController(void) 
{
    // initialize bt controller with default configuration
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_err_t init_ret = esp_bt_controller_init(&bt_cfg);
    if (init_ret != ESP_OK) {
        printf("Bluetooth controller initialization failed: %s\n", esp_err_to_name(init_ret));
        return ESP_BT_CONTROLLER_STATUS_IDLE;
    }

    // enable bt controller
    esp_err_t enable_ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
    if (enable_ret != ESP_OK) {
        printf("Bluetooth controller enable failed: %s\n", esp_err_to_name(enable_ret));
        return ESP_BT_CONTROLLER_STATUS_IDLE;
    }

    // return the current status of the bt controller
    return esp_bt_controller_get_status();
}




esp_bluedroid_status_t init_and_en_bluedroid(void) 
{
    // initialize bluedroid with default configuration
    esp_bluedroid_config_t bd_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();
    esp_err_t init_ret = esp_bluedroid_init_with_cfg(&bd_cfg);
    if (init_ret != ESP_OK) {
        printf("Bluedroid initialization failed: %s\n", esp_err_to_name(init_ret));
        return ESP_BLUEDROID_STATUS_UNINITIALIZED;
    }

    // enable bluedroid
    esp_err_t enable_ret = esp_bluedroid_enable();
    if (enable_ret != ESP_OK) {
        printf("Bluedroid enable failed: %s\n", esp_err_to_name(enable_ret));
        return ESP_BLUEDROID_STATUS_UNINITIALIZED;
    }

    // return the current status of bluedroid
    return esp_bluedroid_get_status();
}


esp_bt_gap_cb_t bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_BT_GAP_DISC_RES_EVT: {
        // Device discovery result event
        char bda_str[18];
        bda2str(param->disc_res.bda, bda_str, sizeof(bda_str));
        printf("Device found: %s\n", bda_str);
        break;
    }
    case ESP_BT_GAP_DISC_STATE_CHANGED_EVT: {
        // Discovery state changed event
        printf("Discovery state changed.\n");
        break;
    }
    default:
        printf("Unhandled GAP event: %d\n", event);
        break;
    }
    
}

void app_main(void)
{

    // init NVS flash
    //ESP_ERROR_CHECK(nvs_flash_init()); //is eqvt to below
    esp_err_t err = nvs_flash_init();
    if (err != ESP_OK) {
        printf("NVS Init failed: %s\n", esp_err_to_name(err));
        abort();  // or return;
    }

    
    //set initial bluetooth config as default
    // esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    
    
    // //initalize the bluetooth
    
    // //esp_err_t ret = esp_bt_controller_init(&bt_cfg);
    // //start the bluetooth init:

    // //has a single param, takes in the addr of the bluetooth config struct.
    // esp_err_t initRet1 =  esp_bt_controller_init(&bt_cfg); 

    // //check if the bluetooth init was successful
    // if (initRet1 != ESP_OK) 
    // {
    //     printf("Bluetooth controller initialization failed: \n %s \n", esp_err_to_name(initRet1));
    //     return;
    // }
    // // to use esp_bt_controller_get_status() fucntion, replace the if statement at line 21 with line below
    // //if (esp_bt_controller_get_status() != ESP_BT_CONTROLLER_STATUS_INITED) {


    // //enable the bluetooth controller
    // esp_err_t enRet1 = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
    // if (enRet1 != ESP_OK) 
    // {
    //     printf("Bluetooth controller enable failed: \n %s \n", esp_err_to_name(enRet1));
    //     return;
    // }

    
    // esp_bt_controller_status_t status = esp_bt_controller_get_status();
    // printf("Bluetooth controller status: %d\n", status); // prints the status code    
    // if (status == ESP_BT_CONTROLLER_STATUS_ENABLED) {
    //     printf("Bluetooth controller is enabled.\n");
    // } else if (status == ESP_BT_CONTROLLER_STATUS_INITED) {
    //     printf("Bluetooth controller is initialized but not enabled.\n");
    // } else {
    //     printf("Bluetooth controller is in an unknown state.\n");
    // }
    printf("BT controller init and en status: %s/n", init_and_en_btController());

    //bluedroid init and enable

    // esp_bluedroid_config_t bd_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();

    // esp_err_t initRet2 = esp_bluedriod_init_with_cfg(&bd_cfg);

    // esp_err_t enRet2 = esp_bluedroid_enable();

    // esp_bluedroid_status_t bd_status = esp_bluedroid_get_status();
    // printf("Bluedroid status: %d\n", bd_status); // prints the status code
    // if (bd_status == ESP_BLUEDROID_STATUS_ENABLED) {
    //     printf("Bluedroid is enabled.\n");
    // } else if (bd_status == ESP_BLUEDROID_STATUS_INITED) {
    //     printf("Bluedroid is initialized but not enabled.\n");
    // } else {
    //     printf("Bluedroid is in an unknown state.\n");
    // }
    printf("Bluedroid init and en status: %s/n", init_and_en_bluedroid());

    //to start scanning for devices
    // resgiter the callback function
    //set the device name
    //set the scan mode
    //initliaze GAP:
    //  register the callback whose purpose is to define what to do when the api finds devices.
    //     the api raises 'events' that are processed by the callback fucntion, which does all the word, you can connect, read the type of device.
    
    //  set the device name
    //  set the scan mode  
    //  start scanning, in general mode esp_bt_gap_start_discovery
    esp_bt_gap_register_callback(bt_gap_cb);

    esp_bt_dev_set_device_name("Critac_ESP_BT");

    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

    esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
    printf("Bluetooth GAP started scanning for devices.\n");

}
