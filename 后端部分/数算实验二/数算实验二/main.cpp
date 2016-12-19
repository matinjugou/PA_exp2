
#include "stdafx.h"
#include "Functions.h"

int main(int argc, char* argv)
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	if (argc > 1)
		work(1);
	else
		work(0);
	return 0;
}