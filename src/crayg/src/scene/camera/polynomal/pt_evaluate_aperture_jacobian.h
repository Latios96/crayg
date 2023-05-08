const float dx00 =
    +0.852921 + 0.000124527 * dx + -2.71154e-06 * y + 1.30552 * lens_ipow(dy, 2) + 4.19041 * lens_ipow(dx, 2) +
    0.0274398 * y * dy + 3.07262e-05 * lens_ipow(y, 2) + 0.0847662 * x * dx + 0.000102202 * lens_ipow(x, 2) +
    -0.0148531 * lens_ipow(lambda, 3) + 0.000421551 * lens_ipow(y, 2) * lens_ipow(dy, 2) +
    0.00100649 * x * y * dx * dy + 0.000444441 * lens_ipow(x, 2) * lens_ipow(dy, 2) +
    7.2146e-06 * lens_ipow(x, 2) * y * dy + -5.91978 * lens_ipow(dx, 2) * lens_ipow(dy, 2) * lambda +
    -0.00538447 * x * dx * lens_ipow(lambda, 3) + -14.25 * lens_ipow(dy, 6) +
    -9.02734 * lens_ipow(dx, 4) * lens_ipow(lambda, 2) + 5.06585e-09 * lens_ipow(y, 5) * dy +
    3.87732e-06 * lens_ipow(x, 4) * lens_ipow(dx, 2) + 0.760605 * y * lens_ipow(dx, 4) * dy * lens_ipow(lambda, 2) +
    7.50047e-09 * lens_ipow(x, 4) * lens_ipow(y, 2) * lens_ipow(dx, 2) +
    -3.14874e-12 * lens_ipow(x, 4) * lens_ipow(y, 4) + -1.36459e-12 * lens_ipow(x, 8) +
    -1.46507e-13 * x * lens_ipow(y, 8) * dx + 0.000235717 * lens_ipow(x, 2) * lens_ipow(lambda, 8) +
    5.97434e-07 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(lambda, 6) + 0.0f;
const float dx01 =
    +-6.98437e-06 + -0.000167247 * dx + -2.71154e-06 * x + 2.77587 * dx * dy + 0.0281048 * y * dx + 0.0274398 * x * dy +
    6.14524e-05 * x * y + 0.000843102 * x * y * lens_ipow(dy, 2) + 0.000503246 * lens_ipow(x, 2) * dx * dy +
    2.40487e-06 * lens_ipow(x, 3) * dy + 1.26841 * y * lens_ipow(dx, 3) * lens_ipow(dy, 2) +
    2.53292e-08 * x * lens_ipow(y, 4) * dy + 0.760605 * x * lens_ipow(dx, 4) * dy * lens_ipow(lambda, 2) +
    3.00019e-09 * lens_ipow(x, 5) * y * lens_ipow(dx, 2) + -2.51899e-12 * lens_ipow(x, 5) * lens_ipow(y, 3) +
    -5.8603e-13 * lens_ipow(x, 2) * lens_ipow(y, 7) * dx + 3.98289e-07 * lens_ipow(x, 3) * y * lens_ipow(lambda, 6) +
    0.0f;
