from filterSpeech import FilterSpeech
import microphoneRecognition
from ToolProperties import Length
from ToolWithSizes import ToolWithSizes
from SurgeryType import SurgeryType
from SurgeryType import TraumaBoneType
from SurgeryType import BoneTypeReconstruction
import Data
from ToolHandleType import ToolHandleType
from ScrewTrauma import ScrewTrauma


def main():
    surgery_type = input("Please choose the type of operation you want to do. We offer three different types: Spine, "
                         "Trauma, Reconstruction \n.")
    if surgery_type == SurgeryType.Trauma.value:
        print("Please choose the type of bone \n")
        bone_type_trauma = input("For this type of surgery : you have two options Ankle and Wrist \n ")
        Data.toolListTrauma.append(ScrewTrauma(["screwdriver", "screw"], ToolHandleType.Pistol, bone_type_trauma))
        if bone_type_trauma == TraumaBoneType.Ankle.value:
            Data.toolListTrauma.append(ToolWithSizes(["plate"], ToolHandleType.Straight,
                                                     [Length.Three, Length.Four, Length.Five, Length.Six, Length.Seven,
                                                      Length.Eight, Length.Nine]))
        if bone_type_trauma == TraumaBoneType.Wrist.value:
            Data.toolListTrauma.append(ToolWithSizes(["plate"], ToolHandleType.Straight,
                                                     [Length.Seven, Length.Eight, Length.Ten, Length.Thirteen]))
    if surgery_type == SurgeryType.Reconstruction.value:
        print("Please choose the type of bone\n")
        bone_type_reconstruction = input("For this type of surgery : you have three options Patellar and Femoral and "
                                         "other bones \n ")
        if bone_type_reconstruction == BoneTypeReconstruction.OtherBones:
            Data.toolListReconstruction.append(ToolWithSizes(["drill"], ToolHandleType.Pistol,
                                                             [Length.TwoPointFive, Length.ThreePointTwo,
                                                              Length.FourPointThree, Length.Eight, Length.Twelve,
                                                              Length.SixteenPointSeven]))
        if bone_type_reconstruction == BoneTypeReconstruction.Femoral or bone_type_reconstruction == BoneTypeReconstruction.Patellar:
            Data.toolListReconstruction.append(ToolWithSizes(["drill"], ToolHandleType.Pistol, [Length.SixPointFour]))

    microphoneRecognition.recognize(True, FilterSpeech(surgery_type))


if __name__ == '__main__':
    main()
