#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include <string>


// Path Class
class Path
{
	public:
		std::string				 _separator;			// Path Separator
		std::string				 _path;					// Complete Path
		std::vector<std::string> _components;			// Components used to construct path

	public:
		 Path(std::string path, std::string separator);
		 Path(std::string path);
		 Path();
		~Path();
		
		
		// Set
		void						setPath						(std::string path);							// Set Path
		void						setSeparator				(std::string separator);					// Set Separator
		
		// Get
		std::string					toString					(void);										// Return Path String
		std::string					getPath						(void);										// Return Path string
		std::string					getSeparator				(void);										// Return Separator
		std::vector<std::string>&	getComponents				(void);										// Return Reference to Components vector
		unsigned int				size						(void);										// Return length of the path string
		unsigned int				length						(void);										// Alias of size
		unsigned int				depth						(void);										// Return Number of Components in the vector
		unsigned int				componentCount				(void);										// Depth alias
		
		bool						isEmpty						(void);										// Returns if the path is empty

		
		
		// Methods
		void						push						(Path &path);								// Append new path to current path
		void						push						(std::string component);					// Append new component to current path
		void						pop							(void);										// Pop a component off the path
		std::string					first						(void);										// First component in the path (left side path)
		std::string					last						(void);										// Last component in the path (right side of path)
		void						clear						(void);										// Clear the path
		int							find						(std::string component);					// Return the index of the component found. -1 if component wasnt found
		int							find						(Path& path);								// Return the index of the path found. -1 if component wasnt found
		unsigned int				count						(std::string component);					// Count the amount of duplicate components
		unsigned int				count						(Path& path);								// Count the amount of duplicate paths
		Path						left						(std::string component, bool include);		// Returns left of the rhs found in the lhs
		Path						left						(Path& path, bool include);					// Returns left of the rhs found in the lhs
		Path						right						(std::string component, bool include);		// Returns right of the rhs found in the lhs
		Path						right						(Path& path, bool include);					// Returns right of the rhs found in the lhs
		
		void						buildPathFromComponents		(void);										// Construct path from components vector
		std::vector<std::string>	extractComponentsFromPath	(std::string path);							// Fill vector with components of the path
		std::string					extractSeparatorFromPath	(std::string path);							// Identify the separator used in the path
		std::string					extractSeparatorFromPath	(Path& path);								// Identify the separator used in the path

		// Debug
		void						displayComponents			(void);										// Cout the components in the path
		
		// Overloads
		Path						operator+					(Path& rhs);								// Append RHS Path to LHS Path
		Path						operator+					(std::string rhs);							// Append RHS String to LHS Path (Not reference, copy constructor takes const char* and char array)
		
		Path						operator+=					(Path& rhs);								// Append RHS Path to THIS
		Path						operator+=					(std::string rhs);							// Append RHS String to THIS (Not reference, copy constructor takes const char* and char array)
		
		Path						operator=					(Path& rhs);								// Assign RHS Path to LHS Path
		Path						operator=					(std::string rhs);							// Assign RHS String to LHS Path (Not reference, copy constructor takes const char* and char array)
		
		bool						operator==					(Path& rhs);								// Compare LHS Path to RHS Path
		bool						operator==					(std::string rhs);							// Compare LHS String to RHS Path (Not reference, copy constructor takes const char* and char array)
		
		std::string					operator[]					(const unsigned int &index);				// Return specific component within the path
		
		// Stream Overload
		friend std::ostream&		operator<<					(std::ostream &os, const Path& path);		// Console out 
};




#endif  PATH_H
