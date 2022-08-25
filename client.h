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
//�����̲߳�ʹ���ź�������ģ��ͻ���������֮���ͨ��
#define void LDA
#define BufSize 10000
class client
{
private:
	vector<string> client_id;            //�ͻ���id
	SOCKET  c;
	string server_id;                    //�����id
	vector<void> model;                  //ģ��
	int local_epochs;                    //ѵ�������������������ԣ�
	vector<int> batch_size;                      //ÿ��ѵ�������ѡȡ����������С
	vector<vector<vector<double> > > data;        //��ʾ������ѧϰ�����иÿͻ�����ӵ�е���������
	vector<vector<int> > labels;
public:
	client() {};
	bool set(vector<string> Id, string Server_id, vector<void> Model, int Local_epochs, vector<int> Batch_size, vector<vector<vector<double> > >& Data, vector<vector<int> >& Labels);
	bool  send_para();                        //ͨ��ģ��ָ�����ģ���еĻ�ȡ�����ĺ������������˷���ѵ���õĲ���
	bool  get_para();
	bool  run();                              //����ģ��ѵ��     
	bool  cmp(int i, void Model, const vector<vector<double> >& test_data, const vector<int>& test_labels);//�Ƚ���һ�־ۺϺ�Ĳ����Լ���ǰ����ѵ���õĲ����ķ���Ч��
	bool  evaluate();
};
#endif
