class ScrewWristPropertySearch:
    def __init__(self, screw_need_thread_fullness, screw_need_headType, screw_need_length, attention_for_user,
                 head_type, thread_fullness, length):
        self.screw_need_thread_fullness_ = screw_need_thread_fullness
        self.screw_need_headType_ = screw_need_headType
        self.screw_need_length_ = screw_need_length
        self.attention_for_user_ = attention_for_user
        self.head_type_ = head_type
        self.thread_fullness_ = thread_fullness
        self.length_ = length


class UpdateProperty:
    def __init__(self, update_head_type, update_thread_fulness, update_length):
        self.update_head_type_ = update_head_type
        self.update_thread_fulness_ = update_thread_fulness
        self.update_length_ = update_length


class ScrewSpinePropertySearch:
    def __init__(self, diameter, length, screw_need_diameter, screw_need_length):
        self.diameter_ = diameter
        self.length_ = length
        self.screw_need_diameter_ = screw_need_diameter
        self.screw_need_length_ = screw_need_length


class ScrewAnklePropertySearch:
    def __init__(self, attention_for_user, thread_type, length, screw_need_thread_type, screw_need_length):
        self.attention_for_user_ = attention_for_user
        self.thread_type_ = thread_type
        self.length_ = length
        self.screw_need_thread_type_ = screw_need_thread_type
        self.screw_need_length_ = screw_need_length


class ToolPropertySearch:
    def __init__(self, screw_wrist_property_search, screw_ankle_property_search, screw_spine_property_search,
                 tool_handle, length,
                 is_tool_found, tool_need_size, feature_action, is_feature_found, feed_back_user):
        self.screw_wrist_property_search_ = screw_wrist_property_search
        self.screw_ankle_property_search_ = screw_ankle_property_search
        self.screw_spine_property_search_ = screw_spine_property_search
        self.tool_handle_ = tool_handle
        self.length_ = length
        self.is_tool_found_ = is_tool_found
        self.toolneedsize_ = tool_need_size
        self.feature_action_ = feature_action
        self.is_feature_found_= is_feature_found
        self.feed_back_user_ = feed_back_user
