#include<iostream>
#include<string>
#include<sstream>
#include"client.h"
#include"data.h"
#include"model.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;

bool client::set(vector<string> Id, string Server_id, vector<void> Model, int Local_epochs, vector<int> Batch_size, vector<vector<vector<double> > >& Data, vector<vector<int> >& Labels)
{
	client_id.assign(Id.begin(),Id.end());
	server_id = Server_id;
	model.assign(Model.begin(),Model.end());
	local_epochs = Local_epochs;
	batch_size.assign(Batch_size.begin(),Batch_size.end());
	data.assign(Data.begin(), Data.end());
	labels.assign(Labels.begin(), Labels.end());
	c = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c == INVALID_SOCKET)
	{
		cout << "socket  error：" << GetLastError() << endl;
		return false;
	}
	//cout << 1 << endl;
	//2.链接服务端
	sockaddr_in   addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr(server_id.c_str());

	int len = sizeof(sockaddr_in);
	if (connect(c, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
	{
		cout << "connect  error：" << GetLastError() << endl;
		return false;
	}
	cout << "Connected Server!" << endl;
	return true;
}
bool client::send_para()
{
	string para = "";
	int clt_num = client_id.size();
	for (int i = 0; i < clt_num; i++)
	{
		if (i)
			para += "\n";
		para += client_id[i] + ":";
		para += model[i].para_to_str(model[i].get_para());
	}
	int ret = 0;
	char msg[1] = { 'S' };
	while (send(c, msg, 1, 0) == 0);
	char buf[BufSize] = { 0 };
	sprintf(buf, para.c_str());
	while (send(c, buf, BufSize, 0) == 0);
	return true;
}

bool client::get_para()
{
	int clt_num = client_id.size();
	char msg[1] = { 'R' };
	while (send(c, msg, 1, 0) == 0);
	char buf[BufSize] = { 0 };
	while (recv(c, buf, BufSize, 0) == 0);
	string para(buf);
	for (int i = 0; i < clt_num; i++)
	{
		model[i].set_para(model[i].str_to_para(para));
	}
	return true;
}

bool  client::run()
{
	int clt_num = client_id.size();
	for (int i = 0; i < clt_num; i++)
	{
		vector< vector<vector<double> > > data_sect;
		vector<vector<int> > labels_sect;
		split_data(data_sect, labels_sect, data[i], labels[i], vector<double>({ 0.7,0.3 }));
		void Model(data[i][0].size());
		Model.train(data_sect[0], labels_sect[0]);
		//if (cmp(Model, data_sect[1], labels_sect[1]))
		model[i].set_para(Model.get_para());
	}
	return true;
}

bool  client::cmp(int i,void Model, const vector<vector<double> >& test_data, const vector<int>& test_labels)
{
	
	vector<int> p1 = model[i].predict(test_data);
	//cout << test_data.size() << endl;
	vector<int> p2 = Model.predict(test_data);
	//cout << data.size() << endl;
	double a1 = accuracy(test_labels, p1);
	double a2 = accuracy(test_labels, p2);
	if (a1 < a2)
		return true;
	else
		return false;
}

bool  client::evaluate()
{
	int clt_num = client_id.size();
	cout << "-------------------Result---------------------" << endl;
	for (int i = 0; i < clt_num; i++)
	{
		cout << "Client " << client_id[i] << endl;
		vector<int> pred_labels = model[i].predict(data[i]);
		printf("准确率: %5.2lf%%\n", accuracy(labels[i], pred_labels) * 100);
		printf("查准率: %5.2lf%% %5.2lf%%\n", precision(labels[i], pred_labels)[0] * 100, precision(labels[i], pred_labels)[1] * 100);
		printf("查全率: %5.2lf%% %5.2lf%%\n", recall(labels[i], pred_labels)[0] * 100, recall(labels[i], pred_labels)[1] * 100);
		cout << endl;
	}
	cout << "----------------------------------------------" << endl;
	return true;
}