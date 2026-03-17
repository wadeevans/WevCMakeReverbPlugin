#pragma once

#include <array>

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
    void setPreDelayEnabled(bool preDelayEnabled);
    void clear();

    void setInputAllPassesEnabled(bool inputAllPassesEnabled) { m_inputAllPassesEnabled = inputAllPassesEnabled; }
    void setOutputAllPassesEnabled(bool outputAllPassesEnabled) { m_outputAllPassesEnabled = outputAllPassesEnabled; }

private:

    static constexpr int NUM_COMBS = 4;

    std::array<FixedAllPass, 3> m_inAllPasses;
    std::array<FeedbackCombFilter, 4> m_fbcfs;
    std::array<FixedAllPass, 2> m_outAllPasses;

    bool m_inputAllPassesEnabled = true;
    bool m_outputAllPassesEnabled = false;

};
