Set WshShell = CreateObject("WScript.Shell")
WshShell.Run chr(34) & "c:\My\TacticsVictory\out\Server.bat"  & Chr(34), 0
Set WshShell = Nothing