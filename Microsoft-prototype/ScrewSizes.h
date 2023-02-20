#pragma once
#include <string>
#include <vector>


enum class ThreadFullness {
	BadThreadFulness,
	PartiallyThreaded,
	FullyThreaded
};

enum class Length {
	BadLength,
	Sixteen,
	Eighteen,
	Twenty,
	TwentyTwo,
	TwentyFour,
	Twentysix,
	TwentyEight,
	Ten,
	Twelve,
	Fourteen,
	ThirtyTwo,
	Thirty,
	ThirtyFive,
	ThirtyFour,
	ThirtyEight,
	Thirtysix,
	FourtyFive,
	FourtySix,
	FourtyTwo,
	FourtyFour,
	FourtyEight,
	Fourty,
	FiftyFive,
	FiftyFour,
	Fifty,
	FiftyTwo,
	FiftySix,
	FiftyEight,
	Sixty,
	SixtyFour,
	SixtySix,
	SixtyEight,
	Seventy,
	SeventyFive,
	SixtyFive,
	Eighty,
	Eleven,
	Fifteen,
	Nineteen,
	Three,
	ThreePointFive,
	ThreePointEight,
	Cylinder,
	OnePointEight,
	TwoPointThree,
	TwoPointFive,
	One,
	Two,
	Four,
	Five,
	Seven,
	TwoPointEight,
	ThreePointTwo,
	FourPointFive,
	Six,
	Eight,
	Nine,
	Thirteen,
	SixPointFour,
	FourPointThree,
	SixteenPointSeven,
};
enum class DiameterScrew {
	ThreePointFive,
	FourPointFive,
	FivePointFive,
	SixPointFive,
	SevenPointFive,
	BadDiameter
};

enum class UpdatePropertyType {
	UpdateHeadType,
	UpdateThreadFulness,
	UpdateLength,
};

enum class HeadType {
	BadHeadType,
	NonLockingCross,
	Locking
};
enum class ThreadType {
	BadThreadType,
	Cancellous,
	Cortical
};

struct ScrewSpine
{
	std::string diameter;
	std::vector<std::string> length;
};

struct ScrewWrist {
	ThreadFullness threadFullness;
	HeadType headType;
	bool operator<(const ScrewWrist& screwWrist) const
	{
		return (threadFullness < screwWrist.threadFullness&& headType < screwWrist.headType);
	}
	bool operator==(const ScrewWrist& screwWrist) const
	{
		return (threadFullness == screwWrist.threadFullness && headType == screwWrist.headType);
	}
};

struct ScrewAnkle {
	ThreadType threadType;
	std::vector<std::string> length;
};




