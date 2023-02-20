#pragma once

#include "../filterSpeech.h"
#include "../StringData.h"
#include "../Data.h"
#include "map"
using namespace std;

TEST(FilterSpeechTest, ToolPropertySearch)
{
	SurgeryType surgery = SurgeryType::Spine;
	FilterSpeech filter(surgery);
	const string EmptyString = "";
	ScrewWristPropertySearch screwWristPropertySearch = { EmptyString , EmptyString , EmptyString ,EmptyString ,HeadType::BadHeadType ,ThreadFullness::BadThreadFulness, {} };
	ScrewSpinePropertySearch screwSpinePropertySearch = {DiameterScrew::BadDiameter,Length::BadLength,EmptyString};
	ScrewAnklePropertySearch screwAnklePropertySearch = { EmptyString , ThreadType::BadThreadType , Length::BadLength , EmptyString , EmptyString };
	ToolPropertySearch toolPropertySearch = { screwWristPropertySearch, screwAnklePropertySearch , screwSpinePropertySearch ,ToolHandleType::BadToolHandle,Length::BadLength, false ,EmptyString };

	filter.searchProperties("ball tip probe", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Straight);
	EXPECT_EQ(toolPropertySearch.toolNeedSize, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me scalpel", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::ActuatedStraight);
	EXPECT_EQ(toolPropertySearch.toolNeedSize, "scalpel");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me drill 2.3", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::ActuatedStraight);
	EXPECT_EQ(toolPropertySearch.toolNeedSize, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me scalpel 10 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::ActuatedStraight);
	EXPECT_EQ(toolPropertySearch.length,Length::Ten);
	EXPECT_EQ(toolPropertySearch.toolNeedSize, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("give me drill", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::ActuatedStraight);
	EXPECT_EQ(toolPropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.toolNeedSize, "drill");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("1.8", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::ActuatedStraight);
	EXPECT_EQ(toolPropertySearch.length, Length::OnePointEight);
	EXPECT_EQ(toolPropertySearch.toolNeedSize, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "screw");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "screw");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("3.5", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter, DiameterScrew::ThreePointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "screw");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("10", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter, DiameterScrew::ThreePointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::Ten);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw 4.5 30 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter, DiameterScrew::FourPointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::Thirty);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw 4.5 55 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter, DiameterScrew::FourPointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "screw");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw 4.5 35 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter, DiameterScrew::FourPointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::ThirtyFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw 4.5 ", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter,DiameterScrew::FourPointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "screw");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("60", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter, DiameterScrew::FourPointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length,Length::BadLength);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "screw");
	filter.reinitPropertySearch(toolPropertySearch);


	filter.searchProperties("30", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter,DiameterScrew::FourPointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::Thirty);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("screw 45", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "screw");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter,DiameterScrew::BadDiameter);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::FourtyFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("3.5", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "screw");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter,DiameterScrew::BadDiameter);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::FourtyFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

	filter.searchProperties("7.5", toolPropertySearch);
	EXPECT_EQ(toolPropertySearch.toolHandle, ToolHandleType::Pistol);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedDiameter, "");
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.diameter,DiameterScrew::SevenPointFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.length, Length::FourtyFive);
	EXPECT_EQ(toolPropertySearch.screwSpinePropertySearch.screwNeedLength, "");
	filter.reinitPropertySearch(toolPropertySearch);

}