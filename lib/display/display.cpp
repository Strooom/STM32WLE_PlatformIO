// ######################################################################################
// ### MuMo node : https://github.com/Strooom/MuMo-v2-Node-SW                         ###
// ### Author : Pascal Roobrouck - https://github.com/Strooom                         ###
// ### License : CC 4.0 BY-NC-SA - https://creativecommons.org/licenses/by-nc-sa/4.0/ ###
// ######################################################################################

#include "display.h"

// extern peripheralRegister PORTA_BSRR;
// extern peripheralRegister PORTB_BSRR;
// extern peripheralRegister PORTC_BSRR;
// extern peripheralRegister PORTB_IDR;

// Initialize the static variables

displayRotation display::rotation{displayRotation::rotation0};
displayMirroring display::mirroring{displayMirroring::none};
uint8_t display::displayBuffer[display::bufferSize]{0};

void display::setPixel(uint32_t x, uint32_t y) {
    uint32_t byteOffset       = getByteOffset(x, y);
    uint32_t bitOffset        = getBitOffset(x);
    displayBuffer[byteOffset] = displayBuffer[byteOffset] | (1 << bitOffset);
}

void display::clearPixel(uint32_t x, uint32_t y) {
    uint32_t byteOffset       = getByteOffset(x, y);
    uint32_t bitOffset        = getBitOffset(x);
    displayBuffer[byteOffset] = displayBuffer[byteOffset] & ~(1 << bitOffset);
}

void display::changePixel(uint32_t x, uint32_t y, bool onOff) {
    if (!inBounds(x, y)) {        // NOTE : as our display is 200 x 200, we could already perform this check earlier (eg in graphics::drawPixel), and avoid executing some code in case the pixel is out of bounds
        return;
    }
    rotateAndMirrorCoordinates(x, y);
    if (onOff) {
        setPixel(x, y);
    } else {
        clearPixel(x, y);
    }
}

bool display::inBounds(uint32_t c) {
    return (c >= 0 && c < display::width);
}

bool display::inBounds(uint32_t x, uint32_t y) {
    return (inBounds(x) && inBounds(y));
}

void display::swapCoordinates(uint32_t& c1, uint32_t& c2) {
    uint32_t temp = c1;
    c1            = c2;
    c2            = temp;
}

void display::mirrorCoordinate(uint32_t& c, uint32_t maxC) {
    c = (maxC - 1) - c;
}

uint32_t display::getByteOffset(uint32_t x, uint32_t y) {
    return ((y * 25) + (x / 8));
}

uint32_t display::getBitOffset(uint32_t x) {
    return (x % 8);
}

void display::rotateAndMirrorCoordinates(uint32_t& x, uint32_t& y) {
    switch (display::rotation) {
        case displayRotation::rotation0:
            break;
        case displayRotation::rotation90:
            swapCoordinates(x, y);
            mirrorCoordinate(y, display::height);
            break;
        case displayRotation::rotation180:
            mirrorCoordinate(x, display::width);
            mirrorCoordinate(y, display::height);
            break;
        case displayRotation::rotation270:
            swapCoordinates(x, y);
            mirrorCoordinate(x, display::width);
            break;
    }

    switch (display::mirroring) {
        case displayMirroring::none:
            break;
        case displayMirroring::horizontal:
            mirrorCoordinate(x, display::width);
            break;
        case displayMirroring::vertical:
            mirrorCoordinate(y, display::height);
            break;
        case displayMirroring::both:
            mirrorCoordinate(x, display::width);
            mirrorCoordinate(y, display::height);
            break;
    }
}

#ifndef environment_desktop
#include "main.h"
extern SPI_HandleTypeDef hspi2;

