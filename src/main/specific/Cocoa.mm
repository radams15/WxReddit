
#import <Cocoa/Cocoa.h>

extern "C" void tweak(void* window){
#ifdef __WXOSX_COCOA__

    NSWindow* win = (NSWindow*) window;

#if USE_HEADERBAR && defined(MAC_OS_X_VERSION_10_10)
    win.titleVisibility = NSWindowTitleHidden;

    win.titlebarAppearsTransparent = true;

#endif

    NSToolbar* toolbar = win.toolbar;
    if(toolbar != NULL){
        toolbar.showsBaselineSeparator = false;
    }
#endif
}