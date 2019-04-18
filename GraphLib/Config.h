#include <string>
#include "boost\filesystem.hpp"
#pragma once

class CConfig
{ //Singleton class to store configuration.
	static CConfig*         m_instance;
	boost::filesystem::path m_ExePath;
	boost::filesystem::path m_DotExe;

	CConfig();
public:
	static CConfig* GetInstance();
	void   LoadConfig(const std::string&);

	boost::filesystem::path GetExePath() { return m_ExePath; }
	boost::filesystem::path GetDotPath() { return m_DotExe;  }
	~CConfig() = delete;
};

