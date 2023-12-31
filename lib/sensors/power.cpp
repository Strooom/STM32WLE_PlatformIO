#include "power.h"

bool power::usbPower{false};

#ifndef environment_desktop

#include "main.h"

extern ADC_HandleTypeDef hadc;

bool power::hasUsbPower() {
    return (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, usbPowerPresent_Pin));
}

bool power::isUsbConnected() {
    bool newUsbPower = (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, usbPowerPresent_Pin));
    if (newUsbPower && !usbPower) {
        usbPower = true;
        return true;
    } else {
        return false;
    }
}

bool power::isUsbRemoved() {
    bool newUsbPower = (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, usbPowerPresent_Pin));
    if (!newUsbPower && usbPower) {
        usbPower = false;
        return true;
    } else {
        return false;
    }
}

#else

bool power::hasUsbPower() {
    return false;
}

bool power::isUsbConnected() {
    return false;
}

bool power::isUsbRemoved() {
    return false;
}

#endif