const float dx02 =
    +102.533 + -0.000167247 * y + 0.000124527 * x + 93.3834 * lens_ipow(dy, 2) + 281.858 * lens_ipow(dx, 2) +
    2.77587 * y * dy + 0.0140524 * lens_ipow(y, 2) + 8.38082 * x * dx + 0.0423831 * lens_ipow(x, 2) +
    -0.6378 * lens_ipow(lambda, 4) + 0.000503246 * lens_ipow(x, 2) * y * dy +
    -11.8396 * x * dx * lens_ipow(dy, 2) * lambda + -0.00269224 * lens_ipow(x, 2) * lens_ipow(lambda, 3) +
    -16925.1 * lens_ipow(dx, 4) * lens_ipow(dy, 2) + 1.90262 * lens_ipow(y, 2) * lens_ipow(dx, 2) * lens_ipow(dy, 2) +
    -36.1094 * x * lens_ipow(dx, 3) * lens_ipow(lambda, 2) + 1.55093e-06 * lens_ipow(x, 5) * dx +
    -121270 * lens_ipow(dx, 2) * lens_ipow(dy, 6) + 3.04242 * x * y * lens_ipow(dx, 3) * dy * lens_ipow(lambda, 2) +
    3.00019e-09 * lens_ipow(x, 5) * lens_ipow(y, 2) * dx + -69045.9 * lens_ipow(dx, 6) * lens_ipow(lambda, 4) +
    -7.32537e-14 * lens_ipow(x, 2) * lens_ipow(y, 8) + 0.0f;
const float dx03 = +186.767 * dx * dy + 2.77587 * y * dx + 2.61103 * x * dy + 0.0274398 * x * y +
                   0.000843102 * x * lens_ipow(y, 2) * dy + 0.000503246 * lens_ipow(x, 2) * y * dx +
                   0.000296294 * lens_ipow(x, 3) * dy + 2.40487e-06 * lens_ipow(x, 3) * y +
                   -11.8396 * x * lens_ipow(dx, 2) * dy * lambda + -6770.03 * lens_ipow(dx, 5) * dy +
                   1.26841 * lens_ipow(y, 2) * lens_ipow(dx, 3) * dy + -85.4999 * x * lens_ipow(dy, 5) +
                   5.06585e-09 * x * lens_ipow(y, 5) + -242541 * lens_ipow(dx, 3) * lens_ipow(dy, 5) +
                   0.760605 * x * y * lens_ipow(dx, 4) * lens_ipow(lambda, 2) + 0.0f;
const float dx04 =
    +-0.0445594 * x * lens_ipow(lambda, 2) + -2.5512 * dx * lens_ipow(lambda, 3) +
    -5.91978 * x * lens_ipow(dx, 2) * lens_ipow(dy, 2) + -0.00807671 * lens_ipow(x, 2) * dx * lens_ipow(lambda, 2) +
    -18.0547 * x * lens_ipow(dx, 4) * lambda + 1.52121 * x * y * lens_ipow(dx, 4) * dy * lambda +
    -39454.8 * lens_ipow(dx, 7) * lens_ipow(lambda, 3) + 0.000628579 * lens_ipow(x, 3) * lens_ipow(lambda, 7) +
    1.19487e-06 * lens_ipow(x, 3) * lens_ipow(y, 2) * lens_ipow(lambda, 5) + 0.0f;
const float dx10 =
    +2.799 * dx * dy + 0.0277656 * y * dx + 0.028556 * x * dy + 6.13974e-05 * x * y +
    0.000499806 * lens_ipow(y, 2) * dx * dy + 0.000206748 * x * y * lens_ipow(dy, 2) +
    -0.0155679 * lens_ipow(x, 2) * lens_ipow(dx, 3) * dy + 7.5428e-06 * lens_ipow(x, 3) * y * lens_ipow(dx, 2) +
    2.60457 * y * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 2) +
    -1.38782e-07 * lens_ipow(y, 5) * dx * lens_ipow(dy, 2) + 0.000108189 * x * y * lens_ipow(lambda, 6) +
    -6.92164e-09 * x * lens_ipow(y, 4) * lens_ipow(dx, 2) * dy + -2.74116e-12 * lens_ipow(x, 3) * lens_ipow(y, 5) +
    3.0797e-10 * lens_ipow(x, 6) * y * dx + -7.64458e-11 * lens_ipow(x, 7) * dy +
    -3.18705e-10 * lens_ipow(x, 3) * lens_ipow(y, 4) * dy * lens_ipow(lambda, 2) + 0.0f;
