#pragma once 
#include <iostream>
using namespace std;

enum class SurgeryType {
	Trauma,
	Spine,
	Reconstruction
};

enum class TraumaBoneType {
	Ankle,
	Wrist
};

enum class BoneTypeReconstruction {
	Patellar ,
	Femoral,
	OtherBones,
};

std::istream& operator>>(std::istream& is, SurgeryType& suregeryType);
std::istream& operator>>(std::istream& is, TraumaBoneType&  traumaBoneType);
std::istream& operator>>(std::istream& is, BoneTypeReconstruction& boneTypeReconstruction);