//standard Includes
#include <windows.h>	//console commands
#include <iostream>		//std::cout istream
#include <fstream>		//std::fstream
#include <vector>		//std::vector
#include <string>		//std::string
#include <ctime>		//std::clock_t

// Boost Includes
#include <boost/cstdint.hpp>		//uint8, uint16, uint32, uint64...
#include <boost/filesystem.hpp>		//exists, is_regular
#include <boost/lexical_cast.hpp>	//boost::lexical_cast<int>(string)
#include <boost/timer/timer.hpp>	//boost::timer::cpu_timer
#include <boost/thread.hpp>			//boost::thread

// User Includes
//#include "virtualFileSystem.h"

#include "path.h"

void checkPath (void);


int main()
{
	checkPath();

	std::system("pause");
	return 0;
};





void checkPath ()
{
	// Create Path
	Path path("user/data/doc", "/");
	std::cout << "path 1 = " << path << std::endl;
	
	// Append /code
	path.push("code");
	std::cout << "path 2 = " << path << std::endl;

	// Append /gcn
	path += "gcn";
	std::cout << "path 3 = " << path << std::endl;

	// Append path 
	Path path2("gcn.text", "/");
	path.push(path2);
	std::cout << "path 4 = " << path << std::endl << std::endl;
	
	// Seperator mismatch
	std::cout << "using lhs seperator   = " << (Path("documents", "/") + Path("abc\\123\\456"))	        << std::endl;
	std::cout << "using rhs seperator   = " << (Path("documents")      + Path("abc\\123\\456", "/"))    << std::endl;
	std::cout << "using rhs path as sep = " << (Path("documents")      + Path("abc\\123\\456\\\\\\\\")) << std::endl << std::endl;

	// is empty
	std::cout << "is empty = " << path.isEmpty() << std::endl << std::endl;

	// Find subpaths
	Path path3("data/doc", "/");
	std::cout << "find1 'data'     = " << path.find("data") << std::endl;
	std::cout << "find2 'data/doc' = " << path.find(path3) << std::endl << std::endl;

	// Count components
	std::cout << "Count1 'gcn'      = " << path.count("gcn") << std::endl;
	std::cout << "Count2 'data/doc' = " << path.count(path3) << std::endl;
	std::cout << "Count3 'games'    = " << path.count("games") << std::endl << std::endl;

	// Get left, right and difference
	std::cout << "left and right of /gcn/" << std::endl;
	std::cout << "left(no include)  of 'user/data/doc/code/gcn/gcn.txt' = " << path.left("gcn", false) << std::endl;
	std::cout << "right(no include) of 'user/data/doc/code/gcn/gcn.txt' = " << path.right("gcn", false) << std::endl;
	std::cout << "left(include)     of 'user/data/doc/code/gcn/gcn.txt' = " << path.left("gcn", true) << std::endl;
	std::cout << "right(include)    of 'user/data/doc/code/gcn/gcn.txt' = " << path.right("gcn", true) << std::endl << std::endl;

	// Compare paths
	std::cout << "compare ('user/data/doc/code/gcn/gcn.txt' == 'gcn.text') = " << (path == path2) << std::endl;
	std::cout << "compare ('data/doc' == 'data/doc') = "					   << (path == path) << std::endl << std::endl;

	// Get first, last and index
	std::cout << "first of     'user/data/doc/code/gcn/gcn.txt' = " << path.first() << std::endl;
	std::cout << "last of      'user/data/doc/code/gcn/gcn.txt' = " << path.last()  << std::endl;
	std::cout << "3rd index of 'user/data/doc/code/gcn/gcn.txt' = " << path[3]      << std::endl;
	
}
