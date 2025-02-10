# gmsv_trueterm
Truecolor terminal output for Garry's Mod Linux dedicated servers.

An amalgamation of [gm_spew](https://github.com/danielga/gm_spew), [gm_xterm](https://github.com/Metastruct/gm_xterm) and [gm_xconsole_x64](https://github.com/Earu/gmsv_xconsole_x64).

# Installation
Put the DLL file in `lua/bin/`, then choose a method to load it

## Method 1: Standard module
`require("trueterm")` in an autorun script. If you want it to load early you can use something like [extload](https://github.com/wrldspawn/extload) and a preinit script ([example](https://github.com/wrldspawn/gmod-misc/blob/main/lua/preinit/server/trueterm.lua)).

## Method 2: Plugin
> [!WARNING]
> This is currently untested and not included in the latest release as of writing.

Create `gmsv_trueterm.vdf` in `addons` with the following contents:
```
Plugin
{
    file        "lua/bin/gmsv_trueterm_linux.dll" // use _linux64 for 64bit
}
```
