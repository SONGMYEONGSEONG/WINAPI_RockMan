#include <cmath>

#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

namespace ENGINE
{
	struct Vector2
	{
		float x, y;

		Vector2() : x(0), y(0) {} //x,y를 0으로 초기화 함수
		Vector2(float x, float y) : x(x), y(y) {}	//x,y 인자값으로 set하는 함수

		Vector2 operator-() const { return Vector2(-x,-y); }//(부호 변경)

		Vector2 operator*(const float& value) const { return Vector2( x * value , y * value );}
		Vector2 operator/(const float& value) const { return Vector2( x / value, y * value); }
		Vector2 operator*=(const float& value) { return Vector2(x *= value, y *= value); }
		Vector2 operator/=(const float& value) { return Vector2(x /= value, y /= value); }

		Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator+=(const Vector2& v) { return Vector2(x += v.x, y += v.y); }
		Vector2 operator-=(const Vector2& v) { return Vector2(x -= v.x, y -= v.y); }

	};

	inline bool operator== (const Vector2& lhs, const Vector2& rhs) { if (lhs.x == lhs.y) { return true; } false; }
	inline bool operator!= (const Vector2& lhs, const Vector2& rhs) { if (lhs.x != lhs.y) { return true; } false; }

	const float Epsilon = 0.0001f;

	inline bool Equal(float lhs, float rhs) { return (std::abs(lhs - rhs) <= Epsilon); }

#ifndef clamp
#define clamp(v, a, b) (a < b) ? min(max(v, a), b) : min(max(v, b), a)
#endif // !clamp

	int Repeat(int value, const int& max);	// value 인자값 받으면 숫자 도돌이표,


}

#endif // !ENGINE_MATH_H