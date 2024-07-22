
let sunTexture;
let earthTexture;
let moonTexture;
let buffer;
let starLocs = [];

function preload() {
    sunTexture = loadImage("./assets/sun.jpg");
    earthTexture = loadImage("./assets/earth.jpg");
    moonTexture = loadImage("./assets/moon.jpg");
}

function setup() {
    createCanvas(900, 600, WEBGL);
    angleMode(DEGREES);
    buffer = createGraphics(1400,1400);
    
    
    for (let i = 0; i < 200; i++) {
        let pos = {
            x: random(0,buffer.width),
            y: random(0,buffer.height)
        }
        starLocs.push(pos);
    }
    console.log(starLocs);
    
}

function draw() {
    background(125);
    sky();
    camera(0,-300,600,0,0,0,0,1,0);
    
    push();    
    rotateY(frameCount/10);
    texture(sunTexture);
    sphere(100,50,50);
    pop();

    pointLight(255,255,255,0,0,0);
    pointLight(255,255,255,0,0,0);

    push();
    rotateY(frameCount/2); //Rotate around the sun
    translate(-300,0,0);
    rotateY(frameCount);  //Rotate on its own axis
    ambientMaterial(255,255,255);
    texture(earthTexture);
    sphere(40,40,50,50);
        push();
        translate(-100,0,0);
        rotateY(frameCount);
        texture(moonTexture);
        sphere(15,50,50);
        pop();
    pop();
    
    push();
    translate(0,100,-200);
    fill(0);
    rotateX(40);
    texture(buffer);
    plane(2400,2400,50,50);
    pop();
}

function sky() {
    buffer.background(0);
    buffer.fill(255);
    buffer.noStroke();
    for (let i = 0; i < starLocs.length; i++) {
        buffer.ellipse(starLocs[i].x,starLocs[i].y,3,3);
        if (random(0,1) < 0.01) {
            starLocs[i].x = random(0,buffer.width);
            starLocs[i].y = random(0,buffer.height);
        }
    }
}