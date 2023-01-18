#include <iostream>
#include "StudentManager.h"

StudentManager::StudentManager()
{
	std::cout << "Initalize the Class: StudentManager~" << std::endl;

	// ��ʼ�����ݿ���
	this->mysql = mysql_init(NULL);
	if (nullptr == this->mysql)
	{
		std::cerr << "MySQL�����ʼ��ʧ��~" << mysql_error(this->mysql) << std::endl;
	}

	// ����ַ�����
	mysql_options(this->mysql, MYSQL_SET_CHARSET_NAME, "GBK");

	if (nullptr == mysql_real_connect(this->mysql,
		this->host.c_str(), this->user.c_str(), this->pw.c_str(),
		this->database_name.c_str(), this->port, NULL, 0))
	{
		std::cerr << "MySQL���ݿ������޷���������~" << mysql_error(this->mysql) << std::endl;
	}
}

StudentManager::~StudentManager()
{
	// �ر����ݿ�
	mysql_close(this->mysql);
	mysql_library_end();

	std::cout << "Destory the Class: StudentManager~" << std::endl;
}

// ����һ���оͳ�ʼ������ʵ�� ��������̰߳�ȫ�����ⶨ�岢��ʼ���������ټ�static�ؼ��֣�
StudentManager* StudentManager::pStudentManager = new (std::nothrow) StudentManager();

StudentManager* StudentManager::getInstance()
{
	return pStudentManager;
}

void StudentManager::deleteInstance()
{
	if (pStudentManager)
	{
		delete pStudentManager;
		pStudentManager = nullptr;
		std::cout << "ɾ������ģʽ�е�ָ��~" << std::endl;
	}
}

bool StudentManager::insertStudent(Student& stu)
{
	std::string message =
		std::format("INSERT INTO students (student_id,student_name,class_id) VALUES({},'{}','{}');",
			stu.student_id, stu.student_name.c_str(), stu.class_id.c_str());

	// �ɹ�����0��ʧ�ܷ���1
	if (mysql_real_query(this->mysql, message.c_str(), message.size()))
	{
		std::cerr << "insert failed! " << mysql_error(this->mysql) << std::endl;
		return false;
	}
	return true;
}

bool StudentManager::deleteStudent(int student_id)
{
	std::string message =
		std::format("DELETE FROM students WHERE student_id={};", student_id);

	// �ɹ�����0��ʧ�ܷ���1
	if (mysql_real_query(this->mysql, message.c_str(), message.size()))
	{
		std::cerr << "update failed! " << mysql_error(this->mysql) << std::endl;
		return false;
	}
	return true;
}

bool StudentManager::updateStudent(Student& stu)
{
	std::string message =
		std::format("UPDATE students SET student_name='{}',class_id='{}' WHERE student_id={};",
			stu.student_name.c_str(), stu.class_id.c_str(), stu.student_id);

	// �ɹ�����0��ʧ�ܷ���1
	if (mysql_real_query(this->mysql, message.c_str(), message.size()))
	{
		std::cerr << "update failed! " << mysql_error(this->mysql) << std::endl;
		return false;
	}
	return true;
}

std::vector<Student> StudentManager::getStudent(std::string condination)
{
	std::vector<Student> student_vector;

	std::string message =
		std::format("SELECT * FROM students {};",
			condination.c_str());

	// �ɹ�����0��ʧ�ܷ���1
	if (mysql_real_query(this->mysql, message.c_str(), message.size()))
	{
		std::cerr << "get failed! " << mysql_error(this->mysql) << std::endl;
	}

	// ��ȡ�����
	MYSQL_RES* res = mysql_store_result(this->mysql);

	// ��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ����
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		Student stu;
		stu.student_id = atoi(row[0]);
		stu.student_name = row[1];
		stu.class_id = row[2];

		student_vector.push_back(stu);
	}
	return student_vector;
}