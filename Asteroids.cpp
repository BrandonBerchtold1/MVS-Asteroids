#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

/*if ship exits screen, it loops back to other side*/
void screenLoop(float *xPosition, float *yPosition){
	if (*xPosition > 1920){
		*xPosition = 0;
	}

	if (*yPosition > 1080){
		*yPosition = 0;
	}

	if (*xPosition < 0){
		*xPosition = 1920;
	}

	if (*yPosition < 0){
		*yPosition = 1080;
	}
}

/*Use arrow keys to move ship*/
void keyboardInput(float *xVelocity, float *yVelocity){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		*xVelocity = *xVelocity - 0.2f;// left key is pressed: move our character

		if (*xVelocity < -7.0f){
			*xVelocity = -7.0f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		*xVelocity = *xVelocity + 0.2f;// Right key is pressed: move our character

		if (*xVelocity > 7.0f){
			*xVelocity = 7.0f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		*yVelocity = *yVelocity - 0.2f;// Up key is pressed: move our character

		if (*yVelocity < -7.0f){
			*yVelocity = -7.0f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		*yVelocity = *yVelocity + 0.2f;// Down key is pressed: move our character

		if (*yVelocity > 7.0f){
			*yVelocity = 7.0f;
		}
	}
}


/*updates ship position*/
void updatePositions(float *xPosition, float *yPosition, float *xVelocity, float *yVelocity){

	*xPosition = *xPosition + *xVelocity;
	*yPosition = *yPosition + *yVelocity;
}

/*Dis stops dat drift doe*/
void stopDrift(float *xVelocity, float *yVelocity){

	if (xVelocity != 0){

		if (*xVelocity > 0){
			*xVelocity = *xVelocity - 0.05f;
		}

		if (*xVelocity < 0){
			*xVelocity = *xVelocity + 0.05f;
		}
	}

	if (yVelocity != 0){

		if (*yVelocity > 0){
			*yVelocity = *yVelocity - 0.05f;
		}

		if (*yVelocity < 0){
			*yVelocity = *yVelocity + 0.05f;
		}
	}
}

/*fires projectile in direction mouse points
void gun(float xPosition, float yPosition, sf::RenderWindow *window){

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){

		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window); // left mouse button is pressed, get the local mouse position (relative to a window)

		cout << "x: " << mousePosition.x << "y: " << mousePosition.y << endl;
	}
}*/


/*closes wondow if "esc" button is pressed or if top right exit button is. (Allow player to exit to main using esc then use button on screen to exit fully
void closeWindow(sf::RenderWindow *window){
	sf::Event event;
	while (*window.pollEvent(event)){

		if (event.type == sf::Event::Closed){
			*window.close();
		}

		if (event.type == sf::Event::KeyPressed){
			if (event.key.code == sf::Keyboard::Escape){
				*window.close();
			}
		}
	}
}*/