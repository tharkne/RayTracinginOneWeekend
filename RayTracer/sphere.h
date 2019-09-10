#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere : public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r) : center(cen), radius(r) {};

	bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

	vec3 center;
	float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b*b - 4*a*c;

	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / (2.0 * a);
		// solves for the param t when the sphere and vec3 intersect
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_param(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / (2.0 * a);
		// solves for the param t when the sphere and vec3 intersect
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_param(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}

	return false;
}


#endif