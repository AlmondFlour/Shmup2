#ifndef ANIM_H
#define	ANIM_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

//holds information about individual animations, used in Anim
struct Animation
{
    int startX;
    int startY;
    int endX;
    int endY;

    bool loopAnim;
    sf::Time duration;

    Animation() : startX(0), startY(0), endX(0), endY(0),
        loopAnim( false ), duration( sf::milliseconds(100) ) {}

    Animation( int sx, int sy, int ex, int ey, sf::Time dur, bool loop = true ) :
        startX(sx), startY( sy ), endX( ex), endY( ey ), duration( dur ), loopAnim(loop)  {}

    Animation( const Animation & other ) : startX(other.startX),
        startY(other.startY), endX(other.endX), endY(other.endY),
        loopAnim( other.loopAnim ), duration( other.duration ) {}
		
	void reset();
		
};

//Wrapper for SFML graphics for use with animation
class Anim
{
    private:
        sf::RenderWindow * window;
        sf::Texture * texture;
        sf::RectangleShape shape;
        sf::IntRect clip;

        sf::Clock clock;

        bool inAnimation;
        sf::Time duration;

        std::map< std::string, Animation > animList;
        Animation * currentAnimation;
        std::string currentName;

        //clip position for current animation
        int currentX;
        int currentY;

		float rotVel;
		
    public:
        Anim( sf::RenderWindow * win, sf::Texture * t, sf::IntRect c, int w, int h );
        Anim();

        Anim( const Anim &other);

        //for use with empty construction
        void initilize( sf::RenderWindow * w, sf::Texture * t, sf::IntRect c, int x, int y );

        void operator=(const Anim &newAnim);

        void setTexture( sf::Texture * t, bool reset = false );
        void setWindow( sf::RenderWindow * w );
        void setFrame( int fx, int fy );
        void setPosition( int x, int y );
        void setDimensions( int w, int h, bool center = true);
        void setClipDimensions( int w, int h );
        void setColor( sf::Color c);
        void setOutlineThickness( const float & t );
        void setOutlineColor( const sf::Color & c );
		void setRotVel( float rv );
        void setRotation( float r );
		void rotate( float r);
        void setOrigin( sf::Vector2f o );

        sf::Texture * getTexture();
        sf::Vector2f getPosition();
        sf::FloatRect getLocalBounds();
        sf::IntRect getClipDimensions();
        sf::Color getFillColor();

        void addAnimation( std::string name, sf::Time dur, int sx, int sy, int fx, int fy, bool loop = true );
        void setAnimation( std::string name );

        void draw();
        void update();
};

#endif	/* ANIM_H */
