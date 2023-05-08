const float out_x =
    +0.000135404 + 102.533 * dx + -6.98437e-06 * y + 0.852921 * x + -0.000167247 * y * dx + 0.000124527 * x * dx +
    -2.71154e-06 * x * y + 93.3834 * dx * lens_ipow(dy, 2) + 93.9527 * lens_ipow(dx, 3) + 2.77587 * y * dx * dy +
    0.0140524 * lens_ipow(y, 2) * dx + 1.30552 * x * lens_ipow(dy, 2) + 4.19041 * x * lens_ipow(dx, 2) +
    0.0274398 * x * y * dy + 3.07262e-05 * x * lens_ipow(y, 2) + 0.0423831 * lens_ipow(x, 2) * dx +
    3.40673e-05 * lens_ipow(x, 3) + -0.0148531 * x * lens_ipow(lambda, 3) + -0.6378 * dx * lens_ipow(lambda, 4) +
    0.000421551 * x * lens_ipow(y, 2) * lens_ipow(dy, 2) + 0.000503246 * lens_ipow(x, 2) * y * dx * dy +
    0.000148147 * lens_ipow(x, 3) * lens_ipow(dy, 2) + 2.40487e-06 * lens_ipow(x, 3) * y * dy +
    -5.91978 * x * lens_ipow(dx, 2) * lens_ipow(dy, 2) * lambda +
    -0.00269224 * lens_ipow(x, 2) * dx * lens_ipow(lambda, 3) + -3385.02 * lens_ipow(dx, 5) * lens_ipow(dy, 2) +
    0.634207 * lens_ipow(y, 2) * lens_ipow(dx, 3) * lens_ipow(dy, 2) + -14.25 * x * lens_ipow(dy, 6) +
    -9.02734 * x * lens_ipow(dx, 4) * lens_ipow(lambda, 2) + 5.06585e-09 * x * lens_ipow(y, 5) * dy +
    7.75464e-07 * lens_ipow(x, 5) * lens_ipow(dx, 2) + -40423.4 * lens_ipow(dx, 3) * lens_ipow(dy, 6) +
    0.760605 * x * y * lens_ipow(dx, 4) * dy * lens_ipow(lambda, 2) +
    1.50009e-09 * lens_ipow(x, 5) * lens_ipow(y, 2) * lens_ipow(dx, 2) +
    -6.29747e-13 * lens_ipow(x, 5) * lens_ipow(y, 4) + -1.51622e-13 * lens_ipow(x, 9) +
    -9863.71 * lens_ipow(dx, 7) * lens_ipow(lambda, 4) + -7.32537e-14 * lens_ipow(x, 2) * lens_ipow(y, 8) * dx +
    7.85724e-05 * lens_ipow(x, 3) * lens_ipow(lambda, 8) +
    1.99145e-07 * lens_ipow(x, 3) * lens_ipow(y, 2) * lens_ipow(lambda, 6);
const float out_y =
    +5.49149e-06 + 102.517 * dy + 0.853298 * y + -0.000190277 * y * dy + -2.89618e-06 * lens_ipow(y, 2) +
    94.8049 * lens_ipow(dy, 3) + 95.0505 * lens_ipow(dx, 2) * dy + 4.14295 * y * lens_ipow(dy, 2) +
    1.32585 * y * lens_ipow(dx, 2) + 0.0420256 * lens_ipow(y, 2) * dy + 3.41119e-05 * lens_ipow(y, 3) +
    2.799 * x * dx * dy + 0.0277656 * x * y * dx + 0.014278 * lens_ipow(x, 2) * dy + 3.06987e-05 * lens_ipow(x, 2) * y +
    -0.0174172 * y * lens_ipow(lambda, 3) + -0.786573 * dy * lens_ipow(lambda, 4) +
    0.000499806 * x * lens_ipow(y, 2) * dx * dy + 0.000103374 * lens_ipow(x, 2) * y * lens_ipow(dy, 2) +
    -1290.56 * lens_ipow(dx, 6) * dy + 0.386246 * lens_ipow(y, 2) * lens_ipow(dx, 2) * lens_ipow(dy, 3) +
    1.11921e-06 * lens_ipow(y, 5) * lens_ipow(dy, 2) + -0.00518931 * lens_ipow(x, 3) * lens_ipow(dx, 3) * dy +
    1.8857e-06 * lens_ipow(x, 4) * y * lens_ipow(dx, 2) + -6.00427 * y * lens_ipow(dy, 4) * lens_ipow(lambda, 3) +
    -138.659 * y * lens_ipow(dx, 4) * lens_ipow(dy, 2) * lens_ipow(lambda, 2) + -178.461 * y * lens_ipow(dx, 8) +
    -0.0702456 * lens_ipow(y, 3) * lens_ipow(dy, 6) + -1.49786e-13 * lens_ipow(y, 9) +
    2.60457 * x * y * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 2) +
    -1.38782e-07 * x * lens_ipow(y, 5) * dx * lens_ipow(dy, 2) +
    5.40946e-05 * lens_ipow(x, 2) * y * lens_ipow(lambda, 6) +
    -3.46082e-09 * lens_ipow(x, 2) * lens_ipow(y, 4) * lens_ipow(dx, 2) * dy +
    -6.8529e-13 * lens_ipow(x, 4) * lens_ipow(y, 5) + 4.39957e-11 * lens_ipow(x, 7) * y * dx +
    -9.55573e-12 * lens_ipow(x, 8) * dy + -16582.9 * lens_ipow(dx, 2) * lens_ipow(dy, 5) * lens_ipow(lambda, 3) +
    -48491.5 * lens_ipow(dy, 9) * lens_ipow(lambda, 2) + 0.000152732 * lens_ipow(y, 3) * lens_ipow(lambda, 8) +
    -7.96763e-11 * lens_ipow(x, 4) * lens_ipow(y, 4) * dy * lens_ipow(lambda, 2);
