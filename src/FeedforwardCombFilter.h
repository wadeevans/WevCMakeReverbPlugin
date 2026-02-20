#pragma once

#include "FractionalDelay.h"

class FeedforwardCombFilter
{
public:
    FeedforwardCombFilter() = default;
    ~FeedforwardCombFilter() = default;

    void prepare(double sampleRate, float maxDelayMs, float feedforwardGain = 0.5f, float delayMs = -1.0f);
    void setFeedforwardGain(float feedforwardGain) { m_feedforwardGain = feedforwardGain; }
    void setDelayTime(float delayMs) { m_delayLine.setDelay(delayMs); }
    float processSample(float input);
    void clear();

private:
    float m_feedforwardGain = 0.5f;
    

    FractionalDelay m_delayLine;

};