void display::reset() {
    HAL_GPIO_WritePin(GPIOA, displayReset_Pin, GPIO_PIN_RESET);
    // PORTA_BSRR.write(1 << 0);               // reset = LOW
    HAL_Delay(10U);        // datasheet, section 4.2
    HAL_GPIO_WritePin(GPIOA, displayReset_Pin, GPIO_PIN_SET);
    // PORTA_BSRR.write(1 << (0 + 16));        // reset = HIGH
    HAL_Delay(10U);        //
    writeCommand(SSD1681Commands::SW_RESET, nullptr, 0);
}

void display::setDataOrCommand(bool isData) const {
    if (isData) {
        HAL_GPIO_WritePin(GPIOB, displayDataCommand_Pin, GPIO_PIN_SET);
        // PORTB_BSRR.write(1 << 14);               // data = HIGH
    } else {        //
        HAL_GPIO_WritePin(GPIOB, displayDataCommand_Pin, GPIO_PIN_RESET);
        // PORTB_BSRR.write(1 << (14 + 16));        // command = LOW
    }
}

void display::selectChip(bool active) {
    if (active) {
        HAL_GPIO_WritePin(GPIOB, displayChipSelect_Pin, GPIO_PIN_RESET);
        // PORTB_BSRR.write(1 << (5 + 16));        // active = LOW
    } else {        //
        HAL_GPIO_WritePin(GPIOB, displayChipSelect_Pin, GPIO_PIN_SET);
        // PORTB_BSRR.write(1 << 5);               // release = HIGH
    }
}

bool display::isBusy() {
    return (GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOB, displayBusy_Pin));
    // return (PORTB_IDR.readBit(10));
}

void display::write(uint8_t* data, uint32_t length) {
    selectChip(true);
    HAL_SPI_Transmit(&hspi2, data, length, 1000);        // TODO : get the HAL timeout stuff right
    selectChip(false);
}

void display::write(uint8_t data) {
    write(&data, 1);
}

void display::writeData(uint8_t* data, uint32_t length) {
    setDataOrCommand(true);
    write(data, length);
}

void display::writeData(uint8_t data) {
    writeData(&data, 1);
}

void display::writeCommand(SSD1681Commands theCommand, uint8_t* theData, uint32_t dataLength) {
    setChipSelect(true);
    setDataOrCommand(false);
    uint8_t commandAsByte = static_cast<uint8_t>(theCommand);
    HAL_SPI_Transmit(&hspi2, &commandAsByte, 1U, 1U);
    if (dataLength > 0) {
        setDataOrCommand(true);
        HAL_SPI_Transmit(&hspi2, theData, dataLength, 1U);
    }
    setChipSelect(false);
}

void display::waitWhileBusy() {
    // TODO : this is potentially and endless loop -> add a timeout
    while (isBusy()) {
        asm("NOP");
    }
}

void display::wakeUp() {
    reset();
    waitWhileBusy();
}

void display::initialize() {
    uint8_t commandData[4]{0};

    commandData[0] = 0x7C;
    commandData[1] = 0x00;
    commandData[2] = 0x00;
    writeCommand(SSD1681Commands::DRIVER_OUTPUT_CONTROL, commandData, 3);

    commandData[0] = 0x01;
    writeCommand(SSD1681Commands::DATA_ENTRY_MODE_SETTING, commandData, 1);

    commandData[0] = 0x00;
    commandData[1] = 0x18;
    writeCommand(SSD1681Commands::SET_RAM_X_ADDRESS_START_END_POSITION, commandData, 2);

    commandData[0] = 0xC7;
    commandData[1] = 0x00;
    commandData[2] = 0x00;
    commandData[3] = 0x00;
    writeCommand(SSD1681Commands::SET_RAM_Y_ADDRESS_START_END_POSITION, commandData, 4);

    // TODO : some more initialization code required here.. need to study the datasheet first
}

void display::goSleep() {
    uint8_t commandData[1]{0x01};
    writeCommand(SSD1681Commands::DEEP_SLEEP_MODE, commandData, 1);
}

