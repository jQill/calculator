#ifndef CALCMODEL_H
#define CALCMODEL_H

#include <QString>
#include <QAbstractItemModel>
#include "computer.h"

class CalcModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString res READ res NOTIFY resChanged)
    Q_PROPERTY(QString exp READ exp WRITE setExp NOTIFY expChanged)
    Q_PROPERTY(bool type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int error READ error NOTIFY errorChanged)

public:
    explicit CalcModel(QObject *parent = nullptr);

    QString res() const;
    QString exp() const;
    bool type() const;
    int error() const;

public slots:
    void setExp(QString exp);
    void setType(bool type);
    void recalculate();

signals:
    void resChanged(QString res);
    void expChanged(QString exp);
    void typeChanged(bool type);
    void errorChanged(int error);

private:

    QString m_res;
    QString m_exp;
    bool m_type;
    int m_error;
};

#endif // CALCMODEL_H
