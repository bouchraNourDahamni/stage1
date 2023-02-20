#include <cctype>
#include "filterSpeech.h"
#include "Data.h"
#include "Feature.h"
#include <iostream>
#include "algorithm"
using namespace std;

FilterSpeech::FilterSpeech(const SurgeryType& procedure)
	: procedure_(procedure)
{}

const std::vector<shared_ptr<Tool>>& FilterSpeech::setToolList() const {
	if (procedure_ == SurgeryType::Trauma) {
		return toolListTrauma;
	}
	if (procedure_ == SurgeryType::Spine) {
		return toolListSpine;
	}
	if (procedure_ == SurgeryType::Reconstruction) {
		return toolListReconstruction;
	}
	else {
		return std::vector<shared_ptr<Tool>>();
	}
}

void FilterSpeech::searchProperties(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	const string& speechTranscriptionLower = convertToLowerCase(speechTranscription);
	const std::vector<shared_ptr<Tool>>& toolList = setToolList();
	for (const auto& tool : toolList) {
		if (!toolPropertySearch.isToolFound) {
			tool->searchProperty(speechTranscriptionLower, toolPropertySearch);
		}
	}
}


void FilterSpeech::reinitPropertySearch(ToolPropertySearch& toolPropertySearch)const
{
	toolPropertySearch.isToolFound = false;
	toolPropertySearch.toolHandle = ToolHandleType::BadToolHandle;
	if (toolPropertySearch.screwSpinePropertySearch.diameter != DiameterScrew::BadDiameter && toolPropertySearch.screwSpinePropertySearch.length != Length::BadLength) {

		toolPropertySearch.screwSpinePropertySearch.diameter = DiameterScrew::BadDiameter;
		toolPropertySearch.screwSpinePropertySearch.length = Length::BadLength;
	}
	if (toolPropertySearch.screwWristPropertySearch.length != Length::BadLength &&
		toolPropertySearch.screwWristPropertySearch.headType!= HeadType::BadHeadType &&
		toolPropertySearch.screwWristPropertySearch.threadFullness!= ThreadFullness::BadThreadFulness) {
		toolPropertySearch.screwWristPropertySearch.length = Length::BadLength;
		toolPropertySearch.screwWristPropertySearch.threadFullness = ThreadFullness::BadThreadFulness ;
		toolPropertySearch.screwWristPropertySearch.headType = HeadType::BadHeadType;
	}
	if (toolPropertySearch.length!= Length::BadLength) {
		toolPropertySearch.length = Length::BadLength;
	}

	if (toolPropertySearch.screwAnklePropertySearch.threadType != ThreadType::BadThreadType && toolPropertySearch.screwAnklePropertySearch.length != Length::BadLength) {
		toolPropertySearch.screwAnklePropertySearch.threadType = ThreadType::BadThreadType;
		toolPropertySearch.screwAnklePropertySearch.length = Length::BadLength;
	}
}


string FilterSpeech::otherFeature(const string& result)const {
	for (const Feature& feature : otherFeatures) {
		for (const auto& name : feature.featureNames_) {
			if (result.find(string(name)) != string::npos) {
				return feature.action_;
			}
		}

	}
	return "";
}

string FilterSpeech::convertToLowerCase(const string& InString) const {
	std::string result(InString);
	std::transform(std::cbegin(result), std::cend(result), std::begin(result),
		[](unsigned char c) -> unsigned char { return std::tolower(c); });
	return result;
}