const float dx11 =
    +0.853298 + -0.000190277 * dy + -5.79236e-06 * y + 4.14295 * lens_ipow(dy, 2) + 1.32585 * lens_ipow(dx, 2) +
    0.0840512 * y * dy + 0.000102336 * lens_ipow(y, 2) + 0.0277656 * x * dx + 3.06987e-05 * lens_ipow(x, 2) +
    -0.0174172 * lens_ipow(lambda, 3) + 0.000999612 * x * y * dx * dy +
    0.000103374 * lens_ipow(x, 2) * lens_ipow(dy, 2) + 0.772492 * y * lens_ipow(dx, 2) * lens_ipow(dy, 3) +
    5.59606e-06 * lens_ipow(y, 4) * lens_ipow(dy, 2) + 1.8857e-06 * lens_ipow(x, 4) * lens_ipow(dx, 2) +
    -6.00427 * lens_ipow(dy, 4) * lens_ipow(lambda, 3) +
    -138.659 * lens_ipow(dx, 4) * lens_ipow(dy, 2) * lens_ipow(lambda, 2) + -178.461 * lens_ipow(dx, 8) +
    -0.210737 * lens_ipow(y, 2) * lens_ipow(dy, 6) + -1.34807e-12 * lens_ipow(y, 8) +
    2.60457 * x * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 2) +
    -6.93911e-07 * x * lens_ipow(y, 4) * dx * lens_ipow(dy, 2) + 5.40946e-05 * lens_ipow(x, 2) * lens_ipow(lambda, 6) +
    -1.38433e-08 * lens_ipow(x, 2) * lens_ipow(y, 3) * lens_ipow(dx, 2) * dy +
    -3.42645e-12 * lens_ipow(x, 4) * lens_ipow(y, 4) + 4.39957e-11 * lens_ipow(x, 7) * dx +
    0.000458195 * lens_ipow(y, 2) * lens_ipow(lambda, 8) +
    -3.18705e-10 * lens_ipow(x, 4) * lens_ipow(y, 3) * dy * lens_ipow(lambda, 2) + 0.0f;
const float dx12 =
    +190.101 * dx * dy + 2.65171 * y * dx + 2.799 * x * dy + 0.0277656 * x * y +
    0.000499806 * x * lens_ipow(y, 2) * dy + -7743.36 * lens_ipow(dx, 5) * dy +
    0.772492 * lens_ipow(y, 2) * dx * lens_ipow(dy, 3) + -0.0155679 * lens_ipow(x, 3) * lens_ipow(dx, 2) * dy +
    3.7714e-06 * lens_ipow(x, 4) * y * dx + -554.637 * y * lens_ipow(dx, 3) * lens_ipow(dy, 2) * lens_ipow(lambda, 2) +
    -1427.69 * y * lens_ipow(dx, 7) + 2.60457 * x * y * lens_ipow(dy, 4) * lens_ipow(lambda, 2) +
    -1.38782e-07 * x * lens_ipow(y, 5) * lens_ipow(dy, 2) + -6.92164e-09 * lens_ipow(x, 2) * lens_ipow(y, 4) * dx * dy +
    4.39957e-11 * lens_ipow(x, 7) * y + -33165.9 * dx * lens_ipow(dy, 5) * lens_ipow(lambda, 3) + 0.0f;
