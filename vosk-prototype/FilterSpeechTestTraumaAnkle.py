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
from ToolProperties import ThreadType
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
        trauma_bone_type = TraumaBoneType.Ankle.value
        Data.toolListTrauma.append(ScrewTrauma(["screwdriver", "screw"], ToolHandleType.Pistol, trauma_bone_type))
        filter = FilterSpeech(SurgeryType.Trauma.value)

        filter.search_properties("screwdriver", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.BadThreadType)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "screw")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "screw")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("cortical", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.Cortical)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "screw")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("thirty", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.Cortical)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.Thirty)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("screw cancellous thirty", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.Cancellous)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.Thirty)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("screw cancellous", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.Cancellous)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "screw")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("ten", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.Cancellous)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "screw")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("thirty two", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.Cancellous)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.ThirtyTwo)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("screw ten", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.BadThreadType)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.Ten)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "screw")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("cancellous", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.BadThreadType)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.Ten)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "screw")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("cortical", tool_property_search)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.thread_type_, ThreadType.Cortical)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.length_, Length.Ten)
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_, "")
        self.assertEqual(tool_property_search.screw_ankle_property_search_.screw_need_length_, "")
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        filter.reinit_property_search(tool_property_search)


if __name__ == '__main__':
    unittest.main()
