#include "funcs.h"


using namespace apc;

char* SystemInfo::DelSym(char* line_1)
{
	bool del = true;
	int j = 0;
	while(del)
	{
		if(line_1[j] == '\n')
		{
			line_1[j] = ' ';
			del = false;
		}
		j++;
	}
	return line_1;
}

int SystemInfo::IsPid(const struct dirent *entry) {
    const char *p;
 
    for (p = entry->d_name; *p; p++) {
        if (!isdigit(*p))
            return 0;
    }
 
    return 1;
}

SystemInfo::SystemInfo()
{

}

std::string SystemInfo::GetUserInfo()
{
	std::string itog = "";
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);
	itog.append("Computer Name: ");
	itog.append(hostname);
	itog.append("\nUser Name: ");
	itog.append(username);
		
	int user = getuid();//Проверка на root-пользователя
	if(user==0)
	{
		itog.append("\nUser is root\n");
	}
	else
	{
		itog.append("\nUser is not root\n");
	}
		
	char *IP;//для записи IP host'a
	struct hostent *host_entry;
	host_entry = gethostbyname(hostname);
	IP = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
	itog.append("Host IP: ");
	itog.append(IP);
	itog.append("\n\n");
	
	return itog;
}

std::string SystemInfo::GetOSVersionInfo()
{
	std::string itog = "";
	itog.append("---OS Info---\n");
	int skipline = 4;
	char* line = new char[256];
	itog.append("OS Description: ");//вывод названия ОС
	FILE* f = fopen("/etc/lsb-release", "r");
	for(int i = 0; i < skipline; i++, fgets(line, 256, f));
	itog.append(strchr(line, '=') + 1);
	itog.append("\n");
	fclose(f);
	return itog;
}

std::string SystemInfo::GetProcessorInfo()
{
	std::string itog = "";
	itog.append("---Processors Info---\n");
	int skipline = 5;
	char* line = new char[256];
	FILE* f = fopen("/proc/cpuinfo", "r");
	for(int i = 0; i < skipline; i++, fgets(line, 256, f));
	line = DelSym(line);
	itog.append(strchr(line, ':') + 2);
	
	skipline = 7;
	itog.append("\nNumber of processors: ");//вывод числа процессоров
	for(int i = 0; i < skipline; i++, fgets(line, 256, f));
	line = DelSym(line);
	itog.append(strchr(line, ':') + 2);
	
	f = fopen("/proc/cpuinfo", "r");
	skipline = 2;
	itog.append("\nVendors ID: ");//Вывод идентификатора
	for(int i = 0; i < skipline; i++, fgets(line, 256, f));
	line = DelSym(line);
	itog.append(strchr(line, ':') + 2);
	
	skipline = 5;
	itog.append("\nFrequency: ~");//вывод частоты
	for(int i = 0; i < skipline; i++, fgets(line, 256, f));
	itog.append(strchr(line, ':') + 2);
	itog.append("\n");
	fclose(f);
	return itog;
}

MemoryInfo SystemInfo::GetMemoryInfo()
{
	MemoryInfo myVec;
	struct sysinfo info;
	sysinfo(&info);
	myVec.TotalMem = (double)info.totalram/(1024*1024*1024);
	myVec.FreeMem = (double)info.freeram/(1024*1024*1024);
	myVec.Percent = 100 * (double)info.freeram/(double)info.totalram;
	return myVec;
}

std::string SystemInfo::OutMemoryInfo(const MemoryInfo& myVec)
{
	std::string itog = "";
	itog.append("---Memory Info---\n");
	itog.append("Total amount of RAM: ");
	itog.append(std::to_string(myVec.TotalMem));
	itog.append(" GB\n");
	itog.append("Amount of free RAM: ");
	itog.append(std::to_string(myVec.FreeMem));
	itog.append(" GB\n");
	itog.append("Percent of free RAM: ");
	itog.append(std::to_string(myVec.Percent));
	itog.append(" %\n\n");
	return itog;
}

