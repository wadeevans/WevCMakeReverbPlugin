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

    void setMatrixType(MatrixType4 matrixType) { m_fdn4.setMatrixType(matrixType); }
    void setInputAllPassesEnabled(bool inputAllPassesEnabled) { m_inputAllPassesEnabled = inputAllPassesEnabled; }
    void setOutputAllPassesEnabled(bool outputAllPassesEnabled) { m_outputAllPassesEnabled = outputAllPassesEnabled; }

private:
    FDN4 m_fdn4;

    std::array<FixedAllPass, 3> m_inAllPasses;
    
    std::array<FixedAllPass, 2> m_outAllPasses;

    bool m_inputAllPassesEnabled = true;
    bool m_outputAllPassesEnabled = false;
};