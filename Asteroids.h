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

class Bullet{
public:
	float bulletXVel(float bulletTrajectoryX, float xVelocity, float bulletFireAngle);
	float bulletYVel(float bulletTrajectoryY, float yVelocity, float bulletFireAngle);
	//float bulletX(float bulletTrajectoryX, float xVelocity, float bulletFireAngle, float *bulletX);
	//float bulletY(float bulletTrajectoryY, float yVelocity, float bulletFireAngle, float *bulletY);
private:
	float bulletVelocity = 10;
};

void screenLoop(float *xPosition, float *yPosition);

void keyboardInput(float *xVelocity, float *yVelocity);

void updatePositions(float *xPosition, float *yPosition, float *xVelocity, float *yVelocity);

void stopDrift(float *xVelocity, float *yVelocity);

int killBullet(float bulletStats[][100], int bulletNum);

//void closeWindow(sf::RenderWindow *window);

#endif