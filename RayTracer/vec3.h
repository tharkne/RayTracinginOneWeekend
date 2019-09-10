#include<cmath>
#include<iostream>

class vec3 {
public:
	vec3(){
		e[0] = 0;
		e[1] = 0;
		e[2] = 0;
	}
	vec3(float x_v, float y_v, float z_v) {
		e[0] = x_v;
		e[1] = y_v;
		e[2] = z_v;
	}
	// used for coordinate vectors
	inline float x() const {
		return e[0];
	}
	inline float y() const {
		return e[1];
	}
	inline float z() const {
		return e[2];
	}
	// used for colour vectors
	inline float r() const {
		return e[0];
	}
	inline float g() const {
		return e[1];
	}
	inline float b() const {
		return e[2];
	}

	inline vec3& operator+=(const vec3 &v);
	inline vec3& operator-=(const vec3 &v);
	inline vec3& operator*=(const vec3 &v);
	inline vec3& operator/=(const vec3 &v);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline const vec3& operator+() const {
		return *this;
	}
	inline const vec3& operator-() const {
		return vec3(-e[0], -e[1], e[2]);
	}
	// const pure numerical values
	inline const float operator[](int i) const{
		return e[i];
	}
	// reference to vector values
	inline const float& operator[](int i) {
		return e[i];
	}

	inline double length() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	inline double squared_length() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline void unit_vector();

	float e[3];
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];

	return is;
}

inline std::ostream& operator<<(std::ostream &os, vec3 &t) {
	os << " " << t.e[0] << " " << t.e[1] << " " << t.e[2];

	return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const float t) {
	return vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}

// another product function needed to assume flipped role
inline vec3 operator*(const float t, const vec3 &v1) {
	return vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}

inline vec3 operator/(const vec3 &v1, const float t) {
	return vec3(v1.e[0] / t, v1.e[1] / t, v1.e[2] / t);
}

inline float dot(const vec3 &v1, const vec3 &v2) {
	return(v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2]);
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
			  -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
				v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline vec3& vec3::operator+=(const vec3 &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}
inline vec3& vec3::operator-=(const vec3 &v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}
inline vec3& vec3::operator*=(const vec3 &v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}
inline vec3& vec3::operator/=(const vec3 &v) {
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}
inline vec3& vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}
inline vec3& vec3::operator/=(const float t) {
	float k = 1.0 / t;
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}