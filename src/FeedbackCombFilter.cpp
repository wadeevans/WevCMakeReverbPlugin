/// Feedback Comb Filter
/// Output is wet signal only (taken after delay line).
/// For reverb and modulation effects: mix with dry signal.

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

    m_dampingFilter.prepare(sampleRate);
    m_dampingFilter.setCutoffFrequency(10000.0f);

    clear();
}

float FeedbackCombFilter::processSample(float input)
{
    // y(n) = x(n) + g * y(n-M)
    float dampedOutput;

    if (m_dampingEnabled)
        dampedOutput = m_dampingFilter.processSample(m_delayOutput);
    else
        dampedOutput = m_delayOutput;  // TRUE BYPASS

    float output = input + (dampedOutput * m_feedbackGain);
    m_delayOutput = m_delayLine.processSample(output);

    return m_delayOutput;
}


void FeedbackCombFilter::clear()
{
    m_delayLine.clear();
    m_dampingFilter.clear();
    m_delayOutput = 0.0f; // Also reset the output
}


