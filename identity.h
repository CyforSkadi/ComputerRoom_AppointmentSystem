#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include"globalFile.h"
#include<vector>

//��ݻ���
class Identity
{
public:

	//�����˵� ���麯��
	virtual void operMenu() = 0;

	string m_Name;	//�û���
	string m_Pwd;	//����

};
