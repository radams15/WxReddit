
#import <Cocoa/Cocoa.h>

extern "C" void tweak(void* window){
#ifdef MAC_OS_X_VERSION_10_10

#if USE_HEADERBAR
    auto* win = (NSWindow*) window;
    win.titleVisibility = NSWindowTitleHidden;

    win.titlebarAppearsTransparent = true;

#endif

    NSToolbar* toolbar = win.toolbar;
    if(toolbar != nullptr){
        toolbar.showsBaselineSeparator = false;
    }
#endif
}