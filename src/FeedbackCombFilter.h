#pragma once

#include "FractionalDelay.h"

class FeedbackCombFilter
{
public:
    FeedbackCombFilter() = default;
    ~FeedbackCombFilter() = default;

    void prepare(double sampleRate, float maxDelayMs, float feedbackGain = 0.7f, float delayMs = -1.0f);
    void setFeedbackGain(float feedbackGain) { m_feedbackGain = feedbackGain; }
    void setDelayTime(float delayMs) { m_delayLine.setDelay(delayMs); }
    float processSample(float input);
    void clear();

private:
    float m_feedbackGain = 0.7f;
    float m_delayOutput = 0.0f;

    FractionalDelay m_delayLine;


};