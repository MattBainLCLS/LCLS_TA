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
	~Frame();

	arma::Mat<double> myimage;
	int length; 
	arma::uvec pumpOffIndices; // = arma::conv_to<arma::uvec>::from(arma::linspace(0, length, length / 2));
	arma::uvec pumpOnIndices;

	arma::mat test;

	Spectrum pumpOn;
	Spectrum pumpOff;
	Spectrum transientAbsorption;
	
};