void display::set()
// EPD* epd,
// const unsigned char* image_buffer,
// int x,
// int y,
// int image_width,
// int image_height) {
// int x_end;
// int y_end;
{
    // if (
    //     image_buffer == NULL ||
    //     x < 0 || image_width < 0 ||
    //     y < 0 || image_height < 0) {
    //     return;
    // }
    // /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    // x &= 0xF8;
    // image_width &= 0xF8;
    // if (x + image_width >= epd->width) {
    //     x_end = epd->width - 1;
    // } else {
    //     x_end = x + image_width - 1;
    // }
    // if (y + image_height >= epd->height) {
    //     y_end = epd->height - 1;
    // } else {
    //     y_end = y + image_height - 1;
    // }
    // EPD_SetMemoryArea(epd, x, y, x_end, y_end);
    // EPD_SetMemoryPointer(epd, x, y);
    // EPD_SendCommand(epd, WRITE_RAM);
    // /* send the image data */
    // for (int j = 0; j < y_end - y + 1; j++) {
    //     for (int i = 0; i < (x_end - x + 1) / 8; i++) {
    //         EPD_SendData(epd, image_buffer[i + j * (image_width / 8)]);
    //     }
    // }
}

void display::clear() {
    // EPD_SetMemoryArea(epd, 0, 0, epd->width - 1, epd->height - 1);
    // EPD_SetMemoryPointer(epd, 0, 0);
    // EPD_SendCommand(epd, WRITE_RAM);
    // /* send the color data */
    // for (int i = 0; i < epd->width / 8 * epd->height; i++) {
    //     EPD_SendData(epd, color);
    // }
}

void display::show() {
    uint8_t commandData[1]{0xC4};
    writeCommand(SSD1681Commands::DISPLAY_UPDATE_CONTROL_2, commandData, 1);

    writeCommand(SSD1681Commands::MASTER_ACTIVATION, nullptr, 0);
    writeCommand(SSD1681Commands::TERMINATE_FRAME_READ_WRITE, nullptr, 0);
}

// static void EPD_SetMemoryArea(EPD* epd, int x_start, int y_start, int x_end, int y_end) {
//     EPD_SendCommand(epd, SET_RAM_X_ADDRESS_START_END_POSITION);
//     /* x point must be the multiple of 8 or the last 3 bits will be ignored */
//     EPD_SendData(epd, (x_start >> 3) & 0xFF);
//     EPD_SendData(epd, (x_end >> 3) & 0xFF);
//     EPD_SendCommand(epd, SET_RAM_Y_ADDRESS_START_END_POSITION);
//     EPD_SendData(epd, y_start & 0xFF);
//     EPD_SendData(epd, (y_start >> 8) & 0xFF);
//     EPD_SendData(epd, y_end & 0xFF);
//     EPD_SendData(epd, (y_end >> 8) & 0xFF);
// }

// /**
//  *  @brief: private function to specify the start point for data R/W
//  */
// static void EPD_SetMemoryPointer(EPD* epd, int x, int y) {
//     EPD_SendCommand(epd, SET_RAM_X_ADDRESS_COUNTER);
//     /* x point must be the multiple of 8 or the last 3 bits will be ignored */
//     EPD_SendData(epd, (x >> 3) & 0xFF);
//     EPD_SendCommand(epd, SET_RAM_Y_ADDRESS_COUNTER);
//     EPD_SendData(epd, y & 0xFF);
//     EPD_SendData(epd, (y >> 8) & 0xFF);
//     EPD_WaitUntilIdle(epd);
// }

#else

// TODO : a desktop console version goes here

void display::reset() {}
bool display::isBusy() { return false; }
void display::setDataOrCommand(bool isData) {}
void display::selectChip(bool active) {}

void display::write(uint8_t* data, uint32_t length) {}
void display::write(uint8_t data) {}
void display::writeData(uint8_t data) {}
void display::writeData(uint8_t* data, uint32_t length) {}
void display::writeCommand(SSD1681Commands theCommand, uint8_t* theData, uint32_t dataLength) {}

void display::wakeUp() {}
void display::initialize() {}

#endif