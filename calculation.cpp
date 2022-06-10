#include "calculation.h"

Calculation::Calculation(QObject *parent)
    : QObject{parent},
      m_inputValue{0},
      m_resultValue{1}
{

}

int Calculation::factorial(const int &n)
{
    return n ? (n * factorial(n-1) ) : 1;
}

int Calculation::getInputValue() const
{
    return m_inputValue;
}

int Calculation::getResultValue() const
{
    return m_resultValue;
}

void Calculation::setInputValue(const int &value)
{
     m_inputValue = value;
     m_resultValue = factorial(m_inputValue);

     emit inputValueChanged(m_inputValue);
     emit resultValueChanged(m_resultValue);
}

void Calculation::slotStart(int a)
{
    m_inputValue = a;
}
