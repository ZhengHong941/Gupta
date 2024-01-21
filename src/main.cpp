#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

bool l_brake = false;
bool r_brake = false;

void left_brake() {
	pros::Motor lfb_base(lfb_port);
	pros::Motor lft_base(lft_port);
	pros::Motor lbb_base(lbb_port);
	pros::Motor lbt_base(lbt_port);
	while (true) {
		while(l_brake){
			lft_base.brake();
			lfb_base.brake();
			lbt_base.brake();
			lbb_base.brake();
			pros::delay(2);
		}
	}
}
void right_brake() {
	pros::Motor rfb_base(rfb_port);
	pros::Motor rft_base(rft_port);
	pros::Motor rbb_base(rbb_port);
	pros::Motor rbt_base(rbt_port);
	while (true) {
		while (r_brake) {
			rft_base.brake();
			rfb_base.brake();
			rbt_base.brake();
			rbb_base.brake();
			pros::delay(2);
		}
	}
}

void base_move(int power, int delay) {
	//base
    pros::Motor lfb_base(lfb_port);
	pros::Motor lft_base(lft_port);
	pros::Motor lbb_base(lbb_port);
	pros::Motor lbt_base(lbt_port);
	pros::Motor rfb_base(rfb_port);
	pros::Motor rft_base(rft_port);
	pros::Motor rbb_base(rbb_port);
	pros::Motor rbt_base(rbt_port);

	if (!l_brake) {
		lft_base.move_velocity(power);
		lfb_base.move_velocity(power);
		lbt_base.move_velocity(power);
		lbb_base.move_velocity(power);
	}
	else {
		lft_base.move_velocity(0);
		lfb_base.move_velocity(0);
		lbt_base.move_velocity(0);
		lbb_base.move_velocity(0);
	}
	if (!r_brake) {
		rft_base.move_velocity(power);
		rfb_base.move_velocity(power);
		rbt_base.move_velocity(power);
		rbb_base.move_velocity(power);
	}
	else {
		rft_base.move_velocity(0);
		rfb_base.move_velocity(0);
		rbt_base.move_velocity(0);
		rbb_base.move_velocity(0);
	}
	pros::delay(delay);
	lft_base.move_velocity(0);
	lfb_base.move_velocity(0);
	lbt_base.move_velocity(0);
	lbb_base.move_velocity(0);
	rft_base.move_velocity(0);
	rfb_base.move_velocity(0);
	rbt_base.move_velocity(0);
	rbb_base.move_velocity(0);
}


bool rewind_puncher = false;
bool punch = false;
bool puncher_rewind;
bool puncher_release;

void puncher_function() {
	pros::Motor puncher_rewind(puncher_rewind_port);
	pros::Motor puncher_release(puncher_release_port);

	while(true){
		if (punch) {
			std::cout << "punching" << std::endl;
			puncher_release.move_velocity(-100);
			pros::delay(2000);
			puncher_release.move_velocity(100);
			pros::delay(300);
			puncher_release.move_velocity(0);
			punch = false;
			rewind_puncher = true;
		}
		if ( rewind_puncher && (!punch) ) {
			puncher_rewind.tare_position();
			while (puncher_rewind.get_position() < 1000) {	
				puncher_rewind.move(120);
				pros::delay(2);
			}
			puncher_rewind.move(0);
			pros::delay(2);
			rewind_puncher = false;
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
	lft_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lfb_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lbb_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lbt_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rft_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rfb_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rbb_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rbt_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	pros::Motor intake_roller(intake_roller_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor puncher_rewind(puncher_rewind_port, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor puncher_release(puncher_release_port, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Task leftbrake(left_brake);
	pros::Task rightbrake(right_brake);
	pros::Task puncher_task(puncher_function);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	pros::Motor lfb_base(lfb_port);

	base_move(-450, 300);
	// pros::delay(1000);
	base_move(250, 500);
	pros::delay(1000);
	base_move(-200, 3000);
	pros::delay(100);

	l_brake = true;
	r_brake = true;



	// forward_pid(-500, -500, 300);
	// turn_pid(90, false);
	// base_move(100, 400);
	// forward_pid(-1350, -1350, 400);
	// turn_pid(90, false);
	// base_move(100, 1000);

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

	pros::Motor intake_roller(intake_roller_port);
	pros::Motor puncher_rewind(puncher_rewind_port);
	pros::Motor puncher_release(puncher_release_port);
	
	bool tankdrive = false; //drive mode control
	double left, right;
	double power, turn;

	while(true){
        //base control
		if(master.get_digital_new_press(DIGITAL_Y)) tankdrive = !tankdrive; //tank toggle
        if(tankdrive) {
            left = master.get_analog(ANALOG_LEFT_Y);
            right = master.get_analog(ANALOG_RIGHT_Y);
        }      
        else {
            power =  master.get_analog(ANALOG_LEFT_Y);
            turn = master.get_analog(ANALOG_RIGHT_X);
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

		if(master.get_digital(DIGITAL_L1)) {
			intake_roller.move(120);
		}
		else if (master.get_digital(DIGITAL_L2)) {
			intake_roller.move(-120);
		}
		else {
			intake_roller.move(0);
		}

		// if(master.get_digital(DIGITAL_UP) && master.get_digital_new_press(DIGITAL_R1)) {
		// 	puncher.move_velocity(100);
		// 	pros::delay(200);
		// 	puncher.move_velocity(0);
		// 	puncher_rewind = true;
		// }
		// if(master.get_digital(DIGITAL_DOWN)) {
		// 	puncher.move(-100);
		// 	pros::delay(2);
		// }
		// else {
		// 	puncher.move(0);
		// 	pros::delay(2);
		// }

		// if(master.get_digital_new_press(DIGITAL_R1)) {
		// 	puncher.tare_position();
		// 	if (puncher_rewind) {
		// 		puncher.move_absolute(-1050, -70); // 1050 for full draw
		// 		puncher_rewind = false;
		// 	}
		// }
		// if(master.get_digital_new_press(DIGITAL_R1)) {
		// 	rewind_puncher = true;
		// }
		if(master.get_digital(DIGITAL_UP)) {
			puncher_rewind.move(127);
			pros::delay(5);
			puncher_rewind.move(0);
			pros::delay(1);
			rewind_puncher = false;
		}

		if(master.get_digital_new_press(DIGITAL_R2)) {
			punch = true;
		}

		// std::cout << puncher.get_position() << std::endl;
		
		// if(master.get_digital_new_press(DIGITAL_R2)) {
		// 	puncher.move_velocity(100);
		// 	pros::delay(200);
		// 	puncher.move_velocity(0);
		// 	puncher_rewind = true;
		// }
	}
}
