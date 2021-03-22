#ifndef BIRD_H
#define BIRD_H

#include "vector.h"
#include "utils.h"
#include <SFML/Graphics.hpp>

struct Bird
{
	Vector pos;
	Vector speed;
	Vector acceleration;

	float angle;
	int id;
	float moveSpeed;

	float pRCenter;
	float pRAlign;
	float pRRepulse;
	float pRRob;

	float fCenter;
	float fAlign;
	float fRepulse;
	float fRob;

	sf::Color color;
};

Bird bird_b();
Bird bird_b(Vector, float, int);
void move_b(Bird*);
void accelerate_b(Bird*);
void flock(Bird*, Bird*, int, Vector*, int);
Vector center(Bird*, Bird*, int, float*);
Vector align(Bird*, Bird*, int, float*);
Vector repulse(Bird*, Bird*, int, float*);
Vector repulse_obstacle(Bird*, Vector*, int);

#endif