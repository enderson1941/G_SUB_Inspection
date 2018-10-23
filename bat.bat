@echo off
@for /r %%i in (
*.aps *.idb *.ncb *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.res *.iobj *.ipdb
*.sdf *.dep *.ipch *.tlog *.exp *.hpj *.opt *.mdp *.plg *.clw *.db
) do del /f /q "%%i"

set fn=tlog
for /f "delims=" %%i in ('dir *%fn%* /ad/b') do rd /s/q "%%i"
@echo clear done!
@pause>nul