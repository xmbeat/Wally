/*
 * gtk2-dev, libappindicator-dev (NECESARIO PARA COMPILAR, NO PARA EJECUTAR)
 * gtk-builder-convert dynamic_wallpaper.glade interface.xml &&
 * gcc -c *.c `pkg-config --libs --cflags gtk+-2.0`-I/usr/include/libappindicator-0.1/ &&
 * gcc -o main *.o `pkg-config --libs --cflags gtk+-2.0` -I/usr/include/libappindicator-0.1/ -lappindicator
 */

#include <gui/ClassControls.h>
#include <Utils/String.h>
#include <IPC/InstanceManager.h>
#include "Controller.h"
Controller *controlador;
//Llamado cuando algun proceso igual al nuestro, nos envia un mensaje
void onMessageArrived(int key){
	controlador->onMessageArrived(key);
}
int main(int argc, char** argv) {
	InstanceManager instances(666, onMessageArrived);
	//Si este programa aun no esta corriendo
	if (instances.getInstancesCount() == 0) {
		instances.registerInstance();
		controlador = new Controller(argc, argv);
		if (argc > 1 && String("--hidden") == argv[1]) {
			printf("Iniciando en modo oculto\n");
		} else {
			controlador->setVisible(true);
		}
		gtk_main();
		delete controlador;
	}
	else{
		int pid = instances.getPID(0);
		instances.send(pid, "RESTORE", 7);
	}
	return 0;
}
