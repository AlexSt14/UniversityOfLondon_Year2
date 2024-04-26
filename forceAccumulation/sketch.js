//////////////////////////////////
// COURSERA GRAPHICS PROGRAMMING
//////////////////////////////////
// Adapted from https://github.com/nature-of-code/
// released under MIT license

var balls;
////////////////////////////////////////////////////
function setup() {
  createCanvas(900, 600);
  balls = [];
}
////////////////////////////////////////////////////
function draw() {
  background(0);
  for(var i = 0; i < balls.length; i++) {
    var gravity = createVector(0, 0.1);
    var friction = balls[i].velocity.copy();
    friction.mult(-1);
    friction.normalize();
    friction.mult(0.02);
    balls[i].applyForce(friction);
    balls[i].applyForce(gravity);
    if(balls[i].age < 0 && balls.length>1) {
      let index = balls.indexOf(balls[i]);
      balls.splice(index,1);
      console.log(balls.length);
    }
    balls[i].run();
  }  
  fill(255,0,0,150);
  rect(width/2-50,height/2-50,100,100);
}
function mouseDragged() {
  balls.push(new Ball(mouseX, mouseY));
}
function keyPressed() {
  if(key === "k") {
    balls = [];
    console.log("Key pressed  ")
  }
}
//////////////////////////////////////////////////////
class Ball {

  constructor(x, y){
    this.velocity = new createVector(random(-3,3),random(-3,3));
    this.location = new createVector(x, y);
    this.acceleration = new createVector(0, 0);
    this.size = random(50,15);
    this.age = 255;
    this.color = {
      r: 125,
      g: 0,
      b: 110,
    };
  }

  run(){
    this.draw();
    this.move();
    this.bounce();
    this.age -= 0.75;
  }

  draw(){
    if(dist(this.location.x,this.location.y,width/2,height/2)<this.size/2+50) {
      this.color = {
        r:255,
        g:0,
        b:0,
      }
    }
    fill(this.color.r,this.color.g,this.color.b,this.age);
    ellipse(this.location.x, this.location.y, this.size, this.size);
    
  }

  move(){
    this.velocity.add(this.acceleration);
    this.location.add(this.velocity);
    this.acceleration.mult(0);
  }

  bounce(){
    if (this.location.x > width-this.size/2) {
          this.location.x = width-this.size/2;
          this.velocity.x *= -1;
    } else if (this.location.x < this.size/2) {
          this.velocity.x *= -1;
          this.location.x = this.size/2;
    }
    if (this.location.y > height-this.size/2) {
          this.velocity.y *= -1;
          this.location.y = height-this.size/2;
    }
  }

  applyForce(force){
    this.acceleration.add(force);
  }
}
