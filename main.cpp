#include<winsock2.h>//winsock2的头文件
#include<iostream>
#include<string>
#include<vector>
#include"client.h"
#include"model.h"
#include"data.h"
#include<time.h>
using  namespace std;

//勿忘，链接dll的lib
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
//config

#define CLIENT_NUM 10
#define TIME_TO_DELAY 2000000000
vector<string> clt_id({ "1","2","3","4","5","6","7","8","9","10"});
string svr_id = "127.0.0.1";
int local_epochs = 100;
int global_epochs = 100;
vector<int> batch_size({ 50,100,150,200,250,300,350,400,450,500});
vector<vector<double> > Data;
vector<int> Labels;

int  main()
{

	//加载winsock2的环境
	WSADATA  wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
	{
		cout << "WSAStartup  error：" << GetLastError() << endl;
		return 0;
	}
	cout << "Client Config:\n";
	cout << "IDs: ";
	for (int j = 0; j < CLIENT_NUM; j++)
	{
		cout << clt_id[j] << ' ';
	}
	cout << endl;
	cout << "Local_Epochs:  " << local_epochs << endl;
	cout << "Global_Epochs: " << global_epochs << endl;
	cout << "Batch_Size: ";
	for (int j = 0; j < CLIENT_NUM; j++)
	{
		cout << batch_size[j] << ' ';
	}
	cout << endl;
	read_in(Data, Labels, "E:\\FedL\\client\\data.txt", "E:\\FedL\\client\\labels.txt");
	client clt;
	vector<LDA> model(CLIENT_NUM);
	vector<vector<vector<double> > > data_sect(CLIENT_NUM);
	vector<vector<int> > labels_sect(CLIENT_NUM);
	for (int i = 0; i < CLIENT_NUM; i++)
	{
		split_data(data_sect[i], labels_sect[i], Data, Labels, batch_size[i]);
		//cout << data_sect.size() << endl;
		model[i].init(Data[0].size());
	}
	clt.set(clt_id, svr_id, model, local_epochs, batch_size, data_sect, labels_sect);
	//cout << 1 << endl;
	for (int i = 0; i < global_epochs; i++)
	{
		cout << "------------Epoch " << i + 1 << "------------" << endl;
		if(i)
			clt.get_para();
		if(i)
			cout << "!!!!!!!!!All Clients Received Parameters!!!!!!!!!" << endl;
		clt.run();
		cout << "!!!!!!!!!!Model Has Been Trained Locally!!!!!!!!!" << endl;
		clt.send_para();
		cout << "!!!!!All Client Parameters Has Been Uploaded!!!!!"<< endl;
		clt.evaluate();
	}
	WSACleanup();
	return 0;
}