std::string SystemInfo::GetNetAdaptersInfo()
{
	std::string itog = "";
	itog.append("---Network Adapters Info--- \n");
	itog.append("Adapter Name: ");
	std::string strN = "basename /sys/class/net/enp*";
	const char *commandN = strN.c_str();
	FILE* FileOpen;
	char* line = new char[256];
	FileOpen = popen(commandN, "r");
	while(fgets(line, 256, FileOpen))
	{
		itog.append(line);
	}
	
	itog.append("MAC address: ");
	std::string str1 = "cat /sys/class/net/enp*/address";
	const char *command1 = str1.c_str();
	FileOpen = popen(command1, "r");
	while(fgets(line, 256, FileOpen))
	{
		itog.append(line);
	}
	
	itog.append("IP address: ");
	FileOpen = popen("hostname -I", "r");
	while(fgets(line, 256, FileOpen))
	{
		itog.append(line);
	}
	
	itog.append("\nAdapter Name: ");
	strN = "basename /sys/class/net/lo";
	commandN = strN.c_str();
	FileOpen = popen(commandN, "r");
	while(fgets(line, 256, FileOpen))
	{
		itog.append(line);
	}
	
	itog.append("MAC address: ");
	str1 = "cat /sys/class/net/lo/address";
	command1 = str1.c_str();
	FileOpen = popen(command1, "r");
	while(fgets(line, 256, FileOpen))
	{
		itog.append(line);
	}
	
	itog.append("\n");
	return itog;
}

std::string SystemInfo::GetDriveInfo()
{
	std::string itog = "";
	itog.append("---Disk Information---\n");
	FILE* FileOpen;
	char* line = new char[256];
	FileOpen = popen("df -h /dev/sda*", "r");
	while(fgets(line, 256, FileOpen))
	{
		itog.append(line);
	}
	itog.append("\n");
	return itog;
}

std::string SystemInfo::GetLanguageInfo()
{
	std::string itog = "";
	itog.append("---Language Info--- \n");
	itog.append("System language: ");
	itog.append(std::locale("").name());
	itog.append("\n");
	char* encoding = nl_langinfo(CODESET);
	itog.append("Encoding: ");
	itog.append(encoding);
	itog.append("\n\n");
	return itog;
}

std::string SystemInfo::GetDateInfo()
{
	std::string itog = "";
	itog.append("---Time Zone Info--- \n");
	time_t rawtime;
	struct tm *timeinfo;
	//struct tm *timeinfo1;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	itog.append("Data and time(Current): ");
	itog.append(asctime(timeinfo));
	timeinfo = gmtime(&rawtime);
	itog.append("Data and time(GMT): ");
	itog.append(asctime(timeinfo));
	itog.append("\n");
	return itog;
}

std::string SystemInfo::GetScreenInfo()
{
	std::string itog = "";
	itog.append("---Screen Info--- \n");
	FILE* FileOpen;
	char* line = new char[256];
	FileOpen = popen("xrandr | grep ' connected'", "r");
	while(fgets(line, 256, FileOpen))
	{
		itog.append(line);
	}
	itog.append("\n");
	return itog;
}

std::vector<ThreadInfo> SystemInfo::GetThreadsInfo()
{
	std::vector<ThreadInfo> myVec;
	DIR *procdir;
    FILE *fp;
	struct dirent *entry;
	char path[256 + 5 + 5];
	int pid;
	long threads;
	
	procdir = opendir("/proc");
	if (!procdir) 
	{
	    perror("opendir failed");
	}
	
	int iter = 0;
	while ((entry = readdir(procdir))) 
	{
	    if (!IsPid(entry))
	        continue;
	
	    snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);
	    fp = fopen(path, "r");
	
	    if (!fp) 
	    {
	        perror(path);
	        continue;
	    }
	
	    fscanf(fp, "%d %s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %ld",
	        &pid, &path, &threads
	    );
	
	    std::string path1(path);
	    
	    myVec.push_back(ThreadInfo());
	    myVec[iter].pid = pid;
	    myVec[iter].Path = path1;
	    myVec[iter].Thread = threads;
	    
	    iter++;
	    fclose(fp);
	}
	return myVec;
}

std::string SystemInfo::OutThreadsInfo(const std::vector<ThreadInfo>& myVec)
{
	std::string itog = "";
	itog.append("---Threads Info---\n");
	for(auto& a : myVec)
	{
		itog.append(std::to_string(a.pid));
		itog.append(" ");
		itog.append(a.Path);
		itog.append(": ");
		itog.append(std::to_string(a.Thread));
		itog.append("\n");
	}
	return itog;
}

