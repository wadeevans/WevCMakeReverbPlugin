// SchroederReverb.cpp
// Simple Schroeder Reverb class
// created by cwe 16/02/2026

#include "SchroederReverb.h"

void SchroederReverb::prepare(double sampleRate)
{
    inAllpass1.prepare(sampleRate, 7.0f, 0.7f);
    inAllpass2.prepare(sampleRate, 3.0f, 0.7f);
    inAllpass3.prepare(sampleRate, 1.0f, 0.7f);


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
    float diffused = inAllpass1.processSample(input);
    diffused = inAllpass2.processSample(diffused);
    diffused = inAllpass3.processSample(diffused);

    // array would be useful here for loop with sum
    float fbcf1return = fbcf1.processSample(diffused);
    float fbcf2return = fbcf2.processSample(diffused);
    float fbcf3return = fbcf3.processSample(diffused);
    float fbcf4return = fbcf4.processSample(diffused);

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
    inAllpass1.clear();
    inAllpass2.clear();
    inAllpass3.clear();

    fbcf1.clear();
    fbcf2.clear();
    fbcf3.clear();
    fbcf4.clear();

    allpass1.clear();
    allpass2.clear();
}