const float out_dx =
    +8.37575e-06 + 0.709292 * dx + -8.29286e-07 * y + -0.00384714 * x + -0.000739628 * dx * dy +
    -0.000517432 * lens_ipow(dx, 2) + -1.72183e-05 * y * dx + -2.01831e-07 * x * y + 1.76725 * dx * lens_ipow(dy, 2) +
    1.75987 * lens_ipow(dx, 3) + 0.0595432 * y * dx * dy + 0.000393618 * lens_ipow(y, 2) * dx +
    0.0291522 * x * lens_ipow(dy, 2) + 0.0885705 * x * lens_ipow(dx, 2) + 0.000799802 * x * y * dy +
    -6.90312e-07 * x * y * dx + 3.95807e-06 * x * lens_ipow(y, 2) + 0.00119166 * lens_ipow(x, 2) * dx +
    3.90356e-06 * lens_ipow(x, 3) + 0.00086089 * y * lens_ipow(dx, 2) * dy + 1.531e-05 * x * y * dx * dy +
    -5.68659e-10 * lens_ipow(x, 2) * lens_ipow(y, 2) + -5.7437e-08 * lens_ipow(x, 3) * dy +
    -0.448288 * dx * lens_ipow(lambda, 4) + -0.00405009 * x * lens_ipow(lambda, 4) +
    0.000233736 * x * y * lens_ipow(dx, 2) * dy + 3.07865e-06 * x * lens_ipow(y, 2) * lens_ipow(dy, 2) +
    -1.47688e-09 * lens_ipow(x, 3) * lens_ipow(y, 2) +
    0.00805082 * lens_ipow(y, 2) * lens_ipow(dx, 3) * lens_ipow(dy, 2) + -1.28989e-12 * x * lens_ipow(y, 6) +
    2.44198e-08 * lens_ipow(x, 3) * lens_ipow(y, 2) * lens_ipow(dx, 2) +
    -1.29917e-07 * lens_ipow(y, 4) * dx * lens_ipow(lambda, 3) +
    -3.25769e-06 * lens_ipow(x, 2) * lens_ipow(y, 2) * dx * lens_ipow(dy, 2) * lambda +
    -2.44649e-07 * lens_ipow(x, 3) * y * dy * lens_ipow(lambda, 4) +
    -3.6936e-07 * lens_ipow(x, 4) * dx * lens_ipow(lambda, 4) + -3.69529e-15 * lens_ipow(x, 9) +
    -0.245492 * y * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 5) +
    -0.190532 * x * lens_ipow(dx, 4) * lens_ipow(lambda, 5) + 2.1333 * dx * lens_ipow(lambda, 10) +
    0.0191836 * x * lens_ipow(lambda, 10);
