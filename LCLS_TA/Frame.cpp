#include "Frame.h"


Frame::Frame(arma::Mat<double> image)
{

    //image.save("C:\\Users\\mattbain-a\\Data\\armadata.csv", arma::csv_ascii);
    length = image.n_cols; // Number of images

    pumpOffIndices = arma::conv_to<arma::uvec>::from(arma::linspace(0, length-2, length / 2)); // Number of image pump on and pump off
    pumpOnIndices = pumpOffIndices + 1;

    pumpOff = Spectrum(image.cols(pumpOffIndices));

    pumpOn = Spectrum(image.cols(pumpOnIndices));
    transientAbsorption = Spectrum(arma::log10(image.cols(pumpOffIndices) / image.cols(pumpOnIndices)));

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