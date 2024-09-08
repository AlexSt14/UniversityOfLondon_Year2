/* Class for extension of the assignment, playing around with mi5.js and its features*/

class ExtensionFilters {
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
    }
    //Keypoints filter effect to a video region
    keypointsFilter() {
        for (let i = 0; i < faces.length; i++) {
            let face = faces[i];
            for (let i = 0; i < face.keypoints.length; i++) {
                let x = face.keypoints[i].x;
                let y = face.keypoints[i].y;
                //once we have the keypoints we draw green elipses around them
                push();
                fill(0, 255, 0);
                ellipse(x + this.secondImagePos.x, y+this.secondImagePos.y, 1.5, 1.5);
                pop();
            }
        }
        
    }
    //pixelate filter effect to eyes region using ml5.js
    pixelateEyeFilter(pixelateFilterVideo) {
        for (let i = 0; i < faces.length; i++) {
            let face = faces[i];
            let leftEyebrow = face.leftEyebrow;
            let rightEyebrow = face.rightEyebrow;
            let faceOval = face.faceOval;
            let rightEyebrowX = Math.floor(rightEyebrow.x);
            let rightEyebrowY = Math.floor(rightEyebrow.y);
            let eyebrowsWidth = abs(Math.floor(rightEyebrow.x - leftEyebrow.x))+leftEyebrow.width;
            let eyebrowsHeight = abs(Math.floor(faceOval.y - leftEyebrow.y))+leftEyebrow.height;
            videoFilters.pixelateFilter(rightEyebrowX, rightEyebrowY, eyebrowsWidth, eyebrowsHeight, pixelateFilterVideo);
        }
    }
    //Hands detection filter effect to a video region
    handsDetection() {
        for (let i = 0; i < hands.length; i++) {
            let hand = hands[i];
            for (let j = 0; j < hand.keypoints.length; j++) {
                let x = Math.floor(hand.keypoints[j].x);
                let y = Math.floor(hand.keypoints[j].y);
                push();
                fill(0, 255, 0);
                ellipse(x + this.firstImagePos.x, y+this.firstImagePos.y + video.height + this.padding+20, 3, 3);
                pop();
            }
        }
    }
    //Fingers detection filter effect to a video region
    middleFinger(handsVideo) {
        for (let i = 0; i < hands.length; i++) {
            let hand = hands[i];
            if(this.middleFingerDetection(hand)) {
                let handWidth = abs(Math.floor(dist(hand.thumb_ip.x, hand.thumb_ip.y, hand.pinky_finger_pip.x, hand.pinky_finger_pip.y)+30));
                let handHeight = abs(Math.floor(dist(hand.middle_finger_tip.x, hand.middle_finger_tip.y, hand.wrist.x, hand.wrist.y)));
                let xMin = Math.floor(min(hand.thumb_ip.x, hand.pinky_finger_pip.x))-15;
                let yMin = Math.floor(hand.middle_finger_tip.y);
                videoFilters.pixelateFilter(xMin, yMin, handWidth, handHeight, handsVideo);
            }
        }
    }
    middleFingerDetection(hand) {
        if(this.middleFingerVsOther(hand.middle_finger_tip, hand.ring_finger_tip) && this.middleFingerVsOther(hand.middle_finger_tip, hand.pinky_finger_tip) 
        && this.middleFingerVsOther(hand.middle_finger_tip, hand.thumb_tip) && this.middleFingerVsOther(hand.middle_finger_dip, hand.ring_finger_tip) 
        && this.middleFingerVsOther(hand.middle_finger_dip, hand.pinky_finger_tip) && this.middleFingerVsOther(hand.middle_finger_dip, hand.thumb_tip)
        && this.middleFingerVsOther(hand.index_finger_tip, hand.middle_finger_pip)){
            return true;
        }
        return false;
    }
    //Checks if middle finger tip is up vs other finger
    middleFingerVsOther(middleFinger, otherFinger) {
        if (middleFinger.y < otherFinger.y) {
            return true;
        }
        return false;
    }
    //Ok gesture detection filter effect to a video region
    okGesture() {
        for (let i = 0; i < hands.length; i++) {
            let hand = hands[i];
            if(this.okGestureDetection(hand)) {
                push();
                fill(255, 0, 0);
                text("OK Gesture Detected", this.thirdImagePos.x, this.thirdImagePos.y + video.height + this.padding+32);
                pop();
                let xMin = Math.floor(hand.thumb_tip.x) - 10;
                let yMin = Math.floor(hand.thumb_tip.y) - 10;
                let width = 80;
                let height = 80;
                videoFilters.blurFilter(xMin, yMin, width, height);
            }
        }
    }
    okGestureDetection(hand) {
        if(abs(dist(hand.thumb_tip.x, hand.thumb_tip.y, hand.index_finger_tip.x, hand.index_finger_tip.y)) < 8 && 
        abs(dist(hand.thumb_ip.x, hand.thumb_ip.y, hand.ring_finger_tip.x, hand.ring_finger_tip.y)) > 15 && 
        abs(dist(hand.thumb_ip.x, hand.thumb_ip.y, hand.middle_finger_tip.x, hand.middle_finger_tip.y)) > 15){
            return true;
        }
        return false;
    }
    //Draw extension view to canvas
    drawExtension() {
        text("Facemesh keypoints", this.secondImagePos.x, 100);
        image(video, this.secondImagePos.x, this.secondImagePos.y);
        this.keypointsFilter();

        let pixelateFilterVideo = video.get();
        this.pixelateEyeFilter(pixelateFilterVideo);
        text("Pixelate eyes", this.thirdImagePos.x, 100);
        image(pixelateFilterVideo, this.thirdImagePos.x, this.thirdImagePos.y);

        text("Hands detection keypoints", this.firstImagePos.x, this.firstImagePos.y + video.height + this.padding);
        image(video, this.firstImagePos.x, this.firstImagePos.y + video.height + this.padding+20);        
        this.handsDetection();

        text("Symbol of peace sign", this.secondImagePos.x, this.secondImagePos.y + video.height + this.padding);
        let handsVideo = video.get();
        this.middleFinger(handsVideo);
        image(handsVideo, this.secondImagePos.x, this.secondImagePos.y + video.height + this.padding+20);

        text("Ok hand gesture", this.thirdImagePos.x, this.thirdImagePos.y + video.height + this.padding);
        image(video, this.thirdImagePos.x, this.thirdImagePos.y + video.height + this.padding+20);
        this.okGesture();
    }
}