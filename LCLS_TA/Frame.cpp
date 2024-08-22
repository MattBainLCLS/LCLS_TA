#include "Frame.h"


Frame::Frame(arma::Mat<double> image)
{
    //myimage = image;
    //int length = image.n_rows;
    //int length = image.n_cols;
    length = image.n_cols;

    //arma::uvec pumpOffIndices = arma::conv_to<arma::uvec>::from(arma::linspace(0, length-2, length / 2));
    pumpOffIndices = arma::conv_to<arma::uvec>::from(arma::linspace(0, length-2, length / 2));
    pumpOnIndices = pumpOffIndices + 1;
    //arma::uvec pumpOnIndices = pumpOffIndices + 1;
    
    //test = image.cols(pumpOffIndices);

    pumpOff = Spectrum(image.cols(pumpOffIndices));
    //pumpOn = Spectrum(image.cols(pumpOnIndices));
    //transientAbsorption = Spectrum(arma::log10(image.rows(pumpOffIndices) / image.rows(pumpOnIndices)));


}

arma::vec* Frame::pumpOffIntensities()
{
    return pumpOff.getIntensities();
}

Frame::~Frame()
{

}