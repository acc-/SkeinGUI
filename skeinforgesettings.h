#ifndef SKEINFORGESETTINGS_H
#define SKEINFORGESETTINGS_H

#include <QString>

const QString KEY_SETTINGS_SKEINFORGE_DIR = "SkeinforgeDir";
const QString KEY_SETTINGS_SKEINFORGE_COMMAND = "SkeinforgeCommand";

const QString KEY_SETTINGS_LAST_STL_DIR = "LastSTLFilesDirectory";

const QString KEY_UI_SINGLE_WALL_WIDTH = "ui.Single Wall Width";


const QString KEY_CARVE_ADD_LAYER_TEMPLATE_TO_SVG("Add Layer Template to SVG");
const QString KEY_CARVE_EDGE_WIDTH_OVER_HEIGHT_RATIO("Edge Width over Height (ratio):");
const QString KEY_CARVE_EXTRA_DECIMAL_PLACES_FLOAT("Extra Decimal Places (float):");
const QString KEY_CARVE_IMPORT_COARSENESS_RATIO("Import Coarseness (ratio):");
const QString KEY_CARVE_LAYER_HEIGHT_MM("Layer Height (mm):");
const QString KEY_CARVE_LAYERS_FROM_INDEX("Layers From (index):");
const QString KEY_CARVE_LAYERS_TO_INDEX("Layers To (index):");
const QString KEY_CARVE_CORRECT_MESH("Correct Mesh");
const QString KEY_CARVE_UNPROVEN_MESH("Unproven Mesh");
const QString KEY_CARVE_SVG_VIEWER("SVG Viewer:");

const QString KEY_DIMENSION_ACTIVATE_DIMENSION("Activate Dimension");
const QString KEY_DIMENSION_ABSOLUTE_EXTRUSION_DISTANCE("Absolute Extrusion Distance");
const QString KEY_DIMENSION_RELATIVE_EXTRUSION_DISTANCE("Relative Extrusion Distance");
const QString KEY_DIMENSION_EXTRUDER_RETRACTION_SPEED_MMS("Extruder Retraction Speed (mm/s):");
const QString KEY_DIMENSION_FILAMENT_DIAMETER_MM("Filament Diameter (mm):");
const QString KEY_DIMENSION_FILAMENT_PACKING_DENSITY_RATIO("Filament Packing Density (ratio):");
const QString KEY_DIMENSION_MAXIMUM_E_VALUE_BEFORE_RESET_FLOAT("Maximum E Value before Reset (float):");
const QString KEY_DIMENSION_MINIMUM_TRAVEL_FOR_RETRACTION_MILLIMETERS("Minimum Travel for Retraction (millimeters):");
const QString KEY_DIMENSION_RETRACT_WITHIN_ISLAND("Retract Within Island");
const QString KEY_DIMENSION_RETRACTION_DISTANCE_MILLIMETERS("Retraction Distance (millimeters):");
const QString KEY_DIMENSION_RESTART_EXTRA_DISTANCE_MILLIMETERS("Restart Extra Distance (millimeters):");

