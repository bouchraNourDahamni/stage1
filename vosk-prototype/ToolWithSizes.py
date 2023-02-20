from Tool import Tool


class ToolWithSizes(Tool):
    def __init__(self, tool_names, tool_handle, toollengths):
        self.toollengths_ = toollengths
        super().__init__(tool_names, tool_handle)

    def search_property(self, speech_transcription, tool_property_search):
        namefound = super(ToolWithSizes, self).searchname(speech_transcription, tool_property_search)
        oldnamefoud = super(ToolWithSizes, self).searcholdname(tool_property_search)
        if namefound:
            self.searchlength(speech_transcription, tool_property_search)
            tool_property_search.is_tool_found_ = True
        if oldnamefoud:
            self.searchlength(speech_transcription, tool_property_search)

    def searchlength(self, speechTranscription, toolPropertySearch):
        for length in self.toollengths_:
            if speechTranscription.find(length.value) != -1:
                toolPropertySearch.length_ = length
                toolPropertySearch.toolneedsize_ = ""
                toolPropertySearch.is_tool_found_ = True
                return
        toolPropertySearch.toolneedsize_ = self.tool_names[0]
