#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include"globalFile.h"
#include<vector>

//身份基类
class Identity
{
public:

	//操作菜单 纯虚函数
	virtual void operMenu() = 0;

	string m_Name;	//用户名
	string m_Pwd;	//密码

};
