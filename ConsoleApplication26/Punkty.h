#pragma once
#ifndef MY_HEADER_FILE_
#define MY_HEADER_FILE_
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <ctime> 
#include <chrono>
#include <fstream>


using namespace std;
struct point {
    char name;
    int x, y;
    vector <point> connections;
    bool operator == (const point& p) {
        if (p.x == x and p.y == y)
            return true;
        else
            return false;
    }
};

struct dpoint {
    point p;
    double dlugosc;
    char prev;
};

void writePointsToFile(const vector<point>& points, const string& filename);
vector<point> readPointsFromFile(const string& filename, int n);
bool PointInVec(point p, vector <point> vec);
double distance(point p1, point p2);
void findConnections(point* p, vector<point> tab);
point generatePoint(int start = 65, vector <point> used = {}, int radius = 0, point p = {}, int dir = 1, int xmin = -100, int xmax = 100, int ymin = -100, int ymax = 100);
void printPoint(point p);
void generateGroup(int start, int number, point p, int* dir, vector <point>* used, int xmin = -100, int xmax = 100, int ymin = -100, int ymax = 100);
vector <point> vecOfPoints(int quantity = 20, int xmin = -100, int xmax = 100, int ymin = -100, int ymax = 100);
dpoint* finddPoint(char name, vector<dpoint>& board);
void printdji(vector<dpoint> tab);
void djikstra(vector <point> points = {}, vector <dpoint>* path = {});

#endif