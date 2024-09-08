// This file contains the class for video filters.
class VideoFilters {
    constructor() {
        //Matrix 5x5 for stronger blur filter
        this.matrix = [
            [1/256, 4/256, 6/256, 4/256, 1/256],
            [4/256, 16/256, 24/256, 16/256, 4/256],
            [6/256, 24/256, 36/256, 24/256, 6/256],
            [4/256, 16/256, 24/256, 16/256, 4/256],
            [1/256, 4/256, 6/256, 4/256, 1/256]
        ];
    }
    //Grayscale filter effect to a video region
    //I have built upon the example provided from lessons and code provided in Week 15 "grayscaleFilter"
    grayscaleFilter(xMin, yMin, width, height) {
        for (let x = xMin; x < xMin + width; x++) {
            for (let y = yMin; y < yMin + height; y++) {
                let index = (x + y * video.width) * 4;
                let r = video.pixels[index];
                let g = video.pixels[index + 1];
                let b = video.pixels[index + 2];
                let gray = (r + g + b) / 3;
                video.pixels[index] = video.pixels[index + 1] = video.pixels[index + 2] = gray;
            }
        }
    }
    //Blur filter effect to a video region
    //I have built upon the example provided from lessons and code provided in Week 15 "blurFilterTemplate"
    blurFilter(xMin, yMin, width, height) {
        for (let x = xMin; x < xMin + width; x++) {
            for (let y = yMin; y < yMin + height; y++) {
                let index = (x + y * video.width) * 4;
                let c = this.convolution(x, y, this.matrix, this.matrix.length);
                video.pixels[index] = c[0];
                video.pixels[index + 1] = c[1];
                video.pixels[index + 2] = c[2];
                video.pixels[index + 3] = 255;
            }
        }
    }
    convolution(x, y, matrix, matrixSize) {
        let totalRed = 0.0;
        let totalGreen = 0.0;
        let totalBlue = 0.0;
        let offset = Math.floor(matrixSize / 2);
        for (let i = 0; i < matrixSize; i++) {
            for (let j = 0; j < matrixSize; j++) {
                let xLoc = x + i - offset;
                let yLoc = y + j - offset;
                let index = (xLoc + yLoc * video.width) * 4;
                //ensure we don't address a pixel that doesn't exist
                index = constrain(index, 0, video.pixels.length - 1);

                totalRed += video.pixels[index] * matrix[i][j];
                totalGreen += video.pixels[index + 1] * matrix[i][j];
                totalBlue += video.pixels[index + 2] * matrix[i][j];
            }
        }
        return [totalRed, totalGreen, totalBlue];
    }
    /*
    Here I have used CMY(K) (Cyan Magenta Yellow (Black)) function to convert the image to CMY color space
    The function was taken from the resource PDF we were given for final project
    Colour Space Conversions
    Adrian Ford (ajoec1@wmin.ac.uk <defunct>)
    and Alan Roberts (Alan.Roberts@rd.bbc.co.uk).
    August 11, 1998(a)
    Page N.14
    */
    cmyFilter(xMin, yMin, width, height) {
        for (let x = xMin; x < xMin+width; x++) {
            for (let y = yMin; y < yMin+height; y++) {
                let index = (x + y * video.width) * 4;
                let r = video.pixels[index];
                let g = video.pixels[index + 1];
                let b = video.pixels[index + 2];
                let cmy = this.rgbToCMYConvert(r, g, b);
                let C = cmy[0];
                let M = cmy[1];
                let Y = cmy[2];

                video.pixels[index] = C;
                video.pixels[index + 1] = M;
                video.pixels[index + 2] = Y;
            }
        }
    }
    //Converts RGB to CMY
    rgbToCMYConvert(r, g, b) {
        let C = 255 - r;
        let M = 255 - g;
        let Y = 255 - b;
        return [C, M, Y];
    }
    //Pixelate filter effect to a video region
    pixelateFilter(xMin, yMin, width, height, pixelateFilterVideo) {
        if (!(pixelateFilterVideo instanceof p5.Image)) {
            console.error('pixelateFilterVideo is not a valid p5.Image object');
            return;
        }
        pixelateFilterVideo.loadPixels();
        //Applying grayscale filter to the region first
        this.grayscaleFilter(xMin, yMin, width, height);
        //Pixelating a region of 5x5 pixels
        for (let x = xMin; x < xMin + width; x += 5) {
            for (let y = yMin; y < yMin + height; y += 5) {
                let pixelIntensity = 0;
                let pixelCount = 0;
                //Inside the 5x5 region of pixels, calculating the intensity
                for (let i = 0; i < 5; i++) {
                    for (let j = 0; j < 5; j++) {
                        let xLoc = x + i;
                        let yLoc = y + j;
                        //Out of bounds check
                        if (xLoc < xMin + width && yLoc < yMin + height) {
                            let index = (xLoc + yLoc * video.width) * 4;
                            let r = pixelateFilterVideo.pixels[index];
                            let g = pixelateFilterVideo.pixels[index + 1];
                            let b = pixelateFilterVideo.pixels[index + 2];

                            //Calculating the pixel intensity
                            let intensity = 0.299 * r + 0.587 * g + 0.114 * b;
                            pixelIntensity += intensity;
                            pixelCount++;
                        }
                    }
                }
                let averageIntensity = pixelIntensity / pixelCount;
                //Applying the average pixel intensity to the 5x5 region of pixels
                for (let i = 0; i < 5; i++) {
                    for (let j = 0; j < 5; j++) {
                        let xLoc = x + i;
                        let yLoc = y + j;
                        if (xLoc < xMin + width && yLoc < yMin + height) {
                            let index = (xLoc + yLoc * pixelateFilterVideo.width) * 4;
                            pixelateFilterVideo.pixels[index] = averageIntensity;
                            pixelateFilterVideo.pixels[index + 1] = averageIntensity;
                            pixelateFilterVideo.pixels[index + 2] = averageIntensity;
                        }
                    }
                }
            }
        }
        pixelateFilterVideo.updatePixels();
    }
}