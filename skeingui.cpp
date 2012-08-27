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
    ui(new Ui::SkeinGUI), settings("SkeinGUI")
{
    ui->setupUi(this);

    CSV::setSkeinforgeDir(QDir::homePath() + "/.skeinforge");
    loadAppSettings();
    loadSkeinforgeSettings();
}


SkeinGUI::~SkeinGUI()
{
    saveAppSettings();
    delete ui;
}



// helper functions to calculate single wall width
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




// helper functions to register UI 1:1 .csv <-> settings
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



// load app settings
void SkeinGUI::loadAppSettings() {
    ui->craftCommand->setText(settings.value(KEY_SETTINGS_CRAFT_COMMAND,"pypy PATH/TO/SKEINFORGE/skeinforge_utilities/skeinforge_craft.py").toString());
    ui->skeinlayerCommand->setText(settings.value(KEY_SETTINGS_SKEINLAYER_COMMAND,"python PATH/TO/SKEINFORGE/skeinforge_plugins/analyze_plugins/skeinlayer.py").toString());
}


// load skeinforge settings
void SkeinGUI::loadSkeinforgeSettings() {
    carve.load("carve.csv");
    dimension.load("dimension.csv");
    fill.load("fill.csv");
    inset.load("inset.csv");
    skirt.load("skirt.csv");
    speed.load("speed.csv");
    multiply.load("multiply.csv");
    clip.load("clip.csv");
    jitter.load("jitter.csv");
    stretch.load("stretch.csv");

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


// save SkeinGUI settings
void SkeinGUI::saveAppSettings() {
    settings.setValue(KEY_SETTINGS_CRAFT_COMMAND, ui->craftCommand->text());
    settings.setValue(KEY_SETTINGS_SKEINLAYER_COMMAND, ui->skeinlayerCommand->text());
    settings.sync();
}


// action on "push settings to skeinforge" button
// saves SkeinGUI settings and pushes data to skeinforge
void SkeinGUI::saveSkeinforgeSettings()
{
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

    // and save all these CVSs
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
}


// extract directory from full file path (working both on Windows and Unixes)
QString dirOf(QString filename) {
    int idx = filename.lastIndexOf('/');
    int i2 = filename.lastIndexOf('\\');

    if (i2 > idx)
        idx = i2;

    if (idx >= 0)
        return  filename.left(idx);
    else
        return "";
}



// slice stl
void SkeinGUI::on_sliceButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select STL file to slice", settings.value(KEY_SETTINGS_LAST_STL_DIR,"").toString(), "STL files (*.stl)");
    if (path.isNull())
        return;

    saveSkeinforgeSettings();
    settings.setValue(KEY_SETTINGS_LAST_STL_DIR, dirOf(path));

    QString cmd = ui->craftCommand->text() + " " + path;
    QProcess::startDetached(cmd);
}


// skeinlayer - view generated .gcode
void SkeinGUI::on_skeinlayerButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select gcode file to slice", settings.value(KEY_SETTINGS_LAST_STL_DIR,"").toString(), "G-code files (*.g *.gcode)");
    if (path.isNull())
        return;

    QString cmd = ui->skeinlayerCommand->text() + " " + path;

    QProcess::startDetached(cmd);
}


// export skeinforge settings (all the UI input fields)
void SkeinGUI::on_exportButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Select config file", ".", "SkeinGUI config files (*.sg)");

    if (path.isNull())
        return;

    if (path.endsWith(".sg") == false)
        path += ".sg";


    CSV exp;
    // take all registered .csv <-> ui settings
    for (int i=0; i<uiItems.size(); i++) {
        SettingItem item = uiItems[i];
        if (item.line != NULL)
            exp.set(item.csv->getModule()+"|"+item.key, item.line->text());
        else if (item.checkbox != NULL)
            exp.set(item.csv->getModule()+"|"+item.key, item.checkbox->isChecked() ? "True" : "False");

    }

    // and manually handled ones as well
    exp.set(KEY_UI_SINGLE_WALL_WIDTH, ui->singleWallWidth->text());
    exp.setFilename(path);
    exp.save();

    QMessageBox::information(this, "SkeinGUI", "Settings exported to " + path);
}



// import skeinforge settings (all the UI input fields)
void SkeinGUI::on_importButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select config file", ".", "SkeinGUI config files (*.sg)");

    if (path.isNull())
        return;

    CSV exp;

    exp.setFilename(path);
    exp.load();

    // load direct .csv <-> ui settings
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
    // and all the manually handled ones
    ui->singleWallWidth->setText(exp.get(KEY_UI_SINGLE_WALL_WIDTH));

    QMessageBox::information(this, "SkeinGUI", "Settings imported from " + path);
}

