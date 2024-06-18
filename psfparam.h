#ifndef PSFPARAM_H
#define PSFPARAM_H

#include <QMainWindow>

class PSFParam
{
public:
    // размер выборки
    int Size = 512;
    // шаг по предмету/изображению к.е.
    double StepOb = 0;
    // шаг по зрачку
    double StepPupil = 0;
    // коэф. астигматизма и расфокусировки
    double C22 = 0, C20 = 0;
    // охват зрачка
    double PupilD = 0;
    // длина волны
    double Lamda = 0;
    // апертура
    double Aperture = 0;
    // задняя апертура
    double Aperture_ = 0;
    // увеличение
    double V = 0;
    // шаг по предмету мкм
    double StepObMkm = 0;
    // шаг по изображению мкм
    double StepImMkm = 0;


    void Calc();
    PSFParam() = default;
};

#endif // PSFPARAM_H
