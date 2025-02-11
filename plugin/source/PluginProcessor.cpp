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
    totalSeconds += (double) getTimerInterval()/1000;
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

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(buffer);
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
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
    juce::ignoreUnused (destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
