#pragma once
#include <math.h>
#include <cstdlib>
#include <time.h>  


static float pi = atan(1) * 4;

struct Circle {
  float* Position;
  unsigned int* Index;
};

Circle CreateCircle(float radius, int division);

int RandomInt(int min, int max);