#include "Utilities.h"



Circle CreateCircle(float radius, int division) {
  float* position = new float[(division + 1) * 2];
  unsigned int* index = new unsigned int[division * 3];

  float divisionAngle = ((2 * pi) / division);

  position[0] = 0.0f;
  position[1] = 0.0f;

  float x = 0.0f;
  float y = radius;


  for (int i = 0; i < division; i++) {

    position[(2 * i) + 2] = x;
    position[(2 * i) + 3] = y;

    float xnew = (x * cos(divisionAngle)) - (y * sin(divisionAngle));
    float ynew = (x * sin(divisionAngle)) + (y * cos(divisionAngle));

    x = xnew;
    y = ynew;
  }

  for (int i = 0; i < division; i++) {
    if (i != (division - 1)) {
      index[3 * i] = 0;
      index[(3 * i) + 1] = i + 1;
      index[(3 * i) + 2] = i + 2;
    }
    else {
      index[3 * i] = 0;
      index[(3 * i) + 1] = i + 1;
      index[(3 * i) + 2] = 1;
    }
  }


  return { position,index };

}