#include "Confidence.hpp"

std::string confidenceLabel(int confidence)
{
    switch (confidence)
    {
    case 0:
        return "uncertain";
    case 1:
        return "low";
    case 2:
        return "high";
    default:
        return "unknown";
    }
}

bool isUnknown(int confidence)
{
    return confidence == 0 ? true : false;
}

bool isLowConfidence(int confidence)
{
    return confidence == 1 ? true : false;
}

bool isHighConfidence(int confidence)
{
    return confidence == 2 ? true : false;
}