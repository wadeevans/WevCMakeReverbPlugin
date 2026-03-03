// IntegerAllPass.cpp
// Created by CWE 03/03/26

#include "IntegerAllPass.h"

void IntegerAllPass::prepare(int delayInSamples, float feedbackGain)
{
    m_feedbackGain = feedbackGain;
    m_delayLine.prepare(delayInSamples);
    clear();
}

float IntegerAllPass::processSample(float input)
{
    float delayInput = input + (m_delayOutput * m_feedbackGain);

    m_delayOutput = m_delayLine.processSample(delayInput);

    return (delayInput * -m_feedbackGain) + m_delayOutput;
}

void IntegerAllPass::clear()
{
    m_delayLine.clear();
    m_delayOutput = 0.0f; // Also reset the output
}