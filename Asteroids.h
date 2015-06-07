#ifndef ASTEROIDS_H
#define	ASTEROIDS_H

class Ship {
public:
	Ship();
private:
	int health;
	int lives;
	int velocity;
	int posX;
	int posY;
};

void screenLoop(float *xPosition, float *yPosition);

void keyboardInput(float *xVelocity, float *yVelocity);

void updatePositions(float *xPosition, float *yPosition, float *xVelocity, float *yVelocity);

void stopDrift(float *xVelocity, float *yVelocity);

//void gun(float xPosition, float yPosition, sf::RenderWindow *window);//make this function, currently not doin' stuff

//void closeWindow(sf::RenderWindow *window);

#endif