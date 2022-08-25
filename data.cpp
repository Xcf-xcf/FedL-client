#include"data.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<ctime>
#include<cstdio>
using namespace std;

bool read_in(vector<vector<double> >& data, vector<int>& labels, string dataPath, string labelsPath)
{
	ifstream dataFile,labelsFile;
	dataFile.open(dataPath.data());
	labelsFile.open(labelsPath.data());
	string s="";
	while (getline(dataFile, s))
	{
		stringstream ss(s);
		vector<double> x;
		double buf;
		while (ss >> buf)
		{
			x.push_back(buf);
		}
		data.push_back(x);
	}
	int x;
	while (labelsFile >> x)
	{
		labels.push_back(x);
	}
	return true;
}

bool split_data(vector<vector<vector<double> > >& data_sect, vector<vector<int> >& labels_sect, const vector<vector<double> >& data, const vector<int>& labels, const vector<double>& ratio)
{
	int n = data.size();
	vector<int> index;
	for (int i = 0; i < n; i ++ )
	{
		index.push_back(i);
	}
	srand(unsigned(time(0)));
	random_shuffle(index.begin(), index.end());
	double sum = ratio[0];
	int num = sum * n;
	vector<vector<double> > d;
	vector<int> l;
	for (int i = 0, j = 0; i < n; i++)
	{
		if(i >= num)
		{
			data_sect.push_back(d);
			labels_sect.push_back(l);
			d.clear();
			l.clear();
			if (j < ratio.size() - 1)
			{
				++j;
				sum += ratio[j];
				num = (int)(sum * n);
			}
		}
		d.push_back(data[index[i]]);
		l.push_back(labels[index[i]]);
	}
	data_sect.push_back(d);
	labels_sect.push_back(l);
	return true;
}

bool split_data(vector<vector<double> >& data_sect, vector<int>& labels_sect, const vector<vector<double> >& data, const vector<int>& labels, const int& num)
{
	int n = data.size();
	vector<int> index;
	for (int i = 0; i < n; i++)
	{
		index.push_back(i);
	}
	srand(unsigned(time(0)));
	random_shuffle(index.begin(), index.end());
	for (int i = 0, j = 0; i < n; i++)
	{
		if (i >= num)
		{
			break;
		}
		data_sect.push_back(data[index[i]]);
		labels_sect.push_back(labels[index[i]]);
	}
	return true;
}