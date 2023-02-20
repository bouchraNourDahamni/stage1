#pragma once
#include "Feature.h"
#include "Screw.h"
#include "ToolWithSizes.h"
#include "ScrewTrauma.h"
#include <iostream> 
#include <memory>
#include <map>
#include "Data.h"
#include "ToolHandleType.h"

const std::vector<Length> screwWristCommonLength = { Length::Ten,Length::Twelve, Length::Fourteen,Length::Sixteen,Length::Eighteen ,Length::Twenty,Length::TwentyTwo,Length::TwentyFour,Length::Twentysix,Length::TwentyEight,Length::Thirty,
Length::ThirtyTwo,Length::ThirtyFour,Length::Thirtysix,Length::ThirtyEight };

const  multimap< ScrewWrist, std::vector<Length>> screwWristData = { { { ThreadFullness::PartiallyThreaded , HeadType::NonLockingCross} ,{Length::Sixteen , Length::Eighteen ,Length::Twenty ,Length::TwentyTwo,Length::TwentyFour,Length::Twentysix}},
{{ ThreadFullness::FullyThreaded , HeadType::NonLockingCross },  screwWristCommonLength },
{{ ThreadFullness::PartiallyThreaded ,  HeadType::Locking }, {Length::Twenty , Length::TwentyTwo , Length::TwentyFour , Length::Twentysix }},
{{ ThreadFullness::FullyThreaded , HeadType::Locking },  screwWristCommonLength },
};

const std::vector <Length> screwSpineCommonLength = { Length::Thirty , Length::ThirtyFive ,
Length::Fourty , Length::FourtyFive , Length::Fifty , Length::FiftyFive , Length::Sixty };

const map<DiameterScrew, std::vector<Length>> ScrewSpineData = {
{DiameterScrew::ThreePointFive , {Length::Ten ,
Length::Twelve , Length::Fourteen , Length::Sixteen , Length::Eighteen , Length::Twenty ,
Length::TwentyTwo , Length::TwentyFour , Length::Twentysix, Length::TwentyEight , Length::Thirty}},
{DiameterScrew::FourPointFive , {Length::Thirty , Length::ThirtyFive ,
Length::Fourty , Length::FourtyFive , Length::Fifty}},
{DiameterScrew::FivePointFive , screwSpineCommonLength},
{DiameterScrew::SixPointFive ,screwSpineCommonLength},
{DiameterScrew::SevenPointFive ,screwSpineCommonLength},

};

extern const map<ThreadType, std::vector<Length>> screwAnkleData = {
{ThreadType::Cancellous , {Length::Thirty , Length::ThirtyTwo , Length::ThirtyFour , Length::Thirtysix ,
Length::ThirtyEight , Length::Thirty , Length::ThirtyTwo , Length::ThirtyFour, Length::Thirtysix,
Length::ThirtyEight , Length::Fourty , Length::FourtyTwo, Length::FourtyFour, Length::FourtySix ,
Length::FourtyEight , Length::Fifty, Length::FiftyTwo,
Length::FiftyFour , Length::FiftySix, Length::FiftyEight,Length::Sixty,
Length::SixtyFour , Length::SixtySix , Length::SixtyEight,Length::Seventy} ,
},
{ThreadType::Cortical , {Length::Ten , Length::Twelve , Length::Fourteen , Length::Sixteen ,
Length::Eighteen , Length::Twenty , Length::TwentyTwo , Length::TwentyFour, Length::Twentysix,
Length::TwentyEight , Length::Thirty , Length::ThirtyTwo, Length::ThirtyFour, Length::Thirtysix,
Length::ThirtyEight , Length::Fourty, Length::FourtyTwo,
Length::FourtyFour , Length::FourtySix, Length::FourtyEight,Length::Fifty,
Length::FiftyTwo , Length::FiftyFour , Length::FiftySix,Length::FiftyEight,
Length::Sixty , Length::SixtyFive , Length::Seventy,Length::SeventyFive , Length::Eighty}}
};

const std::vector<shared_ptr<Tool>> toolListSpine = {
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"scalpel"},ToolHandleType::ActuatedStraight,{Length::Ten ,Length::Eleven,Length::Twelve,Length::Fifteen,Length::Nineteen})) ,
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"awl"},ToolHandleType::StraightClosing, {Length::Three,Length::ThreePointFive, Length::ThreePointEight})),
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"burr"},ToolHandleType::ActuatedStraight, { Length::Cylinder, Length::Three ,Length::Four})),
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"drill"}, ToolHandleType::ActuatedStraight, {Length::OnePointEight, Length::TwoPointThree,Length::TwoPointFive,Length::ThreePointFive})),
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"kerrison punch" , "kerrison" , "punch" }, ToolHandleType::AngledClosing,{Length::One,Length::Two,Length::Three,Length::Four,Length::Five})),
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"pedicle finder" , "finder" , "pedicle" }, ToolHandleType::Straight,{Length::Two,Length::TwoPointEight,Length::ThreePointFive})),
   unique_ptr<Tool>(new Tool({"ball tip probe" , "probe" , "ball" , "tip" }, ToolHandleType::Straight)),
   unique_ptr<Tool>(new Tool({"ball tip probe" , "probe" , "ball" , "tip" },ToolHandleType::Straight)),
   unique_ptr<Screw>(new Screw({"screwdriver" ,"screw"} ,ToolHandleType::Pistol)),
   unique_ptr<Tool>(new Tool({"bone nibbler" , "nibbler" }, ToolHandleType::StraightClosing)),
   unique_ptr<Tool>(new Tool({"disc rongeur" , "disc"},ToolHandleType::Straight)),
   unique_ptr<Tool>(new Tool({"nerve hook", "nerve" , "hook"}, ToolHandleType::ActuatedStraight)),
   unique_ptr<Tool>(new Tool({"bone curette" , "curette" }, ToolHandleType::ActuatedStraight)),
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"pituitary rongeur","pituitary" , "rongeur"}, ToolHandleType::AngledClosing, {Length::One,Length::Two, Length::Three, Length::Four, Length::Five})),
};

std::vector<shared_ptr<Tool>> toolListTrauma = {
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"drill"}, ToolHandleType::Pistol,{Length::Two,Length::TwoPointFive,Length::ThreePointTwo,Length::ThreePointFive ,Length::FourPointFive})),
   unique_ptr<Tool>(new Tool({"depth gauge" , "depth" , "gauge" },ToolHandleType::ActuatedStraight)),
   unique_ptr<ToolWithSizes>(new ToolWithSizes({"plate"}, ToolHandleType::Straight ,{Length::Three ,Length::Four,Length::Five,Length::Six,Length::Seven,Length::Eight,Length::Nine})),
};

std::vector<shared_ptr<Tool>> toolListReconstruction = {
	unique_ptr<ToolWithSizes>(new ToolWithSizes({"saw"}, ToolHandleType::StraightClosing,{Length::Fourteen , Length::Eighteen})),
	unique_ptr<ToolWithSizes>(new ToolWithSizes({"burr"},ToolHandleType::ActuatedStraight, {Length::Cylinder,Length::Three,Length::Four})),
	unique_ptr<Tool>(new Tool({"bone nibbler" , "nibbler" }, ToolHandleType::StraightClosing)),
};

const std::vector<Feature> otherFeatures = {
   Feature({"Xray" , "ray" } , "I took an xray"),
   Feature({"green" , "remove green guide"} , "I removed green guide"),
   Feature({"flip" , "flip patient"} , "I flipped patient")
};

