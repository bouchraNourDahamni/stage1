from enum import Enum


class SurgeryType(Enum):
    Trauma = "Trauma"
    Spine = "Spine"
    Reconstruction = "Reconstruction"


class TraumaBoneType(Enum):
    Ankle = "Ankle"
    Wrist = "Wrist"


class BoneTypeReconstruction(Enum):
    Patellar = "Patellar"
    Femoral = "Femoral"
    OtherBones = "Other Bones"
