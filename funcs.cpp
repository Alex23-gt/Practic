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
	int skipline_1 = 5;
	char* line_1 = new char[256];
	FILE* f1 = fopen("/proc/cpuinfo", "r");
	for(int i = 0; i < skipline_1; i++, fgets(line_1, 256, f1));
	line_1 = DelSym(line_1);
	itog.append(strchr(line_1, ':') + 2);
	
	skipline_1 = 7;
	itog.append("\nNumber of processors: ");//вывод числа процессоров
	for(int i = 0; i < skipline_1; i++, fgets(line_1, 256, f1));
	line_1 = DelSym(line_1);
	itog.append(strchr(line_1, ':') + 2);
	
	f1 = fopen("/proc/cpuinfo", "r");
	skipline_1 = 2;
	itog.append("\nVendors ID: ");//Вывод идентификатора
	for(int i = 0; i < skipline_1; i++, fgets(line_1, 256, f1));
	line_1 = DelSym(line_1);
	itog.append(strchr(line_1, ':') + 2);
	
	skipline_1 = 5;
	itog.append("\nFrequency: ~");//вывод частоты
	for(int i = 0; i < skipline_1; i++, fgets(line_1, 256, f1));
	itog.append(strchr(line_1, ':') + 2);
	itog.append("\n");
	fclose(f1);
	return itog;
}
std::string SystemInfo::GetMemoryInfo()
{
	std::string itog = "";
	itog.append("---Memory Info---\n");
	struct sysinfo info;
	sysinfo(&info);
	itog.append("Total amount of RAM: ");
	itog.append(std::to_string((double)info.totalram/(1024*1024*1024)));
	itog.append(" GB\n");
	itog.append("Amount of free RAM: ");
	itog.append(std::to_string((double)info.freeram/(1024*1024*1024)));
	itog.append(" GB\n");
	double perc = 100 * (double)info.freeram/(double)info.totalram;
	itog.append("Percent of free RAM: ");
	itog.append(std::to_string(perc));
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
