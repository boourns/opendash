#ifndef __LAUNCHFILEMENU_H__
#define __LAUNCHFILEMENU_H__

#include <libxml/tree.h>
#include <libxml/parser.h>


class LaunchFileMenu : public FileMenu {

public:

   LaunchFileMenu();
   ~LaunchFileMenu();
   
   virtual void xmlConfigure(xmlNode *fNode);
   
   virtual void Execute();
   
};

#endif

