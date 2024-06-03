#pragma once

#include "basics/Color.h"
#include "basics/Ray.h"

namespace crayg {

class AbstractIntegrator;

class IntegratorContext {
  public:
    IntegratorContext(AbstractIntegrator &integrator, int recursionDepth);
    IntegratorContext(const IntegratorContext &integratorContext);
    Color integrateRay(const Ray &ray);

  private:
    AbstractIntegrator &integrator;
    int recursionDepth;
};

} // crayg
