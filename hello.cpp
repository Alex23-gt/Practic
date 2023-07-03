#include "funcs.cpp"

int main()
{
		SystemInfo tst;		
		std::string otvet = "";
		std::string otvet1 = "";
		
		int pid;
		
		std::cout << "Enter the process ID: ";
		std::cin >> pid;
		
		system("clear");
		otvet.append("***System Info***\n\n");
		
		//-------Раздел вывода имен компьютера и пользователя--------
		
		otvet.append(tst.GetUserInfo());
		
		//---------------------Раздел вывода версии ОС-------------------
		
		otvet.append(tst.GetOSVersionInfo());
		
		//--------------Раздел вывода информации о процессоре----------------
		
		otvet.append(tst.GetProcessorInfo());
		
		//------------------Вывод информации о памяти--------------------
		
		const MemoryInfo memory = tst.GetMemoryInfo();
		otvet.append(tst.OutMemoryInfo(memory));
		
		//------------Вывод информации о сетевых адаптерах-----------------
		
		otvet.append(tst.GetNetAdaptersInfo());
		
		//----------------Вывод информации о дисках---------
		
		otvet.append(tst.GetDriveInfo());
		
		//----------------Вывод информации о языке---------------
		
		otvet.append(tst.GetLanguageInfo());
		
		//-------------Вывод информации о дате и времени---------------
		
		otvet.append(tst.GetDateInfo());
		
		//-------------Вывод информации об экране---------------
		
		otvet.append(tst.GetScreenInfo());
		
		//const std::vector<ThreadInfo> threads = tst.GetThreadsInfo();
		//otvet1.append(tst.OutThreadsInfo(threads));
		
		
		
		if(pid == 0)
			pid = getpid();
		
		
		const ProcThreadInfo ProcThr = tst.GetProcThreadInfo(pid);
		otvet1.append(tst.OutProcThreadInfo(ProcThr));
		
		const ProcMemoryInfo ProcMem = tst.GetProcMemoryInfo(pid);
		otvet1.append(tst.OutProcMemoryInfo(ProcMem));
		
		const ProcSocketInfo ProcSoc = tst.GetUsedSocketForProcess(pid);
		otvet1.append(tst.OutUsedSocketForProcess(ProcSoc));
		
		std::cout << otvet;
		std::cout << otvet1;
}
