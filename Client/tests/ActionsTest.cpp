#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "harnass/ArduinoWrapper.h"

#include "Actions.ino"

using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;

TEST(ActionsTest, TestDelayTakesTheCorrectTimeToBeDone)
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

TEST(ActionsTest, TestBuzzerCorrectlyGetsSet)
{
    BuzzerAction action = BuzzerAction(STATE_ON);
}
