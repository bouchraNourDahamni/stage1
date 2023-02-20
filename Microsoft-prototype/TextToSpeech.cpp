#include <iostream>
#include "TextToSpeech.h" 
#include "map"
#include "StringData.h" 
#include "FormatResult.h" 


TextToSpeech::TextToSpeech(const ToolPropertySearch& toolPropertySearch) : toolPropertySearch_(toolPropertySearch) {
}

void TextToSpeech::formatSearchResult(string& resultToFormat)const {
	if (!(toolPropertySearch_.toolHandle == ToolHandleType::BadToolHandle)) {
		resultToFormat = ToolHandeMessage + ToolHandleToString[toolPropertySearch_.toolHandle] + EndLine;
	}
	if (toolPropertySearch_.length != Length::BadLength) {
		resultToFormat += SizeMessage +  lengthToString[toolPropertySearch_.length]+ EndLine;
	}
	if (!toolPropertySearch_.toolNeedSize.empty()) {
		resultToFormat += SizeWait + toolPropertySearch_.toolNeedSize + EndLine;
	}
	formatSearchResultScrewSpine(resultToFormat);
	formatSearchResultScrewTrauma(resultToFormat);
}

void TextToSpeech::formatSearchResultScrewSpine(string& resultToFormat) const {
	const ScrewSpinePropertySearch& screwSpinePropertySearch = toolPropertySearch_.screwSpinePropertySearch;
	if (screwSpinePropertySearch.diameter != DiameterScrew::BadDiameter) {
		resultToFormat += DiameterMessage + diameterToString[toolPropertySearch_.screwSpinePropertySearch.diameter] + EndLine;
	}
	if (screwSpinePropertySearch.length != Length::BadLength) {
		resultToFormat += LengthMessage + lengthToString[toolPropertySearch_.screwSpinePropertySearch.length] + EndLine;
	}
	if (!screwSpinePropertySearch.screwNeedDiameter.empty()) {
		resultToFormat += DiameterWaitM;
	}
	if (!screwSpinePropertySearch.screwNeedLength.empty()) {
		resultToFormat += LengthWait;
	}
}
void TextToSpeech::formatSearchResultScrewTrauma(string& resultToFormat)const {
	const ScrewWristPropertySearch& screwWristPropertySearch = toolPropertySearch_.screwWristPropertySearch;
	if (screwWristPropertySearch.headType != HeadType::BadHeadType) {
		resultToFormat += HeadTypeMessage + headTypeToString[screwWristPropertySearch.headType][0] + EndLine;
	}
	if (screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness) {
		resultToFormat += ThreadFullnessMessage + ThreadFullnessToString[screwWristPropertySearch.threadFullness][0] + EndLine;
	}
	if (screwWristPropertySearch.length != Length::BadLength) {
		resultToFormat += LengthMessage + lengthToString[screwWristPropertySearch.length] + EndLine;
	}
	if (!screwWristPropertySearch.screwNeedHeadType.empty()) {
		resultToFormat += HeadtypeWait;
	}
	if (!screwWristPropertySearch.screwNeedLength.empty()) {
		resultToFormat += LengthWait;
	}
	if (!screwWristPropertySearch.screwNeedThreadFullness.empty()) {
		resultToFormat += ThreadFullnessWait;
	}
	if (!screwWristPropertySearch.attentionForUser.empty()) {
		resultToFormat += screwWristPropertySearch.attentionForUser + EndLine;
	}

	const ScrewAnklePropertySearch& screwAnklePropertySearch = toolPropertySearch_.screwAnklePropertySearch;
	if (screwAnklePropertySearch.threadType != ThreadType::BadThreadType) {
		resultToFormat += ThreadTypeMessage + ThreadTypeToString[screwAnklePropertySearch.threadType] + EndLine;
	}
	if (screwAnklePropertySearch.length != Length::BadLength) {
		resultToFormat += LengthMessage + lengthToString[screwAnklePropertySearch.length] + EndLine;
	}
	if (!screwAnklePropertySearch.screwNeedLength.empty()) {
		resultToFormat += LengthWait + EndLine;
	}
	if (!screwAnklePropertySearch.screwNeedThreadType.empty()) {
		resultToFormat += ThreadTypeWait + EndLine;
	}

}
void TextToSpeech::reply()const {
	string result = EmptyString;
	formatSearchResult(result);
	cout << result << endl;
}