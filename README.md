# Lupinho Libretro

Libretro core for [Lupinho](https://github.com/lupi-org-br/lupinho) the simulator for the Lupi fantasy console. Load a `.lupi` game or `game.lua` inside a game directory in RetroArch.

## Build

```bash
git clone --recurse-submodules https://github.com/humbertodias/lupinho-libretro.git
cd lupinho-libretro
make libretro
```
writes `dist/lupinho_libretro.so` (Linux), `.dylib` (macOS) or `.dll` (Windows), plus `dist/lupinho_libretro.info`.

If the repository was cloned without submodules:

```bash
git submodule update --init
```

## Core

- Install
```bash
make core/install
```
Copy the core and `lupinho_libretro.info` into RetroArch's cores directory

## Game
```bash
make game/clone GAME_URL=https://github.com/lupi-org-br/caio-pernocas
```
Change `GAME_URL` to clone another lupi game 

Codec

```bash
make game/codec
```
Convert game assets to release console format into `dist/game-release`

## RetroArch

```bash
make retroarch/run 
```
<img width="1552" height="950" alt="image" src="https://github.com/user-attachments/assets/6b51f732-0ed8-4019-888e-8028058782f0" />



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
