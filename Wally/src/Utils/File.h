/*
 * File.h
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */

#ifndef FILE_H_
#define FILE_H_

#include <sys/stat.h>
#include "String.h"
#include <Utils/ArrayList.h>
#include <Exception/SecurityException.h>

class File
{
private:
	ArrayList<String> mDirStructure;
	String mPathName;
	struct stat mStatFile;
	bool mExist;
	bool mAccess;
	static String DOT;
	static String DOTDOT;
	static const char* INFO_FILE;
	//=======Trabajando en utilerias como esta======
	void zeroMemory(void *mem, int len)
	{
		char *m = (char*)mem;
		for (int i = 0; i<len;i++)
		{
			m[i] = 0;
		}
	}
	//=======
protected:
	ArrayList<String> toAbsolutePath(String *path);
	void loadInfoFile();
public:
	static int FILES_AND_FOLDERS;
	static int ONLY_FILES;
	static int ONLY_FOLDERS;
	File(String pathName);
	virtual ~File();
	static ArrayList<String> listRoots();
	static bool setWorkDir(String);
	static String getWorkDir();
	virtual long int length();
	virtual long int lastModified();
	virtual long int lastAccess();
	virtual long int lastChange();
	virtual bool exist();
	virtual unsigned int getPermissions();
	virtual bool setPermissions(unsigned int permissions);
	virtual int getHardLinkTo();
	virtual bool isSymbolic();
	virtual bool isDirectory();
	virtual bool isFile();
	virtual bool canRead();
	virtual bool canWrite();
	virtual ArrayList<String> list(int arg = FILES_AND_FOLDERS);
	virtual bool mkdir(bool nothrow = true);
	virtual bool mkdir2();
	virtual String getRelativePath();
	virtual String getParent();
	virtual String getName();
	virtual String getAbsolutePath();
	virtual bool remove();
	static String getUserFolder(const char* folderName);
};



#endif /* FILE_H_ */
