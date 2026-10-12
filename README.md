# Lupinho Libretro

Libretro core for [Lupinho](https://github.com/humbertodias/lupinho), the simulator for the Lupi fantasy console. Load a `.lupi` game, or `game.lua` inside a game directory, in RetroArch.

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

`make` writes `dist/lupinho_libretro.so` (Linux), `.dylib` (macOS), or `.dll` (Windows), plus `dist/lupinho_libretro.info`.

Dependencies: a C99 compiler, make, and zlib. Cross-compile the Windows core with MinGW-w64:

```bash
make libretro-win
```

## RetroArch

Copy the core and `lupinho_libretro.info` into RetroArch's cores directory. Load a `.lupi` file, or open `game.lua` inside a game directory.

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
