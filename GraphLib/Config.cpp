#include "Config.h"
#include "json.hpp"
#include "boost/dll.hpp"
using std::string;

CConfig* CConfig::m_instance = nullptr;

CConfig::CConfig():m_ExePath(boost::dll::program_location().parent_path())
{
}

CConfig* CConfig::GetInstance()
{
	if (m_instance) return m_instance;
	else
	{
		return m_instance = new CConfig();
	}
}

void CConfig::LoadConfig(const string& sConfigFile)
{

}
