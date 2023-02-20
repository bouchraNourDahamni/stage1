#include"ToolHandleType.h"
#include"ScrewSizes.h"
#include <vector>
#pragma once


struct ScrewWristPropertySearch {
	std::string screwNeedThreadFullness;
	std::string screwNeedHeadType;
	std::string screwNeedLength;
	std::string attentionForUser;
	HeadType headType;
	ThreadFullness threadFullness;
	Length length;
};

struct ScrewAnklePropertySearch {
	std::string attentionForUser;
	ThreadType threadType; 
	Length length;
	std::string screwNeedThreadType;
	std::string screwNeedLength;
};

struct ScrewSpinePropertySearch {
	DiameterScrew diameter;
	Length length;
	std::string screwNeedDiameter;
	std::string screwNeedLength;
};

struct UpdateProperty {
	bool UpdateHeadType;
	bool UpdateThreadFulness;
	bool UpdateLength;
};

struct ToolPropertySearch
{
	ScrewWristPropertySearch screwWristPropertySearch;
	ScrewAnklePropertySearch screwAnklePropertySearch;
	ScrewSpinePropertySearch screwSpinePropertySearch;
	ToolHandleType toolHandle;
	Length length;
	bool isToolFound;
	std::string toolNeedSize;
};