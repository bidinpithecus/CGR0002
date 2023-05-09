#ifndef _HELPERS_HPP_
#define _HELPERS_HPP_

#include <math.h>
#include "Utils.hpp"

Position normalize(Position position);
float square(const float num);
int randomNum(int min, int max);
float randomFloat(float min, float max);
float euclidianNormal(Position position);
float map(float value, float in_min, float in_max, float out_min, float out_max);

#endif