const float out_dy =
    +2.39491e-06 + 0.717854 * dy + -0.0038435 * y + 5.61584e-07 * x + -2.69107e-06 * y * dx + -4.87364e-06 * x * dy +
    -4.26523e-06 * x * dx + 1.78744 * lens_ipow(dy, 3) + 1.76155 * lens_ipow(dx, 2) * dy +
    0.0890976 * y * lens_ipow(dy, 2) + 0.029127 * y * lens_ipow(dx, 2) + 0.00119911 * lens_ipow(y, 2) * dy +
    3.93176e-06 * lens_ipow(y, 3) + 0.0593271 * x * dx * dy + 0.000802082 * x * y * dx +
    -8.07297e-09 * x * lens_ipow(y, 2) + 0.000391147 * lens_ipow(x, 2) * dy + 3.97282e-06 * lens_ipow(x, 2) * y +
    -0.295031 * dy * lens_ipow(lambda, 3) + 0.000328168 * y * lens_ipow(dx, 2) * dy +
    -8.40558e-08 * lens_ipow(x, 2) * y * dy + -9.91691e-10 * lens_ipow(x, 2) * lens_ipow(y, 2) +
    -3.98705e-10 * lens_ipow(x, 3) * y + -0.00415324 * y * lens_ipow(lambda, 4) +
    -1.66154e-09 * lens_ipow(x, 2) * lens_ipow(y, 3) + -7.25946e-05 * x * lens_ipow(y, 2) * lens_ipow(dx, 3) * dy +
    -1.33175e-06 * x * lens_ipow(y, 3) * dx * lens_ipow(dy, 2) +
    -2.36134e-07 * lens_ipow(x, 2) * lens_ipow(y, 2) * dy * lens_ipow(lambda, 2) +
    2.24582e-08 * lens_ipow(x, 2) * lens_ipow(y, 3) * lens_ipow(dx, 2) +
    1.03762e-08 * lens_ipow(x, 4) * y * lens_ipow(dy, 2) + -1.58794e-12 * lens_ipow(x, 6) * y +
    -0.000107297 * x * y * dx * lens_ipow(lambda, 5) + -0.163558 * y * lens_ipow(dy, 4) * lens_ipow(lambda, 4) +
    -4.49788e-07 * lens_ipow(y, 4) * dy * lens_ipow(lambda, 4) + -227.097 * lens_ipow(dy, 9) * lambda +
    -6.63539e-15 * lens_ipow(y, 9) * lambda + -0.176694 * x * lens_ipow(dx, 3) * dy * lens_ipow(lambda, 5) +
    1.56342 * dy * lens_ipow(lambda, 10) + 0.0198088 * y * lens_ipow(lambda, 10) +
    0.0881476 * x * y * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 4);
const float out_transmittance =
    +0.493389 + 0.241961 * lambda + -8.97003e-06 * dx + 2.28371e-07 * y + -2.06011e-07 * x +
    -0.0575142 * lens_ipow(dy, 2) + -0.0777672 * lens_ipow(dx, 2) + -0.000335579 * y * dy +
    -8.12413e-06 * lens_ipow(y, 2) + -0.00045066 * x * dx + -5.57666e-06 * lens_ipow(x, 2) +
    -0.201903 * lens_ipow(lambda, 3) + -2.36356 * lens_ipow(dx, 2) * lens_ipow(dy, 2) +
    -0.0811809 * y * lens_ipow(dy, 3) + -0.0737223 * y * lens_ipow(dx, 2) * dy +
    -0.00165936 * lens_ipow(y, 2) * lens_ipow(dy, 2) + -1.40408e-05 * lens_ipow(y, 3) * dy +
    -0.0822769 * x * dx * lens_ipow(dy, 2) + -0.0785551 * x * lens_ipow(dx, 3) + -0.00214266 * x * y * dx * dy +
    -1.13314e-05 * x * lens_ipow(y, 2) * dx + -0.00056944 * lens_ipow(x, 2) * lens_ipow(dy, 2) +
    -0.00168911 * lens_ipow(x, 2) * lens_ipow(dx, 2) + -1.39427e-05 * lens_ipow(x, 2) * y * dy +
    -8.11333e-08 * lens_ipow(x, 2) * lens_ipow(y, 2) + -1.44278e-05 * lens_ipow(x, 3) * dx +
    -14.5748 * lens_ipow(dy, 6) + -9.46362 * lens_ipow(dx, 6) + -0.0574309 * y * lens_ipow(dx, 4) * dy +
    -1.78903e-06 * lens_ipow(y, 4) * lens_ipow(dx, 2) + -6.8234e-11 * lens_ipow(y, 6) +
    -4.29296e-06 * lens_ipow(x, 3) * dx * lens_ipow(dy, 2) + -1.01051e-10 * lens_ipow(x, 6) +
    -106.865 * lens_ipow(dx, 6) * lens_ipow(dy, 2) + 0.00681225 * x * y * dx * lens_ipow(dy, 5) +
    6.4946e-08 * lens_ipow(x, 4) * y * lens_ipow(dx, 2) * dy + -9.36117e-11 * lens_ipow(x, 6) * lens_ipow(dy, 2) +
    -0.811675 * lens_ipow(y, 2) * lens_ipow(dx, 8) + -9.93957e-10 * x * lens_ipow(y, 6) * lens_ipow(dx, 3) +
    0.363877 * lens_ipow(lambda, 11);
