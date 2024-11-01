#pragma once

struct Random {
    // constructor
	Random();

    // returns an integer between a given range
	int randint(int start, int end);

    // returns a floating point value between a given range
	float randfloat(float start, float end);

    // returns an integer between a given range with a stepsize
	int randrange(int start, int end, int step); 
};