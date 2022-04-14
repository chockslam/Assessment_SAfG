/*
    * AnimMasks .h file
    * 19012503
    * Aim: Hides 'string' implementation from animation system by creating macros,
    * which makes it more straightforward for using animation system by restricting  number of 
    * possible states and uniting them for all the game objects. 
*/
#pragma once
#define IDLE L"IDLE"
#define RUN L"RUN"
#define DEATH L"DEATH"
#define FALL L"FALL"
#define ATTACK L"ATTACK"