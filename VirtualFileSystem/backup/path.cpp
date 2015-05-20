// Standard Includes
#include <iostream>
#include <vector>
#include <string>

// Boost Includes
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/cstdint.hpp>

// User Includes
#include "path.h"



Path::Path(std::string path, std::string seperator)
{
	Path::_seperator = seperator;
	Path::_components = Path::extractComponentsFromPath(path);
	Path::buildPathFromComponents();
}

Path::Path(std::string path)
{
	Path::_seperator = Path::extractSeperatorFromPath(path);
	Path::_components = Path::extractComponentsFromPath(path);
	Path::buildPathFromComponents();
}

Path::Path()
{
	// String Default Constructor will ensure string is empty
}

Path::~Path()
{
	// No Heap based data
}

// Set
void						Path::setPath						(std::string path)
{
	Path::_components.clear();
	Path::_seperator = Path::extractSeperatorFromPath(path);
	Path::_components = Path::extractComponentsFromPath(path);
	Path::buildPathFromComponents();
}

void						Path::setSeperator					(std::string seperator)
{
	Path::_seperator = seperator;
	Path::buildPathFromComponents();
}


// Get
std::string					Path::toString						()
{
	return Path::_path;
}

std::string					Path::getPath						()
{
	return Path::_path;
}

std::string					Path::getSeperator					()
{
	return Path::_seperator;
}

std::vector<std::string>&	Path::getComponents					()
{
	return Path::_components;
}

unsigned int				Path::size							()
{
	return Path::_path.size();
}

unsigned int				Path::length						()
{
	return Path::_path.size();
}

unsigned int				Path::depth							()
{
	return Path::_components.size();
}

unsigned int				Path::componentCount				()
{
	return Path::_components.size();
}

bool						Path::isEmpty						()
{
	return Path::_path.empty();
}


// Methods
void						Path::push							(Path &path)
{
	// Find and use a seperator
	if(!Path::_seperator.empty()) 
		// Priority (keep current seperator)
		Path::setSeperator(Path::_seperator);
	else {
		// Otherwise use rhs operator
		std::string rhsSeperator = Path::extractSeperatorFromPath(path);
		if(!rhsSeperator.empty()) { 
			Path::setSeperator(rhsSeperator);
		} else {
			// Error, Unable to reconstruct path
			std::cout << "Path: Error: push Unable to append path to THIS - Unknown seperator" << std::endl;
			return;
		}
	}

	Path::_components.insert(Path::_components.end(), path.getComponents().begin(), path.getComponents().end());
	Path::buildPathFromComponents();
}
void						Path::push							(std::string component)
{
	// Find and use a seperator
	if(!Path::_seperator.empty()) 
		// Priority (keep current seperator)
		Path::setSeperator(Path::_seperator);
	else {
		// Otherwise use rhs operator
		std::string rhsSeperator = Path::extractSeperatorFromPath(component);
		if(!rhsSeperator.empty()) { 
			Path::setSeperator(rhsSeperator);
		} else {
			// Error, Unable to reconstruct path
			std::cout << "Path: Error: push Unable to append path to THIS - Unknown seperator" << std::endl;
			return;
		}
	}

	Path::_components.push_back(component);
	Path::buildPathFromComponents();
}

void						Path::pop							()
{
	// Only pop an item if it exists
	if(Path::_components.size() > 0) {
		Path::_components.pop_back();
		Path::buildPathFromComponents();
	}
}

std::string					Path::first							()
{
	// Only return an item if it exists
	if(Path::_components.size() > 0)
		return Path::_components.front();

	// Return Null
	return std::string();
}

std::string					Path::last							()
{
	// Only return an item if it exists
	if(Path::_components.size() > 0)
		return Path::_components.back();

	// Return Null
	return std::string();
}

void						Path::clear							()
{
	Path::_components.clear();
	Path::_path.clear();
}

int							Path::find							(std::string component)
{
	// Iterate through components and find component
	for(unsigned int i = 0; i < Path::_components.size(); ++i) {
		if(Path::_components[i] == component) {
			return i;
		}
	}

	// Default return of -1
	return -1;
}

