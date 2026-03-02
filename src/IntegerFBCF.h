#pragma once

#include "IntegerDelay.h"
#include "OnePoleFilter.h"

class IntegerFBCF
{
public:
    void prepare(double sampleRate, int delayInSamples, float feedbackGain = 0.7f); 
    void setDampingEnabled(bool dampingEnabled) { m_dampingEnabled = dampingEnabled; }
    void setDampingCutOffFrequency(float frequencyHz) { m_dampingFilter.setCutoffFrequency(frequencyHz); }
    float processSample(float input);
    void clear();


private:
    float m_feedbackGain = 0.7f;
    float m_delayOutput = 0.0f;
    bool m_dampingEnabled = false;
    

    IntegerDelay m_delayLine;
    OnePoleFilter m_dampingFilter;
};