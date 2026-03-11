#pragma once

#include "MixingMatrix4.h"

class Puckette4 : public MixingMatrix4
{
public:
    Puckette4() = default;
    ~Puckette4() override = default;

    void process(const std::array<float, 4> &input, std::array<float, 4> &output) override;
};
