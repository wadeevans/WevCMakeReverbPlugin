#pragma once

#include <array>

#include "FDN4.h"
#include "FixedAllPass.h"

class FDN4Reverb
{
public:

    FDN4Reverb() = default;
    ~FDN4Reverb() = default;

    void prepare(double sampleRate);
    float processSample(float input);
    void setDampingEnabled(bool dampingEnabled);
    void setDampingCutOffFrequency(float dampingCutoffFrequency);
    // void setPreDelayEnabled(bool preDelayEnabled);
    void clear();

private:
    FDN4 m_fdn4;

    std::array<FixedAllPass, 3> m_inAllPasses;
    
    std::array<FixedAllPass, 2> m_outAllPasses;
};