#include "unit.h"

Movement::Movement( const Movement &other) : 
	x(other.x), y(other.y), vx(other.vx), vy(other.vy), ax(other.ax),
	ay(other.ay), angle(other.angle), vel(other.vel), aVel(other.aVel),
	acc(other.acc), aAcc(other.aAcc)
{
	
}

void Movement::move( sf::Vector2f pos )
{
	x = pos.x;
	y = pos.y;
}

void Movement::update( )
{
	vx += ax;
	vy += ay;
	
	vel += acc;
	aVel += aAcc;
	angle += aVel;
	
	x = x + ( vel * sin(angle * ( PI / 180 ) ) ) + vx;
	y = y + ( vel * (-1) * cos(angle * ( PI / 180) ) ) + vy;
	
}
	
	
/*=====================
	Entity
=====================*/

void Entity::update()
{
	movement.update();
	anim.update();
	anim.setPosition(movement.x, movement.y);
}

void Entity::setColor(sf::Color c)
{
	anim.setColor( c );
}

void Entity::draw()
{
	anim.draw();
}