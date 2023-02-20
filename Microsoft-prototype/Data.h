#pragma once
#include "Feature.h"
#include "Screw.h"
#include "ToolWithSizes.h"
#include "ScrewTrauma.h" 
#include <memory>
#include <map>
#include  "ToolHandleType.h"
#include  "SurgeryType.h"

extern const std::vector<Length> screwWristCommonLength;
extern const std::vector <Length> screwSpineCommonLength;
extern const map<DiameterScrew, std::vector<Length>> ScrewSpineData;
extern const multimap< ScrewWrist, std::vector<Length>> screwWristData;
extern const map<ThreadType, std::vector<Length>> screwAnkleData;
extern const std::vector<shared_ptr<Tool>> toolListSpine;
extern const shared_ptr<ScrewTrauma> screwTrauma;
extern std::vector<shared_ptr<Tool>> toolListTrauma;
extern std::vector<shared_ptr<Tool>> toolListReconstruction;
extern const std::vector<Feature> otherFeatures;


