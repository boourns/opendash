#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#ifdef ENABLE_XBOX
   #include <hal/xbox.h>
extern "C" {
   #include <hal/fileio.h>
}
#endif

#include "MenuNode.h"
//#include "ActionNode.h"
#include "BootScript.h"
#include "Environment.h"
#include "debug.h"

extern Environment *theEnv;

BootScript::BootScript() : MenuNode()
{
	mPath = 0;
  mArg = 0;
  mMinimize = 0;
}

BootScript::~BootScript()
{
	if (mPath) {
	   delete[] mPath;
  }
  if (mArg) {
     delete[] mArg;
	}
}

void BootScript::Execute()
{
	LOG_ENTRY("BootScript::Execute()")
	
	struct stat sBuf;
	char cmd[1024];

  cmd[0] = 0;
  strcat(cmd, mPath);
  if (mArg) {
    strcat(cmd, " \"");
    strcat(cmd, mArg);
    strcat(cmd, "\"");
  }

  if (mMinimize) {
    theEnv->minimize();
  }

  system(cmd);

  if (mMinimize) {
    theEnv->maximize();
  }
}

void BootScript::xmlConfigure(xmlNode *fNode)
{
	LOG_ENTRY("BootScript::xmlConfigure")
	
        MenuNode::xmlConfigure(fNode);
	while (fNode) {
	   if (!strcmp((char *) fNode->name, "Path") && fNode->children) {
	      setPath((char *) fNode->children->content);
	   }
     if (!strcmp((char *) fNode->name, "Minimize")) {
        mMinimize = 1;
     }
	   fNode = fNode->next;
	}
        if (!mName && mPath) {
           extractName(mPath);
        }
}

void BootScript::extractName(char *fPath)
{
      	if (mName) {
           free(mName);
        }

        mName = strdup(basename(fPath));
        if (mName[strlen(mName)-4] == '.') {
          mName[strlen(mName)-4] = 0x00;
        }
}

void BootScript::extractDebugName(char *fPath)
{
	LOG_ENTRY("BootScript::extractDebugName")
	
}	
	
void BootScript::setMinimize(int val)
{
  mMinimize = val;
}

void BootScript::setPath(char *fPath)
{
	LOG_ENTRY("BootScript::setPath")
	
	if (fPath) {
	   if (mPath) {
	      delete[] mPath;
	   }
	   mPath = new char[strlen(fPath)+1];
	   strcpy(mPath, fPath);
	}
}

void BootScript::setArg(char *fArg)
{
	LOG_ENTRY("BootScript::setArg")
	
	if (fArg) {
	   if (mArg) {
	      delete[] mArg;
	   }
	   mArg = new char[strlen(fArg)+1];
	   strcpy(mArg, fArg);
	}
}


char *BootScript::getPath()
{
	return mPath;
}

