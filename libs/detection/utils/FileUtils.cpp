//
// Created by lars on 2/25/16.
//

#include "FileUtils.h"

using namespace std;

/*! \file utility functions to read or parse files from disk

*/

/*!
	\brief compare strings to order them
	This is a helper function to sort the filenames (or strings).

*/
bool compareNoCase(string first, string second)
{
	int i = 0;
	while ((i < first.length()) && (i < second.length())) {
		if (tolower(first[i]) < tolower(second[i])) return true;
		else if (tolower(first[i]) > tolower(second[i])) return false;
		i++;
	}

	if (first.length() < second.length()) return true;
	else return false;
}

/*!
	\brief returns the filenames with a given extension in a given directory
	This is a function that returns a sorted list of filenames, given their extension and a directory.

*/
vector<string> listFiles(string path, string extension)
{
	/*The vector to return*/
	vector<string> files;
	DIR *pDIR;
	struct dirent *entry;
	/*Open the directory*/
	if (pDIR = opendir(path.c_str())) {
		while (entry = readdir(pDIR)) {
			/*look if the filename matches,exclude the . and ..*/
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name + strlen(entry->d_name) - strlen(extension.c_str()), extension.c_str()) == 0) {
				if (path[strlen(path.c_str()) - 1] == '/')
					files.push_back(string(path) +  string(entry->d_name));
				else
					files.push_back(string(path) + string("/") + string(entry->d_name));
			}
		}
		/*close the direcory*/
		closedir(pDIR);
	}
	//sort the filenames based on their alphabetic order
	std::sort(files.begin(), files.end(), compareNoCase);

	/*return the vector with filenames*/
	return files;
}

/*!
	\brief parses INRIA dataset annotation text files
	This is a parser function that parses the INRIA annotation text files and returns a DetectionList, containing a
    DetectionList containg the ground truth.

*/
DetectionList parseINRIA(string path)
{
	DetectionList DL;
	string line, subline;
	int xCenter, yCenter, xBoxTop, yBoxTop, xBoxBottom, yBoxBottom;
	ifstream file(path);
	//INRIA annotations start at line 18 and continue with a multiple of 7
	int counter = 0;
	if (file.is_open()) {
		while (getline(file, line)) {
			counter++;
			if (counter >= 17) {
				//read center positions of detection
				//turns out to be not used
				if ((counter - 17) % 7 == 0) {
					std::size_t pos = line.find_last_of(":") + 2;
					subline = line.substr(pos);
					subline.erase(std::remove(subline.begin(), subline.end(), ' '), subline.end());

					std::istringstream iss(subline);
					char delimiterL, delimiterM, delimiterR;
					//format: (x , y)
					iss >> delimiterL >> xCenter >> delimiterM >> yCenter >> delimiterR;
				}
				//read boundary box of detection
				if ((counter - 18) % 7 == 0) {
					std::size_t pos = line.find_last_of(":") + 2;
					subline = line.substr(pos);
					subline.erase(std::remove(subline.begin(), subline.end(), ' '), subline.end());

					std::istringstream iss(subline);
					char delimiterL1, delimiterM1, delimiterR1, delimiterL2, delimiterM2, delimiterR2, delimiterMM;
					//format: (xtop,ytop) - (xbot,ybot)
					iss >> delimiterL1 >> xBoxTop >> delimiterM1 >> yBoxTop >> delimiterR1 >> delimiterMM >> delimiterL2 >> xBoxBottom >> delimiterM2 >> yBoxBottom >> delimiterR2;
					DL.addDetection(xBoxTop, yBoxTop, xBoxBottom - xBoxTop , yBoxBottom - yBoxTop, 0, cv::Scalar(0, 255, 0));
				}
			}
		}
		file.close();
		return DL;
	}
}

/*!
	\brief parses drone footage dataset annotation text files
	This is a parser function that parses the drone footage annotation text files and returns a DetectionList, containing a
    DetectionList containg the ground truth.

*/
vector<std::pair<int, DetectionList>> parseAnnotationFile(string path)
{
	vector<std::pair<int, DetectionList>> ground_truth;
	string line;
	ifstream file(path);
	char not_used;
	int frame_num, num_people;
	int x_top, y_top, x_bottom, y_bottom;
	if (file.is_open()) {
		while (getline(file, line)) {
			std::istringstream iss(line);
			iss >> frame_num >> not_used >> num_people;
			DetectionList detections;
			for (int i = 0; i < num_people; i++) {
				getline(file, line);
				std::istringstream iss(line);
				// format: (x_top, y_top), (x_bottom, y_bottom)
				iss >> not_used >> x_top >> not_used >> y_top >> not_used >> not_used >>
				    not_used >> x_bottom >> not_used >> y_bottom >> not_used;
				detections.addDetection(x_top, y_top, x_bottom - x_top, y_bottom - y_top, 0);
			}
			ground_truth.push_back(std::pair<int, DetectionList>(frame_num, detections));
		}
		file.close();
	}

	return ground_truth;
}








