#pragma once
#include"includes.hpp"


uintptr_t localPlayer;
uintptr_t entList;
uintptr_t viewRenderer;
uintptr_t viewMatrix;
QWORD refdef = 0;
int max_player_count = 0;
float entX = 0;
float entY = 0;
bool ingame;
refdef_t therefofgame{};
float aX = 0;
float aY = 0;

float entNewVisTime = 0;
float entOldVisTime[100];
int visCooldownTime[100];
int spectatorcount = 0;
int realspeccount = 0;
int timetocountspeczero = 1500;
DWORD timecountnow = 0;
ULONG64 Pebadd = 0;
PEB peb;