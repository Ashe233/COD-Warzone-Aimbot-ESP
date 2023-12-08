#pragma once
#define M_PI       3.14159265358979323846
#include"includes.hpp"
#include "GlobalVar.hpp"
#include "entity.hpp"
#include<complex>
#include "includes.hpp"
bool w2s(Vec3 world_location, Vec2* ScreenPos)
{
	auto Camera = read<uintptr_t>(oBaseAddress + camera_ptr);
	//printf("%llx\n", Camera);
	if (!Camera)
		return false;
	auto CameraPos = read<Vec3>(Camera + camera_pos);
	Vec3 local = { world_location.x - CameraPos.x ,world_location.y - CameraPos.y ,world_location.z - CameraPos.z };
	local = world_location;
	auto trans = Vec3{
		local.Dot(therefofgame.view.axis[1]),
		local.Dot(therefofgame.view.axis[2]),
		local.Dot(therefofgame.view.axis[0])
	};
	if (trans.z < 0.01f) {
		return false;
	}

	ScreenPos->x = (static_cast<float>(therefofgame.Width) / 2) * (1 - (trans.x / therefofgame.view.tan_half_fov.x / trans.z));
	ScreenPos->y = (static_cast<float>(therefofgame.Height) / 2) * (1 - (trans.y / therefofgame.view.tan_half_fov.y / trans.z));

	if (ScreenPos->x < 1 || ScreenPos->y < 1 || (ScreenPos->x > therefofgame.Width) || (ScreenPos->y > therefofgame.Height)) {
		return false;
	}
	return true;
}
inline void SolveQuartic(const std::complex<float> coefficients[5], std::complex<float> roots[4]) {
		const std::complex<float> a = coefficients[4];
		const std::complex<float> b = coefficients[3] / a;
		const std::complex<float> c = coefficients[2] / a;
		const std::complex<float> d = coefficients[1] / a;
		const std::complex<float> e = coefficients[0] / a;

		const std::complex<float> Q1 = c * c - 3.f * b * d + 12.f * e;
		const std::complex<float> Q2 = 2.f * c * c * c - 9.f * b * c * d + 27.f * d * d + 27.f * b * b * e - 72.f * c * e;
		const std::complex<float> Q3 = 8.f * b * c - 16.f * d - 2.f * b * b * b;
		const std::complex<float> Q4 = 3.f * b * b - 8.f * c;

		const std::complex<float> Q5 = std::pow(Q2 / 2.f + std::sqrt(Q2 * Q2 / 4.f - Q1 * Q1 * Q1), 1.f / 3.f);
		const std::complex<float> Q6 = (Q1 / Q5 + Q5) / 3.f;
		const std::complex<float> Q7 = 2.f * std::sqrt(Q4 / 12.f + Q6);

		roots[0] = (-b - Q7 - std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 - Q3 / Q7)) / 4.f;
		roots[1] = (-b - Q7 + std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 - Q3 / Q7)) / 4.f;
		roots[2] = (-b + Q7 - std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 + Q3 / Q7)) / 4.f;
		roots[3] = (-b + Q7 + std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 + Q3 / Q7)) / 4.f;
	}
inline void AimCorrection(Vec3 LocalPos, float scale1, Vec3* InVecArg, Vec3 currVelocity, float Bulletspeed)
	{
		double G = GameUnitsToMeter(750.0f / scale1);
		double A = GameUnitsToMeter(LocalPos.y);
		double B = GameUnitsToMeter(LocalPos.z);
		double C = GameUnitsToMeter(LocalPos.x);
		double M = GameUnitsToMeter(InVecArg->y);
		double N = GameUnitsToMeter(InVecArg->z);
		double O = GameUnitsToMeter(InVecArg->x);
		double P = GameUnitsToMeter(currVelocity.y);
		double Q = GameUnitsToMeter(currVelocity.z);
		double R = GameUnitsToMeter(currVelocity.x);
		double S = GameUnitsToMeter(Bulletspeed);
		double H = M - A;
		double J = O - C;
		double K = N - B;
		double L = -.5f * G;
		double c4 = L * L;
		double c3 = -2 * Q * L;
		double c2 = (Q * Q) - (2 * K * L) - (S * S) + (P * P) + (R * R);
		double c1 = (2 * K * Q) + (2 * H * P) + (2 * J * R);
		double c0 = (K * K) + (H * H) + (J * J);

		std::complex<float> pOutRoots[4];
		const std::complex<float> pInCoeffs[5] = { c0, c1, c2, c3, c4 };
		SolveQuartic(pInCoeffs, pOutRoots);
		float fBestRoot = FLT_MAX;
		for (int i = 0; i < 4; i++) {
			if (pOutRoots[i].real() > 0.f && std::abs(pOutRoots[i].imag()) < 0.0001f && pOutRoots[i].real() < fBestRoot) {
				fBestRoot = pOutRoots[i].real();
			}
		}
		InVecArg->y = MeterToGameUnits(A + (H + P * fBestRoot));
		InVecArg->z = MeterToGameUnits(B + (K + Q * fBestRoot - L * fBestRoot * fBestRoot));
		InVecArg->x = MeterToGameUnits(C + (J + R * fBestRoot));
	}