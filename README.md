# ANGRY NERDS

Welcome to our game. This branch is for the Pc-Version. If you want to see the android version, please switch to the android branch. 
There are the apk versions which you can download directly for your phone as well as the necessary anroid packages

The game was built by Nico Harder, David Gastager, Jim Harder and Fatih Özdemir.


[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)


# Android Deployment with QT and Box2D
## Downloads
This procedure was done with Ubuntu 18.04 x86_64 Architecture  and QT Creator 5.15.0 and Samsung Galaxy A3 2017. The guide is subject to changes.
You may need about 20 GB disk space ( It can surely be done with less, just figure it out :) )


*  First, you need to install Qt Creator with all these packages (again, perhaps less packages may be needed )
 (If you already have Qt Creator, you can open the MaintenanceTool in the Qt Folder and add the following packages)

You can check your architecture with (which you may need to know for installation )
```bash
uname -a
``` 


First, update yourself and install the following necessary packages
```sh
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libstdc++6:i386 libgcc++6:i386 libgcc1:i386
libncurses5:i386 zlib1g:i386 libsdl1.2debian:i386 mesa-vulkan-drivers 
```
You will need Openjdk Version 8 (Java JDk for MacOs and Windows) and the newest [Android Studio](https://developer.android.com/studio/) and [Android NDK](https://developer.android.com/ndk/downloads)  
Note: Download Openjdk or Java JDK Version 8 and not newer, since the newer ones may cause building errors
For installing open JDK
```sh
sudo apt-get install openjdk-8-jdk
```
## Configurations
After downloading all the packages, open Android studio via terminal  ( in Downloads folder, not the installed folder)
```sh
cd Downloads/android-studio/bin
./studio.sh
```
After the installation, open configure and then open SDK Manager.
You will need the following packages

At the SDK Platform section , install at least one SDK Platform (e.g. android 10.0+) and the necessary system images (click at show Package details) if you want to use an emulator

At the SDK Tools section, install all the listed packages
![a](/uploads/c43687852cada2008111934f6ccbb807/3e9ac3e4-5c3e-4eb3-a24c-1bd44697bd14.jpg)
#### At Qt
Now we will set up our Android environment in Qt
Open the options in Qt Creator and go to the device settings 
You need to set up the Locations for Android
This is how I have set up the NDK , SDK and JDK locations .You also need to add the NDK after the JDK
![a](/uploads/be5c2845555db5e3c5489797e06079b3/3c2c33d1-64a1-4f4a-bfc6-1eb804dea53e.jpg)
Then install the AndroidOpenSSL settings just bit clicking at the download button

You may get some errors here, but you can solve them easily by looking them up
## Deploy apps
If everything until so far, you can already deploy android apps to your devices.
I am using my own android device (Samsung galaxy a7 with android 8) because emulators (which you can create with the AVD Manager at either android studio  qtcreator) may cause problems.


If you want to test it, just  go to  your 
```sh Qt/Examples/[your newest qt version]/quick/particles/emitters ```

And open the .pro file with Qt Creator
I referred to the [emitter](https://doc.qt.io/qt-5/qtquick-particles-emitters-example.html) example
Plug in your device, select the Arduino Kit and make sure that you are in Developer Mode (click at build-number in the settings several times) and have enabled USB Debugging Options 

## Box2D Integration 
For Box2d Integration in Qt, I refer to the following [video](https://www.youtube.com/watch?v=vg4BQoPuEUI):
1. Download from Box2D
2. Creating a library project in Qt (Type: Statlically Linked Library)
3. Delete the .h and .cpp file in Qt
4. Copy the folders include/box2d, src/collision, src/common, src/dynamic and src/rope (from Box2D download) into the library directory
5. Qt: Right click on the library project -> "Add existing directory" -> add folder from 4. except the file box2d/box2d.h
6. execute the .pro file
7. Then  follow the rest of the video for testing or create your own project

Note: Since we want to create an Android app, we are going to choose the android Kit additionally at around 04:00 of the video.
We take the static library (the .a file ) from the release folder of the project after having build it, and then we integrate it in our project 

# Layout and Design
If you want to add features such as an app name, a protecting keystore etc, then follow the instructions from 14:00 onwards from this [video](https://www.youtube.com/watch?v=w2RRgRGHsDA&t=141s)
But by creating an android template, don't include the gradle directory into your qt project. This may cause deployment errors



subscribe, hit the like button and we see us next time!
