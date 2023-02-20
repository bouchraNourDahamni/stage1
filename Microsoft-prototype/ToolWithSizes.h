#pragma once

#include "Tool.h"
#include "ScrewSizes.h"


class ToolWithSizes : public Tool
{
public:
	ToolWithSizes(const std::vector<string>& toolNames = {}, const ToolHandleType& toolHandle = ToolHandleType::BadToolHandle, const std::vector<Length>& toolLengths = {});
	virtual void searchProperty(const std::string& speechTanscription, ToolPropertySearch& toolPropertySearch)const override;
	virtual ~ToolWithSizes() {};
private:
	const std::vector<Length> toolLengths_;
	void searchLength(const std::string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
};