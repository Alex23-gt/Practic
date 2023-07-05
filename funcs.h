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
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
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
#include <vector>
#include <utility>

namespace apc
{
	struct ThreadInfo
	{
		int pid;
		long Thread;
		std::string Path;
	};
	
	struct MemoryInfo
	{
		double TotalMem;
		double FreeMem;
		double Percent;
	};
	
	
	struct ProcThreadInfo
	{
		int pid;
		long Thread;
		std::string Path;
	};
	
	struct ProcMemoryInfo
	{
		int pid;
		long MemoryMB;
		std::string Path;
	};
	
	struct ProcSocketInfo
	{
		int NumSocket;
	};
	
	class SystemInfo
	{
	public:
		SystemInfo();
		char* DelSym(char* line_1);
		int IsPid(const struct dirent *entry);
		
		std::string GetUserInfo();
		std::string GetOSVersionInfo();
		std::string GetProcessorInfo();
		MemoryInfo GetMemoryInfo();
		std::string OutMemoryInfo(const MemoryInfo& myVec);
		std::string GetNetAdaptersInfo();
		std::string GetDriveInfo();
		std::string GetLanguageInfo();
		std::string GetDateInfo();
		std::string GetScreenInfo();
		std::vector<ThreadInfo> GetThreadsInfo();
		std::string OutThreadsInfo(const std::vector<ThreadInfo>& myVec);
		std::string GetSocketInfo();
		
		ProcThreadInfo GetProcThreadInfo(int pid);
		std::string OutProcThreadInfo (const ProcThreadInfo& myVec);
		ProcMemoryInfo GetProcMemoryInfo(int pid);
		std::string OutProcMemoryInfo(const ProcMemoryInfo& myVec);
		ProcSocketInfo GetProcSocketInfo(int pid);
		std::string OutProcSocketInfo(const ProcSocketInfo& myVec);
	};
}
