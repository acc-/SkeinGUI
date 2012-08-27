#ifndef CSV_H
#define CSV_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QStringList>


// a class to handle skeinforge's .csv files
class CSV
{
public:
   ~CSV() {
        data.clear();
    }

    CSV()  {
    }

    void static setSkeinforgeDir(QString dir) {
        skeinforgeDir = dir;

    }
    void setFilename(QString filename) {
        this->filename = filename;
    }

    void load(QString module);
    void load();
    void save();

    void dumpData();

    QString get(QString key);
    void set(QString key, QString value);

    QString getModule() {
        return module;}

public:
    QList<QStringList> data;

private:
    QString module, filename;
    static QString skeinforgeDir;

    QString makeKey(QString val);
};

#endif // CSV_H
