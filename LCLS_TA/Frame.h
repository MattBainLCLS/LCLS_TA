#pragma once

#include <stdint.h>
#include <QtCore>
#include "Spectrum.h"
#include <armadillo>

class Frame
{
public:
	Frame(arma::Mat<double> image);
	arma::vec* pumpOffIntensities();
	arma::vec* pumpOnIntensities();
	arma::vec* transientAbsorptionIntensities();
	~Frame();

	int length; 
	arma::uvec pumpOffIndices;
	arma::uvec pumpOnIndices;

	arma::mat test;

	Spectrum pumpOn;
	Spectrum pumpOff;
	Spectrum transientAbsorption;
	
};

