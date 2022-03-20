
#import <Cocoa/Cocoa.h>

#ifdef MAC_OS_X_VERSION_10_10

void set_unified_toolbar(void* ptr){
    NSWindow* win = (NSWindow*) ptr;
    win.titleVisibility = NSWindowTitleHidden;
}

#endif