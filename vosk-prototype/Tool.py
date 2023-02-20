class Tool:
    def __init__(self, tool_names, tool_handle):
        self.tool_names = tool_names
        self.tool_handle = tool_handle

    def search_property(self, speech_transcription, tool_property_search):
        self.searchname(speech_transcription, tool_property_search)

    def searchname(self, speechTranscription, tool_property_search):
        for name in self.tool_names:
            if speechTranscription.find(name) != -1:
                tool_property_search.tool_handle_ = self.tool_handle
                return True
        return False

    def searcholdname(self, tool_property_search):
        if tool_property_search.toolneedsize_:
            return self.searchname(tool_property_search.toolneedsize_, tool_property_search)
        if tool_property_search.screw_spine_property_search_.screw_need_diameter_:
            return self.searchname(tool_property_search.screw_spine_property_search_.screw_need_diameter_,
                                   tool_property_search)
        if tool_property_search.screw_spine_property_search_.screw_need_length_:
            return self.searchname(tool_property_search.screw_spine_property_search_.screw_need_length_,
                                   tool_property_search)
        if tool_property_search.screw_wrist_property_search_.screw_need_length_:
            return self.searchname(tool_property_search.screw_wrist_property_search_.screw_need_length_,
                                   tool_property_search)
        if tool_property_search.screw_wrist_property_search_.screw_need_headType_:
            return self.searchname(tool_property_search.screw_wrist_property_search_.screw_need_headType_,
                                   tool_property_search)
        if tool_property_search.screw_wrist_property_search_.screw_need_thread_fullness_:
            return self.searchname(tool_property_search.screw_wrist_property_search_.screw_need_thread_fullness_,
                                   tool_property_search)
        if tool_property_search.screw_ankle_property_search_.screw_need_length_:
            return self.searchname(tool_property_search.screw_ankle_property_search_.screw_need_length_,
                                   tool_property_search)
        if tool_property_search.screw_ankle_property_search_.screw_need_thread_type_:
            return self.searchname(tool_property_search.screw_ankle_property_search_.screw_need_thread_type_,
                                   tool_property_search)
        return False
