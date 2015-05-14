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



Path::Path(std::string path, std::string saperator)
{
	Path::_separator = saperator;
	Path::_components = Path::extractComponentsFromPath(path);
	Path::buildPathFromComponents();
}

Path::Path(std::string path)
{
	Path::_separator = Path::extractSeparatorFromPath(path);
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
	Path::_separator = Path::extractSeparatorFromPath(path);
	Path::_components = Path::extractComponentsFromPath(path);
	Path::buildPathFromComponents();
}

void						Path::setSeparator					(std::string separator)
{
	Path::_separator = separator;
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

std::string					Path::getSeparator					()
{
	return Path::_separator;
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
	// Find and use a separator
	if(!Path::_separator.empty())
		// Priority (keep current separator)
		Path::setSeparator(Path::_separator);
	else {
		// Otherwise use rhs operator
		std::string rhsSeparator = Path::extractSeparatorFromPath(path);
		if(!rhsSeparator.empty()) {
			Path::setSeparator(rhsSeparator);
		} else {
			// Error, Unable to reconstruct path
			std::cout << "Path: Error: push Unable to append path to THIS - Unknown separator" << std::endl;
			return;
		}
	}

	Path::_components.insert(Path::_components.end(), path.getComponents().begin(), path.getComponents().end());
	Path::buildPathFromComponents();
}
void						Path::push							(std::string component)
{
	// Find and use a separator
	if(!Path::_separator.empty())
		// Priority (keep current separator)
		Path::setSeparator(Path::_separator);
	else {
		// Otherwise use rhs operator
		std::string rhsSeparator = Path::extractSeparatorFromPath(component);
		if(!rhsSeparator.empty()) {
			Path::setSeparator(rhsSeparator);
		} else {
			// Error, Unable to reconstruct path
			std::cout << "Path: Error: push Unable to append path to THIS - Unknown separator" << std::endl;
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
	leftPath.setSeparator(Path::_separator);

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
	leftPath.setSeparator(Path::_separator);

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
	leftPath.setSeparator(Path::_separator);

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
	leftPath.setSeparator(Path::_separator);

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

	// Append Component to path. Ensure trailing separator isnt added. ie D:\games\file.txt\ <--- That
	for(unsigned int i = 0; i < Path::_components.size(); ++i) {
		//std::cout << "rebuild it = " << Path::_components[i] << std::endl;
		if(i < Path::_components.size()-1) 
			Path::_path += Path::_components[i] + Path::_separator;
		else
			Path::_path += Path::_components[i];
	}
}

std::vector<std::string>	Path::extractComponentsFromPath		(std::string path)
{
	// Return Vector
	std::vector<std::string> components;

	// Boost splits the string up, into the componenets vector if the separator is \ or /
	boost::split(components, path, boost::is_any_of("/\\"));

	// Delete trailing separators
	if(!components.empty()) {
		if(components.back().empty()) {
			components.pop_back();
		}
	}

	// Error on any blank elements (means there is a double separator 'root/user//adam')
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
		std::cout << "Path: Error: Multiple separators are not valid in path: " << path << std::endl;
		std::cout << "Path: Error: Resolving separator issue..." << std::endl;
	}

	// Return components
	return components;
}

std::string					Path::extractSeparatorFromPath		(std::string path)
{
	// Find \ or /
	unsigned int fowardslash = path.find("/");
	unsigned int backwardslash = path.find("\\");

	if(fowardslash != std::string::npos)
		return std::string("/");
	else if (backwardslash != std::string::npos)
		return std::string("\\");
	
	// Default return separator of ""
	return std::string();
}

std::string					Path::extractSeparatorFromPath		(Path& path)
{
	// Return Separator variable OR separator found in the path itself
	std::string separator1 = path.getSeparator();
	if(!separator1.empty()) {
		return separator1;
	}

	std::string separator2 = Path::extractSeparatorFromPath(path.getPath());
	if(!separator2.empty()) {
		return separator2;
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
	
	// Find and use a separator
	std::string thisSeparator = Path::extractSeparatorFromPath(*this);
	if((!thisSeparator.empty())) {
		// Priority (keep current separator)
		path.setSeparator(thisSeparator);
		//std::cout << "using lhs = " << thisSeparator << std::endl;
	} else {
		// Otherwise use rhs operator
		std::string rhsSeparator = Path::extractSeparatorFromPath(rhs);
		//std::cout << "using rhs = " << rhsSeparator << std::endl;
		if(!rhsSeparator.empty()) {
			path.setSeparator(rhsSeparator);
		} else {
			// Error, Unable to reconstruct path
			std::cout << "Path: Error: push Unable to append path to THIS - Unknown separator" << std::endl;
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

Path						Path::operator+						(std::string rhs)
{
	// By setting the path, it will automatically generate a new components vector
	Path path;

	// Find and use a separator
	std::string thisSeparator = Path::extractSeparatorFromPath(*this);
	if((!thisSeparator.empty())) {
		// Priority (keep current separator)
		path.setSeparator(thisSeparator);
	} else {
		// Otherwise use rhs operator
		std::string rhsSeparator = Path::extractSeparatorFromPath(rhs);
		if(!rhsSeparator.empty()) {
			path.setSeparator(rhsSeparator);
		} else {
			// Error, Unable to reconstruct path
			std::cout << "Path: Error: push Unable to append path to THIS - Unknown separator" << std::endl;
			return Path();
		}
	}
	
	// Extract components from rhs and apply to current lhs componenets + rhs to new path
	path.getComponents() = Path::_components;
	std::vector<std::string> components = Path::extractComponentsFromPath(rhs);
	path.getComponents().insert(path.getComponents().end(), components.begin(), components.end());

	// Rebuild Path by setting the separator
	path.buildPathFromComponents();

	return path;
}


Path						Path::operator+=					(Path& rhs)
{
	(*this) = Path::operator+(rhs);
	return *this;
}
Path						Path::operator+=					(std::string rhs)
{
	(*this) = Path::operator+(rhs);
	return *this;
}

Path						Path::operator=						(Path& rhs)
{
	// This causes unnecessary rebuilding of vector and path. Fix later.
	// Identify separator character and apply it to THIS
	Path::setSeparator(Path::extractSeparatorFromPath(rhs));
	Path::setPath(rhs.getPath()); // rebuilds(useful)

	return *this;
}

Path						Path::operator=						(std::string rhs)
{
	// This causes unnecessary rebuilding of vector and path. Fix later.
	// Identify separator character and apply it to THIS
	Path::setSeparator(Path::extractSeparatorFromPath(rhs));
	Path::setPath(rhs);

	return *this;
}

bool						Path::operator==					(Path& rhs)
{
	return (Path::getPath() == rhs.getPath());
}

bool						Path::operator==					(std::string rhs)
{
	return (Path::getPath() == rhs);
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
