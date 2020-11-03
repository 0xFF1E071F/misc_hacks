# cemu_hacks
Cemu registration file generator/hook

There are 2 variants of the serial algorithm, one with a simple HWID system and another with much more complex
checks and including various forms of obfuscation, which involved some time deobfuscating and rewriting code.

Works up to 1.7.2c. This hook/keygen is worthless now, but I found it fun REing Cemu.
Was a good exercise in 64bit reversing.

### the "keygen" directory

keygen_loader.cpp is a loader. It simply generates a fresh/updated settings/serial.bin whenever you run it.
Use it instead of Cemu.exe to run the emulator. Didn't implement the permanent flag to tag a install is permanently
validated.

### the "hook" directory

Implements a hook DLL which API hooks various things as well as the serial verification function.

