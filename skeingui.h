#ifndef SKEINGUI_H
#define SKEINGUI_H

#include <QMainWindow>
#include <QLineEdit>
#include <QCheckBox>
#include <QSettings>

#include "csv.h"


namespace Ui {
class SkeinGUI;
}



// object representing UI <-> Skeinforge setting, the main goal of this class is to automate loading and saving settings
// items are registered once, and then appropriate .csv keys and UI controls are linked together
class SettingItem {
public:
    QString key;
    QString key2;

    CSV *csv;
    QLineEdit *line;
    QCheckBox *checkbox;

public:
    SettingItem(QString key, QString key2, CSV *csv, QLineEdit *line) {
        this->key = key;
        this->key2 = key2;
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



// Main application class
class SkeinGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SkeinGUI(QWidget *parent = 0);
    ~SkeinGUI();


private slots:
    void loadAppSettings();
    void loadSkeinforgeSettings();

    void saveAppSettings();
    void saveSkeinforgeSettings();

    void on_sliceButton_clicked();
    void on_exportButton_clicked();
    void on_importButton_clicked();

    void on_skeinlayerButton_clicked();

private:
    Ui::SkeinGUI *ui;
    QSettings settings;

    CSV carve, dimension, fill, inset, skirt, speed, multiply, clip, jitter, stretch;
    QList<SettingItem> uiItems;

    // methods to register .csv <-> ui parameters link
    void s(QLineEdit* line, CSV* csv, QString key, QString key2="");
    void s(QCheckBox* cb, CSV* csv, QString key);

};

#endif // SKEINGUI_H