int							Path::find							(Path &path)
{
	if(path.componentCount() > 0) {
		// Iterate through components and find component
		for(unsigned int i = 0; i < Path::_components.size(); ++i) {

			// If Component == path.component & i+path.size is less than this.size()
			if(Path::_components[i] == path.getComponents()[0]) {
				if(i+path.getComponents().size()-1 < Path::_components.size()) {

					// Verify if this == path
					bool verified = true;
					for(unsigned int j = 0; j < path.getComponents().size(); ++j) {
						if(Path::_components[i+j] != path.getComponents()[j]) {
							verified = false;
							break;
						}
					}

					// If the path wasnt equal, check the next component in the current path
					if(!verified) {
						continue;
					} else {
						return i;
					};
				}
			}
		}
	}

	// Default return of -1
	return -1;
}

unsigned int				Path::count							(std::string component)
{
	// Number of components in THIS which equals component
	unsigned int count = 0;

	// Iterate through THIS and count components
	for(unsigned int i = 0; i < Path::_components.size(); ++i) {
		if(Path::_components[i] == component) {
			++count;
		}
	}

	// Return Count
	return count;
}

unsigned int				Path::count							(Path& path)
{
	// Number of components in THIS which equals component
	unsigned int count = 0;

	// Iterate through THIS and count components
	for(unsigned int i = 0; i < Path::_components.size(); ++i) {

		// If Component == path.component & i+path.size is less than this.size()
		if(Path::_components[i] == path.getComponents()[0]) {
			if(i+path.getComponents().size()-1 < Path::_components.size()) {

				// Verify if this == path
				bool verified = true;
				for(unsigned int j = 0; j < path.getComponents().size(); ++j) {
					if(Path::_components[i+j] != path.getComponents()[j]) {
						verified = false;
						break;
					}
				}

				// If the path wasnt equal, check the next component in the current path
				if(!verified) {
					continue;
				} else {
					++count;
				};
			}
		}
	}

	// Return Count
	return count;
}

Path						Path::left							(std::string component, bool include)
{
	int position = Path::find(component);
	Path leftPath;
	leftPath.setSeperator(Path::_seperator);

	// If the component has at least 1 left component
	if((position > 0) && (position < Path::_components.size())) {
		//std::cout << "position = " << position << " which == " << Path::_components[position] << std::endl;
		leftPath.getComponents().insert(leftPath.getComponents().begin(), Path::_components.begin(), Path::_components.begin() + position+((int)include));
		leftPath.buildPathFromComponents();
		return leftPath;
	} 

	// If the component[0] was found (nothing left of index 0, so return nothing)
	else if(position == 0) {
		return Path();
	}

	// If the component nothing was found in the THIS path
	else if(position == -1) {
		return Path();
	}

	// Default of empty Path
	return Path();
}

Path						Path::left							(Path& path, bool include)
{
	int position = Path::find(path);
	Path leftPath;
	leftPath.setSeperator(Path::_seperator);

	// If the component has at least 1 left component
	if((position > 0) && (position < Path::_components.size())) {
		//std::cout << "position = " << position << " which == " << Path::_components[position] << std::endl;
		leftPath.getComponents().insert(leftPath.getComponents().begin(), Path::_components.begin(), Path::_components.begin() + position+((int)include));
		leftPath.buildPathFromComponents();
		return leftPath;
	} 

	// If the component[0] was found (nothing left of index 0, so return nothing)
	else if(position == 0) {
		return Path();
	}

	// If the component nothing was found in the THIS path
	else if(position == -1) {
		return Path();
	}

	// Default of empty Path
	return Path();
}

