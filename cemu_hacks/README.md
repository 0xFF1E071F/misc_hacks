# cemu_hacks
Cemu registration file generator/hook

Works only on the current executable in this directory.

Back up serial.bin and settings.bin if you have a legit install if you wanna mess with this.

keygen_loader.cpp is a loader. It simply generates a fresh/updated settings/serial.bin whenever you run it.
Use it instead of Cemu.exe to run the emulator. Running this removes the need to run every 12 hours the keygen,
since the loader updates the serial on demand. 

There are 2 variants of the serial algorithm, one with a simple HWID system and another with much more complex
checks and including various forms of obfuscation, which involved some time deobfuscating and rewriting code.

Works up to 1.7.2c. This loader/keygen is worthless now for the time being, but I found it fun REing Cemu.
Was a good exercise in 64bit reversing.

The "hook" directory implements a hook DLL which API hooks various things as well as the serial verification function.

