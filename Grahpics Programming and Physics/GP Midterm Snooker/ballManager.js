//Managing the balls positions and creating them
let isAltPressed = false;       //In order to place the cue ball, the user has to press the Alt key and mouse
class BallManager {
    constructor(snookerTable) {
        this.snookerTable = snookerTable;
        this.cueBallID;
        this.cueBallBody;
        //Saving the initial positions of the colored balls
        this.coloredBallsPositions = [
            {x: this.snookerTable.x-this.snookerTable.width/3+30, y: this.snookerTable.y+75, color: 'yellow'},
            {x: this.snookerTable.x-this.snookerTable.width/3+30, y: this.snookerTable.y-75, color: 'green'},
            {x: this.snookerTable.x-this.snookerTable.width/3+30, y: this.snookerTable.y, color: 'orange'},
            {x: this.snookerTable.x, y: this.snookerTable.y, color: 'blue'},
            {x: this.snookerTable.x+this.snookerTable.width/4-23, y: this.snookerTable.y, color: 'pink'},
            {x: this.snookerTable.x+this.snookerTable.width/2-40, y: this.snookerTable.y, color: 'black'}
        ]
    }
    //Functions to set the starting positions of the balls
    setStartingPositions() {
        this.clearBalls();
        this.placeColoredBalls();
        //Placing the red balls in a triangle shape
        this.placeRedBallsInTriangle(this.snookerTable.x+this.snookerTable.width/4, this.snookerTable.y, this.snookerTable.ballsRadius);
    }
    setRandomRedPositionsReds() {
        this.clearBalls();
        this.placeColoredBalls();
        //Placing the red balls in random positions
        for (let i = 0; i < 15; i++) {
            let x = random(this.snookerTable.x-this.snookerTable.width/4, this.snookerTable.x+this.snookerTable.width/4);
            let y = random(this.snookerTable.y-this.snookerTable.height/2+50, this.snookerTable.y+this.snookerTable.height/2-50);
            this.snookerTable.balls.push(new Ball(x, y, this.snookerTable.ballsRadius, 'red'));
        }
    }
    setRandomAllPositions() {
        this.clearBalls();
        //Placing the red balls in random positions
        for (let i = 0; i < 15; i++) {
            let x = random(this.snookerTable.x-this.snookerTable.width/4, this.snookerTable.x+this.snookerTable.width/4);
            let y = random(this.snookerTable.y-this.snookerTable.height/2+50, this.snookerTable.y+this.snookerTable.height/2-50);
            this.snookerTable.balls.push(new Ball(x, y, this.snookerTable.ballsRadius, 'red'));
        }
        //Placing the colored balls in random positions
        let colors = ['yellow', 'green', 'orange', 'blue', 'pink', 'black'];
        for (let i = 0; i < 6; i++) {
            let x = random(this.snookerTable.x-this.snookerTable.width/4, this.snookerTable.x+this.snookerTable.width/4);
            let y = random(this.snookerTable.y-this.snookerTable.height/2+50, this.snookerTable.y+this.snookerTable.height/2-50);
            this.snookerTable.balls.push(new Ball(x, y, this.snookerTable.ballsRadius, colors[i]));
        }
    }
    clearBalls() {
        //Removing all balls from the world except the white one
        this.snookerTable.balls.forEach(ball => {
            if (ball.color !== 'white') {
                World.remove(engine.world, ball.body);
            }
        });
        //Keeping only the white ball in the array
        this.snookerTable.balls = this.snookerTable.balls.filter(ball => ball.color === 'white');
        //If obstacles are active, then removing obstacles too
        if (this.snookerTable.obstaclesActive) {
            this.snookerTable.obstaclesChallenge.removeObstacles();
        }
    }
    //Function to place the red balls in a triangle shape
    placeRedBallsInTriangle(startPositionX, startPositionY, ballRadius) {
        let x = startPositionX;
        let y = startPositionY;
        let rows = 5;
        for (let i = 0; i < rows; i++) {
            for (let j = 0; j <= i; j++) {
                this.snookerTable.balls.push(new Ball(x, y, ballRadius, 'red'));
                y += ballRadius * 2 * Math.sqrt(3)/1.6;
            }
            y = startPositionY - ballRadius * i-12;
            x += ballRadius * 2 * 0.85;
        }
    }
    //Function to place the colored balls in correct positions
    placeColoredBalls() {
        //Drawing colored balls. NO Red balls
        this.coloredBallsPositions.forEach(ball => {
            this.snookerTable.balls.push(new Ball(ball.x, ball.y, this.snookerTable.ballsRadius, ball.color));
        });
    }
    //Function to add balls to the world after we removed them
    addBallsToWorld() {
        this.snookerTable.balls.forEach(ball => {
            World.add(engine.world, ball.body);
        });
    }
    //Function to draw the cue ball wherever the user clicks while pressing alt
    drawCueBall(mouseX, mouseY) {
        this.cueBallBody = this.snookerTable.balls.find(ball => ball.color === 'white'); 
        if (this.cueBallBody) {
            this.cueBallID = this.cueBallBody.body.id;
        }
        //This will prevent the user from adding multiple cue balls 
        //It will also check if the mouse is within the boundaries of the arc before placing the cue ball   
        if (!this.cueBallBody) {
            if (this.snookerTable.isMouseInArc()) {
                //Drawing the cue ball
                let cueBall = new Ball(mouseX, mouseY, this.snookerTable.ballsRadius, 'white')
                this.snookerTable.balls.push(cueBall);
                //Adding it to the world
                World.add(engine.world, cueBall.body);
                console.log(this.snookerTable.balls);
            }
        }
    }
    //Function to add back a colored ball to the world, to the original position
    addColoredBall(ball) {
        for (let i = 0; i < this.coloredBallsPositions.length; i++) {
            if (this.coloredBallsPositions[i].color === ball.label) {
                this.snookerTable.balls.push(new Ball(this.coloredBallsPositions[i].x, this.coloredBallsPositions[i].y, this.snookerTable.ballsRadius, this.coloredBallsPositions[i].color));
                World.add(engine.world, this.snookerTable.balls[this.snookerTable.balls.length-1].body);
            }
        }
    }
}