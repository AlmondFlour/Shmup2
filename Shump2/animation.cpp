#include "animation.h"

Anim::Anim( sf::RenderWindow * win, sf::Texture * t, sf::IntRect c, int w, int h )
    : window( win ), texture( t ), clip( c ), inAnimation( false ), currentAnimation( NULL ), currentName( "" ), rotVel(0)
{
    shape.setSize( sf::Vector2f( w, h ));
    shape.setPosition( sf::Vector2f(0, 0));
    shape.setTexture( texture );
    shape.setTextureRect( clip );
	shape.setOrigin( sf::Vector2f( w / 2, h / 2 ));
}
Anim::Anim() : window( NULL ), texture( NULL ), rotVel(0),
    clip( 0, 0, 1, 1), inAnimation( false ), currentName( "" )
{
    shape.setSize( sf::Vector2f( 1, 1 ));
    shape.setPosition( sf::Vector2f(0, 0));
    shape.setTexture( texture );
    shape.setTextureRect( clip );
}

Anim::Anim( const Anim & other ) : window(other.window),
        texture(other.texture), shape(other.shape), clip(other.clip), rotVel(other.rotVel),
        clock(other.clock), inAnimation(other.inAnimation ), currentX( other.currentX),
        currentY( other.currentY), animList( other.animList ), currentName( other.currentName )
{
    currentAnimation = &animList[currentName];
}

void Anim::operator=(const Anim &other)
{
    window = other.window;
    texture = other.texture;
    shape = other.shape;
    clip = other.clip;
    clock = other.clock;
    inAnimation = other.inAnimation;
    duration = other.duration;
    animList = other.animList;
    currentName = other.currentName;
	rotVel = other.rotVel;
	
    if ( currentName != "" )
    {
        currentAnimation = &animList[currentName];
    }
}

//for use with empty construction
void Anim::initilize( sf::RenderWindow * w, sf::Texture * t, sf::IntRect c, int x, int y )
{
    window = w;
    texture = t;
    clip = c;

    shape.setSize( sf::Vector2f( x, y ));
    shape.setPosition( sf::Vector2f(0, 0));
    shape.setTexture( texture );
    shape.setTextureRect( clip );

    inAnimation = false;
}

sf::Texture * Anim::getTexture()
{
    return texture;
}
void Anim::setTexture( sf::Texture * t, bool reset )
{
    texture = t;
    shape.setTexture( t, reset );
}
void Anim::setWindow( sf::RenderWindow * w )
{
    window = w;
}
void Anim::setFrame( int fx, int fy )
{
    clip.left = fx * clip.width;
    clip.top =  fy * clip.height;

    shape.setTextureRect(clip);
}
void Anim::setPosition( int x, int y )
{
    shape.setPosition( sf::Vector2f( x, y ) );
}
void Anim::setDimensions( int w, int h, bool center)
{
    shape.setSize( sf::Vector2f( w, h ));
	if( center )
	{
		setOrigin(sf::Vector2f( w/2, h/2 ) );
	}
}
void Anim::setClipDimensions( int w, int h )
{
    clip.width = w;
    clip.height = h;

    shape.setTextureRect( clip );
}
void Anim::setColor( sf::Color c )
{
    shape.setFillColor( c );
}
void Anim::setOutlineThickness( const float & x )
{
    shape.setOutlineThickness( x );
}
void Anim::setOutlineColor( const sf::Color & c )
{
    shape.setOutlineColor( c );
}
void Anim::setRotVel( float rv )
{
	rotVel = rv;
}
void Anim::setRotation( float r )
{
    shape.setRotation( r );
}
void Anim::rotate( float r )
{
    shape.rotate( r );
}

void Anim::setOrigin( sf::Vector2f o )
{
    shape.setOrigin( o );
}

sf::Vector2f Anim::getPosition()
{
    return shape.getPosition();
}
sf::FloatRect Anim::getLocalBounds()
{
    return shape.getLocalBounds();
}
sf::IntRect Anim::getClipDimensions()
{
    return clip;
}
sf::Color Anim::getFillColor()
{
    return shape.getFillColor();
}

void Anim::addAnimation( std::string name, sf::Time dur, int sx, int sy, int ex, int ey, bool loop )
{
    Animation a( sx, sy, ex, ey, dur, loop );
    animList.insert( animList.end(), std::pair< std::string, Animation >( name, a ) );

    clock.restart();
}
void Anim::setAnimation( std::string name )
{
    currentName = name;
    currentAnimation = &animList[ name ];
    setFrame( currentAnimation->startX, currentAnimation->startY );
    currentX = currentAnimation->startX;
    currentY = currentAnimation->startY;
    clock.restart();
    inAnimation = true;
}
void Anim::draw()
{
    window->draw( shape );
}
void Anim::update()
{
	rotate(rotVel);
	
    if( !inAnimation || ( currentAnimation == NULL ) )
    {
        return;
    }

    //if not enough time has passed
    if( clock.getElapsedTime() < currentAnimation->duration )
    {
        return;
    }

    currentX++;

    if( currentX * clip.width >  texture->getSize().x )
    {
        currentY++;
        currentX = 0;
    }

    //if animation is still going
    if ( (currentY < currentAnimation->endY ) || (currentX < currentAnimation->endX ) )
    {
        setFrame( currentX, currentY );
    }
    //if animation is ending
    else if( currentAnimation->loopAnim )
    {
        currentX = currentAnimation->startX;
        currentY = currentAnimation->startY;
        setFrame( currentX, currentY );
    }
    else
    {
        inAnimation = false;
    }

    clock.restart();
}