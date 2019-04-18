#include "..\Graph.h"
#include "boost\filesystem.hpp"
#include "boost\process.hpp"
#pragma once

enum class ImageType { JPG };

class CDotFacade
{ //Facade for dot.exe, using boost::process
	boost::process::opstream  m_Write;
	boost::process::child     m_Plot;
public:
	CDotFacade();
	boost::filesystem::path WriteDot(CGraph&);
	boost::filesystem::path CreateImage(CGraph&, ImageType);

	~CDotFacade();
};

