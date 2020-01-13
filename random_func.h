#pragma once

#include <random>
#include <vector>

#include "CONFIGURATION.h"


int random(int min, int max);// range is <min, max>

template <typename T>
T random_from_vect(std::vector<T> vect)
{
	int max = vect.size() - 1;
	int randNumb = random(0, max);
	return vect[randNumb];
}