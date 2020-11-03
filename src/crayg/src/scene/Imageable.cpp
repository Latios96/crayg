//
// Created by Jan Honsbrok on 25.11.18.
//

#include "Imageable.h"

#include <utility>

Imageable::Intersection::Intersection(float rayParameter, std::shared_ptr<Imageable> imageable) : rayParameter(
    rayParameter),
                                                                                                  imageable(std::move(
                                                                                                      imageable)) {}
