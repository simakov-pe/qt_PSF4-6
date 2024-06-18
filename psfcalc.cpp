#include "psfcalc.h"
#include <fftw3.h>

void PSFCalc::PSF(PSFParam& prms, Sample<double>& PSF)
{
	PSF.Resize(prms.Size);
	PSF.SetValue(0.);

	SampleComplex Pupil(prms.Size);

	pupilFunc(prms, Pupil);
	FFT(Pupil);

	Pupil *= std::complex<double>(prms.StepPupil / prms.StepOb, 0.);
	Pupil.Intense();
	Sample<double> pupil_double = Pupil.toSample();

	PSF = pupil_double;
	PSF *= (1 / (M_PI * M_PI));

}

void PSFCalc::pupilFunc(PSFParam& prms, SampleComplex& smpl)
{
	smpl.SetValue(0.);

	for (int j = 0; j < smpl.GetSize(); ++j) {
		double ro_y = smpl.CalcCoord(j, prms.StepPupil);

		for (int i = 0; i < smpl.GetSize(); ++i) {

			double ro_x = smpl.CalcCoord(i, prms.StepPupil);
			if (ro_x * ro_x + ro_y * ro_y <= 1) {
				double ro2 = ro_x * ro_x + ro_y * ro_y;
				double fi = 0;

				if (ro_y == 0) {
					if (ro_x >= 0) {
						fi = M_PI / 2;
					}
					else {
						fi = -M_PI / 2;
					}
				}
				else {
					if (ro_y >= 0) {
						fi = atan(ro_x / ro_y);
					}
					else {
						fi = M_PI + atan(ro_x / ro_y);
					}
				}

				double W = 2 * M_PI * (prms.C20 * (2 * ro2 - 1) + prms.C22 * ro2 * cos(2 * fi));
				smpl(i, j) = std::complex<double>(cos(W), sin(W));
			}
		}

	}
}

void PSFCalc::shift(SampleComplex &smpl)
{
    int size = smpl.GetSize();
    for(int j = 0; j < size; ++j)
    {
        for (int i = 0; i < size; ++i)
        {
            smpl(i,j) *= std::complex<double>(cos(-2.0 * M_PI / 2 * i), sin(-2.0 * M_PI / 2*i));
            smpl(i,j) *= std::complex<double>(cos(-2.0 * M_PI / 2 * j), sin(-2.0 * M_PI / 2*j));
        }
    }
}

void PSFCalc::FFT(SampleComplex &smpl)
{
	shift(smpl);

	fftw_plan oPlan = fftw_plan_dft_2d(smpl.GetSize(), smpl.GetSize(),
										(fftw_complex*)smpl.GetPointer(),
										(fftw_complex*)smpl.GetPointer(),
										FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(oPlan);
	fftw_destroy_plan(oPlan);

	std::complex<double> coeff(1. / sqrt(double(smpl.GetSize() * smpl.GetSize())), 0.);
	smpl *= coeff;

	shift(smpl);
}
