#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "harnass/ArduinoWrapper.h"
#include "mock/MCentipedeShield.h"

#include "HardwareControl.ino"
#include "Actions.ino"
#include "StatusIndicator.ino"
#include "Controls.ino"
#include "Heater.ino"
#include "Motor.ino"
#include "Water.ino"

using ::testing::NiceMock;
using ::testing::AllOf;
using ::testing::Test;
using ::testing::Ge;
using ::testing::Le;
using ::testing::_;

class ActionTest : public ::testing::Test
{
protected:
    NiceMock<MCentipedeShield> centipede;

    HardwareControl* control;
    IAction* action;

    ActionTest()
    {
        // These are all of the Initialize calls on the hardware components.
        EXPECT_CALL(centipede, DigitalWrite(_, _)).Times(7 + 3 + 1 + 3 + 2);

        control = new HardwareControl(&centipede, new StatusIndicator(), new Controls(), new Heater(), new Motor(), new Water());
    }

    virtual ~ActionTest()
    {
        delete action;
    }

    void SetAction(IAction* action)
    {
        action->SetHardwareControl(control);

        this->action = action;
    }
};

TEST(DelayActionTest, TestDelayTakesTheCorrectTimeToBeDone)
{
    unsigned long runTime = 1000L;
    unsigned long margin = 5L;

    DelayAction action = DelayAction(runTime);

    unsigned long start = millis();

    // Start the action.
    action.Handle();

    while (!action.IsDone());

    // Measure the time that it took to run the delay action.
    unsigned long time = millis() - start;

    // Because of small deviations in times between test runs, we add a margin to
    // the original runTime to accomodate for these deviations.
    EXPECT_THAT(time, AllOf(Ge(runTime - margin), Le(runTime + margin)));
}

TEST_F(ActionTest, TestBuzzerCorrectlyGetsSet)
{
    EXPECT_CALL(centipede, DigitalWrite(OUTPUT_BUZZER, HIGH)).Times(1);
    EXPECT_CALL(centipede, DigitalWrite(OUTPUT_BUZZER, LOW)).Times(1);

    SetAction(new BuzzerAction(STATE_ON));
    action->Handle();

    SetAction(new BuzzerAction(STATE_OFF));
    action->Handle();
}

TEST_F(ActionTest, TestSoap1CorrectlyGetsSet)
{
    EXPECT_CALL(centipede, DigitalWrite(OUTPUT_SOAP_1, HIGH)).Times(1);
    EXPECT_CALL(centipede, DigitalWrite(OUTPUT_SOAP_1, LOW)).Times(1);

    SetAction(new SoapAction(STATE_ON, 1));
    action->Handle();

    SetAction(new SoapAction(STATE_OFF, 1));
    action->Handle();
}

TEST_F(ActionTest, TestSoap2CorrectlyGetsSet)
{
    EXPECT_CALL(centipede, DigitalWrite(_, _)).Times((2 + 3 + 3) * 2);

    SetAction(new SoapAction(STATE_ON, 2));
    action->Handle();

    SetAction(new SoapAction(STATE_OFF, 2));
    action->Handle();
}
