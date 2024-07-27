/////////////////////////////////////
// COURSERA GRAPHICS PROGRAMMING
/////////////////////////////////////
// Sea nettles image is taken from Wikipedia
// it is released under a creative commons license:
// https://es.wikipedia.org/wiki/Chrysaora#/media/Archivo:Six-Sea-Nettles.jpg
let imgIn;

function preload() {
    imgIn = loadImage("assets/seaNettles.jpg");
}
//////////////////////////////////////////////////////////////////////
function setup() {
    createCanvas((imgIn.width * 2)+20, imgIn.height);
    pixelDensity(1);
    imgOut = createImage(imgIn.width, imgIn.height);
}
//////////////////////////////////////////////////////////////////////
function draw() {
    background(255);
    image(imgIn, 0, 0, imgIn.width, imgIn.height);
    image(greyscaleFilter(imgIn), imgIn.width+20, 0, imgIn.width, imgIn.height);
}
//////////////////////////////////////////////////////////////////////
function greyscaleFilter(img){
    let imgOut = createImage(img.width, img.height);
    imgOut.loadPixels();
    img.loadPixels();

    for (x = 0; x < imgOut.width; x++) {
        for (y = 0; y < imgOut.height; y++) {

            let index = (x + y * imgOut.width) * 4;

            let r = img.pixels[index + 0];
            let g = img.pixels[index + 1];
            let b = img.pixels[index + 2];

            //let gray = (r + g + b) / 3; // simple
            let gray = r * 0.299 + g * 0.587 + b * 0.114; // LUMA ratios 

            imgOut.pixels[index+0]= imgOut.pixels[index+1] = imgOut.pixels[index+2] = gray;
            imgOut.pixels[index+3]= 255;
        }
    }
    imgOut.updatePixels();
    return imgOut;
}
