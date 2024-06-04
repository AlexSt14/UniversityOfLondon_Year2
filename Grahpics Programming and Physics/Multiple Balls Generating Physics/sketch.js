// module aliases
var Engine = Matter.Engine,
    Render = Matter.Render,
    Runner = Matter.Runner,
    Bodies = Matter.Bodies,
    Composite = Matter.Composite,
    Body = Matter.Body;
var engine;
var box1;
var ground2;
var boxes = [];
var propeller;
var angle = 0;
var angleSpeed = 0.1;

function setup() {
    createCanvas(900, 600);
    // create an engine
    engine = Engine.create();

    box1 = Bodies.rectangle(200,200,80,80, {restitution:0.8, friction: 0.5});
    ground2 = Bodies.rectangle(500,500,810,10,{isStatic: true, angle: Math.PI * -0.06});
    propeller = Bodies.rectangle(width/2, height/2, 300, 15, {isStatic: true, angle: angle});
    // add all of the bodies to the world
    Composite.add(engine.world, [box1, ground2, propeller]);
}

function draw() {
    background(0);
    Engine.update(engine);
    fill(255);
    drawVertices(box1.vertices);
    drawVertices(propeller.vertices);
    Body.setAngle(propeller,angle);
    Body.setAngularVelocity(propeller,angleSpeed);
    angle+= angleSpeed;
    if (random(1)<0.2) {
        generateObject(width/2,0); 
    }
         
    for (var i = 0; i < boxes.length; i++) {
        drawVertices(boxes[i].vertices);

        if (isOffScreen(boxes[i])) {
            Composite.remove(engine.world, boxes[i]);
            boxes.splice(i, 1);
            --i;
        }
    }
    fill(125);
    drawVertices(ground2.vertices);
    
}
function isOffScreen(body) {
    var pos = body.position;
    return (pos.y > height || pos.x < 0 || pos.x > width);
}
function generateObject(x,y) {
    var b = Bodies.rectangle(x, y, random(10,30), random(10,30), {restitution:0.8, friction:0.5});
    boxes.push(b);
    Composite.add(engine.world, [b]);
}
function drawVertices(vertices) {
    beginShape();
    for (var i = 0; i < vertices.length; i++) {
        vertex(vertices[i].x,vertices[i].y);
    }
    endShape(CLOSE);
}