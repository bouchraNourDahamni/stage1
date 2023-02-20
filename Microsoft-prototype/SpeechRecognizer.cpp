#include "SpeechRecognizer.h"

#include <speechapi_cxx.h>

#include "SurgeryType.h"
#include <future>
#include <iostream>

using namespace Microsoft::CognitiveServices::Speech;
const std::string EmptyString = "";
const std::string KeySubscription = "223c9e66623c4b53a29867436e830104";
const std::string RegionApi = "canadacentral";
const std::string ModelId = "0883c6f9-f075-4659-824c-88c5c9e65885";
const std::string StartRecongnition = "start recognizing...\n";
const std::string NoMatch = "NOMATCH: Speech could not be recognized.";
const std::string ConcelledReason = "CANCELED: Reason=";
const std::string CancelledError = "CANCELED: ErrorCode=";
const std::string CancelledErrorDetail = "CANCELED: ErrorDetails=";
const std::string CancelledErrorSubscription = "CANCELED: Did you update the subscription info?";
const std::string SessionStop = "Session stopped.";
const std::string Endline = "\n";


void KeyWordRecognition()
{
	try
	{
		const auto keywordModel = KeywordRecognitionModel::FromFile("add your path");
		const auto audioConfig = Audio::AudioConfig::FromDefaultMicrophoneInput();
		auto recognizer = KeywordRecognizer::FromConfig(audioConfig);
		auto resultFuture = recognizer->RecognizeOnceAsync(keywordModel);
	}
	catch (exception e)
	{
		cout << e.what();
	}
}

void recognizeSpeech(FilterSpeech& filter)
{
	ScrewWristPropertySearch screwWristPropertySearch = { EmptyString , EmptyString , EmptyString ,EmptyString ,HeadType::BadHeadType ,ThreadFullness::BadThreadFulness, Length::BadLength};
	ScrewSpinePropertySearch screwSpinePropertySearch = { DiameterScrew::BadDiameter,Length::BadLength,EmptyString, EmptyString };
	ScrewAnklePropertySearch screwAnklePropertySearch = { EmptyString , ThreadType::BadThreadType , Length::BadLength , EmptyString , EmptyString };
	ToolPropertySearch toolPropertySearch = { screwWristPropertySearch, screwAnklePropertySearch , screwSpinePropertySearch ,ToolHandleType::BadToolHandle, Length::BadLength, false ,EmptyString };
	 //step one 
	// Creates an instance of a speech config with key on azure subscription and region of api call .
	auto config = SpeechConfig::FromSubscription(KeySubscription, RegionApi);
	config->SetEndpointId(ModelId);

	// Creates an instance of speech recognizer//
	auto recognizer = SpeechRecognizer::FromConfig(config);
	cout << StartRecongnition;

	//promise for synchronization of recongition end 

	promise<void> recognitionEnd;

	// Subscribes to events.
	//The event Recognizing signals that an intermediate recognition result is received.
	//Connects given callback function to the event signal, to be invoked when the event is signalled.
	// SpeechRecognitionEventArgs Class
	recognizer->Recognizing.Connect([](const SpeechRecognitionEventArgs& e)
	{
	});


	recognizer->Recognized.Connect([&filter, &toolPropertySearch](const SpeechRecognitionEventArgs& e)

	{
		if (e.Result->Reason == ResultReason::RecognizedSpeech)
		{
			const string speechTranscription = e.Result->Text;
			filter.searchProperties(speechTranscription, toolPropertySearch);
			TextToSpeech textToSpeech(toolPropertySearch);
			textToSpeech.reply();
			filter.reinitPropertySearch(toolPropertySearch);
		}
		else if (e.Result->Reason == ResultReason::NoMatch)
		{
			cout << NoMatch << std::endl;
		}
	});

	recognizer->Canceled.Connect([&recognitionEnd](const SpeechRecognitionCanceledEventArgs& e)
	{
		cout << ConcelledReason << (int)e.Reason << std::endl;

		if (e.Reason == CancellationReason::Error)
		{
			cout << CancelledError << (int)e.ErrorCode << Endline
				<< CancelledErrorDetail << e.ErrorDetails << Endline
				<< CancelledErrorSubscription << std::endl;
			recognitionEnd.set_value(); // Notify to stop recognition.
		}
	});

	recognizer->SessionStopped.Connect([&recognitionEnd](const SessionEventArgs& e)
	{
		cout << SessionStop;
		recognitionEnd.set_value(); // Notify to stop recognition.
	});

	// Starts continuous recognition. Uses StopContinuousRecognitionAsync() to stop recognition.
	recognizer->StartContinuousRecognitionAsync().get();

	// Waits for recognition end.
	recognitionEnd.get_future().get();

	// Stops recognition.
	recognizer->StopContinuousRecognitionAsync().get();
}
