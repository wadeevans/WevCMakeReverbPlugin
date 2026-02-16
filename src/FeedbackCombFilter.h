#pragma once

#include "FractionalDelay.h"
#include "OnePoleFilter.h"

class FeedbackCombFilter
{
public:
    FeedbackCombFilter() = default;
    ~FeedbackCombFilter() = default;

    void prepare(double sampleRate, float maxDelayMs, float feedbackGain = 0.7f, float delayMs = -1.0f);
    void setFeedbackGain(float feedbackGain) { m_feedbackGain = feedbackGain; }
    void setDelayTime(float delayMs) { m_delayLine.setDelay(delayMs); }
    void setDampingEnabled(bool dampingEnabled) { m_dampingEnabled = dampingEnabled; }
    void setDampingCutOffFrequency(float frequencyHz) { m_dampingFilter.setCutoffFrequency(frequencyHz); }
    float processSample(float input);
    void clear();

private:
    float m_feedbackGain = 0.7f;
    float m_delayOutput = 0.0f;
    bool m_dampingEnabled = false;
    // float m_sampleRate = 44100.0;

    FractionalDelay m_delayLine;
    OnePoleFilter m_dampingFilter;


};