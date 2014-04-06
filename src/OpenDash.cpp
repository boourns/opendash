#ifndef NO_TYPEINFO
#include <typeinfo>
#endif

#include <libxml/tree.h>
#include <libxml/parser.h>

#include "MenuNode.h"
#include "SubMenuNode.h"
#include "FileMenu.h"
#include "XBEMenu.h"
#include "SkinMenu.h"
#include "BootScript.h"
#include "Environment.h"
#include "XboxInfo.h"
#include "Controller.h"
#include "HotKey.h"

#include "SDL.h"

#define CONFIG_FILE "config.xml"

Environment *theEnv;

extern "C" {
#define debugPrint printf
  int main(int argc, char **argv)
  {
    SDL_Event event;
    theEnv = new Environment();
    int next_clock, remaining;
    int dirty = 2;

    xmlDoc *theDoc = 0;
    xmlNode *theRoot = 0;

    theEnv->initialize(argc, argv);

    theDoc = xmlReadFile(CONFIG_FILE, NULL, 0);

    if (theDoc == NULL) {
      printf("Error opening file %s\n", CONFIG_FILE);
      exit(1);
    }

    theRoot = xmlDocGetRootElement(theDoc);

    theEnv->xmlConfigure(theRoot->children);

    theEnv->loadSkinPath();

    if (! theEnv->loadSkin(theEnv->getSkinPath())) {
      printf("Cannot load skin\n");
      xmlFreeDoc(theDoc);
      exit(1);
    }

    /*       theEnv->initialize(); */

    theEnv->ensureSkin();

    theEnv->renderMenu();
    Controller *c = theEnv->getController();

    while (1) {
      next_clock = SDL_GetTicks() + 30;

      theEnv->update();

      if (dirty > 0) {
        theEnv->drawScreen();
        dirty--;
      }

      if (theEnv->getMenuState() != State_Normal) {
        dirty = 10;
      }

      // event handling now done in controller thread
      while (SDL_PollEvent(&event)) {
        theEnv->getController()->update(&event);

        if (c->getState(Ctrl_Up) == Button_Pressed) {
          theEnv->setMenuSelected(theEnv->getMenuSelected()-1);
          theEnv->renderMenu();
        } else if (c->getState(Ctrl_Down) == Button_Pressed) {
          theEnv->setMenuSelected(theEnv->getMenuSelected()+1);
          theEnv->renderMenu();
        } else if (c->getState(Ctrl_A) == Button_Pressed) {
          MenuNode *t = theEnv->getCurrentMenu()->getChildren()->getData(theEnv->getMenuSelected());

          if (t) {
            t->Execute();
            theEnv->renderMenu();
          }

          c->setState(Ctrl_A, Button_Released);
        } else if (c->getState(Ctrl_B) == Button_Pressed) {
          MenuNode *t = theEnv->getCurrentMenu()->getParent();
          if (t) {
            t->Execute();
            theEnv->renderMenu();
          }
          c->setState(Ctrl_B, Button_Released);
          c->setState(Ctrl_Y, Button_Released);
        }
      }
      remaining = next_clock - SDL_GetTicks();
      if (remaining > 0)
      {
        SDL_Delay(remaining);
      }
    }

    xmlFreeDoc(theDoc);
  }

}

