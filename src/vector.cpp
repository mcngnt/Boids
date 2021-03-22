#include "vector.h"


Vector vec_v(float x, float y, float z)
{
	Vector myVec;
	myVec.x = x;
	myVec.y = y;
	myVec.z = z;
	return myVec;
}

Vector print_v(Vector vec)
{
	printf("(%f, %f, %f)\n", vec.x, vec.y, vec.z);
	return vec;
}

Vector add_vec_v(Vector vec1, Vector vec2)
{
	return vec_v(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

Vector invert_v(Vector vec)
{
	return vec_v(-vec.x, -vec.y, -vec.z);
}

Vector sub_vec_v(Vector vec1, Vector vec2)
{
	return add_vec_v(vec1, invert_v(vec2));
}

Vector add_scal_v(Vector vec, float scalar)
{
	return vec_v(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

Vector sub_scalar_v(Vector vec, float scalar)
{
	return add_scal_v(vec, -scalar);
}

float get_norm_v(Vector vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

float dist_v(Vector vec1, Vector vec2)
{
	Vector diffVec = sub_vec_v(vec1, vec2);
	return get_norm_v(diffVec);
}

Vector divide_scal_v(Vector vec, float scalar)
{
	if(scalar == 0)
	{
		return vec;
	}
	return vec_v(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

Vector divide_vec_v(Vector vecNum, Vector vecDenom)
{
	Vector result;
	if (vecDenom.x == 0)
	{
		result.x = vecNum.x;
	}
	else
	{
		result.x = vecNum.x / vecDenom.x;
	}
	if (vecDenom.y == 0)
	{
		result.y = vecNum.y;
	}
	else
	{
		result.y = vecNum.y / vecDenom.y;
	}
	if (vecDenom.z == 0)
	{
		result.z = vecNum.z;
	}
	else
	{
		result.z = vecNum.z / vecDenom.z;
	}
	return result;
}

int equal_v(Vector vec1, Vector vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

Vector abs_v(Vector vec)
{
	return vec_v(abs(vec.x), abs(vec.y), abs(vec.z));
}

float dot_v(Vector vec1, Vector vec2)
{
	return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

Vector normalize_v(Vector vec)
{
	return divide_scal_v(vec, get_norm_v(vec));
}

Vector mult_scalar_v(Vector vec, float scalar)
{
	return vec_v(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

Vector max_v(Vector vec, float scalMax)
{
	return vec_v(fmax(vec.x, scalMax), fmax(vec.y, scalMax), fmax(vec.z, scalMax));
}

Vector min_v(Vector vec, float scalMin)
{
	return vec_v(fmin(vec.x, scalMin), fmin(vec.y, scalMin), fmin(vec.z, scalMin));
}

float get_angle_v(Vector vec)
{
	return atan2(vec.y,vec.x) + PI/2;
}

Vector vec_from_angle_v(float angle)
{
	Vector vec;
	vec.x = cos(angle - PI/2);
	vec.y = sin(angle - PI/2);
	return vec;
}

Vector random_vec_v(int minX, int maxX, int minY, int maxY)
{
	Vector vec;
	vec.x = (float)((rand() % (maxX + abs(minX))) - minX);
	vec.y = (float)((rand() % (maxY + abs(minY))) - minY);
	return vec;
}

sf::Vector2f vec_to_sfvec2_v(Vector vec)
{
	return sf::Vector2f(vec.x, vec.y);
}

Vector sfvec2_to_vec_v(sf::Vector2f vec)
{
	return vec_v(vec.x, vec.y, 0.f);
}