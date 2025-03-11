#pragma once

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING	

#include <iostream>
#include <iomanip>
#include <experimental/filesystem>
#include <string>
#include <set>
#include <thread>
#include <atomic>

#include <opencv2\opencv.hpp>

#include <windows.h>
#include <vfw.h>
#include <setupapi.h>
#include <devguid.h>

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib,"vfw32.lib")

using namespace std;
using namespace cv;