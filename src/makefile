#

MOBJS = MenuNode.o SubMenuNode.o FileMenu.o LaunchFileMenu.o Script.o SkinMenu.o BootScript.o DialogBox.o QuestionBox.o LoadSkin.o FileAction.o XboxAction.o LoadKey.o XboxInfo.o Controller.o HotKey.o Environment.o FontResource.o Resources.o Resource.o ImageResource.o Element.o Elements.o Generic.o Setting.o

OBJS = OpenDash.o $(MOBJS)

CPP = g++

CPP_FLAGS = -g `xml2-config --cflags` `sdl-config --cflags` -I/usr/local/include/SDL


all: \
	OpenDash

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(INCLUDE)

OpenDash: $(OBJS)
	$(CPP) -o $@ $(OBJS) -lSDL_ttf -lSDL_image `sdl-config --libs` `xml2-config --libs` -lstdc++

testBootXBE: testBootXBE.o $(OBJS)
	$(CPP) -o $@ testBootXBE.o $(MOBJS) -lSDL_ttf -lSDL_image `xml2-config --libs` -lstdc++

testController: testController.o $(OBJS)
	$(CPP) -o $@ testController.o $(MOBJS) -lSDL_ttf -lSDL_image `sdl-config --libs` `xml2-config --libs` -lstdc++


clean: 
	rm -f *.o *.exe *.dll *.xbe *.cxbe


