//////////////////////////////////
// COURSERA GRAPHICS PROGRAMMING
//////////////////////////////////
// Adapted from https://github.com/nature-of-code/
// released under MIT license
let ball;

function setup() {
    createCanvas(900, 600);
    ball = new Ball();
    background(0);
}

function draw() {
    ball.run();
}

class Ball {
    constructor() {
        this.velocity = new createVector(0,0);
        this.location = new createVector(width/2,height/2);
        this.prevLocation = new createVector(width/2,height/2);
        this.acceleration = new createVector(0,0);
        this.maxVelocity = 5;
    }
    run() {
        this.draw();
        this.move();
        this.edges();
    }
    draw() {
        stroke(255);
        strokeWeight(3);
        line(this.location.x,this.location.y,this.prevLocation.x,this.prevLocation.y);
        this.prevLocation = this.location.copy();
    }
    move() {
        let mouse = new createVector(mouseX,mouseY);
        let dir = p5.Vector.sub(mouse,this.location);
        dir.normalize();
        dir.mult(0.3);
        this.acceleration = dir;
        this.velocity.add(this.acceleration);
        this.velocity.limit(this.maxVelocity);
        this.location.add(this.velocity);
    }
    edges() {
        if (this.location.x<0) this.location.x=width;
        else if (this.location.x>width) this.location.x=0;
        else if (this.location.y<0) this.location.y=height;
        else if (this.location.y>height) this.location.y=0;
    }
}