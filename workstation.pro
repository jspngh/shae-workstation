# Project properties
TEMPLATE = subdirs

SUBDIRS = \
          libs \
          src

# make sure the libraries are compiled befor compiling our app
src.depends += libs

