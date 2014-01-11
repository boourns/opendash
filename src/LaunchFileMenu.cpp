#include "MenuNode.h"
#include "SubMenuNode.h"
#include "FileMenu.h"
#include "LaunchFileMenu.h"
#include "BootScript.h"
#include "Environment.h"

#define debugPrint printf

#include "debug.h"

extern Environment *theEnv;

LaunchFileMenu::LaunchFileMenu() : FileMenu()
{
	// yeah
  mChildren = 0;
}

LaunchFileMenu::~LaunchFileMenu()
{
	
}

void LaunchFileMenu::xmlConfigure(xmlNode *fNode)
{
	FileMenu::xmlConfigure(fNode);
}

void LaunchFileMenu::Execute()
{
	LOG_ENTRY("LaunchFileMenu::Execute")

	if (!mChildren) {

 	   List<char> *fTargets = findFiles();
	   List<char> *t = fTargets;

	   while (t) {
	      if (t->getData()) {
                 BootScript *p = new BootScript();
                 p->setPath(mTarget);
                 p->setArg(t->getData());
	               p->extractName(t->getData());
                 if (mChildren) {
                    mChildren->addItem(p);
                 } else {
                    mChildren = new List<MenuNode>(p, 0x00);
                 }
                 delete[] t->getData();
                 t->setData(0);
              }
	      t = t->getLink();
	   }
           delete fTargets;

	}

        SubMenuNode::Execute();

	LOG_EXIT("LaunchFileMenu::Execute")
}