Path						Path::right							(std::string component, bool include)
{
	int position = Path::find(component);
	Path leftPath;
	leftPath.setSeperator(Path::_seperator);

	// If the component has at least 1 left component
	if((position >= 0) && (position < Path::_components.size())) {
		//std::cout << "position = " << position << " which == " << Path::_components[position] << std::endl;
		leftPath.getComponents().insert(leftPath.getComponents().begin(), Path::_components.begin() + position+((int)!include), Path::_components.end());
		leftPath.buildPathFromComponents();
		return leftPath;
	} 

	// If the component[last] was found (nothing right of the last index, so return nothing)
	else if(position == Path::_components.size()-1) {
		return Path();
	}

	// If the component nothing was found in the THIS path
	else if(position == -1) {
		return Path();
	}

	// Default of empty Path
	return Path();
}

Path						Path::right							(Path& path, bool include)
{
	int position = Path::find(path);
	Path leftPath;
	leftPath.setSeperator(Path::_seperator);

	// If the THIS has at least 1 left component at the position
	if((position >= 0) && (position < Path::_components.size())) {
		//std::cout << "position = " << position << " which == " << Path::_components[position] << std::endl;
		leftPath.getComponents().insert(leftPath.getComponents().begin(), Path::_components.begin() + position+((int)include), Path::_components.end());
		leftPath.buildPathFromComponents();
		return leftPath;
	} 

	// If the component[last] was found (nothing right of the last index, so return nothing)
	else if(position == Path::_components.size()-1) {
		return Path();
	}

	// If the component nothing was found in the THIS path
	else if(position == -1) {
		return Path();
	}

	// Default of empty Path
	return Path();
}

void						Path::buildPathFromComponents		()
{
	// Clear Path before rebuilding
	Path::_path = "";

	// Append Component to path. Ensure trailing seperator isnt added. ie D:\games\file.txt\ <--- That   
	for(unsigned int i = 0; i < Path::_components.size(); ++i) {
		//std::cout << "rebuild it = " << Path::_components[i] << std::endl;
		if(i < Path::_components.size()-1) 
			Path::_path += Path::_components[i] + Path::_seperator;
		else
			Path::_path += Path::_components[i];
	}
}

std::vector<std::string>	Path::extractComponentsFromPath		(std::string path)
{
	// Return Vector
	std::vector<std::string> components;

	// Boost splits the string up, into the componenets vector if the seperator is \ or /
	boost::split(components, path, boost::is_any_of("/\\"));

	// Delete trailing seperators
	if(!components.empty()) {
		if(components.back().empty()) {
			components.pop_back();
		}
	}

	// Error on any blank elements (means there is a double seperator 'root/user//adam')
	bool emptyElement = false;
	for(unsigned int i = 0; i < components.size(); ++i) {
		if(components[i].empty()) {
			emptyElement = true;
			components.erase(components.begin()+i);
			--i; // Ensure the iterator doesnt go out of bounds
		}
	}

	// Display issues from above
	if(emptyElement) {
		std::cout << "Path: Error: Multiple seperators are not valid in path: " << path << std::endl;
		std::cout << "Path: Error: Resolving seperator issue..." << std::endl;
	}

	// Return components
	return components;
}

std::string					Path::extractSeperatorFromPath		(std::string path)
{
	// Find \ or /
	unsigned int fowardslash = path.find("/");
	unsigned int backwardslash = path.find("\\");

	if(fowardslash != std::string::npos)
		return std::string("/");
	else if (backwardslash != std::string::npos)
		return std::string("\\");
	
	// Default return seperator of ""
	return std::string();
}

std::string					Path::extractSeperatorFromPath		(Path& path)
{
	// Return Seperator variable OR seperator found in the path itself
	std::string seperator1 = path.getSeperator();
	if(!seperator1.empty()) {
		return seperator1;
	}

	std::string seperator2 = Path::extractSeperatorFromPath(path.getPath());
	if(!seperator2.empty()) {
		return seperator2;
	}

	return std::string();
}


// Debug
void						Path::displayComponents				()
{
	for(unsigned int i = 0; i < Path::_components.size(); ++i) {
		std::cout << " > " << Path::_components[i] << std::endl;
	}
}

