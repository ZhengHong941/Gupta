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
bool puncher_auto = true;
bool punch = false;
uint32_t end_time;

void puncher_function() {
	pros::Motor puncher_rewind(puncher_rewind_port);
	pros::Motor puncher_release(puncher_release_port);

	while(true){

		if (punch) {
			std::cout << "punching" << std::endl;
			puncher_release.move(-127);
			pros::delay(400);
			puncher_release.move(127);
			pros::delay(100);
			puncher_release.move(0);
			punch = false;
			rewind_puncher = true;
		}
		
		if (rewind_puncher && (puncher_auto)) {
			// puncher_rewind.tare_position();
			puncher_rewind.move(127);
			pros::delay(100);
			while (puncher_rewind.get_actual_velocity() > 0) {
				puncher_rewind.move(127);
				pros::delay(2);
			}
			puncher_rewind.move(0);
			pros::delay(2);
			rewind_puncher = false;
			end_time = pros::millis();
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

	punch = true;
	pros::delay(2000);
	forward_pid(-800, -800, 600);
	forward_pid(-500, -500, 300);
	turn_pid(90, true);
	base_move(100, 400);
	forward_pid(-1350, -1350, 400);
	turn_pid(90, true);
	base_move(100, 1000);

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
	int cam = 0;

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

		if(master.get_digital(DIGITAL_UP)) {
			puncher_rewind.move(127);
			pros::delay(5);
			puncher_rewind.move(0);
			pros::delay(1);
			rewind_puncher = false;
		}

		if(master.get_digital_new_press(DIGITAL_DOWN)) {
			puncher_auto = !puncher_auto;
			pros::delay(2);
		}

		if(master.get_digital_new_press(DIGITAL_R1)) {
			rewind_puncher = true;
			// std::cout << puncher_rewind.get_current_draw() << " : " << puncher_release.get_current_draw() << std::endl;
		}
		if(master.get_digital_new_press(DIGITAL_R2)) {
			punch = true;
			// std::cout << puncher_rewind.get_current_draw() << " : " << puncher_release.get_current_draw() << std::endl;
		}
		if(master.get_digital_new_press(DIGITAL_UP)) {
			puncher_rewind.move(127);
			pros::delay(10);
			puncher_rewind.move(0);
			pros::delay(2);
		}
		if(master.get_digital_new_press(DIGITAL_LEFT)) {
			for (int i = 1; i <= 12; i++) {
				uint32_t start_time = pros::millis();
				punch = true;
				pros::delay(1800);
				std::cout << (end_time - start_time) << std::endl;
				pros::delay(2);
			}
		}
		// if(master.get_digital_new_press(DIGITAL_RIGHT)) {
		// 	cam++;
		// 	cam = cam % 3;
		// 	if (cam == 1) {
		// 		puncher_release.move(127);
		// 	}
		// 	else if (cam == 2) {
		// 		puncher_release.move(0);
		// 	}
		// 	pros::delay(2);
		// }
		pros::delay(2);
	}
}
