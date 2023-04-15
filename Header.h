#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Hỗ trợ random
#include <ncurses.h> // Thư viện đồ hoạ cho Mac OS
#include <chrono> // Hỗ trợ sleep
#include <thread> // Hỗ trợ sleep

#define ppxy prevX, prevY, x, y
#define ippxy int prevX, int prevY, int x, int y
#define iPPXY int &prevX, int &prevY, int &x, int &y

#define heightS 19
#define widthS 79
#define heightM 39
#define widthM 79
#define heightB 39
#define widthB 159

#define passingHeightMenu 12

using namespace std;