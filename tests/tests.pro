# This file makes sure all tests get built
###############################################

TEMPLATE = subdirs
QMAKE_CXX = ccache g++

SUBDIRS = \
    unit_tests \
    integration_tests
