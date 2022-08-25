#ifndef MATRIX
#define MATRIX
#include<iostream>
#include<vector>
using namespace std;

vector<vector<double> > eye(const int& n, const int& m);                  //单位阵

vector<vector<double> > diag(const vector<double>& a);             //主对角线元素为a中元素的方阵

vector<vector<double> > T(const vector<vector<double> >& a);//转置

vector<vector<double> > T(const vector<double>& a);

vector<double> flat(const vector<vector<double> >& a);

vector<vector<double> > repeat(const vector<double>& a, const int& n, const int& axis=0);//每行（axis=0）或每列（axis=1）均为a中元素的矩阵

double det(vector<vector<double> > a);                                             //行列式

vector<vector<double> > operator*(const vector<vector<double> >& a, const vector<vector<double> >& b);//两矩阵相乘

vector<vector<double> > operator*(const vector<vector<double> >& a, const double& b);

vector<vector<double> > operator*(const double& b, const vector<vector<double> >& a);

vector<double> operator*(const vector<double>& a, const double& b);

vector<double> operator*(const double& b, const vector<double>& a);

vector<double> operator*(const vector<double>& a, const vector<double>& b);

vector<vector<double> > operator+(const vector<vector<double> >& a, const vector<vector<double> >& b);//矩阵加法

vector<double> operator+(const vector<double>& a, const vector<double>& b);

template<typename T>
vector<bool> operator==(const vector<T>& a, const T& b)
{
	int n = a.size();
	vector<bool> x(n);
	for (int i = 0; i < n; i++)
	{
		x[i] = (a[i] == b);
	}
	return x;
}

vector<bool> operator&&(const vector<bool>& a, const vector<bool>& b);

int sum(const vector<bool>& a);

vector<vector<double> > row(const vector<vector<double> >& a, const vector<bool>& b);

vector<vector<double> > col(const vector<vector<double> >& a, const vector<bool>& b);

vector<vector<double> > inv(const vector<vector<double> >& a);                            //矩阵求逆

vector<double> mean(const vector<vector<double> >& a, int axis=0);                              //求均值（axis=0代表按行求，反之按列求）

vector<vector<double> > cov(const vector<vector<double> >& a, bool colvar = true);                           //求方差（colvar=true代表a中每列为一个变量，反之每行为一个变量）
#endif
