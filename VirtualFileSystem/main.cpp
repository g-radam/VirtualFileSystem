#include <iostream>
#include "path.h"
#include "attributes.h"

int main()
{
	// Virtual Filesystem Terminal
	Attributes attributes;

	attributes["isVisible"] = true;
	attributes["viewCount"] = 23;
	attributes["registry"]  = "application";
	attributes.append("systemPath", "\\system\\");


	// Boolean
	if(attributes.isBool("isVisible"))
		std::cout << "isVisible  = " << attributes.getBool("isVisible") << std::endl;

	// Integer
	if(attributes.isInt("viewCount"))
		std::cout << "viewCount  = " << attributes.getInt("viewCount") << std::endl;

	// Const char *
	if(attributes.isString("registry"))
		std::cout << "registry   = " << attributes.getString("registry") << std::endl;

	// std::string
	if(attributes.isString("systemPath"))
		std::cout << "systemPath = " << attributes.getString("systemPath") << std::endl;

	// General Commands
	std::cout << std::endl;
	std::cout << "count           = " << attributes.size() << std::endl;
	std::cout << "is empty        = " << attributes.empty() << std::endl;
	std::cout << "registry exists = " << attributes.exists("registry") << std::endl;

	// Iterator Access
	std::cout << std::endl;
	for(Attributes::iterator it = attributes.begin(); it != attributes.end(); ++it) {
		std::cout << " > " << it->first << " = " << it->second << std::endl;
	}
	
	std::system("pause");
	return 0;
}
