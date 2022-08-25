#ifndef LAYER
#define LAYER
#include<iostream>
#include<vector>
#include"matrix.h"
using namespace std;

class layer
{
private:
	int n, m;
	vector<vector<double> > w;
	vector<double> b;
	vector<double> (*f)(const vector<double>&);
	vector<double> (*df)(const vector<double>&);
public:
	layer(int N, int M, vector<double> (*F)(const vector<double>&), vector<double> (*Df)(const vector<double>&));
	bool init();
	vector<vector<double> > get_w();
	vector<double> get_b();
	bool set_w(const vector<vector<double> >& W);
	bool set_b(const vector<double>& B);
	vector<double> y(const vector<double>& x);
	vector<double> dx(const vector<double>& x, const vector<double>& dy);
	vector<vector<double> > dw(const vector<double>& x, const vector<double>& dy);
	vector<double> db(const vector<double>& x, const vector<double>& dy);
};

#endif // !LAYER