std::string SystemInfo::GetSocketInfo()
{
	std::string itog = "";
	itog.append("---Sockets Info--- \n");
	itog.append("TCP Sockets:\n");
	std::ifstream fin("/proc/net/tcp");
	std::string strbuf;
	
	while(!fin.eof())
	{
		getline(fin, strbuf);
		itog += strbuf;
		if(!fin.eof())
		{
			itog += '\n';
		}
	}
	
	itog.append("UDP Sockets:\n");
	std::ifstream fin1("/proc/net/udp");
	
	while(!fin1.eof())
	{
		getline(fin1, strbuf);
		itog += strbuf;
		if(!fin1.eof())
		{
			itog += '\n';
		}
	}
	return itog;
}


ProcThreadInfo SystemInfo::GetProcThreadInfo(int pid)
{
	ProcThreadInfo myVec;
	DIR *procdir;
    FILE *fp;
	struct dirent *entry;
	char path[256 + 5 + 5]; // d_name + /proc + /stat
	//int pid;
	long threads;
	
	procdir = opendir("/proc");
	if (!procdir) 
	{
	    perror("opendir failed");
	}
	
	std::string cur_dir = "/proc/";
	cur_dir += std::to_string(pid);
	cur_dir += "/stat";
	const char* cur_dir1 = cur_dir.c_str();
	
	snprintf(path, sizeof(path), cur_dir1);
	fp = fopen(path, "r");
	
	fscanf(fp, "%d %s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %ld",
	        &pid, &path, &threads
	    );
	
	std::string path1(path);
	    
	myVec.pid = pid;
	myVec.Path = path1;
	myVec.Thread = threads;
	fclose(fp);
	return myVec;
}

std::string SystemInfo::OutProcThreadInfo (const ProcThreadInfo& myVec)
{
	std::string itog = "";
	itog.append("---Process Threads Info---\n");
	itog.append(std::to_string(myVec.pid));
	itog.append(" ");
	itog.append(myVec.Path);
	itog.append(": ");
	itog.append(std::to_string(myVec.Thread));
	itog.append("\n\n");
	return itog;
}
		
ProcMemoryInfo SystemInfo::GetProcMemoryInfo(int pid)
{
	ProcMemoryInfo myVec;
	DIR *procdir;
    FILE *fp;
	struct dirent *entry;
	char path[256 + 5 + 5]; // d_name + /proc + /stat
	//int pid;
	long ram;
	
	procdir = opendir("/proc");
	if (!procdir) 
	{
	    perror("opendir failed");
	}
	
	std::string cur_dir = "/proc/";
	cur_dir += std::to_string(pid);
	cur_dir += "/stat";
	const char* cur_dir1 = cur_dir.c_str();
	
	snprintf(path, sizeof(path), cur_dir1);
	fp = fopen(path, "r");
	
	fscanf(fp, "%d %s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %*ld %*ld %*llu %*lu %ld",
	    &pid, &path, &ram
	);
	
	long page_size_kb = sysconf(_SC_PAGE_SIZE)/1024;
	std::string path1(path);
	
	myVec.pid = pid;
	myVec.Path = path1;
	myVec.MemoryMB = ram * page_size_kb / 1024;
	fclose(fp);
	return myVec;
}

std::string SystemInfo::OutProcMemoryInfo(const ProcMemoryInfo& myVec)
{
	std::string itog = "";
	itog.append("---Process Memory Info---\n");
	itog.append(std::to_string(myVec.pid));
	itog.append(" ");
	itog.append(myVec.Path);
	itog.append(": ");
	itog.append(std::to_string(myVec.MemoryMB));
	itog.append("\n\n");
	return itog;
}

ProcSocketInfo SystemInfo::GetProcSocketInfo(int pid)
{
	ProcSocketInfo myVec;
	//int pid = getpid();
	char path[256];
	snprintf(path, sizeof(path), "/proc/%d/net/sockstat", pid);
	
	FILE* file = fopen(path, "r");
	char line[256];
	int numSockets = 0;
	
	while(fgets(line, sizeof(line), file) != NULL)
	{
		if(strncmp(line, "sockets:", 8) == 0)
		{
			sscanf(line + 8, "%d %d %d %d %d", &numSockets);
			break;
		}
	}
	
	myVec.NumSocket = numSockets;
	fclose(file);
	return myVec;
}

std::string SystemInfo::OutProcSocketInfo(const ProcSocketInfo& myVec)
{
	std::string itog = "";
	itog.append("---Process Sockets Info---\n");
	itog.append("Number of sockets used in proccess: ");
	itog.append(std::to_string(myVec.NumSocket));
	itog.append("\n\n");
	return itog;
}
