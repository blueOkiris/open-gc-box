#include <ArduGcn.hpp>

const int g_gcPin = 7;
ardugcn::GCControllerData g_contData = ardugcn::defaultController();

void setup(void) {
    Serial.begin(9600);
}

void loop(void) {
    if (!sendToConsole(g_gcPin, g_contData)) {
        Serial.println(F("Failed to send controller data!"));
    }
}

