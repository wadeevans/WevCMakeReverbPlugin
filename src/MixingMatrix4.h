#pragma once

#include <array>

class MixingMatrix4
{
public:
    virtual ~MixingMatrix4() = default;

    virtual void process(const std::array<float, 4> &input, std::array<float, 4> &output) = 0;
};
