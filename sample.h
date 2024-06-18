//-----------------------------------------------------------------------
// 3-я (1 часть) лабораторная работа по дисциплине "Программирование на языках высокого уровня"
// Преподаватель: Иванова Т.В.
// Студент      : Симаков П.Е.
//
// 3nd (1 part) laboratory work on the discipline "Programming in high-level languages"
// Teacher      : Ivanova T.V.
// Student      : Simakov P.E.
//-----------------------------------------------------------------------


#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
//-------------------------------------------------------------------------------------------------
// базовый класс для выборки (квадратной или прямоугольной)
template <class PAR>
class Sample
{
    friend class SampleComplex;
protected:
    // число элементов выборки по x и y
    unsigned int m_size_x = 0, m_size_y = 0;
    // массив данных
    std::vector<PAR> m_data;
	
public:
    // конструктор
    Sample() = default;
    // деструктор
    ~Sample() = default;

    Sample(unsigned int size);
    Sample(unsigned int x, unsigned int y);
    Sample(unsigned int x, unsigned int y, std::vector<PAR> data);

    inline double CalcCoord(int i, double dx) const;
    // изменение размера для квадратной выборки
    inline void Resize(unsigned int size);
    // изменение размера для прямоугольной выборки
    inline void Resize(unsigned int size_x, unsigned int size_y);

    // размер выборки (для квадратной)
    inline unsigned int GetSize() const;
    // размер выборки по X и Y
    inline unsigned int GetSizeX() const;
    inline unsigned int GetSizeY() const;

    // оператор получения значения элемента с номером i,j
    inline PAR& operator()(unsigned int i,unsigned int j);
    // оператор получения const значения элемента с номером i,j
    inline const PAR& operator()(unsigned int i,unsigned int j) const;

    // проверка квадратная ли выборка
    inline bool IsSquare() const;
    // проверка что размер != 0
    inline bool IsZeroSize() const;
    // проверка равенства размеров с другой выборкой
    inline bool IsEqualSize(const Sample<PAR> &temp) const;

    // инициализация всех элементов выборки одинаковым значением
    void SetValue(PAR value);
    // получение указателя на всю выборку
    PAR* GetPointer();
    // вычисление максимального значения
    PAR GetMax() const;

    // операции с выборкой и числом
    // сложение всех элементов выборки и числа
    Sample<PAR>& operator+=(PAR value);
    // умножение всех элементов выборки на число
    Sample<PAR>& operator*=(PAR value);
    // деление всех элементов выборки на число
    Sample<PAR>& operator/=(PAR value);

    // операции с двумя выборками
    // присваивание
    Sample<PAR>& operator= (const Sample<PAR> &temp);
    // поэлементное сложение двух выборок
    Sample<PAR>& operator+=(const Sample<PAR> &temp);
    // поэлементное вычитание двух выборок
    Sample<PAR>& operator-=(const Sample<PAR>& temp);
    // поэлементное перемножение двух выборок
    Sample<PAR>& operator*=(const Sample<PAR> &temp);

    // вывод выборки в поток (файл или экран)
    std::ostream& Save(std::ostream& out);
    // перегрузка оператора чтения выборки из файла
    std::istream& Load(std::istream& out);

protected:
    // проверяет квадратная ли выборка, если нет - создает исключение
    void CheckSquare() const;
};

template<class PAR>
Sample<PAR>::Sample(unsigned int size)
    : m_size_x(size), m_size_y(size) 
{
    m_data.resize(size * size);
};

template<class PAR>
Sample<PAR>::Sample(unsigned int x, unsigned int y)
    : m_size_x(x), m_size_y(y) 
{
    m_data.resize(x * y);
};

template<class PAR>
Sample<PAR>::Sample(unsigned int x, unsigned int y, std::vector<PAR> data)
    : m_size_x(x), m_size_y(y), m_data(data) {};


template <class PAR>
double Sample<PAR>::CalcCoord(int i, double dx) const
{
    return (i - m_size_x / 2.) * dx;
};

template <class PAR>
void Sample<PAR>::Resize(unsigned int size)
{
    m_data.resize(size * size);
    m_size_x = size;
    m_size_y = size;
};

template<class PAR>
void Sample<PAR>::Resize(unsigned int size_x, unsigned int size_y)
{
    m_data.resize(size_x * size_y);
    m_size_x = size_x;
    m_size_y = size_y;
}

template<class PAR>
unsigned int Sample<PAR>::GetSize() const
{
    if (this->IsSquare())
    {
        return m_size_x;
    } else
    {
        throw "wrong method: non-square matrix";
    }
}

