#pragma once
#include "ScrewSizes.h"
#include "StringData.h"
#include "map"

std::map< ThreadFullness, std::vector<std::string>> ThreadFullnessToString = {
	{{ThreadFullness::FullyThreaded} , {"fully" , "full"}},
	{{ThreadFullness::PartiallyThreaded} , {"partially" , "part"} },
};

std::map< HeadType, std::vector<std::string>> headTypeToString = {
	{{HeadType::NonLockingCross} , {"nonlockingCross" , "nonlocking" , "nonlocking" , "non loocking" , "none looking" , "non loock" , "not looking", "know looking", "non locking" , "non looking"}},
	{{HeadType::Locking} , {"locking" , "look"} },
};

std::map<ThreadType, std::string> ThreadTypeToString = {
	{ThreadType::Cancellous , "cancellous"},
	{ThreadType::Cortical , "cortical" },
};

std::map<Length, std::string> lengthToString = {
	{Length::Sixteen,"16"},
	{Length::Eighteen ,"18"},
	{Length::Twenty,"20"},
	{Length::TwentyTwo ,"22"},
	{Length::TwentyFour,"24"},
	{Length::Twentysix,"26"},
	{Length::Ten,"10"},
	{Length::Twelve,"12"},
	{Length::Fourteen,"14"},
	{Length::TwentyEight,"28"},
	{Length::Thirty,"30"},
	{Length::ThirtyTwo,"32"},
	{Length::ThirtyFour,"34"},
	{Length::Thirtysix,"36"},
	{Length::ThirtyEight,"38"},
	{Length::Fourteen ,"14"},
	{Length::ThirtyFive,"35"},
	{Length::Fourty ,"40"},
	{Length::FourtyFive ,"45"},
	{Length::Fifty ,"50"},
	{Length::FiftyFive,"55"},
	{Length::Sixty,"60"},
	{Length::ThirtyTwo , "22"},
	{Length::ThirtyFive , "35"},
	{Length::FourtySix , "46"},
	{Length::FourtyTwo , "42"},
	{Length::FourtyFour , "44"},
	{Length::FourtyEight , "48"},
	{Length::FiftyFive , "55"},
	{Length::FiftyFour , "54"},
	{Length::FiftyTwo , "52"},
	{Length::FiftySix , "56"},
	{Length::FiftyEight , "58"},
	{Length::Sixty , "60"},
	{Length::SixtyFour , "64"},
	{Length::SixtySix , "66"},
	{Length::SixtyEight , "68"},
	{Length::Seventy , "70"},
	{Length::SeventyFive , "75"},
	{Length::SixtyFive , "65"},
	{Length::Eighty , "80"},
    {Length::Eleven , "11"},
	{Length::Fifteen, "15"},
	{Length::Nineteen, "19"},
	{Length::Three, "3"},
	{Length::ThreePointFive , "3.5"},
	{Length::ThreePointEight , "3.8"},
	{Length::Cylinder , "cylinder"},
	{Length::OnePointEight , "1.8"},
	{Length::TwoPointThree , "2.3"},
	{Length::TwoPointFive , "2.5"},
	{Length::One, "1"},
	{Length::Two , "2"},
	{Length::Four , "4"},
	{Length::Five , "5"},
	{Length::Seven , "7"},
	{Length::TwoPointEight , "2.8"},
	{Length::ThreePointTwo, "3.2"},
	{Length::FourPointFive , "4.5"},
	{Length::Six , "6"},
	{Length::Eight , "8"},
	{Length::Nine , "9"},
	{Length::Thirteen, "13"},
	{Length::SixPointFour, "6.4"},
	{Length::FourPointThree , "4.3"},
	{Length::SixteenPointSeven, "4.3"},

};

std::map<DiameterScrew, std::string> diameterToString = {
	{DiameterScrew::ThreePointFive , "3.5"},
	{DiameterScrew::FourPointFive , "4.5"},
	{DiameterScrew::FivePointFive , "5.5"},
	{DiameterScrew::SixPointFive , "6.5"},
	{DiameterScrew::SevenPointFive , "7.5"},
};

std::map< ToolHandleType, std::string > ToolHandleToString = {
{ToolHandleType::ActuatedStraight, "ActuatedStraight"},
{ToolHandleType::StraightClosing, "StraightClosing"},
{ToolHandleType::AngledClosing,"AngledClosing"},
{ToolHandleType::Straight, "Straight"},
{ToolHandleType::Pistol, "Pistol"},
{ToolHandleType::StraightClosing, "StraightClosing"},
{ToolHandleType::BadToolHandle, "BadToolHandle"},
};
