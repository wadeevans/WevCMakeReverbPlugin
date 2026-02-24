// FDN4.cpp
// created by CWE 2026-02-24

#include "FDN4.h"
#include "Hadamard4.h"

FDN4::FDN4()
    : m_mixingMatrix(std::make_unique<Hadamard4>())
{

}

void FDN4::prepare(double sampleRate)
{
    float smoothingMs = 50.0f * 0.05f;

    for (auto& delayLine : m_delayLines)
    {
        delayLine.prepare(sampleRate, 50.0f, smoothingMs);

    }

    m_delayLines[0].setDelay(37.0f);
    m_delayLines[1].setDelay(41.0f);
    m_delayLines[2].setDelay(43.0f);
    m_delayLines[3].setDelay(47.0f);

    for (auto& dampingFilter : m_dampingFilters)
    {
        dampingFilter.prepare(sampleRate);
        dampingFilter.setCutoffFrequency(10000.0f);
    }

    for (auto& delayOutput : m_delayOutputs)
    {
        delayOutput = 0.0f;
    }
}

float FDN4::processSample(float input)
{
    std::array<float, 4> delayInputs;

    std::array<float, 4> mixingMatrixInputs;

    std::array<float, 4> mixingMatrixOutputs;

    mixingMatrixInputs = m_delayOutputs;

    m_mixingMatrix->process(mixingMatrixInputs, mixingMatrixOutputs);

    for (int i = 0; i < 4; i++)
    {
        delayInputs[i] = m_dampingFilters[i].processSample(mixingMatrixOutputs[i]) * m_feedbackGain + input;
    }
    
    for (int i = 0; i < 4; i++)
    {
        m_delayOutputs[i] = m_delayLines[i].processSample(delayInputs[i]);
    }
    

    return (m_delayOutputs[0] + m_delayOutputs[1] + m_delayOutputs[2] + m_delayOutputs[3]) * 0.25f;
}

void FDN4::clear()
{
    for (auto& delayLine : m_delayLines)
    {
        delayLine.clear();
    }

    for (auto& dampingFilter : m_dampingFilters)
    {
        dampingFilter.clear();
    }

    for (auto& delayOutput : m_delayOutputs)
    {
        delayOutput = 0.0f;
    }
}

void FDN4::setDelayTimes(const std::array<float, 4>& delayTimes)
{
    

}