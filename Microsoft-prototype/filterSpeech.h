#pragma once

#include <string>
#include "Tool.h"
#include "SurgeryType.h"
#include "ToolPropertySearch.h"

class FilterSpeech {
public:
	explicit FilterSpeech(const SurgeryType& surgeryType = SurgeryType::Spine);
	void searchProperties(const string& result, ToolPropertySearch& toolPropertySearch)const;
	void reinitPropertySearch(ToolPropertySearch& toolPropertySearch)const;
	~FilterSpeech() {};
private:
	SurgeryType procedure_;
	string otherFeature(const string& speechTranscription)const;
	string convertToLowerCase(const string& InString)const;
	const std::vector<shared_ptr<Tool>>& setToolList() const;

};