const float dx13 =
    +102.517 + -0.000190277 * y + 284.415 * lens_ipow(dy, 2) + 95.0505 * lens_ipow(dx, 2) + 8.28589 * y * dy +
    0.0420256 * lens_ipow(y, 2) + 2.799 * x * dx + 0.014278 * lens_ipow(x, 2) + -0.786573 * lens_ipow(lambda, 4) +
    0.000499806 * x * lens_ipow(y, 2) * dx + 0.000206748 * lens_ipow(x, 2) * y * dy + -1290.56 * lens_ipow(dx, 6) +
    1.15874 * lens_ipow(y, 2) * lens_ipow(dx, 2) * lens_ipow(dy, 2) + 2.23843e-06 * lens_ipow(y, 5) * dy +
    -0.00518931 * lens_ipow(x, 3) * lens_ipow(dx, 3) + -24.0171 * y * lens_ipow(dy, 3) * lens_ipow(lambda, 3) +
    -277.319 * y * lens_ipow(dx, 4) * dy * lens_ipow(lambda, 2) + -0.421474 * lens_ipow(y, 3) * lens_ipow(dy, 5) +
    10.4183 * x * y * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 2) + -2.77565e-07 * x * lens_ipow(y, 5) * dx * dy +
    -3.46082e-09 * lens_ipow(x, 2) * lens_ipow(y, 4) * lens_ipow(dx, 2) + -9.55573e-12 * lens_ipow(x, 8) +
    -82914.7 * lens_ipow(dx, 2) * lens_ipow(dy, 4) * lens_ipow(lambda, 3) +
    -436424 * lens_ipow(dy, 8) * lens_ipow(lambda, 2) +
    -7.96763e-11 * lens_ipow(x, 4) * lens_ipow(y, 4) * lens_ipow(lambda, 2) + 0.0f;
const float dx14 = +-0.0522516 * y * lens_ipow(lambda, 2) + -3.14629 * dy * lens_ipow(lambda, 3) +
                   -18.0128 * y * lens_ipow(dy, 4) * lens_ipow(lambda, 2) +
                   -277.319 * y * lens_ipow(dx, 4) * lens_ipow(dy, 2) * lambda +
                   5.20915 * x * y * dx * lens_ipow(dy, 4) * lambda +
                   0.000324568 * lens_ipow(x, 2) * y * lens_ipow(lambda, 5) +
                   -49748.8 * lens_ipow(dx, 2) * lens_ipow(dy, 5) * lens_ipow(lambda, 2) +
                   -96983 * lens_ipow(dy, 9) * lambda + 0.00122185 * lens_ipow(y, 3) * lens_ipow(lambda, 7) +
                   -1.59353e-10 * lens_ipow(x, 4) * lens_ipow(y, 4) * dy * lambda + 0.0f;
const float dx20 = +-0.00384714 + -2.01831e-07 * y + 0.0291522 * lens_ipow(dy, 2) + 0.0885705 * lens_ipow(dx, 2) +
                   0.000799802 * y * dy + -6.90312e-07 * y * dx + 3.95807e-06 * lens_ipow(y, 2) + 0.00238333 * x * dx +
                   1.17107e-05 * lens_ipow(x, 2) + 1.531e-05 * y * dx * dy + -1.13732e-09 * x * lens_ipow(y, 2) +
                   -1.72311e-07 * lens_ipow(x, 2) * dy + -0.00405009 * lens_ipow(lambda, 4) +
                   0.000233736 * y * lens_ipow(dx, 2) * dy + 3.07865e-06 * lens_ipow(y, 2) * lens_ipow(dy, 2) +
                   -4.43063e-09 * lens_ipow(x, 2) * lens_ipow(y, 2) + -1.28989e-12 * lens_ipow(y, 6) +
                   7.32594e-08 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(dx, 2) +
                   -6.51537e-06 * x * lens_ipow(y, 2) * dx * lens_ipow(dy, 2) * lambda +
                   -7.33946e-07 * lens_ipow(x, 2) * y * dy * lens_ipow(lambda, 4) +
                   -1.47744e-06 * lens_ipow(x, 3) * dx * lens_ipow(lambda, 4) + -3.32576e-14 * lens_ipow(x, 8) +
                   -0.190532 * lens_ipow(dx, 4) * lens_ipow(lambda, 5) + 0.0191836 * lens_ipow(lambda, 10) + 0.0f;
