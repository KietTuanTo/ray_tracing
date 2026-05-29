#include "camera/camera.h"
#include "common/common.h"
#include "hittable/hittable.h"
#include "hittable/hittable_list/hittable_list.h"
#include "hittable/sphere/sphere.h"

int main() {
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;
    cam.aspect_ratio_ = 16.0 / 9.0;
    cam.image_width_ = 400;
    cam.render(world);
}