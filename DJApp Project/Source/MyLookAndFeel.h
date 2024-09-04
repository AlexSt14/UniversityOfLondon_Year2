/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 2 Sep 2024 12:27:12pm
    Author:  alex_

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
*/
class MyLookAndFeel  : public LookAndFeel_V4
{
public:
    MyLookAndFeel();
    ~MyLookAndFeel() override;

    /*Overriding drawing the button background*/
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown) override;
    /*Overriding drawing button text*/
    void drawButtonText (Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override;
    /*Overriding drawing the rotary slider*/
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
    /*Overriding drawing the linear slider*/
    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, Slider::SliderStyle style, Slider& slider) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyLookAndFeel)
};
