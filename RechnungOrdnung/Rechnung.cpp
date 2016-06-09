#include <iostream>
#include <sstream>
#include "Rechnung.h"

namespace _NS_RECHNUNG
{
	Rechnung::Rechnung()
	{
	}


	Rechnung::Rechnung(KEY_RECHNUNG rhsNummer)
		: numRechnung(rhsNummer)
	{
	}

	Rechnung::~Rechnung()
	{
	}

	bool RechnungMgr::CreateRechnung(KEY_RECHNUNG numRechnung)
	{		
		/* Integrity Test Required */
		_cont.insert_or_assign(numRechnung, Rechnung(numRechnung));
		return false;
	}

	//1mal 17052016 passt, 
	inline bool RechnungMgr::ReportInvalidRechnungNummer()
	{

		KEY_RECHNUNG lastNummer( INVALID_RECHNUNGNUMMER );
		for each(auto& cur in this->_cont)
		{
			KEY_RECHNUNG curNummer(cur.first),
						tmpNummer(lastNummer);
			lastNummer = curNummer;
			if (tmpNummer == INVALID_RECHNUNGNUMMER
				|| tmpNummer == curNummer //Worked
				)
				continue;
			
			int nDiff = abs(tmpNummer - curNummer);
			
			if (1 < nDiff)
			{
				while (--nDiff != 0)
					std::cout << ++tmpNummer << ',';
				
				std::cout << std::endl;
			}
		}
		return true;
	}

	bool RechnungMgr::ReportInvalidRechnungNummerSStream()
	{
		KEY_RECHNUNG lastNummer( INVALID_RECHNUNGNUMMER );
		std::stringstream ssOut;
		for each(auto& cur in this->_cont)
		{
			KEY_RECHNUNG curNummer(cur.first),
						tmpNummer(lastNummer);
			lastNummer = curNummer;
			if (tmpNummer == INVALID_RECHNUNGNUMMER
				|| tmpNummer == curNummer //Worked
				)
				continue;
			
			int nDiff = abs(tmpNummer - curNummer);
			
			if (1 < nDiff)
			{
				while (--nDiff != 0)
					ssOut << ++tmpNummer << ',';
				
				ssOut << std::endl;
			}
		}

		std::cout << ssOut.str() << std::endl;
		return true;
	}

	bool RechnungMgr::ReportInvalidRechnungNummer(RechnungReport & outReport)
	{
		return false;
	}

	bool RechnungMgr::DoTest(Tester &)
	{
		int LoopCnt( rand()+10 );
		while( --LoopCnt )
		{
			CreateRechnung(LoopCnt);
		}
		ReportInvalidRechnungNummer();
		_cont.clear();
		return false;
	}

	bool RechnungMgr::AddRechnung(Rechnung & rechnung)
	{
		KEY_RECHNUNG rechnungNummer = rechnung.GetRechnungNummer();
		
		// nexte Zeit wöllen diesem Rechnung wird Doppel, z.b. 3 Rechnungen haben 1 Rechnung Nummer.
		_cont.insert_or_assign( rechnungNummer, rechnung );
		return false;
	}
	
	void Tester::operator()()
	{
		//wir brauchen GetTestInstance() nur für testen.
		RechnungMgr::GetInstance().DoTest(*this);
	}
}