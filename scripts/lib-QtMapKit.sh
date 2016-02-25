#!/bin/sh

git clone "git@github.com:uranusjr/QtMapKit.git"
cd QtMapKit
qmake && make && sudo make install
cd ..
rm -r QtMapKit

