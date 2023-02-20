from SurgeryType import SurgeryType
import Data
from ToolHandleType import ToolHandleType
from ToolProperties import Length
from ToolProperties import HeadType
from ToolProperties import DiameterScrew
from ToolProperties import ThreadFullness
from ToolProperties import ThreadType


def display_speech(text):
    print(text)


class FilterSpeech:
    def __init__(self, surgeryType):
        self.surgeryType_ = surgeryType

    def settoollist(self):
        if self.surgeryType_ == SurgeryType.Spine.value:
            return Data.toolListSpine
        elif self.surgeryType_ == SurgeryType.Trauma.value:
            return Data.toolListTrauma
        elif self.surgeryType_ == SurgeryType.Reconstruction.value:
            return Data.toolListReconstruction

    def search_properties(self, speech_transcription, tool_property_search):
        tool_list = self.settoollist()
        for tool in tool_list:
            if not tool_property_search.is_tool_found_:
                tool.search_property(speech_transcription, tool_property_search)
        self.search_features(speech_transcription, tool_property_search)

    def search_features(self, speech_transcription, tool_property_search):
        for feature in Data.otherFeatures:
            for name in feature.feature_names_:
                if speech_transcription.find(name) != -1:
                    tool_property_search.feature_action_ = feature.action_
                    tool_property_search.is_feature_found_ = True

    def reinit_property_search(self, tool_property_search):
        tool_property_search.is_tool_found_ = False
        tool_property_search.tool_handle_ = ToolHandleType.BadToolHandle
        if tool_property_search.length_ != Length.BadLength:
            tool_property_search.length_ = Length.BadLength
        if tool_property_search.screw_spine_property_search_.diameter_ != DiameterScrew.BadDiameter and \
                tool_property_search.screw_spine_property_search_.length_ != Length.BadLength:
            tool_property_search.screw_spine_property_search_.diameter_ = DiameterScrew.BadDiameter
            tool_property_search.screw_spine_property_search_.length_ = Length.BadLength
        if tool_property_search.screw_wrist_property_search_.length_ != Length.BadLength and \
                tool_property_search.screw_wrist_property_search_.head_type_ != HeadType.BadHeadType and \
                tool_property_search.screw_wrist_property_search_.thread_fullness_ != ThreadFullness.BadThreadFulness:
            tool_property_search.screw_wrist_property_search_.length_ = Length.BadLength
            tool_property_search.screw_wrist_property_search_.head_type_ = HeadType.BadHeadType
            tool_property_search.screw_wrist_property_search_.thread_fullness_ = ThreadFullness.BadThreadFulness
        if tool_property_search.screw_ankle_property_search_.thread_type_ != ThreadType.BadThreadType and \
                tool_property_search.screw_ankle_property_search_.length_ != Length.BadLength:
            tool_property_search.screw_ankle_property_search_.thread_type_ = ThreadType.BadThreadType
            tool_property_search.screw_ankle_property_search_.length_ = Length.BadLength
        if tool_property_search.feature_action_:
            tool_property_search.feature_action_ = ""
        if tool_property_search.feed_back_user_:
            tool_property_search.feed_back_user_ = ""