// Overloads
Path						Path::operator+						(Path& rhs)
{
	// By setting the path, it will automatically generate a new components vector
	Path path;
	
	// Find and use a seperator
	std::string thisSeperator = Path::extractSeperatorFromPath(*this);
	if((!thisSeperator.empty())) {
		// Priority (keep current seperator)
		path.setSeperator(thisSeperator);
		//std::cout << "using lhs = " << thisSeperator << std::endl;
	} else {
		// Otherwise use rhs operator
		std::string rhsSeperator = Path::extractSeperatorFromPath(rhs);
		//std::cout << "using rhs = " << rhsSeperator << std::endl;
		if(!rhsSeperator.empty()) { 
			path.setSeperator(rhsSeperator);
		} else {
			// Error, Unable to reconstruct path
			std::cout << "Path: Error: push Unable to append path to THIS - Unknown seperator" << std::endl;
			return Path();
		}
	}

	// Append Components
	path.getComponents() = Path::_components;
	path.getComponents().insert(path.getComponents().end(), rhs.getComponents().begin(), rhs.getComponents().end());

	// Rebuild Path
	path.buildPathFromComponents();

	return path;
}

Path						Path::operator+						(std::string& rhs)
{
	// By setting the path, it will automatically generate a new components vector
	Path path;

	// Find and use a seperator
	std::string thisSeperator = Path::extractSeperatorFromPath(*this);
	if((!thisSeperator.empty())) {
		// Priority (keep current seperator)
		path.setSeperator(thisSeperator);
	} else {
		// Otherwise use rhs operator
		std::string rhsSeperator = Path::extractSeperatorFromPath(rhs);
		if(!rhsSeperator.empty()) { 
			path.setSeperator(rhsSeperator);
		} else {
			// Error, Unable to reconstruct path
			std::cout << "Path: Error: push Unable to append path to THIS - Unknown seperator" << std::endl;
			return Path();
		}
	}
	
	// Extract components from rhs and apply to current lhs componenets + rhs to new path
	path.getComponents() = Path::_components;
	std::vector<std::string> components = Path::extractComponentsFromPath(rhs);
	path.getComponents().insert(path.getComponents().end(), components.begin(), components.end());

	// Rebuild Path by setting the seperator
	path.buildPathFromComponents();

	return path;
}

Path						Path::operator+						(const char *rhs)
{
	return Path::operator+(std::string(rhs));
}

Path						Path::operator+=					(Path& rhs)
{
	(*this) = Path::operator+(rhs);
	return *this;
}
Path						Path::operator+=					(std::string& rhs)
{
	(*this) = Path::operator+(rhs);
	return *this;
}

Path						Path::operator+=					(const char *rhs)
{
	(*this) = Path::operator+(std::string(rhs));
	return *this;
}

Path						Path::operator=						(Path& rhs)
{
	// This causes uneccessary rebuilding of vector and path. Fix later.
	// Identify seperator character and apply it to THIS
	Path::setSeperator(Path::extractSeperatorFromPath(rhs));
	Path::setPath(rhs.getPath()); // rebuilds(useful)

	return *this;
}

Path						Path::operator=						(std::string& rhs)
{
	// This causes uneccessary rebuilding of vector and path. Fix later.
	// Identify seperator character and apply it to THIS
	Path::setSeperator(Path::extractSeperatorFromPath(rhs));
	Path::setPath(rhs);

	return *this;
}

Path						Path::operator=						(const char *rhs)
{
	return Path::operator=(std::string(rhs));
}

bool						Path::operator==					(Path& rhs)
{
	return (Path::getPath() == rhs.getPath());
}

bool						Path::operator==					(std::string& rhs)
{
	return (Path::getPath() == rhs);
}

bool						Path::operator==					(const char *rhs)
{
	return Path::operator==(std::string(rhs));
}

std::string					Path::operator[]					(const unsigned int &index)
{
	return Path::_components[index];
}

// Stream Overload
std::ostream&				operator<<							(std::ostream &os, const Path& path)
{
	return os << path._path;
}