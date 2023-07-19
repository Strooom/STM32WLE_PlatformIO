// #############################################################################
// ### This file is part of the source code for the Moovr CNC Controller     ###
// ### https://github.com/Strooom/Moovr                                      ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################

#include "maincontroller.h"
#include "settingscollection.h"
#include "sensorcollection.h"
// #include "logging.h"

#include "nvs.h"

// #include "applicationevent.h"
// #include "eventbuffer.h"
// #include "lorawan.h"
// #include "measurementcollection.h"

mainState mainController::theMainState{mainState::boot};

// extern eventBuffer<applicationEvent, 16U> applicationEventBuffer;
// extern LoRaWAN loraNetwork;

void mainController::initialize() {
    // if (nonVolatileStorage::isPresent()) {
    //     if (!settingsCollection::isInitialized()) {
    //         settingsCollection::initializeOnce();
    //     }
    // }

    // sensorChannelCollection::discover();
    
    // loraNetwork.initialize();        // LoRaWAN layer + the LoRa radio
}

void mainController::handleEvents() {
    // while (applicationEventBuffer.hasEvents()) {
    //     applicationEvent theEvent = applicationEventBuffer.pop();
    //     logging::snprintf(logging::source::applicationEvents, "Application Event [%u] : %s\n", static_cast<uint8_t>(theEvent), toString(theEvent));
    //     switch (theEvent) {
    //         case applicationEvent::usbConnected:
    //             // MX_USART2_UART_Init();
    //             break;

    //         case applicationEvent::usbRemoved:
    //             // MX_USART2_UART_DeInit();
    //             break;

    //         case applicationEvent::downlinkApplicationPayloadReceived: {
    //             // byteBuffer receivedData;
    //             // loraNetwork.getDownlinkMessage(receivedData);
    //         } break;

    //         case applicationEvent::realTimeClockTick: {
    //             // 1. run all measurements
    //             sensorCollection::runResult theResult = theSensors.run();
    //             if (theResult == sensorCollection::runResult::newMeasurements) {
    //                 // 2. Send them as payload in an UpLink message
    //                 uint8_t tempData[256]{};
    //                 uint32_t tempDataIndex{0};

    //                 tempData[tempDataIndex] = static_cast<uint8_t>(payloadEncodingVersion::mumo_v2_0);        // first byte of payload identifies how the rest should be interpreted
    //                 tempDataIndex++;

    //                 for (uint32_t measurementIndex = 0; measurementIndex < theSensors.actualNumberOfMeasurements; measurementIndex++) {        // for each measurement, store the 9 bytes (type, timestamp, value) in the payload
    //                     tempData[tempDataIndex] = static_cast<uint8_t>(theSensors.latestMeasurements[measurementIndex].type);

    //                     tempData[tempDataIndex + 1] = theSensors.latestMeasurements[measurementIndex].timestamp.asBytes[0];
    //                     tempData[tempDataIndex + 2] = theSensors.latestMeasurements[measurementIndex].timestamp.asBytes[1];
    //                     tempData[tempDataIndex + 3] = theSensors.latestMeasurements[measurementIndex].timestamp.asBytes[2];
    //                     tempData[tempDataIndex + 4] = theSensors.latestMeasurements[measurementIndex].timestamp.asBytes[3];

    //                     tempData[tempDataIndex + 5] = theSensors.latestMeasurements[measurementIndex].value.asBytes[0];
    //                     tempData[tempDataIndex + 6] = theSensors.latestMeasurements[measurementIndex].value.asBytes[1];
    //                     tempData[tempDataIndex + 7] = theSensors.latestMeasurements[measurementIndex].value.asBytes[2];
    //                     tempData[tempDataIndex + 8] = theSensors.latestMeasurements[measurementIndex].value.asBytes[3];

    //                     tempDataIndex += 9;
    //                 }
    //                 // loraNetwork.checkNetwork();
    //                 loraNetwork.sendUplink(0x10, tempData, tempDataIndex);
    //             }

    //             // 2. check if we have enough unsent data to send uplink
    //             //                uint32_t maxUplinkPayloadNow =                     loraNetwork.getMaxApplicationPayloadLength();
    //             //                uint32_t measurementToBeTransmitted =                     theMeasurements.getNmbrToBeTransmitted();
    //             //                if (((measurementToBeTransmitted + 1) * measurement::length) > maxUplinkPayloadNow) {
    //             //                    logging::snprintf(
    //             //                        "[%u] measurement bytes to transmit, [%u] bytes payload capacity\n",
    //             //                        (measurementToBeTransmitted + 1) * measurement::length,
    //             //                        maxUplinkPayloadNow);
    //             //                    if (loraNetwork.isReadyToTransmit()) {
    //             //                        logging::snprintf("LoRaWAN layer ready to transmit\n");
    //             //                        byteBuffer thePayload;        //
    //             //                        thePayload.setFromHexAscii(
    //             //                            "000102030405060708090A0B0C0D0E0F");        // TODO - TEST msg
    //             //                        loraNetwork.sendUplink(thePayload, 0x10);
    //             //                    }
    //             //                } else {
    //             //                    logging::snprintf("Not enough data to transmit\n");
    //             //                }
    //         } break;

    //         default:
    //             break;
    //     }
    // }
}
