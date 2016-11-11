#include "stdafx.h"
#include "Parm.hpp"
#include "Ping.hpp"
#include "Id.hpp"
#define MAX_SIZE_OF_BUFFER 255
int Find(int argc, char** argv, char* parm, char* &buf)
{
	int i(0);
	while ((i < argc) && !strstr(argv[i], parm)) i++;
	if (i < argc) strcpy(buf, argv[i]);
	return i < argc? i : -1;
}
namespace Parm
{
	PARM getParm(int argc, char **argv)
	{
	  PARM param;
	  bool isMask = 0;
	  int parm_ip_size = strlen(PARM_IP),  i(0);
	  if (argc == 1) throw "Параметры отсутствуют.";
	  char* buf = new char[MAX_SIZE_OF_BUFFER];
	  if (!strcmp(argv[1], PARM_PING))
	  {
	      i= Find(argc, argv, PARM_IP, buf);
	      if (i > 0)//strstr(buf, PARM_IP))
	      {
	         strcpy(buf, argv[i] + strlen(PARM_IP));
	         if (!Ping::checkValidIP(buf)) throw "Вы ввели неправильный ip адрес";
	         strcpy(param.ping.IP, buf);
	         param.ping.count = 10; // инициализация по умолчанию
	         param.ping.timeout = 1000;
	      }
	      i = Find(argc, argv, PARM_TIME_OUT, buf);		//else if (strstr(buf, PARM_TIME_OUT))
	      if (i > 0)
	      {
	      	strcpy(buf, argv[i] + strlen(PARM_TIME_OUT));
	      	param.ping.timeout = atoi(buf);
	      }
	      i = Find(argc, argv, PARM_COUNT, buf);
	      if (i > 0)
	      {
	      	 strcpy(buf, argv[i] + strlen(PARM_COUNT));
	      	 param.ping.count = atoi(buf);
	      }
	  }
	  else if (!strcmp(argv[1], PARM_ID))
	  {
		  i = Find(argc, argv, PARM_MASK, buf);
		  if (i > 0)
		  {
			  strcpy(buf, argv[i] + strlen(PARM_MASK));
			  if (!Id::isValidMask(buf)) throw "Вы ввели неправильную маску подсети";
			  strcpy(param.id.MASK, buf);
		  }
		  i = Find(argc, argv, PARM_IP, buf);
		  if (i > 0)//strstr(buf, PARM_IP))
		  {
			  strcpy(buf, argv[i] + strlen(PARM_IP));
			  if (!Ping::checkValidIP(buf)) throw "Вы ввели неправильный ip адрес";
			  strcpy(param.id.IP, buf);
		  }
	  }
	  return param;
	}
}