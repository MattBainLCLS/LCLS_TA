#pragma once


#include <vector>
#include <armadillo>
#include <QtCore>


class Spectrum
{

public:
	Spectrum();
	Spectrum(arma::Mat<double> data);
	arma::vec* getIntensities();
	~Spectrum();

private:
	arma::vec intensities;
	arma::vec variance;

};

