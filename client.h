#ifndef CLIENT
#define CLIENT
#include<iostream>
#include<string>
#include<vector>
#include "model.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
//创建线程并使用信号量机制模拟客户端与服务端之间的通信
#define void LDA
#define BufSize 10000
class client
{
private:
	vector<string> client_id;            //客户端id
	SOCKET  c;
	string server_id;                    //服务端id
	vector<void> model;                  //模型
	int local_epochs;                    //训练轮数（针对神经网络而言）
	vector<int> batch_size;                      //每轮训练中随机选取的数据量大小
	vector<vector<vector<double> > > data;        //表示在联邦学习过程中该客户端所拥有的所有数据
	vector<vector<int> > labels;
public:
	client() {};
	bool set(vector<string> Id, string Server_id, vector<void> Model, int Local_epochs, vector<int> Batch_size, vector<vector<vector<double> > >& Data, vector<vector<int> >& Labels);
	bool  send_para();                        //通过模型指针调用模型中的获取参数的函数，并向服务端发送训练好的参数
	bool  get_para();
	bool  run();                              //进行模型训练     
	bool  cmp(int i, void Model, const vector<vector<double> >& test_data, const vector<int>& test_labels);//比较上一轮聚合后的参数以及当前本地训练好的参数的分类效果
	bool  evaluate();
};
#endif
