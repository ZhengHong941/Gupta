#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_

//base
#define lfb_port 4
#define lft_port 5
#define lbb_port 2
#define lbt_port 3
#define rfb_port 9
#define rft_port 8
#define rbb_port 20
#define rbt_port 19

#define twl_port 6
#define twr_port 18

//value of pi
#define pi 3.14159265358979

//omniwheel diameter is about 28 mm
#define tw_diameter 29
// distance between omniwheel is about 232 to 235 mm
#define base_diameter 197

#define base_error 2
// #define base_max_rpm 300
#define turn_max_rpm 250

//pid valules
#define base_kp 1.5
#define base_ki 0
#define base_kd 5

//base pid - turning
#define turn_kp 3
#define turn_ki 0
#define turn_kd 0

#define intake_roller_port 7
#define puncher_port 16


#endif