const float dx21 = +-8.29286e-07 + -1.72183e-05 * dx + -2.01831e-07 * x + 0.0595432 * dx * dy + 0.000787236 * y * dx +
                   0.000799802 * x * dy + -6.90312e-07 * x * dx + 7.91613e-06 * x * y +
                   0.00086089 * lens_ipow(dx, 2) * dy + 1.531e-05 * x * dx * dy + -1.13732e-09 * lens_ipow(x, 2) * y +
                   0.000233736 * x * lens_ipow(dx, 2) * dy + 6.1573e-06 * x * y * lens_ipow(dy, 2) +
                   -2.95375e-09 * lens_ipow(x, 3) * y + 0.0161016 * y * lens_ipow(dx, 3) * lens_ipow(dy, 2) +
                   -7.73932e-12 * x * lens_ipow(y, 5) + 4.88396e-08 * lens_ipow(x, 3) * y * lens_ipow(dx, 2) +
                   -5.19667e-07 * lens_ipow(y, 3) * dx * lens_ipow(lambda, 3) +
                   -6.51537e-06 * lens_ipow(x, 2) * y * dx * lens_ipow(dy, 2) * lambda +
                   -2.44649e-07 * lens_ipow(x, 3) * dy * lens_ipow(lambda, 4) +
                   -0.245492 * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 5) + 0.0f;
const float dx22 =
    +0.709292 + -0.000739628 * dy + -0.00103486 * dx + -1.72183e-05 * y + 1.76725 * lens_ipow(dy, 2) +
    5.27962 * lens_ipow(dx, 2) + 0.0595432 * y * dy + 0.000393618 * lens_ipow(y, 2) + 0.177141 * x * dx +
    -6.90312e-07 * x * y + 0.00119166 * lens_ipow(x, 2) + 0.00172178 * y * dx * dy + 1.531e-05 * x * y * dy +
    -0.448288 * lens_ipow(lambda, 4) + 0.000467471 * x * y * dx * dy +
    0.0241525 * lens_ipow(y, 2) * lens_ipow(dx, 2) * lens_ipow(dy, 2) +
    4.88396e-08 * lens_ipow(x, 3) * lens_ipow(y, 2) * dx + -1.29917e-07 * lens_ipow(y, 4) * lens_ipow(lambda, 3) +
    -3.25769e-06 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(dy, 2) * lambda +
    -3.6936e-07 * lens_ipow(x, 4) * lens_ipow(lambda, 4) + -0.245492 * y * lens_ipow(dy, 3) * lens_ipow(lambda, 5) +
    -0.762129 * x * lens_ipow(dx, 3) * lens_ipow(lambda, 5) + 2.1333 * lens_ipow(lambda, 10) + 0.0f;
const float dx23 = +-0.000739628 * dx + 3.53449 * dx * dy + 0.0595432 * y * dx + 0.0583045 * x * dy +
                   0.000799802 * x * y + 0.00086089 * y * lens_ipow(dx, 2) + 1.531e-05 * x * y * dx +
                   -5.7437e-08 * lens_ipow(x, 3) + 0.000233736 * x * y * lens_ipow(dx, 2) +
                   6.1573e-06 * x * lens_ipow(y, 2) * dy + 0.0161016 * lens_ipow(y, 2) * lens_ipow(dx, 3) * dy +
                   -6.51537e-06 * lens_ipow(x, 2) * lens_ipow(y, 2) * dx * dy * lambda +
                   -2.44649e-07 * lens_ipow(x, 3) * y * lens_ipow(lambda, 4) +
                   -0.736476 * y * dx * lens_ipow(dy, 2) * lens_ipow(lambda, 5) + 0.0f;
