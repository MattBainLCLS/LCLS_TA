#pragma once


#include <vector>

// Todo replace with Armadillo implementation?

class Spectrum
{

public:
	Spectrum();
	Spectrum(int pixels);
	~Spectrum();

	std::vector<double> intensity;
	std::vector<double> variance;
	std::vector<int> number;
};

