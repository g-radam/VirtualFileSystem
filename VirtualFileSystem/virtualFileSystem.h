//standard Includes
#include <iostream>		//std::cout istream
#include <fstream>		//std::fstream
#include <vector>		//std::vector
#include <string>		//std::string

// Boost Includes
#include <boost/cstdint.hpp>						//uint8, uint16, uint32, uint64...
#include <boost/filesystem.hpp>						//exists, is_regular
#include <boost/lexical_cast.hpp>					//boost::lexical_cast<int>(string)
#include <boost/thread.hpp>							//boost::thread
#include "boost/date_time/gregorian/gregorian.hpp"	//western calendar


// Class Definitions
class AccessControlList;
class Attributes;
class File;
class Folder;
class FileSystem;


// Node Permissions
class AccessControlList
{
	public:
		struct UserPermission
		{
			std::string	   _userName; // Username
			boost::uint8_t _rwx;	  // Read Write Execute
		};
		std::vector<UserPermission> _permissions;
		
	public:
		 AccessControlList();
		~AccessControlList();

		// 
		bool	createPermission	(boost::uint8_t userID, boost::uint8_t rwx);
		bool	updatePermission	(boost::uint8_t userID, boost::uint8_t rwx);
		bool	deletePermission	(boost::uint8_t userID);
		
		
};


// Modifiable attributes for each node
class Attributes
{
	public:
		bool				   _protected;	 // System File (never viewed by user)
		bool				   _hidden;		 // Hidden (can be toggled)
		boost::gregorian::date _dateCreated; // Date of creation
		boost::gregorian::date _dateUpdated; // Date of update
		
	public:
		 Attributes();
		~Attributes();


		// Set
		void					setProtected	(bool isProtected);
		void					setHidden		(bool isHidden);
		void					setDateCreated	(boost::gregorian::date date);
		void					setDateUpdated	(boost::gregorian::date date);
		
		// Get
		bool					getProtected	(void);
		bool					getHidden		(void);
		boost::gregorian::date	getDateCreated	(void);
		boost::gregorian::date	getDateUpdated	(void);

};


// File Node
class File
{
	public:
		std::string		  _name;			  // File Name
		std::string		  _path;			  // File Path
		boost::uint32_t   _size;			  // File size in bytes
		Attributes		  _attributes;		  // Modifiable attributes
		AccessControlList _accessControlList; // Permissions
		
	public:
		 File(FileSystem &fileSystem, std::string parentDirectory, std::string name);
		~File();
		
		// Set
		void				setName					(const std::string &name);
		void				setPath					(const std::string &path);
		void				setSize					(const boost::uint32_t &size);
		void				setAttributes			(const Attributes &attributes);
		void				setAccessControlList	(const AccessControlList &acl);
		
		// Get
		std::string&		getName					(void);
		std::string&		getPath					(void);
		boost::uint32_t&	getSize					(void);
		AccessControllList&	getAccessControllList	(void);
		
		
};

class FileSystem
{
	public:	
		
		
	public:
		 FileSystem();
		~FileSystem();
		
		
		
};
