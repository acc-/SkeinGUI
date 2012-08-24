#ifndef CSV_H
#define CSV_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QStringList>

class CSV
{
public:
    CSV();
    ~CSV();
    QString getModule() { return module; }

    void loadSkeinforge(QString module);
    void load(QString module, QString dir);
    void save();
    void save(QString fname);
    void dumpData();

    QString get(QString key);
    void set(QString key, QString value);

    void setSkeinforgeDir(QString dir) { skeinforgeDir = dir; }

    QList<QStringList> data;

private:
    QString module, filename;
    static QString skeinforgeDir;

    QString makeKey(QString val);

};

#endif // CSV_H
