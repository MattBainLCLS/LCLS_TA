#pragma once

#include <stdint.h>

#include "Spectrum.h"

class Frame
{
public:
	Frame();
	Frame(uint16_t* image);
	~Frame();

	Spectrum pumpOn;
	Spectrum pumpOff;
	Spectrum transientAbsorption;
	
};

