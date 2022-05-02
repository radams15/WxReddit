ARCH ?= -arch ppc
TARGET ?= -mmacosx-version-min=10.4 -isysroot /Developer/SDKs/MacOSX10.4u.sdk
CC=gcc
CXX=g++

CJSON_SRC=lib/libreddit/lib/cJSON/cJSON.c lib/libreddit/lib/cJSON/cJSON_Utils.c

B64_SRC=lib/libreddit/lib/librequest/lib/b64.c/buffer.c lib/libreddit/lib/librequest/lib/b64.c/decode.c lib/libreddit/lib/librequest/lib/b64.c/encode.c

REQ_SRC=lib/libreddit/lib/librequest/src/main/res.c lib/libreddit/lib/librequest/src/main/header.c lib/libreddit/lib/librequest/src/main/request_generic.c
REDDIT_SRC=lib/libreddit/src/Reddit.c lib/libreddit/src/Post.c lib/libreddit/src/List.c lib/libreddit/src/Subreddit.c lib/libreddit/src/Comment.c

INCLUDES=-Ilib/libreddit/lib/librequest/include -Ilib/libreddit/include -Ilib/libreddit/lib/cJSON -Ilib/libreddit/lib/librequest/lib/b64.c/

WXREDDIT_SRC=src/main/MainApp.cpp src/main/MainFrame.cpp src/main/MainFrameCust.cpp src/main/Table.cpp src/main/Util.cpp src/main/main.cpp src/main/specific/Cocoa.mm

libreddit.dylib:
	${CC} -fPIC -dynamiclib ${ARCH} ${TARGET} -o libreddit.dylib ${INCLUDES} ${CJSON_SRC} ${B64_SRC} ${REQ_SRC} lib/libreddit/lib/librequest/src/main/backends/darwin/request.m ${REDDIT_SRC} -framework Foundation
 
libreddit.so:
	${CC} -fPIC -shared -o libreddit.so ${INCLUDES} ${CJSON_SRC} ${B64_SRC} ${REQ_SRC} lib/librequest/src/main/backends/curl/request.c ${REDDIT_SRC} `pkg-config --libs --cflags libcurl`

WxReddit:
	${CC} ${ARCH} ${TARGET} -o WxReddit ${INCLUDES} ${WXREDDIT_SRC} ${CJSON_SRC} ${B64_SRC} ${REQ_SRC} lib/libreddit/lib/librequest/src/main/backends/darwin/request.m ${REDDIT_SRC} -framework Foundation `wx-config --libs --cflags` -lstdc++
	
clean:
	rm -rf *.dylib *.so
