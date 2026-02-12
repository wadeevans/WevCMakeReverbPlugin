// FeedbackCombFilter
// created 

#include "FeedbackCombFilter.h"

void FeedbackCombFilter::prepare(double sampleRate, float maxDelayMs, float feedbackGain, float delayMs)
{
    m_feedbackGain = feedbackGain;
    // float smoothingMs = maxDelayMs * 0.05f;
    float smoothingMs = 0.0f;
    m_delayLine.prepare(sampleRate, maxDelayMs, smoothingMs);

    // If delayMs not specified, use maxDelayMs
    float actualDelay = (delayMs < 0.0f) ? maxDelayMs : delayMs;
    m_delayLine.setDelay(actualDelay);

    clear();
}

float FeedbackCombFilter::processSample(float input)
{
    // y(n) = x(n) + g * y(n-M)

    float output = input + (m_delayOutput * m_feedbackGain);
    m_delayOutput = m_delayLine.processSample(output);

    return output;
}


void FeedbackCombFilter::clear()
{
    m_delayLine.clear();
    m_delayOutput = 0.0f; // Also reset the output
}


