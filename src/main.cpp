#include "main.h"


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
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}


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
	pros::Motor intake(intake_port);
	int intake_power = 120;

	//cascade
	pros::Motor dpl(dpl_port);
	pros::Motor dpr(dpr_port);

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
		intake.move(((master.get_digital(DIGITAL_L1)) - master.get_digital(DIGITAL_L2)) * intake_power);

		//cascade driver pulley control
		dpl.move(((master.get_digital(DIGITAL_R1)) - master.get_digital(DIGITAL_R2)) * intake_power);
		dpr.move(((master.get_digital(DIGITAL_R1)) - master.get_digital(DIGITAL_R2)) * intake_power);
	}
}
