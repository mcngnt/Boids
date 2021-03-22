#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Graphics.hpp>

#pragma once

#define PI 3.14

typedef struct Vector
{
	float x, y, z;
} Vector;

Vector vec_v(float, float, float);
Vector print_v(Vector);
Vector add_vec_v(Vector, Vector);
Vector invert_v(Vector);
Vector sub_vec_v(Vector, Vector);
Vector add_scal_v(Vector, float);
Vector sub_scalar_v(Vector, float);
float get_norm_v(Vector);
float dist_v(Vector, Vector);
Vector divide_scal_v(Vector, float);
Vector divide_vec_v(Vector, Vector);
int equal_v(Vector, Vector);
Vector abs_v(Vector);
float dot_v(Vector, Vector);
Vector normalize_v(Vector);
Vector mult_scalar_v(Vector, float);
Vector max_v(Vector, float);
Vector min_v(Vector, float);
float get_angle_v(Vector);
Vector vec_from_angle_v(float);
Vector random_vec_v(int, int, int, int);
sf::Vector2f vec_to_sfvec2_v(Vector);
Vector sfvec2_to_vec_v(sf::Vector2f);

#endif