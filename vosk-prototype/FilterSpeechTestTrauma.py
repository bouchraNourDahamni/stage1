from ToolPropertySearch import ToolPropertySearch
from ToolPropertySearch import ScrewSpinePropertySearch
from ToolPropertySearch import ScrewWristPropertySearch
from ToolHandleType import ToolHandleType
from ToolProperties import Length
from ToolWithSizes import ToolWithSizes
from ToolProperties import HeadType
from ToolProperties import ThreadFullness
from ToolProperties import DiameterScrew
from ToolProperties import ThreadType
from filterSpeech import FilterSpeech
from ScrewTrauma import ScrewTrauma
import Data
from ToolPropertySearch import ScrewAnklePropertySearch
from SurgeryType import SurgeryType
from SurgeryType import TraumaBoneType
import unittest


class TestStringMethods(unittest.TestCase):
    def test_filter_speech_trauma(self):
        screw_spine_property_search = ScrewSpinePropertySearch(DiameterScrew.BadDiameter, Length.BadLength, "", "")
        screw_wrist_property_search = ScrewWristPropertySearch("", "", "", "",
                                                               HeadType.BadHeadType, ThreadFullness.BadThreadFulness,
                                                               Length.BadLength)
        screw_ankle_property_search = ScrewAnklePropertySearch("", ThreadType.BadThreadType, Length.BadLength, "", "")

        tool_property_search = ToolPropertySearch(screw_wrist_property_search, screw_ankle_property_search,
                                                  screw_spine_property_search,
                                                  ToolHandleType.BadToolHandle,
                                                  Length.BadLength, False, "", "",False,"")
        trauma_bone_type = TraumaBoneType.Wrist.value
        Data.toolListTrauma.append(ScrewTrauma(["screwdriver", "screw"], ToolHandleType.Pistol, trauma_bone_type))
        Data.toolListTrauma.append(ToolWithSizes(["plate"], ToolHandleType.Straight,
                                                 [Length.Three, Length.Four, Length.Five, Length.Six, Length.Seven,
                                                  Length.Eight, Length.Nine]))
        filter = FilterSpeech(SurgeryType.Trauma.value)
        # Test Case for ScrewTrauma
        # Case one: The Head Type is already mentioned, but length and ThreadFulness are not
        filter.search_properties("give me screw driver nonlocking", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("partially sixteen", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me screw driver locking", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("partially ten", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.Locking)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.BadThreadFulness)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.BadLength)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("partially twenty", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.Locking)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Twenty)
        filter.reinit_property_search(tool_property_search)

        # Case Two: Property Length is already mentioned, but HeadType and ThreadFulness are not

        filter.search_properties("give me screw driver sixteen", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("not looking partially.", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me screw driver sixteen", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("partially looking", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.BadHeadType)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.BadThreadFulness)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("partially not looking", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        # Case Three: Property Thread Fulllness is already mentioned, but headType and Length are not

        filter.search_properties("give me screw driver partially ", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("locking sixteen", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.BadHeadType)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.BadLength)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("not looking sixteen", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        # Case Four: Property Head Type and Length is already mentioned and ThreadFulness are not

        filter.search_properties("give me screw driver nonlocking sixteen", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("partially", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me screw driver nonlocking sixteen ", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("fully", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.FullyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        # Case Five: Property Head Type and Thread Fulness is already mentioned, but length is not

        filter.search_properties("give me screw driver partially nonlocking", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("sixteen", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me screw driver partially nonlocking", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("twelve", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.BadLength)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me screw driver partially nonlocking", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("ten", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.BadLength)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("sixteen", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        # Case Six: Property Length and Thread Fulness is already mentionned, but HeadType is not

        filter.search_properties("give me screw driver partially sixteen", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("nonlocking", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me screw driver partially sixteen", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("locking", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.BadHeadType)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("nonlocking", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        # Case Seven: Property Lenght and Thread Fulness and Head Type are not already mentioned

        filter.search_properties("give me screw driver partially sixteen not looking", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("give me screw driver partially", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("sixteen", tool_property_search)
        filter.reinit_property_search(tool_property_search)
        filter.search_properties("nonlocking", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        # we set the ThreadFulness and we don't set the length because the length 10 and ThreadFulness Partially doesn't exist
        filter.search_properties("give me screw driver partially ten", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.BadHeadType)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_length_, "screw")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_headType_, "screw")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("nonlocking sixteen", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me screw driver", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.BadHeadType)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.BadThreadFulness)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_length_, "screw")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_headType_, "screw")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_thread_fullness_, "screw")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("partially non locking sixteen", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_length_, "")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_headType_, "")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_thread_fullness_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("screw partially non locking thirty six", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_length_, "screw")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_headType_, "")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_thread_fullness_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("sixteen", tool_property_search)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.head_type_, HeadType.NonLockingCross)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.thread_fullness_,
                         ThreadFullness.PartiallyThreaded)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.length_, Length.Sixteen)
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_length_, "")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_headType_, "")
        self.assertEqual(tool_property_search.screw_wrist_property_search_.screw_need_thread_fullness_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("plate three", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Straight)
        self.assertEqual(tool_property_search.length_, Length.Three)
        filter.reinit_property_search(tool_property_search)

        # remove plate and screw that we append at the beginning of test suit
        Data.toolListTrauma.pop(4)
        Data.toolListTrauma.pop(3)


if __name__ == '__main__':
    unittest.main()
