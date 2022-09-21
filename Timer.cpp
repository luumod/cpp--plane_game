#include "Timer.h"

bool Timer(int id, int ms)
{
	static DWORD t[100];		//100¸ö¼ÆÊ±Æ÷
	if (clock() - t[id] > ms) {
		t[id] = clock();
		return true;
	}
	return false;
}