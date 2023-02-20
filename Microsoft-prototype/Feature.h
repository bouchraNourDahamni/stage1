// Feature.h

#pragma once

#include <string>
#include <vector>

using namespace std;
class Feature
{
public:
	Feature(const std::vector<string>& featureNames = {}, const std::string& action = "");
	std::vector<string> featureNames_;
	std::string action_;
};