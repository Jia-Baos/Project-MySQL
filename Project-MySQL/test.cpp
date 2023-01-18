#include <iostream>
#include <string>
#include <mysql.h>

const std::string host = "127.0.0.1";
const std::string user = "root";
const std::string pw = "6213";
const std::string database_name = "student";
const int port = 3306;

struct Student
{
	int student_id;
	std::string student_name;
	std::string class_id;
};
int main(int argc, char* argv[])
{
	// ��ʼ�����ݿ�
	MYSQL* mysql;		// ���ݿ���
	mysql = mysql_init(NULL);

	// ����ַ�����
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "GBK");

	if (!mysql_real_connect(mysql, host.c_str(), user.c_str(), pw.c_str(), database_name.c_str(), port, NULL, 0))
	{
		std::cerr << "Failed to connect to MySQL database: " << mysql_error(mysql) << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Successed to connect to MySQL database" << std::endl;
	}

	// ��ѯ����
	std::string select_info = "select * from students;";
	int ret = mysql_real_query(mysql, select_info.c_str(), select_info.size());
	if (ret != 0)
	{
		std::cout << "mysql_real_query faied! " << std::endl;
	}
	else
	{
		std::cout << "mysql_real_query success! " << std::endl;
	}

	// ��ȡ�����
	MYSQL_RES* res;		// ��ѯ�����
	res = mysql_store_result(mysql);

	// ��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ����
	MYSQL_ROW row;		// ��¼�ṹ��
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		std::cout << row[0] << " "
			<< row[1] << " "
			<< row[2] << " "
			<< std::endl;
	}

	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�
	mysql_close(mysql);
	mysql_library_end();

	system("pause");
	return 0;
}