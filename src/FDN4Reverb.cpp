// FDN4Reverb.cpp
// 
// created by cwe 09/03/2026

#include "FDN4Reverb.h"

void FDN4Reverb::prepare(double sampleRate)
{
    float inAllPassLengths[3] = { 7.0f, 3.0f, 1.0f };
    float inAllPassGains[3] = { 0.7f, 0.7f, 0.7f };

    for (size_t i = 0; i < m_inAllPasses.size(); i++)
    {
        m_inAllPasses[i].prepare(sampleRate, inAllPassLengths[i], inAllPassGains[i]);
    }

    m_fdn4.prepare(sampleRate);

    float outAllPassLengths[2] = { 5.0f, 1.70f };
    float outAllPassGains[2] = { 0.7f, 0.7f };

    for (size_t i = 0; i < m_outAllPasses.size(); i++)
    {
        m_outAllPasses[i].prepare(sampleRate, outAllPassLengths[i], outAllPassGains[i]);
    }

}

float FDN4Reverb::processSample(float input)
{
    float diffused = m_inAllPasses[0].processSample(input);
    diffused = m_inAllPasses[1].processSample(diffused);
    diffused = m_inAllPasses[2].processSample(diffused);

    float output = m_fdn4.processSample(diffused);

    // output = m_outAllPasses[0].processSample(output);

    // output = m_outAllPasses[1].processSample(output);

    return output;
}

void FDN4Reverb::setDampingEnabled(bool dampingEnabled)
{
    m_fdn4.setDampingEnabled(dampingEnabled);
}

void FDN4Reverb::setDampingCutOffFrequency(float dampingCutoffFrequency)
{
    m_fdn4.setDampingCutOffFrequency(dampingCutoffFrequency);
}

void FDN4Reverb::clear()
{
    for (auto& inAllPass : m_inAllPasses)
    {
        inAllPass.clear();
    }

    m_fdn4.clear();

    for (auto& outAllPass : m_outAllPasses)
    {
        outAllPass.clear();
    }
}