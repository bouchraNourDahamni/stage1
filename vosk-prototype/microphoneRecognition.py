import os
from ToolPropertySearch import ToolPropertySearch
from ToolHandleType import ToolHandleType
from ToolProperties import Length
from TextToSpeech import TextToSpeech
from ToolPropertySearch import ScrewSpinePropertySearch
from ToolPropertySearch import ScrewWristPropertySearch
from ToolProperties import DiameterScrew
from ToolPropertySearch import ScrewAnklePropertySearch
from ToolProperties import ThreadType
from ToolProperties import HeadType
from ToolProperties import ThreadFullness

import pyaudio
from vosk import Model, KaldiRecognizer

if not os.path.exists("model"):
    print("Please download the model from https://alphacephei.com/vosk/models and unpack as 'model' in the current "
          "folder.")
    exit(1)

model = Model("model")
rec = KaldiRecognizer(model, 16000)

p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paInt16, channels=1,
                rate=16000, input=True, frames_per_buffer=8000)
stream.start_stream()

screw_spine_property_search = ScrewSpinePropertySearch(DiameterScrew.BadDiameter, Length.BadLength, "", "")
screw_wrist_property_search = ScrewWristPropertySearch("", "", "", "",
                                                       HeadType.BadHeadType, ThreadFullness.BadThreadFulness,
                                                       Length.BadLength)
screw_ankle_property_search = ScrewAnklePropertySearch("", ThreadType.BadThreadType, Length.BadLength, "", "")

tool_property_search = ToolPropertySearch(screw_wrist_property_search, screw_ankle_property_search,
                                          screw_spine_property_search,
                                          ToolHandleType.BadToolHandle,
                                          Length.BadLength, False, "", "", False, "")


def recognize(continueRecognition, Filter):
    while continueRecognition:
        data = stream.read(4000, exception_on_overflow=False)
        if len(data) == 0:
            break
        if rec.AcceptWaveform(data):
            Filter.search_properties(rec.Result(), tool_property_search)
            feed_back_user(rec.Result(), tool_property_search)
            text_to_speech = TextToSpeech(tool_property_search)
            text_to_speech.reply()
            Filter.reinit_property_search(tool_property_search)


def feed_back_user(result, tool_property_search):
    if not tool_property_search.is_feature_found_ and not tool_property_search.is_tool_found_ and result.find(
            "noise") == -1:
        tool_property_search.feed_back_user_ = "we apologize, we can't process the orders you mentioned. we only process the surgical orders that correspond to the chosen surgery.\n "
