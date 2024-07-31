#include "Frame.h"

Frame::Frame()
{
    pumpOn = Spectrum(8192);
    pumpOff = Spectrum(8192);
    transientAbsorption = Spectrum(8192);
}

Frame::Frame(uint16_t* image)
{
    int length = 100;

    pumpOn = Spectrum(8192);
    pumpOff = Spectrum(8192);
    transientAbsorption = Spectrum(8192);

    double off;
    double on;

    for (int i = 0; i < 8192; i++) // Loop over frames (half number of loops
    {

        for (int j = 0; j < 100; j+=2)
        {
            off = image[i + j * 8192];
            on = image[i + (j + 1) * 8192];
            pumpOff.intensity[i] += off;
            pumpOn.intensity[i] += on;
            transientAbsorption.intensity[i] += (off / on); // Calculate -log later

        }

    }

}

Frame::~Frame()
{

}