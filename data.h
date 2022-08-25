#ifndef DATA
#define DATA
#include"data.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool read_in(vector<vector<double> >& data, vector<int>& labels, string dataPath, string labelsPath);

bool split_data(vector< vector<vector<double> > >& data_sect, vector<vector<int> >& labels_sect, const vector<vector<double> >& data, const vector<int>& labels, const vector<double>& ratio);

bool split_data(vector<vector<double> >& data_sect, vector<int>& labels_sect, const vector<vector<double> >& data, const vector<int>& labels, const int& num);

#endif
