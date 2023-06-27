#include <iostream>
#include <cstdio>
#include <ctype.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fstream>
#include <string>
#include <cstring>//для strchr
#include <inttypes.h>//для вывода %
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <ctime>
#include <locale.h>
#include <langinfo.h>
#include <thread>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

namespace apc
{
	class SystemInfo
	{
	public:
		SystemInfo();
		char* DelSym(char* line_1);//вспомогательная функция
		int is_pid_folder(const struct dirent *entry);
		
		std::string GetUserInfo();
		std::string GetOSVersionInfo();
		std::string GetProcessorInfo();
		std::string GetMemoryInfo();
		std::string GetNetAdaptersInfo();
		std::string GetDriveInfo();
		std::string GetLanguageInfo();
		std::string GetDateInfo();
		std::string GetScreenInfo();
		std::string GetThreadsInfo();
		std::string GetProcMemInfo();
		std::string GetSocketInfo();
	};
}
