#include "funcs.h"
#include <iostream>
#include <cstdio>
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
#include <locale.h>
#include <langinfo.h>
#include <X11/Xlib.h>
#define XLIB_ILLEGAL_ACCESS

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
void SystemInfo::Names()
{
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);
	printf("Computer Name: %s\n"
		"User Name: %s\n",
		hostname,
		username);
		
	int user = getuid();//Проверка на root-пользователя
	if(user==0)
	{
		printf("User is root\n");
	}
	else
	{
		printf("User is not root\n");
	}
		
	char *IP;//для записи IP host'a
	struct hostent *host_entry;
	host_entry = gethostbyname(hostname);
	IP = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
	printf("Host IP: %s\n\n", IP);
}
void SystemInfo::Version()
{
	printf("---OS Info---\n");
	int skipline = 4;
	char line[256];
	printf("OS Description: ");//вывод названия ОС
	FILE* f = fopen("/etc/lsb-release", "r");
	for(int i = 0; i < skipline; i++, fgets(line, 256, f));
	puts(strchr(line, '=') + 1);
	fclose(f);
}
void SystemInfo::Processors()
{
	printf("---Processors Info---\n");
	int skipline_1 = 5;
	char* line_1 = new char[256];
	FILE* f1 = fopen("/proc/cpuinfo", "r");
	for(int i = 0; i < skipline_1; i++, fgets(line_1, 256, f1));
	line_1 = DelSym(line_1);
	puts(strchr(line_1, ':') + 2);
	
	skipline_1 = 7;
	printf("Number of processors: ");//вывод числа процессоров
	for(int i = 0; i < skipline_1; i++, fgets(line_1, 256, f1));
	line_1 = DelSym(line_1);
	puts(strchr(line_1, ':') + 2);
	
	f1 = fopen("/proc/cpuinfo", "r");
	skipline_1 = 2;
	printf("Vendors ID: ");//Вывод идентификатора
	for(int i = 0; i < skipline_1; i++, fgets(line_1, 256, f1));
	line_1 = DelSym(line_1);
	puts(strchr(line_1, ':') + 2);
	
	skipline_1 = 5;
	printf("Frequency: ~");//вывод частоты
	for(int i = 0; i < skipline_1; i++, fgets(line_1, 256, f1));
	puts(strchr(line_1, ':') + 2);
	fclose(f1);
}
void SystemInfo::Memory()
{
	printf("---Memory Info---\n");
	struct sysinfo info;
	sysinfo(&info);//по сути, обращение к файлу meminfo
	printf("Total amount of RAM: %.3lf GB\n", (double)info.totalram/(1024*1024*1024));//Весь объем оперативки
	printf("Amount of free RAM: %.3lf GB\n", (double)info.freeram/(1024*1024*1024));//Свободная оперативка
	double perc = (double)info.freeram/(double)info.totalram;//для хранения процента свободной оперативки
	printf("Percent of free RAM: %.1lf % \n", perc * 100);
	printf("\n");
}
void SystemInfo::Adapters()
{
	printf("---Network Adapters Info--- \n");
	printf("Adapter Name: \n");
	string strN = "basename /sys/class/net/enp*";
	const char *commandN = strN.c_str();
	system(commandN);
	printf("MAC address: \n");
	string str1 = "cat /sys/class/net/enp*/address";
	const char *command1 = str1.c_str();
	system(command1);
	printf("IP address: \n");
	system("hostname -I");
	
	printf("\nAdapter Name: \n");
	strN = "basename /sys/class/net/lo";
	commandN = strN.c_str();
	system(commandN);
	printf("MAC address: \n");
	str1 = "cat /sys/class/net/lo/address";
	command1 = str1.c_str();
	system(command1);
	printf("\n");
}
void SystemInfo::Discs()
{
	printf("---Disk Information---\n");
	system("df -h /dev/sda*");
	printf("\n");
}
void SystemInfo::Language()
{
	printf("---Language Info--- \n");
	cout << "System language: " << locale("").name() << endl;
	char* encoding = nl_langinfo(CODESET);
	printf("Encoding: %s\n\n", encoding);
}
void SystemInfo::Data()
{
	printf("---Time Zone Info--- \n");
	time_t rawtime;
	struct tm *timeinfo;
	struct tm *timeinfo1;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("Data and time(Current): %s", asctime(timeinfo));
	timeinfo = localtime(&rawtime);
	timeinfo1 = gmtime(&rawtime);
	printf("Data and time(GMT): %s\n", asctime(timeinfo1));
}
void SystemInfo::Screen()
{
	printf("---Screen Info--- \n");
	system("xrandr | grep ' connected'");
}
