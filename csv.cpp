#include "csv.h"

using namespace std;
#include <iostream>

#include <QFile>
#include <QTextStream>

QString CSV::skeinforgeDir = "";




// load skeinforge settings
void CSV::load(QString module) {
    this->module = module;
    this->filename = skeinforgeDir + "/profiles/extrusion/ABS/" + module;

    load();
}


void CSV::load() {
    cout << "Reading settings from " << filename.toStdString();
    QFile file(filename);

    data.clear(); // in case of reloading

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();

            if (line.indexOf('\t') < 0) {
                QStringList l(line);
                data.append(l);
            } else {
                QStringList vals = line.split("\t");
                data.append(vals);
            }
            cout << '.';
        }
        file.close();
        cout << endl;
    } else
        cerr << "Cannot open file '" <<file.fileName().toStdString() << "' for reading" << endl;
}



// save settings
void CSV::save() {
    cout << "Writing settings to " << filename.toStdString();

    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for (int i=0; i<data.size(); i++) {
            QStringList vals = data[i];

            for (int j=0; j<vals.size(); j++) {
                out << vals.at(j);
                if (j < vals.size()-1)
                    out << '\t';
            }
            out << endl;
            cout << '.';
        }
        file.close();
        cout << endl;
    } else
        cerr << "Cannot open file '" << file.fileName().toStdString() << "' for writing" << endl;

}


// helper method to generate C++ constant key name (like KEY_CARVE_LAYERS_TO_INDEX)
QString CSV::makeKey(QString val) {
    QString tmp;
    QChar lastChar('_');

    for (int i=0; i<val.size(); i++) {
        QChar ch = val.at(i).toUpper();
        if (ch == ' ')
            ch = '_';
        if (!ch.isLetter() && !ch.isDigit() && ch != '_')
            continue;
        if ((ch == '_') && (ch == lastChar))
            continue;
        lastChar = ch;
        tmp.append(ch);
    }

    return QString("KEY_" + module.toUpper().replace(".CSV","")+"_"+tmp);
}


// dump data to console
void CSV::dumpData() {
    for (int i=0; i<data.size(); i++) {
        QStringList l = data.at(i);
        // display c++ const or dump values
        if (true) {
            cout << "const QString " << makeKey(l[0]).toStdString() << "(\"" << l[0].toStdString() << "\");";
        } else {
            cout << "Key: [" << l[0].toStdString() << "]";
            if (l.size() > 1)
                cout << ", value: [" << l[1].toStdString() << "]";
        }

        cout << endl;
    }

    cout << endl;
}


// retrieve setting
QString CSV::get(QString key) {
    for (int i=0; i<data.size(); i++) {
        QStringList l = data.at(i);
        if (key == l[0]) {
            if (l.size() > 1)
                return l[1];
            else
                return NULL;
        }
    }
    return NULL;
}


// store setting
void CSV::set(QString key, QString value) {
    for (int i=0; i<data.size(); i++) {
        QStringList l = data[i];
        if (key == l[0]) {
            l.replace(1, value);
            data.replace(i, l);
            return;
        }
    }

    // key not found, make a new one
    QStringList l;
    l.append(key);
    l.append(value);

    data.append(l);
}
