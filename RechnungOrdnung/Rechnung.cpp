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

	inline bool RechnungMgr::ReportInvalidRechnungNummer()
	{
		for each(auto& cur in this->_cont)
		{
			printf("%d", cur.first);
		}
		return true;
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
	
	void Tester::operator()()
	{
		//wir brauchen GetTestInstance() nur für testen.
		RechnungMgr::GetInstance().DoTest(*this);
	}
}