//
// Created by lars on 2/25/16.
//

#ifndef DETECTION_FILEUTILS_H
#define DETECTION_FILEUTILS_H

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include "../detection/DetectionList.h"


using namespace std;
vector<string> listFiles(string path, string extension);
vector<std::pair<int, DetectionList>> parseAnnotationFile(string path);
DetectionList parseINRIA(string path);




#endif //DETECTION_FILEUTILS_H


