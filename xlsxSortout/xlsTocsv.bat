@echo off
set tmpVbs=convert_temp.vbs
more +12 %0 >%tmpVbs%
for /f "tokens=*" %%a in (
 'dir *.xls /a /b'
) do (
 wscript //Nologo "%tmpVbs%" "%%~dpnxa"
)
del "%tmpVbs%" /q 1>nul 2>nul
pause
Exit
Const xlCSV = 6
dim filepathname
Set objExcel = CreateObject("Excel.Application")
'Filename = objExcel.GetOpenFilename("Excel Files (*.xls), *.xls")
'objExcel.DisplayAlerts=FALSE
'If filename<>false Then
On Error Resume Next
Filename = WScript.Arguments.Unnamed.Item(0)
Set objWorkbook = objExcel.Workbooks.Open(Filename)
If Err.Number <> 0 Then
Err.Raise Err.Number
Return "-1"
End If
objWorkbook.SaveAs mid(Filename,1,len(Filename)-4) & ".csv",xlCSV
If Err.Number <> 0 Then
Err.Raise Err.Number
Return "-1"
End If
'MsgBox objWorkbook.path
filepathname = objWorkbook.path & "\\" & mid(Filename,1,len(Filename)-4) & ".csv"
objWorkbook.close false
'End If
objExcel.Quit
'MsgBox filepathname
'If filepathname>"" then
'Return filepathname
'end if