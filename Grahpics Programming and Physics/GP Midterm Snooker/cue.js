//Managing and creating the cue
let isSpacePressed = false;     //In order to use the cue, the user has to press the space key and mouse simultaneously
class Cue {
    constructor(snookerTable) {
        this.snookerTable = snookerTable;
        this.angle = 0;
        this.power = 0;
        this.length = 200; 
        this.maxLength = 400;   
        this.isDrawing = false;
    }
    //Updating the angle and power of the cue based on the cue ball
    update(mouseX, mouseY) {
        if (this.isDrawing) {
            let whiteBall = this.snookerTable.balls.find(ball => ball.color === 'white');
            this.angle = atan2(mouseY - whiteBall.body.position.y, mouseX - whiteBall.body.position.x);
            this.power = dist(mouseX, mouseY, whiteBall.body.position.x, whiteBall.body.position.y);
        }
    }
    //Drawing the cue
    draw() {
        let whiteBall = this.snookerTable.balls.find(ball => ball.color === 'white');
        let cueBallVelocity, speed;
        if (whiteBall) {
            cueBallVelocity = whiteBall.body.velocity;
            speed = Math.sqrt(cueBallVelocity.x*cueBallVelocity.x + cueBallVelocity.y*cueBallVelocity.y);
        }
        //Drawing the cue only if the speed is low enough
        if (whiteBall && speed < 0.025) {
            push();
            translate(whiteBall.body.position.x, whiteBall.body.position.y);
            strokeWeight(5);
            stroke(139,69,19);
            rotate(this.angle);
            let cueLength = constrain(this.length + this.power, this.length, this.maxLength);   
            line(whiteBall.radius+10+this.power/20, 0, cueLength, 0);
            pop();
        }
    }
    //Controlling the hit of the cue and the power
    hit() {
        let whiteBall = this.snookerTable.balls.find(ball => ball.color === 'white'); 
        if (whiteBall) {
            //This controls the power of the hit
            let force = p5.Vector.fromAngle(this.angle).mult(-1).mult(this.power*0.05);  
            Matter.Body.setVelocity(whiteBall.body, {x: force.x, y: force.y});
        }
        this.isDrawing = false;
        this.power = 0;
    }
}