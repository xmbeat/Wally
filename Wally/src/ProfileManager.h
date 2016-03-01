/*
 * ProfileManager.h
 *
 *  Created on: 27/07/2015
 *      Author: xmbeat
 */

#ifndef PROFILEMANAGER_H_
#define PROFILEMANAGER_H_
#include <Utils/ArrayList.h>
#include <Utils/String.h>
#include <Utils/File.h>
#include <Utils/TreeSet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Utils/MapString.h>
class ProfileManager{
private:
	String mBaseName;
	String mIndexedName;
	MapString< ArrayList<String> *> mContainer;
public:
	ProfileManager(String baseName, String indexedName){
		mBaseName = baseName;
		mIndexedName = indexedName;
		File file(mBaseName);
		file.mkdir2();
	}
	bool erase(int index){
		String path = mBaseName + index;
		File file(path);
		return file.remove();
	}

	bool load(const char* filename){
		String path = mBaseName + "/" + filename;
		FILE* file = fopen(path.c_str(), "r");
		if (file == NULL){
			return false;
		}
		char* buffer = NULL;
		size_t size = 0;
		while (getline(&buffer, &size, file) > 0){
			int len = strlen(buffer);
			if (buffer[len - 1] == '\n'){
				buffer[len - 1] = 0;
			}
			String line(buffer);
			int i = line.inString(":", 0);
			if (i > 0){
				String key = line.substring(0, i);
				String value = line.substring(i + 1);
				ArrayList<String> *data = mContainer.get(key);
				if (!data){
					data = new ArrayList<String>();
					mContainer.put(key, data);
				}
				data->add(value);
			}
		}
		if (buffer)
			free(buffer);
		fclose(file);
		return true;
	}

	bool load(int index){
		String path = mBaseName + "/" + mIndexedName + index;
		FILE* file = fopen(path, "r");
		if (file == NULL){
			return false;
		}
		char* buffer = NULL;
		size_t size = 0;
		while (getline(&buffer, &size, file) > 0){
			int len = strlen(buffer);
			if (buffer[len - 1] == '\n'){
				buffer[len - 1] = 0;
			}
			String line(buffer);
			int i = line.inString(":", 0);
			if (i > 0){
				String key = line.substring(0, i);
				String value = line.substring(i + 1);
				ArrayList<String> *data = mContainer.get(key);
				if (!data){
					data = new ArrayList<String>();
					mContainer.put(key, data);
				}
				data->add(value);
			}
		}
		if (buffer)
			free(buffer);
		fclose(file);
		return true;
	}

	void clear(){
		mContainer.clearAndDelete();
	}
	ArrayList<String>* get(String key){
		return mContainer.get(key);
	}

	String getString(String key){
		ArrayList<String>* data = mContainer.get(key);
		if (data && data->size() > 0){
			return data->get(0);
		}
		return String();
	}

	ArrayList<String>* set(String key, ArrayList<String> &data){
		ArrayList<String>* aux = new ArrayList<String>(data);
		return mContainer.put(key, aux);
	}

	void add(String key, ArrayList<String> &data){
		ArrayList<String>* aux = mContainer.get(key);
		if (!aux){
			aux = new ArrayList<String>();
			mContainer.put(key, aux);
		}
		aux->addAll(&data);
	}

	void addString(String key, String data){
		ArrayList<String> *aux = mContainer.get(key);
		if (!aux){
			aux = new ArrayList<String>();
			mContainer.put(key, aux);
		}
		aux->add(data);
	}

	bool save(const char* filename){
		String path = mBaseName + "/" + filename;
 		FILE* file = fopen(path.c_str(), "w");
		if (file == NULL){
			return false;
		}
		ArrayList<String> keys = mContainer.getKeys();
		for (int i = 0; i < keys.size(); i++){
			ArrayList<String>* current = mContainer.get(keys[i]);
			if (current){
				for (int j = 0; j < current->size(); j++){
					String line = keys[i] + ":" + current->get(j) + "\n";
					fputs(line.c_str(), file);
				}
			}
		}
		fclose(file);
		return true;
	}

	bool save(int index){
		String path = mBaseName + "/" + mIndexedName + index;
		FILE* file = fopen(path, "w");
		if (file == NULL){
			return false;
		}
		ArrayList<String> keys = mContainer.getKeys();
		for (int i = 0; i < keys.size(); i++){
			ArrayList<String>* current = mContainer.get(keys[i]);
			if (current){
				for (int j = 0; j < current->size(); j++){
					String line = keys[i] + ":" + current->get(j) + "\n";
					fputs(line.c_str(), file);
				}
			}
		}
		fclose(file);
		return true;
	}
};



#endif /* PROFILEMANAGER_H_ */
