﻿// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once 
#include "_defines.h"


#define VIEW_MASK_FOR_MISSILE   1
#define VIEW_MASK_FOR_EFFECTS   2

#ifdef _DEBUG
#define PROFILER_FUNC_ENTER()  TheProfiler->BeginBlock(__FUNCTION__);
#define PROFILER_FUNC_LEAVE()  TheProfiler->EndBlock();
#else
#define PROFILER_FUNC_ENTER()
#define PROFILER_FUNC_LEAVE()
#endif

#define PRESS_UP        (TheInput->GetKeyDown(KEY_UP))
#define PRESS_DOWN      (TheInput->GetKeyDown(KEY_DOWN))
#define PRESS_LEFT      (TheInput->GetKeyDown(KEY_LEFT))
#define PRESS_RIGHT     (TheInput->GetKeyDown(KEY_RIGHT))
#define PRESS_HOME      (TheInput->GetKeyDown(KEY_HOME))
#define PRESS_PAGEUP    (TheInput->GetKeyDown(KEY_PAGEUP))
#define PRESS_W         (TheInput->GetKeyDown(KEY_W))
#define PRESS_S         (TheInput->GetKeyDown(KEY_S))
#define PRESS_A         (TheInput->GetKeyDown(KEY_A))
#define PRESS_D         (TheInput->GetKeyDown(KEY_D))
#define PRESS_Q         (TheInput->GetKeyDown(KEY_Q))
#define PRESS_E         (TheInput->GetKeyDown(KEY_E))

#define KEY_IS_F1       (key == KEY_F1)
#define KEY_IS_F10      (key == KEY_F10)
#define KEY_IS_F11      (key == KEY_F11)
#define KEY_IS_ESC      (key == KEY_ESCAPE)
#define KEY_IS_SPACE    (key == KEY_SPACE)
#define KEY_IS_UP       (key == KEY_UP)
#define KEY_IS_DOWN     (key == KEY_DOWN)
#define KEY_IS_LEFT     (key == KEY_LEFT)
#define KEY_IS_RIGHT    (key == KEY_RIGHT)
#define KEY_IS_KP_MINUS (key == KEY_KP_MINUS)
#define KEY_IS_KP_PLUS  (key == KEY_KP_PLUS)
#define KEY_IS_9        (key == KEY_9)
#define KEY_IS_I        (key == KEY_I)

#define IN_PAUSE        (TheScene->GetTimeScale() <= M_EPSILON)

// Имена узлов

#define NODE_CAMERA_TARGET "CameraTarget"

#define UNUSED(x) (void)(x)

#define CALL_MEMBER_IF_EXIST(object, function) if(object) (object)->function()
