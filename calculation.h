#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>

class Calculation : public QObject
{
    Q_OBJECT
public:
    explicit Calculation(QObject *parent = nullptr);

public:
    Q_INVOKABLE int factorial(int const& n);
    int getInputValue() const;
    int getResultValue() const;
    void setInputValue(int const& value);

private:
    Q_PROPERTY(int input WRITE setInputValue
                         READ getInputValue
                         NOTIFY inputValueChanged
               )

    Q_PROPERTY(int result READ getResultValue
                          NOTIFY resultValueChanged
               )

    int m_inputValue;
    int m_resultValue;

signals:
    void inputValueChanged(int);
    void resultValueChanged(int);

    void signalStart();

public slots:
    void slotStart(int);


};

#endif // CALCULATION_H
