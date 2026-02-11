#pragma once

#include "FractionalDelay.h"

class VariableAllPass
{
public:
    VariableAllPass() = default;
    ~VariableAllPass() = default;

    void prepare(double sampleRate, float maxDelayMs, float feedbackGain = 0.7f, float delayMs = -1.0f);
    void setFeedbackGain(float feedbackGain) { m_feedbackGain = feedbackGain; }
    void setDelay(float delayMs) { m_delayLine.setDelay(delayMs); }
    float processSample(float input);
    void clear();

private:
    float m_feedbackGain = 0.7f;
    float m_delayOutput = 0.0f;

    FractionalDelay m_delayLine;
};