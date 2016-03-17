# Workstation: Readme

## Dependencies
Make sure you have these installed when trying the commands below.
* Qt (version 5.2 or higher)
* libqtwebkit
* Doxygen (for the documentation)

On an Ubuntu machine, these can be installed using the following commands:
```
sudo apt-get install qt5-default qttools5-dev-tools libqt5webkit5 doxygen
```

Additionally, OpenCV needs to be installed and build correctly so that it can be used in combination with Qt:
```
# install dependencies
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev v4l-utils

mkdir OpenCV3
cd OpenCV3
wget https://github.com/Itseez/opencv/archive/3.0.0.zip
unzip 3.0.0.zip
cd opencv-3.0.0
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
make -j 4
sudo make install
sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
```


## How to get started
First of all, you will need the following commands:
```bash
git clone "git@github.ugent.be:shae/workstation"
cd workstation
qmake
```

After this, you have several possibilities:
* Build and execute the binary using
  ```bash
  make release && ./bin/release/frontend
  ```
* If you're interested in the debug version, use the following instead:
  ```bash
  make debug && ./bin/debug/frontend
  ```
* To run all unit tests
  ```bash
  make && ./tests/frontend_unit_tests
  ```
* To create the documentation
  ```bash
  doxygen Doxyfile
  ```

