// JCReverb.cpp
// Created by CWE on 05/03/2026

#include "JCReverb.h"

void JCReverb::prepare(double sampleRate)
{
    // Placeholder for any initialization code needed for the reverb
    int inAllPassLengths[3] = { 225, 341, 441 };
    float inAllPassGains[3] = { 0.7f, 0.7f, 0.7f };

    for (size_t i = 0; i < m_inAllPasses.size(); i++)
    {
        m_inAllPasses[i].prepare(inAllPassLengths[i], inAllPassGains[i]);
    }


    int fbcfLengths[4] = { 1116, 1356, 1422, 1617 };

    for (size_t i = 0; i < m_fbcfs.size(); i++)
    {
        m_fbcfs[i].prepare(sampleRate, fbcfLengths[i], 0.9f); // set up array of floats to replace feedbackGains
    }

    int outAllPassLengths[2] = { 221, 73 };
    float outAllPassGains[2] = { 0.7f, 0.7f };

    for (size_t i = 0; i < m_outAllPasses.size(); i++)
    {
        m_outAllPasses[i].prepare(outAllPassLengths[i], outAllPassGains[i]);
    }  
}


float JCReverb::processSample(float input)
{
    // Placeholder for reverb processing algorithm

    float diffused = m_inAllPasses[0].processSample(input);
    diffused = m_inAllPasses[1].processSample(diffused);
    diffused = m_inAllPasses[2].processSample(diffused);

    // array would be useful here for loop with sum
    float fbcf0return = m_fbcfs[0].processSample(diffused);
    float fbcf1return = m_fbcfs[1].processSample(diffused);
    float fbcf2return = m_fbcfs[2].processSample(diffused);
    float fbcf3return = m_fbcfs[3].processSample(diffused);

    float output = (fbcf0return + fbcf1return + fbcf2return + fbcf3return) / static_cast<float>(NUM_COMBS);

    // output = m_outAllPasses[0].processSample(output);
    // output = m_outAllPasses[1].processSample(output);

    return output;
}

void JCReverb::setDampingEnabled(bool dampingEnabled)
{
    // Placeholder for enabling/disabling damping in the reverb
    for (auto& fbcf : m_fbcfs)
    {
        fbcf.setDampingEnabled(dampingEnabled);
    }
}

void JCReverb::setDampingCutOffFrequency(float dampingCutoffFrequency)
{
    // Placeholder for setting the damping cutoff frequency in the reverb
    for (auto& fbcf : m_fbcfs)
    {
        fbcf.setDampingCutOffFrequency(dampingCutoffFrequency);
    }
}

void JCReverb::setPreDelayEnabled(bool preDelayEnabled)
{
    OutputTap tap = preDelayEnabled ? OutputTap::PreDelay : OutputTap::PostDelay;

    for (auto& fbcf : m_fbcfs)
    {
        fbcf.setOutputTap(tap);
    }
}

void JCReverb::clear()
{
    // Placeholder for any cleanup code needed for the reverb
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