const float dx24 = +-1.79315 * dx * lens_ipow(lambda, 3) + -0.0162004 * x * lens_ipow(lambda, 3) +
                   -3.8975e-07 * lens_ipow(y, 4) * dx * lens_ipow(lambda, 2) +
                   -3.25769e-06 * lens_ipow(x, 2) * lens_ipow(y, 2) * dx * lens_ipow(dy, 2) +
                   -9.78594e-07 * lens_ipow(x, 3) * y * dy * lens_ipow(lambda, 3) +
                   -1.47744e-06 * lens_ipow(x, 4) * dx * lens_ipow(lambda, 3) +
                   -1.22746 * y * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 4) +
                   -0.952661 * x * lens_ipow(dx, 4) * lens_ipow(lambda, 4) + 21.333 * dx * lens_ipow(lambda, 9) +
                   0.191836 * x * lens_ipow(lambda, 9) + 0.0f;
const float dx30 =
    +5.61584e-07 + -4.87364e-06 * dy + -4.26523e-06 * dx + 0.0593271 * dx * dy + 0.000802082 * y * dx +
    -8.07297e-09 * lens_ipow(y, 2) + 0.000782293 * x * dy + 7.94563e-06 * x * y + -1.68112e-07 * x * y * dy +
    -1.98338e-09 * x * lens_ipow(y, 2) + -1.19612e-09 * lens_ipow(x, 2) * y + -3.32309e-09 * x * lens_ipow(y, 3) +
    -7.25946e-05 * lens_ipow(y, 2) * lens_ipow(dx, 3) * dy + -1.33175e-06 * lens_ipow(y, 3) * dx * lens_ipow(dy, 2) +
    -4.72269e-07 * x * lens_ipow(y, 2) * dy * lens_ipow(lambda, 2) +
    4.49165e-08 * x * lens_ipow(y, 3) * lens_ipow(dx, 2) + 4.15048e-08 * lens_ipow(x, 3) * y * lens_ipow(dy, 2) +
    -9.52765e-12 * lens_ipow(x, 5) * y + -0.000107297 * y * dx * lens_ipow(lambda, 5) +
    -0.176694 * lens_ipow(dx, 3) * dy * lens_ipow(lambda, 5) +
    0.0881476 * y * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 4) + 0.0f;
const float dx31 =
    +-0.0038435 + -2.69107e-06 * dx + 0.0890976 * lens_ipow(dy, 2) + 0.029127 * lens_ipow(dx, 2) + 0.00239822 * y * dy +
    1.17953e-05 * lens_ipow(y, 2) + 0.000802082 * x * dx + -1.61459e-08 * x * y + 3.97282e-06 * lens_ipow(x, 2) +
    0.000328168 * lens_ipow(dx, 2) * dy + -8.40558e-08 * lens_ipow(x, 2) * dy + -1.98338e-09 * lens_ipow(x, 2) * y +
    -3.98705e-10 * lens_ipow(x, 3) + -0.00415324 * lens_ipow(lambda, 4) +
    -4.98463e-09 * lens_ipow(x, 2) * lens_ipow(y, 2) + -0.000145189 * x * y * lens_ipow(dx, 3) * dy +
    -3.99524e-06 * x * lens_ipow(y, 2) * dx * lens_ipow(dy, 2) +
    -4.72269e-07 * lens_ipow(x, 2) * y * dy * lens_ipow(lambda, 2) +
    6.73747e-08 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(dx, 2) +
    1.03762e-08 * lens_ipow(x, 4) * lens_ipow(dy, 2) + -1.58794e-12 * lens_ipow(x, 6) +
    -0.000107297 * x * dx * lens_ipow(lambda, 5) + -0.163558 * lens_ipow(dy, 4) * lens_ipow(lambda, 4) +
    -1.79915e-06 * lens_ipow(y, 3) * dy * lens_ipow(lambda, 4) + -5.97185e-14 * lens_ipow(y, 8) * lambda +
    0.0198088 * lens_ipow(lambda, 10) + 0.0881476 * x * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 4) + 0.0f;
