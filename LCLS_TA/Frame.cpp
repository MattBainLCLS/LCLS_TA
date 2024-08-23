#include "Frame.h"


Frame::Frame(arma::Mat<double> image)
{

    length = image.n_cols;

    pumpOffIndices = arma::conv_to<arma::uvec>::from(arma::linspace(0, length-2, length / 2));
    pumpOnIndices = pumpOffIndices + 1;

    pumpOff = Spectrum(image.cols(pumpOffIndices));
    pumpOn = Spectrum(image.cols(pumpOnIndices));
    transientAbsorption = Spectrum(arma::log10(image.rows(pumpOffIndices) / image.rows(pumpOnIndices)));





}

arma::vec* Frame::pumpOffIntensities()
{
    return pumpOff.getIntensities();
}

arma::vec* Frame::pumpOnIntensities()
{
    return pumpOn.getIntensities();
}

arma::vec* Frame::transientAbsorptionIntensities()
{
    return transientAbsorption.getIntensities();
}

Frame::~Frame()
{

}