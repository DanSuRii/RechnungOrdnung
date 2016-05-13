#include <iostream>
#include "Rechnung.h"
#include "Parser.h"

bool Question(std::string& strQuestion )
{
	char Answer('N');
	std::cout << strQuestion.c_str() << "[Y/N]:";
	std::cin >> Answer;

	return Answer == 'Y' || Answer == 'y';
}

int main(int argc, const char* argv[ ])
{
	/*
	_NS_RECHNUNG::Tester _tester;
	_NS_RECHNUNG::Rechnung rechnung(32);
	_tester();
	*/
	int nCnt = argc;

	std::map< int, std::string > mapParam;
	while (--nCnt != 0)
		mapParam.insert_or_assign(nCnt, std::string( argv[nCnt] ) );

	for each(auto& cur in  mapParam)
		std::cout << cur.first << ".\t" << cur.second.c_str() << std::endl;
	
	std::string strPath("C:\\Users\\A.Roennburg\\Documents\\052016 TagesAbschlüss PROGRAMMING\\OLDH60503.DAT");
	if (mapParam.count(1) <= 0)
	{
		if ( false == Question( std::string( "Use Default path?") ) )
			return -1;
	}
	else
		strPath = mapParam.at(1);
	

	_NS_RECHNUNG::Parser parser(strPath);
	_NS_RECHNUNG::RechnungMgr::GetInstance().ReportInvalidRechnungNummer();
	system("pause");
}