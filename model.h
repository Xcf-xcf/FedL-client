#ifndef MODEL
#define MODEL
#include<iostream>
#include<vector>
#include"matrix.h"
#include"layer.h"

double accuracy(vector<int> true_labels, vector<int> pred_labels);//��ȷ��

vector<double> precision(vector<int> true_labels, vector<int> pred_labels);//��׼��

vector<double> recall(vector<int> true_labels, vector<int> pred_labels);//��ȫ��

double ROC(vector<int> true_labels, vector<int> pred_labels);//ROC����

class LDA//������
{
private:
	vector<double> w;       //ͶӰ������ģ�Ͳ���
	double threshold;       //������ֵ
public:
	LDA() {};
	LDA(int d) { w.resize(d); threshold = 0; }                                   //dά����
	bool init(int d);
	void set_para(const vector<double>& para);                   //����ģ�Ͳ���
	vector<double> get_para();                                   //��ȡʵ������ģ�Ͳ���
	string para_to_str(const vector<double>& para);              //��ʵ�ʲ���ת��Ϊ����ͨ�ŵ��ı����Ͳ���
	vector<double> str_to_para(string para);                     //������ͨ�ŵ��ı����Ͳ���ת��Ϊʵ�ʲ���
	void train(const vector<vector<double> >& data, const vector<int>& labels);//ѵ��ģ��
	vector<int> predict(const vector<vector<double> >& data);           //���Ԥ����
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
