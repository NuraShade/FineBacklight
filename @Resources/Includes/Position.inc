;============================================================
;  NuraShade Skin
;  Copyright (c) 2025 NuraShade
;
;  Licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License.
;  You are free to:
;    • Share — copy and redistribute the material in any medium or format
;    • Adapt — remix, transform, and build upon the material
;      for any purpose, even commercially.
;
;  Under the following terms:
;    • Attribution — You must give appropriate credit, provide a link to the license,
;      and indicate if changes were made.
;    • ShareAlike — If you remix, transform, or build upon the material,
;      you must distribute your contributions under the same license as the original.
;
;  License Details: https://creativecommons.org/licenses/by-sa/3.0/
;============================================================

[Variables]
Use_As_Widget=0
;Position
Position=BR
Monitor_Index=1
X_Padding=0
Y_Padding=0
Preserve_Taskbar_Space=1
;Animation
Animated=1
Ease_Type=OutQuart
Animation_Direction=Bottom
Animation_Steps=18
Animation_Displacement=30

; ;============================================================================================================================;
; ;                                          Position                                                                          ;
; ;============================================================================================================================;
; Position=CC
; MonitorIndex=1
; XPad=0
; YPad=0
; PreserveTaskbarSpace=1
; ;============================================================================================================================;
; ;                                         Animation                                                                          ;
; ;============================================================================================================================;
; Animated=1
; EaseType=OutSine
; AniDir=Bottom
; AniSteps=18
; AnimationDisplacement=30
;=============================================================
;           Measures
;=============================================================

; [Measure_Focus]
; Measure=Plugin
; Plugin=Focus

; [Measure_Position_Animation]
; Measure=Script
; ScriptFile=#@#Scripts\Lua\Position.lua
; UpdateDivider=1

; [Measure_Position_Animation_Timer]
; Measure=Plugin
; Plugin=ActionTimer
; DynamicVariables=1
; ActionList1=Show | Repeat In,2,#Animation_Steps#
; ActionList2=Repeat Out,2,#Animation_Steps# | Hide
; In=[!CommandMeasure Measure_Position_Animation "TweenAnimation('in')"]
; Out=[!CommandMeasure Measure_Position_Animation "TweenAnimation('out')"]
; DefaultUpdateDivider=-1

;=========================================================================================================================================;
;                                                                   Transition                                                            ;
;=========================================================================================================================================;

[mToggle]
Measure=Calc
Formula=1 - mToggle
IfCondition=mToggle = 0
IfTrueAction=[!UpdateMeasure ACTIONLOAD][!CommandMEasure Focus "#CURRENTCONFIG#"]
IfCondition2=mToggle = 1
IfTrueAction2=[!UpdateMeasure ACTIONUNLOAD]
IfConditionMode=1
DynamicVariables=1
UpdateDivider=-1

[mToggleSet]
Measure=Calc
Formula=mToggle
IfCondition=mToggle = 0
iftrueaction=[!UpdateMeasure mToggle]
ifconditionmode=1
Group=NUOL
Disabled=1
UpdateDivider=-1

[ActionTimer]
Measure=Plugin
Plugin=ActionTimer
DynamicVariables=1
ActionList1=Show | Custom0 | Repeat In,2,#Animation_Steps#
ActionList2=SaveLocation | Repeat Out,2,#Animation_Steps# | Hide
Show=[!Show]
Hide=[!Hide]
In=[!CommandMeasure transition_Lua "tweenAnimation('in')"]
Out=[!CommandMeasure transition_Lua "tweenAnimation('out')"]
UpdateDivider=-1

[ACTIONLOAD]
Measure=String
OnUpdateAction=[!CommandMeasure ActionTimer "Stop 2"][!CommandMeasure ActionTimer "Execute 1"]
Disabled=1
Group=NUOL
UpdateDivider=-1

[ACTIONUNLOAD]
Measure=String
OnUpdateAction=[!CommandMeasure ActionTimer "Stop 1"][!CommandMeasure ActionTimer "Execute 2"]
Disabled=1
Group=NUOL
UpdateDivider=-1

[transition_Lua]
Measure=Script
ScriptFile=#@#scripts\lua\Position.lua
UpdateDivider=-1

[Focus]
Measure=Plugin
Plugin=Focus