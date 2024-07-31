#pragma once

#include <iostream>
#include "windows.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class Monochromator
{
public:

	Monochromator();
	~Monochromator();

	bool connect();
	bool isConnected();
	bool disconnect();

	int getComPort();
	void setComPort(int port);

	int getGrating();
	void setGrating(int index);

	double getWavelength();
	void setWavelength(double Wavelength);

private:
	HANDLE hSerial;
	COMSTAT status;
	DWORD errors;

	char comNumber = 3;
	char comPort[4];

	std::string serialRead();
	void serialWrite(std::string);
};

