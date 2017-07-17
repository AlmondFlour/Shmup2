#include "init.h"

using namespace std;




//Start Menu TODO: move this to it's own file to expand
void startMenu();

//Game
void gameLoop();
void gameInput( sf::Event & event );
void pauseMenuInput( sf::Event & event );
void gameKeyState();
void gamePauseMenu();
void gameUpdate( bool paused );

//Cleanup TODO: move this to it's own file
void cleanup();

int main()
{
    init();
	
    //startMenu();
	gameLoop(); //TODo: remove this after fixing menu

    cleanup();
    return 0;
}

//====Menu
/*
void startMenu()
{
    Menu menu( window, menuView, font );
    menu.addItem( "Start" );

    //Menu loop
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            //Mouse button pressed
            if( event.type == sf::Event::MouseButtonPressed )
            {
                //if mouse left is pressed (toggle terrain)
                if( event.mouseButton.button == sf::Mouse::Left )
                {
                    int buttonPressed = menu.checkClicked( event.mouseButton.x, event.mouseButton.y );

                    switch( buttonPressed )
                    {
                        case 0:
                            gameLoop();
                            break;
                    }
                }
            }
            //check to close window
            else if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        //update screen
        menu.draw();
        window->display();
    }
}*/

//=====Game
void gameLoop()
{
	/*
    if( pauseMenu != NULL )
    {
        delete pauseMenu;
    }*/
	
	
    while (window->isOpen())
    {
        sf::Event event;

        //=====Input events
        while (window->pollEvent(event))
        {
            if ( !paused )
            {
                gameInput( event );
            }
            else
            {
                pauseMenuInput( event );
            }

            if ( event.type == sf::Event::Closed )
            {
                window->close();
            }

        }

        //=====Key state actions
        gameKeyState();

        //=====Update
        gameUpdate( paused );
    }
}

void gameInput( sf::Event & event )
{
    if( event.type == sf::Event::KeyPressed)
    {
        //Space pressed(random paths)
        if( event.key.code == sf::Keyboard::Space )
        {
			for(int n = 0; n < 1; n++ )
			{
				;
			}
        }
    }
}

void pauseMenuInput( sf::Event & event )
{
}

void gameKeyState()
{
    if (sf::Keyboard::isKeyPressed(keyMap["up"]))
    {
		
    }
    if (sf::Keyboard::isKeyPressed(keyMap["down"]))
    {
    }
    if (sf::Keyboard::isKeyPressed(keyMap["left"]))
    {
    }
    if (sf::Keyboard::isKeyPressed(keyMap["right"]))
    {
    }
}

void gameUpdate( bool paused )
{


    
    if( !paused ) //TODO: move after rewriting pause
    {
        //Update game stage
    }
	
	
	window->clear();
	/*
	float testRot = 0.5;
	//animators["star"].setOrigin(sf::Vector2f(50, 50) );
	animators["star"].setPosition(25,25 );
	animators["star"].setColor(sf::Color(75, 252, 50 ) );
	animators["star"].setDimensions(25, 25 );
	animators["star"].rotate(testRot);
	animators["star"].update();
	
	animators["star"].draw();
	*/
	
	#pragma omp parallel for
	for( int n = 0; n < entities.size(); n++ )
	{
		entities[n].update();
	}
	
	for( int n = 0; n < entities.size(); n++ )
	{
		entities[n].draw();
	}
	

    if( paused )
    {
        //note: menu class uses views by itself
        //pauseMenu->draw();
    }
	
	//check fps
	frames++;
	float currentTime = gameClock.getElapsedTime().asSeconds();
	if( currentTime >= FPS_UPDATE )
	{
		float fps = frames / currentTime;
		cout << fps << "\n";
		frames = 0;
		gameClock.restart().asSeconds();
	}
	

    window->display();
}
