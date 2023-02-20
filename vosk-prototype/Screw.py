from Tool import Tool
from ToolProperties import DiameterScrew
from ToolProperties import Length
import Data


class Screw(Tool):
    def __init__(self, tool_names, tool_handle):
        super().__init__(tool_names, tool_handle)

    def search_property(self, speech_transcription, tool_property_search):
        namefound = super(Screw, self).searchname(speech_transcription, tool_property_search)
        oldnamefoud = super(Screw, self).searcholdname(tool_property_search)
        if namefound or oldnamefoud:
            self.search_size(speech_transcription, tool_property_search)
            tool_property_search.is_tool_found_ = True

    def search_size(self, speech_transcription, tool_property_search):
        screw_spine_property_search = tool_property_search.screw_spine_property_search_
        if screw_spine_property_search.diameter_ != DiameterScrew.BadDiameter:
            return self.search_length(speech_transcription, tool_property_search)
        if screw_spine_property_search.length_ != Length.BadLength:
            return self.map_length_to_diameter(speech_transcription, tool_property_search)
        if screw_spine_property_search.diameter_ == DiameterScrew.BadDiameter and screw_spine_property_search.length_ == Length.BadLength:
            for screw_data in Data.ScrewSpineData:
                if speech_transcription.find(screw_data.value) != -1:
                    screw_spine_property_search.diameter_ = screw_data
                    screw_spine_property_search.screw_need_diameter_ = ""
                    self.search_length(speech_transcription, tool_property_search)
                    return
            for screw_data in Data.ScrewSpineData:
                for length in Data.ScrewSpineData[screw_data]:
                    if speech_transcription.find(length.value) != -1:
                        screw_spine_property_search.length_ = length
                        screw_spine_property_search.screw_need_length_ = ""
                        self.map_length_to_diameter(speech_transcription, tool_property_search)
                        return
            # we put index one :  because at the index one we put the name "screw" which is sufficient to perform the
            # next search for the length and diameter
            screw_spine_property_search.screw_need_diameter_ = self.tool_names[1]
            screw_spine_property_search.screw_need_length_ = self.tool_names[1]

    def search_length(self, speech_transcription, tool_property_search):
        screw_spine_property_search = tool_property_search.screw_spine_property_search_
        lengths = Data.ScrewSpineData.get(tool_property_search.screw_spine_property_search_.diameter_, False)
        if lengths:
            for length in lengths:
                if speech_transcription.find(length.value) != -1:
                    screw_spine_property_search.length_ = length
                    screw_spine_property_search.screw_need_length_ = ""
                    return
        # we put index one :  because at the index one we put the name "screw" which is sufficient to perform the
        # next search for the length
        screw_spine_property_search.screw_need_length_ = self.tool_names[1]

    def map_length_to_diameter(self, speech_transcription, tool_property_search):
        screw_spine_property_search = tool_property_search.screw_spine_property_search_
        for screwData in Data.ScrewSpineData:
            if speech_transcription.find(screwData.value) != -1:
                for length in Data.ScrewSpineData[screwData]:
                    if length == screw_spine_property_search.length_:
                        screw_spine_property_search.diameter_ = screwData
                        screw_spine_property_search.screw_need_diameter_ = ""
                        return
        # we put index one :  because at the index one we put the name "screw" which is sufficient to perform the
        # next search for the  diameter
        screw_spine_property_search.screw_need_diameter_ = self.tool_names[1]