const float dx32 =
    +-2.69107e-06 * y + -4.26523e-06 * x + 3.5231 * dx * dy + 0.0582539 * y * dx + 0.0593271 * x * dy +
    0.000802082 * x * y + 0.000656337 * y * dx * dy + -0.000217784 * x * lens_ipow(y, 2) * lens_ipow(dx, 2) * dy +
    -1.33175e-06 * x * lens_ipow(y, 3) * lens_ipow(dy, 2) + 4.49165e-08 * lens_ipow(x, 2) * lens_ipow(y, 3) * dx +
    -0.000107297 * x * y * lens_ipow(lambda, 5) + -0.530082 * x * lens_ipow(dx, 2) * dy * lens_ipow(lambda, 5) +
    0.0881476 * x * y * lens_ipow(dy, 4) * lens_ipow(lambda, 4) + 0.0f;
const float dx33 =
    +0.717854 + -4.87364e-06 * x + 5.36232 * lens_ipow(dy, 2) + 1.76155 * lens_ipow(dx, 2) + 0.178195 * y * dy +
    0.00119911 * lens_ipow(y, 2) + 0.0593271 * x * dx + 0.000391147 * lens_ipow(x, 2) +
    -0.295031 * lens_ipow(lambda, 3) + 0.000328168 * y * lens_ipow(dx, 2) + -8.40558e-08 * lens_ipow(x, 2) * y +
    -7.25946e-05 * x * lens_ipow(y, 2) * lens_ipow(dx, 3) + -2.66349e-06 * x * lens_ipow(y, 3) * dx * dy +
    -2.36134e-07 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(lambda, 2) + 2.07524e-08 * lens_ipow(x, 4) * y * dy +
    -0.654232 * y * lens_ipow(dy, 3) * lens_ipow(lambda, 4) + -4.49788e-07 * lens_ipow(y, 4) * lens_ipow(lambda, 4) +
    -2043.87 * lens_ipow(dy, 8) * lambda + -0.176694 * x * lens_ipow(dx, 3) * lens_ipow(lambda, 5) +
    1.56342 * lens_ipow(lambda, 10) + 0.35259 * x * y * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 4) + 0.0f;
const float dx34 = +-0.885092 * dy * lens_ipow(lambda, 2) + -0.016613 * y * lens_ipow(lambda, 3) +
                   -4.72269e-07 * lens_ipow(x, 2) * lens_ipow(y, 2) * dy * lambda +
                   -0.000536487 * x * y * dx * lens_ipow(lambda, 4) +
                   -0.654232 * y * lens_ipow(dy, 4) * lens_ipow(lambda, 3) +
                   -1.79915e-06 * lens_ipow(y, 4) * dy * lens_ipow(lambda, 3) + -227.097 * lens_ipow(dy, 9) +
                   -6.63539e-15 * lens_ipow(y, 9) + -0.88347 * x * lens_ipow(dx, 3) * dy * lens_ipow(lambda, 4) +
                   15.6342 * dy * lens_ipow(lambda, 9) + 0.198088 * y * lens_ipow(lambda, 9) +
                   0.35259 * x * y * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 3) + 0.0f;
const float dx40 = +-2.06011e-07 + -0.00045066 * dx + -1.11533e-05 * x + -0.0822769 * dx * lens_ipow(dy, 2) +
                   -0.0785551 * lens_ipow(dx, 3) + -0.00214266 * y * dx * dy + -1.13314e-05 * lens_ipow(y, 2) * dx +
                   -0.00113888 * x * lens_ipow(dy, 2) + -0.00337822 * x * lens_ipow(dx, 2) + -2.78854e-05 * x * y * dy +
                   -1.62267e-07 * x * lens_ipow(y, 2) + -4.32834e-05 * lens_ipow(x, 2) * dx +
                   -1.28789e-05 * lens_ipow(x, 2) * dx * lens_ipow(dy, 2) + -6.06305e-10 * lens_ipow(x, 5) +
                   0.00681225 * y * dx * lens_ipow(dy, 5) + 2.59784e-07 * lens_ipow(x, 3) * y * lens_ipow(dx, 2) * dy +
                   -5.6167e-10 * lens_ipow(x, 5) * lens_ipow(dy, 2) +
                   -9.93957e-10 * lens_ipow(y, 6) * lens_ipow(dx, 3) + 0.0f;
