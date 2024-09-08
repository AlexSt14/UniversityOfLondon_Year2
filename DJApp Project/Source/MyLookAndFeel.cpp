/*
  ==============================================================================

    MyLookAndFeel.cpp
    Created: 2 Sep 2024 12:27:12pm
    Author:  alex_

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyLookAndFeel.h"

//==============================================================================
MyLookAndFeel::MyLookAndFeel()
{
	setColour(ResizableWindow::backgroundColourId, Colour{ 48, 48, 48 });
}

MyLookAndFeel::~MyLookAndFeel()
{
}

/*Overriding drawing the button background*/
void MyLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
    bool isMouseOverButton, bool isButtonDown)
{
	auto generalColour = Colour{ 25, 23, 26 };
	auto borderColour = Colour{ 52, 50, 53 };
    auto buttonArea = button.getLocalBounds();
	//Changing the colour of the button when pressed or hovered
	if (isButtonDown)
	{
		generalColour = generalColour.darker();
	}
	else if (isMouseOverButton)
	{
		generalColour = generalColour.brighter(0.1f);
	}
	//Drawing the button background
	g.setColour(generalColour);
	g.fillRect(buttonArea.toFloat());
	auto cornerSize = 6.0f;
	g.fillRoundedRectangle(buttonArea.toFloat(), cornerSize);
	//Drawing border around the buttons
	g.setColour(borderColour);
	g.drawRect(buttonArea.toFloat());
}
/*Overriding drawing button text*/
void MyLookAndFeel::drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown)
{
	auto textColour = Colour{ 255, 255, 255 };
	auto font = Font(15.0f, Font::plain);
	g.setColour(textColour);
	g.setFont(font);
	g.drawFittedText(button.getButtonText(), button.getLocalBounds(), Justification::centred, 1);
}
/*Overriding drawing the rotary slider*/
//This method was inspired and built upon the code from this youtube video: https://www.youtube.com/watch?v=_IocXoXUWdQ
//Channel name: The Audio Programmer
void MyLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
	//Calculating the diameter, radius, center, and angle of the rotary slider
	//Minimising the width and height
	int mWidth = width - 20;
	int mHeight = height - 20;
	float diameter = jmin(jmin(mWidth, mHeight),100);
	float radius = diameter / 2;
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float rx = centerX - radius;
	float ry = centerY - radius;
	float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
	//Defining the colours of the rotary slider
	Colour dialBorder = Colour{ 5, 5, 5 };
	Colour dialColourN1 = Colour{ 34, 34, 34 };
	Colour dialColourN2 = Colour{ 46, 46, 46 };
	Colour dialTickColour = Colour{ 255, 255, 255 };
	//Drawing the rotary slider
	Rectangle<float> dialArea(rx, ry, diameter, diameter);
	g.setColour(dialColourN1);
	g.fillEllipse(dialArea);
	g.setColour(dialColourN2.brighter(0.1f));
	g.fillEllipse(dialArea.reduced(5.0f));
	g.setColour(dialTickColour);
	Path dialTick;
	dialTick.addRectangle(0, -radius, 3.0f, radius * 0.45);
	g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));
	g.setColour(dialBorder);
	g.drawEllipse(rx, ry, diameter, diameter, 2.0f);
}
/*Overriding drawing the linear slider according to the type of slider that is added
I have only added code for the linear vertical slider as this is the only one I am using*/
void MyLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, Slider::SliderStyle style, Slider& slider)
{
	Colour trackColour = Colour{ 25, 23, 26 };
	Colour thumbBorder = Colour{ 13, 13, 13 };
	Colour thumbN1 = Colour{ 29, 28, 28 };
	Colour thumbN2 = Colour{ 46, 46, 46 };
	Colour thumbN3 = Colour{ 213, 213, 213 };
	if (style == Slider::LinearVertical)
	{
		//Track and thumb dimensions
		float trackWidth = 5.0f;
		auto trackX = x + (width - trackWidth) * 0.5f;
		float thumbWidth = 40.0f;
		float thumbN1Height = 20.0f;
		float thumbN2Height = 12.0f;
		float thumbN3Height = 2.0f;
		float thumbX = trackX + (trackWidth - thumbWidth) * 0.5f;

		////Drawing a thin rectangle every certain interval of the slider and when it reaches integer values, it will draw a thicker rectangle
		float sliderX = thumbX - 2.0f;
		float sliderWidth = 44.0f;
		float sliderHeight = 2.0f;
		float sliderRangeMin = slider.getMinimum();
		float sliderRangeMax = slider.getMaximum();
		float interval = 0.2f;

		//Customize slider track
		if (sliderRangeMax < 1.1f) {
			//Drawing intervals
			interval = 0.2f;
			for (float val = sliderRangeMin; val <= sliderRangeMax; val += interval) {
				//Determine when I am at an integer
				bool isInteger = (std::abs(fmod(val, 1)) < 0.0001f) ? true : false;
				float thickness = isInteger ? 1.5f : 0.5f;
				float heightAdjustment = isInteger ? 1.5f : 0.5f;
				//Mapping the values of the slider to the height of the slider
				float mappedPos = jmap(val, sliderRangeMin, sliderRangeMax, static_cast<float>(y), static_cast<float>(y + height));
				//Drawing lines
				g.setColour(juce::Colours::white);
				g.fillRect(sliderX, mappedPos - thickness * 0.5f, sliderWidth, heightAdjustment);
			}
		}
		else {
			//Drawing intervals
			interval = 1.0f; // Interval for thin rectangles
			for (float val = sliderRangeMin; val <= sliderRangeMax; val += interval) {
				//Determining when I am at number 0, 1 or 5
				bool isInteger = (val == 0) || (val == 4) || (val == 5) ? true : false;
				DBG("isInteger: " << std::to_string(isInteger) << " val: " << std::to_string(val));
				float thickness = isInteger ? 1.5f : 0.5f;
				float heightAdjustment = isInteger ? 1.5f : 0.5f;
				DBG("thickness: " << std::to_string(thickness) << " heightAdjustment: " << std::to_string(heightAdjustment));
				//Map the value to the slider's position range using jmap
				float mappedPos = jmap(val, sliderRangeMin, sliderRangeMax, static_cast<float>(y), static_cast<float>(y + height)); // Inverted for vertical slider

				g.setColour(juce::Colours::white);
				g.fillRect(sliderX, mappedPos - thickness * 0.5f, sliderWidth, heightAdjustment);
			}
		}
		
		//Drawing the slider track
		g.setColour(trackColour);
		g.fillRect(static_cast<int>(trackX), y, static_cast<int>(trackWidth), height);
		//Drawing the slider thumb		
		g.setColour(Colour(thumbN1));
		g.fillRect(static_cast<int>(thumbX), static_cast<int>(sliderPos - thumbN1Height * 0.5f), static_cast<int>(thumbWidth), static_cast<int>(thumbN1Height));
		g.setColour(Colour(thumbN2));
		g.fillRect(static_cast<int>(thumbX), static_cast<int>(sliderPos - thumbN2Height * 0.5f), static_cast<int>(thumbWidth), static_cast<int>(thumbN2Height));
		g.setColour(Colour(thumbN3));
		g.fillRect(static_cast<int>(thumbX), static_cast<int>(sliderPos - thumbN3Height * 0.5f), static_cast<int>(thumbWidth), static_cast<int>(thumbN3Height));
		g.setColour(Colour(thumbBorder));
		g.drawRect(static_cast<int>(thumbX), static_cast<int>(sliderPos - thumbN1Height * 0.5f), static_cast<int>(thumbWidth), static_cast<int>(thumbN1Height));		
	}
}