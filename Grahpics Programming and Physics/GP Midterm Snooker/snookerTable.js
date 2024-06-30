//Drawing the snooker table using fromVertices
class SnookerTable {
    constructor(x, y, width, height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.balls = [];
        this.cueBall;
        this.ballsRadius = (this.width/36)/2;   //Calculating the ball radius
        this.pocketRadius = this.ballsRadius * 1.5;    //Calculating the pocket radius based on the ball radius
        this.angledSidesRestitution = 1;
        //drawing surface of the table
        this.surface = Bodies.rectangle(this.x, this.y, this.width+40, this.height+40, { isStatic: true, label: 'tableSurface', isSensor: true, friction: 0.5 });
        //drawing the angled sides / cushions of the table
        this.verticesLeft = [
            { x: this.x - this.width/2-15, y: this.y - this.height/2+15 },
            { x: this.x - this.width/2+15, y: this.y - this.height/2+40 },
            { x: this.x - this.width/2+15, y: this.y + this.height/2-35 },
            { x: this.x - this.width/2-15, y: this.y + this.height/2 }
        ];
        this.verticesRight = [
            { x: this.x + this.width/2-14, y: this.y - this.height/2+35 },
            { x: this.x + this.width/2+15, y: this.y - this.height/2 },
            { x: this.x + this.width/2+15, y: this.y + this.height/2-10 },
            { x: this.x + this.width/2-14, y: this.y + this.height/2-35 }
        ];
        this.verticesTop = [
            { x: this.x - this.width/2+17, y: this.y - this.height/2-10 },
            { x: this.x-5, y: this.y - this.height/2-10 },
            { x: this.x-25, y: this.y - this.height/2+15 },
            { x: this.x - this.width/2+50, y: this.y - this.height/2+15 }
        ];
        this.verticesBottom = [
            { x: this.x - this.width/2+50, y: this.y + this.height/2-25 },
            { x: this.x-10, y: this.y + this.height/2 },
            { x: this.x-30, y: this.y + this.height/2-25 },
            { x: this.x - this.width/2+15, y: this.y + this    .height/2 }
        ];
        this.verticesTop2 = [
            { x: this.x+45, y: this.y - this.height/2-10 },
            { x: this.x+this.width/2+25, y: this.y - this.height/2-10 },
            { x: this.x+this.width/2-10, y: this.y - this.height/2+15 },
            { x: this.x +65, y: this.y - this.height/2+15 }
        ];
        this.verticesBottom2 = [
            { x: this.x+68, y: this.y + this.height/2 },
            { x: this.x+this.width/2-10, y: this.y + this.height/2 },
            { x: this.x+this.width/2+25, y: this.y + this.height/2+25 },
            { x: this.x +48, y: this.y + this.height/2+25 }
        ];
        this.angledSideLeft = Bodies.fromVertices(this.x - this.width / 2-5, this.y, this.verticesLeft, { isStatic: true, label: 'angledSide', restitution: this.angledSidesRestitution});
        this.angledSideRight = Bodies.fromVertices(this.x + this.width / 2+7, this.y, this.verticesRight, { isStatic: true, label: 'angledSide', restitution: this.angledSidesRestitution});
        this.angledSideTop = Bodies.fromVertices(this.x-this.width/4, this.y - this.height / 2-5.5, this.verticesTop, { isStatic: true, label: 'angledSide', restitution: this.angledSidesRestitution});
        this.angledSideBottom = Bodies.fromVertices(this.x-this.width/4, this.y + this.height / 2+5, this.verticesBottom, { isStatic: true, label: 'angledSide', restitution: this.angledSidesRestitution});
        this.angledSideTop2 = Bodies.fromVertices(this.x+this.width/4, this.y - this.height / 2-5.5, this.verticesTop2, { isStatic: true, label: 'angledSide', restitution: this.angledSidesRestitution});
        this.angledSideBottom2 = Bodies.fromVertices(this.x+this.width/4, this.y + this.height / 2+5, this.verticesBottom2, { isStatic: true, label: 'angledSide', restitution: this.angledSidesRestitution});

        //Drawing the borders of the table
        this.borderLeft = Bodies.rectangle(this.x - this.width / 2-17, this.y, 20, this.height+50, { isStatic: true, label: 'border'});
        this.borderRight = Bodies.rectangle(this.x + this.width / 2+17, this.y, 20, this.height+50, { isStatic: true, label: 'border'});
        this.borderTop = Bodies.rectangle(this.x, this.y - this.height / 2-17, this.width+50, 20, { isStatic: true, label: 'border'});
        this.borderBottom = Bodies.rectangle(this.x, this.y + this.height / 2+17, this.width+50, 20, { isStatic: true, label: 'border'});
        //Drawing the pocket backings behind the pockets
        this.pocketBacking1 = Bodies.rectangle(this.angledSideLeft.position.x-2, this.angledSideLeft.position.y-this.height/2-17, 40, 20, { isStatic: true, label: 'pocketBacking'});
        this.pocketBacking2 = Bodies.rectangle(this.angledSideLeft.position.x-2, this.angledSideLeft.position.y+this.height/2+17, 40, 20, { isStatic: true, label: 'pocketBacking'});
        this.pocketBacking3 = Bodies.rectangle(this.angledSideLeft.position.x-12, this.angledSideLeft.position.y-this.height/2-7, 20, 40, { isStatic: true, label: 'pocketBacking'});   
        this.pocketBacking4 = Bodies.rectangle(this.angledSideLeft.position.x-12, this.angledSideLeft.position.y+this.height/2+7, 20, 40, { isStatic: true, label: 'pocketBacking'});
        this.pocketBacking5 = Bodies.rectangle(this.x, this.angledSideTop.position.y-11, 50, 20, { isStatic: true, label: 'pocketBacking'});
        this.pocketBacking6 = Bodies.rectangle(this.x, this.angledSideBottom.position.y+11, 50, 20, { isStatic: true, label: 'pocketBacking'});
        this.pocketBacking7 = Bodies.rectangle(this.angledSideRight.position.x, this.angledSideRight.position.y-this.height/2-17, 40, 20, { isStatic: true, label: 'pocketBacking'});
        this.pocketBacking8 = Bodies.rectangle(this.angledSideRight.position.x, this.angledSideRight.position.y+this.height/2+17, 40, 20, { isStatic: true, label: 'pocketBacking'});
        this.pocketBacking9 = Bodies.rectangle(this.angledSideRight.position.x+10, this.angledSideRight.position.y-this.height/2-7, 20, 40, { isStatic: true, label: 'pocketBacking'});
        this.pocketBacking10 = Bodies.rectangle(this.angledSideRight.position.x+10, this.angledSideRight.position.y+this.height/2+7, 20, 40, { isStatic: true, label: 'pocketBacking'});
        //Drawing the pockets of the table
        this.pocket1 = Bodies.circle(this.angledSideLeft.position.x+8, this.angledSideLeft.position.y-this.height/2+4, this.pocketRadius, { isStatic: true, isSensor: true, label: 'pocket'});
        this.pocket2 = Bodies.circle(this.angledSideLeft.position.x+8, this.angledSideLeft.position.y+this.height/2-4, this.pocketRadius, { isStatic: true, isSensor: true, label: 'pocket'});
        this.pocket3 = Bodies.circle(this.angledSideRight.position.x-10, this.angledSideRight.position.y-this.height/2+4, this.pocketRadius, { isStatic: true, isSensor: true, label: 'pocket'});
        this.pocket4 = Bodies.circle(this.angledSideRight.position.x-12, this.angledSideRight.position.y+this.height/2-4, this.pocketRadius, { isStatic: true, isSensor: true, label: 'pocket'});
        this.pocket5 = Bodies.circle(this.x, this.angledSideTop.position.y+3, this.pocketRadius, { isStatic: true, isSensor: true, label: 'pocket'});
        this.pocket6 = Bodies.circle(this.x, this.angledSideBottom.position.y-3, this.pocketRadius, { isStatic: true, isSensor: true, label: 'pocket'});
        this.collisionManager = new CollisionManager(this);
        this.ballManager = new BallManager(this);
        this.cue = new Cue(this);
        this.obstaclesChallenge = new randomObstaclesChallenge(this);
        this.ballManager.setStartingPositions();
    }
    //draw function for white lines and arc
    draw() {
        push();
        stroke(200);
        strokeWeight(2);
        line(this.x-this.width/3+30,this.y-this.height/2+9,this.x-this.width/3+30,this.y+this.height/2-9);
        noFill();
        arc(this.x-this.width/3+30,this.y,this.width/5.3, this.width/5.3,PI/2,3*PI/2);
        pop();
    }
    setup() {
        //Adding snooker table to the world
        World.add(engine.world, [
            snookerTable.surface,
            snookerTable.angledSideLeft,
            snookerTable.angledSideRight,
            snookerTable.angledSideTop,
            snookerTable.angledSideBottom,
            snookerTable.angledSideTop2,
            snookerTable.angledSideBottom2,
            snookerTable.borderLeft,
            snookerTable.borderRight,
            snookerTable.borderTop,
            snookerTable.borderBottom,
            snookerTable.pocketBacking1,
            snookerTable.pocketBacking2,
            snookerTable.pocketBacking3,
            snookerTable.pocketBacking4,
            snookerTable.pocketBacking5,
            snookerTable.pocketBacking6,
            snookerTable.pocketBacking7,
            snookerTable.pocketBacking8,
            snookerTable.pocketBacking9,
            snookerTable.pocketBacking10,
            snookerTable.pocket1,
            snookerTable.pocket2,
            snookerTable.pocket3,
            snookerTable.pocket4,
            snookerTable.pocket5,
            snookerTable.pocket6
        ]);
        //Adding the balls to the world
        World.add(engine.world, snookerTable.balls.map(ball => ball.body));
    }
    //Checking if the mouse is within the boundaries of the arc for placement of cue ball
    isMouseInArc() {
        if (mouseX >= this.x-this.width/3+30) {
            return false;
        }
        let arcCenterX = this.x-this.width/3+30;
        let arcCenterY = this.y;
        let arcRadius = this.width/5.3/2;
        //Checking if the mouse is within the circular region of the arc
        let distanceFromCenter = dist(mouseX, mouseY, arcCenterX, arcCenterY);
        if (distanceFromCenter > arcRadius) {
            return false;
        }
        //Checking if the mouse is within the angle of the arc
        let arcAngle = atan2(mouseY - arcCenterY, mouseX - arcCenterX);
        if (arcAngle < 0) {
            arcAngle += TWO_PI;
        }
        return arcAngle >= PI/2 && arcAngle <= 3*PI/2;
    }
}   