const float dx41 = +2.28371e-07 + -0.000335579 * dy + -1.62483e-05 * y + -0.0811809 * lens_ipow(dy, 3) +
                   -0.0737223 * lens_ipow(dx, 2) * dy + -0.00331871 * y * lens_ipow(dy, 2) +
                   -4.21224e-05 * lens_ipow(y, 2) * dy + -0.00214266 * x * dx * dy + -2.26627e-05 * x * y * dx +
                   -1.39427e-05 * lens_ipow(x, 2) * dy + -1.62267e-07 * lens_ipow(x, 2) * y +
                   -0.0574309 * lens_ipow(dx, 4) * dy + -7.15612e-06 * lens_ipow(y, 3) * lens_ipow(dx, 2) +
                   -4.09404e-10 * lens_ipow(y, 5) + 0.00681225 * x * dx * lens_ipow(dy, 5) +
                   6.4946e-08 * lens_ipow(x, 4) * lens_ipow(dx, 2) * dy + -1.62335 * y * lens_ipow(dx, 8) +
                   -5.96374e-09 * x * lens_ipow(y, 5) * lens_ipow(dx, 3) + 0.0f;
const float dx42 =
    +-8.97003e-06 + -0.155534 * dx + -0.00045066 * x + -4.72711 * dx * lens_ipow(dy, 2) + -0.147445 * y * dx * dy +
    -0.0822769 * x * lens_ipow(dy, 2) + -0.235665 * x * lens_ipow(dx, 2) + -0.00214266 * x * y * dy +
    -1.13314e-05 * x * lens_ipow(y, 2) + -0.00337822 * lens_ipow(x, 2) * dx + -1.44278e-05 * lens_ipow(x, 3) +
    -56.7817 * lens_ipow(dx, 5) + -0.229723 * y * lens_ipow(dx, 3) * dy + -3.57806e-06 * lens_ipow(y, 4) * dx +
    -4.29296e-06 * lens_ipow(x, 3) * lens_ipow(dy, 2) + -641.192 * lens_ipow(dx, 5) * lens_ipow(dy, 2) +
    0.00681225 * x * y * lens_ipow(dy, 5) + 1.29892e-07 * lens_ipow(x, 4) * y * dx * dy +
    -6.4934 * lens_ipow(y, 2) * lens_ipow(dx, 7) + -2.98187e-09 * x * lens_ipow(y, 6) * lens_ipow(dx, 2) + 0.0f;
const float dx43 = +-0.115028 * dy + -0.000335579 * y + -4.72711 * lens_ipow(dx, 2) * dy +
                   -0.243543 * y * lens_ipow(dy, 2) + -0.0737223 * y * lens_ipow(dx, 2) +
                   -0.00331871 * lens_ipow(y, 2) * dy + -1.40408e-05 * lens_ipow(y, 3) + -0.164554 * x * dx * dy +
                   -0.00214266 * x * y * dx + -0.00113888 * lens_ipow(x, 2) * dy + -1.39427e-05 * lens_ipow(x, 2) * y +
                   -87.4488 * lens_ipow(dy, 5) + -0.0574309 * y * lens_ipow(dx, 4) +
                   -8.58593e-06 * lens_ipow(x, 3) * dx * dy + -213.731 * lens_ipow(dx, 6) * dy +
                   0.0340613 * x * y * dx * lens_ipow(dy, 4) + 6.4946e-08 * lens_ipow(x, 4) * y * lens_ipow(dx, 2) +
                   -1.87223e-10 * lens_ipow(x, 6) * dy + 0.0f;
const float dx44 = +0.241961 + -0.605708 * lens_ipow(lambda, 2) + 4.00265 * lens_ipow(lambda, 10) + 0.0f;
