#pragma once

#include <array>
#include <string>

enum class ReverbType
{
    Schroeder = 0,
    JCRev = 1,
    FDN4 = 2,
    Count = 3
};

inline std::array<std::string, static_cast<size_t>(ReverbType::Count)> getReverbTypeNames()
{
    return {"Schroeder", "JCRev", "FDN4"};
}

// Abstract base class - future implementation
// class Reverb
// {
// public:
//     virtual void prepare(double sampleRate) = 0;
//     virtual float processSample(float input) = 0;
//     virtual void clear() = 0;
// };