const QString KEY_FILL_ACTIVATE_FILL("Activate Fill");
const QString KEY_FILL_DIAPHRAGM_PERIOD_LAYERS("Diaphragm Period (layers):");
const QString KEY_FILL_DIAPHRAGM_THICKNESS_LAYERS("Diaphragm Thickness (layers):");
const QString KEY_FILL_EXTRA_SHELLS_ON_ALTERNATING_SOLID_LAYER_LAYERS("Extra Shells on Alternating Solid Layer (layers):");
const QString KEY_FILL_EXTRA_SHELLS_ON_BASE_LAYERS("Extra Shells on Base (layers):");
const QString KEY_FILL_EXTRA_SHELLS_ON_SPARSE_LAYER_LAYERS("Extra Shells on Sparse Layer (layers):");
const QString KEY_FILL_GRID_CIRCLE_SEPARATION_OVER_PERIMETER_WIDTH_RATIO("Grid Circle Separation over Perimeter Width (ratio):");
const QString KEY_FILL_GRID_EXTRA_OVERLAP_RATIO("Grid Extra Overlap (ratio):");
const QString KEY_FILL_GRID_JUNCTION_SEPARATION_BAND_HEIGHT_LAYERS("Grid Junction Separation Band Height (layers):");
const QString KEY_FILL_GRID_JUNCTION_SEPARATION_OVER_OCTOGON_RADIUS_AT_END_RATIO("Grid Junction Separation over Octogon Radius At End (ratio):");
const QString KEY_FILL_GRID_JUNCTION_SEPARATION_OVER_OCTOGON_RADIUS_AT_MIDDLE_RATIO("Grid Junction Separation over Octogon Radius At Middle (ratio):");
const QString KEY_FILL_INFILL_BEGIN_ROTATION_DEGREES("Infill Begin Rotation (degrees):");
const QString KEY_FILL_INFILL_BEGIN_ROTATION_REPEAT_LAYERS("Infill Begin Rotation Repeat (layers):");
const QString KEY_FILL_INFILL_ODD_LAYER_EXTRA_ROTATION_DEGREES("Infill Odd Layer Extra Rotation (degrees):");
const QString KEY_FILL_GRID_CIRCULAR("Grid Circular");
const QString KEY_FILL_GRID_HEXAGONAL("Grid Hexagonal");
const QString KEY_FILL_GRID_RECTANGULAR("Grid Rectangular");
const QString KEY_FILL_LINE("Line");
const QString KEY_FILL_INFILL_PERIMETER_OVERLAP_RATIO("Infill Perimeter Overlap (ratio):");
const QString KEY_FILL_INFILL_SOLIDITY_RATIO("Infill Solidity (ratio):");
const QString KEY_FILL_SHARPEST_ANGLE_DEGREES("Sharpest Angle (degrees):");
const QString KEY_FILL_SOLID_SURFACE_THICKNESS_LAYERS("Solid Surface Thickness (layers):");
const QString KEY_FILL_LOWER_LEFT("Lower Left");
const QString KEY_FILL_NEAREST("Nearest");
const QString KEY_FILL_SURROUNDING_ANGLE_DEGREES("Surrounding Angle (degrees):");
const QString KEY_FILL_INFILL__LOOPS__PERIMETER("Infill > Loops > Perimeter");
const QString KEY_FILL_INFILL__PERIMETER__LOOPS("Infill > Perimeter > Loops");
const QString KEY_FILL_LOOPS__INFILL__PERIMETER("Loops > Infill > Perimeter");
const QString KEY_FILL_LOOPS__PERIMETER__INFILL("Loops > Perimeter > Infill");
const QString KEY_FILL_PERIMETER__INFILL__LOOPS("Perimeter > Infill > Loops");
const QString KEY_FILL_PERIMETER__LOOPS__INFILL("Perimeter > Loops > Infill");

const QString KEY_INSET_OPEN_FILE_FOR_INSET("Open File for Inset");
const QString KEY_INSET_ADD_CUSTOM_CODE_FOR_TEMPERATURE_READING("Add Custom Code for Temperature Reading");
const QString KEY_INSET_INFILL_IN_DIRECTION_OF_BRIDGE("Infill in Direction of Bridge");
const QString KEY_INSET_INFILL_WIDTH_OVER_THICKNESS_RATIO("Infill Width over Thickness (ratio):");
const QString KEY_INSET_ASCENDING_AREA("Ascending Area");
const QString KEY_INSET_DESCENDING_AREA("Descending Area");
const QString KEY_INSET_OVERLAP_REMOVAL_WIDTH_OVER_PERIMETER_WIDTH_RATIO("Overlap Removal Width over Perimeter Width (ratio):");
const QString KEY_INSET_TURN_EXTRUDER_HEATER_OFF_AT_SHUT_DOWN("Turn Extruder Heater Off at Shut Down");
const QString KEY_INSET_VOLUME_FRACTION_RATIO("Volume Fraction (ratio):");

const QString KEY_SKIRT_ACTIVATE_SKIRT("Activate Skirt");
const QString KEY_SKIRT_CONVEX("Convex:");
const QString KEY_SKIRT_GAP_OVER_PERIMETER_WIDTH_RATIO("Gap over Perimeter Width (ratio):");
const QString KEY_SKIRT_LAYERS_TO_INDEX("Layers To (index):");
const QString KEY_SKIRT_BRIM_WIDTH("Brim Width:");

