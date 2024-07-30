#include <ESP8266WiFi.h>
extern "C" {
    #include <espnow.h>
}

typedef struct struct_message {
    char a[32];
    int b;
    float c;
} struct_message;

struct_message myData;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Char: ");
    Serial.println(myData.a);
    Serial.print("Int: ");
    Serial.println(myData.b);
    Serial.print("Float: ");
    Serial.println(myData.c);
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    
    WiFi.mode(WIFI_STA);
    Serial.println(WiFi.macAddress());
    
    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
