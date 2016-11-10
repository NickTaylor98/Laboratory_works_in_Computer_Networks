#pragma once
#define PARM_MAX_SIZE 20
#define PARM_PING		"ping"
#define PARM_IP			"-ip:"
#define PARM_TIME_OUT	"-t:"
#define PARM_COUNT		"-n:"
namespace Parm
{
	struct PARM
	{
		struct PING
		{
			char IP[PARM_MAX_SIZE];
			int timeout;
			int count;
		} ping;
		struct ID
		{
			char IP[PARM_MAX_SIZE];
			char MASK[PARM_MAX_SIZE];
			char MAC[PARM_MAX_SIZE];
		} id;
	};
	PARM getParm(int argc, char ** argv);
}