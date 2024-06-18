#include "SampleComplex.h"
#include <utility>
#include <fstream>
#include <boost/mpl/vector/aux_/size.hpp>


SampleComplex::SampleComplex(int sizeX, int sizeY, std::vector<std::complex<double>> data)
{
    m_size_x = sizeX;
    m_size_y = sizeY;
    m_data = std::move(data);
}

SampleComplex::SampleComplex(int size) : Sample<std::complex<double>>(size, size)
{
    m_size_x = size;
    m_size_y = size;

}
//конструктор от sample
SampleComplex::SampleComplex(Sample &sample)
{
    this->m_size_x = sample.GetSizeX();
    this->m_size_y = sample.GetSizeY();
    this->m_data = sample.m_data;
}
//модуль
void SampleComplex::Modulus()
{
    for (int i = 0; i < m_data.size(); i++)
    {
        modulus.emplace_back(abs(m_data[i]));
    }
}
//фаза
void SampleComplex::Phase()
{
    for (int i = 0; i < m_data.size(); i++)
    {
        phase.emplace_back(arg(m_data[i]));
    }
}
//интенсивность
void SampleComplex::Intense()
{
    for (int i = 0; i < m_data.size(); i++)
    {
        intense.emplace_back(norm(m_data[i]));
    }
}

SampleComplex SampleComplex::getIntense()
{
    std::vector<double> img(intense.size(), 0);
    std::vector<std::complex<double>> complex(intense.size());
    std::transform(intense.begin(), intense.end(), img.begin(), complex.begin(), [](double da, double db) {
        return std::complex<double>(da, db);
        });
    return SampleComplex(this->GetSizeX(), this->GetSizeY(), complex);
}

Sample<double> SampleComplex::getPhase()
{
    return Sample<double>(this->GetSizeX(), this->GetSizeY(), this->phase);
}

Sample<double> SampleComplex::getModulus()
{
    return Sample<double>(this->GetSizeX(), this->GetSizeY(), this->modulus);
}

//преобразование в sample
Sample<double> SampleComplex::toSample()
{
    Sample<double> res;
    res.m_size_x = this->m_size_x;
    res.m_size_y = this->m_size_y;
    res.m_data.resize(res.m_size_x * res.m_size_y);
    for (int i = 0; i < this->m_data.size(); i++)
    {
        res.m_data[i] = m_data[i].real();
    }
    return res;
}

//вывод в файл
void SampleComplex::Print(std::string filename)
{
    std::ofstream out;
    out.open(filename);
    for (int i = 0; i < m_size_x; i++)
    {
        for (int j = 0; j < m_size_y; j++)
        {
            out << m_data.at((i) * m_size_y + j).real() << "+" << m_data.at((i) * m_size_y + j).imag() << "i  ";
        }
        out << std::endl;
    }
    out.close();
}
//вещественную часть
void SampleComplex::printReal(std::string filename)
{
    std::ofstream out;
    out.open(filename);
    for (int i = 0; i < m_size_x; i++)
    {
        for (int j = 0; j < m_size_y; j++)
        {
            out << m_data.at((i) * m_size_y + j).real() << "  ";
        }
        out << std::endl;
    }
    out.close();
}
//мнимая часть
void SampleComplex::printIm(std::string filename)
{
    std::ofstream out;
    out.open(filename);
    for (int i = 0; i < m_size_x; i++)
    {
        for (int j = 0; j < m_size_y; j++)
        {
            out << m_data.at((i) * m_size_y + j).imag() << "  ";
        }
        out << std::endl;
    }
    out.close();
}
//модуля
void SampleComplex::printModulus(std::string filename)
{
    std::ofstream out;
    out.open(filename);
    this->Modulus();
    for (int i = 0; i < m_size_x; i++)
    {
        for (int j = 0; j < m_size_y; j++)
        {
            out << modulus.at((i) * m_size_y + j) << "  ";
        }
        out << std::endl;
    }
    out.close();
}
//фазы выборки
void SampleComplex::printPhase(std::string filename)
{
    std::ofstream out;
    out.open(filename);
    this->Phase();
    for (int i = 0; i < m_size_x; i++)
    {
        for (int j = 0; j < m_size_y; j++)
        {
            out << phase.at((i) * m_size_y + j) << "  ";
        }
        out << std::endl;
    }
    out.close();
}
//интенсивности выборки
void SampleComplex::printIntense(std::string filename)
{
    std::ofstream out;
    out.open(filename);
    this->Intense();
    for (int i = 0; i < m_size_x; i++)
    {
        for (int j = 0; j < m_size_y; j++)
        {
            out << intense.at((i) * m_size_y + j) << "  ";
        }
        out << std::endl;
    }
    out.close();
}
