#pragma once
#include "ToolPropertySearch.h"
#include "ScrewTrauma.h" 
#include <string>
using namespace std;


class TextToSpeech {
public:
	TextToSpeech(const ToolPropertySearch& toolPropertySearch = {});
	void reply() const;
	~TextToSpeech() {};
private:
	ToolPropertySearch toolPropertySearch_;
	void formatSearchResult(string& resultToFormat) const;
	void formatSearchResultScrewSpine(string& resultToFormat)const;
	void formatSearchResultScrewTrauma(string& resultToFormat) const;
};