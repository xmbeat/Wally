from gi.repository import Caja, GObject
import subprocess

class ColumnExtension(GObject.GObject, Caja.MenuProvider):
    def __init__(self):
        pass

    def menu_activate_cb(self, menu, files):
    	mimes = ["image/jpeg", "image/png", "image/gif", "image/x-ms-bmp"]
    	for file in files:
    		for mime in mimes:
    			if file.is_mime_type(mime):
    				subprocess.Popen(["wally", "add", file.get_location().get_path()])
    	
    def get_file_items(self, window, files):
    	if len(files) > 0:
		    file = files[0]
		    item = Caja.MenuItem(
		        name="Wally::AddImages",
		        label="Agregar a wally",
		        tip="Agregar %s" % file.get_name(),
		        icon="/home/xmbeat/bin/resources/desktop.png"
		    )
		    item.connect('activate', self.menu_activate_cb, files)
		    
		    return [item]

	def get_background_items(self, window, file):
		submenu = Caja.Menu()
		submenu.append_item(Caja.MenuItem(name='ExampleMenuProvider::Bar2', 
		                                 label='Bar2', 
		                                 tip='',
		                                 icon=''))

		menuitem = Caja.MenuItem(name='ExampleMenuProvider::Foo2', 
		                                 label='Foo2', 
		                                 tip='',
		                                 icon='')
		menuitem.set_submenu(submenu)

		return menuitem

