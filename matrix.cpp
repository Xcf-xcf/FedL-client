#include"matrix.h"
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

vector<vector<double> > eye(const int& n, const int& m)
{
	vector<vector<double> > x(n,vector<double>(m));
	int mi = min(n, m);
	for (int i = 0; i < mi; i++)
	{
		x[i][i] = 1;
	}
	return x;
}

vector<vector<double> > diag(const vector<double>& a)
{
	int siz = a.size();
	vector<vector<double> > x(siz, vector<double>(siz));
	for (int i = 0; i < siz; i++)
	{
		x[i][i] = a[i];
	}
	return x;
}

vector<vector<double> > T(const vector<vector<double> >& a)
{
	int n = a[0].size(), m = a.size();
	vector<vector<double> > x(n,vector<double>(m, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			x[i][j] = a[j][i];
		}
	}
	return x;
}

vector<vector<double> > T(const vector<double>& a)
{
	vector<vector<double> > x(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		x[i].push_back(a[i]);
	}
	return x;
}

vector<double> flat(const vector<vector<double> >& a)
{
	vector<double> x;
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a[i].size(); j++)
		{
			x.push_back(a[i][j]);
		}
	}
	return x;
}

vector<vector<double> > repeat(const vector<double>& a, const int& n, const int& axis)
{
	vector<vector<double> > x(n, vector<double>(a.begin(), a.end()));
	if (axis == 1)
		x = T(x);
	return x;
}


double det(vector<vector<double> > a)
{
	int n = a.size();
	for (int i = 0; i < n; i++)
	{
		if (a[i][i] == 0)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (a[j][i] != 0)
				{
					swap(a[i], a[j]);
					break;
				}
			}
			if (a[i][i] == 0)
				return 0;
		}
		for (int k = i + 1; k < n; k++)
		{
			double t = a[k][i] / a[i][i];
			for (int j = i; j < n; j++)
			{
				a[k][j] -= t * a[i][j];
			}
		}
	}
	double x = 1;
	for (int i = 0; i < n; i++)
	{
		x *= a[i][i];
	}
	return x;
}

vector<vector<double> > operator*(const vector<vector<double> >& a, const vector<vector<double> >& b)
{
	int n = a.size(), m = b[0].size(), d=a[0].size();
	vector<vector<double> > x(n, vector<double>(m,0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < d; k++)
			{
				x[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return x;
}

vector<vector<double> > operator*(const vector<vector<double> >& a, const double& b)
{
	vector<vector<double> > x = a;
	int n = x.size(), m = x[0].size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			x[i][j] *= b;
		}
	}
	return x;
}

vector<vector<double> > operator*(const double& b, const vector<vector<double> >& a)
{
	vector<vector<double> > x = a;
	int n = x.size(), m = x[0].size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			x[i][j] *= b;
		}
	}
	return x;
}

vector<double> operator*(const vector<double>& a, const double& b)
{
	vector<double> x(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		x[i] = a[i] * b;
	}
	return x;
}

vector<double> operator*(const double& b, const vector<double>& a)
{
	vector<double> x(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		x[i] = a[i] * b;
	}
	return x;
}
vector<double> operator*(const vector<double>& a, const vector<double>& b)
{
	vector<double> x(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		x[i] = a[i] * b[i];
	}
	return x;
}

vector<vector<double> > operator+(const vector<vector<double> >& a, const vector<vector<double> >& b)
{
	int n = a.size(), m = a[0].size();
	vector<vector<double> > x(n, vector<double>(m, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			x[i][j] = a[i][j] + b[i][j];
		}
	}
	return x;
}

vector<double> operator+(const vector<double>& a, const vector<double>& b)
{
	vector<double> x(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		x[i] = a[i] + b[i];
	}
	return x;
}

vector<bool> operator&&(const vector<bool>& a, const vector<bool>& b)
{
	int n = a.size();
	vector<bool> x(n);
	for (int i = 0; i < n; i++)
	{
		x[i] = (a[i] && b[i]);
	}
	return x;
}

int sum(const vector<bool>& a)
{
	int n = a.size();
	int x = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i])
			x++;
	}
	return x;
}

vector<vector<double> > row(const vector<vector<double> >& a, const vector<bool>& b)
{
	vector<vector<double> > x;
	int n = a.size();
	for (int i = 0; i < n; i++)
	{
		if (b[i])
			x.push_back(a[i]);
	}
	return x;
}

vector<vector<double> > col(const vector<vector<double> >& a, const vector<bool>& b)
{
	vector<vector<double> > A = T(a);
	vector<vector<double> > x = T(row(A, b));
	return x;
}

vector<vector<double> > inv(const vector<vector<double> >& a)
{
	int n = a.size();
	vector<vector<double> > D(n, vector<double>(2 * n, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2 * n; j++)
		{
			if (j < n)
			{
				D[i][j] = a[i][j];
			}
			else
			{
				if ((j - n) == i)
				{
					D[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (D[i][i] == 0)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (D[j][i] != 0)
				{
					swap(D[i], D[j]);
				}
			}
			if (D[i][i] == 0)
			{
				throw - 1;
			}
		}
		double t = D[i][i];
		for (int j = i; j < 2*n; j++)
		{
			D[i][j] /= t;
		}
		for (int k = 0; k < n; k++)
		{
			if (k == i)continue;
			t = -D[k][i];
			for (int j = i; j < 2 * n; j++)
			{
				D[k][j] += t * D[i][j];
			}
		}
	}
	vector<vector<double> > x(n, vector<double>(n, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			x[i][j] = D[i][j + n];
		}
	}
	return x;
}

vector<double> mean(const vector<vector<double> >& a, int axis)
{
	if (axis == 0)
	{
		int m = a[0].size(), n=a.size();
		vector<double> x(m);
		for (int j = 0; j < m; j++)
		{
			for (int i = 0; i < n; i++)
			{
				x[j] += a[i][j];
			}
			x[j] /= n;
		}
		return x;
	}
	else
	{
		int m = a[0].size(), n = a.size();
		vector<double> x(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				x[i] += a[i][j];
			}
			x[i] /= m;
		}
		return x;
	}
}

vector<vector<double> > cov(const vector<vector<double> >& a, bool colvar)
{
	if (colvar)
	{
		vector<double> b = mean(a);
		vector<vector<double> > avg = repeat(b, a.size());
		vector<vector<double> > x = a + avg * (-1);
		vector<vector<double> > var = T(x) * x;
		return var;
	}
	else
	{
		vector<double> b = mean(a, 1);
		vector<vector<double> > avg = repeat(b, a.size(), 1);
		vector<vector<double> > x = a + avg * (-1);
		vector<vector<double> > var = x * T(x);
		return var;
	}
}