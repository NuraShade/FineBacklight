[Measure_Backlight]
IfCondition=(Measure_Backlight = 0)
IfTrueAction=[!SetOption Brightness_Icon ImageName "0.png"][!SetOption Measure_TrayIcon Icon "#@#Images\Brightness\Icons\0.ico"][!UpdateMeter *][!Redraw]
IfCondition2=(Measure_Backlight > 0) && (Measure_Backlight <= 34)
IfTrueAction2=[!SetOption Brightness_Icon ImageName "1.png"][!SetOption Measure_TrayIcon Icon "#@#Images\Brightness\Icons\1.ico"][!UpdateMeter *][!Redraw]
IfCondition3=(Measure_Backlight > 34) && (Measure_Backlight <= 67)
IfTrueAction3=[!SetOption Brightness_Icon ImageName "2.png"][!SetOption Measure_TrayIcon Icon "#@#Images\Brightness\Icons\2.ico"][!UpdateMeter *][!Redraw]
IfCondition4=(Measure_Backlight > 67)
IfTrueAction4=[!SetOption Brightness_Icon ImageName "3.png"][!SetOption Measure_TrayIcon Icon "#@#Images\Brightness\Icons\3.ico"][!UpdateMeter *][!Redraw]

[Measure_TrayIcon]
Measure=Plugin
Plugin=SkinTray
Icon="#@#Images\Brightness\Icons\3.ico"
ToolTipText=Brightness: [Measure_Backlight]%
LeftMouseUpAction=[!UpdateMeasure Measure_Visibility_Toggle]
DynamicVariables=1