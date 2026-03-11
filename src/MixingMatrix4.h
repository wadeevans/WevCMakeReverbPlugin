#pragma once

#include <array>
#include <string>

enum class MatrixType4
{
    Hadamard4 = 0,
    Puckette4 = 1,
    Householder4 = 2,
    Count = 3
};

inline std::array<std::string, static_cast<size_t>(MatrixType4::Count)> getMatrixType4Names()
{
    return {"Hadamard4", "Puckette4", "Householder4"};
}

class MixingMatrix4
{
public:
    virtual ~MixingMatrix4() = default;

    virtual void process(const std::array<float, 4> &input, std::array<float, 4> &output) = 0;
};
