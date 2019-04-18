#include "..\Graph.h"
#include "boost\filesystem.hpp"
#pragma once

enum class ImageType { JPG };

class CDotFacade
{ //Facade for dot.exe, using boost::process
public:
	CDotFacade() = default;

	boost::filesystem::path WriteDot(CGraph&);
	boost::filesystem::path CreateImage(CGraph&, ImageType);

	~CDotFacade() = default;
};

