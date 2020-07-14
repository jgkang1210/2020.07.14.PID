#include<iostream>
#include<time.h> 

class PID { //PID object
private: //working variable
	unsigned long lastTime;
	double Input, Output, Setpoint;
	double errSum, lastErr;
	double ki, kp, kd;
	time_t time_now;

public:
	void setSetpoint(double _Setpoint);
	void setPIDconstant(double _kp, double _ki, double _kd);
	void Compute_output();
	void Print_current_output();

	PID() { //initiallizing
		time_t time_now;
		time_now = time(NULL);
		lastTime = unsigned long(time_now); //setting the initial time

		Input = 0, Output = 0, Setpoint = 0;
		errSum = 0, lastErr = 0;
		kp = 0, ki = 0, kd = 0;

		std::cout << "initial time : " << lastTime << std::endl;
	}
};

void PID::setSetpoint(double _Setpoint) {
	Setpoint = _Setpoint;
}

void PID::setPIDconstant(double _kp, double _ki, double _kd) { // set the kp, ki, kd value for system
	kp = _kp;
	ki = _ki;
	kd = _kd;
}

void PID::Compute_output() { // calculating the output of PID system
	time_now = time(NULL);
	unsigned long now = unsigned long(time_now);
	
	unsigned long time_change = now - lastTime; //time change

	//calculate the error variable
	double error = Setpoint - Input;
	errSum += (error * time_change);
	double dErr = (error - lastErr) / time_change;

	//coumpute pid output
	Output = kp * error + ki * errSum + kd * dErr;

	//re-setting the variales
	lastErr = error;
	lastTime = now;
}

void PID::Print_current_output() {
	std::cout<< "Input : " << Input << " Output : " << Output << " Setpoint : " << Setpoint <<std::endl;
}

int main() {
	PID system;
	double user_Setpoint = 100;
	double user_kp = 1, user_ki = 0, user_kd = 0;

	system.setSetpoint(user_Setpoint);
	system.setPIDconstant(user_kp, user_ki, user_kd);

	for (int i = 0; i < 100; i++) {
		system.Compute_output();
		system.Print_current_output();
	}


}