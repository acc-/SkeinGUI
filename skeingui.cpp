using namespace std;
#include <iostream>

#include "skeingui.h"
#include "ui_skeingui.h"
#include "skeinforgesettings.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>


SkeinGUI::SkeinGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SkeinGUI)
{
    ui->setupUi(this);
    loadSettings();
}

SkeinGUI::~SkeinGUI()
{
    delete ui;
}


QString mul(QString v1, QString v2) {
    if (v1.isEmpty() || v2.isEmpty())
        return "";

    QString s;

    s.sprintf("%.2f", v1.toDouble()*v2.toDouble());
    return s;
}

QString div(QString v1, QString v2) {

    QString s;

    s.sprintf("%.2f", v1.toDouble() / v2.toDouble());
    return s;
}


void SkeinGUI::loadSettings() {
    settings.load("skeingui.ini", "./");
    ui->skeinforgeCommand->setText(settings.get(KEY_SETTINGS_SKEINFORGE_COMMAND));

    loadSkeinforgeSettings(settings.get(KEY_SETTINGS_SKEINFORGE_DIR));
}


void SkeinGUI::s(QLineEdit* line, CSV* csv, QString key) {
    line->setText(csv->get(key));

    SettingItem setting(key, csv, line);
    uiItems.append(setting);
}

void SkeinGUI::s(QCheckBox* cb, CSV* csv, QString key) {
    cb->setChecked("True" == csv->get(key));

    SettingItem setting(key, csv, cb);
    uiItems.append(setting);
}


void SkeinGUI::loadSkeinforgeSettings(QString dir) {
    ui->skeinforgeDir->setText(dir);
    settings.setSkeinforgeDir(dir);

    carve.loadSkeinforge("carve.csv");
    dimension.loadSkeinforge("dimension.csv");
    fill.loadSkeinforge("fill.csv");
    inset.loadSkeinforge("inset.csv");
    skirt.loadSkeinforge("skirt.csv");
    speed.loadSkeinforge("speed.csv");
    multiply.loadSkeinforge("multiply.csv");
    clip.loadSkeinforge("clip.csv");
    jitter.loadSkeinforge("jitter.csv");
    stretch.loadSkeinforge("stretch.csv");

    ui->layerHeight->setFocus();

    uiItems.clear();
    s(ui->layerHeight, &carve, KEY_CARVE_LAYER_HEIGHT_MM);
    s(ui->filamentDiameter, &dimension, KEY_DIMENSION_FILAMENT_DIAMETER_MM);
    ui->singleWallWidth->setText(mul(carve.get(KEY_CARVE_LAYER_HEIGHT_MM), carve.get(KEY_CARVE_EDGE_WIDTH_OVER_HEIGHT_RATIO)));
    s(ui->layersTo, &carve, KEY_CARVE_LAYERS_TO_INDEX);

    s(ui->infillSolidity, &fill, KEY_FILL_INFILL_SOLIDITY_RATIO);
    s(ui->infillPerimeterOverlap, &fill, KEY_FILL_INFILL_PERIMETER_OVERLAP_RATIO);
    s(ui->infillBeginRotation, &fill, KEY_FILL_INFILL_BEGIN_ROTATION_DEGREES);
    s(ui->extraShellsBase, &fill, KEY_FILL_EXTRA_SHELLS_ON_BASE_LAYERS);
    s(ui->extraShellsAlternating, &fill, KEY_FILL_EXTRA_SHELLS_ON_ALTERNATING_SOLID_LAYER_LAYERS);
    s(ui->extraShellsSparse, &fill, KEY_FILL_EXTRA_SHELLS_ON_SPARSE_LAYER_LAYERS);

    s(ui->skirtGap, &skirt, KEY_SKIRT_GAP_OVER_PERIMETER_WIDTH_RATIO);
    s(ui->convexSkirt, &skirt, KEY_SKIRT_CONVEX);
    s(ui->brimWidth, &skirt, KEY_SKIRT_BRIM_WIDTH);

    s(ui->clip, &clip, KEY_CLIP_ACTIVATE_CLIP);
    s(ui->clipOverPerimeter, &clip, KEY_CLIP_CLIP_OVER_PERIMETER_WIDTH_RATIO);

    s(ui->printingSpeed, &speed, KEY_SPEED_FEED_RATE_MMS);
    s(ui->travelSpeed, &speed, KEY_SPEED_TRAVEL_FEED_RATE_MMS);
    s(ui->perimetersSpeedRatio, &speed, KEY_SPEED_PERIMETER_FEED_RATE_MULTIPLIER_RATIO);
    s(ui->bridgesSpeedRatio, &speed, KEY_SPEED_BRIDGE_FEED_RATE_MULTIPLIER_RATIO);
    s(ui->firstLayerPerimeterSpeed, &speed, KEY_SPEED_OBJECT_FIRST_LAYER_FEED_RATE_PERIMETER_MULTIPLIER_RATIO);
    s(ui->firstLayerInfillSpeed, &speed, KEY_SPEED_OBJECT_FIRST_LAYER_FEED_RATE_INFILL_MULTIPLIER_RATIO);

    s(ui->retractionSpeed, &dimension, KEY_DIMENSION_EXTRUDER_RETRACTION_SPEED_MMS);
    s(ui->retractionDistance, &dimension, KEY_DIMENSION_RETRACTION_DISTANCE_MILLIMETERS);
    s(ui->retractionExtraDistance, &dimension, KEY_DIMENSION_RESTART_EXTRA_DISTANCE_MILLIMETERS);

    s(ui->jitter, &jitter, KEY_JITTER_ACTIVATE_JITTER);
    s(ui->jitterPerimeterWidth, &jitter, KEY_JITTER_JITTER_OVER_PERIMETER_WIDTH_RATIO);

    s(ui->stretch, &stretch, KEY_STRETCH_ACTIVATE_STRETCH);

    s(ui->multiplyColumns, &multiply, KEY_MULTIPLY_NUMBER_OF_COLUMNS_INTEGER);
    s(ui->multiplyRows, &multiply, KEY_MULTIPLY_NUMBER_OF_ROWS_INTEGER);
    s(ui->centerX, &multiply, KEY_MULTIPLY_CENTER_X_MM);
    s(ui->centerY, &multiply, KEY_MULTIPLY_CENTER_Y_MM);
}

