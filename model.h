#ifndef MODEL
#define MODEL
#include<iostream>
#include<vector>
#include"matrix.h"
#include"layer.h"

double accuracy(vector<int> true_labels, vector<int> pred_labels);//精确率

vector<double> precision(vector<int> true_labels, vector<int> pred_labels);//查准率

vector<double> recall(vector<int> true_labels, vector<int> pred_labels);//查全率

double ROC(vector<int> true_labels, vector<int> pred_labels);//ROC曲线

class LDA//二分类
{
private:
	vector<double> w;       //投影向量即模型参数
	double threshold;       //分类阈值
public:
	LDA() {};
	LDA(int d) { w.resize(d); threshold = 0; }                                   //d维数据
	bool init(int d);
	void set_para(const vector<double>& para);                   //设置模型参数
	vector<double> get_para();                                   //获取实际类型模型参数
	string para_to_str(const vector<double>& para);              //将实际参数转换为用于通信的文本类型参数
	vector<double> str_to_para(string para);                     //将用于通信的文本类型参数转换为实际参数
	void train(const vector<vector<double> >& data, const vector<int>& labels);//训练模型
	vector<int> predict(const vector<vector<double> >& data);           //输出预测结果
};

class BP
{
private:
	int epochs;
	double learning_rate;
	vector<layer> layers;
	double (*loss)(const vector<double>& output, const vector<double>& y);
	vector<double>(*dloss)(const vector<double>& output, const vector<double>& y);
public:
	BP(int Epochs, double Learning_rate, vector<layer> Layers, double (*Loss)(const vector<double>& output, const vector<double>& y), vector<double>(*Dloss)(const vector<double>& output, const vector<double>& y));
	bool train(vector<vector<double> > data, vector<vector<double> > Y);
	vector<vector<double> > predict(vector<vector<double> > data);
	vector<vector<vector<double> > > get_para();
	bool set_para(const vector<vector<vector<double> > >& para);
	vector<vector<vector<double> > > str_to_para(const string& str);
	string para_to_str(const vector<vector<vector<double> > >& para);
};

#endif
