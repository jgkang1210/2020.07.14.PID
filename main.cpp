#include<iostream>
#include<time.h> 

class PID {
private:
	unsigned long lastTime;
	double Input, Output, Setpoint;
	double errSum, lastErr;
	double ki, kp, kd;

public:
	double setSetpoint(double _Setpoint);
	double setPIDconstant(double _kp, double _ki, double _kd);
	double Compute_output();

	PID() { //initiallizing
		time_t time_now;
		time_now = time(NULL);
		unsigned long lastTime = unsigned long(lastTime);

		Input, Output, Setpoint = 0;
		errSum, lastErr = 0;
		kp, ki, kd = 0;
	}
};

double PID::setSetpoint(double _Setpoint) {
	Setpoint = _Setpoint;
}

double PID::setPIDconstant(double _kp, double _ki, double _kd) {
	kp = _kp;
	ki = _ki;
	kd = _kd;
}

double PID::Compute_output() {
	time_t time_now;
	time_now = time(NULL);
	unsigned long now = unsigned long(time_now);
	
	
}

int main() {
	PID system;
	double user_Setpoint;
	double user_kp, user_ki, user_kd;

	system.setSetpoint(user_Setpoint);
	system.setPIDconstant(user_kp, user_ki, user_kd);
	system.Compute_output();


}