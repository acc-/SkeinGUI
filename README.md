# SkeinGUI

## What is it ?
SkeinGUI is a simple Skeinforge 50 frontend enabling user to set the most often used settings at one page, without using Skeinforge's awful GUI. User can enter commonly used values, click to slice STL file, and when it's ready - click to view generated g-code with Skeinlayer.

Be warned - it's not meant to replace Skeinforge, Slic3r, Cura etc... it's just a simple Skeinforge frontend allowing you to use your favourite and the only Skeinforge.

The tool was born because of pypy... not running TkInter under Windows :-) This way Windows users can use pypy to slice and python to run skeinlayer - G-Code viewer.

Yhm, you don't know pypy? You better do, if you use Skeinforge :)


## Who can use it ?
It's not for beginners. It's for people willing to know *what* and *how*. If you are familiar with Skeinforge settings, but it's TkInter GUI makes you sick - probably this is the tool you may want to try.


## What is needed to run?
* Supported OS. Currently SkeinGUI provides binaries for Linux and Windows. However full source codes are included, so you probably can build it on Mac without any hassle.

* Skeinforge 50 (newest at the moment of writing these words). SkeinGUI automatically recognizes Skeinforge's configuration files location ($HOME/.skeinforge)

* QT 4 - SkeinGUI is being developed using QT Creator, a free portable C++ IDE. So you surely need it to launch SkeinGUI. The binaries are built using QT 4.8.1 (Ubuntu Linux) and 4.8.2 (Linux cross-compiling for Windows).


## How to install?
There is no installer right now. You can either use binaries or build your own from soources.

## How to link SkeinGUI with Skeinforge?
You do it by entering two commands - one for slicing and next one for viewing g-codes (skeinlayer). SkeinGUI launches them by appending filename at the end.

* For slicing, you should set the path to `skeinforge_utilities/skeinforge_craft.pyfile`. Better launch it via some terminal, I use `xterm -hold` (Linux) or `cmd /k` (Windows) to have the window open once it finishes (to see if there were any problems).

My setting are:

for Linux:
```
xterm -hold -e pypy /home/acc/3d/skeinforge_application/skeinforge_utilities/skeinforge_craft.py
```
for Windows:
```
cmd /k pypy h:/3d/skeinforge_application/skeinforge_utilities/skeinforge_craft.py
```

* For skeinlayer you should point to `analyze_plugins/skeinlayer.py`.

My setting are:

for Linux:
```
xterm -e pypy  /home/acc/3d/skeinforge_application/skeinforge_plugins/analyze_plugins/skeinlayer.py
```

for windows:
```
cmd /c python  h:/home/acc/3d/skeinforge_application/skeinforge_plugins/analyze_plugins/skeinlayer.py
```


## What settings can I set?
Well - the answer is simple, the ones I've ever used with Skeinforge. Probably you're setting most of them. Perhaps you can use even more. But - for the initial release the settings set is the one I use. Of course if you wish you can always ask for more :)

Current settings are:

![SkeinGUI 1.0 main screen](http://img155.imageshack.us/img155/75/skeingui10.png)


## Whoa! Import/Export?
Yep :) You can save your settings in one single file.
Note - this saves only the settings visible on screen.


## What are speed settings and how does it relate to Skeinforge?
While using Skeinforge with stepper motors, I always set Flow Rate the same as Feed Rate. Therefore in SkeinGUI there is only one setting called Speed. So it's quite an important assumption - Flow Rate = Feed Rate.

While reading Skeinforge configuration, it takes Feed Rate.
While writing - it updates both of them.

All the settings (excep Single Wall Width) are exactly the same as entered via Skeinforge. It's a simple 1:1 copy :-) Single Wall Width is the only exception. See assumptions below.

## What are the assumptions?
* Skeinforge's profile used is always Extrusion/ABS
* Single wall width divied by Layer height is entered as both Carve/Edge Width over Height and Infill/Infill Width over Thickness
* Feed=Flow for printing speed
* others I don't remember...? :-)

## Global SkeinGUI config file
SkeinGUI has it's own configuration file managed by QT. It is $HOME/.config/SkeinGUI.conf under Linux or somewhere in the registry under Windows.

SkeinGUI remembers craft and skeinlayer commands and last directory used for opening STL files.
The configuration is saved automatically when quitting the application.

## Can I help?
Sure! Go ahead and fork SkeinGUI :-) You contact also me directly by emailing to my gmail.com account - adam[dot]czysciak (smart anti spam)

## What is the license ?
In progress... for now it's free, you can use it at your own risk :) Feel free to fork and modify.
