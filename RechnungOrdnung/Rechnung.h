#pragma once
#include <map>

namespace _NS_RECHNUNG
{
	class Rechnung;
	class Tester;

	typedef int									KEY_RECHNUNG;
	typedef std::map<KEY_RECHNUNG, Rechnung>	CONT_RECHNUNG;
	enum {INVALID_RECHNUNGNUMMER = -1};

	class Rechnung
	{
		KEY_RECHNUNG numRechnung;
		Rechnung();
	
	public:
		Rechnung(KEY_RECHNUNG rhsNummer);
		virtual ~Rechnung();

		__inline KEY_RECHNUNG GetRechnungNummer() const { return numRechnung; }
	};


	
	class RechnungMgr
	{
	public:
		_inline static RechnungMgr& GetInstance(){
			static RechnungMgr _Instance; 
			return _Instance;
		}				
		
		bool ReportInvalidRechnungNummer( /*out list*/);		
		bool DoTest(Tester&);
		bool AddRechnung( Rechnung& );

	private:
		CONT_RECHNUNG _cont;
		RechnungMgr() { }

		/* Alle Rechnung haben UNIQUE Rechnung nummer */
		bool CreateRechnung(KEY_RECHNUNG numRechnung);
	};

	class Tester
	{
	public:
		void operator()();
	};
}