
#import <Cocoa/Cocoa.h>

extern "C" void tweak(void* window){
#ifdef MAC_OS_X_VERSION_10_10
    NSWindow* win = (NSWindow*) ptr;
    win.titleVisibility = NSWindowTitleHidden;
#endif
}