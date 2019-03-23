#include <string>
#include "boost\filesystem.hpp"
#pragma once

class CConfig
{
	static CConfig*         m_instance;
	boost::filesystem::path m_ExePath;

	CConfig();
public:
	static CConfig* GetInstance();
	void   LoadConfig(const std::string&);

	boost::filesystem::path GetExePath() { return m_ExePath; }

	~CConfig() = delete;
};

