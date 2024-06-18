#ifndef PSFCALC_H
#define PSFCALC_H

#include "SampleComplex.h"
#include "psfparam.h"

class PSFCalc
{
public:
    PSFCalc() = default;
    void PSF(PSFParam& prms, Sample<double>& PSF);
private:
    void pupilFunc(PSFParam& prms, SampleComplex& smpl);
    void shift(SampleComplex& smpl);
    void FFT(SampleComplex& smpl);
};

#endif // PSFCALC_H
