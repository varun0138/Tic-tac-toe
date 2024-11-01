#include "Random.hpp"

#include <iostream>
#include <ctime>

Random::Random() {
    srand((unsigned) time(NULL));
}

int Random::randint(int start, int end) {
    return (rand() % (end - start)) + start;
}

float Random::randfloat(float start, float end) {
    float range = end - start;
	return start + (rand() / (RAND_MAX / range));
}

int Random::randrange(int start, int end, int step) {
    int r = randint(start, end);
    return r - (r % step);
}