// FDN4.cpp
// created by CWE 2026-02-24

#include "FDN4.h"
#include "Hadamard4.h"
#include "Puckette4.h"
#include "Householder4.h"

FDN4::FDN4()
    : m_mixingMatrix(std::make_unique<Hadamard4>())
{
}

void FDN4::prepare(double sampleRate)
{
    float maxDelayInMs = 100.0f;
    float smoothingMs = maxDelayInMs * 0.05f;

    for (auto &delayLine : m_delayLines)
    {
        delayLine.prepare(sampleRate, maxDelayInMs, smoothingMs);
    }

    /*m_delayLines[0].setDelayInMs(37.0f);
    m_delayLines[1].setDelayInMs(41.0f);
    m_delayLines[2].setDelayInMs(43.0f);
    m_delayLines[3].setDelayInMs(47.0f);*/

    m_delayLines[0].setDelayInSamples(1571.0f);
    m_delayLines[1].setDelayInSamples(2053.0f);
    m_delayLines[2].setDelayInSamples(2719.0f);
    m_delayLines[3].setDelayInSamples(3463.0f);

    for (auto &dampingFilter : m_dampingFilters)
    {
        dampingFilter.prepare(sampleRate);
        dampingFilter.setCutoffFrequency(20000.0f);
    }

    for (auto &delayOutput : m_delayOutputs)
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
        if (m_dampingEnabled)
            delayInputs[i] = m_dampingFilters[i].processSample(mixingMatrixOutputs[i]) * m_feedbackGains[i] + input;
        else
            delayInputs[i] = mixingMatrixOutputs[i] * m_feedbackGains[i] + input;
    }

    for (int i = 0; i < 4; i++)
    {
        m_delayOutputs[i] = m_delayLines[i].processSample(delayInputs[i]);
    }

    return (m_delayOutputs[0] + m_delayOutputs[1] + m_delayOutputs[2] + m_delayOutputs[3]) * 0.25f;
}

void FDN4::setDampingCutOffFrequency(float frequencyHz)
{
    for (auto &dampingFilter : m_dampingFilters)
        dampingFilter.setCutoffFrequency(frequencyHz);
}

void FDN4::clear()
{
    for (auto &delayLine : m_delayLines)
    {
        delayLine.clear();
    }

    for (auto &dampingFilter : m_dampingFilters)
    {
        dampingFilter.clear();
    }

    for (auto &delayOutput : m_delayOutputs)
    {
        delayOutput = 0.0f;
    }
}

void FDN4::setDelayTimesInMs(const std::array<float, 4> &delayTimesInMs)
{
    for (int i = 0; i < 4; i++)
        m_delayLines[i].setDelayInMs(delayTimesInMs[i]);
}

void FDN4::setDelayTimesInSamples(const std::array<float, 4> &delayTimesInSamples)
{
    for (int i = 0; i < 4; i++)
        m_delayLines[i].setDelayInSamples(delayTimesInSamples[i]);
}

void FDN4::setMatrixType(MatrixType4 matrixType)
{
    switch (matrixType)
    {
    case MatrixType4::Hadamard4:
        m_mixingMatrix = std::make_unique<Hadamard4>();
        break;
    case MatrixType4::Puckette4:
        m_mixingMatrix = std::make_unique<Puckette4>();
        break;
    case MatrixType4::Householder4:
        m_mixingMatrix = std::make_unique<Householder4>();
        break;
    default:
        break;
    }
}