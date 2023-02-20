#pragma once
#include "ScrewSizes.h"
#include "ToolHandleType.h"
#include "map"
 
extern std::map< ThreadFullness, std::vector<std::string>> ThreadFullnessToString;
 
extern std::map< HeadType, std::vector<std::string>> headTypeToString;
 
extern std::map<Length, std::string> lengthToString;

extern std::map<DiameterScrew, std::string> diameterToString;

extern std::map<ThreadType, std::string> ThreadTypeToString;

extern std::map< ToolHandleType, std::string > ToolHandleToString;
 
