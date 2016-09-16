const xlCSV = 6

Set objExcel = CreateObject("Excel.Application")
Set objWorkbook = objExcel.Workbooks.Open("e:\output.xlsx")
objExcel.DisplayAlerts = FALSE
objExcel.Visible = TRUE

Set objWorksheet = objWorkbook.Worksheets("Sheet1")
objWorksheet.SaveAs "e:\test.csv", xlCSV
'objWorksheet.ActiveWorkBook.Saved = True

objExcel.Quit