#pragma once

#include "../filterSpeech.h"
#include "../StringData.h"

TEST(FilterSpeechTestTrauma, ToolPropertySearch)
{
	SurgeryType surgery = SurgeryType::Trauma;
	const string EmptyString = "";
	ScrewWristPropertySearch screwWristPropertySearch = { EmptyString , EmptyString , EmptyString ,EmptyString ,HeadType::BadHeadType ,ThreadFullness::BadThreadFulness, Length::BadLength};
	ScrewSpinePropertySearch screwSpinePropertySearch = { DiameterScrew::BadDiameter,Length::BadLength,EmptyString };
	ScrewAnklePropertySearch screwAnklePropertySearch = { EmptyString , ThreadType::BadThreadType , Length::BadLength , EmptyString , EmptyString };
	ToolPropertySearch toolPropertySearch = { screwWristPropertySearch, screwAnklePropertySearch , screwSpinePropertySearch ,ToolHandleType::BadToolHandle, Length::BadLength, false ,EmptyString };
	TraumaBoneType traumaBoneType = TraumaBoneType::Wrist;
	toolListTrauma.push_back(unique_ptr<ScrewTrauma>(new ScrewTrauma({ "screwdriver" ,"screw" }, ToolHandleType::Pistol, traumaBoneType)));
	toolListTrauma.push_back(unique_ptr<ToolWithSizes>(new ToolWithSizes({ "plate" }, ToolHandleType::Straight, { Length::Three,Length::Four,Length::Five,Length::Six,Length::Seven,Length::Eight,Length::Nine })));
	FilterSpeech filter(surgery);
	//Test Case for ScrewTrauma
	//Case one : The Head Type is already mentioned,but length and ThreadFulness are not
	filter.searchProperties("give me screw driver nonlocking", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("partially 16 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me screw driver locking", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("partially 10", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::Locking);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::BadThreadFulness);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("partially 20", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::Locking);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Twenty);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	filter.reinitPropertySearch(toolPropertySearch);

	//Case Two : Property Length is already mentioned , but HeadType and ThreadFulness are not
	filter.searchProperties("give me screw driver 16 ", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("not looking partially.", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	filter.reinitPropertySearch(toolPropertySearch);
	
	filter.searchProperties("give me screw driver 16 ", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("partially looking", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::BadHeadType);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::BadThreadFulness);
	filter.reinitPropertySearch(toolPropertySearch);
	
	filter.searchProperties("partially not looking", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	filter.reinitPropertySearch(toolPropertySearch);

	//Case Three : Property  Thread Fulllness is already mentioned, but headType and Length are not
	filter.searchProperties("give me screw driver partially ", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("locking 16", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::BadHeadType);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::BadLength);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("not looking 16", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	//Case Four:  Property Head Type and Length is already mentioned and ThreadFulness are not 
	filter.searchProperties("give me screw driver nonlocking 16 ", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("partially", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me screw driver nonlocking 16 ", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("fully", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::FullyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	//Case Five : Property Head Type and Thread Fulness is already mentioned, but length is not
	filter.searchProperties("give me screw driver partially nonlocking", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("16", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me screw driver partially nonlocking", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("12", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::BadLength);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me screw driver partially nonlocking", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("10", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::BadLength);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("16", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);


	//Case Six :  Property Length and Thread Fulness is already mentionned ,but HeadType is not 
	filter.searchProperties("give me screw driver partially 16 ", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("nonlocking", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me screw driver partially 16 ", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("locking", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::BadHeadType);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("nonlocking", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	//Case Seven : Property Lenght and Thread Fulness and Head Type are not already mentioned
	/////
	filter.searchProperties("give me screw driver partially 16 not looking", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("give me screw driver partially", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("16", toolPropertySearch);
	filter.reinitPropertySearch(toolPropertySearch);
	filter.searchProperties("nonlocking", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	//we set the ThreadFulness and we don't set the length because the length 10 and ThreadFulness Partially doesn't exist
	filter.searchProperties("give me screw driver partially 10", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::BadHeadType);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedLength, "screw");
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedHeadType, "screw");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("nonlocking 16", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me screw driver ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::BadHeadType);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::BadThreadFulness);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedLength, "screw");
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedHeadType, "screw");
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedThreadFullness, "screw");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("partially non locking 16 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedLength, "");
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedHeadType, "");
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedThreadFullness, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw partially non locking 36 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedLength, "screw");
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedHeadType, "");
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.screwNeedThreadFullness, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("16 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.threadFullness, ThreadFullness::PartiallyThreaded);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.headType, HeadType::NonLockingCross);
	EXPECT_EQ(toolPropertySearch.screwWristPropertySearch.length, Length::Sixteen);
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("plate 3", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Straight);
	EXPECT_EQ(toolPropertySearch.length, Length::Three);
	filter.reinitPropertySearch(toolPropertySearch);

	toolListTrauma.pop_back();
	toolListTrauma.pop_back();
}
