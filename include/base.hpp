#ifndef BASE_HPP
#define BASE_HPP

void forward_pid(float TARGET_L, float TARGET_R, int base_max_rpm);
void turn_pid(double TARGET_ANGLE, bool clockwise);

#endif