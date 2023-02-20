#include "ScrewTrauma.h" 
#include "AttentionUser.h" 
#include "Data.h" 
#include <iostream>
#include "StringData.h"
#include <algorithm>

ScrewTrauma::ScrewTrauma(const std::vector<string>& toolNames, const  ToolHandleType& toolHandle,const TraumaBoneType& traumaBoneType)
	: Tool(toolNames, toolHandle),traumaBoneType_(traumaBoneType){}

void ScrewTrauma::searchProperty(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	const bool nameFound = Tool::searchName(speechTranscription, toolPropertySearch);
	const bool oldNameFound = Tool::searchOldName(toolPropertySearch);
	if (nameFound || oldNameFound) {
		searchParameter(speechTranscription, toolPropertySearch);
		toolPropertySearch.isToolFound = true;
	}
}

void ScrewTrauma::setTraumaBoneType(const TraumaBoneType& traumaBoneType) {
	traumaBoneType_ = traumaBoneType;
}

void  ScrewTrauma::searchParameter(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const {
	if (traumaBoneType_ == TraumaBoneType::Wrist) {
		searchScrewWristParameters(speechTranscription, toolPropertySearch);
	}
	else if (traumaBoneType_ == TraumaBoneType::Ankle) {
		searchScrewAnkleProperties(speechTranscription, toolPropertySearch);
	}
	toolPropertySearch.isToolFound = true;
}

void ScrewTrauma::searchScrewAnkleProperties(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const {
	ScrewAnklePropertySearch& screwAnklePropertySearch = toolPropertySearch.screwAnklePropertySearch;
	if (screwAnklePropertySearch.threadType != ThreadType::BadThreadType) {
		return searchLengthAnkle(speechTranscription, toolPropertySearch);
	}
	if (screwAnklePropertySearch.length != Length::BadLength) {
		return mapLengthToThreadType(speechTranscription, toolPropertySearch);
	}
	if (screwAnklePropertySearch.threadType == ThreadType::BadThreadType && screwAnklePropertySearch.length == Length::BadLength) {
		for (const auto& screwAnkle : screwAnkleData) {
			if (speechTranscription.find(ThreadTypeToString[screwAnkle.first]) != string::npos) {
				screwAnklePropertySearch.threadType = screwAnkle.first;
				screwAnklePropertySearch.screwNeedThreadType = "";
				searchLengthAnkle(speechTranscription, toolPropertySearch);
				return;
			}
			for (const auto& length : screwAnkle.second)
			{
				if (speechTranscription.find(lengthToString[length]) != string::npos) {
					screwAnklePropertySearch.length = length;
					screwAnklePropertySearch.screwNeedLength = "";
					mapLengthToThreadType(speechTranscription, toolPropertySearch);
					return;
				}
			}
		}
		screwAnklePropertySearch.screwNeedThreadType = toolNames_[1];
		screwAnklePropertySearch.screwNeedLength = toolNames_[1];
	}

}

void ScrewTrauma::searchScrewWristParameters(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const {
	ScrewWristPropertySearch& screwWristPropertySearch = toolPropertySearch.screwWristPropertySearch;
	screwWristPropertySearch.attentionForUser.clear();
	// Cas one : Property Head Type property is already mentioned , but length and Threaf Fulness are not
	if (screwWristPropertySearch.headType != HeadType::BadHeadType &&
		screwWristPropertySearch.length == Length::BadLength &&
		screwWristPropertySearch.threadFullness == ThreadFullness::BadThreadFulness) {
		searchLength(speechTranscription, toolPropertySearch);
		searchThreadFulness(speechTranscription, toolPropertySearch);
		const UpdateProperty& updateProperty = { false,true,true };
		if (screwWristPropertySearch.length != Length::BadLength && screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness) {
			if (!(verifyProperty(toolPropertySearch, updateProperty))) {
				screwWristPropertySearch.attentionForUser = LTPreviousHeadType;
			};

		};
		return;
	}
	//Case Two : Property Length is already mentioned , but HeadType and ThreadFulness are not
	if (screwWristPropertySearch.length != Length::BadLength &&
		screwWristPropertySearch.headType == HeadType::BadHeadType &&
		screwWristPropertySearch.threadFullness == ThreadFullness::BadThreadFulness) {
		searchHeadType(speechTranscription, toolPropertySearch);
		searchThreadFulness(speechTranscription, toolPropertySearch);
		if (screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness) {
			if (!verifyLength(toolPropertySearch, UpdatePropertyType::UpdateLength)) {
				screwWristPropertySearch.attentionForUser = LTMatch;
			};
		}
		if (screwWristPropertySearch.headType != HeadType::BadHeadType
			&& screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness) {
			const UpdateProperty updateProperty = { true,true,false };
			if (!verifyProperty(toolPropertySearch, updateProperty)) {
				screwWristPropertySearch.attentionForUser = HTPreviousLength;
			};

		}
		return;
	}
	//Case Three : Property  Thread Fulllness is already mentioned and headType and Length are not
	if (screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness
		&& screwWristPropertySearch.headType == HeadType::BadHeadType &&
		screwWristPropertySearch.length == Length::BadLength
		) {
		searchLength(speechTranscription, toolPropertySearch);
		if (screwWristPropertySearch.length != Length::BadLength) {
			if (!verifyLength(toolPropertySearch, UpdatePropertyType::UpdateThreadFulness)) {
				screwWristPropertySearch.attentionForUser = LTMatch;
			};
		}
		searchHeadType(speechTranscription, toolPropertySearch);
		const UpdateProperty updateProperty = { true , false , true };
		if (screwWristPropertySearch.headType != HeadType::BadHeadType && screwWristPropertySearch.length != Length::BadLength) {
			if (!verifyProperty(toolPropertySearch, updateProperty)) {
				screwWristPropertySearch.attentionForUser = HLPreviousThreadFulness;
			};
		}
		return;
	}
	//Case Four:  Property Head Type and Length is already mentioned and ThreadFulness is not 
	//We don't call verify Property because with threadFulness because all combination are possible 
	if (screwWristPropertySearch.headType != HeadType::BadHeadType
		&& screwWristPropertySearch.length != Length::BadLength &&
		screwWristPropertySearch.threadFullness == ThreadFullness::BadThreadFulness) {
		searchThreadFulness(speechTranscription, toolPropertySearch);
		return;
	}

	//Case Five : Property Head Type and Thread Fulness is already mentioned and length is not
	if (screwWristPropertySearch.headType != HeadType::BadHeadType &&
		screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness &&
		screwWristPropertySearch.length == Length::BadLength) {
		searchLength(speechTranscription, toolPropertySearch);
		const UpdateProperty updateProperty = { false , false , true };
		if (screwWristPropertySearch.length != Length::BadLength) {
			if (!verifyProperty(toolPropertySearch, updateProperty)) {
				screwWristPropertySearch.attentionForUser = LPreviousThreadHeadType;
			};
		}
		return;

	}
	//Case Six :  Property Length and Thread Fulness is already mentionned and head type is not
	if (screwWristPropertySearch.length != Length::BadLength &&
		screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness &&
		screwWristPropertySearch.headType == HeadType::BadHeadType) {
		searchHeadType(speechTranscription, toolPropertySearch);
		const UpdateProperty updateProperty = { true , false ,false };
		if (screwWristPropertySearch.headType != HeadType::BadHeadType) {
			if (!verifyProperty(toolPropertySearch, updateProperty)) {
				screwWristPropertySearch.attentionForUser = HPreviousLengthThread;
			};
		}
		return;

	}
	//Case Seven : Property Lenght and Thread Fulness and Head Type are not already mentioned
	if (screwWristPropertySearch.length == Length::BadLength &&
		screwWristPropertySearch.threadFullness == ThreadFullness::BadThreadFulness &&
		screwWristPropertySearch.headType == HeadType::BadHeadType) {
		searchHeadType(speechTranscription, toolPropertySearch);
		searchLength(speechTranscription, toolPropertySearch);
		searchThreadFulness(speechTranscription, toolPropertySearch);
		if (screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness && screwWristPropertySearch.length != Length::BadLength) {
			if (!verifyLength(toolPropertySearch, UpdatePropertyType::UpdateThreadFulness)) {
				screwWristPropertySearch.attentionForUser = LTMatch;
			};
		}
		if (screwWristPropertySearch.headType != HeadType::BadHeadType && screwWristPropertySearch.length !=
			Length::BadLength && screwWristPropertySearch.threadFullness !=
			ThreadFullness::BadThreadFulness) {
			const UpdateProperty updateProperty = { false,false,true };
			if (!verifyProperty(toolPropertySearch, updateProperty)) {
				screwWristPropertySearch.attentionForUser = HeadLengthThreadMatch;
			};
		}
		return;
	}

}

bool ScrewTrauma::verifyProperty(ToolPropertySearch& toolPropertySearch, const UpdateProperty& updateProperty)const {
	// check the combination of the three properties when mentioned
	ScrewWristPropertySearch& screwWristPropertySearch = toolPropertySearch.screwWristPropertySearch;
	const ScrewWrist screwWristToSearch = { screwWristPropertySearch.threadFullness ,screwWristPropertySearch.headType };
	const auto screwWristItr = std::find_if(screwWristData.begin(),
		screwWristData.end(),
		[&screwWristToSearch](std::pair<ScrewWrist, std::vector<Length>> const& item) {
		return (screwWristToSearch == item.first);
	});
	if (screwWristItr != screwWristData.end()) {
		auto it = find(screwWristItr->second.begin(), screwWristItr->second.end(), screwWristPropertySearch.length);
		if (it == screwWristItr->second.end()) {
			if (updateProperty.UpdateLength) {
				screwWristPropertySearch.length = Length::BadLength;
				screwWristPropertySearch.screwNeedLength = toolNames_[1];
			}
			if (updateProperty.UpdateThreadFulness) {
				screwWristPropertySearch.threadFullness = ThreadFullness::BadThreadFulness;
				screwWristPropertySearch.screwNeedThreadFullness = toolNames_[1];
			}
			if (updateProperty.UpdateHeadType) {
				screwWristPropertySearch.headType = HeadType::BadHeadType;
				screwWristPropertySearch.screwNeedHeadType = toolNames_[1];
			}
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}
bool ScrewTrauma::verifyLength(ToolPropertySearch& toolPropertySearch, const UpdatePropertyType& updateProperty)const {
	// We don't need to check the combination of Head Type and Thread Fulness , because all combination are possible
	// return true if we fin the good comibnation
	ScrewWristPropertySearch& screwWristPropertySearch = toolPropertySearch.screwWristPropertySearch;
	const ScrewWrist  screwWristToSearch1 = { screwWristPropertySearch.threadFullness,HeadType::Locking };
	const ScrewWrist screwWristToSearch2 = { screwWristPropertySearch.threadFullness,HeadType::NonLockingCross };
	const auto screwWristItr1 = std::find_if(screwWristData.begin(),
		screwWristData.end(),
		[&screwWristToSearch1](std::pair<ScrewWrist, std::vector<Length>> const& item) {
		return (screwWristToSearch1 == item.first);
	});
	const auto screwWristItr2 = std::find_if(screwWristData.begin(),
		screwWristData.end(),
		[&screwWristToSearch2](std::pair<ScrewWrist, std::vector<Length>> const& item) {
		return (screwWristToSearch2 == item.first);
	});
	const auto lengthItr1 = find(screwWristItr1->second.begin(), screwWristItr1->second.end(), screwWristPropertySearch.length);
	const auto lengthItr2 = find(screwWristItr2->second.begin(), screwWristItr2->second.end(), screwWristPropertySearch.length);
	if (lengthItr1 == screwWristItr1->second.end() && lengthItr2 == screwWristItr2->second.end()) {
		if (updateProperty == UpdatePropertyType::UpdateLength) {
			if (screwWristPropertySearch.threadFullness != ThreadFullness::BadThreadFulness) {
				screwWristPropertySearch.threadFullness = ThreadFullness::BadThreadFulness;
				screwWristPropertySearch.screwNeedThreadFullness = toolNames_[1];
			}
		}
		else {
			screwWristPropertySearch.length = Length::BadLength;
			screwWristPropertySearch.screwNeedLength = toolNames_[1];
		}
		return false;
	}
	else {
		return true;
	}
	return true;
}
void ScrewTrauma::searchThreadFulness(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	for (const auto& screwWrist : screwWristData) {
		for (const auto& threadFulness : ThreadFullnessToString[screwWrist.first.threadFullness]) {
			if (speechTranscription.find(threadFulness) != string::npos) {
				toolPropertySearch.screwWristPropertySearch.threadFullness = screwWrist.first.threadFullness;
				toolPropertySearch.screwWristPropertySearch.screwNeedThreadFullness = "";
				return;
			}
		}
	}
	toolPropertySearch.screwWristPropertySearch.screwNeedThreadFullness = toolNames_[1];
}


void ScrewTrauma::searchLength(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	for (const auto& screwWrist : screwWristData) {
		for (const auto& length : screwWrist.second) {
			if (speechTranscription.find(lengthToString[length]) != string::npos) {
				toolPropertySearch.screwWristPropertySearch.length = length;
				toolPropertySearch.screwWristPropertySearch.screwNeedLength = "";
				return;
			}
		}
	}
	//we put index 0 : because at the index one, we put the name "screw" which is sufficient to perform the next search for the length
	toolPropertySearch.screwWristPropertySearch.screwNeedLength = toolNames_[1];
}

void ScrewTrauma::searchHeadType(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const {
	for (const auto& screwWrist : screwWristData) {
		for (const auto& headType : headTypeToString[screwWrist.first.headType]) {
			if (speechTranscription.find(headType) != string::npos) {
				toolPropertySearch.screwWristPropertySearch.headType = screwWrist.first.headType;
				toolPropertySearch.screwWristPropertySearch.screwNeedHeadType = "";
				return;
			}
		}
	}
	toolPropertySearch.screwWristPropertySearch.screwNeedHeadType = toolNames_[1];
}

void ScrewTrauma::searchLengthAnkle(const string& speechTranscription, ToolPropertySearch& toolPropertySearch) const {
	const auto screwAnkleItr = screwAnkleData.find(toolPropertySearch.screwAnklePropertySearch.threadType);
	if (screwAnkleItr != screwAnkleData.end()) {
		for (const auto& length : screwAnkleItr->second)
		{
			if (speechTranscription.find(lengthToString[length]) != string::npos)
			{
				toolPropertySearch.screwAnklePropertySearch.length = length;
				toolPropertySearch.screwAnklePropertySearch.screwNeedLength = "";
				return;
			}

		}
	}
	toolPropertySearch.screwAnklePropertySearch.screwNeedLength = toolNames_[1];

}

void ScrewTrauma::mapLengthToThreadType(const string& speechTranscription, ToolPropertySearch& toolPropertySearch)const {
	for (const auto& kv : screwAnkleData) {
		if (speechTranscription.find(ThreadTypeToString[kv.first]) != string::npos) {
			if (std::find(kv.second.begin(), kv.second.end(), toolPropertySearch.screwAnklePropertySearch.length) != kv.second.end()) {
				toolPropertySearch.screwAnklePropertySearch.threadType = kv.first;
				toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType = "";
				return;
			};
		}
	}
	toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType = toolNames_[1];
}

