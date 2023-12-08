#pragma once
#include "simhei.h"
#include"imgui_toggle.h"
#include"skStr.h"
#include"includes.hpp"
#include "Driver.h"
#include "structures.hpp"
#include "target.hpp"
#include "GlobalVar.hpp"
#include "offsets.h"
#include"entity.hpp"
#include"Decryption.hpp"
#include"Renderer.hpp"
#include "candy.h"
inline std::vector<CEntity> entities = {};
CEntity AimEntity;
CEntity LocalEntity;
Matrix m;
int lastfoundentity = 0;
int keydown = 0;
DWORD keydowntime = 0;
std::string random_string_window()
{
	srand((unsigned)time(NULL));
	std::string str = skCrypt("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890").decrypt();
	std::string newstr;
	int pos;
	while (newstr.size() != 5)
	{
		pos = ((rand() % (str.size() + 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}
/*void aimbotthread() {
	float crosshairX = screenWeight / 2.f;
	float crosshairY = screenHeight / 2.f;
	QAngle aimingangle = { 0,0 };
	Vec3 HeadPosition1 = { 0,0,0 };
	while (1) {
		int dotrigger = 0;
		if (!LocalEntity.Address || entities.empty()) continue;
		//std::cout << "1\n";
		uint64_t viewRenderer = read<uint64_t>(oBaseAddress + OFFSET_RENDER);
		uint64_t viewMatrix = read<uint64_t>(viewRenderer + OFFSET_MATRIX);
		m = read<Matrix>(viewMatrix);
		Vec3 HeadPosition = { 0,0,0 };
		float closestX = 9999;
		float closestY = 9999;
		int decideaimorno = 0;
		for (CEntity ce : entities) {
			if (ce.Address == LocalEntity.Address) continue;

			float WorldTime = read<float>(LocalEntity.Address + timeBase);
			ce.IsAimedAt = ce.IsTarget(WorldTime);

			if (!GetAsyncKeyState(1) && Config::trigger) {
				if (ce.IsAimedAt && ce.visible && ce.Team && !ce.DyingState && !ce.BleedOutState && ce.Health > 0 && LocalEntity.Health > 0) {
					float dis = pow(pow(LocalEntity.HeadPos.x - ce.HeadPos.x, 2) + pow(LocalEntity.HeadPos.y - ce.HeadPos.y, 2) + pow(LocalEntity.HeadPos.z - ce.HeadPos.z, 2), 0.5);
					if ((GameUnitsToMeter(dis) < Config::triggerdiszoom && LocalEntity.zoomin) || (GameUnitsToMeter(dis) < Config::triggerdisnotzoom && !LocalEntity.zoomin)) {
						if (!keydown)
							mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						keydown = 1;
						keydowntime = GetTickCount();
						dotrigger = 1;
					}
				}
			}
			if (Config::bone == 0 || Config::autobone) HeadPosition = GetEntityBonePosition(ce.Address, id::head, GetEntityBasePosition(ce.Address));
			else if (Config::bone == 1) HeadPosition = GetEntityBonePosition(ce.Address, id::neck, GetEntityBasePosition(ce.Address));
			else if (Config::bone == 2) HeadPosition = GetEntityBonePosition(ce.Address, id::body, GetEntityBasePosition(ce.Address));
			else if (Config::bone == 3) HeadPosition = GetEntityBonePosition(ce.Address, id::hips, GetEntityBasePosition(ce.Address));
			//printf("%f,%f,%f\n", HeadPosition.x, HeadPosition.y, HeadPosition.z);
			// Convert to screen position
			Vec3 PreditPos = HeadPosition;
			Vec3 w2sHeadAimPos;
			if (Config::Prediction) {
				ce.AbsVelocity = read<Vec3>(ce.Address + OFF_ABSVELOCITY);
				AimCorrection(LocalEntity.HeadPos, LocalEntity.WeaponProjectileScale, &PreditPos, ce.AbsVelocity, LocalEntity.WeaponProjectileSpeed);
				//printf("%f,%f\n\n", aimingangle.x, aimingangle.y);
				w2sHeadAimPos = _WorldToScreen(PreditPos, m);
			}
			else {
				w2sHeadAimPos = _WorldToScreen(HeadPosition, m);
			}
			float entX = w2sHeadAimPos.x;
			float entY = w2sHeadAimPos.y;
			if (ce.visible && ce.Team && !ce.DyingState && !ce.BleedOutState)//¿É¼û
			{
				// Aimbot fov
				if (abs(crosshairX - entX) < abs(crosshairX - closestX) && sqrt(pow((crosshairX - entX), 2) + pow((crosshairY - entY), 2)) < FOV)
				{
					// Aimbot find closest target
					//auto viewAngles = read <QAngle>(LocalEntity.Address + OFF_VIEW_ANGLES).fixAngle();
					closestX = entX;
					closestY = entY;
					AimEntity = ce;
					AimEntity.aimx = entX;
					AimEntity.aimy = entY;
					decideaimorno = 1;
					HeadPosition1 = PreditPos;

				}
			}
		}
		auto viewAngles = read <QAngle>(LocalEntity.Address + OFF_VIEW_ANGLES);
		if (!decideaimorno) aimingangle = viewAngles;
		aimingangle = CalculateAngle(LocalEntity.HeadPos, HeadPosition1);
		aimingangle = SmoothLinear(viewAngles, aimingangle, aSmoothAmount / 10.f);
		//printf("%f,%f\n", AimEntity.aimx, AimEntity.aimy);
		if ((GetAsyncKeyState(Config::aim_key) || GetAsyncKeyState(Config::aim_key2)) && decideaimorno && (!keydown || !Config::trigger)) {
			if (AimEntity.aimx != 9999.f && AimEntity.aimy != 9999.f && AimEntity.aimx && AimEntity.aimy && !LocalEntity.DyingState && !LocalEntity.BleedOutState)
			{
				//Aim(&LocalEntity, &AimEntity);
				// If mouse cursor shown
				CURSORINFO ci = { sizeof(CURSORINFO) };
				if (GetCursorInfo(&ci))
				{
					if (ci.flags == 0) {
						if (LocalEntity.zoomin) {
							aX = (closestX - crosshairX) / smoothzoomin;
							aY = (closestY - crosshairY) / smoothzoomin;
						}
						else {
							aX = (closestX - crosshairX) / aSmoothAmount;
							aY = (closestY - crosshairY) / aSmoothAmount;
						}
						mouse_event(MOUSEEVENTF_MOVE, aX, aY, 0, 0);
						//write<QAngle>(LocalEntity.Address + OFF_VIEW_ANGLES, aimingangle);
					}
				}
			}
		}

		auto PunchWeapon = read<QAngle>(LocalEntity.Address + m_vecPunchWeapon_Angle);
		if (Config::NoRecoil && LocalEntity.Health > 0) {
			auto viewAngles1 = read <QAngle>(LocalEntity.Address + OFF_VIEW_ANGLES);
			NewAngle.x = viewAngles1.x + ((PreviousAngle.x - PunchWeapon.x) * (Config::Recoilnumx / 100.f));
			NewAngle.y = viewAngles1.y + ((PreviousAngle.y - PunchWeapon.y) * (Config::Recoilnumy / 100.f));
			if (NewAngle.x != viewAngles1.x || NewAngle.y != viewAngles1.y)
				write<QAngle>(LocalEntity.Address + OFF_VIEW_ANGLES, NewAngle);
		}
		if (keydown && GetTickCount() - keydowntime > Config::triggertime && Config::dianshe) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(Config::intervaltime);
			keydown = 0;
		}
		else if (!Config::dianshe && keydown && !dotrigger) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			keydown = 0;
		}
		PreviousAngle = PunchWeapon;
		Sleep(1);
	}
}*/
int get_max_player_count()
{
	return read<int>(oBaseAddress + game_mode);
}
void mainthread() {
	while (true)
	{
		max_player_count = get_max_player_count();
		auto decryptedPtr = decrypt_client_info();
		auto local_index_ptr = read<uintptr_t>(decryptedPtr + OFF_local_index);
		int local_index = read<int>(local_index_ptr + OFF_local_index_pos);
		auto client_info_base = decrypt_client_base(decryptedPtr);
		int closestX = 9999;
		int closestY = 9999;
		CEntity TmpEntity{};
		CEntity tmpaim{};
		std::vector<CEntity> tmpentities = {};
		//printf("%d,%llx\n", max_player_count, client_info_base);
		for (int i = 0; i < max_player_count; i++)
		{
			TmpEntity.index = i;
			DWORD64 EntityAddress = client_info_base + (i * OFF_player_size);
			if (EntityAddress == 0)
				continue;
			TmpEntity.Address = EntityAddress;
			TmpEntity.is_valid_player();
			TmpEntity.get_player_all_things();
			TmpEntity.getlife();
			//printf("%d\n", TmpEntity.teamid);
			uint64_t decrypted_bone_ptr = decrypt_bone_base();

			unsigned short bone_index = get_bone_index(i);
			if (bone_index != 0)
			{
				uint64_t bone_ptr = read<uint64_t>(decrypted_bone_ptr + (bone_index * bone_size) + bone_offset);

				Vec3 bone_pos_head = read<Vec3>(bone_ptr + (7 * 0x20) + 0x10);
				Vec3 bone_pos_neck = read<Vec3>(bone_ptr + (6 * 0x20) + 0x10);
				Vec3 bone_pos_chest = read<Vec3>(bone_ptr + (5 * 0x20) + 0x10);
				Vec3 bone_pos_body = read<Vec3>(bone_ptr + (4 * 0x20) + 0x10);
				Vec3 basepos = read<Vec3>(decryptedPtr + bone_base);

				bone_pos_head.x += basepos.x;
				bone_pos_head.y += basepos.y;
				bone_pos_head.z += basepos.z;
				bone_pos_neck.x += basepos.x;
				bone_pos_neck.y += basepos.y;
				bone_pos_neck.z += basepos.z;
				bone_pos_chest.x += basepos.x;
				bone_pos_chest.y += basepos.y;
				bone_pos_chest.z += basepos.z;
				bone_pos_body.x += basepos.x;
				bone_pos_body.y += basepos.y;
				bone_pos_body.z += basepos.z;
				TmpEntity.headpos = bone_pos_head;
				TmpEntity.neckpos = bone_pos_neck;
				TmpEntity.chestpos = bone_pos_chest;
				TmpEntity.bodypos = bone_pos_body;
			}
			//printf("%f,%f,%f\n", TmpEntity.headpos.x, TmpEntity.headpos.y, TmpEntity.headpos.z);
			if (i == local_index) LocalEntity = TmpEntity;
			TmpEntity.is_friendly = (TmpEntity.teamid == LocalEntity.teamid);
			if (i != local_index)tmpentities.push_back(TmpEntity);
		}
		entities = tmpentities;
		// After entity loop ends
		Sleep(10);
	}
}
inline void esp() {
	therefofgame = read<refdef_t>(refdef);
	ImDrawList* Draw = ImGui::GetBackgroundDrawList();
	ImVec2 CrossHair = ImVec2(screenWeight / 2.0f, screenHeight / 2.0f);
	if (Config::draw_fov)
	{
		Draw->AddCircle(CrossHair, FOV, ImGui::GetColorU32(Config::fovcol), 3000, 2);
	}
	if (!entities.empty()) {
		for (CEntity drawentity : entities) {
			//if (drawentity.is_friendly && !Config::espteammates) continue;
			//if (drawentity.isdead) continue;
			//if (drawentity.health == 0) continue;
			Vec3 drawpos = drawentity.headpos;
			if (drawentity.headpos.x > -0.000001 && drawentity.headpos.x < 0.000001&& drawentity.headpos.y > -0.000001 && drawentity.headpos.y < 0.000001) continue;
			Vec3 downpos = drawentity.chestpos;
			//printf("%f,%f,%f\n", drawentity.headpos.x, drawentity.headpos.y, drawentity.headpos.z);
			//float dis = pow(pow(LocalEntity.headpos.x - drawentity.headpos.x, 2) + pow(LocalEntity.headpos.y - drawentity.headpos.y, 2) + pow(LocalEntity.headpos.z - drawentity.headpos.z, 2), 0.5);
			if (1) {
				if (Config::healthbar) {
					Vec2 Vec2_A{}, Vec2_B{};
					if (!w2s(drawpos, &Vec2_A))
						continue;
					if (!w2s(downpos, &Vec2_B))
						continue;
					float height = abs(Vec2_A.y - Vec2_B.y)*3;
					float width = height * 0.85;
					float Height2 = abs(Vec2_A.y - Vec2_B.y) * 2;
					OW::Render::DrawHealthBar(OW::Vector2(Vec2_B.x - width / 2, Vec2_B.y), -Height2, drawentity.health, 127);

				}
				if (Config::draw2dbox) {
					Vec2 Vec2_A{}, Vec2_B{};
					if (!w2s(drawpos, &Vec2_A))
						continue;
					if (!w2s(drawpos, &Vec2_B))
						continue;

					float height = abs(Vec2_A.y - Vec2_B.y) * 2;
					float width = height * 0.85;

					OW::Render::DrawCorneredBox(Vec2_A.x - (width / 2) - 1, Vec2_A.y - (height / 5) - 1, width + 2, height + 12, ImGui::GetColorU32(Config::EnemyCol));
					OW::Render::DrawFilledRect(Vec2_A.x - (width / 2) - 1, Vec2_A.y - (height / 5) - 1, width + 2, height + 12, ImColor(0, 0, 0, 60));
				}
			}
		}
	}
}
void overlaythread() {
	//__try {
	int doingone = 0;
	int tab_index = 0;
	std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point b = std::chrono::system_clock::now();

	HWND tWnd = FindWindowW(skCrypt(L"Notepad"), NULL);

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, skCrypt("asdkjghb"), NULL };
	RegisterClassEx(&wc);
	hwnd = CreateWindow(wc.lpszClassName, random_string_window().c_str(), WS_POPUP, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);

	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
	}

	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromMemoryTTF((void*)SimHei_data, sizeof(SimHei_data), 18.f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.Fonts->AddFontFromFileTTF(".\\SimHei.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());

	//ImGui::StyleColorsDark();
	ImCandy::Theme_Blender();
	//ImGui::StyleColorsLight();


	ImGui_ImplWin32_Init(tWnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	int FPS;
	DEVMODE dm;
	while (FindWindowA(skCrypt("Notepad"), NULL))
	{

		dm.dmSize = sizeof(DEVMODE);

		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);

		FPS = dm.dmDisplayFrequency;
		FPS = 200;

		a = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> work_time = a - b;
		if (work_time.count() < 1000 / FPS)
		{
			std::chrono::duration<double, std::milli> delta_ms(1000 / FPS - work_time.count());
			auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
			//std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
		}

		b = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> sleep_time = b - a;
		//viewMatrix = SDK->RPM<Matrix>(viewMatrixPtr);
		//viewMatrix_xor = SDK->RPM<Matrix>(viewMatrix_xor_ptr);
		DWORD Style = GetWindowLong(tWnd, GWL_STYLE);
		RECT rect;
		GetWindowRect(tWnd, &rect);

		SetWindowPos(hwnd, HWND_TOPMOST, rect.left, rect.top, rect.right, rect.bottom, SWP_NOZORDER);

		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			//continue;
		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			ImGui::GetIO().MouseDown[0] = true;
		}
		else
		{
			ImGui::GetIO().MouseDown[0] = false;
		}

		if (GetAsyncKeyState(VK_INSERT)) {
			Config::Menu = !Config::Menu;
			//ImGui::GetIO().MouseDrawCursor = Config::Menu;
			Sleep(250);
		}
		if (!Config::Menu && doingone == 0) {
			doingone = 1;
			SetFocus(tWnd);
			SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);
		}
		if (Config::Menu && doingone == 1)
		{
			SetFocus(hwnd);
			ShowCursor(TRUE);
			SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW);
			//UpdateWindow(hwnd);
			//Config::doingentity = 0;
			//Sleep(100);
			//Config::doingentity = 1;
			//_beginthread((_beginthread_proc_type)entity_thread, 0, 0);
			doingone = 0;
		}
		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		if (Config::Menu)
		{
			ImGui::SetNextWindowPos(ImVec2{ 50, 30 }, ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2{ 500, 600 }, ImGuiCond_Once);
			bool _visible = true;
			//if (ImGui::Begin(skCrypt(u8"Imperial Beta"), &_visible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar)) {
			if (ImGui::Begin(random_string_window().c_str(), &_visible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar)) {
				//ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.8f, 1.0f));
				ImGui::Text(skCrypt("Rigel External"));
				ImGui::PopStyleColor(1);
				if (ImGui::Button(skCrypt(u8"AIM"), ImVec2(150, 50)))
					tab_index = 1;

				ImGui::SameLine();

				if (ImGui::Button(skCrypt(u8"ESP"), ImVec2(150, 50)))
					tab_index = 2;
				ImGui::SameLine();

				if (ImGui::Button(skCrypt(u8"MISC"), ImVec2(150, 50)))
					tab_index = 3;

				ImGui::Separator();

				if (tab_index == 1) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.0f));
					ImGui::Toggle(skCrypt(u8"TriggerBot"), &Config::trigger, ImGuiToggleFlags_Animated);
					if (Config::trigger) {
						ImGui::Toggle(skCrypt(u8"Click"), &Config::dianshe, ImGuiToggleFlags_Animated);
						if (Config::dianshe) {
							ImGui::BulletText(u8"Hold on Fire for:");
							ImGui::SliderInt(u8"Delay Time", &Config::triggertime, 10, 1000, "%d");
							ImGui::BulletText(u8"After one shot, wait for:");
							ImGui::SliderInt(u8"Interval", &Config::intervaltime, 10, 1000, "%d");
							ImGui::Spacing();
						}
						ImGui::SliderFloat(u8"Trigger Distance", &Config::triggerdisnotzoom, 0.1f, 50.f, "%.2f");
						ImGui::SliderFloat(u8"Trigger Distance (Zoom)", &Config::triggerdiszoom, 0.1f, 200.f, "%.2f");
						ImGui::Spacing();
					}
					ImGui::Toggle(skCrypt(u8"Prediction"), &Config::Prediction, ImGuiToggleFlags_Animated);
					ImGui::PopStyleColor(1);
					ImGui::SliderFloat(u8"Smooth", &aSmoothAmount, 0.1f, 20.f, "%.2f");
					ImGui::SliderFloat(u8"Smooth(Zoom)", &smoothzoomin, 0.1f, 20.f, "%.2f");
					ImGui::SliderFloat(u8"Fov", &FOV, 0.1f, 500.f, "%.2f");
					ImGui::BulletText(skCrypt(u8"KeyBind"));
					if (ImGui::BeginCombo(skCrypt(u8"##Key"), keys))
					{
						for (int i = 0; i < 5; i++)
						{
							const bool type = keys == key_type[i];
							if (ImGui::Selectable(key_type[i], type))
							{
								keys = key_type[i];
								switch (i)
								{
								case 0:
									Config::aim_key = VK_LBUTTON;
									break;
								case 1:
									Config::aim_key = VK_RBUTTON;
									break;
								case 2:
									Config::aim_key = VK_MBUTTON;
									break;
								case 3:
									Config::aim_key = VK_XBUTTON1;
									break;
								case 4:
									Config::aim_key = VK_XBUTTON2;
									break;
								}
							}
						}
						ImGui::EndCombo();
					}
					ImGui::BulletText(skCrypt(u8"KeyBind2"));
					if (ImGui::BeginCombo(skCrypt(u8"##Key2"), keys2))
					{
						for (int i = 0; i < 5; i++)
						{
							const bool type = keys2 == key_type2[i];
							if (ImGui::Selectable(key_type2[i], type))
							{
								keys2 = key_type2[i];
								switch (i)
								{
								case 0:
									Config::aim_key2 = VK_LBUTTON;
									break;
								case 1:
									Config::aim_key2 = VK_RBUTTON;
									break;
								case 2:
									Config::aim_key2 = VK_MBUTTON;
									break;
								case 3:
									Config::aim_key2 = VK_XBUTTON1;
									break;
								case 4:
									Config::aim_key2 = VK_XBUTTON2;
									break;
								}
							}
						}
						ImGui::EndCombo();
					}
					ImGui::BulletText(skCrypt(u8"BoneSelect"));
					if (ImGui::BeginCombo(skCrypt(u8"##Bone"), bones))
					{
						for (int i = 0; i < 4; i++)
						{
							const bool type = bones == bones_type[i];
							if (ImGui::Selectable(bones_type[i], type))
							{
								bones = bones_type[i];
								switch (i)
								{
								case 0:
									Config::bone = 0;
									break;
								case 1:
									Config::bone = 1;
									break;
								case 2:
									Config::bone = 2;
									break;
								case 3:
									Config::bone = 3;
									break;
								}
							}
						}
						ImGui::EndCombo();
					}
				}

				if (tab_index == 2) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.0f));
					ImGui::Toggle(skCrypt(u8"GlowESP"), &Config::BodyEsp, ImGuiToggleFlags_Animated);
					if (Config::BodyEsp) {
						ImGui::Toggle(skCrypt(u8"Enable Shield Color"), &Config::BodyEspShield, ImGuiToggleFlags_Animated);
					}
					else Config::BodyEspShield = false;
					ImGui::PopStyleColor(1);
					if (!Config::BodyEspShield) {
						ImGui::ColorEdit3(skCrypt(u8"Visible Enemy Color"), (float*)&Config::enargb);
						ImGui::ColorEdit3(skCrypt(u8"Invisible Enemy Color"), (float*)&Config::invisenargb);
					}
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.0f));
					ImGui::Toggle(u8"ItemESP", &Config::ItemEsp, ImGuiToggleFlags_Animated);
					ImGui::Spacing();
					ImGui::PopStyleColor(1);
					ImGui::BulletText(u8"Drawing Options");
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.0f));
					ImGui::Toggle(u8"Draw Bone", &Config::draw_bone, ImGuiToggleFlags_Animated);
					ImGui::Toggle(u8"Draw Spec", &Config::spectcount, ImGuiToggleFlags_Animated);
					ImGui::Toggle(u8"Draw Fov", &Config::draw_fov, ImGuiToggleFlags_Animated);
					ImGui::Toggle(u8"Draw Teammates", &Config::espteammates, ImGuiToggleFlags_Animated);
					ImGui::Toggle(u8"Draw HealthBar", &Config::healthbar, ImGuiToggleFlags_Animated);
					ImGui::Toggle(u8"Draw 2D Box", &Config::draw2dbox, ImGuiToggleFlags_Animated);
					ImGui::PopStyleColor(1);
					ImGui::SliderFloat(u8"Max Drawing Distance", &Config::espdist, 10.f, 500.f, "%.1f");
				}
				if (tab_index == 3) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.0f));
					ImGui::Toggle(u8"No Recoil", &Config::NoRecoil, ImGuiToggleFlags_Animated);
					ImGui::PopStyleColor(1);
					ImGui::SliderFloat(u8"Recoil Restrain X", &Config::Recoilnumx, 1.f, 100.f, "%.1f");
					ImGui::SliderFloat(u8"Recoil Restrain Y", &Config::Recoilnumy, 1.f, 100.f, "%.1f");
				}
			}
			ImGui::End();
		}

		esp();
		ImGui::EndFrame();
		ImGui::Render();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		auto ss = ImVec4(0, 0, 0, 0);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&ss);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		g_pSwapChain->Present(1, 0);
	}

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);
	//}
	//__except (1) {

	//}
}