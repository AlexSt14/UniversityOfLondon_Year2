//Random obstacles challenge class and management
class randomObstaclesChallenge {
    constructor(snookerTable) {
        this.snookerTable = snookerTable;
        this.obstacles = [];
        this.obstaclesActive = false;

    }
    //Adding random obstacles around pockets for a challenge mode extension
    randomObstaclesChallenge() {
        //Obstacles will be placed with small random positions, sizes and angular velocities
        let pockets = [this.snookerTable.pocket1, this.snookerTable.pocket2, this.snookerTable.pocket3, 
                    this.snookerTable.pocket4, this.snookerTable.pocket5, this.snookerTable.pocket6];
        pockets.forEach(pocket => {
            if (pocket.position.x < this.snookerTable.x+this.snookerTable.width/4 && pocket.position.y < this.snookerTable.y) {
                let x = pocket.position.x+70; 
                let y = pocket.position.y+40; 
                let obstacle = Bodies.rectangle(x, y, random(15,25), random(45,60), { isStatic: true, angularSpeed: 0.02, label: 'obstacle'});
                Matter.Body.setAngularVelocity(obstacle, this.setRandomAngularVelocity());
                this.obstacles.push(obstacle);
            }
            else if (pocket.position.x < this.snookerTable.x+this.snookerTable.width/4 && pocket.position.y > this.snookerTable.y) {
                let x = pocket.position.x+70; 
                let y = pocket.position.y-40; 
                let obstacle = Bodies.rectangle(x, y, random(15,25), random(45,60), { isStatic: true, angularSpeed: 0.02, label: 'obstacle'});
                Matter.Body.setAngularVelocity(obstacle, this.setRandomAngularVelocity());
                this.obstacles.push(obstacle);
            }
            else if (pocket.position.x > this.snookerTable.x+this.snookerTable.width/4 && pocket.position.y < this.snookerTable.y) {
                let x = pocket.position.x-90; 
                let y = pocket.position.y+140; 
                let obstacle = Bodies.rectangle(x, y, random(15,25), random(65,110), { isStatic: true, angularSpeed: 0.02, label: 'obstacle'});
                Matter.Body.setAngularVelocity(obstacle, -0.02);
                this.obstacles.push(obstacle);
            }
        });
        World.add(engine.world, this.obstacles);
    }
    //Changing the angle of the obstacles for the challenge mode extension
    obstaclesAngleUpdate() {
        this.obstacles.forEach(obstacle => {
            Matter.Body.setAngle(obstacle, obstacle.angle + obstacle.angularVelocity);
        });
    }
    //Creating a random angular velocity for obstacles that can be positive or negative
    setRandomAngularVelocity() {
        if (random(1) < 0.5) return random(-0.02, -0.006);
        else return random(0.006, 0.02);
    }
    //Removing the obstacles from the world and clearing array when game mode changes
    removeObstacles() {
        World.remove(engine.world, this.obstacles);
        this.obstacles = [];
        this.obstaclesActive = false;
    }
}