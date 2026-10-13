# Lupinho Libretro

Libretro core for [Lupinho](https://github.com/lupi-org-br/lupinho) the simulator for the Lupi fantasy console. Load a `.lupi` game or `game.lua` inside a game directory in RetroArch.

## Build

```bash
git clone --recurse-submodules https://github.com/humbertodias/lupinho-libretro.git
cd lupinho-libretro
make
```

If the repository was cloned without submodules:

```bash
git submodule update --init
```

## Core

- Build
```shell
make libretro
``` 
writes `dist/lupinho_libretro.so` (Linux), `.dylib` (macOS) or `.dll` (Windows), plus `dist/lupinho_libretro.info`.

Dependencies: a C99 compiler, make and zlib.

- Install
```bash
make core/install
```
Copy the core and `lupinho_libretro.info` into RetroArch's cores directory

## Game
```bash
make game/clone GAME_URL=https://github.com/lupi-org-br/caio-pernocas
```
Codec

```bash
make game/codec
```

## RetroArch

```bash
make retroarch/run 
```

<img width="1552" height="950" alt="image" src="https://github.com/user-attachments/assets/7ecad6d9-47b0-4477-998e-24266e3b49ac" />


## Joystick
| Retropad | Lupi |
| --- | --- |
| D-pad / left stick | UP, DOWN, LEFT, RIGHT |
| A | BTN_X |
| B | BTN_Z |
| X | BTN_Q |
| Y | BTN_E |
| L | BTN_F |
| R | BTN_G |
| Start / Select | ? / ? |
