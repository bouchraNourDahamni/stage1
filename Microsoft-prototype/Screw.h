#pragma once

#include "Tool.h"
#include "ScrewSizes.h" 
#include <map> 

class Screw : public Tool {

public:
	Screw(const std::vector<string>& toolNames ,
		const ToolHandleType& toolHandle);
	virtual void searchProperty(const std::string& speechTranscription, ToolPropertySearch& toolPropertySearch)const override;
	virtual ~Screw() {};
private:
	void searchSize(const std::string& result, ToolPropertySearch& toolPropertySearch)const;
	void searchLength(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const;
	void mapLengthToDiameter(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
};
