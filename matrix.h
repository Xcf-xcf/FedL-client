#ifndef MATRIX
#define MATRIX
#include<iostream>
#include<vector>
using namespace std;

vector<vector<double> > eye(const int& n, const int& m);                  //��λ��

vector<vector<double> > diag(const vector<double>& a);             //���Խ���Ԫ��Ϊa��Ԫ�صķ���

vector<vector<double> > T(const vector<vector<double> >& a);//ת��

vector<vector<double> > T(const vector<double>& a);

vector<double> flat(const vector<vector<double> >& a);

vector<vector<double> > repeat(const vector<double>& a, const int& n, const int& axis=0);//ÿ�У�axis=0����ÿ�У�axis=1����Ϊa��Ԫ�صľ���

double det(vector<vector<double> > a);                                             //����ʽ

vector<vector<double> > operator*(const vector<vector<double> >& a, const vector<vector<double> >& b);//���������

vector<vector<double> > operator*(const vector<vector<double> >& a, const double& b);

vector<vector<double> > operator*(const double& b, const vector<vector<double> >& a);

vector<double> operator*(const vector<double>& a, const double& b);

vector<double> operator*(const double& b, const vector<double>& a);

vector<double> operator*(const vector<double>& a, const vector<double>& b);

vector<vector<double> > operator+(const vector<vector<double> >& a, const vector<vector<double> >& b);//����ӷ�

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

vector<vector<double> > inv(const vector<vector<double> >& a);                            //��������

vector<double> mean(const vector<vector<double> >& a, int axis=0);                              //���ֵ��axis=0�������󣬷�֮������

vector<vector<double> > cov(const vector<vector<double> >& a, bool colvar = true);                           //�󷽲colvar=true����a��ÿ��Ϊһ����������֮ÿ��Ϊһ��������
#endif
