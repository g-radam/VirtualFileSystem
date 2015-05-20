//standard Includes
#include <iostream>		//std::cout istream
#include <vector>		//std::vector
#include <string>		//std::string

// Boost Includes
#include "boost/date_time/gregorian/gregorian.hpp"	//western calendar
#include "boost/variant.hpp"						//variant

// User Includes
#include "attributes.h"





// Constructor & Destructor
Attributes:: Attributes()
{
	
}

Attributes::~Attributes()
{
	
}



// Unmodifiable Attributes
void					Attributes::setProtected		(bool isProtected)
{
	Attributes::_isProtected = isProtected;
}

bool					Attributes::getProtected		()
{
	return Attributes::_isProtected;
}


// Modifiable Attribute Functions
void					Attributes::append				(std::string key, AttributeData &data)
{
	if(!Attributes::exists(key)) {
		Attributes::_attributes[key] = data;
	}
}
void					Attributes::append				(std::string key, std::string data)
{
	if(!Attributes::exists(key)) {
		Attributes::_attributes[key] = data;
	}
}

AttributeData&			Attributes::operator[]			(std::string key)
{
	if(!Attributes::exists(key)) {
		return Attributes::_attributes[key];
	}

	// Return empty element
	return Attributes::_attributes[""];
}

		
bool					Attributes::getBool				(std::string key)
{
	if(bool *data = boost::get<bool>(&Attributes::_attributes[key])) {
		return *data;
	}

	// Default Return
	return false;
}

signed int				Attributes::getInt				(std::string key)
{
	if(signed int *data = boost::get<signed int>(&Attributes::_attributes[key])) {
		return *data;
	}

	// Default Return
	return 0;
}

std::string				Attributes::getString			(std::string key)
{
	// is std String
	if(std::string *data = boost::get<std::string>(&Attributes::_attributes[key])) {
		return *data;
	} else if(const char **data = boost::get<const char*>(&Attributes::_attributes[key])) {
		return std::string(*data);
	}

	// Default Return
	return std::string();
}

boost::gregorian::date  Attributes::getDate				(std::string key)
{
	if(boost::gregorian::date *data = boost::get<boost::gregorian::date>(&Attributes::_attributes[key])) {
		return *data;
	}

	// Default Return
	return boost::gregorian::date();
}

std::string				Attributes::toString			(std::string key)
{
	return "";
}

		
bool					Attributes::exists				(std::string key)
{
	if(Attributes::_attributes.count(key) == 0) {
		return false;
	} else {
		return true;
	}
}

bool					Attributes::empty				()
{
	return Attributes::_attributes.empty();
}

int						Attributes::size				()
{
	return Attributes::_attributes.size();
}

void					Attributes::clear				()
{
	Attributes::_attributes.clear();
}

		
bool					Attributes::isBool				(std::string key)
{
	if(bool *data = boost::get<bool>(&Attributes::_attributes[key])) {
		return true;
	}

	// Default Return
	return false;
}

bool					Attributes::isInt				(std::string key)
{
	if(signed int *data = boost::get<signed int>(&Attributes::_attributes[key])) {
		return true;
	}

	// Default Return
	return false;
}

bool					Attributes::isString			(std::string key)
{
	if(std::string *data = boost::get<std::string>(&Attributes::_attributes[key])) {
		return true;
	} else if(const char **data = boost::get<const char*>(&Attributes::_attributes[key])) {
		return true;
	}

	// Default Return
	return false;
}

bool					Attributes::isDate				(std::string key)
{
	if(boost::gregorian::date *data = boost::get<boost::gregorian::date>(&Attributes::_attributes[key])) {
		return true;
	}

	// Default Return
	return false;
}



// Iterator Access
Attributes::iterator	Attributes::begin				()
{
	return Attributes::_attributes.begin();
}

Attributes::iterator	Attributes::end					()
{
	return Attributes::_attributes.end();
}

		