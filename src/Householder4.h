#pragma once

#include "MixingMatrix4.h"

class Householder4 : public MixingMatrix4
{
public:
    Householder4() = default;
    ~Householder4() override = default;

    void process(const std::array<float, 4> &input, std::array<float, 4> &output) override;
};