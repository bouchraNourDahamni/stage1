#include "Screw.h"
#include "Data.h"
#include <iostream>
#include <iterator>
#include "StringData.h" 
using namespace std;


Screw::Screw(const std::vector<string>& toolNames, const ToolHandleType& toolHandle) :
	Tool(toolNames, toolHandle) {
}

void Screw::searchProperty(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const {
	const bool nameFound = Tool::searchName(speechTranscription, toolPropertySearch);
	const bool oldnameFound = Tool::searchOldName(toolPropertySearch);
	if (nameFound || oldnameFound) {
		searchSize(speechTranscription, toolPropertySearch);
		toolPropertySearch.isToolFound = true;
	}
}

void Screw::searchSize(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	ScrewSpinePropertySearch& screwSpinePropertySearch = toolPropertySearch.screwSpinePropertySearch;
	if (screwSpinePropertySearch.diameter != DiameterScrew::BadDiameter) {
		return searchLength(speechTranscription, toolPropertySearch);
	}
	if (screwSpinePropertySearch.length != Length::BadLength) {
		return mapLengthToDiameter(speechTranscription, toolPropertySearch);
	}
	if (screwSpinePropertySearch.diameter == DiameterScrew::BadDiameter && screwSpinePropertySearch.length == Length::BadLength) {
		for (const auto& screwData : ScrewSpineData) {
			if (speechTranscription.find(diameterToString[screwData.first]) != string::npos) {
				screwSpinePropertySearch.diameter = screwData.first;
				screwSpinePropertySearch.screwNeedDiameter = "";
				searchLength(speechTranscription, toolPropertySearch);
				return;
			}
			for (const auto& length : screwData.second)
			{
				if (speechTranscription.find(lengthToString[length]) != string::npos) {
					screwSpinePropertySearch.length = length;
					screwSpinePropertySearch.screwNeedLength = "";
					mapLengthToDiameter(speechTranscription, toolPropertySearch);
					return;
				}
			}
		}
		screwSpinePropertySearch.screwNeedDiameter = toolNames_[1];
		screwSpinePropertySearch.screwNeedLength = toolNames_[1];
	}
}
void Screw::searchLength(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const {
	auto lengthsPtr = ScrewSpineData.find(toolPropertySearch.screwSpinePropertySearch.diameter);
	if (lengthsPtr != ScrewSpineData.end()) {
		for (const auto& length : lengthsPtr->second)
		{
			if (speechTranscription.find(lengthToString[length]) != string::npos)
			{
				toolPropertySearch.screwSpinePropertySearch.length = length;
				toolPropertySearch.screwSpinePropertySearch.screwNeedLength = "";
				return;
			}

		}
	}
	//we put index one : because at the index one, we put the name "screw" which is sufficient to perform the next search for the length
	toolPropertySearch.screwSpinePropertySearch.screwNeedLength = toolNames_[1];

}

void Screw::mapLengthToDiameter(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	for (const auto& screwData : ScrewSpineData) {
		if (speechTranscription.find(diameterToString[screwData.first]) != string::npos) {
			if (std::find(screwData.second.begin(), screwData.second.end(), toolPropertySearch.screwSpinePropertySearch.length) != screwData.second.end()) {
				toolPropertySearch.screwSpinePropertySearch.diameter = screwData.first;
				toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter = "";
				return;
			};
		}
	}
	//we put index one : because at the index one, we put the name "screw" which is sufficient to perform the next search for the Diameter
	toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter = toolNames_[1];
}

