/*
 * WallpaperManager.h
 *
 *  Created on: 20/07/2015
 *      Author: xmbeat
 */

#ifndef WALLPAPERMANAGER_H_
#define WALLPAPERMANAGER_H_
#include <Utils/ArrayList.h>
#include <time.h>
#include <IPC/Process.h>
#include <Utils/Thread.h>
#include <stdlib.h> //getenv

#include <stdio.h>
static int pseudo_random_number(int seed){
    int w = ((seed & 0xFFFF) + 7933) * 15487429;
    int z = ((seed >> 16) + 15487429) * 179425879;
    z = 36969 * (z & 0xFFFF) + (z >> 16);
    w = 18000 * (w & 0xFFFF) + (w >> 16);
    return ((z  << 16) + w) & 0x7FFFFFFF;
}


class WallpaperManager: public Synchronizable{
private:
	ArrayList<String> mImages;
	ArrayList<int> mHistory;
	int mHistoryIndex;
	int mCurrentIndex;
	bool mRandom;
	class AutoChanger: public Thread{
	private:
		int mDelay;
		int mElapsed;
		WallpaperManager *mManager;
		bool mAlive;
	public:
		AutoChanger(WallpaperManager *manager){
			mDelay = 0;
			mElapsed = 0;
			mManager = manager;
			mAlive = true;
		}
		void setDelay(int seconds){
			mDelay = seconds;
			mElapsed = mDelay;
		}
		void stop(){
			mAlive = false;
		}

		void run(){
			while(mAlive){
				if (mDelay > 0){
					mElapsed++;
					if(mElapsed >= mDelay){
						mElapsed = 0;
						mManager->next();
					}
				}
				Thread::sleep(1000);
			}
		}
	};
	AutoChanger *mChanger;
protected:
	void setActive2(int index){
		if (index < mImages.size() && index >= 0){
			int pid = -1;
			char *desktop = getenv("DESKTOP_SESSION");
			if (String("mate").equals(desktop, true)){
				pid = Process::createProcess("gsettings", "set", "org.mate.background","picture-filename", mImages[index].c_str(), NULL, false);
			}
			else if (String("gnome").equals(desktop, true)){
				String param = String("file://") + mImages[index];
				//pid = Process::createProcess("gsettings", "set", "org.gnome.desktop.background", "draw-background", "false", NULL, false);
				pid = Process::createProcess("gsettings", "set", "org.gnome.desktop.background","picture-uri", param.c_str(), NULL, false);//pid = Process::createProcess("gsettings", "set", "org.gnome.desktop.background", "draw-background", "true", NULL, false);
				if (pid <= 0){
					pid = Process::createProcess("gconftool-2", "-t", "str", "--set", "/desktop/gnome/background/picture_filename", mImages[index].c_str(), NULL, false);

				}
			}
			else if (String ("KDE").equals(desktop, true)){
				String param = String("string:") + mImages[index];
				pid = Process::createProcess("dbus-send", "--session", "--dest=org.new_wallpaper.Plasmoid", "--type=method_call", "org/new_wallpaper/Plasmoid/0", "org.new_wallpaper.Plasmoid.SetWallpaper", param.c_str(), NULL, false);
			}
			if (pid <= 0){
				//  string:/path/to/your/wallpaper
				fprintf(stderr, "No se pudo cambiar el fondo\n");
			}
		}
	}
public:
	WallpaperManager(){
		mCurrentIndex = -1;
		mHistoryIndex = -1;
		mRandom = false;
		mChanger = new AutoChanger(this);
		mChanger->start();
	}
	virtual ~WallpaperManager(){
		mChanger->stop();
		mChanger->join();
		delete mChanger;
	}
	void setImages(ArrayList<String> images){
		synchronizeOn();
		mImages = images;
		mHistory.clear();
		mHistory.ensureCapacity(mImages.size());
		mHistoryIndex = -1;
		synchronizeOff();
	}

	void next(){
		synchronizeOn();
		if (mImages.size() > 0){
			mHistoryIndex = (mHistoryIndex + 1) % mImages.size();
			if (mHistory.size() < mImages.size()){
				if (mRandom){
					mCurrentIndex = pseudo_random_number(time(NULL)) % mImages.size();
					while (mHistory.lastIndexOf(mCurrentIndex) >= 0){
						mCurrentIndex = (mCurrentIndex + 1) % mImages.size();
					}
				}
				else{
					mCurrentIndex = (mCurrentIndex + 1) % mImages.size();
				}
				mHistory.add(mCurrentIndex);
			}
			if (mHistoryIndex < mHistory.size()){
				int index = mHistory[mHistoryIndex];
				setActive2(index);
			}
		}
		synchronizeOff();
	}

	void previous(){
		synchronizeOn();
		mHistoryIndex = (mHistoryIndex - 1);
		if (mHistoryIndex < 0){
			mHistoryIndex = mHistory.size() - 1;
		}
		if (mHistoryIndex >= 0){
			int index = mHistory[mHistoryIndex];
			setActive2(index);
		}
		synchronizeOff();
	}

	void setRandom(bool value){
		mRandom = value;
		mHistoryIndex = -1;
		mHistory.clear();
	}

	bool isRandom(){
		return mRandom;
	}

	void setDelay(int seconds){
		mChanger->setDelay(seconds);
	}

	void setActive(int index){
		synchronizeOn();
		setActive2(index);
		synchronizeOff();
	}
};


#endif /* WALLPAPERMANAGER_H_ */
