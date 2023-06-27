#include "funcs.cpp"





int main()
{
		SystemInfo tst;		
		std::string otvet = "";
		std::string otvet1 = "";
		system("clear");
		otvet.append("***System Info***\n\n");
		
		//-------Раздел вывода имен компьютера и пользователя--------
		
		otvet.append(tst.GetUserInfo());
		
		//---------------------Раздел вывода версии ОС-------------------
		
		otvet.append(tst.GetOSVersionInfo());
		
		//--------------Раздел вывода информации о процессоре----------------
		
		otvet.append(tst.GetProcessorInfo());
		
		//------------------Вывод информации о памяти--------------------
		
		otvet.append(tst.GetMemoryInfo());
		
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
		
		
		otvet1.append(tst.GetThreadsInfo());
		otvet1.append(tst.GetProcMemInfo());
		otvet1.append(tst.GetSocketInfo());
		
		std::cout << otvet1;
		
		pid_t pid, ppid;
		
		pid = getpid();
		ppid = getppid();
		
		//printf("PID: %d\n", pid);
		//printf("PPID: %d\n", ppid);
			
		
}
