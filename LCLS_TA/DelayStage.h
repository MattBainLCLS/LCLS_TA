#pragma once

#include <boost/asio.hpp>
#include <iostream>

class DelayStage
{

public:
	DelayStage();
	~DelayStage();

	bool connect();
	void setReverse(bool state);
	void home();
	void goToTime(double time);
	double getTime();
	void setTimeZero();
	bool disconnect();

private:

	//boost::asio::io_service io;

	//boost::asio::serial_port serial;

	std::string comPort;

	void serialWrite(std::string instruction);

	double timeZeroPosition;

	double currentPosition;

	double timeToPos(double time);
	double posToTime(double position);

	double c_mm_per_ps;

	double inv_c_ps_per_mm;

	bool reverse;

};


