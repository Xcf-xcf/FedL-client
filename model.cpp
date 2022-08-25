#include"matrix.h"
#include"model.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<set>
using namespace std;

double accuracy(vector<int> true_labels, vector<int> pred_labels)
{
	double acc=0;
	set<int> cls(true_labels.begin(), true_labels.end());
	for (set<int>::iterator it = cls.begin(); it != cls.end(); it++)
	{
		acc += sum((true_labels == (*it))&&(pred_labels == (*it)));
	}
	acc /= (1.0 * true_labels.size());
	return acc;
}

vector<double> precision(vector<int> true_labels, vector<int> pred_labels)
{
	set<int> cls(true_labels.begin(), true_labels.end());
	vector<double> x;
	for (set<int>::iterator it = cls.begin(); it != cls.end(); it++)
	{
		x.push_back(1.0 * sum((true_labels == (*it)) && (pred_labels == (*it))) / sum(pred_labels == (*it)));
	}
	return x;
}

vector<double> recall(vector<int> true_labels, vector<int> pred_labels)
{
	set<int> cls(true_labels.begin(), true_labels.end());
	vector<double> x;
	for (set<int>::iterator it = cls.begin(); it != cls.end(); it++)
	{
		x.push_back(1.0 * sum((true_labels == (*it)) && (pred_labels == (*it))) / sum(true_labels == (*it)));
	}
	return x;
}

bool LDA::init(int d)
{
	w.resize(d); 
	threshold = 0;
	return true;
}

void LDA::set_para(const vector<double>& para)
{
	threshold = para[para.size() - 1];
	w.assign(para.begin(), para.end()-1);
}

vector<double> LDA::get_para()
{
	vector<double> para(w.begin(), w.end());
	para.push_back(threshold);
	return para;
}

string LDA::para_to_str(const vector<double>& para)
{
	int n = para.size();
	string str = "";
	for (int i = 0; i < n; i++)
	{
		if (i)
			str = str + " ";
		stringstream ss;
		ss << setprecision(15) << para[i];
		str = str + ss.str();
	}
	return str;
}

vector<double> LDA::str_to_para(string para)
{
	stringstream ss(para);
	double buf;
	vector<double> p;
	while (ss >> buf)
	{
		p.push_back(buf);
		//cout << buf << endl;
	}
	return p;
}

void LDA::train(const vector<vector<double> >& data, const vector<int>& labels)
{
	vector<vector<double> > d0=row(data, labels == 0), d1= row(data, labels == 1);
	vector<vector<double> > s0 = cov(d0), s1 = cov(d1);
	vector<double> m0 = mean(d0), m1 = mean(d1);
	vector<vector<double> > M0 = T(m0);
	vector<vector<double> > M1 = T(m1);
	vector<vector<double> > s = s0 + s1;
	s = inv(s + (1e-6) * eye(s.size(), s.size()));
	//cout << M0.size() << endl;
	vector<vector<double> > t = T(s * (M0 + (-1) * M1));
	w = t[0];
	M0 = T(M0);
	M1 = T(M1);
	threshold = (((0.5 * M0) + (0.5 * M1)) * T(vector<vector<double> >(1, vector<double>(w.begin(), w.end()))))[0][0];
}

vector<int> LDA::predict(const vector<vector<double> >& data)
{
	int n = data.size();
	vector<int> labels(n);
	//cout << data.size() << ' ' << data[0].size() << endl;
	//cout << w.size() << endl;
	vector<vector<double> > y = data * T(w);
	for (int i = 0; i < n; i++)
	{
		if (y[i][0] >= threshold)
		{
			labels[i] = 0;
		}
		else
		{
			labels[i] = 1;
		}
	}
	return labels;
}


BP::BP(int Epochs, double Learning_rate, vector<layer> Layers, double (*Loss)(const vector<double>& output, const vector<double>& y), vector<double>(*Dloss)(const vector<double>& output, const vector<double>& y))
{
	epochs = Epochs;
	learning_rate = Learning_rate;
	layers.assign(Layers.begin(), Layers.end());
	loss = Loss;
	dloss = Dloss;
}

bool BP::train(vector<vector<double> > data, vector<vector<double> > Y)
{
	int n = data.size();
	for (int i = 0; i < epochs; i++)
	{
		for (int j = 0; j < n; j++)
		{
			vector<vector<double> > y;
			y.push_back(data[j]);
			for (int k = 0; k < layers.size(); i++)
			{
				y.push_back(layers[k].y(y[k]));
			}
			vector<double> dy = dloss(y[layers.size()], Y[i]);
			for (int k = layers.size()-1; k >= 0; k--)
			{
				vector<vector<double> > dw = layers[k].dw(y[k], dy);
				vector<double> db = layers[k].db(y[k], dy);
				vector<vector<double> > Dy;
				Dy.push_back(dy);
				dy = flat(Dy * layers[k].get_w());
				dw = (-learning_rate) * dw;
				db = (-learning_rate) * db;
				layers[k].set_w(layers[k].get_w() + dw);
				layers[k].set_b(layers[k].get_b() + db);
			}
		}
	}
	return true;
}

vector<vector<double> > BP::predict(vector<vector<double> > data)
{
	vector<vector<double> > y;
	for (int i = 0; i < data.size(); i++)
	{
		vector<double> x = data[i];
		for (int j = 0; j < layers.size(); j++)
		{
			x = layers[j].y(x);
		}
		y.push_back(x);
	}
	return y;
}

vector<vector<vector<double> > > BP::get_para()
{
	vector<vector<vector<double> > > para;
	for (int i = 0; i < layers.size(); i++)
	{
		vector<vector<double> > w = layers[i].get_w();
		vector<double> b = layers[i].get_b();
		for (int j = 0; j < b.size(); j++)
		{
			w[j].push_back(b[j]);
		}
		para.push_back(w);
	}
	return para;
}

bool BP::set_para(const vector<vector<vector<double> > >& para)
{
	for (int i = 0; i < layers.size(); i++)
	{
		vector<vector<double> > w(para[i].size());
		vector<double> b(para[i].size());
		for (int j = 0; j < para[i].size(); j++)
		{
			w[j].assign(para[i][j].begin(), para[i][j].end()-1);
			b.push_back(para[i][j][para[i][j].size() - 1]);
		}
		layers[i].set_w(w);
		layers[i].set_b(b);
	}
	return true;
}

vector<vector<vector<double> > > BP::str_to_para(const string& str)
{
	vector<vector<vector<double> > > para;
	stringstream sss(str);
	string layer = "", buf = "";
	while (getline(sss, layer, ';'))
	{
		vector<vector<double> > p;
		stringstream ss(layer);
		while (getline(ss, buf))
		{
			vector<double> x;
			stringstream s(buf);
			double cnt;
			while (s >> cnt)
			{
				x.push_back(cnt);
			}
			p.push_back(x);
		}
		para.push_back(p);
	}
	return para;
	
}

string BP::para_to_str(const vector<vector<vector<double> > >& para)
{
	string str = "";
	for (int i = 0; i < para.size(); i++)
	{
		if (i)
			str += ";";
		for (int j = 0; j < para[i].size(); j++)
		{
			if (j)
				str += "\n";
			for (int k = 0; k < para[i][j].size(); k++)
			{
				if (k)
					str += " ";
				stringstream ss;
				ss << setprecision(15) << para[i][j][k];
				str += ss.str();
			}
		}
	}
	return str;
}