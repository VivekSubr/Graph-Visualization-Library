#include "Config.h"
#include "json.hpp"
#include "boost/dll.hpp"
using std::string;
using json   = nlohmann::json;
namespace fs = boost::filesystem;

CConfig* CConfig::m_instance = nullptr;

CConfig::CConfig():m_ExePath(boost::dll::program_location().parent_path())
{
	LoadConfig((m_ExePath / "config.json").string());
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
	std::ifstream fConfig(sConfigFile);
    json jConfig = json::parse(fConfig);

    string temp = jConfig.at("dotpath"); //hack to get this working, tofix
	m_DotExe    = fs::path(temp);
}
