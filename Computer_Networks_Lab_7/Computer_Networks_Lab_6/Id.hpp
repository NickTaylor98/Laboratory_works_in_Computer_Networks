#pragma once
#include "Parm.hpp"
namespace Id
{
	struct Octet
	{
		char* octet;
		int value_of_octet;
		Octet(char* arr);
		Octet();
	};
	bool isValidMask(char mask[255]);
	void IDs(Parm::PARM parm);
}