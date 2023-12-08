#pragma once
namespace Config {
	bool BodyEsp = 0;
	bool BodyEspShield = false;
	bool ItemEsp = 0;
	bool draw2dbox = 0;
	bool Menu = 1;
	bool draw_fov = false;
	bool healthbar = false;
	bool espteammates = false;
	bool spectcount = false;
	bool Prediction = false;
	bool NoRecoil = false;
	bool draw_bone = false;
	bool trigger = false;
	bool dianshe = false;
	int intervaltime = 500;
	int triggertime = 200;
	float triggerdisnotzoom = 10;
	float triggerdiszoom = 100;
	int aim_key = 6;
	int aim_key2 = 1;
	float Recoilnumx = 85.f;
	float Recoilnumy = 85.f;
	int bone = 3;
	bool autobone = false;
	float espdist = 100;
	ImVec4 fovcol = ImVec4(1.0f, 0.9f, 0, 1);
	ImVec4 EnemyCol = ImVec4(1, 1, 1, 1);//这是给FOV的
	ImVec4 enargb = ImVec4(1, 0.3, 0, 1);//可见敌人
	ImVec4 invisenargb = ImVec4(0.4, 0.37, 0.91, 1);//不可见敌人
}
	int screenWeight = 1920; // In-game resolution
	int screenHeight = 1080;
	float FOV = 200; //AimbotFOV
	float aSmoothAmount = 10.f; // Aimbot smoothness
	float smoothzoomin = 10.f;