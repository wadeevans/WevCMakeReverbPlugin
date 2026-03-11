// Householder.cpp
// created by CWE on 2026-03-11

#include "Householder4.h"

static constexpr float HOUSEHOLDER4_NORM = 0.5f;

void Householder4::process(const std::array<float, 4> &input, std::array<float, 4> &output)
{
    //

    output[0] = (input[0] - input[1] - input[2] - input[3]) * HOUSEHOLDER4_NORM;
    output[1] = (-input[0] + input[1] - input[2] - input[3]) * HOUSEHOLDER4_NORM;
    output[2] = (-input[0] - input[1] + input[2] - input[3]) * HOUSEHOLDER4_NORM;
    output[3] = (-input[0] - input[1] - input[2] + input[3]) * HOUSEHOLDER4_NORM;
}