const QString KEY_SPEED_ACTIVATE_SPEED("Activate Speed");
const QString KEY_SPEED_ADD_FLOW_RATE("Add Flow Rate:");
const QString KEY_SPEED_BRIDGE_FEED_RATE_MULTIPLIER_RATIO("Bridge Feed Rate Multiplier (ratio):");
const QString KEY_SPEED_BRIDGE_FLOW_RATE_MULTIPLIER_RATIO("Bridge Flow Rate Multiplier (ratio):");
const QString KEY_SPEED_DUTY_CYLE_AT_BEGINNING_PORTION("Duty Cyle at Beginning (portion):");
const QString KEY_SPEED_DUTY_CYLE_AT_ENDING_PORTION("Duty Cyle at Ending (portion):");
const QString KEY_SPEED_FEED_RATE_MMS("Feed Rate (mm/s):");
const QString KEY_SPEED_FLOW_RATE_SETTING_FLOAT("Flow Rate Setting (float):");
const QString KEY_SPEED_OBJECT_FIRST_LAYER_FEED_RATE_INFILL_MULTIPLIER_RATIO("Object First Layer Feed Rate Infill Multiplier (ratio):");
const QString KEY_SPEED_OBJECT_FIRST_LAYER_FEED_RATE_PERIMETER_MULTIPLIER_RATIO("Object First Layer Feed Rate Perimeter Multiplier (ratio):");
const QString KEY_SPEED_OBJECT_FIRST_LAYER_FLOW_RATE_INFILL_MULTIPLIER_RATIO("Object First Layer Flow Rate Infill Multiplier (ratio):");
const QString KEY_SPEED_OBJECT_FIRST_LAYER_FLOW_RATE_PERIMETER_MULTIPLIER_RATIO("Object First Layer Flow Rate Perimeter Multiplier (ratio):");
const QString KEY_SPEED_ORBITAL_FEED_RATE_OVER_OPERATING_FEED_RATE_RATIO("Orbital Feed Rate over Operating Feed Rate (ratio):");
const QString KEY_SPEED_MAXIMUM_Z_FEED_RATE_MMS("Maximum Z Feed Rate (mm/s):");
const QString KEY_SPEED_PERIMETER_FEED_RATE_MULTIPLIER_RATIO("Perimeter Feed Rate Multiplier (ratio):");
const QString KEY_SPEED_PERIMETER_FLOW_RATE_MULTIPLIER_RATIO("Perimeter Flow Rate Multiplier (ratio):");
const QString KEY_SPEED_TRAVEL_FEED_RATE_MMS("Travel Feed Rate (mm/s):");


const QString KEY_MULTIPLY_ACTIVATE_MULTIPLY("Activate Multiply");
const QString KEY_MULTIPLY_CENTER_X_MM("Center X (mm):");
const QString KEY_MULTIPLY_CENTER_Y_MM("Center Y (mm):");
const QString KEY_MULTIPLY_NUMBER_OF_COLUMNS_INTEGER("Number of Columns (integer):");
const QString KEY_MULTIPLY_NUMBER_OF_ROWS_INTEGER("Number of Rows (integer):");
const QString KEY_MULTIPLY_REVERSE_SEQUENCE_EVERY_ODD_LAYER("Reverse Sequence every Odd Layer");
const QString KEY_MULTIPLY_SEPARATION_OVER_PERIMETER_WIDTH_RATIO("Separation over Perimeter Width (ratio):");

const QString KEY_CLIP_ACTIVATE_CLIP("Activate Clip");
const QString KEY_CLIP_CLIP_OVER_PERIMETER_WIDTH_RATIO("Clip Over Perimeter Width (ratio):");
const QString KEY_CLIP_MAXIMUM_CONNECTION_DISTANCE_OVER_PERIMETER_WIDTH_RATIO("Maximum Connection Distance Over Perimeter Width (ratio):");

const QString KEY_JITTER_ACTIVATE_JITTER("Activate Jitter");
const QString KEY_JITTER_JITTER_OVER_PERIMETER_WIDTH_RATIO("Jitter Over Perimeter Width (ratio):");

const QString KEY_STRETCH_ACTIVATE_STRETCH("Activate Stretch");
const QString KEY_STRETCH_CROSS_LIMIT_DISTANCE_OVER_PERIMETER_WIDTH_RATIO("Cross Limit Distance Over Perimeter Width (ratio):");
const QString KEY_STRETCH_LOOP_STRETCH_OVER_PERIMETER_WIDTH_RATIO("Loop Stretch Over Perimeter Width (ratio):");
const QString KEY_STRETCH_PATH_STRETCH_OVER_PERIMETER_WIDTH_RATIO("Path Stretch Over Perimeter Width (ratio):");
const QString KEY_STRETCH_PERIMETER_INSIDE_STRETCH_OVER_PERIMETER_WIDTH_RATIO("Perimeter Inside Stretch Over Perimeter Width (ratio):");
const QString KEY_STRETCH_PERIMETER_OUTSIDE_STRETCH_OVER_PERIMETER_WIDTH_RATIO("Perimeter Outside Stretch Over Perimeter Width (ratio):");
const QString KEY_STRETCH_STRETCH_FROM_DISTANCE_OVER_PERIMETER_WIDTH_RATIO("Stretch From Distance Over Perimeter Width (ratio):");

#endif // SKEINFORGESETTINGS_H

