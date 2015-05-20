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
#include "attributes.h"


// Class Definitions
class AccessControlList;
class NodeBase;
class File;
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

// Base for all Inodes - files, folders
class InodeBase
{
	public:
		// Variables
		std::string		  _name;			  // File Name
		std::string		  _path;			  // File Path
		boost::uint32_t   _size;			  // File size in bytes
		Attributes		  _attributes;		  // Modifiable attributes
		AccessControlList _accessControlList; // Permissions

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
		Attributes&			getAttributes			(void);
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
		 File(FileSystem &fileSystem, std::string parentDirectory, std::string name); //add '..' & '.' files 
		~File();
		
		void				setInodes	(std::vector<Inode> inodes);
		std::vector<Inode>&	getInodes	(void);
		
};


// Filesystem
class FileSystem
{
	public:	
		
		
	public:
		 FileSystem();
		~FileSystem();
		
		std::string		normalisePath				(Path path);
		std::string		absolutePath				(Path localPath);
		
		
		void			setWorkingDirectory			(std::string path);
		std::string		getWorkingDirectory			(void);
		
};
