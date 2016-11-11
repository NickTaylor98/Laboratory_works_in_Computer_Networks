#include "stdafx.h"
#include "Ping.hpp"
namespace Ping
{
	void ping(Parm::PARM param)
	{
		char sendData[32] = "Send Data";
		int badPercent, badEcho = 0;
		LPVOID replyBuffer = NULL;
		DWORD replySize = 0;
		DWORD dwRetValue = 0;

		auto ipAddres = inet_addr(param.ping.IP);
		HANDLE hIP = IcmpCreateFile();	// создаем соединение с которым будем работать
		replySize = sizeof(ICMP_ECHO_REPLY) + sizeof(sendData);
		replyBuffer = (VOID*)malloc(replySize);
		IP_OPTION_INFORMATION option = { 255, 0, 0, 0, 0 };
		if (hIP == INVALID_HANDLE_VALUE)	// если не удалось создать
		{
			throw "Не удалось создать подключение.";
			WSACleanup();	// i?euaai iaiyou
			return;
		}
		cout << "Обмен пакетами с " << param.ping.IP << " размером " << sizeof(sendData) << " байт" << endl;
		for (int i = 0; i < param.ping.count; i++)
		{
			dwRetValue = IcmpSendEcho(hIP, ipAddres, sendData, sizeof(sendData), &option, replyBuffer, replySize, param.ping.timeout);
			if (dwRetValue > 0)
			{
				PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)replyBuffer;
				cout << "Ответ от " << param.ping.IP << " Время: " << pEchoReply->RoundTripTime << " мс." <<
					" Число байт: " << pEchoReply->DataSize << endl;
			}
			else
			{
				badEcho++;
				PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)replyBuffer;
				cout << "Превышен интервал ожидания" << endl;
			}
		}
		badPercent = (badEcho * 100) / param.ping.count;
		cout << "Статистика с " << param.ping.IP << endl;
		cout << "Пакетов отправлено: " << param.ping.count << ". Пакетов получено: " << param.ping.count - badEcho <<
			". Пакетов потеряно: " << badEcho << " (" << badPercent << "% потерь)" << endl;
		WSACleanup();
	}
	bool checkValidIP(char ip[255])
	{
		bool rc(true);
		char *buf = new char[4];
		int bufCount = 0, octet = 0, octetCount = 0;
		for (unsigned int i = 0; i < strlen(ip) && rc; i++)
		{
			if (ip[i] == '.')
			{
				buf[bufCount] = 0x00;
				octetCount++;
				octet = atoi(buf);
				if (octet > 255) rc = false;
				bufCount = 0;
			}
			else
			{
				if (ip[i] >= '0' && ip[i] <= '9') buf[bufCount++] = ip[i];
				else rc = false;
			}
		}
		if (octetCount!=3) rc = false;
		return rc;
	}
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       