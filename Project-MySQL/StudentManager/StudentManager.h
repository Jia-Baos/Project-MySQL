#pragma once
#ifndef __STUDENTMANAGER_H__
#define __STUDENTMANAGER_H__

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <format>
#include <mysql.h>

typedef struct Student
{
	int student_id;
	std::string student_name;
	std::string class_id;
};

class StudentManager
{
private:
	MYSQL* mysql;
	const std::string host = "127.0.0.1";
	const std::string user = "root";
	const std::string pw = "6213";
	const std::string database_name = "student";
	const int port = 3306;

public:
	StudentManager();
	virtual ~StudentManager();
	static StudentManager* pStudentManager;	// ��������
	static StudentManager* getInstance();		// ��ȡ��ʵ��
	static void deleteInstance();	// �ͷŵ�ʵ���������˳�ʱ����
	bool insertStudent(Student& stu);
	bool deleteStudent(int student_id);
	bool updateStudent(Student& stu);
	std::vector<Student> getStudent(std::string condination = "");
};

#endif // !__STUDENTMANAGER_H__
