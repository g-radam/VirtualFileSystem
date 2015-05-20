#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

//standard Includes
#include <iostream>		//std::cout istream
#include <vector>		//std::vector
#include <string>		//std::string

// Boost Includes
#include "boost/date_time/gregorian/gregorian.hpp"	//western calendar
#include "boost/variant.hpp"						//variant


// Variant Attribute Type
typedef boost::variant<
	bool,
	signed int,
	std::string,
	boost::gregorian::date,
	const char *
> AttributeData;



// Modifiable attributes for each node
class Attributes
{
	public:
		bool								 _isProtected;	// Protected File/Folder (Only the VFS can access such node)
		std::map<std::string, AttributeData> _attributes;	// Contains modifiable attributes
		
	public:
		 Attributes();
		~Attributes();


		// Unmodifiable Attributes
		void					setProtected		(bool isProtected);							// Sets VFS Protected
		bool					getProtected		(void);										// Gets VFS Protected

		// Modifiable Attribute Functions
		void					append				(std::string key, AttributeData &data);		// Append Data to map if key isnt used
		void					append				(std::string key, std::string data);		// Append Overload for const char array to string
		AttributeData&			operator[]			(std::string key);							// Access Data using Key
		
		bool					getBool				(std::string key);							// Return Boolean type data
		signed int				getInt				(std::string key);							// Return Integer type data
		std::string				getString			(std::string key);							// Return String type data
		boost::gregorian::date  getDate				(std::string key);							// Return Date type data
		std::string				toString			(std::string key);							// Return any data as string (for eg cout)
		
		bool					exists				(std::string key);							// Return true if key exists
		bool					empty				(void);										// Returns If Map is empty
		int						size				(void);										// Returns Size of map
		void					clear				(void);										// Clears map
		
		bool					isBool				(std::string key);							// Returns true if attribute data is boolean
		bool					isInt				(std::string key);							// Returns true if attribute data is integer
		bool					isString			(std::string key);							// Returns true if attribute data is string
		bool					isDate				(std::string key);							// Returns true if attribute data is date


		// Iterator Access
		typedef std::map<std::string, AttributeData>::iterator iterator;						// Iterator
		typedef std::map<std::string, AttributeData>::const_iterator const_iterator;			// Constant Iterator
		iterator				begin				(void);										// Begin iterator
		iterator				end					(void);										// End iterator
		
};

#endif ATTRIBUTES_H




/*
	
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
*/
