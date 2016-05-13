#pragma once
namespace _NS_RECHNUNG
{
#define _DELIMITER "@BS"

	class Parser
	{
		Parser();
	public:
		Parser(std::string & filePath);
		virtual ~Parser();
	};

}