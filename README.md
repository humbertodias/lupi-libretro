# Lupinho Libretro

Libretro core for [Lupinho](https://github.com/humbertodias/lupinho), the simulator for the Lupi fantasy console. Load a `.lupi` game (or a directory with `game.lua`) in RetroArch.

Lupinho is a submodule and is compiled as it is on `main`. The Libretro frontend, joypad input, RGB565 output, portable `.lupi` extraction, and the BGR555 palette fix live in this repository, so the simulator does not need a `LIBRETRO` build mode.

## Build

```bash
git clone --recurse-submodules https://github.com/humbertodias/lupinho-libreto.git
cd lupinho-libreto
make
```

If the repository was cloned without submodules:

```bash
git submodule update --init
```

`make` writes:

- `dist/lupinho_libretro.so` on Linux
- `dist/lupinho_libretro.dylib` on macOS
- `dist/lupinho_libretro.dll` on Windows
- `dist/lupinho_libretro.info`

Dependencies: a C99 compiler, make, and zlib. Cross-compile the Windows core from Linux or macOS with MinGW-w64 and a MinGW zlib:

```bash
make libretro-win
```

## RetroArch

Copy `lupinho_libretro.*` and `lupinho_libretro.info` into RetroArch's cores directory, then load a `.lupi` file. The core needs a full path (`need_fullpath`) and extracts the archive itself (`block_extract`).

## Release

Pushing a `v*` tag builds the Linux, macOS, and Windows cores and publishes them on a GitHub Release, together with `lupinho_libretro.info`.

```bash
git tag v0.1.0
git push origin v0.1.0
```

The same workflow can be started from the Actions tab; it asks for the tag name.

A directory that already contains `game.lua` also loads, which is useful while iterating on a game.

| Retropad | Lupi |
| --- | --- |
| D-pad / left stick | UP, DOWN, LEFT, RIGHT |
| A | BTN_X |
| B | BTN_Z |
| X | BTN_Q |
| Y | BTN_E |
| L | BTN_F |
| R | BTN_G |
| Start / Select | Start / Select |

Keyboard comes from RetroArch's retropad mapping. The core does not read the host keyboard itself.

`require("palette")` loads `palette.lua` and adds `Palette.hex(0xRRGGBB)`, which returns a 0-based palette index.

## Layout

```
src/        Libretro frontend and the host seams (input, video, zip, palette)
lupinho/    Simulator submodule: ui, Lua API, and Lua 5.5
```

`palset` in the submodule still swaps the red and blue channels of a lupi-codec BGR555 word. This core compiles that function under another name and links the corrected `palset` from `src/palette.c`.
