//////////////////////////////////////////////////
/* GRAPHICS PROGRAMMING Midterm Report
Snooker Game Design and Extension Report

My snooker game implementation combines traditional gameplay with innovative controls and
a unique obstacle challenge mode.

Control Design: The game utilizes a hybrid keyboard-mouse control system for precise and intuitive interaction:
1. Cue Control: The player activates the cue by holding the spacebar and right-clicking. Mouse movement then
adjusts the angle and power of the cue, mimicking the physical action of drawing back a cue stick. This design offers
fine-grained control over shot power and direction.

2. Cue Ball Placement: Using the "alt+right-click" combination, the player can precisely position the cue ball inside 
the arc area of the table. This feature accurately simulates the "ball in hand" rule in snooker. An important aspect is that 
the cue ball can only be placed inside the arc area, not outside.

3. Game State Selection: Keys 1-3 allow players to reset the game to different states, offering variety in gameplay scenarios.

Unique Extension: Rotating Obstacle Challenge Mode

To extend the game beyond conventional snooker gameplay and beyond the requirements of the assignment, I implemented a 
"Rotating Obstacle Challenge Mode", activated by pressing key '4'. This mode introduces the following elements:

1. Random Red Ball Placement: Upon activation, all red balls are randomly distributed across the table, creating 
unique and unpredictable game states.

2. Rotating Obstacles: Small, rectangular obstacles are strategically placed near the pockets. These obstacles continuously
rotate, adding a dynamic challenge when taking shots.

3. Variable Rotation: Each obstacle is assigned a random angular velocity, ensuring diverse rotational speeds and directions 
(clockwise or counterclockwise). This variability increases the mode's replay value and challenge.

4. Precision Shot-Making: The player must time their shots to navigate around these rotating barriers which requires more skills
than the standard snooker game.

Implementation Details:
- Obstacles are created as static Matter.js bodies, allowing rotation without displacement.
- Angular velocities are carefully tuned (between +-0.006 and +-0.02) to provide noticeable but not overly rapid rotation.
- The 'obstaclesAngleUpdate' function continuously updates obstacle angles based on their angular velocities, 
ensuring smooth rotation.

This extension transforms the traditional snooker experience into a puzzle-like challenge, requiring players to consider
not just standard snooker tactics, but also the timing and positioning of their shots in relation to the moving obstacles.
It provides a fresh twist on the classic game.

By combining authentic snooker elements with this innovative obstacle system, the game bridges the gap between traditional 
sport simulation and creative puzzle gameplay, offering a distinctive and engaging experience that sets it apart from 
standard snooker games.
*/

//////////////////////////////////////////////////
//Module aliases
let Engine = Matter.Engine;
let Render = Matter.Render;
let World = Matter.World;
let Bodies = Matter.Bodies;
let Mouse = Matter.Mouse;
let MouseConstraint = Matter.MouseConstraint;
let engine;
let snookerTable;
let canvas;
let helper;

function setup() {
    canvas = createCanvas(1520, 730);
    //Create an engine
    engine = Engine.create();
    //Create the snooker table
    snookerTable = new SnookerTable(width/2, height/2, 800, 400);
    //Create the helper text class
    helper = new Helper();
    //Add the table to the world
    snookerTable.setup();
    //Removing gravity
    engine.world.gravity.x = 0;
    engine.world.gravity.y = 0;
    //Setup mouse for interaction with balls
    //This mouse constraint was taken from the class example from week 4
    let mouse = Mouse.create(canvas.elt);
    let mouseParams = {
        mouse: mouse,
        constraint: { stiffness: 0.05 }
    };
    mouseConstraint = MouseConstraint.create(engine, mouseParams);
    mouseConstraint.mouse.pixelRatio = pixelDensity();
    World.add(engine.world, mouseConstraint);
    rectMode(CENTER);
}
function draw() {
    background(0);
    Engine.update(engine);

    //Draw the snooker table and balls
    engine.world.bodies.forEach(body => {
        //Drawing only bodies that are static, doing so, we avoid drawing the balls
        if (body.isStatic) {
            noStroke();
            if (body.label == 'angledSide') {
                // color for angled sides
                fill(0, 95, 0);
            }
            else if (body.label == 'border') {
                // color for rect borders
                fill(84, 46, 14);
            }
            else if (body.label == 'tableSurface') {
                // color for table surface
                fill(0, 150, 0);
            }
            else if (body.label == 'pocket') {
                // color for pockets
                fill(0);
            }
            else if (body.label == 'pocketBacking') {
                // color for pocket backings
                fill(222, 177, 18);
            }
            else if (body.label == 'obstacle') {
                // color for obstacles
                fill(115, 50, 0);
            }
            drawVertices(body.vertices);
        }
    });
    //Drawing lines and arc
    snookerTable.draw();
    //Drawing the balls
    snookerTable.balls.forEach(ball => {
        fill(ball.color);
        stroke(1);  
        drawVertices(ball.body.vertices);
    });
    //Check for collisions with pockets
    snookerTable.collisionManager.checkPockets();
    //Draw the cue
    if (isSpacePressed) {
        snookerTable.cue.update(mouseX, mouseY);
    }
    snookerTable.cue.draw();
    //Drawing the collision matrix
    snookerTable.collisionManager.drawCollisionMatrix();
    //Drawing the helper text to canvas
    helper.draw();
    //Update the obstacles angle
    if (snookerTable.obstaclesActive) {
        snookerTable.obstaclesChallenge.obstaclesAngleUpdate();
    }
}
//This function was taken from the class example for drawing vertices
//It was shown in multiple lessons during the Graphics Programming course
function drawVertices(vertices) {
    beginShape();
    for (let i = 0; i < vertices.length; i++) {
        vertex(vertices[i].x, vertices[i].y);
    }
    endShape(CLOSE);
}
//Key action functions for different interactivity
function keyPressed() {
    if (key === '1') {
        snookerTable.ballManager.setStartingPositions();
        snookerTable.ballManager.addBallsToWorld();
    } else if (key === '2') {
        snookerTable.ballManager.setRandomRedPositionsReds();
        snookerTable.ballManager.addBallsToWorld();
    } else if (key === '3') {
        snookerTable.ballManager.setRandomAllPositions();
        snookerTable.ballManager.addBallsToWorld();
    } else if (key === '4') {
        snookerTable.ballManager.setRandomRedPositionsReds();
        snookerTable.ballManager.addBallsToWorld();
        snookerTable.obstaclesChallenge.randomObstaclesChallenge();
        snookerTable.obstaclesActive = true;
    }
    if (key === ' ') {
        isSpacePressed = true;
    }
    if (key === 'Alt') {
        isAltPressed = true;
    }
}
function keyReleased() {
    if (key === ' ') {
        isSpacePressed = false;
        snookerTable.cue.isDrawing = false;
    }
    if (key === 'Alt') {
        isAltPressed = false;
    }
}
function mousePressed() {
    if (isSpacePressed) {
        snookerTable.cue.isDrawing = true;
    }
    if (isAltPressed) {
        snookerTable.ballManager.drawCueBall(mouseX, mouseY);
    }
}
function mouseReleased() {
    if (isSpacePressed) {
        snookerTable.cue.hit();
    }
}