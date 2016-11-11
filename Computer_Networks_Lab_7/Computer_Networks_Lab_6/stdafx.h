#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <WinSock2.h>
#include <IPHlpApi.h>
#include <IcmpAPI.h>
#include <Ws2tcpip.h> 
#include <stdlib.h>
#include <stdio.h>


#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

using namespace std;