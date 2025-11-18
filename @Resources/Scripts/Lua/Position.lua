local MoveX = 0
local MoveY = 0
local AnchorX = 0
local AnchorY = 0
local Animation_Steps
local Animation_Displacement
local Animation_Direction
local Tween
local Tween_Subject

function calculatePosition(position)
    local position_x = position:sub(2, 2)
    local position_y = position:sub(1, 1)
    
    local x_padding = tonumber(SKIN:GetVariable('X_Padding')) or 0
    local y_padding = tonumber(SKIN:GetVariable('Y_Padding')) or 0
    local monitor_index = SKIN:GetVariable('Monitor_Index')
    local preserve_taskbar = tonumber(SKIN:GetVariable('Preserve_Taskbar_Space')) or 0
    
    local screen_area_x = tonumber(SKIN:GetVariable('SCREENAREAX@' .. monitor_index)) or 0
    local screen_area_y = tonumber(SKIN:GetVariable('SCREENAREAY@' .. monitor_index)) or 0
    local screen_area_width = tonumber(SKIN:GetVariable('SCREENAREAWIDTH@' .. monitor_index)) or 0
    local screen_area_height = tonumber(SKIN:GetVariable('SCREENAREAHEIGHT@' .. monitor_index)) or 0
    local work_area_width = tonumber(SKIN:GetVariable('WORKAREAWIDTH@' .. monitor_index)) or 0
    local work_area_height = tonumber(SKIN:GetVariable('WORKAREAHEIGHT@' .. monitor_index)) or 0
    
    local x_difference = screen_area_width - work_area_width
    local y_difference = screen_area_height - work_area_height
    
    MoveX, MoveY = 0, 0
    AnchorX, AnchorY = 0, 0
    
    if position_x == 'L' then
        MoveX = screen_area_x + x_padding + preserve_taskbar * x_difference
    elseif position_x == 'C' then
        MoveX = screen_area_x + screen_area_width * 0.5
        AnchorX = "50%"
    elseif position_x == 'R' then
        MoveX = screen_area_x + screen_area_width - x_padding - preserve_taskbar * x_difference
        AnchorX = "100%"
    end
    
    if position_y == 'T' then
        MoveY = screen_area_y + y_padding + preserve_taskbar * y_difference
    elseif position_y == 'C' then
        MoveY = screen_area_y + screen_area_height * 0.5
        AnchorY = "50%"
    elseif position_y == 'B' then
        MoveY = screen_area_y + screen_area_height - y_padding - preserve_taskbar * y_difference
        AnchorY = "100%"
    end
end

function Initialize()
    local use_as_widget = tonumber(SKIN:GetVariable('Use_As_Widget')) or 0
    local position = SKIN:GetVariable('Position')
    
    -- If Use_As_Widget is not 0, apply widget bangs and skip animation
    if use_as_widget ~= 0 then
        -- In widget mode, just show and make draggable - preserve saved position
        SKIN:Bang('[!Delay 100][!Show][!SetTransparency 255][!Draggable 1][!ZPos 0]')
        return
    end
    print('animating')
    
    calculatePosition(position)
    SKIN:Bang('[!Draggable 0][!ZPos 1]')
    SKIN:Bang('!SetWindowPosition', MoveX, MoveY, AnchorX, AnchorY)
    
    if tonumber(SKIN:GetVariable('Animated')) == 1 then
        Animation_Steps = tonumber(SKIN:GetVariable('Animation_Steps')) or 18
        Animation_Displacement = tonumber(SKIN:GetVariable('Animation_Displacement')) or 30
        Animation_Direction = SKIN:GetVariable('Animation_Direction')
        
        dofile(SELF:GetOption("ScriptFile"):match("(.*[/\\])") .. "tween.lua")
        
        Tween_Subject = { TweenNode = 0 }
        Tween = tween.new(Animation_Steps, Tween_Subject, { TweenNode = 100 }, SKIN:GetVariable('Ease_Type'))
    end
end

function tweenAnimation(direction)
    local use_as_widget = tonumber(SKIN:GetVariable('Use_As_Widget')) or 0
     if use_as_widget ~= 0 then
        return
    end
    if not Tween or not Tween_Subject then
        return
    end
    
    Tween:update(direction == 'in' and 1 or -1)
    
    local tween_node = Tween_Subject.TweenNode
    if tween_node > 100 then
        tween_node = 100
    elseif tween_node < 0 then
        tween_node = 0
    end
    
    local transparency = tween_node * 2.55
    
    local offset_x, offset_y = 0, 0
    local progress = tween_node * 0.01
    
    if Animation_Direction == 'Left' then
        offset_x = (progress - 1) * Animation_Displacement
    elseif Animation_Direction == 'Right' then
        offset_x = (1 - progress) * Animation_Displacement
    elseif Animation_Direction == 'Top' then
        offset_y = (progress - 1) * Animation_Displacement
    elseif Animation_Direction == 'Bottom' then
        offset_y = (1 - progress) * Animation_Displacement
    end
    
    SKIN:Bang('!SetTransparency', transparency)
    SKIN:Bang('!SetWindowPosition', MoveX + offset_x, MoveY + offset_y, AnchorX, AnchorY)
    SKIN:Bang('!UpdateMeasure', 'Measure_Position_Animation_Timer')
end
