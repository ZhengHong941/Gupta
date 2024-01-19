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
}

bool punch = false;

void puncher() {
	pros::Motor puncher(puncher_port);
	double currentPos;
	double startPos;
	// puncher.move_relative(-1900, 70);
	// while (true) {
		// if (punch) {
			// currentPos = puncher.get_position();
			// puncher.move_relative();
		// }
		

	// }


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
	pros::Motor puncher(puncher_port, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

	pros::Task leftbrake(left_brake);
	pros::Task rightbrake(right_brake);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	pros::Motor lfb_base(lfb_port);

	base_move(-450, 400);
	base_move(0, 700);
	base_move(300, 100);
	base_move(-300, 2000);
	base_move(0, 1000);
	std::cout << lfb_base.get_brake_mode() << std::endl;
	pros::delay(100);

	l_brake = true;
	r_brake = true;

	// power = -600;
	// lft_base.move_velocity(power);
	// lfb_base.move_velocity(power);
	// lbt_base.move_velocity(power);
	// lbb_base.move_velocity(power);
	// rft_base.move_velocity(power);
	// rfb_base.move_velocity(power);
	// rbt_base.move_velocity(power);
	// rbb_base.move_velocity(power);
	// std::cout << "back" << std::endl;
	// pros::delay(1000);

	// power = 0;
	// lft_base.move_velocity(power);
	// lfb_base.move_velocity(power);
	// lbt_base.move_velocity(power);
	// lbb_base.move_velocity(power);
	// rft_base.move_velocity(power);
	// rfb_base.move_velocity(power);
	// rbt_base.move_velocity(power);
	// rbb_base.move_velocity(power);
	// std::cout << "stop" << std::endl;
	// pros::delay(1000);

	// forward_pid(500, 500, 300);

	// turn_pid(90, true);
	// forward_pid(1300, 1300, 300);
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
	pros::Motor puncher(puncher_port);
	
	bool tankdrive = false; //drive mode control
	double left, right;
	double power, turn;

	bool puncher_rewind = true;

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

		if(master.get_digital_new_press(DIGITAL_R1)) {
			puncher.tare_position();
			if (puncher_rewind) {
				puncher.move_absolute(-1050, -70);
				puncher_rewind = false;
			}
			// puncher.move(0);
			// pros::delay(2);
		}
		std::cout << puncher.get_position() << std::endl;
		
		if(master.get_digital_new_press(DIGITAL_R2)) {
			puncher.move_velocity(100);
			pros::delay(200);
			puncher.move_velocity(0);
			puncher_rewind = true;

		}
	}
}
