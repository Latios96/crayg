#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORCONTEXT_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORCONTEXT_H_

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

#endif //CRAYG_SRC_CRAYG_SRC_INTEGRATORS_INTEGRATORCONTEXT_H_
