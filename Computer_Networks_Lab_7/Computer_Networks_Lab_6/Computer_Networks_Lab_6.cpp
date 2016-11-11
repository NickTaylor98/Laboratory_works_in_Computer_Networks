// Computer_Networks_Lab_6.cpp: определ€ет точку входа дл€ консольного приложени€.
//
// ¬вод в командной строке:Computer_Networks_Lab_6.exe id -ip:192.168.0.1 -mask:255.255.0.0
#include "stdafx.h"
#include "Ping.hpp"
#include "Parm.hpp"
#include "Id.hpp"
int main(int argc, char **argv)
{
	try
	{
		setlocale(LC_ALL, "RUS");
		Parm::PARM rc = Parm::getParm(argc, argv);
		Id::IDs(rc);
	}
	catch (char* e)
	{
		cout << e << endl;
	}
	system("pause");
	return 0;
}