// FeedforwadrCombFilter.cpp
// Created by CWE on 2024-06-17.

#include "FeedforwardCombFilter.h"

void FeedforwardCombFilter::prepare(double sampleRate, float maxDelayMs, float feedforwardGain, float delayMs)
{
    m_feedforwardGain = feedforwardGain;

    float smoothingMs = 0.0f;
    m_delayLine.prepare(sampleRate, maxDelayMs, smoothingMs);

    // If delayMs not specified, use maxDelayMs
    float actualDelay = (delayMs < 0.0f) ? maxDelayMs : delayMs;
    m_delayLine.setDelay(actualDelay);

    clear();
}

float FeedforwardCombFilter::processSample(float input)
{
    float delayedSample = m_delayLine.processSample(input);
    return input + (m_feedforwardGain * delayedSample);
}

void FeedforwardCombFilter::clear()
{
    m_delayLine.clear();
    
}