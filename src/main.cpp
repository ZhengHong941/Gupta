#include "main.h"

double prevErrorLeft = 0;
double prevErrorRight = 0;
double encdleft = 0;
double encdright = 0;
double errorLeft = 0;
double errorRight = 0;
double LEFTTARGET = 0;
double RIGHTTARGET = 0;

void pidvalues(double targleft, double targright){
  LEFTTARGET = targleft;
  RIGHTTARGET = targright;

  errorLeft = targleft;
  errorRight = targright;
}

void pidmove() {
    using namespace pros;
    
	pros::Motor lfb_base(lfb_port);
	pros::Motor lft_base(lft_port);
	pros::Motor lbb_base(lbb_port);
	pros::Motor lbt_base(lbt_port);
	pros::Motor rfb_base(rfb_port);
	pros::Motor rft_base(rft_port);
	pros::Motor rbb_base(rbb_port);
	pros::Motor rbt_base(rbt_port);
    
    //25 units = 1cm
    //and fabs(errorRight) >= 50
    while (true){
        if (fabs(errorLeft) >= 50 ){
            while (fabs(errorLeft) >= 50 ){
                encdleft = lft_base.get_position();
                encdright = rft_base.get_position();

                errorLeft = LEFTTARGET - encdleft;
                errorRight = RIGHTTARGET - encdright;

                double deltaErrorLeft = errorLeft - prevErrorLeft;
                double deltaErrorRight = errorRight - prevErrorRight;

                double powerL = base_kp * (errorLeft/25) + base_kd * deltaErrorLeft;
                double powerR = base_kp * (errorRight/25) + base_kd * deltaErrorRight;

                lfb_base.move(powerL);
        		lft_base.move(powerL);
        		lbb_base.move(powerL);
				lbt_base.move(powerL);
        		rfb_base.move(powerR);
        		rft_base.move(powerR);
        		rbb_base.move(powerR);
				rbt_base.move(powerR);

    
                //printf("encdleft: %f encdright:%f errorleft:%f errorright:%f deltaerrleft:%f deltaerrright:%f \n",\
                encdleft, encdright, errorLeft, errorRight, deltaErrorLeft, deltaErrorRight);

                prevErrorLeft = errorLeft;
                prevErrorRight = errorRight;
                pros::delay(2);
            }
        }
        pros::delay(2);
    }
}


void initialize() {
	//controller
    pros::Controller master(CONTROLLER_MASTER);

	//base
    pros::Motor lfb_base(lfb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lft_base(lft_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lbb_base(lbb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lbt_base(lbt_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rfb_base(rfb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rft_base(rft_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rbb_base(rbb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rbt_base(rbt_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor intake(intake_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor dpl(dpl_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor dpr(dpr_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Task hardcode(pidmove);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}


void opcontrol() {
	
	int a_l = 2000/76*165;
	int a_r = 2000/76*165;
	// int b_l = 2000;
	// int b_r = 3000;
	// int c_l = 2650;
	// int c_r = 2300;
	// int d_l = 1000;
	// int d_r = -1000;
	// int e_l = -2300;
	// int e_r = -1750;

	pidvalues(a_l, a_r);
	pros::delay(2000);
	// pidvalues(a_l+b_l, a_r+b_r);
	// pros::delay(70);
	// pidvalues(a_l+b_l+c_l, a_r+b_r+c_r);
	// pros::delay(100);
	// //controller
    // pros::Controller master(CONTROLLER_MASTER);

	// //base
    // pros::Motor lfb_base(lfb_port);
	// pros::Motor lft_base(lft_port);
	// pros::Motor lbb_base(lbb_port);
	// pros::Motor lbt_base(lbt_port);
	// pros::Motor rfb_base(rfb_port);
	// pros::Motor rft_base(rft_port);
	// pros::Motor rbb_base(rbb_port);
	// pros::Motor rbt_base(rbt_port);
	// bool tankdrive = false; //drive mode control

	// //intake
	// pros::Motor intake(intake_port);
	// int intake_power = 120;

	// //cascade
	// pros::Motor dpl(dpl_port);
	// pros::Motor dpr(dpr_port);

	// while(true){

    //     //base control
    //     double left, right;
        
	// 	if(master.get_digital_new_press(DIGITAL_Y)) tankdrive = !tankdrive; //tank toggle

    //     if(tankdrive) {
    //         left = master.get_analog(ANALOG_LEFT_Y);
    //         right = master.get_analog(ANALOG_RIGHT_Y);
    //     } 
                
    //     else {
    //         double power =  master.get_analog(ANALOG_LEFT_Y);
    //         double turn = master.get_analog(ANALOG_RIGHT_X);
    //         left = power + turn;
    //         right = power - turn;
    //     }

    //     lfb_base.move(left);
    //     lft_base.move(left);
    //     lbb_base.move(left);
	// 	lbt_base.move(left);
    //     rfb_base.move(right);
    //     rft_base.move(right);
    //     rbb_base.move(right);
	// 	rbt_base.move(right);

	// 	//intake control
	// 	intake.move(((master.get_digital(DIGITAL_L1)) - master.get_digital(DIGITAL_L2)) * intake_power);

	// 	//cascade driver pulley control
	// 	dpl.move(((master.get_digital(DIGITAL_R1)) - master.get_digital(DIGITAL_R2)) * intake_power);
	// 	dpr.move(((master.get_digital(DIGITAL_R1)) - master.get_digital(DIGITAL_R2)) * intake_power);
	// }
}
