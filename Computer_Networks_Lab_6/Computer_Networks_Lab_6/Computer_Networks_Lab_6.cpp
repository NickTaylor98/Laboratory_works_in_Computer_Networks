// Computer_Networks_Lab_6.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Ping.hpp"
#include "Parm.hpp"
int main(int argc, char **argv)
{
	try
	{
		setlocale(LC_ALL, "RUS");
		Parm::PARM rc = Parm::getParm(argc, argv);
		Ping::ping(rc);
	}
	catch (char* e)
	{
		cout << e << endl;
	}
	system("pause");
	return 0;
}