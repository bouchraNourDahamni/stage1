#include "SurgeryType.h" 
#include <iostream>
#include <istream>
#include <string>
using namespace std;
//Change the name to SurgeryConfiguration
std::istream& operator>>(std::istream& is, SurgeryType& surgery)
{
	std::string name;
	is >> name;
	if (name == "Trauma")
		surgery = SurgeryType::Trauma;
	else if (name == "Spine")
		surgery = SurgeryType::Spine;
	else if (name == "Reconstruction")
		surgery = SurgeryType::Reconstruction;
	return is;

}

std::istream& operator>>(std::istream& is, TraumaBoneType& traumaBoneType) {
	std::string name;
	is >> name;
	if (name == "Ankle")
		traumaBoneType = TraumaBoneType::Ankle;
	else if (name == "Wrist")
		traumaBoneType = TraumaBoneType::Wrist;
	return is;
};

std::istream& operator>>(std::istream& is, BoneTypeReconstruction& boneTypeReconstruction) {
	std::string name;
	is >> name;
	if (name == "Patellar")
		boneTypeReconstruction = BoneTypeReconstruction::Patellar;
	else if (name == "Femoral")
		boneTypeReconstruction = BoneTypeReconstruction::Femoral;
	else if(name == "Other Bones")
		boneTypeReconstruction = BoneTypeReconstruction::OtherBones;
	return is;
};