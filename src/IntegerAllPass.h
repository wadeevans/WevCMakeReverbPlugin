#pragma once

#include "IntegerDelay.h"

class IntegerAllPass
{
public:
    IntegerAllPass() = default;
    ~IntegerAllPass() = default;

    void prepare(int delayInSamples, float feedbackGain);
    float processSample(float input);
    void clear();

private:
    IntegerDelay m_delayLine;
    float m_delayOutput = 0.0f;
    float m_feedbackGain = 0.7f;
};