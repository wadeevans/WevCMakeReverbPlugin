#pragma once

#include "FractionalDelay.h"

class FixedAllPass
{
public:
    FixedAllPass() = default;
    ~FixedAllPass() = default;

    void prepare(double sampleRate, float delayMs, float feedbackGain);
    float processSample(float input);
    void clear();

private:
    float m_feedbackGain = 0.7f;
    float m_delayOutput = 0.0f;

    FractionalDelay m_delayLine;
};