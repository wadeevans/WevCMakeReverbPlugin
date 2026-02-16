// SchroederReverb.cpp
// Simple Schroeder Reverb class
// created by cwe 16/02/2026

#include "SchroederReverb.h"

void SchroederReverb::prepare(double sampleRate)
{
    fbcf1.prepare(sampleRate, 37.0f, 0.8f);
    fbcf2.prepare(sampleRate, 41.0f, 0.8f);
    fbcf3.prepare(sampleRate, 43.0f, 0.8f);
    fbcf4.prepare(sampleRate, 47.0f, 0.8f);

    //// Test: Dark damping at 2kHz
    //fbcf1.setDampingCutOffFrequency(2000.0f);
    //fbcf2.setDampingCutOffFrequency(2000.0f);
    //fbcf3.setDampingCutOffFrequency(2000.0f);
    //fbcf4.setDampingCutOffFrequency(2000.0f);

    allpass1.prepare(sampleRate, 5.0f, 0.7f);
    allpass2.prepare(sampleRate, 1.70f, 0.7f);
}

float SchroederReverb::processSample(float input)
{
    // array would be useful here for loop with sum
    float fbcf1return = fbcf1.processSample(input);
    float fbcf2return = fbcf2.processSample(input);
    float fbcf3return = fbcf3.processSample(input);
    float fbcf4return = fbcf4.processSample(input);

    float firstAllpassInput = fbcf1return + fbcf2return + fbcf3return + fbcf4return;

    float secondAllPassInput = allpass1.processSample(firstAllpassInput);

    float output = allpass2.processSample(secondAllPassInput);

    return output;
}

void SchroederReverb::setDampingEnabled(bool dampingEnabled)
{
    fbcf1.setDampingEnabled(dampingEnabled);
    fbcf2.setDampingEnabled(dampingEnabled);
    fbcf3.setDampingEnabled(dampingEnabled);
    fbcf4.setDampingEnabled(dampingEnabled);
}

void SchroederReverb::setDampingCutOffFrequency(float dampingCutoffFrequency)
{
    fbcf1.setDampingCutOffFrequency(dampingCutoffFrequency);
    fbcf2.setDampingCutOffFrequency(dampingCutoffFrequency);
    fbcf3.setDampingCutOffFrequency(dampingCutoffFrequency);
    fbcf4.setDampingCutOffFrequency(dampingCutoffFrequency);
}

void SchroederReverb::clear()
{
    fbcf1.clear();
    fbcf2.clear();
    fbcf3.clear();
    fbcf4.clear();

    allpass1.clear();
    allpass2.clear();
}