/*
 * File.cpp
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <mntent.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "File.h"
#include <string.h>

String File::DOT = ".";
String File::DOTDOT = "..";
const char* File::INFO_FILE = "/etc/mtab";
int File::FILES_AND_FOLDERS = 0;
int File::ONLY_FILES = 1;
int File::ONLY_FOLDERS = 2;

String File::getUserFolder(const char* folder){
	char* home;
	home = getenv ("HOME");
	if (folder == NULL && home){
		return home;
	}
	if (home != NULL){
		File userDirs(String(home) + "/.config/user-dirs.dirs");

		if (userDirs.isFile()){
			FILE* file = fopen(userDirs.getAbsolutePath().c_str(), "r");
			char* line = NULL;
			size_t size = 0;
			while(getline(&line, &size, file) > 0){
				char* xdg_folder;
				char* xdg_path;
				xdg_folder = strtok(line, "=");
				xdg_path = strtok(NULL, " ");
				if (strncmp(xdg_folder, "XDG_", 4) == 0 && strncmp(xdg_folder + 4, folder, strlen(folder)) == 0){
					String ret;
					xdg_path++;
					int len = strlen(xdg_path);
					if (xdg_path[len - 1] == '\n'){
						xdg_path[len - 2] = 0;
					}
					else{
						xdg_path[len-1] = 0;
					}
					if (xdg_path[0]=='$'){
						xdg_path = strstr(xdg_path, "/") + 1;
						ret = File(String(home) + "/" + xdg_path).getAbsolutePath();
					}
					else{
						ret = xdg_path;
					}
					free(line);
					return ret;
				}
				free(line);
				line = NULL;
				size = 0;
			}
			fclose(file);
		}

	}
	return "";
}

File::~File(){
}

void File::loadInfoFile(){
	mAccess = true;
	mExist = true;

	zeroMemory(&mStatFile, sizeof(mStatFile));
	if (stat(mPathName, &mStatFile) == -1)
	{
		mExist = (errno != ENOENT);
		mAccess = ((errno & EACCES) != EACCES);
	}
}
File::File(String pathName):
	mDirStructure(),
	mPathName(pathName),
	mAccess(true),
	mExist(true)
{
	loadInfoFile();
	mDirStructure = toAbsolutePath(&pathName);
}



ArrayList<String> File::toAbsolutePath(String * path){
	if (path->charAt(0)=='/')
	{
		int lastIndex = 1;
		ArrayList<String>folders;
		folders.add("/");
		int count = 1;
		for (int i = 1; i < path->length();i++)
		{
			if (path->charAt(i) == '/')
			{
				String folder = path->substring(lastIndex, i - lastIndex + 1);
				lastIndex = i+1;
				if (folder == "../")
				{
					if (count > 1)
						count--;
				}
				else if (!folder.equals("./"))
				{
					folders.add(count, folder);
					count++;
				}
			}
		}

		if (lastIndex < path->length())
		{
			folders.add(count++, path->substring(lastIndex));
		}
		return folders.subArrayList(0, count);

	}else//se trata de una ruta relativa
	{
		char workDir[PATH_MAX];
		getcwd(workDir, PATH_MAX);
		String ruta = workDir;
		if (ruta.charAt(ruta.length()-1)!='/') ruta+= "/";
		ruta += *path;
		printf("ruta: %s\n", ruta.c_str());
		return toAbsolutePath(&ruta);
	}
}

long int File::length(){
	return mStatFile.st_size;
}

long int File::lastModified(){
	return mStatFile.st_mtim.tv_nsec;
}

long int File::lastAccess(){
	return mStatFile.st_atim.tv_nsec;
}

long int File::lastChange(){
	return mStatFile.st_ctime;
}

bool File::exist(){
	return mExist;
}

unsigned int File::getPermissions(){
	return mStatFile.st_mode;
}

bool File::setPermissions(unsigned int permissions){
	//vea: http://linux.die.net/man/2/chmod
	return	~chmod(getAbsolutePath(), permissions);
}

int File::getHardLinkTo(){
	return mStatFile.st_nlink;
}

bool File::isSymbolic(){
	return (S_IFLNK & mStatFile.st_mode) == S_IFLNK;
}

bool File::isDirectory(){
	//return S_ISDIR(mStatFile.st_mode);
	return (S_IFDIR & mStatFile.st_mode) == S_IFDIR;
}

bool File::isFile(){
	//return S_ISREG(mStatFile.st_mode);
	return (S_IFREG & mStatFile.st_mode) == S_IFREG;
}

bool File::canRead(){
	if (mAccess)
		return (S_IRUSR & mStatFile.st_mode) == S_IRUSR;
	return false;
}

bool File::canWrite()
{
	if (mAccess)
		return (S_IWUSR & mStatFile.st_mode) == S_IWUSR;
	return false;
}

ArrayList<String> File::list(int arg){
	ArrayList<String> dirs;
	if (isDirectory())
	{
		DIR* srcDir = opendir(mPathName);
		struct dirent* dent;
		if (srcDir == NULL)
		{
			switch(errno)
			{
			case EACCES:
				throw SecurityException("No tiene permisos para acceder a la carpeta");
			case ELOOP:
				throw Exception("Muchas ligas simbolicas encontradas");
			case ENAMETOOLONG:
				throw Exception("The length of the path argument exceeds PATH_MAX, or a pathname component is longer than NAME_MAX");
			case ENOENT:
				throw Exception("No existe la carpeta");
			case ENOTDIR:
				throw Exception("El pathname no es carpeta");
				//no deberia pasar esto
			default:
				throw Exception("No se puede leer desde la carpeta");
			}
			//strerror en string.h, es mas especifico
		}

		while((dent = readdir(srcDir)) !=  NULL)
		{
			struct stat st;
			if (!DOT.equals(dent->d_name) && !DOTDOT.equals(dent->d_name))
			{
				if (fstatat(dirfd(srcDir), dent->d_name, &st,0) < 0)
				{
					continue;
				}
				if (arg == FILES_AND_FOLDERS)
				{
					dirs.add(dent->d_name);
				}
				else if (arg == ONLY_FILES)
				{
					if ((st.st_mode & S_IFREG) == S_IFREG)
					{
						dirs.add(dent->d_name);
					}
				}
				else
				{
					if ((st.st_mode & S_IFDIR) ==S_IFDIR)
					{
						dirs.add(dent->d_name);
					}
				}
			}
		}
		closedir(srcDir);
	}
	return dirs;
}

bool File::mkdir(bool nothrow)
{//http://linux.die.net/man/2/mkdir
	mode_t modo;
	modo = S_IRWXU | S_IRWXG | S_IRWXO;//pueden cambiar los valores, pero estos son por default en linux
	if (nothrow)
	{
		bool ret = ~::mkdir(getAbsolutePath(), modo);
		loadInfoFile();
		return ret;
	}
	else
	{
		if (::mkdir(getAbsolutePath(), modo) == -1)
		{
			switch(errno)
			{
			case EACCES:
				throw SecurityException("The parent directory does not allow write permission to the process, or one of the directories in pathname did not allow search permission");
			case EEXIST:
				throw Exception("Pathname already exists (not necessarily as a directory)");
			case EROFS:
				throw Exception("Pathname refers to a file on a read-only file system.");
			case EPERM:
				throw Exception("The file system containing pathname does not support the creation of directories");
			case ENOSPC:
				throw Exception("The new directory cannot be created because the user's disk quota is exhausted");
			case ENOMEM:
				throw Exception("Insufficient kernel memory was available");
			case ENOENT:
				throw Exception("A directory component in pathname does not exist or is a dangling symbolic link.");
			default:
				throw Exception(String("Excepcion no manejada: ") + errno + "\nVea: //http://linux.die.net/man/2/mkdir");
			}
		}
	}
	return true;
}

bool File::mkdir2(){
	String path;
	for (int i = 0; i < mDirStructure.size(); i++){
		path += mDirStructure[i];
		File file(path);
		//No existe, lo creamos
		if (!file.exist()){
			if (!file.mkdir()){
				return false;
			}
		}
		//Existe, pero no es un directorio
		else if (!file.isDirectory()){
			return false;
		}
	}
	return true;
}

String File::getRelativePath(){
	char workDir[PATH_MAX];
	getcwd(workDir, PATH_MAX);
	String ruta = workDir;
	String ret;
	if (ruta.charAt(ruta.length()-1)!='/') ruta+= "/";
	ArrayList<String> workStructure = toAbsolutePath(&ruta);
	int index = mDirStructure.size() - 1;
	for (int i = 0; i < mDirStructure.size();i++)//bucle para saber si debemos hacer "../"
	{
		if (workStructure.size()>i){
			if (mDirStructure[i] != workStructure[i]){
				index = i;
				break;
			}
		}
		else{
			index = i;
			break;
		}
	}

	if (index == 0)index++;//para no incluir el "/"
	for (int i = workStructure.size();i>index;i--)
	{
		ret += "../";
	}
	for (;index < mDirStructure.size();index++)
	{
		ret+=mDirStructure[index];
	}
	return ret;
}
String File::getParent(){
	if (mDirStructure.size()>1)
	{
		return mDirStructure[mDirStructure.size()-2];
	}
	return mDirStructure[0];
}

String File::getName(){
	return mDirStructure[mDirStructure.size()-1];
}

String File::getAbsolutePath(){
	String ret;
	for (int  i = 0; i <  mDirStructure.size();i++)
	{
		ret+= mDirStructure[i];
	}
	return ret;
}

bool File::remove(){
	int flag = isDirectory()?AT_REMOVEDIR: 0;
	return ~unlinkat(0, getAbsolutePath(), flag);
}


String File::getWorkDir()
{
	char workDir[PATH_MAX];
	getcwd(workDir, PATH_MAX);
	return workDir;
}
bool File::setWorkDir(String dir)
{
	return ~chdir(dir);
}

/**
 * Esta es una version beta, puede cambiar en dependiendo la distribucion linux
 */
ArrayList<String> File::listRoots()
{
	ArrayList<String> list;
	FILE *f = setmntent(INFO_FILE, "r");
	if (f != NULL)
	{
		struct mntent *prop;
		while((prop = getmntent(f))!= NULL)
		{
			String fsname = prop->mnt_fsname;
			if (fsname != "none")
			{
				String prefix = fsname.substring(0,6);
				if (prefix == "/dev/s" || prefix == "/dev/h")
					list.add(prop->mnt_dir);//donde esta montado
			}
		}
		endmntent(f);
	}
	return list;
}