// saves SkeinGUI settings
void SkeinGUI::saveSettings() {
    settings.set(KEY_SETTINGS_SKEINFORGE_DIR, ui->skeinforgeDir->text());
    settings.set(KEY_SETTINGS_SKEINFORGE_COMMAND, ui->skeinforgeCommand->text());

    settings.save();
}

void SkeinGUI::on_selectAndLoadButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Select .skeinforge directory", ui->skeinforgeDir->text());
    if (path.isNull())
        return;

    loadSkeinforgeSettings(path);
}


// action on "push settings to skeinforge" button
// saves SkeinGUI settings and pushes data to skeinforge
void SkeinGUI::on_saveButton_clicked()
{
    saveSettings();

    // dump UI settings to CSVs - these are direct ones
    for (int i=0; i<uiItems.size(); i++) {
        SettingItem item = uiItems[i];
        QString val = NULL;
        if (item.line != NULL)
            val = item.line->text();
        else if (item.checkbox != NULL)
            val = item.checkbox->isChecked() ? "True" : "False";

        item.csv->set(item.key, val);
    }

    // calculate other values
    QString wtRatio = div(ui->singleWallWidth->text(), ui->layerHeight->text());
    carve.set(KEY_CARVE_EDGE_WIDTH_OVER_HEIGHT_RATIO, wtRatio);
    inset.set(KEY_INSET_INFILL_WIDTH_OVER_THICKNESS_RATIO, wtRatio);

    // and save these CVSs
    carve.save();
    dimension.save();
    fill.save();
    inset.save();
    skirt.save();
    speed.save();
    multiply.save();
    clip.save();
    jitter.save();
    stretch.save();

    QMessageBox::information(this, "SkeinGUI", "Settings pushed to " + ui->skeinforgeDir->text());
}


void SkeinGUI::on_sliceButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select .STL file to slice", settings.get(KEY_SETTINGS_LAST_STL_DIR), "STL files (*.stl)");
    if (path.isNull())
        return;

    int idx = path.lastIndexOf('/');
    int i2 = path.lastIndexOf('\\');
    if (i2 > idx)
        idx = i2;

    if (idx >= 0) {
        QString stlPath = path.left(idx);
        settings.set(KEY_SETTINGS_LAST_STL_DIR, stlPath);
        settings.save();
    }

    QString cmd = ui->skeinforgeCommand->text() + " " + path;

    QProcess::startDetached(cmd);
}



void SkeinGUI::on_exportButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Select config file", ".", "SkeinGUI config files (*.sg)");

    if (path.isNull())
        return;

    CSV exp;
    for (int i=0; i<uiItems.size(); i++) {
        SettingItem item = uiItems[i];
        if (item.line != NULL)
            exp.set(item.csv->getModule()+"|"+item.key, item.line->text());
        else if (item.checkbox != NULL)
            exp.set(item.csv->getModule()+"|"+item.key, item.checkbox->isChecked() ? "True" : "False");

    }
    exp.set(KEY_UI_SINGLE_WALL_WIDTH, ui->singleWallWidth->text());

    exp.save(path);
    QMessageBox::information(this, "SkeinGUI", "Settings exported");
}


void SkeinGUI::on_importButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select config file", ".", "SkeinGUI config files (*.sg)");

    if (path.isNull())
        return;

    CSV exp;
    exp.load("", path);

    for (int i=0; i<exp.data.size(); i++) {
        QStringList vals = exp.data[i];
        QString key = vals[0];
        QString val = (vals.size() > 1) ? vals[1] : "";

        for (int j=0; j<uiItems.size(); j++) {
            SettingItem item = uiItems[j];
            if (item.csv->getModule()+"|"+item.key == key) {
                if (item.line != NULL)
                    item.line->setText(val);
                else if (item.checkbox != NULL)
                    item.checkbox->setChecked("True" == val);

                break;
            }
        }
    }
    ui->singleWallWidth->setText(exp.get(KEY_UI_SINGLE_WALL_WIDTH));
    QMessageBox::information(this, "SkeinGUI", "Settings imported, remember to push them to Skeinforge before slicing");
}
