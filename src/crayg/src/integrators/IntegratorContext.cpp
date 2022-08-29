#include "IntegratorContext.h"
#include "AbstractIntegrator.h"

namespace crayg {
IntegratorContext::IntegratorContext(AbstractIntegrator &integrator, int recursionDepth)
    : integrator(integrator), recursionDepth(recursionDepth) {}

Color IntegratorContext::integrateRay(const Ray &ray) {
    return integrator.integrate(ray, recursionDepth + 1);
}
IntegratorContext::IntegratorContext(const IntegratorContext &integratorContext) = default;
} // crayg