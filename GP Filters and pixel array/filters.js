// This file contains the Filters class which contains functions for applying filters to images

class ImageFilters {
    constructor() {
    }
    //Grayscale filter function
    //I have built upon the example provided from lessons and code provided in Week 15 "grayscaleFilter"
    grayscaleFilter(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();
    
        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;
    
                let r = img.pixels[index];
                let g = img.pixels[index+1];
                let b = img.pixels[index+2];
                //Calculating the grayscale value and increasing brightness by 20%  
                let gray = ((r + g + b) / 3)*1.2;
                gray = constrain(gray, 0, 255); //will ensure that no pixel goes above 255 or below 0
    
                imgOut.pixels[index] = imgOut.pixels[index+1] = imgOut.pixels[index+2] = gray;
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Red Channel filter function
    redChannelFilter(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();
    
        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;
    
                let r = img.pixels[index];
    
                imgOut.pixels[index] = r;
                imgOut.pixels[index+1] = imgOut.pixels[index+2] = 0;
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Green Channel filter function
    greenChannelFilter(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();
    
        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;
    
                let g = img.pixels[index+1];
    
                imgOut.pixels[index+1] = g;
                imgOut.pixels[index] = imgOut.pixels[index+2] = 0;
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Blue Channel filter function
    blueChannelFilter(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();
    
        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;
    
                let b = img.pixels[index+2];
    
                imgOut.pixels[index+2] = b;
                imgOut.pixels[index] = imgOut.pixels[index+1] = 0;
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Threshold the image based on red channel values
    //I have built upon the example provided from lessons and code provided in Week 15 "thresholdFilter"
    thresholdFilterRedChannel(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();
    
        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;
    
                let r = img.pixels[index];
                
                let threshold = thresholdSliderRed.value();
                if (r > threshold) {
                    imgOut.pixels[index] = r;   
                }
                else {
                    imgOut.pixels[index] = 0;
                }
                img.pixels[index+1] = img.pixels[index+2] = 0;
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Threshold the image based on green channel values
    //I have built upon the example provided from lessons and code provided in Week 15 "thresholdFilter"
    thresholdFilterGreenChannel(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();
    
        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;
    
                let g = img.pixels[index+1];
        
                let threshold = thresholdSliderGreen.value();
                if (g > threshold) {
                    imgOut.pixels[index+1] = g;   
                }
                else {
                    imgOut.pixels[index+1] = 0;
                }
                imgOut.pixels[index] = imgOut.pixels[index+2] = 0;
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Threshold the image based on blue channel values
    //I have built upon the example provided from lessons and code provided in Week 15 "thresholdFilter"
    thresholdFilterBlueChannel(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();
    
        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;
    
                let b = img.pixels[index+2]; 
        
                let threshold = thresholdSliderBlue.value();
                if (b > threshold) {
                    imgOut.pixels[index+2] = b;   
                }
                else {
                    imgOut.pixels[index+2] = 0;
                }
                imgOut.pixels[index] = imgOut.pixels[index+1] = 0;
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    /*
    Here I have used Travis' HUEColorSpace function to convert the image to HSV color space
    The function was taken from the resource PDF we were given for final project
    Colour Space Conversions
    Adrian Ford (ajoec1@wmin.ac.uk <defunct>)
    and Alan Roberts (Alan.Roberts@rd.bbc.co.uk).
    August 11, 1998(a)
    Page N.15
    */
    HUEColorSpace(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();

        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;

                let r = img.pixels[index];  
                let g = img.pixels[index+1];
                let b = img.pixels[index+2];
                let hsv = this.rgbToHsv(r, g, b);
                let h = hsv[0];
                let s = hsv[1];
                let v = hsv[2];
                //We convert the HSV values back to RGB
                let newColor = color(h, s*255, v*255);
                imgOut.pixels[index] = red(newColor);
                imgOut.pixels[index+1] = green(newColor);
                imgOut.pixels[index+2] = blue(newColor);
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Thresholding the image based on HSV values
    //I have built upon the example provided from lessons and code provided in Week 15 "thresholdFilter"
    //But applying the threshold differently since I deal with HSV values
    HUEColorSpaceThreshold(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();

        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x+y*imgOut.width)*4;

                let r = img.pixels[index];  
                let g = img.pixels[index+1];
                let b = img.pixels[index+2];
                let hsv = this.rgbToHsv(r, g, b);
                let h = hsv[0];
                let s = hsv[1];
                let v = hsv[2];
                let threshold = thresholdSliderHSV.value();
                let newColor = color(h, s*255, v*255);
                //Modifying pixel values based on brightness v and threshold
                if (v * 255 > threshold) {
                    imgOut.pixels[index] = red(newColor);
                    imgOut.pixels[index+1] = green(newColor);
                    imgOut.pixels[index+2] = blue(newColor);  
                }
                else {
                    imgOut.pixels[index] = imgOut.pixels[index+1] = imgOut.pixels[index+2] = 0;
                }
                //We convert the HSV values back to RGB
                imgOut.pixels[index+3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //This function converts RGB to HSV
    rgbToHsv(r, g, b) {
        //I first normalize the values of RGB
        r /= 255;
        g /= 255;
        b /= 255;
        //Finding the min and max
        let max = Math.max(r, g, b);
        let min = Math.min(r, g, b);

        let h;
        let s = (max - min) / max;
        let v = max;
        //If the saturation is 0, the hue is undefined
        if (s === 0) {
            h = undefined;
        }
        //Otherwise, I calculate the hue
        else {
            let delta = max - min;
            let rPrime = (max - r) / (max - min);
            let gPrime = (max - g) / (max - min);
            let bPrime = (max - b) / (max - min);

            if (r === max && g === min) {
                h = 5 + bPrime;
            }
            else if (r === max && g != min) {
                h = 1 - gPrime;
            }
            else if (g === max && b === min) {
                h = rPrime + 1;
            }
            else if (g === max && b != min) {
                h = 3 - bPrime;
            }
            else if (r === max) {
                h = 3 + gPrime;
            }
            else {
                h = 5 - rPrime;
            }
            //I convert hue to degrees 
            h *= 60;
            //And ensure it is between 0 and 360
            h = h % 360;
        }
        return [h, s, v];
    }
    /*
    Here I have used CMY (Cyan Magenta Yellow) function to convert the image to CMY color space
    The function was taken from the resource PDF we were given for final project
    Colour Space Conversions
    Adrian Ford (ajoec1@wmin.ac.uk <defunct>)
    and Alan Roberts (Alan.Roberts@rd.bbc.co.uk).
    August 11, 1998(a)
    Page N.14
    */
    //CMY Color Space filter function
    cmyFilter(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();

        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x + y * imgOut.width) * 4;
                let r = img.pixels[index];
                let g = img.pixels[index + 1];
                let b = img.pixels[index + 2];
                let cmy = this.rgbToCMYConvert(r, g, b);
                let C = cmy[0];
                let M = cmy[1];
                let Y = cmy[2];

                imgOut.pixels[index] = C;
                imgOut.pixels[index + 1] = M;
                imgOut.pixels[index + 2] = Y;
                imgOut.pixels[index + 3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Thresholding the image based on CMY values
    //I have built upon the example provided from lessons and code provided in Week 15 "thresholdFilter"
    //But applying the threshold differently since I deal with CMY values
    cmyFilterThreshold(img) {
        let imgOut = createImage(img.width, img.height);
        imgOut.loadPixels();
        img.loadPixels();

        for (let x = 0; x < imgOut.width; x++) {
            for (let y = 0; y < imgOut.height; y++) {
                let index = (x + y * imgOut.width) * 4;
                let r = img.pixels[index];
                let g = img.pixels[index + 1];
                let b = img.pixels[index + 2];
                let cmy = this.rgbToCMYConvert(r, g, b);
                let C = cmy[0];
                let M = cmy[1];
                let Y = cmy[2];
                let threshold = thresholdSliderCMY.value();

                if (C < threshold && M < threshold && Y < threshold) {
                    C = 255;
                    M = 255;
                    Y = 255;
                }
                else {
                    C = 0;
                    M = 0;
                    Y = 0;
                }

                imgOut.pixels[index] = C;
                imgOut.pixels[index + 1] = M;
                imgOut.pixels[index + 2] = Y;
                imgOut.pixels[index + 3] = 255;
            }
        }
        imgOut.updatePixels();
        return imgOut;
    }
    //Converts RGB to CMY
    rgbToCMYConvert(r, g, b) {
        let C = 255 - r;
        let M = 255 - g;
        let Y = 255 - b;
        return [C, M, Y];
    }
}