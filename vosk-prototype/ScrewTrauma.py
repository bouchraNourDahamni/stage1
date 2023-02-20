from Tool import Tool
from SurgeryType import TraumaBoneType
from ToolProperties import HeadType
from ToolProperties import Length
from ToolProperties import ThreadFullness
from ToolPropertySearch import UpdateProperty
from ToolProperties import ScrewWrist
from ToolProperties import ThreadType
from ToolProperties import UpdatePropertyType
import AttentionUser
import Data


class ScrewTrauma(Tool):
    def __init__(self, tool_names, tool_handle, trauma_bone_type):
        super().__init__(tool_names, tool_handle)
        self.trauma_bone_type_ = trauma_bone_type

    def search_property(self, speech_transcription, tool_property_search):
        name_found = super(ScrewTrauma, self).searchname(speech_transcription, tool_property_search)
        old_name_found = super(ScrewTrauma, self).searcholdname(tool_property_search)
        if name_found or old_name_found:
            self.search_parameter(speech_transcription, tool_property_search)

    def set_trauma_bone_type(self, trauma_bone_type):
        self.trauma_bone_type_ = trauma_bone_type

    def search_parameter(self, speech_transcription, tool_property_search):
        if self.trauma_bone_type_ == TraumaBoneType.Wrist.value:
            self.search_screw_wrist_parameters(speech_transcription, tool_property_search)
        elif self.trauma_bone_type_ == TraumaBoneType.Ankle.value:
            self.search_screw_ankle_properties(speech_transcription, tool_property_search)
        tool_property_search.is_tool_found_ = True

    def search_screw_ankle_properties(self, speech_transcription, tool_property_search):
        screw_ankle_property_search = tool_property_search.screw_ankle_property_search_
        if screw_ankle_property_search.thread_type_ != ThreadType.BadThreadType:
            return self.search_length_ankle(speech_transcription, tool_property_search)
        if screw_ankle_property_search.length_ != Length.BadLength:
            return self.map_length_to_thread_type(speech_transcription, tool_property_search)
        if screw_ankle_property_search.length_ == Length.BadLength and screw_ankle_property_search.thread_type_ == ThreadType.BadThreadType :
            for screw_ankle in Data.screwAnkleData:
                if speech_transcription.find(screw_ankle.value)!= -1 :
                    screw_ankle_property_search.thread_type_ = screw_ankle
                    screw_ankle_property_search.screw_need_thread_type_=""
                    self.search_length_ankle(speech_transcription,tool_property_search)
                    return
            for screw_ankle in Data.screwAnkleData :
                for length in Data.screwAnkleData[screw_ankle]:
                    if speech_transcription.find(length.value)!= -1:
                        screw_ankle_property_search.length_ = length
                        screw_ankle_property_search.screw_need_length_ = ""
                        self.map_length_to_thread_type(speech_transcription,tool_property_search)
                        return
            screw_ankle_property_search.screw_need_length_ = self.tool_names[1]
            screw_ankle_property_search.screw_need_thread_type_ = self.tool_names[1]

    def map_length_to_thread_type(self, speech_transcription, tool_property_search):
        screw_ankle_property_search = tool_property_search.screw_ankle_property_search_
        for screw_ankle in Data.screwAnkleData:
            if speech_transcription.find(screw_ankle.value) != -1:
                for length in Data.screwAnkleData[screw_ankle]:
                    if length == screw_ankle_property_search.length_:
                        screw_ankle_property_search.thread_type_ = screw_ankle
                        screw_ankle_property_search.screw_need_thread_type_ = ""
                        return
        screw_ankle_property_search.screw_need_thread_type_ = self.tool_names[1]

    def search_length_ankle(self, speech_transcription, tool_property_search):
        if tool_property_search.screw_ankle_property_search_.thread_type_ in Data.screwAnkleData:
            for length in Data.screwAnkleData[tool_property_search.screw_ankle_property_search_.thread_type_]:
                if speech_transcription.find(length.value) != -1:
                    tool_property_search.screw_ankle_property_search_.length_ = length
                    tool_property_search.screw_ankle_property_search_.screw_need_length_ = ""
                    return

        tool_property_search.screw_ankle_property_search_.screw_need_length_ = self.tool_names[1]

    def search_screw_wrist_parameters(self, speech_transcription, tool_property_search):
        # method to check which property is already mentioned by user, according to these probabilities, We perform
        # the search
        screw_wrist_property_search = tool_property_search.screw_wrist_property_search_
        screw_wrist_property_search.attention_for_user_ = ""
        # Cas one: Property Head Type is already mentioned
        if screw_wrist_property_search.head_type_ != HeadType.BadHeadType and screw_wrist_property_search.length_ == Length.BadLength and screw_wrist_property_search.thread_fullness_ == ThreadFullness.BadThreadFulness:
            self.search_length(speech_transcription, tool_property_search)
            self.search_thread_fulness(speech_transcription, tool_property_search)
            update_property = UpdateProperty(False, True, True)
            if screw_wrist_property_search.length_ != Length.BadLength and screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness:
                if not self.verify_property(tool_property_search, update_property):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.LTPreviousHeadType
            return
        # Case Two: Property Length is already mentioned, but  HeadType and ThreadFulness are not
        if screw_wrist_property_search.length_ != Length.BadLength and screw_wrist_property_search.head_type_ == HeadType.BadHeadType and screw_wrist_property_search.thread_fullness_ == ThreadFullness.BadThreadFulness:
            self.search_head_type(speech_transcription, tool_property_search)
            self.search_thread_fulness(speech_transcription, tool_property_search)
            if screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness:
                if not self.verify_length(tool_property_search, UpdatePropertyType.UpdateLength):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.LTMatch
            if screw_wrist_property_search.head_type_ != HeadType.BadHeadType and screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness:
                update_property = UpdateProperty(True, True, False)
                if not self.verify_property(tool_property_search, update_property):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.HTPreviousLength
            return
        # Case Three: Property Thread Fulllness is already mentioned and headType and Length are not
        if screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness and screw_wrist_property_search.head_type_ == HeadType.BadHeadType and screw_wrist_property_search.length_ == Length.BadLength:
            self.search_length(speech_transcription, tool_property_search)
            if screw_wrist_property_search.length_ != Length.BadLength:
                if not self.verify_length(tool_property_search, UpdatePropertyType.UpdateThreadFulness):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.LTMatch
            self.search_head_type(speech_transcription, tool_property_search)
            update_property = UpdateProperty(True, False, True)
            if screw_wrist_property_search.head_type_ != HeadType.BadHeadType and screw_wrist_property_search.length_ != Length.BadLength:
                if not self.verify_property(tool_property_search, update_property):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.HLPreviousThreadFulness
            return
        # Case Four: Property Head Type and Length is already mentioned and ThreadFulness is not
        # We don't call verify Property because with threadFulness because all combination are possible
        if screw_wrist_property_search.head_type_ != HeadType.BadHeadType and screw_wrist_property_search.length_ != Length.BadLength and screw_wrist_property_search.thread_fullness_ == ThreadFullness.BadThreadFulness:
            self.search_thread_fulness(speech_transcription, tool_property_search)
            return
        # Case Five: Property Head Type and Thread Fulness is already mentioned and length is not
        if screw_wrist_property_search.head_type_ != HeadType.BadHeadType and screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness and screw_wrist_property_search.length_ == Length.BadLength:
            self.search_length(speech_transcription, tool_property_search)
            update_property = UpdateProperty(False, False, True)
            if screw_wrist_property_search.length_ != Length.BadLength:
                if not self.verify_property(tool_property_search, update_property):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.LPreviousThreadHeadType
            return

        # Case Six: Property Length and Thread Fulness is already mentionned and head type is not
        if screw_wrist_property_search.length_ != Length.BadLength and screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness and screw_wrist_property_search.head_type_ == HeadType.BadHeadType:
            self.search_head_type(speech_transcription, tool_property_search)
            update_property = UpdateProperty(True, False, False)
            if screw_wrist_property_search.head_type_ != HeadType.BadHeadType:
                if not self.verify_property(tool_property_search, update_property):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.HPreviousLengthThread
            return
        # Case Seven: Property Lenght and Thread Fulness and Head Type are not already mentioned
        if screw_wrist_property_search.length_ == Length.BadLength and screw_wrist_property_search.thread_fullness_ == ThreadFullness.BadThreadFulness and screw_wrist_property_search.head_type_ == HeadType.BadHeadType:
            self.search_head_type(speech_transcription, tool_property_search)
            self.search_length(speech_transcription, tool_property_search)
            self.search_thread_fulness(speech_transcription, tool_property_search)
            if screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness and screw_wrist_property_search.length_ != Length.BadLength:
                if not self.verify_length(tool_property_search, UpdatePropertyType.UpdateThreadFulness):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.LTMatch
            if screw_wrist_property_search.head_type_ != HeadType.BadHeadType and screw_wrist_property_search.length_ != Length.BadLength and screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness:
                update_property = UpdateProperty(True, False, False)
                if not self.verify_property(tool_property_search, update_property):
                    screw_wrist_property_search.attention_for_user_ = AttentionUser.HeadLengthThreadMatch
            return

    def search_length(self, speech_transcription, tool_property_search):
        for screw_Wrist in Data.screwWristData:
            for length in Data.screwWristData[screw_Wrist]:
                if speech_transcription.find(length.value) != -1:
                    tool_property_search.screw_wrist_property_search_.length_ = length
                    tool_property_search.screw_wrist_property_search_.screw_need_length_ = ""
                    return
        # we put index one :  because at the index one we put the name "screw" which is sufficient to perform the
        # next search for the  length
        tool_property_search.screw_wrist_property_search_.screw_need_length_ = self.tool_names[1]

    def search_thread_fulness(self, speech_transcription, tool_property_search):
        for screw_Wrist in Data.screwWristData:
            for thread_fulness in screw_Wrist.thread_fullness_.value:
                if speech_transcription.find(thread_fulness) != -1:
                    tool_property_search.screw_wrist_property_search_.thread_fullness_ = screw_Wrist.thread_fullness_
                    tool_property_search.screw_wrist_property_search_.screw_need_thread_fullness_ = ""
                    return
        tool_property_search.screw_wrist_property_search_.screw_need_thread_fullness_ = self.tool_names[1]

    def search_head_type(self, speech_transcription, tool_property_search):
        for screw_Wrist in Data.screwWristData:
            for head_type in screw_Wrist.head_type_.value:
                if speech_transcription.find(head_type) != -1:
                    tool_property_search.screw_wrist_property_search_.head_type_ = screw_Wrist.head_type_
                    tool_property_search.screw_wrist_property_search_.screw_need_headType_ = ""
                    return
        tool_property_search.screw_wrist_property_search_.screw_need_headType_ = self.tool_names[1]

    def verify_property(self, tool_property_search, update_property):
        # check the combination of the three properties when mentioned
        screw_wrist_property_search = tool_property_search.screw_wrist_property_search_
        screw_wrist_to_search = ScrewWrist(screw_wrist_property_search.thread_fullness_,
                                           screw_wrist_property_search.head_type_)
        if screw_wrist_to_search in Data.screwWristData:
            for length in Data.screwWristData[screw_wrist_to_search]:
                if length == screw_wrist_property_search.length_:
                    return True
            if update_property.update_length_:
                screw_wrist_property_search.length_ = Length.BadLength
                screw_wrist_property_search.screw_need_length_ = self.tool_names[1]
            if update_property.update_thread_fulness_:
                screw_wrist_property_search.thread_fullness_ = ThreadFullness.BadThreadFulness
                screw_wrist_property_search.screw_need_thread_fullness_ = self.tool_names[1]
            if update_property.update_head_type_:
                screw_wrist_property_search.head_type_ = HeadType.BadHeadType
                screw_wrist_property_search.screw_need_headType_ = self.tool_names[1]
            return False

        return False

    def verify_length(self, tool_property_search, updateProperty):
        ##check the combination of the length property with the two other properties : Thread Fulness and Head Type.
        ## we don't  need to check between HeadType and Length ,because all combination are possible
        ##  We don't need to check the combination of Head Type and Thread Fulness , because all combination are possible
        ## return true if we fin the good comibnation
        screw_wrist_property_search = tool_property_search.screw_wrist_property_search_
        screw_wrist_to_search1 = ScrewWrist(screw_wrist_property_search.thread_fullness_, HeadType.Locking)
        screw_wrist_to_search2 = ScrewWrist(screw_wrist_property_search.thread_fullness_, HeadType.NonLockingCross)
        if screw_wrist_to_search1 in Data.screwWristData or screw_wrist_to_search2 in Data.screwWristData:
            for length in Data.screwWristData[screw_wrist_to_search1]:
                if tool_property_search.screw_wrist_property_search_.length_ == length:
                    return True
            for length in Data.screwWristData[screw_wrist_to_search2]:
                if tool_property_search.screw_wrist_property_search_.length_ == length:
                    return True
        if updateProperty == UpdatePropertyType.UpdateLength:
            if screw_wrist_property_search.thread_fullness_ != ThreadFullness.BadThreadFulness:
                screw_wrist_property_search.thread_fullness_ = ThreadFullness.BadThreadFulness
                screw_wrist_property_search.screw_need_thread_fullness_ = self.tool_names[1]

        else:
            screw_wrist_property_search.length_ = Length.BadLength
            screw_wrist_property_search.screw_need_length_ = self.tool_names[1]

        return False
