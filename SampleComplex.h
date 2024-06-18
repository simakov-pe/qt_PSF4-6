#ifndef SAMPLECOMPLEX_H
#define SAMPLECOMPLEX_H
#include <complex>
#include "sample.h"
#include <fstream>



class SampleComplex: public Sample<std::complex<double>>
{
public:
    //полный конструктор
    SampleComplex(int sizeX, int sizeY, std::vector<std::complex<double>> data);
    SampleComplex(int size);
    //конструктор от sample
    explicit SampleComplex(Sample &sample);
    //модуль
    void Modulus();
    //фаза
    void Phase();
    //интенсивность
    void Intense();
    //геттеры
    SampleComplex getIntense();
    Sample<double> getPhase();
    Sample<double> getModulus();
    //преобразование в sample
    Sample<double> toSample();
    //вывод в файл
    void Print(std::string filename);
    //вещественную часть
    void printReal(std::string filename);
    //мнимая часть
    void printIm(std::string filename);
    //модуля
    void printModulus(std::string filename);
    //фазы выборки
    void printPhase(std::string filename);
    //интенсивности выборки
    void printIntense(std::string filename);
private:
    std::vector<double> modulus;
    std::vector<double> phase;
    std::vector<double> intense;
};



#endif //SAMPLECOMPLEX_H
