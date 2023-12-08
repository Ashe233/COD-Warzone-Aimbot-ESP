#pragma once
#include"includes.hpp"
#include "structures.hpp"
#include "Driver.h"
#include "offsets.h"
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define AutoPadding(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#define is_valid_ptr(p) ((uint64_t)(p) <= 0x7FFFFFFEFFFF && (uint64_t)(p) >= 0x1000) 
#define is_bad_ptr(p)	(!is_valid_ptr(p))


class clientinfo_t {
public:
	union {
		AutoPadding(char, name[36], 0x4);
		AutoPadding(uint32_t, game_extrainfo, 0x70);
		AutoPadding(int32_t, health, 0x84);
		AutoPadding(uint8_t, squadIndex, 0x90);
		AutoPadding(Vec3, vecOrigin, 0x40);
		AutoPadding(Vec3, deltaAngle, 0x11C);
		AutoPadding(unsigned int, clientnum, 0x2A0);
		AutoPadding(Vec3, viewAngle, 0x2A4);
		AutoPadding(bool, radarEnabled, 0x42D);
		AutoPadding(bool, radarBlocked, 0x42E);
	};
};
class CEntity	// 游戏实体类
{
public:
	int index = 0;
	DWORD64 Address = 0;	// 实体地址
	bool is_dead = 0;
	bool is_friendly = 0;
	bool is_valid = 0;
	float fdistance = 0;
	bool visible = false;
	float healthpercentage = 0;
	bool isdead = 0;
	uint8_t teamid = 0;

	Vec3 position = { 0,0,0 };
	Vec3 headpos = { 0,0,0 };
	Vec3 neckpos = { 0,0,0 };
	Vec3 chestpos = { 0,0,0 };
	Vec3 bodypos = { 0,0,0 };

	std::string name = "";
	uint32_t game_extrainfo = 0;
	int32_t health=0;
	uint8_t squadIndex=0;
	Vec3 vecOrigin={ 0,0,0 };
	Vec3 deltaAngle={ 0,0,0 };
	unsigned int clientnum=0;
	Vec3 viewAngle={ 0,0,0 };
	bool radarEnabled=0;
	bool radarBlocked = 0;


	bool is_valid_player() {
		is_valid = read<bool>(Address + OFF_player_valid);
		return 1;
	}
	bool get_player_all_things() {

		//先弄不需要info的 
		//team
		if (is_valid_ptr(Address))
			teamid = read<uint8_t>(Address + player_team_id);
		//位置
		auto local_pos_ptr = read<uint64_t>(Address + player_pos);

		if (is_valid_ptr(local_pos_ptr))
			position = read<Vec3>(local_pos_ptr + 0x48);


		//读namearray
		uint64_t bgs = read<uint64_t>(oBaseAddress + OFF_name_array);
		if (is_bad_ptr(bgs))return 0;
		DWORD64 pCinforAdd = (bgs + OFF_name_array_padding + (this->index * OFF_name_array_size));
		if (is_bad_ptr(pCinforAdd))return 0;
		clientinfo_t pClientInfo = read<clientinfo_t>(pCinforAdd);

		//所有pclientinfo里面的东西都存到entity里面去
		game_extrainfo = pClientInfo.game_extrainfo;
		name = pClientInfo.name;
		squadIndex = pClientInfo.squadIndex;
		vecOrigin = pClientInfo.vecOrigin;
		deltaAngle = pClientInfo.deltaAngle;
		clientnum = pClientInfo.clientnum;
		viewAngle = pClientInfo.viewAngle;
		radarEnabled = pClientInfo.radarEnabled;
		radarBlocked = pClientInfo.radarBlocked;

		//健康存一下
		uint8_t healthValue = pClientInfo.health;
		health = healthValue;
		float healthPercentage = ((float)health / 100.0f) * 100.0f;
		this->healthpercentage = healthPercentage;


		return 1;
	}
	bool getlife() {
		if (is_valid_ptr(Address)) {
			auto dead1 = read<bool>(Address + OFF_player_dead_1);
			auto dead2 = read<bool>(Address + OFF_player_dead_2);
			isdead = !(!dead1 && !dead2 && !is_valid);
			return 1;
		}
		else
			return 0;
	}
};