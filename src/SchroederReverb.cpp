// SchroederReverb.cpp
// Simple Schroeder Reverb class
// created by cwe 16/02/2026

#include "SchroederReverb.h"

void SchroederReverb::prepare(double sampleRate)
{
    float inAllPassLengths[3] = { 7.0f, 3.0f, 1.0f };
    float inAllPassGains[3] = { 0.7f, 0.7f, 0.7f };

    for (size_t i = 0; i < m_inAllPasses.size(); i++)
    {
        m_inAllPasses[i].prepare(sampleRate, inAllPassLengths[i], inAllPassGains[i]);
    }

    float fbcfLengths[4] = { 37.0f, 41.0f, 43.0f, 47.0f };
    float fbcfGains[4] = { 0.84f, 0.82f, 0.80f, 0.78f };

    for (size_t i = 0; i < m_fbcfs.size(); i++)
    {
        m_fbcfs[i].prepare(sampleRate, fbcfLengths[i], fbcfGains[i]); // set up array of floats to replace feedbackGains
    }


    float outAllPassLengths[2] = { 5.0f, 1.70f };
    float outAllPassGains[2] = { 0.7f, 0.7f };

    for (size_t i = 0; i < m_outAllPasses.size(); i++)
    {
        m_outAllPasses[i].prepare(sampleRate, outAllPassLengths[i], outAllPassGains[i]);
    }

}

float SchroederReverb::processSample(float input)
{
    float diffused = m_inAllPasses[0].processSample(input);
    diffused = m_inAllPasses[1].processSample(diffused);
    diffused = m_inAllPasses[2].processSample(diffused);

    // array would be useful here for loop with sum
    float output = 0.0f;
    for (auto& fbcf : m_fbcfs)
    {
        output += fbcf.processSample(diffused);
    }

    output /= static_cast<float>(NUM_COMBS);

    // output = m_outAllPasses[0].processSample(output);

    // output = m_outAllPasses[1].processSample(output);

    return output;
}

void SchroederReverb::setDampingEnabled(bool dampingEnabled)
{
    for (auto& fbcf : m_fbcfs)
    {
        fbcf.setDampingEnabled(dampingEnabled);
    }
}

void SchroederReverb::setDampingCutOffFrequency(float dampingCutoffFrequency)
{
    for (auto& fbcf : m_fbcfs)
    {
        fbcf.setDampingCutOffFrequency(dampingCutoffFrequency);
    }
}

void SchroederReverb::setPreDelayEnabled(bool preDelayEnabled)
{
    OutputTap tap = preDelayEnabled ? OutputTap::PreDelay : OutputTap::PostDelay;

    for (auto& fbcf : m_fbcfs)
    {
        fbcf.setOutputTap(tap);
    }
}

void SchroederReverb::clear()
{
    for (auto& inAllPass : m_inAllPasses)
    {
        inAllPass.clear();
    }

    for (auto& fbcf : m_fbcfs)
    {
        fbcf.clear();
    }

    for (auto& outAllPass : m_outAllPasses)
    {
        outAllPass.clear();
    }
}