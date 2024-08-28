#include "DelayStage.h"

DelayStage::DelayStage()
{
	c_mm_per_ps = 0.5*0.299792458;
	inv_c_ps_per_mm = 1/c_mm_per_ps;
	comPort = "COM5";
	timeZeroPosition = 0;
	currentPosition = 0;

	reverse = false;

}

DelayStage::~DelayStage()
{

}

// Public Member Functions

bool DelayStage::connect()
{

	//boost::asio::io_service io;
	return true;



}

void DelayStage::setReverse(bool state)
{
	reverse = state;
}

void DelayStage::home()
{
	serialWrite("1OR\r");
	currentPosition = 0;
}

void DelayStage::goToTime(double time)
{

	double targetPosition = timeZeroPosition + timeToPos(time);

	reverse ? targetPosition *= -1 : targetPosition;

	std::string instruction = "1PA" + std::to_string(targetPosition) + "\r";

	serialWrite(instruction);

	currentPosition = targetPosition;
}

double DelayStage::getTime()
{
	return posToTime(currentPosition- timeZeroPosition);
}

void DelayStage::setTimeZero()
{
	timeZeroPosition = currentPosition;
}


bool DelayStage::disconnect()
{

}

// Private Member Functions


double DelayStage::timeToPos(double time)
{
	return time * c_mm_per_ps;

}

double DelayStage::posToTime(double position)
{
	return position * inv_c_ps_per_mm;
}


void DelayStage::serialWrite(std::string instruction)
{

	boost::asio::io_service io;
	boost::asio::serial_port serial(io);
	serial.open(comPort);
	serial.set_option(boost::asio::serial_port_base::baud_rate(921600));
	serial.set_option(boost::asio::serial_port_base::character_size(8));
	serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

	if (serial.is_open())
	{
		std::cout << "Connected, writing..." << std::endl;
		boost::asio::write(serial, boost::asio::buffer(instruction));

	}

	serial.close();

}
