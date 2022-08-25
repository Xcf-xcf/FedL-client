#include"layer.h"
#include"matrix.h"
#include<iostream>
#include<vector>
#include<string>
#include <iomanip>
using namespace std;

layer::layer(int N, int M, vector<double> (*F)(const vector<double>&), vector<double> (*Df)(const vector<double>&))
{
	n = N;
	m = M;
	w.resize(m);
	for (int i = 0; i < m; i++)
	{
		w[i].resize(n);
	}
	b.resize(m);
	f = F;
	df = Df;
}

bool layer::init()
{
	srand(time(0));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			w[i][j] = rand() / double(RAND_MAX);
		}
		b[i] = rand() / RAND_MAX;
	}
	return true;
}

vector<vector<double> > layer::get_w()
{
	return w;
}

vector<double> layer::get_b()
{
	return b;
}

bool layer::set_w(const vector<vector<double> >& W)
{
	w.assign(W.begin(), W.end());
	return true;
}

bool layer::set_b(const vector<double>& B)
{
	b.assign(B.begin(), B.end());
	return true;
}

vector<double> layer::y(const vector<double>& x)
{
	vector<double> output = flat(w * T(x));
	output = output + b;
	output = f(output);
	return output;
}

vector<double> layer::dx(const vector<double>& x, const vector<double>& dy)
{
	vector<double> dX;
	vector<vector<double> > dY;
	dY.push_back(df(y(x)) * dy);
	dX = flat(dY * w);
	return dX;
}

vector<vector<double> > layer::dw(const vector<double>& x, const vector<double>& dy)
{
	vector<double> d(m,1.0);
	d = df(y(x));
	vector<vector<double> > X;
	X.push_back(x);
	vector<vector<double> > dW = T(d * dy) * X;
	return dW;
}

vector<double> layer::db(const vector<double>& x, const vector<double>& dy)
{
	vector<double> d(m, 1.0);
	d = df(y(x));
	vector<double > dB = d * dy;
	return dB;
}

