#!/bin/bash

astyle --options=coding-conventions.astylerc --recursive "./*.cpp" "./*.h"
find . -name "*.orig" -type f -delete
