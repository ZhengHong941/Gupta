#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

double prevErrorLeft = 0;
double prevErrorRight = 0;
double encdleft = 0;
double encdright = 0;
double errorLeft = 0;
double errorRight = 0;
double LEFTTARGET = 0;
double RIGHTTARGET = 0;
double deltaErrorLeft = 0;
double deltaErrorRight = 0;
double powerL = 0;
double powerR = 0;

void pidvalues(double targleft, double targright){
	LEFTTARGET = targleft;
	RIGHTTARGET = targright;
	errorLeft = targleft;
	errorRight = targright;
}

void pidmove() {
    // using namespace pros;
	pros::Motor lfb_base(lfb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lft_base(lft_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lbb_base(lbb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lbt_base(lbt_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rfb_base(rfb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rft_base(rft_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rbb_base(rbb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rbt_base(rbt_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Rotation trackingwheel_l(twl_port);
	pros::Rotation trackingwheel_r(twr_port);
	trackingwheel_l.set_position(0);
	trackingwheel_r.set_position(0);
	while(true){
		// std::cout << "0" << std::endl;
		// pros::delay(20);
		encdleft = trackingwheel_l.get_position() * pi * 28 / 36000;
		encdright = trackingwheel_r.get_position() * pi * 28 / 36000;
		errorLeft = LEFTTARGET - encdleft;
		errorRight = RIGHTTARGET - encdright;
		deltaErrorLeft = errorLeft - prevErrorLeft;
		deltaErrorRight = errorRight - prevErrorRight;
		powerL = base_kp * errorLeft + base_ki * prevErrorLeft + base_kd * deltaErrorLeft; // divide 25 to prevent from going insane - kp must not be too high - when ki=0.1 kd=0,  
		powerR = base_kp * errorRight + base_ki * prevErrorRight + base_kd * deltaErrorRight;
		printf("encdleft: %f \n", encdleft);
		printf("encdright: %f \n", encdright);
		if (fabs(errorLeft) >= base_error ){
			lft_base.move(powerL);
			lfb_base.move(powerL);
			lbt_base.move(powerL);
			lbb_base.move(powerL);
			rft_base.move(powerR);
			rfb_base.move(powerR);
			rbt_base.move(powerR);
			rbb_base.move(powerR);
			printf("powerL: %f \n", powerL);
			printf("powerR: %f \n", powerR);
			pros::delay(2);
		}
		else {
			powerL = 0;
			powerR = 0;
			lft_base.move(powerL);
			lfb_base.move(powerL);
			lbt_base.move(powerL);
			lbb_base.move(powerL);
			rft_base.move(powerR);
			rfb_base.move(powerR);
			rbt_base.move(powerR);
			rbb_base.move(powerR);
			pros::delay(2);
		}
		prevErrorLeft = errorLeft;
		prevErrorRight = errorRight;
		pros::delay(2);
		
	}
}

bool brake = false;

void base_brake() {
	pros::Motor lfb_base(lfb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lft_base(lft_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lbb_base(lbb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lbt_base(lbt_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rfb_base(rfb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rft_base(rft_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rbb_base(rbb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rbt_base(rbt_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

	if (brake){
		lfb_base.brake();
		lft_base.brake();
		lbb_base.brake();
		lbt_base.brake();
		rfb_base.brake();
		rft_base.brake();
		rbb_base.brake();
		rbt_base.brake();
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
	//tracking wheel
	pros::Rotation trackingwheel_l(twl_port);
	pros::Rotation trackingwheel_r(twr_port);
	trackingwheel_l.set_position(0);
	trackingwheel_r.set_position(0);

}

void disabled() {}

void competition_initialize() {}

void autonomous() {

	pros::Task base_pid(pidmove);
	pros::delay(2);
	// pros::Motor intake(intake_port);

	// int a_l = 1000; //2000/76*165
	// int a_r = 1000; //2000/76*165
	// int b_l = -10000;
	// int b_r = -10000;
	// //crossing barrier
	// int c_l = -10000;
	// int c_r = -10000;
	// int d_l = 16000;
	// int d_r = 16000;

	// pidmove(-5000, -5000);
	// pros::delay(1000);
	// // encoder_reset();
	// //base_break();
	// //pros::delay(1000);
	
	// pidmove(10000, 10000);
	// pros::delay(1000);
	// // encoder_reset();
	// base_break();
	// pros::delay(1000);

	// pidvalues(800, 800);
	// pros::delay(500);
	// encoder_reset();
	// base_break();
	// pros::delay(2000);

	// pidvalues(600, -600);
	// pros::delay(500);
	// encoder_reset();
	// base_break();
	// pros::delay(2000);

	// pidvalues(1000, 1000);
	// int intake_power = 120;
	// pros::delay(700);
	// encoder_reset();
	// base_break();
	// pros::delay(5000);



	// pidvalues(-1000, -1000);
	// pros::delay(500);
	// encoder_reset();
	// pidvalues(-1000, -1000);
	// pros::delay(500);
	// encoder_reset();


	// //crossing barrier
	// pidvalues(-10000, -10000);
	// pros::delay(200);
	// base_break();
	// pros::delay(50);
	// encoder_reset();
	// pidvalues(16000, 16000);
	// pros::delay(3000);
	// pidvalues(d_l, d_r);
	// pidvalues(e_l, e_r);

}


void opcontrol() {
	//controller
    pros::Controller master(CONTROLLER_MASTER);

	//base
    pros::Motor lfb_base(lfb_port);
	pros::Motor lft_base(lft_port);
	pros::Motor lbb_base(lbb_port);
	pros::Motor lbt_base(lbt_port);
	pros::Motor rfb_base(rfb_port);
	pros::Motor rft_base(rft_port);
	pros::Motor rbb_base(rbb_port);
	pros::Motor rbt_base(rbt_port);
	bool tankdrive = false; //drive mode control

	//intake
	// pros::Motor intake(intake_port);
	// int intake_power = 120;

	//cascade
	// pros::Motor dpl(dpl_port);
	// pros::Motor dpr(dpr_port);

	while(true){

        //base control
        double left, right;
        
		if(master.get_digital_new_press(DIGITAL_Y)) tankdrive = !tankdrive; //tank toggle

        if(tankdrive) {
            left = master.get_analog(ANALOG_LEFT_Y);
            right = master.get_analog(ANALOG_RIGHT_Y);
        } 
                
        else {
            double power =  master.get_analog(ANALOG_LEFT_Y);
            double turn = master.get_analog(ANALOG_RIGHT_X);
            left = power + turn;
            right = power - turn;
        }

        lfb_base.move(left);
        lft_base.move(left);
        lbb_base.move(left);
		lbt_base.move(left);
        rfb_base.move(right);
        rft_base.move(right);
        rbb_base.move(right);
		rbt_base.move(right);

		//intake control
		// intake.move(((master.get_digital(DIGITAL_L1)) - master.get_digital(DIGITAL_L2)) * intake_power);

		//cascade driver pulley control
		// dpl.move(((master.get_digital(DIGITAL_R1)) - master.get_digital(DIGITAL_R2)) * intake_power);
		// dpr.move(((master.get_digital(DIGITAL_R1)) - master.get_digital(DIGITAL_R2)) * intake_power);
	}
}
