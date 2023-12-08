#pragma once
#include"includes.hpp"
#include"offsets.h"

struct Color {
	float red;
	float green;
	float blue;

	bool operator==(const Color& other) const {
		return (red == other.red) && (green == other.green) && (blue == other.blue);
	}

	bool operator!=(const Color& other) const {
		return !(*this == other);
	}
};

struct Matrix {
	float matrix[16];
};
struct Vec3 {
	float x, y, z;
	Vec3() { x = 0; y = 0; z = 0; }
	Vec3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
	bool operator==(const float _t) {
		return x == _t && y == _t && z == _t;
	}
	bool operator==(Vec3 _t) {
		return x == _t.x && y == _t.y && z == _t.z;
	}
	bool operator!=(Vec3 _t) {
		return x != _t.x && y != _t.y && z != _t.z;
	}
	bool operator<(const float _t) {
		return x < _t && y < _t && z < _t;
	}
	bool operator>(const float _t) {
		return x > _t && y > _t && z > _t;
	}
	bool operator>=(const float _t) {
		return x >= _t && y >= _t && z >= _t;
	}
	bool operator<=(const float _t) {
		return x <= _t && y <= _t && z <= _t;
	}
	bool operator!=(const float _t) {
		return x != _t && y != _t && z != _t;
	}
	float Dot(const Vec3& rhs) const
	{
		return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
	}
};
struct Vec2 {
	float x, y;
	Vec2() { x = 0; y = 0; }
	Vec2(float _x, float _y) { x = _x; y = _y; }
	Vec2(Vec3 _t) { x = _t.x; y = _t.y; }
	bool operator==(const float _t) {
		return x == _t && y == _t;
	}
	bool operator<(const float _t) {
		return x < _t && y < _t;
	}
	bool operator>(const float _t) {
		return x > _t && y > _t;
	}
	bool operator>=(const float _t) {
		return x >= _t && y >= _t;
	}
	bool operator<=(const float _t) {
		return x <= _t && y <= _t;
	}
	bool operator!=(const float _t) {
		return x != _t && y != _t;
	}
};
struct ref_def_view {
	Vec2 tan_half_fov;
	char pad[0xC];
	Vec3 axis[3];
};
class refdef_t {
public:
	int x;
	int y;
	int Width;
	int Height;
	ref_def_view view;
};