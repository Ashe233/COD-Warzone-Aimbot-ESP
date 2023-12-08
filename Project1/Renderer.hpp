#pragma once
#include "Vector.hpp"

namespace OW {
	namespace Render {
		std::string string_To_UTF8(const std::string& str) {
			int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
			wchar_t* pwBuf = new wchar_t[nwLen + 1];
			ZeroMemory(pwBuf, nwLen * 2 + 2);
			::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
			int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
			char* pBuf = new char[nLen + 1];
			ZeroMemory(pBuf, nLen + 1);
			::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
			std::string retStr(pBuf);
			delete[]pwBuf;
			delete[]pBuf;
			pwBuf = NULL;
			pBuf = NULL;
			return retStr;
		}

		inline void DrawFilledRect(float x, float y, float w, float h, const ImU32& color)
		{
			ImDrawList* Draw = ImGui::GetBackgroundDrawList();

			auto a = (color >> 24) & 0xFF;
			auto r = (color >> 16) & 0xFF;
			auto g = (color >> 8) & 0xFF;
			auto b = (color) & 0xFF;

			Draw->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), NULL, NULL);
		}

		inline void DrawStrokeText(const ImVec2& pos, ImU32 col, const char* str, float size = 15.f)
		{
			ImDrawList* Draw = ImGui::GetBackgroundDrawList();

			Draw->AddText(NULL, size, ImVec2(pos.x, pos.y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), str);
			Draw->AddText(NULL, size, ImVec2(pos.x, pos.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), str);
			Draw->AddText(NULL, size, ImVec2(pos.x - 1, pos.y), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), str);
			Draw->AddText(NULL, size, ImVec2(pos.x + 1, pos.y), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), str);
			Draw->AddText(NULL, size, ImVec2(pos.x, pos.y), col, str);
		}

		inline void DrawInfo(const ImVec2& Pos, ImU32 TagCol, int HeightSize, std::string Info, float distance, float EnHealth, float EnHealthMax) {
			ImDrawList* Draw = ImGui::GetBackgroundDrawList();
			ImVec2 InfoSize = ImGui::CalcTextSize(Info.c_str());
			if (distance < 200)  // 병신같은게 1 / distance 안해놓고 걍 연산때려서 그런거아님 
			{
				// 
				if (EnHealth > 0.f)
				{
					Draw->AddRectFilled(ImVec2(Pos.x - (InfoSize.x / 2), Pos.y + (HeightSize / 2)), ImVec2(Pos.x + (InfoSize.x / 2) + 35, Pos.y - (HeightSize / 2)), ImGui::GetColorU32(ImVec4(0.2, 0.2, 0.6, 0.3)));
					Draw->AddRectFilled(ImVec2(Pos.x - (InfoSize.x / 2), Pos.y + (HeightSize / 2)), ImVec2(Pos.x - (InfoSize.x / 2) + 5, Pos.y - (HeightSize / 2)), TagCol);
					Draw->AddRectFilled(ImVec2(Pos.x - (InfoSize.x / 2) + 7, Pos.y + (HeightSize / 2) - 6), ImVec2(Pos.x - (InfoSize.x / 2) + 7 + ((abs((Pos.x - (InfoSize.x / 2) + 7) - (Pos.x + (InfoSize.x / 2))) / EnHealthMax) * EnHealth), Pos.y + (HeightSize / 2) - 2), ImGui::GetColorU32(ImVec4(0, 1, 0, 1)));
					DrawStrokeText(ImVec2(Pos.x - ((InfoSize.x / 2)) + 10, Pos.y - (HeightSize / 2)), ImGui::GetColorU32(ImVec4(1, 0.6, 0.6, 1)), Info.c_str());
					// 여기부분
					//std::cout << Info;
				}
				else
				{
					Draw->AddRectFilled(ImVec2(Pos.x - (InfoSize.x / 2), Pos.y + (HeightSize / 2)), ImVec2(Pos.x + (InfoSize.x / 2) + 35, Pos.y - (HeightSize / 2)), ImGui::GetColorU32(ImVec4(0.2, 0.2, 0.6, 0.3)));
					Draw->AddRectFilled(ImVec2(Pos.x - (InfoSize.x / 2), Pos.y + (HeightSize / 2)), ImVec2(Pos.x - (InfoSize.x / 2) + 5, Pos.y - (HeightSize / 2)), ImGui::GetColorU32(ImVec4(0.4, 0.4, 0.4, 1.0f)));
					Draw->AddRectFilled(ImVec2(Pos.x - (InfoSize.x / 2) + 7, Pos.y + (HeightSize / 2) - 6), ImVec2(Pos.x - (InfoSize.x / 2) + 7 + ((abs((Pos.x - (InfoSize.x / 2) + 7) - (Pos.x + (InfoSize.x / 2))) / EnHealthMax) * EnHealth), Pos.y + (HeightSize / 2) - 2), ImGui::GetColorU32(ImVec4(0, 1, 0, 1)));
					DrawStrokeText(ImVec2(Pos.x - ((InfoSize.x / 2)) + 10, Pos.y - (HeightSize / 2)), ImGui::GetColorU32(ImVec4(1, 0.6, 0.6, 1)), Info.c_str());
				}
			}
			else  // distance >= 200m
			{
				DrawStrokeText(ImVec2(Pos.x - ((InfoSize.x / 2)) + 10, Pos.y - (HeightSize / 2)), ImGui::GetColorU32(ImVec4(1, 0.6, 0.6, 1)), Info.c_str());
			}
		}

		inline void RenderLine(const Vector2& from, const Vector2& to, uint32_t color, float thickness = 1.0f)
		{
			ImDrawList* Draw = ImGui::GetBackgroundDrawList();

			auto a = (color >> 24) & 0xff;
			auto r = (color >> 16) & 0xff;
			auto g = (color >> 8) & 0xff;
			auto b = (color) & 0xff;

			Draw->AddLine(ImVec2(from.X, from.Y), ImVec2(to.X, to.Y), ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), thickness);
		}
		void Help(const char* desc) {
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered()) {
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(desc);
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}
		inline void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness = 0.5f)
		{
			ImDrawList* Draw = ImGui::GetBackgroundDrawList();
			float lineW = (W / 3);
			float lineH = (H / 3);

			////black outlines
			Draw->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
			Draw->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
			Draw->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
			Draw->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
			Draw->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
			Draw->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
			Draw->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
			Draw->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

			//corners
			Draw->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), color, thickness);
			Draw->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), color, thickness);
			Draw->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), color, thickness);
			Draw->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), color, thickness);
			Draw->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), color, thickness);
			Draw->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), color, thickness);
			Draw->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), color, thickness);
			Draw->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), color, thickness);
		}
		inline void DrawEdges(const ImVec2& top, const ImVec2& bot, const ImVec2& base, ImU32 col)
		{
			ImDrawList* Draw = ImGui::GetBackgroundDrawList();
			float scale = (bot.y - top.y) / 3.0f;
			float length = scale / 1;
			Draw->AddLine(ImVec2(base.x - scale, top.y), ImVec2(base.x - scale + length, top.y), col, 2.0f); //  --- Top left
			Draw->AddLine(ImVec2(base.x - scale, top.y), ImVec2(base.x - scale, top.y + length), col, 2.0f); // | Top left
			Draw->AddLine(ImVec2(base.x + scale / 3, top.y), ImVec2(base.x + scale / 3 + length, top.y), col, 2.0f); // --- Top right
			Draw->AddLine(ImVec2(base.x + scale / 3 + length, top.y), ImVec2(base.x + scale / 3 + length, top.y + length), col, 2.0f); // | Top right
			Draw->AddLine(ImVec2(base.x - scale, bot.y), ImVec2(base.x - scale + length, bot.y), col, 2.0f); // --- Bottom left
			Draw->AddLine(ImVec2(base.x - scale, bot.y), ImVec2(base.x - scale, bot.y - length), col, 2.0f); // | Bottom left
			Draw->AddLine(ImVec2(base.x + scale / 3 + length, bot.y), ImVec2(base.x + scale / 3, bot.y), col, 2.0f); // --- Bottom right
			Draw->AddLine(ImVec2(base.x + scale / 3 + length, bot.y), ImVec2(base.x + scale / 3 + length, bot.y - length), col, 2.0f); // | Bottom right
		}
		inline void DrawSKILL(const ImVec2& Pos, std::string skill) {
			ImDrawList* Draw = ImGui::GetBackgroundDrawList();
			ImVec2 InfoSize = ImGui::CalcTextSize(skill.c_str());
			DrawStrokeText(ImVec2(Pos.x, Pos.y), ImGui::GetColorU32(ImVec4(1, 1, 1, 1)), skill.c_str(), 19);
			//std::cout << skillstring << std::endl;
		}


		void DrawLine(Vector2 From, Vector2 To, Color color, int thickness) {
			int x1 = From.X;
			int y1 = From.Y;
			int x2 = To.X;
			int y2 = To.Y;

			ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), thickness);
		}
		void DrawBox(Rect rect, Color color, float thickness) {
			Vector2 v1 = Vector2(rect.x, rect.y);
			Vector2 v2 = Vector2(rect.x + rect.width, rect.y);
			Vector2 v3 = Vector2(rect.x + rect.width, rect.y + rect.height);
			Vector2 v4 = Vector2(rect.x, rect.y + rect.height);

			DrawLine(v1, v2, color, thickness);
			DrawLine(v2, v3, color, thickness);
			DrawLine(v3, v4, color, thickness);
			DrawLine(v4, v1, color, thickness);

		}
		void DrawHealthBar(Vector2 screenPos, float height, float currentHealth, float maxHealth) {
			screenPos.X += 8;
			DrawBox(Rect(screenPos.X, screenPos.Y, 5.0f, height + 2), Color(0, 0, 0), 3);
			screenPos.X += 1;
			screenPos.Y += 1;
			float barHeight = (currentHealth * height) / maxHealth;
			Color HealthColor = Color(10, 255, 10);
			if (currentHealth <= (80)) {
				HealthColor = { 255,255,10 };
			}
			if (currentHealth <= (60)) {
				HealthColor = { 255,150,10 };
			}
			if (currentHealth < (40)) {
				HealthColor = { 255,50,10 };
			}
			if (currentHealth < (20)) {
				HealthColor = { 255,10,10 };
			}
			if (currentHealth < (maxHealth * 0)) {
				HealthColor = { 0,0,0 };
			}
			DrawBox(Rect(screenPos.X, screenPos.Y, 3.0f, barHeight), HealthColor, 3);
		}
		void DrawString(Vector2 Position, Color color, const char* str) {
			int x = Position.X;
			int y = Position.Y;
			ImFont a;
			std::string utf_8_1 = std::string(str);
			std::string utf_8_2 = string_To_UTF8(utf_8_1);
			ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), utf_8_2.c_str());
		}

	}
}