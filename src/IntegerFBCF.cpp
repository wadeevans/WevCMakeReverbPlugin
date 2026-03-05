// IntegerFBCF.cpp
// Created by CWE 02/03/26

#include "IntegerFBCF.h"

void IntegerFBCF::prepare(double sampleRate, int delayInSamples, float feedbackGain)
{
    m_feedbackGain = feedbackGain;
    m_delayLine.prepare(delayInSamples);

    m_dampingFilter.prepare(sampleRate);
    m_dampingFilter.setCutoffFrequency(10000.0f);

    clear();
}

float IntegerFBCF::processSample(float input)
{
    // y(n) = x(n) + g * y(n-M)
    float dampedOutput;

    if (m_dampingEnabled)
        dampedOutput = m_dampingFilter.processSample(m_delayOutput);
    else
        dampedOutput = m_delayOutput;  // TRUE BYPASS

    float output = input + (dampedOutput * m_feedbackGain);
    m_delayOutput = m_delayLine.processSample(output);

    // return m_delayOutput;
    return (m_outputTap == OutputTap::PostDelay) ? m_delayOutput : output;
    // return (m_outputTap == OutputTap::PostDelay) ? m_delayOutput : 0.0f; // test case
}

void IntegerFBCF::clear()
{
    m_delayLine.clear();
    m_dampingFilter.clear();
    m_delayOutput = 0.0f; // Also reset the output
}