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

