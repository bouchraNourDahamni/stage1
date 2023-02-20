#include "ToolWithSizes.h" 
#include "StringData.h"
ToolWithSizes::ToolWithSizes(const std::vector<string>& toolNames, const ToolHandleType& toolHandle, const std::vector<Length>& toolLengths) : Tool(toolNames, toolHandle), toolLengths_(toolLengths) {
}

void ToolWithSizes::searchProperty(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	const bool nameFound = Tool::searchName(speechTranscription, toolPropertySearch);
	const bool oldNameFound = Tool::searchOldName(toolPropertySearch);
	if (nameFound) {
		searchLength(speechTranscription, toolPropertySearch);
		toolPropertySearch.isToolFound = true;
	}
	if (oldNameFound) {
		searchLength(speechTranscription, toolPropertySearch);
	}
}

void ToolWithSizes::searchLength(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	for (const auto& length : toolLengths_) {
		if (speechTranscription.find(lengthToString[length]) != string::npos) {
			toolPropertySearch.length = length;
			toolPropertySearch.toolNeedSize = "";
			toolPropertySearch.isToolFound = true;
			return;
		}
	}
	toolPropertySearch.toolNeedSize = this->toolNames_[0];
}
