// Puckette4.cpp
// created by CWE on 2026-03-11

#include "Puckette4.h"

static constexpr float PUCKETTE4_NORM = 0.7071067811865475f; // 1/sqrt(2)

void Puckette4::process(const std::array<float, 4>& input, std::array<float, 4>& output)
{
    output[0] = (input[1] + input[2]) * PUCKETTE4_NORM;
    output[1] = (-input[0] - input[3]) * PUCKETTE4_NORM;
    output[2] = (input[0] - input[3]) * PUCKETTE4_NORM;
    output[3] = (input[1] - input[2]) * PUCKETTE4_NORM;

}

