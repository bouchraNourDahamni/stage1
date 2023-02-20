#pragma once
#include "../filterSpeech.h"
#include "../StringData.h"

TEST(FilterSpeechTestTraumaAnkle, ToolPropertySearch)
{
	SurgeryType surgery = SurgeryType::Trauma;
	const string EmptyString = "";
	ScrewWristPropertySearch screwWristPropertySearch = { EmptyString , EmptyString , EmptyString ,EmptyString ,HeadType::BadHeadType ,ThreadFullness::BadThreadFulness, Length::BadLength};
	ScrewSpinePropertySearch screwSpinePropertySearch = { DiameterScrew::BadDiameter,Length::BadLength,EmptyString };
	ScrewAnklePropertySearch screwAnklePropertySearch = { EmptyString , ThreadType::BadThreadType , Length::BadLength , EmptyString , EmptyString };
	ToolPropertySearch toolPropertySearch = { screwWristPropertySearch, screwAnklePropertySearch , screwSpinePropertySearch ,ToolHandleType::BadToolHandle, Length::BadLength, false ,EmptyString };
	TraumaBoneType traumaBoneType = TraumaBoneType::Ankle;
	toolListTrauma.push_back(unique_ptr<ScrewTrauma>(new ScrewTrauma({"screwdriver", "screw" }, ToolHandleType::Pistol, traumaBoneType)));
	FilterSpeech filter(surgery);

	filter.searchProperties("screwdriver", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "screw");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::BadThreadType);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "screw");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("cortical", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "screw");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::Cortical);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("30", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::Cortical);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::Thirty);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw cancellous 30 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::Cancellous);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::Thirty);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw cancellous", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::Cancellous);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "screw");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("10 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::Cancellous);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "screw");
	filter.reinitPropertySearch(toolPropertySearch);


	filter.searchProperties("32", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::Cancellous);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::ThirtyTwo);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw 10 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "screw");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::BadThreadType);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::Ten);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("cancellous", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "screw");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::BadThreadType);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::Ten);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("cortical", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedThreadType, "");
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.threadType, ThreadType::Cortical);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.length, Length::Ten);
	EXPECT_EQ(toolPropertySearch.screwAnklePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	 
}
