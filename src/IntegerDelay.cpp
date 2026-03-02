// IntegerDelay.cpp
// Created by CWE 02/03/26


#include "IntegerDelay.h"

void IntegerDelay::prepare(int delayInSamples)
{
    m_bufferSize = delayInSamples;
    m_buffer.resize(m_bufferSize);
    m_writeIndex = 0;
    clear();
}

float IntegerDelay::processSample(float input)
{
    float output = m_buffer[m_writeIndex];

    m_buffer[m_writeIndex] = input;
    m_writeIndex = (m_writeIndex + 1) % m_bufferSize;

    return output;
}
   
void IntegerDelay::clear()
{
    for (auto& sample : m_buffer) sample = 0.0f;
    m_writeIndex = 0;
}