#include "physics.h" 
// Thing constructor 
Thing::Thing(float x, float y, float radius) 
	: x{ x }, y{ y }, radius{ radius }, dX{ 0.0f }, dY{ 0.0f }
{ 

} 
// end of Thing constructor 
void Thing::setPosition(float x, float y) {

} 
float Thing::getX() { 
	return this->x; 
} 
float Thing::getY() { 
	return this->y; 
} 
void Thing::applyForce(float xForce, float yForce) { 
	x += xForce;
	y += yForce;
} 
void Thing::update() { 
	x += dX;
	y += dY;
}

// World constructor
World::World(float width, float height, float gravity)
	: width{ width }, height{ height }, gravity{ gravity }
{

}
// end of World constructor
void World::addThing(Thing* thing) {
	things.push_back(thing);
}
bool World::didThingsCollide(Thing* thing1, Thing* thing2) {
	return false;
}
int World::countThings() {
	return things.size();
}
void World::update() {
	for (auto& thing : things) {
		thing->applyForce(0.0f, gravity);
		thing->update();
	}

}
