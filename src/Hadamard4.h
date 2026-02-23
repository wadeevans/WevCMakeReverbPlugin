#pragma once

#include "MixingMatrix4.h"

class Hadamard4 : public MixingMatrix4
{
public:
    Hadamard4() = default;
    ~Hadamard4() override = default;

    void process(const std::array<float, 4> &input, std::array<float, 4> &output) override;
};