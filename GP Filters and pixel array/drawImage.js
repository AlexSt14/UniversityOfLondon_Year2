//This class will draw images accordingly
//The images will be drawn in a grid-like manner
let thresholdSliderRed, thresholdSliderGreen, thresholdSliderBlue, thresholdSliderHue, thresholdSliderSaturation, 
    thresholdSliderHSV, thresholdSliderCMY;
class ImageGenerator {
    //Constructor for ImageGenerator class that sets the width, height, margin, padding, and positions of the images
    constructor() {
        this.videoWidth = 160;
        this.videoHeight = 120;
        this.marginLeft = 80;
        this.padding = 40;
        this.firstImagePos = {
            x: 40,
            y: 120
        }
        this.secondImagePos = {
            x: this.videoWidth+this.padding*2,
            y: this.firstImagePos.y
        }
        this.thirdImagePos = {
            x: this.secondImagePos.x+this.videoWidth+this.padding,
            y: this.firstImagePos.y
        }
        //Storing filtered images
        this.processedImg = null;
        this.grayscaleImg = null;
        this.redChannelImg = null;
        this.greenChannelImg = null;
        this.blueChannelImg = null;
        this.thresholdImgRed = null;
        this.thresholdImgGreen = null;
        this.thresholdImgBlue = null;
        this.hsvImg = null;
        this.cmyImg = null;
        this.thresholdImgHSV = null;
        this.thresholdImgCMY = null;
        //Creating sliders for thresholding
        thresholdSliderRed = createSlider(0, 255, 127);
        thresholdSliderGreen = createSlider(0, 255, 127);
        thresholdSliderBlue = createSlider(0, 255, 127);
        thresholdSliderHSV = createSlider(0, 255, 127);
        thresholdSliderCMY = createSlider(0, 255, 127);
        this.sliderRedValue = 127;
        this.sliderGreenValue = 127;
        this.sliderBlueValue = 127;
        this.sliderHSVValue = 127;
        this.sliderCMYValue = 127;
        this.thresholdChanged = false;
        this.hideSliders();
        //Face detection and required variables
        this.firstFaceEffect = true;
        this.secondFaceEffect = false;
        this.thirdFaceEffect = false; 
        this.fourthFaceEffect = false;
        this.numberOptionsX = this.firstImagePos.x;
        this.numberOptionsY = this.firstImagePos.y+this.videoHeight*4+this.padding*4+160;
    }
    //Draws images in a grid-like manner
    drawImages(img) {
        //Draws images only if the incoming img is different from the processedImg
        if (img !== this.processedImg) {
            this.processedImg = img;
            this.triggerFilters(img);    
            console.log("Filters triggered");     
        }
        //Redraws images if the threshold has changed
        if (this.sliderValueChanged()) {
            this.triggerFilters(img);
            console.log("Filters triggered");
        }
        this.showSliders();
        //Drawing images
        text("Webcam Image", this.secondImagePos.x, this.secondImagePos.y-20);
        image(img, this.secondImagePos.x, this.secondImagePos.y);
        text("Grayscale Image + 20% Brightness", this.thirdImagePos.x, this.thirdImagePos.y-20);
        image(this.grayscaleImg, this.thirdImagePos.x, this.thirdImagePos.y);
        text("Red Channel Image", this.firstImagePos.x, this.firstImagePos.y+this.videoHeight+this.padding);
        image(this.redChannelImg, this.firstImagePos.x, this.firstImagePos.y+this.videoHeight+this.padding+20);
        text("Green Channel Image", this.secondImagePos.x, this.secondImagePos.y+this.videoHeight+this.padding);
        image(this.greenChannelImg, this.secondImagePos.x, this.secondImagePos.y+this.videoHeight+this.padding+20);
        text("Blue Channel Image", this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight+this.padding);
        image(this.blueChannelImg, this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight+this.padding+20);
        text("Threshold Image R", this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*2+this.padding*2); 
        image(this.thresholdImgRed, this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*2+this.padding*2+20);  
        thresholdSliderRed.position(this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*2+this.padding*2+195);
        text("Threshold Image G", this.secondImagePos.x, this.secondImagePos.y+this.videoHeight*2+this.padding*2);
        image(this.thresholdImgGreen, this.secondImagePos.x, this.secondImagePos.y+this.videoHeight*2+this.padding*2+20);
        thresholdSliderGreen.position(this.secondImagePos.x, this.secondImagePos.y+this.videoHeight*2+this.padding*2+195);
        text("Threshold Image B", this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight*2+this.padding*2);
        image(this.thresholdImgBlue, this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight*2+this.padding*2+20);
        thresholdSliderBlue.position(this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight*2+this.padding*2+195);
        text("Webcam Image", this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*3+this.padding*3+10);
        image(img, this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*3+this.padding*3+20);
        /*
        Here I have used Travis' HUEColorSpace function to convert the image to HUE color space
        The function was taken from the resource PDF we were given for final project
        Colour Space Conversions
        Adrian Ford (ajoec1@wmin.ac.uk <defunct>)
        and Alan Roberts (Alan.Roberts@rd.bbc.co.uk).
        August 11, 1998(a)
        Page N.15
        */
        text("HSV (Travis) Color Space", this.secondImagePos.x, this.secondImagePos.y+this.videoHeight*3+this.padding*3+10);
        image(this.hsvImg, this.secondImagePos.x, this.secondImagePos.y+this.videoHeight*3+this.padding*3+20);
        /*
        Here I have used CMY(K) (Cyan Magenta Yellow (Black)) function to convert the image to CMY color space
        The function was taken from the resource PDF we were given for final project
        Colour Space Conversions
        Adrian Ford (ajoec1@wmin.ac.uk <defunct>)
        and Alan Roberts (Alan.Roberts@rd.bbc.co.uk).
        August 11, 1998(a)
        Page N.14
        */
        text("CMY Color Space", this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight*3+this.padding*3+10);
        image(this.cmyImg, this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight*3+this.padding*3+20);
        text("Face detection", this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*4+this.padding*4+10);
        text("HSV Threshold", this.secondImagePos.x, this.secondImagePos.y+this.videoHeight*4+this.padding*4+10);
        thresholdSliderHSV.position(this.secondImagePos.x, this.secondImagePos.y+this.videoHeight*4+this.padding*4+195);
        image(this.thresholdImgHSV, this.secondImagePos.x, this.secondImagePos.y+this.videoHeight*4+this.padding*4+20);
        text("CMY Threshold", this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight*4+this.padding*4+10);
        thresholdSliderCMY.position(this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight*4+this.padding*4+195);
        image(this.thresholdImgCMY, this.thirdImagePos.x, this.thirdImagePos.y+this.videoHeight*4+this.padding*4+20);

        //Face detection using ML5.js https://ml5js.org/
        //Grayscale as first effect
        if (this.firstFaceEffect) { 
            video.loadPixels();   
            //Using ML5.js to detect faces in the video
            // Process detected faces
            for (let i = 0; i < faces.length; i++) {
                let face = faces[i];
                let box = face.box;
                let xMin = Math.floor(box.xMin);
                let yMin = Math.floor(box.yMin);
                let boxWidth = Math.floor(box.width);
                let boxHeight = Math.floor(box.height);
                videoFilters.grayscaleFilter(xMin, yMin, boxWidth, boxHeight);
            }
            video.updatePixels();
            image(video, this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*4+this.padding*4+20);
        }
        //Blur as second effect
        if (this.secondFaceEffect) {
            for (let i = 0; i < faces.length; i++) {
                let face = faces[i];
                let box = face.box;
                let xMin = Math.floor(box.xMin);
                let yMin = Math.floor(box.yMin);
                let boxWidth = Math.floor(box.width);
                let boxHeight = Math.floor(box.height);
                videoFilters.blurFilter(xMin, yMin, boxWidth, boxHeight);
            }         
            video.updatePixels();
            image(video, this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*4+this.padding*4+20);   
        }
        //CMY as third effect
        if (this.thirdFaceEffect) {
            for (let i = 0; i < faces.length; i++) {
                let face = faces[i];
                let box = face.box;
                let xMin = Math.floor(box.xMin);
                let yMin = Math.floor(box.yMin);
                let boxWidth = Math.floor(box.width);
                let boxHeight = Math.floor(box.height);
                videoFilters.cmyFilter(xMin, yMin, boxWidth, boxHeight);
            }
            video.updatePixels();
            image(video, this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*4+this.padding*4+20);
        }
        //Pixelate as fourth effect
        if (this.fourthFaceEffect) {
            let pixelateFilterVideo = video.get();
            for (let i = 0; i < faces.length; i++) {
                let face = faces[i];
                let box = face.box;
                let xMin = Math.floor(box.xMin);
                let yMin = Math.floor(box.yMin);
                let boxWidth = Math.floor(box.width);
                let boxHeight = Math.floor(box.height);
                videoFilters.pixelateFilter(xMin, yMin, boxWidth, boxHeight, pixelateFilterVideo);
            }
            image(pixelateFilterVideo, this.firstImagePos.x, this.firstImagePos.y+this.videoHeight*4+this.padding*4+20);
        }
        push();
        //Highlighting the face detection option that was chosen
        for (let i = 1; i < 5; i++) {
            if (i === 1 && this.firstFaceEffect) {
                fill(255, 0, 0);
            }
            else if (i === 2 && this.secondFaceEffect) {
                fill(255, 0, 0);
            }
            else if (i === 3 && this.thirdFaceEffect) {
                fill(255, 0, 0);
            }
            else if (i === 4 && this.fourthFaceEffect) {
                fill(255, 0, 0);
            }
            else {
                fill(255);
            }
            textSize(16);
            text(i, this.numberOptionsX + (i - 1) * 25, this.numberOptionsY);
        }
        pop();
    }
    //Functions to hide and show sliders
    hideSliders() {
        thresholdSliderRed.hide();
        thresholdSliderGreen.hide();
        thresholdSliderBlue.hide();
        thresholdSliderHSV.hide();
        thresholdSliderCMY.hide();
    }
    showSliders() {
        thresholdSliderRed.show();
        thresholdSliderGreen.show();
        thresholdSliderBlue.show();
        thresholdSliderHSV.show();
        thresholdSliderCMY.show();
    }
    //Triggers filters on the incoming image if the image is different from the processedImg or if threshold has changed
    triggerFilters(img) {
        this.processedImg = img;
        this.grayscaleImg = imageFilters.grayscaleFilter(img);
        this.redChannelImg = imageFilters.redChannelFilter(img);
        this.greenChannelImg = imageFilters.greenChannelFilter(img);
        this.blueChannelImg = imageFilters.blueChannelFilter(img);
        this.thresholdImgRed = imageFilters.thresholdFilterRedChannel(imageFilters.redChannelFilter(img));
        this.thresholdImgGreen = imageFilters.thresholdFilterGreenChannel(imageFilters.greenChannelFilter(img));
        this.thresholdImgBlue = imageFilters.thresholdFilterBlueChannel(imageFilters.blueChannelFilter(img));
        this.hsvImg = imageFilters.HUEColorSpace(img);
        this.cmyImg = imageFilters.cmyFilter(img);
        this.thresholdImgHSV = imageFilters.HUEColorSpaceThreshold(img, thresholdSliderHSV.value());
        this.thresholdImgCMY = imageFilters.cmyFilterThreshold(img, thresholdSliderCMY.value());        
    }
    //Checks if the slider values have changed and returns true to trigger filters
    sliderValueChanged() {
        if (this.sliderRedValue !== thresholdSliderRed.value() || 
            this.sliderGreenValue !== thresholdSliderGreen.value() || 
            this.sliderBlueValue !== thresholdSliderBlue.value() || 
            this.sliderHSVValue !== thresholdSliderHSV.value() || 
            this.sliderCMYValue !== thresholdSliderCMY.value()) 
        {
            this.sliderRedValue = thresholdSliderRed.value();
            this.sliderGreenValue = thresholdSliderGreen.value();
            this.sliderBlueValue = thresholdSliderBlue.value();
            this.sliderHSVValue = thresholdSliderHSV.value();
            this.sliderCMYValue = thresholdSliderCMY.value();
            return true;
        }
        else return false;
    }
    //Activate first face detection effect
    activateFirstEffect() {
        this.firstFaceEffect = true;
        this.secondFaceEffect = false;
        this.thirdFaceEffect = false;
        this.fourthFaceEffect = false;
    }
    //Activate second face detection effect
    activateSecondEffect() {
        this.firstFaceEffect = false;
        this.secondFaceEffect = true;
        this.thirdFaceEffect = false;
        this.fourthFaceEffect = false;
    }
    //Activate third face detection effect
    activateThirdEffect() {
        this.firstFaceEffect = false;
        this.secondFaceEffect = false;
        this.thirdFaceEffect = true;
        this.fourthFaceEffect = false;
    }
    //Activate fourth face detection effect
    activateFourthEffect() {
        this.firstFaceEffect = false;
        this.secondFaceEffect = false;
        this.thirdFaceEffect = false;
        this.fourthFaceEffect = true;
    }
}