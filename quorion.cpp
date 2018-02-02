#include "quorion.h"
#include <stdio.h>
#include <string.h>

namespace Quorion {

	Quorion::Quorion() {}

	Quorion::~Quorion() {}

	int Quorion::__HelloWorld(char* name, char* resp)
	{
		int i = 0;
		while (*name != '\0')
		{
			i++;
			name++;
		}
		char* nameManArr = new char[i];
		name -= i;
		i = 0;
		while (*name != '\0')
		{
			nameManArr[i] = *name;
			name++;
			i++;
		}
		nameManArr[i] = '\0';
		name -= i;

		strncpy(resp, nameManArr, i);
		return i;
	}
}
