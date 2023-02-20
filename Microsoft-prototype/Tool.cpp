
#include "Tool.h" 
#include <iostream>
using namespace std;

Tool::Tool(const std::vector<string>& toolNames, const ToolHandleType& toolHandle) : toolNames_(toolNames), toolHandle_(toolHandle) {
}

void Tool::searchProperty(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	this->searchName(speechTranscription, toolPropertySearch);
}

bool Tool::searchName(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	for (const auto& name : toolNames_) {
		if (speechTranscription.find(name) != string::npos) {
			toolPropertySearch.toolHandle = toolHandle_;
			return true;
		}
	}
	return false;

}


bool Tool::searchOldName(ToolPropertySearch& toolPropertySearch) const {
	if (!toolPropertySearch.toolNeedSize.empty()) {
		return searchName(toolPropertySearch.toolNeedSize, toolPropertySearch);
	}
	if (!toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter.empty()) {
		return searchName(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, toolPropertySearch);
	}
	if (!toolPropertySearch.screwSpinePropertySearch.screwNeedLength.empty()) {
		return searchName(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, toolPropertySearch);
	}
	if (!toolPropertySearch.screwWristPropertySearch.screwNeedHeadType.empty()) {
		return searchName(toolPropertySearch.screwWristPropertySearch.screwNeedHeadType, toolPropertySearch);
	}
	if (!toolPropertySearch.screwWristPropertySearch.screwNeedThreadFullness.empty()) {
		return searchName(toolPropertySearch.screwWristPropertySearch.screwNeedThreadFullness, toolPropertySearch);
	}
	if (!toolPropertySearch.screwWristPropertySearch.screwNeedLength.empty()) {
		return searchName(toolPropertySearch.screwWristPropertySearch.screwNeedLength, toolPropertySearch);
	}

	if (!toolPropertySearch.screwAnklePropertySearch.screwNeedLength.empty()) {
		return searchName(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, toolPropertySearch);
	}
	if (!toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType.empty()) {
		return searchName(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, toolPropertySearch);
	}
	return false;
}







