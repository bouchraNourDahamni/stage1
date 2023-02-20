from ToolHandleType import ToolHandleType
import FormatResult
from ToolProperties import Length
from ToolProperties import DiameterScrew
from ToolProperties import HeadType
from ToolProperties import ThreadFullness
from ToolProperties import ThreadType


class TextToSpeech:
    def __init__(self, toolPropertySearch):
        self.tool_property_search_ = toolPropertySearch

    def format_search_result(self):
        result_to_format = FormatResult.EmptyString
        if self.tool_property_search_.tool_handle_ != ToolHandleType.BadToolHandle:
            result_to_format += FormatResult.ToolHandeMessage + self.tool_property_search_.tool_handle_.value + FormatResult.EndLine
        if self.tool_property_search_.length_ != Length.BadLength:
            result_to_format += FormatResult.SizeMessage + self.tool_property_search_.length_.value + FormatResult.EndLine
        if self.tool_property_search_.toolneedsize_:
            result_to_format += FormatResult.SizeWait + self.tool_property_search_.toolneedsize_ + FormatResult.EndLine
        if self.tool_property_search_.feature_action_:
            result_to_format += self.tool_property_search_.feature_action_ + FormatResult.EndLine
        if self.tool_property_search_.feed_back_user_ :
            result_to_format += self.tool_property_search_.feed_back_user_
        result_to_format += self.format_search_result_screw_spine()
        result_to_format += self.format_search_result_screw_trauma_wrist()
        result_to_format += self.format_search_result_screw_trauma_ankle()
        return result_to_format

    def format_search_result_screw_spine(self):
        screw_spine_property_search = self.tool_property_search_.screw_spine_property_search_
        result_screw_spine = FormatResult.EmptyString
        if screw_spine_property_search.diameter_ != DiameterScrew.BadDiameter:
            result_screw_spine += FormatResult.DiameterMessage + screw_spine_property_search.diameter_.value + FormatResult.EndLine
        if screw_spine_property_search.length_ != Length.BadLength:
            result_screw_spine += FormatResult.LengthMessage + screw_spine_property_search.length_.value + FormatResult.EndLine
        if screw_spine_property_search.screw_need_diameter_:
            result_screw_spine += FormatResult.DiameterWaitM
        if screw_spine_property_search.screw_need_length_:
            result_screw_spine += FormatResult.LengthWait
        return result_screw_spine

    def format_search_result_screw_trauma_wrist(self):
        screw_wrist_property_search = self.tool_property_search_.screw_wrist_property_search_
        result_screw_wrist = FormatResult.EmptyString
        if screw_wrist_property_search.head_type_ != HeadType.BadHeadType:
            result_screw_wrist += FormatResult.HeadTypeMessage + screw_wrist_property_search.head_type_.value[
                0] + FormatResult.EndLine
        if screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness:
            result_screw_wrist += FormatResult.ThreadFullnessMessage + \
                                  screw_wrist_property_search.thread_fullness_.value[0] + FormatResult.EndLine
        if screw_wrist_property_search.length_ != Length.BadLength:
            result_screw_wrist += FormatResult.LengthMessage + screw_wrist_property_search.length_.value + FormatResult.EndLine
        if screw_wrist_property_search.screw_need_headType_:
            result_screw_wrist += FormatResult.HeadtypeWait
        if screw_wrist_property_search.screw_need_length_:
            result_screw_wrist += FormatResult.LengthWait
        if screw_wrist_property_search.screw_need_thread_fullness_:
            result_screw_wrist += FormatResult.ThreadFullnessWait
        if screw_wrist_property_search.attention_for_user_:
            result_screw_wrist += screw_wrist_property_search.attention_for_user_ + FormatResult.EndLine
        return result_screw_wrist

    def format_search_result_screw_trauma_ankle(self):
        screw_ankle_property_search = self.tool_property_search_.screw_ankle_property_search_
        result_screw_ankle = FormatResult.EmptyString
        if screw_ankle_property_search.thread_type_ != ThreadType.BadThreadType:
            result_screw_ankle += FormatResult.ThreadTypeMessage + screw_ankle_property_search.thread_type_.value + FormatResult.EndLine
        if screw_ankle_property_search.length_ != Length.BadLength:
            result_screw_ankle += FormatResult.LengthMessage + screw_ankle_property_search.length_.value + FormatResult.EndLine
        if screw_ankle_property_search.screw_need_thread_type_:
            result_screw_ankle += FormatResult.ThreadTypeWait + FormatResult.EndLine
        if screw_ankle_property_search.screw_need_length_:
            result_screw_ankle += FormatResult.LengthWait + FormatResult.EndLine
        return result_screw_ankle

    def reply(self):
        result = self.format_search_result()
        print(result)
