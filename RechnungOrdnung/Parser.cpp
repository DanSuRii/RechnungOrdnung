#include <string>
#include <fstream>

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
	Parser::Parser(  )
	{
		const char* szFilePath = "C:\\Users\\A.Roennburg\\Documents\\052016 TagesAbschlüss PROGRAMMING\\OLDH60503.DAT";
		std::ifstream ifs(szFilePath);

		if ( !ifs.is_open() )
		{
			//Reise Exception
			return;
		}
		std::string strTmp;
		std::string strCmp(_DELIMITER);

		int nRechnungNummer(INVALID_RECHNUNGNUMMER);
		
		//initialize PropCur, nexte InitProperty() für die Initialize,mit enum EPROPERTY_INIT
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
			
			propCur = EPROPERTY( int(propCur) + 1 );
			/* if, eProperty == INVALID Create Rechnung und Add here, and skip to next Delimiter*/
			/*LOGIC */
			if (propCur == EPROPERTY::RechnungNummer)
			{
				int nTempNummer(nRechnungNummer);
				nRechnungNummer = stoi(strTmp);
				if (nTempNummer == INVALID_RECHNUNGNUMMER)
					continue;

				//nTempNummer must be lesser then nRechnungNummer, Noch nicht Stimmen
				//Nach dem alle Logic stimmen, es will STIMMEN
				int nDifference = abs(nTempNummer - nRechnungNummer);
				if (1 < nDifference)
				{
					while (--nDifference != 0)
						std::cout << ++nTempNummer << ',' ;

					std::cout << std::endl;
				}
			}
		}
	}

	Parser::~Parser()
	{
	}
}