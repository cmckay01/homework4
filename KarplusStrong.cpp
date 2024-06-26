#include "KarplusStrong.h"

KarplusStrong::KarplusStrong()
    : frequency(440.0f),
      sampleRate(44100),
      writePosition(0),
      smoothing(0.5f),
      decay(0.99f)
{
}

void KarplusStrong::prepare(double sampleRate, int samplesPerBlock)
{
    this->sampleRate = (int)sampleRate;
    delayBuffer.setSize(1, (int)(sampleRate / frequency));
    delayBuffer.clear();
}


void KarplusStrong::process(juce::AudioBuffer<float>& buffer)
{
    auto* channelData = buffer.getWritePointer(0);
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        float delay = delayBuffer.getSample(0, writePosition);
        float noise = juce::Random::getSystemRandom().nextFloat() * 2.0f - 1.0f;
        float output = (delay + noise) / 2.0f;
        delayBuffer.setSample(0, writePosition, output * decay);
        channelData[sample] = output;
        writePosition = (writePosition + 1) % delayBuffer.getNumSamples();
    }
}

void KarplusStrong::setFrequency(float freq)
{
    frequency = freq;
    delayBuffer.setSize(1, (int)(sampleRate / frequency));
    delayBuffer.clear();
}

void KarplusStrong::pluck()
{
    for (int i = 0; i < delayBuffer.getNumSamples(); ++i)
    {
        delayBuffer.setSample(0, i, juce::Random::getSystemRandom().nextFloat() * 2.0f - 1.0f);
    }
}
