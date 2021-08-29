#include"manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器 获取到所有文件中学生和教师信息
	this->initVector();

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId&&ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}

	ifs.close();
	//cout << "机房的数量为：" << vCom.size() << endl;
}

//菜单界面
void Manager::operMenu()
{
	cout << "欢迎管理员："<< this->m_Name << "登录！" << endl;
	cout << "\t\t --------------------------------- \n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|         1、添加账号             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|         2、查看账号             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|         3、查看机房             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|         4、清空预约             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|         0、注销登录             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t --------------------------------- \n";
	cout << "请输入您的选择：";
}

//添加账号
void Manager::addPerson()
{

	string fileName;	//操作文件名
	string tip;	//提示id号
	ofstream ofs;	//文件操作对象

	string errorTip;	//重复错误提示

	int select = 0;

	while (true)
	{
		cout << "请输入添加账号的类型：" << endl;
		cout << "1、添加学生" << endl;
		cout << "2、添加教师" << endl;


		cin >> select;

		if (select == 1)
		{
			//添加学生
			fileName = STUDENT_FILE;
			tip = "请输入学号：";
			errorTip = "学号重复，请重新输入！";
			break;
		}
		else if(select==2)
		{
			//添加教师
			fileName = TEACHER_FILE;
			tip = "请输入职工号：";
			errorTip = "职工号重复，请重新输入！";
			break;
		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
		}
	}
	

	ofs.open(fileName, ios::out | ios::app);	//利用追加方式写文件

	int id;
	string name;
	string pwd;

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);

		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功！" << endl;
	
	system("pause");
	system("cls");

	ofs.close();

	//初始化容器 防止刚添加的账号不会出现重复
	this->initVector();

}

//打印学生
void printStudent(Student &s)
{
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}

//打印教师
void printTeacher(Teacher &t)
{
	cout << "职工号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}


//查看账号
void Manager::showPerson()
{
	while (true)
	{
		cout << "请选择查看内容：" << endl;
		cout << "1、查看所有学生" << endl;
		cout << "2、查看所有老师" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//查看学生
			cout << "所有学生信息如下：" << endl;
			for_each(vStu.begin(), vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			//查看老师
			cout << "所有教师信息如下：" << endl;
			for_each(vTea.begin(), vTea.end(), printTeacher);
			break;
		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
		}
	}
	
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;

	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号为：" << it->m_ComId << " 机房最大容量为：" << it->m_MaxNum << endl;
	}

	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	cout << "确认清空所有预约记录？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs;
		ofs.open(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "清空成功！" << endl;

		system("pause");
		system("cls");
		
	}
	else
	{
		system("cls");
	}
	
	
}

//初始化容器
void Manager::initVector()
{
	//确保容器清空
	vStu.clear();
	vTea.clear();

	//读取学生信息 
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id&&ifs >> s.m_Name&&ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}

	//cout << "当前学生个数为：" << vStu.size() << endl;
	ifs.close();

	//读取教师信息 
	ifs.open(TEACHER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId&&ifs >> t.m_Name&&ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}

	//cout << "当前教师个数为：" << vTea.size() << endl;
	ifs.close();


}

//检测重复 id号 身份类型
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		//检测教师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}

	return false;
}
