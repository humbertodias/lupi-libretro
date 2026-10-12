# Libretro core for Lupinho. The simulator stays in the lupinho/ submodule;
# this makefile only adds the frontend and the seams that must not live there.

LUPI := lupinho/src
LUA  := $(LUPI)/libs/linux/lua-5.5.0/src

ifeq ($(wildcard $(LUPI)/ui.c),)
$(error lupinho submodule is missing. Run: git submodule update --init)
endif

MINGW_CC ?= x86_64-w64-mingw32-gcc

ifeq ($(OS),Windows_NT)
  EXT := dll
  SOFLAGS := -shared
  LIBS := -lz -lm -static-libgcc
  LUAFLAGS :=
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Darwin)
    EXT := dylib
    SOFLAGS := -dynamiclib
    LIBS := -lz -lm
    LUAFLAGS := -DLUA_USE_POSIX
  else
    EXT := so
    SOFLAGS := -shared
    LIBS := -lz -lm -ldl
    LUAFLAGS := -DLUA_USE_POSIX
  endif
endif

CC ?= gcc
CFLAGS := -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -O2 -fPIC $(LUAFLAGS)
CPPFLAGS := -Isrc/compat -Isrc -I$(LUPI) -I$(LUA)

OUTPUT := dist/lupinho_libretro.$(EXT)

CORE_SRCS := libretro.c input.c video.c palette.c zip.c raylib_shim.c
CORE_OBJS := $(addprefix build/,$(CORE_SRCS:.c=.o))

LUA_SRCS := \
	lapi.c lcode.c lctype.c ldebug.c ldo.c ldump.c lfunc.c lgc.c llex.c \
	lmem.c lobject.c lopcodes.c lparser.c lstate.c lstring.c ltable.c ltm.c \
	lundump.c lvm.c lzio.c lauxlib.c lbaselib.c lcorolib.c ldblib.c liolib.c \
	lmathlib.c loadlib.c loslib.c lstrlib.c ltablib.c lutf8lib.c linit.c
LUA_OBJS := $(addprefix build/lua/,$(LUA_SRCS:.c=.o))

OBJS := $(CORE_OBJS) build/ui.o build/lua_api.o $(LUA_OBJS)

.PHONY: all libretro libretro-win clean

all: libretro

libretro: $(OUTPUT)

$(OUTPUT): $(OBJS)
	@mkdir -p dist
	$(CC) $(SOFLAGS) -o $@ $(OBJS) $(LIBS)
	cp -f src/lupinho_libretro.info dist/lupinho_libretro.info

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/lua_api.o: $(LUPI)/lua_api.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Keep lupinho's palset symbol out of the link. palette.c supplies the
# BGR555 channel order used by lupi-codec.
build/ui.o: $(LUPI)/ui.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Dpalset=lupi_core_palset -c $< -o $@

build/lua/%.o: $(LUA)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

libretro-win:
	$(MAKE) all CC="$(MINGW_CC)" EXT=dll SOFLAGS="-shared" LIBS="-lz -lm -static-libgcc" LUAFLAGS=""

clean:
	rm -rf build dist
