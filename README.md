# [This module is irrelevant now](https://github.com/Facepunch/garrysmod-issues/issues/6174)

# gmsv_trueterm
Truecolor terminal output for Garry's Mod Linux dedicated servers.

An amalgamation of [gm_spew](https://github.com/danielga/gm_spew), [gm_xterm](https://github.com/Metastruct/gm_xterm) and [gm_xconsole_x64](https://github.com/Earu/gmsv_xconsole_x64).

# Installation
Put the DLL file in `lua/bin/`, then call `require("trueterm")` in an autorun script.

If you want it to load early you can use something like [extload](https://github.com/wrldspawn/extload) and a preinit script ([example](https://github.com/wrldspawn/gmod-misc/blob/main/lua/preinit/server/trueterm.lua)).

> [!NOTE]
> There is code for loading through server plugin and ghostinj.dll, but it is non-functional and not included in the current release.
