#include<iostream>
#include<time.h>
#include<fstream>
#include<string>
#include<chrono>

class PID { //PID object
private: //working variable
	unsigned long lastTime;
	double Input, Output, Setpoint;
	double errSum, lastErr;
	double ki, kp, kd;
	unsigned long sample_time = 1000; // 0.1 sec
	unsigned __int64 time_now;

public:
	void setSetpoint(double _Setpoint);
	void setPIDconstant(double _kp, double _ki, double _kd);
	void Compute_output();
	std::string Print_current_status();
	void Set_sample_time(unsigned long NewSampleTime);

	PID() { //initiallizing
		time_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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

// set the kp, ki, kd value for system
void PID::setPIDconstant(double _kp, double _ki, double _kd) { 
	kp = _kp;
	ki = _ki * sample_time;
	kd = _kd / sample_time;
}

void PID::Set_sample_time(unsigned long NewSampleTime)
{
	if (NewSampleTime > 0)
	{
		double ratio = double(NewSampleTime)/double(sample_time);
		ki *= ratio;
		kd /= ratio;
		sample_time = unsigned long(NewSampleTime);
	}
}

void PID::Compute_output() { // calculating the output of PID system
	time_now = unsigned long(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	
	unsigned long time_change = time_now - lastTime; //time change

	if (time_change >= sample_time) { //time change must be bigger than 0.1 seconds
		//calculate the error variable
		double error = Setpoint - Input;
		errSum += (error * (time_change/1000));
		double dErr = (error - lastErr) / (time_change/1000);

		//coumpute pid output
		Output = kp * error + ki * errSum + kd * dErr;

		//re-setting the variales
		lastErr = error;
		lastTime = time_now;
	}
}

//printing the value of input, output, setpoint
std::string PID::Print_current_status() {
	std::string pid_record_string;

	std::cout << "Input : " << Input << " Output : " << Output << " Setpoint : " << Setpoint << std::endl;
	std::cout << "Current time : " << lastTime << std::endl;

	return std::to_string(Input) + "," + std::to_string(Output) + "," + std::to_string(Setpoint) + "," + std::to_string(lastTime) + "\n";
}

int main() {
	// create csv file to record the data
	std::ofstream pid_record_tape("graph.csv", std::ios::app);

	// create pid system
	PID system;
	double user_Setpoint = 100;
	double user_kp = 0.6, user_ki = 0.02, user_kd = 0.001;

	system.setSetpoint(user_Setpoint);
	system.setPIDconstant(user_kp, user_ki, user_kd);

	for (int i = 0; i < 10000; i++) {
		system.Compute_output();
		std::cout << "Current step : " << i << std::endl;
		pid_record_tape << system.Print_current_status();
	}
}