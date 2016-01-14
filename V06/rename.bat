for /f "tokens=1,2,3 delims=()" %%i in ('dir /B') DO ren "%%i(%%j)%%k" %%j
