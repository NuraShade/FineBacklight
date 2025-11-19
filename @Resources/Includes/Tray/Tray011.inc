[Measure_Backlight]
IfCondition=(Measure_Backlight = 0)
IfTrueAction=[!SetOption * ImageName "0.png"][!SetOption Measure_TrayIcon Icon "#@#Images\Brightness\Icons\#Icon_Style#\0.ico"][!UpdateMeter *][!Redraw]
IfCondition2=(Measure_Backlight > 0) && (Measure_Backlight <= 34)
IfTrueAction2=[!SetOption * ImageName "1.png"][!SetOption Measure_TrayIcon Icon "#@#Images\Brightness\Icons\#Icon_Style#\1.ico"][!UpdateMeter *][!Redraw]
IfCondition3=(Measure_Backlight > 34) && (Measure_Backlight <= 67)
IfTrueAction3=[!SetOption * ImageName "2.png"][!SetOption Measure_TrayIcon Icon "#@#Images\Brightness\Icons\#Icon_Style#\2.ico"][!UpdateMeter *][!Redraw]
IfCondition4=(Measure_Backlight > 67)
IfTrueAction4=[!SetOption * ImageName "3.png"][!SetOption Measure_TrayIcon Icon "#@#Images\Brightness\Icons\#Icon_Style#\3.ico"][!UpdateMeter *][!Redraw]

[Measure_TrayIcon]
Measure=Plugin
Plugin=SKinTray
Icon="#@#Images\Brightness\Icons\#Icon_Style#\3.ico"
ToolTipText=Brightness: [Measure_Backlight]%
LeftMouseUpAction=[!UpdateMeasure Measure_Visibility_Toggle]
MouseWheelUpAction=[!CommandMeasure Measure_Backlight "ChangeBacklight #Volume_Change_Level#"][!UpdateMeasure Measure_Backlight][!UpdateMeasure Measure_TrayIcon]
MouseWheelDownAction=[!CommandMeasure Measure_Backlight "ChangeBacklight -#Volume_Change_Level#"][!UpdateMeasure Measure_Backlight][!UpdateMeasure Measure_TrayIcon]
DynamicVariables=1