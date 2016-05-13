#include <string>
#include <fstream>
#include <algorithm>
// template include for use std::cout. will be delete.
#include <iostream>

#include "Parser.h"
#include "Rechnung.h"


namespace _NS_RECHNUNG
{
	enum EPROPERTY 
	{
#undef RECHNUNG_PROP
#define RECHNUNG_PROP(x) x,
#include "RechnungProperties.h"
		EPROPERTY_CNT = INVALID,
		EPROPERTY_INIT = Delimitor,
	};


	const struct PROPERTY
	{
		EPROPERTY	eProperty;
		std::string strName;
		//type;
		int			nLen;
		size_t		nArrayLen;

		PROPERTY(const char* szName, EPROPERTY eProp)
			: strName(szName)
			, eProperty(eProp)
		{}
	} PropertyTree[] = {
		//{},
#undef RECHNUNG_PROP
#define RECHNUNG_PROP(x) {#x, x},
#include "RechnungProperties.h"
#if 0
		{"Delimitor", std::string},
		{"Unbekannt", int, 3},
		{"Unbekannt2", std::string },
		{"RechnungNummer", int, 6},
		{"RechnungDatum", time_t},
#endif // 0		
	};
	Parser::Parser( std::string& filePath )
	{
		//const char* szFilePath = "C:\\Users\\A.Roennburg\\Documents\\052016 TagesAbschlüss PROGRAMMING\\OLDH60503.DAT";
		std::ifstream ifs(filePath);

		if ( !ifs.is_open() )
		{
			std::cout << "invalid file path:" << filePath << std::endl;
			//Reise Exception
			exit(-1);
			return;
		}
		std::string strTmp;
		std::string strCmp(_DELIMITER);

		int nRechnungNummer(INVALID_RECHNUNGNUMMER);
		
		//initialize PropCur, nexte InitProperty() für die Initialize,mit enum EPROPERTY_INIT
		std::string arrRechInitList[EPROPERTY_CNT];
		EPROPERTY propCur(EPROPERTY::EPROPERTY_INIT);
		while ( !std::getline(ifs, strTmp, '\n').eof() )
		{			
			if (strTmp == strCmp)
			{
				propCur = EPROPERTY::EPROPERTY_INIT;
				continue;
			}
			if (propCur == EPROPERTY::INVALID) 
				continue;
			
			//작성중인 Rechnung 이 완성되기 전에 tmp에 걸리는 경우
			propCur = EPROPERTY( int(propCur) + 1 );
			/* if, eProperty == INVALID Create Rechnung und Add here, and skip to next Delimiter*/
			if (EPROPERTY::EPROPERTY_CNT > propCur  )
			{
				arrRechInitList[propCur] = strTmp;
			}
			else
			{
				//if arrRechInitList[EPROPERTY::RechnungNummer] == std::to_string(INVALID_RECHNUNGNUMMER)
				//reinit
				Rechnung rechnung(
					stoi(arrRechInitList[EPROPERTY::RechnungNummer])
					//, arrRechInitList[]
				);

				RechnungMgr::GetInstance().AddRechnung(rechnung);

				for each(std::string& curStr in arrRechInitList)
					curStr.clear();
				
			}
		}
	}

	Parser::~Parser()
	{
	}
}