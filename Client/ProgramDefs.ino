#include "includes/program/Programs.h"
#include "includes/program/Actions.h"

#define WATER_TANK_SIZE (20)
#define HEATER_WATT     (500)

void AddPrograms(Programs* programs)
{
    // Load program A.
    programs->Add(0, {
        // Prewash
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new HeatAction(TEMP_OFF),
        new SoapAction(STATE_ON, 1),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 1),

        // Main wash (1)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_MEDIUM),
        new SoapAction(STATE_ON, 2),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 2),

        // Main wash (2)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new HeatAction(TEMP_OFF),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),

        // Centrifugation
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),

        // Beep!
        new BuzzerAction(STATE_ON),
        new DelayAction(1000L),
        new BuzzerAction(STATE_OFF),
    });

    // Load program B.
    programs->Add(1, {
        // Prewash
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_MEDIUM),
        new SoapAction(STATE_ON, 1),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 1),

        // Main wash (1)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_MEDIUM),
        new SoapAction(STATE_ON, 2),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 2),

        // Main wash (2)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new HeatAction(TEMP_OFF),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),

        // Centrifugation
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),

        // Beep!
        new BuzzerAction(STATE_ON),
        new DelayAction(1000L),
        new BuzzerAction(STATE_OFF),
    });

    // Load program C.
    programs->Add(2, {
        // Prewash
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_MEDIUM),
        new SoapAction(STATE_ON, 1),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 1),

        // Main wash (1)
        new RequestWaterAction(WATER_TANK_SIZE),
        new FillWaterAction(WL_FULL),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_HOT),
        new SoapAction(STATE_ON, 2),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 2),

        // Main wash (2)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new HeatAction(TEMP_OFF),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),

        // Centrifugation
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),

        // Beep!
        new BuzzerAction(STATE_ON),
        new DelayAction(1000L),
        new BuzzerAction(STATE_OFF),
    });
}
