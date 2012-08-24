#ifndef SKEINGUI_H
#define SKEINGUI_H

#include <QMainWindow>
#include <QLineEdit>
#include <QCheckBox>

#include "csv.h"


namespace Ui {
class SkeinGUI;
}


class SettingItem {
public:
    QString key;

    CSV *csv;
    QLineEdit *line;
    QCheckBox *checkbox;

public:
    SettingItem(QString key, CSV *csv, QLineEdit *line) {
        this->key = key;
        this->csv = csv;
        this->line = line;
        this->checkbox = NULL;
    }

    SettingItem(QString key, CSV *csv, QCheckBox *checkbox) {
        this->key = key;
        this->csv = csv;
        this->checkbox = checkbox;
        this->line = NULL;
    }
};

class SkeinGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SkeinGUI(QWidget *parent = 0);
    ~SkeinGUI();
    void loadSettings();
    void saveSettings();

private slots:
    void on_selectAndLoadButton_clicked();
    void loadSkeinforgeSettings(QString dir);

    void on_saveButton_clicked();
    void on_sliceButton_clicked();
    void on_exportButton_clicked();

    void on_importButton_clicked();

private:
    Ui::SkeinGUI *ui;
    CSV settings;
    CSV carve, dimension, fill, inset, skirt, speed, multiply, clip, jitter, stretch;
    QList<SettingItem> uiItems;

    void s(QLineEdit* line, CSV* csv, QString key);
    void s(QCheckBox* cb, CSV* csv, QString key);

};

#endif // SKEINGUI_H
