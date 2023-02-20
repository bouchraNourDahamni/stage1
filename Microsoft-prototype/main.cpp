#include <string>
#include <iostream>
#include "filterSpeech.h"
#include "SpeechRecognizer.h"
#include "SurgeryType.h"
#include "Data.h"
using namespace std;

int main()
{
	SurgeryType surgeryType = {};
	cout << "Please choose the type of operation you want to do. We offer three different types: Spine, Trauma, Reconstruction." << endl;
	std::cin >> surgeryType;
	if (surgeryType == SurgeryType::Trauma) {
		TraumaBoneType traumaBoneType = {};
		cout << "Please choose the type of bone" << endl;
		cout << "For this type of surgery : you have two options Ankle and Wrist" << endl;
		std::cin >> traumaBoneType;
		toolListTrauma.push_back(unique_ptr<ScrewTrauma>(new ScrewTrauma({ "screwdriver" ,"screw" }, ToolHandleType::Pistol, traumaBoneType)));
		if (traumaBoneType == TraumaBoneType::Ankle) {
			toolListTrauma.push_back(unique_ptr<ToolWithSizes>(new ToolWithSizes({ "plate" }, ToolHandleType::Straight, { Length::Three,Length::Four,Length::Five,Length::Six,Length::Seven,Length::Eight,Length::Nine })));
		}
		if (traumaBoneType == TraumaBoneType::Wrist) {
			toolListTrauma.push_back(unique_ptr<ToolWithSizes>(new ToolWithSizes({ "plate" }, ToolHandleType::Straight, { Length::Seven,Length::Eight,Length::Ten,Length::Thirteen })));
		}
	}
	if (surgeryType == SurgeryType::Reconstruction) {
		BoneTypeReconstruction boneTypeReconstruction = {};
		cout << "Please choose the type of bone" << endl;
		cout << "For this type of surgery : you have three options Patellar and Femoral and other bones " << endl;
		std::cin >> boneTypeReconstruction;
		if (boneTypeReconstruction == BoneTypeReconstruction::OtherBones) {
			toolListReconstruction.push_back(unique_ptr<ToolWithSizes>(new ToolWithSizes({ "drill" }, ToolHandleType::Pistol, { Length::TwoPointFive,Length::ThreePointTwo ,Length::FourPointThree,Length::Eight,Length::Twelve,Length::SixteenPointSeven })));
		}
		if (boneTypeReconstruction == BoneTypeReconstruction::Femoral || boneTypeReconstruction == BoneTypeReconstruction::Patellar) {
			toolListReconstruction.push_back(unique_ptr<ToolWithSizes>(new ToolWithSizes({ "drill" }, ToolHandleType::Pistol, { Length::SixPointFour })));
		}
	}
	FilterSpeech filter(surgeryType);
	try
	{
		recognizeSpeech(filter);
	}
	catch (exception e)
	{
		cout << e.what();
	}
	return 0;
}