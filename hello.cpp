#include "funcs.cpp"


int main()
{
SystemInfo tst;
//bool flag = true;
//char ch='y';
//while(flag)
//	{
//	if(ch=='y')
//	{
		std::string otvet = "";
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
		
		std::cout << otvet << std::endl;
		
		return 0;
		
		
		
		//cout << "Update?(y - yes, another key - no): ";
		//cin >> ch;
	//}
	//else
	//{
	//	flag = false;
	//}
//}
}