template<class PAR>
unsigned int Sample<PAR>::GetSizeX() const
{
    return m_size_x;
}

template<class PAR>
unsigned int Sample<PAR>::GetSizeY() const
{
    return m_size_y;
}

template<class PAR>
PAR& Sample<PAR>::operator()(unsigned int i, unsigned int j)
{
    if (i > this->m_size_x || j > this->m_size_y)
    {
        throw "Large number";
    }
    return m_data.at(i * m_size_y + j);
}

template<class PAR>
const PAR &Sample<PAR>::operator()(unsigned int i, unsigned int j) const
{
    if (i > m_size_x || j > m_size_y)
    {
        throw "Large number";
    }
    return m_data.at(i * m_size_y + j); // семантика копирования
}

template<class PAR>
bool Sample<PAR>::IsSquare() const
{
    return m_size_x == m_size_y;
}

template<class PAR>
bool Sample<PAR>::IsZeroSize() const
{
    return m_size_x == 0 || m_size_y == 0; // такое условие выбрал из-за названия функции
}

template<class PAR>
bool Sample<PAR>::IsEqualSize(const Sample<PAR> &temp) const
{
    return m_size_x == temp.m_size_x && m_size_y == temp.m_size_y;
}

template<class PAR>
void Sample<PAR>::SetValue(PAR value)
{
    m_data.assign(m_size_x * m_size_y, value);
}

template<class PAR>
PAR *Sample<PAR>::GetPointer()
{
    return m_data.data();
}

template<class PAR>
PAR Sample<PAR>::GetMax() const
{
    return *std::max_element(m_data.begin(), m_data.end());
}

template<class PAR>
Sample<PAR> &Sample<PAR>::operator+=(PAR value)
{
    for (auto &i: m_data)
    {
        i += value;
    }
    return *this;
}

template<class PAR>
Sample<PAR> &Sample<PAR>::operator*=(PAR value)
{
    for (auto &i: m_data)
    {
        i *= value;
    }
    return *this;
}

template<class PAR>
Sample<PAR> &Sample<PAR>::operator/=(PAR value)
{
    for (auto &i: m_data)
    {
        i /= value;
    }
    return *this;
}

template<class PAR>
Sample<PAR> &Sample<PAR>::operator=(const Sample<PAR> &temp)
{
    if (this->IsEqualSize(temp))
    {
        int size = m_data.size();
        for (int i = 0; i < size; i++)
        {
            this->m_data[i] = temp.m_data[i];
        }
        return *this;
    } else
    {
        throw "Wrong matrix size";
    }
}

template<class PAR>
Sample<PAR> &Sample<PAR>::operator+=(const Sample<PAR> &temp)
{
    if (this->IsEqualSize(temp))
    {
        int size = m_data.size();
        for (int i = 0; i < size; i++)
        {
            this->m_data[i] += temp.m_data[i];
        }
        return *this;
    } else
    {
        throw "Wrong matrix size";
    }
}

template<class PAR>
Sample<PAR> &Sample<PAR>::operator-=(const Sample<PAR> &temp)
{
    if (this->IsEqualSize(temp))
    {
        int size = m_data.size();
        for (int i = 0; i < size; i++)
        {
            this->m_data[i] -= temp.m_data[i];
        }
        return *this;
    } else
    {
        throw "Wrong matrix size";
    }
}

template<class PAR>
Sample<PAR> &Sample<PAR>::operator*=(const Sample<PAR> &temp)
{
    if (this->IsEqualSize(temp))
    {
        int size = m_data.size();
        for (int i = 0; i < size; i++)
        {
            this->m_data[i] *= temp.m_data[i];
        }
        return *this;
    } else
    {
        throw "Wrong matrix size";
    }
}

template<class PAR>
std::ostream &Sample<PAR>::Save(std::ostream &out)
{
    for (int i = 0; i < m_size_x; i++)
    {
        for (int j = 0; j < m_size_y; j++)
        {
            out << m_data.at((i) * m_size_y + j) << "  ";
        }
        out << std::endl;
    }
    return out;
}

template<class PAR>
std::istream &Sample<PAR>::Load(std::istream &out)
{
    PAR num;
    while (out >> num)
    {
        m_data.emplace_back(num);
    }
    return out;
}

template<class PAR>
void Sample<PAR>::CheckSquare() const
{
    if (m_size_x != m_size_y) throw "non square matrix";
}
//-------------------------------------------------------------------------------------------------
