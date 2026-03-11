// Hadamard4.cpp
// created by CWE on 2026-02-23

#include "Hadamard4.h"

static constexpr float HADAMARD4_NORM = 0.5f;

void Hadamard4::process(const std::array<float, 4> &input, std::array<float, 4> &output)
{
    float a = input[0] + input[1];
    float b = input[0] - input[1];
    float c = input[2] + input[3];
    float d = input[2] - input[3];

    output[0] = (a + c) * HADAMARD4_NORM;
    output[1] = (b + d) * HADAMARD4_NORM;
    output[2] = (a - c) * HADAMARD4_NORM;
    output[3] = (b - d) * HADAMARD4_NORM;
}