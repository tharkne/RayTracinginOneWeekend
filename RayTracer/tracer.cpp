#include <iostream>
#include "sphere.h"
#include "float.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

#include <random>

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		float rand_x = (float)(rand() % 100) / (float)100;
		float rand_y = (float)(rand() % 100) / (float)100;
		float rand_z = (float)(rand() % 100) / (float)100;

		p = 2.0 * vec3(rand_x, rand_y, rand_z) - vec3(1, 1, 1);

	} while (p.squared_length() >= 1);

	return p;
}

class lambertarian : public material {
public:
	lambertarian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const ray& ray_in, const hit_record &rec, vec3 &attenuation, ray& scattered) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};

vec3 reflect(const vec3& v, const vec3 &n) {
	return v - 2 * dot(v, n) * n;
}


vec3 color(const ray& r, hitable *world) {
	//float t = hit_sphere(vec3(0, 0, -1), .5, r);
	hit_record rec;

	// returns the normalized color representation of the chosen object if a ray
	// intersects the given object
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return .5 * color(ray(rec.p, target - rec.p), world);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = .5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(.5, .7, 1.0);
	}
}


int main() {
	int nx = 200;
	int ny = 100;
	int ns = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	// 'screen' output in the -z direction
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	// declaring the hitable objects in the world
	hitable *list[2];
	list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);

	camera cam;

	for (int j = ny-1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			/*float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = .8;*/
			vec3 col(0, 0, 0);


			if (i == 100 && j == 50) {
				std::cout << "";
			}

			// samples the 'edge pixels' and computes the average to get smoother lines around the object
			
			for (int s = 0; s < ns; s++) {
				float rand_i = (float)(rand() % 100) / (float)100;
				float rand_j = (float)(rand() % 100) / (float)100;

				float u = float(i + rand_i) / float(nx);
				float v = float(j + rand_j) / float(ny);

				ray r = cam.get_ray(u, v);

				vec3 p = r.point_at_param(2.0);
				col += color(r, world);
			}

			col /= float(ns);

			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}