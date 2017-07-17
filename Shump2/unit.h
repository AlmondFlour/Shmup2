#include <math.h>
#include <map>
#include <string>
#define PI 3.14159265

#include "animation.h"
#include "constants.h"

class Hitbox;
class Movement;
class Entity;

class Hitbox
{

};

class Movement
{
	public:
	
	double x;
	double y;
	double vx;
	double vy;
	double ax;
	double ay;
	
	double angle; //degrees
	double vel;
	double aVel;
	double acc;
	double aAcc;
	
	
	Movement( ):
		x(0), y(0), vx(0), vy(0), ax(0), ay(0), angle(0), vel(0), aVel(0), acc(0), aAcc(0) {}
	
	Movement( const Movement &other);
	
	void move( sf::Vector2f pos );
	//bool preupdate(); //check for collisions before updating
	void update( );
	
};

class Entity
{
	public:
	
	Movement movement;
	Anim anim;
	
	Entity(): movement(Movement()), anim(Anim()) {}
	Entity(Anim  &a) : movement(Movement()), anim( a) {} 
	
	void move();
	void setColor(sf::Color c);
	
	void update();
	void draw();
};

class Player
{
	public:
	Entity ent;
	
	std::map< std::string, sf::Keyboard::Key >* keyMap;
	
	Player(std::map< std::string, sf::Keyboard::Key >* km, int a);
	
	void getInput();
};