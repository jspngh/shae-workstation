# Project properties
TEMPLATE = subdirs

SUBDIRS += libs
SUBDIRS += src
SUBDIRS += tests

# make sure the libraries are compiled before compiling our app and the tests
src.depends += libs
tests += libs

# configure compiler to use c++11s
QMAKE_CXX = ccache g++
CONFIG += c++11


DISTFILES += ./coding-conventions.astylerc
