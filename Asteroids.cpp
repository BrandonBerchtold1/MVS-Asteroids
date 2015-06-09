#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Asteroids.h"
#include "Parameters.h"

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
			*yVelocity = *yVelocity + 0.05f;//yVelocity += 0.05f; change in all places possible
		}
	}
}

/*sets bullet X velocity to ship velocity + component of trajectory velocity)*/
float Bullet::bulletXVel(float bulletTrajectoryX, float xVelocity, float bulletFireAngle){
	
	if (bulletTrajectoryX > 0){
		return xVelocity + bulletVelocity * cos(abs(bulletFireAngle));
	}

	else{
		return xVelocity - bulletVelocity * cos(abs(bulletFireAngle));
	}
}

/*sets bullet Y velocity to ship velocity + component of trajectory velocity)*/
float Bullet::bulletYVel(float bulletTrajectoryY, float yVelocity, float bulletFireAngle){

	if (bulletTrajectoryY > 0){
		return yVelocity + bulletVelocity * sin(abs(bulletFireAngle));
	}

	else{
		return yVelocity - bulletVelocity * sin(abs(bulletFireAngle));
	}
}

/*updates bullet X position
float Bullet::bulletX(float bulletTrajectoryX, float xVelocity, float bulletFireAngle, float *bulletX){
	*bulletX = bulletX(bulletTrajectoryX, xVelocity, bulletFireAngle, *bulletX) + bulletXVel(bulletTrajectoryX, xVelocity, bulletFireAngle);
}*/

/*updates bullet Y position
float Bullet::bulletY(float bulletTrajectoryY, float yVelocity, float bulletFireAngle, float *bulletY){
	return bulletY(bulletTrajectoryY, yVelocity, bulletFireAngle, *bulletY) + bulletYVel(bulletTrajectoryY, yVelocity, bulletFireAngle);
}*/

/*kills bullet if it exits screen and empties it's array elements*/
int killBullet(float bulletStats[][10000], int bulletNum, int currentBullets){

	if (bulletStats[0][bulletNum] > 1920 || bulletStats[0][bulletNum] < 0 || bulletStats[1][bulletNum] > 1080 || bulletStats[1][bulletNum] < 0){
		return 1;
	}

	else return 0;
}

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