#include "stdafx.h"
#include "Id.hpp"
#define MAX_SIZE_OF_BUFFER 16
#define NUMBER_OF_OCTETS 4
namespace Id
{
	Octet::Octet(char* arr)
	{
		this->octet = new char[4];
		strcpy(this->octet, arr);
		this->value_of_octet = atoi(octet);
	}
	Octet::Octet()
	{
		this->octet = nullptr;
		this->value_of_octet = 0;
	}
	Octet* Divide(char* IP_or_Mask)
	{
		Octet* rc = new Octet[NUMBER_OF_OCTETS];
		char* IP_Copy = new char[strlen(IP_or_Mask)];
		strcpy(IP_Copy, IP_or_Mask);
		int Number_of_octets = 0;
		for (int i(0), j(0); i <= strlen(IP_or_Mask); i++)
		{
			if (IP_or_Mask[i] == '.' || IP_or_Mask[i] == 0x00)
			{
				IP_Copy[j] = 0x00;
				rc[Number_of_octets++] = { IP_Copy };
				IP_Copy = IP_Copy + j + 1;
				j = 0;
			}
			else j++;
		}
		return rc;
	}
	bool isValidMask(char mask[255])
	{
		bool rc(true), isEndOne(false); // isEndOne - переменная, отвечающая за окончание единиц в октете (0 - если, 
		char *buf = new char[4];         // на предыдущем октете были одни единицы, 1 - если, были нули)
		int bufCount = 0, octet = 0, octetCount = 0; 
		for (unsigned int i = 0; i < strlen(mask) && rc; i++)      
		{
			if (mask[i] == '.')
			{
				buf[bufCount] = 0x00;
				octetCount++;
				octet = atoi(buf);
				if (octet > 255) rc = false;
				if (octet != 128 && octet != 192 && octet != 224 && octet != 240 
					&& octet != 248 &&  octet != 252 && octet !=  254 && octet != 0 
					&& octet != 255) rc = false;
				if (isEndOne && octet != 0) rc = false;
				if (octet != 255) isEndOne = true;
				bufCount = 0;
			}
			else
			{
				if (mask[i] >= '0' && mask[i] <= '9') buf[bufCount++] = mask[i];
				else rc = false;
			}
		}
		if (octetCount != 3) rc = false;
		return rc;
	}
	void Print(char * str, Octet* For_IP_Adress, Octet* For_Mask)
	{
		cout << str << endl;
		short rc(0);
		for (int i(0); i < NUMBER_OF_OCTETS; i++)
		{
			if (strstr(str, "Network ID:")) rc = For_IP_Adress[i].value_of_octet & For_Mask[i].value_of_octet;
			else if (strstr(str, "Host ID: ")) rc = For_IP_Adress[i].value_of_octet & ~For_Mask[i].value_of_octet;
			else if (strstr(str, "Broadcast: "))
				if (!(rc = For_IP_Adress[i].value_of_octet & For_Mask[i].value_of_octet)) rc = 0xff;
			cout << rc << (i == NUMBER_OF_OCTETS - 1 ? '\n' : '.');
		}
		cout << endl;
	}
	void IDs(Parm::PARM parm)
	{
		Octet* For_IP_Adress = Divide(parm.id.IP);
		Octet* For_Mask = Divide(parm.id.MASK);
		cout << "IP Adress:" << '\n' << parm.id.IP << '\n' << '\n';
		cout << "Mask: " << '\n' << parm.id.MASK << '\n' << '\n';
		Print("Network ID:", For_IP_Adress, For_Mask);
		Print("Host ID: ", For_IP_Adress, For_Mask);
		Print("Broadcast: ", For_IP_Adress, For_Mask);
		delete[] For_Mask, For_IP_Adress;
	}
}