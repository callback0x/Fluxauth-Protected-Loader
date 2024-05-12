#include "implement.h"
#include <thread>


#include "../antidebug/antidebug.h"
#include "../virtualprotect/virtualprotect.h"
#include "../antiprocess/antiprocess.h"
#include "../thread/dummythread.h"

 void CheckDebugger()
{
    Raise_Check();
    EnumWindows(EnumWindowsProc, 0);
    CheckCloseHandleDebugger();
    std::thread(contextthread).detach();
}

 void virtualProtect() {
     virtualprotect();
 }

 void dummythread() {
     std::thread(IfResumeDummy).detach();
 }