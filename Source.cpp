#define _WIN32_DCOM

#include <windows.h>
#include <rpcsal.h>
#include <gameux.h>
#include <strsafe.h>
#include <shlobj.h>
#include <wbemidl.h>
#include <objbase.h>
#include <string>
#include <vector>
#include "FirewallInstallHelper.h"

//#pragma comment(lib, "FirewallInstallHelper.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


template <typename List>
void split(const std::string & s, const std::string & delim, List & result)
{
	result.clear();

	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
}

int main(int argc, char * argv[])
{
	std::vector<std::string> commands;
	for (int i = 1; i < argc; ++i)
	{
		commands.push_back(argv[i]);
	}

	if (commands.size() < 1)
	{
		return -1;
	}

	std::string fullpath;
	std::string friend_name;

	if (commands[0] == "-friend")
	{
		if (commands.size() < 3)
		{
			return -1;
		}
		friend_name = commands[1];
		fullpath = commands[2];
	}
	else
	{
		fullpath = commands[0];
		if (commands.size() >= 3)
		{
			if (commands[1] != "-friend")
			{
				return -1;
			}
			friend_name = commands[2];
		}
		else
		{
			friend_name = fullpath;
		}
	}

	HRESULT hr = AddApplicationToExceptionListA(fullpath.c_str(), friend_name.c_str());
	if (FAILED(hr))
	{
		return -1;
	}

	return 0;
}


