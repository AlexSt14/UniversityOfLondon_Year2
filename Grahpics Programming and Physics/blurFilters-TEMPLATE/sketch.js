/////////////////////////////////////
// COURSERA GRAPHICS PROGRAMMING
/////////////////////////////////////
// code adapted from Coding Train (https://thecodingtrain.com/)
// released under MIT license by Daniel Shiffman

// Sea nettles image is taken from Wikipedia
// it is released under a creative commons license:
// https://es.wikipedia.org/wiki/Chrysaora#/media/Archivo:Six-Sea-Nettles.jpg
var imgIn;
let matrix = [
    [1/16, 2/16, 1/16],
    [2/16, 4/16, 2/16],
    [1/16, 2/16, 1/16]
]

function preload() {
    imgIn = loadImage("assets/seaNettles.jpg");
}
/////////////////////////////////////////////////////////////
function setup() {
    createCanvas((imgIn.width * 2) + 20, imgIn.height);
    pixelDensity(1);
}
/////////////////////////////////////////////////////////////
function draw() {
    background(255);

    image(imgIn, 0, 0);
    image(blur(imgIn), imgIn.width + 20, 0);
    noLoop();
}
/////////////////////////////////////////////////////////////
function blur(img){
  var imgOut = createImage(img.width, img.height);

  let matrixSize = matrix.length;
  imgOut.loadPixels();
  img.loadPixels();

  // read every pixel
  for (var x = 0; x < imgOut.width; x++) {
      for (var y = 0; y < imgOut.height; y++) {

          var index = (x + y * imgOut.width) * 4;

          let c = convolution(x, y, matrix, matrixSize, imgIn);

          imgOut.pixels[index + 0] = c[0];
          imgOut.pixels[index + 1] = c[1];
          imgOut.pixels[index + 2] = c[2];
          imgOut.pixels[index + 3] = 255;
      }
  }
  imgOut.updatePixels();
  return imgOut;
}
function convolution(x, y, matrix, matrixSize, img) {
    let totalRed = 0;
    let totalGreen = 0;
    let totalBlue = 0;

    let offset = Math.floor(matrixSize / 2);

    for (let i = 0; i < matrixSize; i++) {
        for (let j = 0; j < matrixSize; j++) {
            let xLoc = x + i - offset;
            let yLoc = y + j - offset;

            let index = (img.width * yLoc + xLoc) * 4;

            index = constrain(index, 0, img.pixels.length - 1);

            totalRed += img.pixels[index + 0] * matrix[i][j];
            totalGreen += img.pixels[index + 1] * matrix[i][j];
            totalBlue += img.pixels[index + 2] * matrix[i][j];
        }
    }
    return [totalRed, totalGreen, totalBlue];
}