#!/bin/bash

pwd

mkdir -p WxReddit.app/Contents/Frameworks

WX_LOC=/usr/local/lib/libwx_mac-2.8.0.dylib


cp lib/libreddit/libreddit.dylib WxReddit.app/Contents/Frameworks/
cp lib/libreddit/lib/librequest/librequest.dylib WxReddit.app/Contents/Frameworks/

#cp $WX_LOC WxReddit.app/Contents/Frameworks/libwx_mac.dylib

install_name_tool -change $PWD/lib/libreddit/libreddit.dylib @executable_path/../Frameworks/libreddit.dylib WxReddit.app/Contents/MacOS/WxReddit
install_name_tool -change $PWD/lib/libreddit/lib/librequest/librequest.dylib @executable_path/../Frameworks/librequest.dylib WxReddit.app/Contents/MacOS/WxReddit
install_name_tool -change $PWD/lib/libreddit/lib/librequest/librequest.dylib @executable_path/../Frameworks/librequest.dylib WxReddit.app/Contents/Frameworks/libreddit.dylib

#install_name_tool -change $WX_LOC @executable_path/../Frameworks/libwx_mac.dylib WxReddit.app/Contents/MacOS/WxReddit
