#pragma once

#include <string>

std::string confidenceLabel(int confidence);

bool isUnknown(int confidence);

bool isLowConfidence(int confidence);

bool isHighConfidence(int confidence);