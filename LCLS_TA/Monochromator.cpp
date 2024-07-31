#include "Monochromator.h"

Monochromator::Monochromator()
{
}

bool Monochromator::connect()
{
	status = { 0 };
	char comPort[] = "COM2";
	comPort[3] = (char)(comNumber + 0x30);

	hSerial = CreateFileA((LPCSTR)comPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);

	if (hSerial == INVALID_HANDLE_VALUE);
	{
		// TODO Log Error
		return false;
	}

	if (!PurgeComm(hSerial, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
	{
		return false;
	}

	if (!ClearCommBreak(hSerial))
	{
		return false;
	}

	DCB dcbSerial;

	if (!GetCommState(hSerial, &dcbSerial))
	{
		return false;
	}

	dcbSerial.BaudRate = CBR_9600;
	dcbSerial.ByteSize = 8;
	dcbSerial.Parity = NOPARITY;
	dcbSerial.StopBits = ONESTOPBIT;

	if (!SetCommState(hSerial, &dcbSerial))
	{
		return false;
	}

	ClearCommError(hSerial, &errors, &status);

	serialWrite("NO-ECHO\r");
	serialRead();

	return true;
}

bool Monochromator::isConnected()
{
	return hSerial != INVALID_HANDLE_VALUE;
}

bool Monochromator::disconnect()
{
	return true;
}

int Monochromator::getComPort()
{
	return (int)comNumber;
}

void Monochromator::setComPort(int port)
{
	comNumber = (char)port;
}

Monochromator::~Monochromator()
{
	if (isConnected())
	{
		disconnect();
	}
}

int Monochromator::getGrating()
{
	serialWrite("?GRATING\r");
	std::stringstream infoStream(serialRead());
	std::string fragment;
	std::vector<std::string> fragments;

	while (std::getline(infoStream, fragment, ' '))
	{
		fragments.push_back(fragment);
	}

	return stoi(fragments[1]);
}

void Monochromator::setGrating(int index)
{
	std::string gratingIndex = std::to_string(index);

	serialWrite(gratingIndex + " GRATING\r");
	serialRead();
}

double Monochromator::getWavelength()
{
	serialWrite("?NM\r");
	std::stringstream infoStream(serialRead());
	std::string fragment;
	std::vector<std::string> fragments;

	while (std::getline(infoStream, fragment, ' '))
	{
		fragments.push_back(fragment);
	}

	return std::stod(fragments[1]);
}

void Monochromator::setWavelength(double wavelength)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(3) << wavelength;

	std::string instruction = stream.str() + " GOTO\r";

	serialWrite(instruction);
	serialRead();
}


// Private member functions

void Monochromator::serialWrite(std::string instruction)
{
	if (isConnected())
	{
		DWORD bc;
		const char* cstr = instruction.data();
		WriteFile(hSerial, cstr, instruction.size(), &bc, NULL);
	}
}

std::string Monochromator::serialRead()
{
	// Note doesn't depend on abs value of bytesAvail at any time because bytes don't appear simultaneously
	int bytesAvail = 0;

	std::string information;
	while (bytesAvail == 0) // Loop waiting for some bytes to appear
	{
		ClearCommError(hSerial, &errors, &status);
		bytesAvail = status.cbInQue;

	}

	DWORD bc;
	char tmpBuff = 0x00;
	do // while bytes are still available keep reading them in. 
	{
		if (bytesAvail > 0)
		{
			ReadFile(hSerial, &tmpBuff, 1, &bc, NULL);
			information.push_back(tmpBuff);
		}
		ClearCommError(hSerial, &errors, &status);
		bytesAvail = status.cbInQue;
	} while (tmpBuff != 0x0A); // Loop until the byte read is "\r" (0x0A is \r);

	return information;
}