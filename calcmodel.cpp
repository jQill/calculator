#include "calcmodel.h"

CalcModel::CalcModel(QObject *parent)
    : QObject(parent), m_res(""), m_exp(""), m_type(false), m_error(-1)
{
    connect(this, &CalcModel::typeChanged, this, &CalcModel::recalculate);
    connect(this, &CalcModel::expChanged, this, &CalcModel::recalculate);
}

QString CalcModel::res() const { return m_res; }
QString CalcModel::exp() const { return m_exp; }
bool CalcModel::type() const { return m_type; }
int CalcModel::error() const { return m_error; }

void CalcModel::setExp(QString exp)
{
    if (m_exp == exp) return;

    m_exp = exp;
    emit expChanged(m_exp);
}

void CalcModel::setType(bool type)
{
    if (m_type == type) return;

    m_type = type;
    emit typeChanged(m_type);
}

void CalcModel::recalculate()
{
    if (m_exp == "") return;

    string str = m_exp.toStdString();
    std::pair<int, string> res = m_type ?
                call_calculator<double>(str) :
                call_calculator<rational>(str);
    m_res = m_type ? erase_extra_zeroes(res.second).c_str() :
                    res.second.c_str();
    m_error = res.first;
    emit resChanged(m_res);
    emit errorChanged(m_error);
}



