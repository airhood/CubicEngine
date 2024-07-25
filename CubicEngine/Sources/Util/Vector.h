#pragma once

#include <cmath>

namespace CubicEngine {
	class Vector2 {
	public:
		float x, y;

		Vector2() : x(0.0f), y(0.0f) {}

		Vector2(float x, float y) : x(x), y(y) {}

		~Vector2() {}

		void Set(float x, float y) {
			this->x = x;
			this->y = y;
		}

		float Dot(const Vector2& v) const {
			return x * v.x + y * v.y;
		}

		Vector2 operator+(const Vector2& v) const {
			return Vector2(x + v.x, y + v.y);
		}

		Vector2 operator-(const Vector2& v) const {
			return Vector2(x - v.x, y - v.y);
		}

		Vector2 operator*(const Vector2& v) const {
			return Vector2(x * v.x, y * v.y);
		}

		Vector2 operator/(const Vector2& v) const {
			return Vector2(x / v.x, y / v.y);
		}

		void operator+=(const Vector2& v) {
			x += v.x;
			y += v.y;
		}

		void operator-=(const Vector2& v) {
			x -= v.x;
			y -= v.y;
		}

		void operator*=(float s) {
			x *= s;
			y *= s;
		}

		void operator/=(float s) {
			x /= s;
			y /= s;
		}

		bool operator==(const Vector2& v) const {
			return ((x == v.x) && (y == v.y));
		}

		bool operator!=(const Vector2& v) const {
			return ((x != v.x) || (y != v.y));
		}

		void Normalize() {
			float s = 1.0f / Magnitude();
			x *= s;
			y *= s;
		}

		Vector2 Normalized() const {
			Vector2 v = *this;
			v.Normalize();
			return v;
		}

		float sqrMagnitude() const {
			return x * x + y * y;
		}

		float Magnitude() const {
			return sqrt(sqrMagnitude());
		}

		operator Vector3() const {
			return Vector3(x, y, 0);
		}

		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
			return Vector2(a.x * (1 - t) + b.x * t, a.y * (1 - t) + b.y * t);
		}

		static float Distance(const Vector2& a, const Vector2& b) {
			return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
		}
	};

	class Vector3 {
	public:
		float x, y, z;

		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		~Vector3() {}

		Vector3 Cross(const Vector3& v) const {
			return Vector3(y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x);
		}

		float Dot(const Vector3& v) const {
			return x * v.x + y * v.y + z * v.z;
		}

		Vector3 operator+(const Vector3& v) const {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 operator-(const Vector3& v) const {
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		Vector3 operator*(const Vector3& v) const {
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		Vector3 operator/(const Vector3& v) const {
			return Vector3(x / v.x, y / v.y, z / v.z);
		}

		void operator+=(const Vector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void operator-=(const Vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator*=(float s) {
			x *= s;
			y *= s;
			z *= s;
		}

		void operator/=(float s) {
			x /= s;
			y /= s;
			z /= s;
		}

		bool operator==(const Vector3& v) const {
			return ((x == v.x) && (y == v.y) && (z == v.z));
		}

		bool operator!=(const Vector3& v) const {
			return ((x != v.x) || (y != v.y) || (z != v.z));
		}

		void Normalize() {
			float s = 1.0f / Magnitude();
			x *= s;
			y *= s;
			z *= s;
		}

		Vector3 Normalized() const {
			Vector3 v = *this;
			v.Normalize();
			return v;
		}

		float sqrMagnitude() const {
			return x * x + y * y + z * z;
		}

		float Magnitude() const {
			return sqrt(sqrMagnitude());
		}

		explicit operator Vector2() const {
			return Vector2(x, y);
		}

		static Vector3 Lerp(const Vector3& a, Vector3& b, float t) {
			return Vector3(a.x * (1 - t) + b.x * t,
				a.y * (1 - t) + b.y * t,
				a.z * (1 - t) + b.z * t);
		}

		static float Distance(const Vector3& a, const Vector3& b) {
			return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2) + powf(a.z - b.z, 2));
		}
	};

	class Vector4 {
	public:
		float x, y, z, w;

		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		~Vector4() {}

		void Set(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		float Dot(const Vector4& v) const {
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		Vector4 operator+(const Vector4& v) const {
			return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		Vector4 operator-(const Vector4& v) const {
			return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		Vector4 operator*(const Vector4& v) const {
			return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
		}

		Vector4 operator/(const Vector4& v) const {
			return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
		}

		void operator+=(const Vector4& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}

		void operator-=(const Vector4& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		}

		void operator*=(float s) {
			x *= s;
			y *= s;
			z *= s;
			w *= s;
		}

		void operator/=(float s) {
			x /= s;
			y /= s;
			z /= s;
			w /= s;
		}

		bool operator==(const Vector4& v) const {
			return ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w));
		}

		bool operator!=(const Vector4& v) const {
			return ((x != v.x) || (y != v.y) || (z != v.z) || (w != v.w));
		}

		void Normalize() {
			float s = 1.0f / Magnitude();
			x *= s;
			y *= s;
			z *= s;
			w *= s;
		}

		Vector4 Normalized() const {
			Vector4 v = *this;
			v.Normalize();
			return v;
		}

		float sqrMagnitude() const {
			return x * x + y * y + z * z + w * w;
		}

		float Magnitude() const {
			return sqrt(sqrMagnitude());
		}

		explicit operator Vector2() const {
			return Vector2(x, y);
		}

		explicit operator Vector3() const {
			return Vector3(x, y, z);
		}

		static Vector4 Lerp(const Vector4& a, Vector4& b, float t) {
			return Vector4(a.x * (1 - t) + b.x * t,
				a.y * (1 - t) + b.y * t,
				a.z * (1 - t) + b.z * t,
				a.w * (1 - t) + b.w * t);
		}

		static float Distance(const Vector3& a, const Vector3& b) {
			return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2) + powf(a.z - b.z, 2));
		}
	};
}