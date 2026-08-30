#pragma once

#include "Hit.h"
#include "Ray.h"

namespace hlab
{
    using namespace glm;

    class Sphere
    {
    public:
        glm::vec3 center;
        float radius;
        glm::vec3 color; // 뒤에서 '재질(material)'로 확장

        Sphere(const glm::vec3 &center, const float radius, const glm::vec3 &color)
            : center(center), color(color), radius(radius)
        {
        }

        // Wikipedia Line–sphere intersection
        // https://en.wikipedia.org/wiki/Line-sphere_intersection
        Hit IntersectRayCollision(Ray &ray)
        {
            Hit hit = Hit{-1.0f, vec3(0.0f), vec3(0.0f)}; // d가 음수이면 충돌을 안한 것으로 가정

            /*
             * hit.d = ... // 광선의 시작점으로부터 충돌지점까지의 거리 (float)
             * hit.point = ... // 광선과 구가 충돌한 지점의 위치 (vec3)
             * hit.normal = .. // 충돌 지점에서 구의 단위 법선 벡터(unit normal vector)
             */



            const float a = glm::dot(ray.dir, ray.dir);
            const float b = 2 * (glm::dot( ray.dir, (ray.start - this->center) ));
            const float c = glm::dot( (ray.start - this->center), (ray.start - this->center) ) - pow(this->radius, 2);

            const float discriminant =( pow(b, 2) ) - (4 * a * c);

            if (discriminant < 0) {}
            else if (discriminant == 0) {
                hit.d = -b / (2 * a);
                hit.point = ray.start + (hit.d * ray.dir);
            
                glm::normalize(hit.point - this->center);
            }
                
            else {
                const float temp1{ (-b + sqrt(discriminant)) / 2 * a };
                const float temp2{ (-b - sqrt(discriminant)) / 2 * a };

                if (temp1 < temp2)
                    hit.d = temp1;
                else
                    hit.d = temp2;

                hit.point = ray.start + (hit.d * ray.dir);

                glm::normalize(hit.point - this->center);


            }


            return hit;
        }
    };
}

// 거리 d가 크면 클수록 밝기가 밝아지고 작으면 작을수록 검게 느껴지게 표현함.
