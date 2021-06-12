@echo off
echo Assembling library modules.

cd CIPHERS
echo.
echo Assembling CIPHERS
echo ==================
echo.
\masm32\bin\ml /nologo /c /Cp /coff *.asm
if errorlevel 1 goto _end
copy *.obj .\..\*.obj
del *.obj
cd ..

cd hashes
echo.
echo Assembling HASHES
echo =================
echo.
\masm32\bin\ml /nologo /c /Cp /coff *.asm
copy *.obj .\..\*.obj
del *.obj
cd ..

cd checksums
echo.
echo Assembling CHECKSUMS
echo ====================
echo.
\masm32\bin\ml /nologo /c /Cp /coff *.asm
copy *.obj .\..\*.obj
del *.obj
cd ..

cd textformats
echo.
echo Assembling TEXTFORMATS
echo ======================
echo.
\masm32\bin\ml /nologo /c /Cp /coff *.asm
copy *.obj .\..\*.obj
del *.obj
cd ..

\masm32\bin\link /lib /nologo *.obj /out:cryptohash.lib
echo.

copy        cryptohash.lib \masm32\lib\cryptohash.lib
copy        cryptohash.inc \masm32\include\cryptohash.inc
:_end
pause
del *.obj