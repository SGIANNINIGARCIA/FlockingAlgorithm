#pragma once

namespace Flocking {

  const int    WEIGHTS_RANGE       = 50;
  const int    WEIGHTS_FEAR        = 1;
  const int    STRETCH_FACTOR      = 100;
  const double PI                  = 3.141592653;
  const double DEG_TO_RAD          = (PI/180.0);
  const double RAD_TO_DEG          = (180.0/PI);
  const double EPSILON             = 0.000001;
  const double MIN_AVOID_DIST      = 30;
  const double  DESIRED_SPEED      = 5;
  const double MAX_AVOID_FORCE     = 30;
  const double MAX_SEE_AHEAD_DISTANCE = 30;
  const int ADD_PREY = 10;

}
