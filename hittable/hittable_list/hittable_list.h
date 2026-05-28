#pragma once

#include "hittable/hittable.h"
#include "interval/interval.h"
#include <memory>
#include <vector>

class hittable_list : public hittable {
public:
    hittable_list();
    hittable_list(std::shared_ptr<hittable> object);

    void clear();
    void add(std::shared_ptr<hittable> object);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

private:
    std::vector<std::shared_ptr<hittable>> objects_;
};