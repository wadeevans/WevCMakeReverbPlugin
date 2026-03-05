#pragma once

#include <array>

#include "IntegerAllPass.h"
#include "IntegerFBCF.h"

class JCReverb
{
public:
    JCReverb() = default;
    ~JCReverb() = default;

    void prepare(double sampleRate);
    float processSample(float input);
    void setDampingEnabled(bool dampingEnabled);
    void setDampingCutOffFrequency(float dampingCutoffFrequency);
    void setPreDelayEnabled(bool preDelayEnabled);
    void clear();

private:
    static constexpr int NUM_COMBS = 4;

    std::array<IntegerAllPass, 3> m_inAllPasses;
    std::array<IntegerFBCF, 4> m_fbcfs;
    std::array<IntegerAllPass, 2> m_outAllPasses;
};