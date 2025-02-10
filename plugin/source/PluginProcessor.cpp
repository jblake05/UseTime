#include "../include/UseTime/PluginProcessor.h"
#include "../include/UseTime/PluginEditor.h"
#include <fstream>
#include <iostream>
// #include <juce_AudioParameterInt.h>

//==============================================================================
double srate;
double elapsedSamples = 0.0;
int timesCalled = 0;

// double totalSeconds;
double secondsElapsed = 0.0;

const int SAMPLE_FACTOR = 4;
const double SAVE_INTERVAL = 60.0;
const int hz = 2;

using namespace std;
//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
        //                ,
        // apvts(*this, nullptr, juce::Identifier("APVTS"), {
        //     std::make_unique<juce::AudioParameterInt> ("hourId", "Hours", 0, 1000000000, 0),
        //     std::make_unique<juce::AudioParameterInt> ("minuteId", "Minutes", 0, 59, 0),
        //     std::make_unique<juce::AudioParameterInt> ("secondId", "Seconds", 0, 59, 0)
        // })
{
    srate = getSampleRate();
    string time;
    ifstream fileIn;

    fileIn.open("C:/Program Files/Common Files/VST3/UseTime.vst3/Contents/x86_64-win/time.txt");
	if (!fileIn.is_open()) {
		std::cerr << "Time input file couldn't open!";
	}

    getline(fileIn, time);

    fileIn.close();

    totalSeconds = stod(time);

    startTimerHz(hz);
}

static int writeFile() {
	ofstream fileOut;
	fileOut.open("C:/Program Files/Common Files/VST3/UseTime.vst3/Contents/x86_64-win/time.txt");

	if (!fileOut.is_open()) {
		cerr << "Time output file couldn't open!";
		return -1;
	}

	string newTime = to_string(totalSeconds);

	fileOut << newTime;

	fileOut.close();

	return 0;
}

void timerCallback() {
    totalSeconds +=
    if (++timesCalled == (int) SAMPLE_INTERVAL * hz) {
        writeFile();
    }

    
}
AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
    writeFile();
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

struct time {
    int hour;
    int minute;
    int second;
};

struct time secondToTime(double second) {
	int hr = (int) (second / 3600);

	second = fmod(second, 3600);

	int min = (int) (second / 60);

	second = fmod(second, 60);

	int sec = (int)(second);

	struct time result = {
		hr,
		min,
		sec
	};

	return result;
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    // auto totalNumInputChannels  = getTotalNumInputChannels();
    // auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    // for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //     buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    // for (int channel = 0; channel < totalNumInputChannels; ++channel)
    // {
    //     auto* channelData = buffer.getWritePointer (channel);
    //     juce::ignoreUnused (channelData);
    //     // ..do something to the data...
    // }
    elapsedSamples += buffer.getNumSamples();

    srate = getSampleRate();

    if (elapsedSamples > srate / SAMPLE_FACTOR) {
        double fracSeconds = elapsedSamples / srate;

        totalSeconds += fracSeconds;
        secondsElapsed += fracSeconds;

        elapsedSamples -= srate / SAMPLE_FACTOR;

        // edit parameter now
        struct time timeVal = secondToTime(totalSeconds);
        if (*hour != timeVal.hour)
            *hour = timeVal.hour;
        if (*minute != timeVal.minute)
            *minute = timeVal.minute;
        if (*second != timeVal.second)
            *second = timeVal.second;
        // apvts
    }

    if (secondsElapsed > SAVE_INTERVAL) {
        writeFile();
        secondsElapsed -= SAVE_INTERVAL;
    }
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    // return new AudioPluginAudioProcessorEditor (*this, *hour, *minute, *second);
    return new AudioPluginAudioProcessorEditor(*this);

    // generic until you add a UI that is read only and nice fonts :)
    // return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    // juce::ignoreUnused (destData);
    juce::MemoryOutputStream (destData, true).writeInt(*hour);
    juce::MemoryOutputStream (destData, true).writeInt(*minute);
    juce::MemoryOutputStream (destData, true).writeInt(*second);

}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    // juce::ignoreUnused (data, sizeInBytes);
    *hour = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readInt();
    *minute = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readInt();
    *second = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readInt();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
