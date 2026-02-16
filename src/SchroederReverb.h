#pragma once

#include "FeedbackCombFilter.h"
#include "FixedAllPass.h"

class SchroederReverb
{
public:
    SchroederReverb() = default;
    ~SchroederReverb() = default;



    void prepare(double sampleRate);
    float processSample(float input);
    void setDampingEnabled(bool dampingEnabled);
    void setDampingCutOffFrequency(float dampingCutoffFrequency);
    void clear();

private:

    FeedbackCombFilter fbcf1;
    FeedbackCombFilter fbcf2;
    FeedbackCombFilter fbcf3;
    FeedbackCombFilter fbcf4;

    FixedAllPass allpass1;
    FixedAllPass allpass2;

};
