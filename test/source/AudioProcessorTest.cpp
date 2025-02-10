#include <gtest/gtest.h>
#include <UseTime/PluginProcessor.h>
// #include <juce_AudioSampleBuffer.h>

namespace audio_plugin_test {
    // Audio processor inits correctly
    TEST(AudioProcessor, Initialize) {
        AudioPluginAudioProcessor processor;
        ASSERT_FALSE(false);
    }

    void fillBuffer(juce::AudioBuffer<float>& buffer, float val) {
        for (int c = 0; c < 2; c++) {
            auto* channelData = buffer.getWritePointer(c);
            for (int s = 0; s < 256; s++) {
                channelData[s] = val;
            }
        } 
    }

    void fillSample(juce::AudioBuffer<float>& buffer, float val, int channel, int sampleNumber) {
        auto* channelData = buffer.getWritePointer(channel);
        channelData[sampleNumber] = val;
    }

    // Audio processor in buffer = out buffer, filled with 0s
    TEST(AudioProcessor, ZeroFill) {
        juce::AudioBuffer<float> in(2, 256);
        
        fillBuffer(in, 0.0f);

        juce::AudioBuffer<float> copyIn(in);
        juce::MidiBuffer midiBuffer;

        AudioPluginAudioProcessor processor;
        processor.processBlock(in, midiBuffer);

        for (int c = 0; c < 2; c++) {
            auto* inData = in.getReadPointer(c);
            auto* copyInData = copyIn.getReadPointer(c);
            for (int s = 0; s < 256; s++) {
                ASSERT_TRUE(inData[s] == copyInData[s]);
            }
        }
    }
    
    // Audio processor in buffer = out buffer, filled with 1s
    TEST(AudioProcessor, OneFill) {
        juce::AudioBuffer<float> in(2, 256);
        
        fillBuffer(in, 1.0f);

        juce::AudioBuffer<float> copyIn(in);
        juce::MidiBuffer midiBuffer;

        AudioPluginAudioProcessor processor;
        processor.processBlock(in, midiBuffer);

        for (int c = 0; c < 2; c++) {
            auto* inData = in.getReadPointer(c);
            auto* copyInData = copyIn.getReadPointer(c);
            for (int s = 0; s < 256; s++) {
                ASSERT_TRUE(inData[s] == copyInData[s]);
            }
        }
    }

    // // Audio processor in buffer = out buffer, filled with sine wave
    // TEST(AudioProcessor, SineFill) {

    // }

    // // Audio processor in buffers = out buffers, filled with sine wave, checks two buffers with a sine wave that continues throughout both
    // TEST(AudioProcessor, SineTwoFill) {

    // }
}