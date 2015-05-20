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
#include "boost/variant.hpp"						//variant

// User Includes
#include "path.h"



// Class Definitions
class Path;
class AccessControlList;
class Attributes;
class NodeBase;
class Folder;
class FileSystem;


// Inode
typedef boost::variant<
	boost::recursive_wrapper<File>,
	boost::recursive_wrapper<Folder>
> Inode;





// Node Permissions
class AccessControlList
{
	public:
		struct UserPermission
		{
			std::string	   _userName; // Username
			boost::uint8_t _rwx;	  // Read Write Execute
		};
		std::vector<UserPermission> _permissions;	// User - Permission link vector
		
	public:
		 AccessControlList();
		~AccessControlList();

		// 
		bool	createPermission	(boost::uint8_t userID, boost::uint8_t rwx);	// Create & Link permission to user
		bool	updatePermission	(boost::uint8_t userID, boost::uint8_t rwx);	// Update permission linked to user
		bool	deletePermission	(boost::uint8_t userID);						// Delete permission linked to user
		
		
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

// Base for all Inodes - files, folders
class InodeBase
{
	public:
		// Variables
		std::string		  _name;			  // File Name
		Path			  _path;			  // File Path
		boost::uint32_t   _size;			  // File size in bytes
		Attributes		  _attributes;		  // Modifiable attributes
		AccessControlList _accessControlList; // Permissions

		// Set
		void				setName					(const std::string &name);
		void				setPath					(const Path &path);
		void				setSize					(const boost::uint32_t &size);
		void				setAttributes			(const Attributes &attributes);
		void				setAccessControlList	(const AccessControlList &acl);
		
		// Get
		std::string&		getName					(void);
		Path&				getPath					(void);
		boost::uint32_t&	getSize					(void);
		Attrobutes&			getAttributes			(void);
		AccessControllList&	getAccessControllList	(void);
};


// File Node
class File : InodeBase
{
	private:
		// File specific Properties
		//Contents _contents;
		
	public:
		 File(FileSystem &fileSystem, std::string parentDirectory, std::string name);
		~File();
		
		
};

// Folder Node
class Folder : InodeBase
{
	private:
		// Folder specific Properties
		std::vector<Inode> _inodes;
		
	public:
		 File(FileSystem &fileSystem, Path parentDirectory, std::string name); //add .. & . 
		~File();
		
		void				setInodes	(std::vector<Inode> inodes);
		std::vector<Inode>&	getInodes	(void);
		
};



class FileSystem
{
	public:	
		
		
	public:
		 FileSystem();
		~FileSystem();
		
		std::string		normalisePath				(Path path);
		std::string		absolutePath				(Path localPath);
		
		
		void			setWorkingDirectory			(Path path);
		std::string		getWorkingDirectory			(void);
		
};
