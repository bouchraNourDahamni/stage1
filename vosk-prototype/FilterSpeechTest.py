from ToolPropertySearch import ToolPropertySearch
from ToolPropertySearch import ScrewSpinePropertySearch
from ToolPropertySearch import ScrewWristPropertySearch
from ToolHandleType import ToolHandleType
from ToolProperties import Length
from ToolProperties import HeadType
from ToolProperties import ThreadFullness
from ToolProperties import DiameterScrew
from filterSpeech import FilterSpeech
from ToolPropertySearch import ScrewAnklePropertySearch
from ToolProperties import ThreadType
from SurgeryType import SurgeryType
import unittest


class TestStringMethods(unittest.TestCase):
    def test_filter_speech(self):
        filter = FilterSpeech(SurgeryType.Spine.value)
        screw_spine_property_search = ScrewSpinePropertySearch(DiameterScrew.BadDiameter, Length.BadLength, "", "")
        screw_wrist_property_search = ScrewWristPropertySearch("", "", "", "",
                                                               HeadType.BadHeadType, ThreadFullness.BadThreadFulness,
                                                               Length.BadLength)
        screw_ankle_property_search = ScrewAnklePropertySearch("", ThreadType.BadThreadType, Length.BadLength, "", "")
        tool_property_search = ToolPropertySearch(screw_wrist_property_search, screw_ankle_property_search,
                                                  screw_spine_property_search,
                                                  ToolHandleType.BadToolHandle,
                                                  Length.BadLength, False, "", "",False,"")
        filter.search_properties("ball tip probe", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Straight)
        self.assertEqual(tool_property_search.toolneedsize_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me scalpel", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.ActuatedStraight)
        self.assertEqual(tool_property_search.toolneedsize_, "scalpel")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me drill two point three", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.ActuatedStraight)
        self.assertEqual(tool_property_search.toolneedsize_, "")
        self.assertEqual(tool_property_search.length_, Length.TwoPointThree)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me scalpel ten", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.ActuatedStraight)
        self.assertEqual(tool_property_search.toolneedsize_, "")
        self.assertEqual(tool_property_search.length_, Length.Ten)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me drill", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.ActuatedStraight)
        self.assertEqual(tool_property_search.toolneedsize_, "drill")
        self.assertEqual(tool_property_search.length_, Length.BadLength)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("one point eight", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.ActuatedStraight)
        self.assertEqual(tool_property_search.toolneedsize_, "")
        self.assertEqual(tool_property_search.length_, Length.OnePointEight)
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("give me screwdriver", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "screw")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "screw")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("three point five", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.ThreePointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "screw")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("ten", tool_property_search)
        self.assertEqual(tool_property_search.tool_handle_, ToolHandleType.Pistol)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.ThreePointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.Ten)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("screw four point five thirty ", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.FourPointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.Thirty)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("screw four point five sixteen ", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.FourPointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "screw")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("thirty five", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.FourPointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.ThirtyFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("screw four point five", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.FourPointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "screw")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("sixty", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.FourPointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.BadLength)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "screw")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("thirty", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.FourPointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.Thirty)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties(" screw forty five", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.BadDiameter)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.FourtyFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "screw")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("three point five", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.BadDiameter)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.FourtyFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "screw")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "")
        filter.reinit_property_search(tool_property_search)

        filter.search_properties("seven point five", tool_property_search)
        self.assertEqual(tool_property_search.screw_spine_property_search_.diameter_, DiameterScrew.SevenPointFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.length_, Length.FourtyFive)
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_diameter_, "")
        self.assertEqual(tool_property_search.screw_spine_property_search_.screw_need_length_, "")
        filter.reinit_property_search(tool_property_search)


if __name__ == '__main__':
    unittest.main()
