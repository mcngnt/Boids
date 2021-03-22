#include "bird.h"
#include "utils.h"
#include "vector.h"

Bird bird_b()
{
	Bird b;
	b.pos = vec_v(0.f, 0.f, 0.f);
	b.speed = vec_v(0.f, 0.f, 0.f);
	b.acceleration = vec_v(0.f, 0.f, 0.f);
	b.angle = 0.f;
	b.moveSpeed = 4.f;
	b.pRCenter = 100.f;
	b.pRAlign = 33.f;
	b.pRRepulse = 16.f;
	b.pRRob = 70.f;
	b.fCenter = .15f;
	b.fAlign = .05f;
	b.fRepulse = .3f;
	b.fRob = .3f;
	b.color = sf::Color(rand()%210+45,rand()%210+45,rand()%210+45,255);
	return b;
}

Bird bird_b(Vector pos, float angle, int id)
{
	Bird b = bird_b();
	b.pos = pos;
	b.id = id;
	b.angle = angle;
	return b;
}
void move_b(Bird* b)
{
	b->speed = mult_scalar_v(b->speed, b->moveSpeed);
	b->pos = add_vec_v(b->pos, b->speed);
	b->angle = get_angle_v(b->speed);

	if (b->pos.x < -1)
	{
		b->pos.x = SCREEN_W+1;
	}
	if (b->pos.x > SCREEN_W+1)
	{
		b->pos.x = -1;
	}
	if (b->pos.y < -1)
	{
		b->pos.y = SCREEN_H+1;
	}
	if (b->pos.y > SCREEN_H+1)
	{
		b->pos.y = -1;
	}
}
void accelerate_b(Bird* b)
{
	b->speed = b->acceleration;
	b->speed = normalize_v(b->speed);
}
void flock(Bird* b, Bird* birds, int birdsNB, Vector* obstacles, int obstaclesNB)
{
	b->acceleration = vec_v(0.f, 0.f, 0.f);
	b->acceleration = add_vec_v(b->acceleration, b->speed);
	float distTable[birdsNB];
	for (int i = 0; i < birdsNB; ++i)
	{
		distTable[i] = dist_v(b->pos, birds[i].pos);
	}
	b->acceleration = add_vec_v(b->acceleration, mult_scalar_v(center(b, birds, birdsNB, distTable), b->fCenter));
	b->acceleration = add_vec_v(b->acceleration, mult_scalar_v(align(b, birds, birdsNB, distTable), b->fAlign));
	b->acceleration = add_vec_v(b->acceleration, mult_scalar_v(repulse(b, birds, birdsNB, distTable), b->fRepulse));
	b->acceleration = add_vec_v(b->acceleration, mult_scalar_v(repulse_obstacle(b, obstacles, obstaclesNB), b->fRob));
}


Vector center(Bird* b, Bird* birds, int birdsNB, float* distTable)
{
	Vector steering = vec_v(0.f, 0.f, 0.f);
	int birdsInRadiusNB = 0;

	for (int i = 0; i < birdsNB; ++i)
	{
		if (birds[i].id != b->id && distTable[i] < b->pRCenter)
		{
			birdsInRadiusNB++;
			steering = add_vec_v(steering, birds[i].pos);
			// print_v(steering);
		}
	}

	if (birdsInRadiusNB > 0)
	{
		steering = divide_scal_v(steering, birdsInRadiusNB);
		steering = sub_vec_v(steering, b->pos);
		steering = normalize_v(steering);
		steering = sub_vec_v(steering, b->speed);
	}
	return steering;
}



Vector align(Bird* b, Bird* birds, int birdsNB, float* distTable)
{
	Vector steering = vec_v(0.f, 0.f, 0.f);
	int birdsInRadiusNB = 0;

	for (int i = 0; i < birdsNB; ++i)
	{
		if (birds[i].id != b->id && distTable[i] < b->pRAlign)
		{
			birdsInRadiusNB++;
			steering = add_vec_v(steering, birds[i].speed);
		}
	}

	if (birdsInRadiusNB > 0)
	{
		steering = divide_scal_v(steering, birdsInRadiusNB);
		steering = sub_vec_v(steering, b->speed);
	}
	return steering;
}
Vector repulse(Bird* b, Bird* birds, int birdsNB, float* distTable)
{
	Vector steering = vec_v(0.f, 0.f, 0.f);
	Vector repulseVec = vec_v(0.f, 0.f, 0.f);;
	int birdsInRadiusNB = 0;

	for (int i = 0; i < birdsNB; ++i)
	{
		if (birds[i].id != b->id && distTable[i] < b->pRRepulse)
		{
			birdsInRadiusNB++;
			repulseVec = sub_vec_v(birds[i].pos, b->pos);
			repulseVec = normalize_v(repulseVec);
			repulseVec = mult_scalar_v(repulseVec, -1 + distTable[i]/b->pRRepulse);
			steering = add_vec_v(steering, repulseVec);
		}
	}

	if (birdsInRadiusNB > 0)
	{
		steering = normalize_v(steering);
		steering = sub_vec_v(steering, b->speed);
	}
	return steering;
}

Vector repulse_obstacle(Bird* b, Vector* obstacles, int obstaclesNB)
{
	Vector steering = vec_v(0.f, 0.f, 0.f);
	Vector repulseVec = vec_v(0.f, 0.f, 0.f);;
	int obstaclesInRadiusNB = 0;
	float distOb = 0.f;

	for (int i = 0; i < obstaclesNB; ++i)
	{
		distOb = dist_v(b->pos, obstacles[i]);
		if (distOb < b->pRRob)
		{
			obstaclesInRadiusNB++;
			repulseVec = sub_vec_v(obstacles[i], b->pos);
			repulseVec = normalize_v(repulseVec);
			repulseVec = mult_scalar_v(repulseVec, -1 + distOb/b->pRRob);
			steering = add_vec_v(steering, repulseVec);
		}
	}

	if (obstaclesInRadiusNB > 0)
	{
		steering = normalize_v(steering);
		steering = sub_vec_v(steering, b->speed);
	}
	return steering;
}