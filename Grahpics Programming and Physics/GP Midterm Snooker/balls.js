//Creating the balls class
class Ball {
    constructor(x, y, radius, color) {
        this.x = x;
        this.y = y;
        this.radius = radius;
        this.color = color;
        this.restitution = 0.8;
        this.mass = 1;
        this.friction = 0.18;
        this.label = "ball";
        if (this.color === 'white') {
            this.label = 'cueBall';
        } else if (this.color !== 'red' && this.color !== 'white') {
            this.label = this.color;
        }
        this.body = Bodies.circle(this.x, this.y, this.radius, {label: this.label, restitution: this.restitution, mass: this.mass, friction: this.friction});
    }
}