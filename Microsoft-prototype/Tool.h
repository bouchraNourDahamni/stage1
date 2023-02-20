// Tool.h

#pragma once

#include <string>
#include <vector>
#include "ToolPropertySearch.h"
#include "ToolHandleType.h"


using namespace std;
class Tool
{
public:
	Tool(const std::vector<string>& toolNames = {}, const  ToolHandleType& toolHandle = ToolHandleType::BadToolHandle);
	virtual void searchProperty(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
	virtual ~Tool() {};
protected:
	virtual bool searchName(const string& result, ToolPropertySearch& toolPropertySearch)const;
	bool searchOldName(ToolPropertySearch& toolPropertySearch) const;
	ToolHandleType toolHandle_;
	vector<string> toolNames_;
};

