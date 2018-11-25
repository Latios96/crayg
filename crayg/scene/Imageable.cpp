//
// Created by Jan Honsbrok on 25.11.18.
//

#include "Imageable.h"

Imageable::Intersection::Intersection(float rayParameter, Imageable *imageable) : rayParameter(rayParameter),
                                                                                  imageable(imageable) {}
