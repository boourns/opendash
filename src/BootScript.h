#ifndef __BOOTXBE_H__
#define __BOOTXBE_H__

#include <libxml/tree.h>
#include <libxml/parser.h>

class BootScript : public MenuNode {

public:

   BootScript();
   ~BootScript();
   
   virtual void Execute();
   virtual void xmlConfigure(xmlNode *fNode);
   
   void setPath(char *fPath);
   void setArg(char *fPath);
   void setMinimize(int val);
   void extractName(char *fPath);
   void extractDebugName(char *fPath);
   
   char *getPath();

protected:
   
   char *mPath;
   char *mArg;
   int mMinimize;
};

#endif
   
