/*

**Commentary:**

Image thresholding applies a binary decision to each pixel based on its intensity in a specific color channel. Pixels above the threshold become 
painted, while those below turn black, revealing unique aspects of the image's color composition. In my example, the red channel threshold appears 
brightest, likely due to skin tones and background colors. The green channel balances detail and contrast, and the blue channel appears darkest, 
indicating lower overall blue intensity.

These variations illustrate how color distribution varies across channels. Optimal thresholds depend on image factors like lighting and palette. 
Channel-specific thresholding has practical uses in image processing, such as using the red channel for skin detection or the green for edge 
detection. By thresholding individual color channels, we can isolate and analyze specific color information for tasks like object detection, 
segmentation, and color-based feature extraction.

Thresholding in color spaces like HSV and CMY provides an alternate approach to individual RGB channels. HSV thresholding, especially using the 
Value component, often results in smoother images with less noise, as Value correlates directly to brightness. However, RGB, CMY, and HSV are not 
perceptually uniform color spaces, meaning their numerical values don’t perfectly align with human color perception. For more accuracy, converting 
to a perceptually uniform color space like Lab and applying thresholds to the Lightness component can give results more consistent with how we 
perceive brightness. In our example, HSV thresholding appears noisier than RGB thresholds, while CMY thresholding, though clear, may not be 
perceptually accurate.

**Challenges and Solutions:**

One problem encountered was with the `createFileInput` function in p5.js, which took time to debug. I was incorrectly using the `loadImage` method 
with the callback function and trying to access the wrong method from `createFileInput`, which resulted in errors within the p5 code. The issue 
was eventually resolved by correctly using the `handleFile` method and the `loadImage` method with the appropriate parameters.

Another challenge was applying filters directly to the video. It became evident that creating a copy of the video and applying filters to the 
copy, rather than the original, provided a solution. The four primary face effects were managed by toggling booleans to ensure only one effect 
took place at a time.

**Project Completion:**

Although the project plan was delayed slightly, it was successfully completed five days before the deadline, although with some stress. Overall, 
the initial goals were met.

**App Extension:**

The implemented extension involved using ML5 for face and hand detection. The face detection drew keypoints and applied grayscale and pixelate 
filters to the eyes region only. For hand detection, keypoints were analyzed to identify an "OK" sign and a "V" (peace) sign. When an "OK" sign 
is detected, the app overlays a red text indicating its recognition. For a "V" sign, the region of the hand is extracted from the video, a filter 
is applied, and the updated pixels are reinserted into the video. This feature is unique because it integrates machine learning with real-time 
video processing, enhancing interactivity.

Additionally, another extension allows users to load their own images into the app, upon which various filters are applied. This utilizes the 
`createFileInput` method from p5.js and employs the `handleFile` callback method to manage the image upload process. This enhances user control 
and interaction by allowing personalized content to be processed using the app's filtering capabilities.

*/

let video;
let inputImage;
let filters, imageGenerator;
let faceMesh;
let handPose;
let options;
let faces = [];
let hands = [];
let extension;
let extensionFilters;
let fileInput;
//Required fr ML5.js face detection https://ml5js.org/
function preload() {
    options = {
        maxFaces: 2, 
        refineLandmarks: false,
        flipped: false
    }
    faceMesh = ml5.faceMesh(options);
    handPose = ml5.handPose();
}
/////////////////////////////////////////////////////////////////
//Setting up the necessary classes, file processing, ML5.js and video for canvas
function setup() {
    imageFilters = new ImageFilters();
    videoFilters = new VideoFilters();
    imageGenerator = new ImageGenerator();
    extensionFilters = new ExtensionFilters();
    createCanvas(640, 1060);
    pixelDensity(1);
    video = createCapture(VIDEO);
    video.size(160, 120);
    video.hide();
    noStroke();
    fill(255);
    faceMesh.detectStart(video, gotFaces);
    handPose.detectStart(video, gotHands);
    extension = false;
    //File processing for loading an image from disk
    fileInput = createFileInput(handleFile);
    fileInput.hide();
}

/////////////////////////////////////////////////////////////////
function draw() {
    background(0);
    //Assignment general view
    if (!extension) {
        fill(255);
        text("Press SPACE to capture an image while live video is running", 40, 60);
        text("Live Video", 40, 100);
        image(video, 40, 120);

        if(inputImage) {
            imageGenerator.drawImages(inputImage);
        }
        video.loadPixels();

    }
    //Extension view
    else {
        fill(255);
        text("This is the extension VIEW", 40, 60);
        text("Live Video", 40, 100);
        image(video, 40, 120);
        imageGenerator.hideSliders();
        extensionFilters.drawExtension();
        video.loadPixels();
    }
}

function keyPressed() {
    //Creates an image from the video feed, to be filtered under the normal assignment view only
    if (!extension) {
        if (key == ' ') {
            inputImage = createImage(160, 120);   
            inputImage.copy(video, 0, 0, video.width, video.height, 0, 0, video.width, video.height);  
        }
        //Switching between different face effects
        if (key == 1) {
            imageGenerator.activateFirstEffect();
        }
        if (key == 2) {
            imageGenerator.activateSecondEffect();
        }
        if (key == 3) {
            imageGenerator.activateThirdEffect();
        }
        if (key == 4) {
            imageGenerator.activateFourthEffect();
        }
    }
}
//Required for ML5.js face detection
function gotFaces(results) {
    faces = results;
}
//Required for ML5.js hand detection
function gotHands(results) {
    hands = results;
}
//Toggling between extension and normal assignment
function myButton(event) {
    extension = !extension;
    //Remove focus from the button to avoid a bug of toggling between views with space when capturing images
    event.target.blur(); 
}
//Loading an image from disk for filtering effects
//This is an extension to the project as the base project already works with an image
//from the webcam
function loadImageBtn(event) {
    if (!extension) {
        fileInput.elt.click();
    }
    else {
        alert("Please switch to the normal assignment view to load an image");
    }
    event.target.blur();
}
//Function to handle the file input
//and loading the image to the inputImage variable
//looked into https://p5js.org/reference/p5/createFileInput/ to see how to process this
function handleFile(file) {
    if (file.type === 'image') {
        loadImage(file.data, (img) => {
            img.resize(160, 120);
            inputImage = createImage(160, 120);
            inputImage.copy(img, 0, 0, img.width, img.height, 0, 0, img.width, img.height);
        });
    } else {
      console.error("Not a valid image file.");
    }
}