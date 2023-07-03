#include "battery.h"

batteryType battery::type{batteryType::liFePO4_700mAh};        // initialize static member

const interpolationPoint battery::voltageVsCharge[nmbrBatteryTypes][nmbrInterpolationPoints] = {
    {
        {2.80F, 0},
        {3.00F, 25},
        {3.10F, 50},
        {3.15F, 96},
        {3.25F, 160},
        {3.30F, 200},
        {3.40F, 225},
        {3.60F, 255},
    },
    {
        {2.80F, 0},
        {3.00F, 25},
        {3.10F, 50},
        {3.15F, 100},
        {3.25F, 150},
        {3.30F, 200},
        {3.40F, 225},
        {3.60F, 255},
    },
    {
        {2.80F, 0},
        {3.00F, 25},
        {3.10F, 50},
        {3.15F, 100},
        {3.25F, 150},
        {3.30F, 200},
        {3.40F, 225},
        {3.60F, 255},
    },
    {
        {2.80F, 0},
        {3.00F, 25},
        {3.10F, 50},
        {3.15F, 100},
        {3.25F, 150},
        {3.30F, 200},
        {3.40F, 225},
        {3.60F, 255},
    }};

void battery::run() {
    // TODO : read battery voltage
    // TODO : calculate charge
}

bool battery::isAwake() {
    return false;
}

uint8_t battery::getChargeLevel() {
    return 0;
}

float battery::getVoltage() {
    return 3.2F;
}

uint8_t battery::calculateCharge(float voltage) {
    if (voltage <= voltageVsCharge[static_cast<uint8_t>(type)][0].voltage) {
        return 0;
    }
    if (voltage >= voltageVsCharge[static_cast<uint8_t>(type)][nmbrInterpolationPoints - 1].voltage) {
        return 255;
    }
    for (auto interpolationPointIndex = 0; interpolationPointIndex < nmbrInterpolationPoints - 2; interpolationPointIndex++) {
        if ((voltage >= voltageVsCharge[static_cast<uint8_t>(type)][interpolationPointIndex].voltage) &&
            (voltage <= voltageVsCharge[static_cast<uint8_t>(type)][interpolationPointIndex + 1].voltage)) {
            uint8_t A = voltageVsCharge[static_cast<uint8_t>(type)][interpolationPointIndex].charge;
            uint8_t B = voltageVsCharge[static_cast<uint8_t>(type)][interpolationPointIndex + 1].charge - voltageVsCharge[static_cast<uint8_t>(type)][interpolationPointIndex].charge;
            float C   = voltage - voltageVsCharge[static_cast<uint8_t>(type)][interpolationPointIndex].voltage;
            float D   = voltageVsCharge[static_cast<uint8_t>(type)][interpolationPointIndex + 1].voltage - voltageVsCharge[static_cast<uint8_t>(type)][interpolationPointIndex].voltage;

            return static_cast<uint8_t>(A + B * (C / D));
        }
    }
    return 0;
}

bool battery::checkVoltageVsCharge() {
    for (auto batteryTypeIndex = 1; batteryTypeIndex < nmbrBatteryTypes; batteryTypeIndex++) {
        for (auto interpolationPointIndex = 0; interpolationPointIndex < nmbrInterpolationPoints - 2; interpolationPointIndex++) {
            if (voltageVsCharge[batteryTypeIndex][interpolationPointIndex].voltage >= voltageVsCharge[batteryTypeIndex ][interpolationPointIndex + 1].voltage) {
                return false;
            }
        }
    }
    return true;
}

#ifndef environment_desktop

#include "main.h"

static void MX_ADC_Init(void);
extern ADC_HandleTypeDef hadc;

static void MX_ADC_Init(void) {
    /* USER CODE BEGIN ADC_Init 0 */

    /* USER CODE END ADC_Init 0 */

    /* USER CODE BEGIN ADC_Init 1 */

    /* USER CODE END ADC_Init 1 */

    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
     */
    hadc.Instance                        = ADC;
    hadc.Init.ClockPrescaler             = ADC_CLOCK_SYNC_PCLK_DIV1;
    hadc.Init.Resolution                 = ADC_RESOLUTION_12B;
    hadc.Init.DataAlign                  = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode               = ADC_SCAN_DISABLE;
    hadc.Init.EOCSelection               = ADC_EOC_SINGLE_CONV;
    hadc.Init.LowPowerAutoWait           = DISABLE;
    hadc.Init.LowPowerAutoPowerOff       = ENABLE;
    hadc.Init.ContinuousConvMode         = DISABLE;
    hadc.Init.NbrOfConversion            = 1;
    hadc.Init.DiscontinuousConvMode      = DISABLE;
    hadc.Init.ExternalTrigConv           = ADC_SOFTWARE_START;
    hadc.Init.ExternalTrigConvEdge       = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc.Init.DMAContinuousRequests      = DISABLE;
    hadc.Init.Overrun                    = ADC_OVR_DATA_PRESERVED;
    hadc.Init.SamplingTimeCommon1        = ADC_SAMPLETIME_79CYCLES_5;
    hadc.Init.SamplingTimeCommon2        = ADC_SAMPLETIME_79CYCLES_5;
    hadc.Init.OversamplingMode           = DISABLE;
    hadc.Init.Oversampling.Ratio         = ADC_OVERSAMPLING_RATIO_8;
    hadc.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;
    hadc.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
    hadc.Init.TriggerFrequencyMode       = ADC_TRIGGER_FREQ_HIGH;
    if (HAL_ADC_Init(&hadc) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC_Init 2 */

    /* USER CODE END ADC_Init 2 */
}

void power::measureBatteryLevel() {
    // Now some code to test the ADC conversion..
    HAL_ADCEx_Calibration_Start(&hadc);        // calibrate the ADC after power in

    ADC_ChannelConfTypeDef theAdcConfig;
    theAdcConfig.Channel      = ADC_CHANNEL_VREFINT;
    theAdcConfig.Rank         = ADC_REGULAR_RANK_1;
    theAdcConfig.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc, &theAdcConfig);
    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, 1);
    uint32_t adcRawResult = HAL_ADC_GetValue(&hadc);
    batteryVoltage        = static_cast<float>(__HAL_ADC_CALC_VREFANALOG_VOLTAGE((adcRawResult), ADC_RESOLUTION_12B)) / 1000.0f;
}

#endif