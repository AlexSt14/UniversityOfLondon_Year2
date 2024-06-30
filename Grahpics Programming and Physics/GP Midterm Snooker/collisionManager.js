//Managing collision with pockets and balls, updating score and matrix
class CollisionManager {
    constructor(snookerTable) {
        this.snookerTable = snookerTable;
        this.setupCollisionListener();
        this.createCollisionMatrix();
        this.collisionColor = 'green';
        this.defaultColor = 'black';
        this.coloredBallCounter = 0;
    }
    //Setting up a matrix for collisions showing to user
    createCollisionMatrix() {
        this.matrix = [
            ['', 'Colored', 'Red Ball', 'Cushion'],
            ['Cue', '', '', '']
        ];
        this.matrixColors = [
            ['black', 'black', 'black', 'black'],
            ['black', 'black', 'black', 'black']
        ]
    }
    //Drawing the matrix to the canvas
    drawCollisionMatrix() {
        push();
        textAlign(CENTER, BOTTOM); 
        textSize(16);
        let matrixCellWidth = 70;
        let matrixCellHeight = 30;
        let startX = width/2 - matrixCellWidth;
        let startY = 50;
        for (let i = 0; i < this.matrix.length; i++) {
            for (let j = 0; j < this.matrix[i].length; j++) {
                fill(this.matrixColors[i][j]);
                stroke(255);
                strokeWeight(2);
                rect(startX + j*matrixCellWidth, startY + i*matrixCellHeight, matrixCellWidth, matrixCellHeight);
                noStroke();
                fill(255);
                text("Collisions", width/2-70, 30);
                text(this.matrix[i][j], startX + j*matrixCellWidth + matrixCellWidth/2-35, startY + i*matrixCellHeight + matrixCellHeight/2);
            }
        }
        pop();
    }
    //Listening for collisions in the engine
    setupCollisionListener() {
        Matter.Events.on(engine, 'collisionStart', (event) => {
            this.handleCollision(event);
        });
    }
    //Handles the collisions
    handleCollision(event) {
        let pairs = event.pairs;
        pairs.forEach(pair => {
            let bodyA = pair.bodyA;
            let bodyB = pair.bodyB;
            //Checking if one of the bodies is the cue ball
            if (this.checkCueBall(bodyA) || this.checkCueBall(bodyB)) {
                let otherBody;
                if (this.checkCueBall(bodyA)) otherBody = bodyB;
                else otherBody = bodyA;
                this.promptCollisionType(otherBody);
            }
        });
    }
    //Checking if the body is the cueball
    checkCueBall(body) {
        return body.label === 'cueBall';
    }

    //Prompts the collision type
    promptCollisionType(otherBody) {
        if (otherBody.label === 'angledSide') {
            console.log('Cue-cushion collision');
            this.matrixColors[1][3] = this.collisionColor;
        } else if (otherBody.label === 'ball') {
            console.log('Cue-red ball collision');
            this.matrixColors[1][2] = this.collisionColor;
        } 
        //Checking for colored ball collisions
        this.snookerTable.balls.forEach(ball => {
            if (ball.label === otherBody.label && ball.label !== 'ball') {
                console.log('Cue-colored ball collision');
                this.matrixColors[1][1] = this.collisionColor;
            }
        });
        this.resetCollisionMatrixColors();
    }   
    //Resetting colors of the matrix to black after collision after 1.8 seconds
    resetCollisionMatrixColors() {
        setTimeout(() => {
            this.matrixColors.forEach((row, i) => {
                this.matrixColors[i] = row.map(() => this.defaultColor);
            });
        }, 1800);
    }
    //Checking for pocket collisions
    checkPockets() {
        const pocketTreshold = (this.snookerTable.pocketRadius - this.snookerTable.ballsRadius)+7;
        const pockets = [this.snookerTable.pocket1, this.snookerTable.pocket2, this.snookerTable.pocket3,
                        this.snookerTable.pocket4, this.snookerTable.pocket5, this.snookerTable.pocket6];

        //Using the dist function to check if the ball is in the pocket, iterating over all the balls
        this.snookerTable.balls.forEach(ball => {
            pockets.forEach(pocket => {
                if (dist(ball.body.position.x, ball.body.position.y, pocket.position.x, pocket.position.y) < pocketTreshold) {
                    this.removeBall(ball.body);
                }
            });
        });
        //In case of user pocketing a colored ball twice in a row, we alert the user of the fault
        if (this.coloredBallCounter >= 2) {
            alert("Fault! You have pocketed a colored ball twice in a row!");
            this.coloredBallCounter = 0;
        }
    }
    //Function to remove a ball from the world depending on what type of ball it is
    removeBall(ball) {
        if (ball.label === 'ball') {
            World.remove(engine.world, ball);
            this.snookerTable.balls = this.snookerTable.balls.filter(b => b.body !== ball);
            this.coloredBallCounter = 0;
        }
        else if (ball.label === 'cueBall') {
            World.remove(engine.world, ball);
            this.snookerTable.balls = this.snookerTable.balls.filter(b => b.body !== ball);
            this.snookerTable.ballManager.drawCueBall();
            alert('Fault! You have pocketed the cue ball! You can place back the cue ball inside the arc!')
        }
        else {
            World.remove(engine.world, ball);
            this.snookerTable.balls = this.snookerTable.balls.filter(b => b.body !== ball);
            this.snookerTable.ballManager.addColoredBall(ball);
            this.coloredBallCounter++;
        }
    }
}