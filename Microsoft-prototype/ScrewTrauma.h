#pragma once

#include "Tool.h"
#include "ScrewSizes.h"
#include "SurgeryType.h" 
#include <map> 

class ScrewTrauma : public Tool {
public:
	ScrewTrauma(const std::vector<string>& toolNames = {}, const  ToolHandleType& toolHandle = ToolHandleType::BadToolHandle, const TraumaBoneType& traumaBoneType = {});
	virtual void searchProperty(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const override;
	void setTraumaBoneType(const TraumaBoneType& traumaBoneType);
	virtual ~ScrewTrauma() {};
private:
	void searchScrewAnkleProperties(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const;
	void searchParameter(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const;
	// method to check which property is already mentioned by user, according to these probabilities, We perform the search
	void searchScrewWristParameters(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
	void searchThreadFulness(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
	void searchLength(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
	void searchHeadType(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
	bool verifyProperty(ToolPropertySearch& toolPropertySearch, const UpdateProperty& updateProperty)const;
	// method to check the combination of the length property with the two other properties : Thread Fulness and Head Type.
	bool verifyLength(ToolPropertySearch& toolPropertySearch ,const UpdatePropertyType& updateProperty)const;
	void searchLengthAnkle(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
	void mapLengthToThreadType(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const;
	TraumaBoneType traumaBoneType_;

};
