#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <omp.h>
#include <random> 

#include "animation.h"
#include "unit.h"
#include "constants.h"

using namespace std;

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;
const int MAX_FPS = 60;
const string WINDOW_TITLE = "Shmup";

sf::RenderWindow * window;
sf::Font * font;
map< string, sf::Texture * > textures;
map< string, Anim > animators;
vector<Entity> entities;
sf::Clock gameClock;
float frames; //since last update
map< string, sf::Keyboard::Key > keyMap;

bool paused = false; //move this later

int init(); //returns 0, or the init that went wrong
bool initializeWindow();
bool initializeTextures();
bool initializeAnimators();
bool initializeOther();
bool initializeInput();

int init()
{
	initializeWindow();
    initializeTextures();
    initializeAnimators();
	initializeInput();
    initializeOther();
	
	return 0;
}


//=====Initialization
bool initializeWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE );
    window->setFramerateLimit( MAX_FPS );
    window->setKeyRepeatEnabled( false );

}
bool initializeTextures()
{
    sf::Texture * slime = new sf::Texture;
    if(!slime->loadFromFile( "Images/slime1.png" ) )
        return -1;
    textures.insert( textures.end(), std::pair< string, sf::Texture * >( "slime", slime ) );

    sf::Texture * tile = new sf::Texture;
    if(!tile->loadFromFile( "Images/tile1 Border.png" ) )
        return -2;
    textures.insert( textures.end(), std::pair< string, sf::Texture * >( "tile", tile ) );

    font = new sf::Font;
    if(!font->loadFromFile( "Choktoff.ttf"))
        return -3;

    sf::Texture * fire = new sf::Texture;
    if( !fire->loadFromFile( "Images/fire.png" ) )
        return -4;
    textures.insert( textures.end(), std::pair< string, sf::Texture * >( "fire", fire ) );
	
	sf::Texture * star = new sf::Texture;
    if(!star->loadFromFile( "Images/star.png" ) )
        return -5;
    textures.insert( textures.end(), std::pair< string, sf::Texture * >( "star", star ) );
	
	sf::Texture * player = new sf::Texture;
    if(!star->loadFromFile( "Images/player.png" ) )
        return -6;
    textures.insert( textures.end(), std::pair< string, sf::Texture * >( "player", star ) );
}

bool initializeAnimators()
{

    Anim baseAnim( window, NULL, sf::IntRect( 0, 0, 75, 75 ), 100, 100 );
    //baseAnim.addAnimation( "idle", sf::milliseconds( 100 ), 0, 0, 5, 0 );
    //baseAnim.setAnimation( "idle");

    animators.insert( animators.end(), std::pair< string, Anim >( "slime", baseAnim ) );
    animators["slime"].setTexture( textures["slime"] );
    animators["slime"].addAnimation( "idle", sf::milliseconds( 100 ), 0 , 0, 5, 0 );
    animators["slime"].setAnimation( "idle" );

    animators.insert( animators.end(), std::pair< string, Anim >( "fire", baseAnim ) );
    animators["fire"].setTexture( textures["fire"] );
    animators["fire"].setClipDimensions( 256, 256 );
    animators["fire"].addAnimation( "idle", sf::milliseconds( 100 ), 0, 0, 2, 0 );
    animators["fire"].setAnimation( "idle" );
	
	animators.insert( animators.end(), std::pair< string, Anim >( "star", baseAnim ) );
    animators["star"].setTexture( textures["star"] );
    animators["star"].setClipDimensions( 50, 50 );
    animators["star"].addAnimation( "idle", sf::milliseconds( 100 ), 0, 0, 1, 0 );
    animators["star"].setAnimation( "idle" );
    animators["star"].setDimensions(30, 30 );
	
	animators.insert( animators.end(), std::pair< string, Anim >( "player", baseAnim ) );
    animators["player"].setTexture( textures["player"] );
    animators["player"].setClipDimensions( 32, 32 );
    animators["player"].addAnimation( "idle", sf::milliseconds( 100 ), 0, 0, 1, 0 );
    animators["player"].setAnimation( "idle" );
    animators["player"].setDimensions(40, 40 );
}

bool initializeInput()
{
	keyMap["up"] = sf::Keyboard::Up;
	keyMap["down"] = sf::Keyboard::Down;
	keyMap["left"] = sf::Keyboard::Left;
	keyMap["right"] = sf::Keyboard::Right;
}

bool initializeOther()
{
	frames = 0;
	random_device rng;
	mt19937 rand(rng());
	uniform_real_distribution<> angle(0, 360);
	uniform_real_distribution<> percent(0, 1);
	
	Entity * baseEnt = new Entity( animators["star"] );
	
	int numDanmaku = 2000;
	
	for( int n = 0; n < numDanmaku / 2; n++ )
	{
		double speed = floor(angle(rand));
		baseEnt->anim.setRotVel(1 + (speed / 90) );
		baseEnt->setColor( sf::Color(0, 200 + (floor(angle(rand)) / 360.0 * 55), 0, 255 ) );
		baseEnt->movement.x = 0;
		baseEnt->movement.y = 0;
		baseEnt->movement.vel = 1.0 + ( speed / 180) ;
		baseEnt->movement.aVel = -0.2;
		baseEnt->movement.angle = 120 + ( floor(angle(rand)) / 4 );
		entities.push_back( *baseEnt);
		/*
		baseEnt->anim.setRotVel(1 + 3 * (n / numDanmaku ) );
		baseEnt->setColor( sf::Color(0, 150 + 105 * ( n * 2 / numDanmaku ), 0, 255 ) );
		baseEnt->movement.x = 0;
		baseEnt->movement.y = n * 2 * ( SCREEN_HEIGHT / (numDanmaku * 1.f ) );
		baseEnt->movement.vel = 0.25+ 4.0 * ( n / (numDanmaku * 1.f ));
		baseEnt->movement.aVel = 0;
		baseEnt->movement.angle = 90;
		entities.push_back( *baseEnt);
		*/
	}
	
	for( int n = 0; n < numDanmaku / 2; n++ )
	{
		double speed = floor(angle(rand));
		baseEnt->anim.setRotVel(1 + (speed / 90) );
		baseEnt->setColor( sf::Color(0, 0, 200 + (floor(angle(rand)) / 360.0 * 55), 255 ) );
		baseEnt->movement.x = SCREEN_WIDTH;
		baseEnt->movement.y = 0;
		baseEnt->movement.vel = 1.0 + ( speed / 180) ;
		baseEnt->movement.aVel = 0.2;
		baseEnt->movement.angle = 240 - ( floor(angle(rand)) / 4 );
		entities.push_back( *baseEnt);
	}
	
}

//=====Cleanup
void cleanup()
{
    for (map< string, sf::Texture * >::iterator it = textures.begin() ; it != textures.end(); ++it)
	{
		delete (*it).second;
	}
	textures.clear();
	animators.clear();
	entities.clear();
	
	delete window;
	delete font;
	
}