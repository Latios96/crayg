float pred_x;
float pred_y;
float pred_dx;
float pred_dy;
float sqr_err = std::numeric_limits<float>::max();
for (int k = 0; k < 5 && sqr_err > 1e-4f; k++) {
    const float begin_x = x + dist * dx;
    const float begin_y = y + dist * dy;
    const float begin_dx = dx;
    const float begin_dy = dy;
    /*__attribute__((unused))*/ const float begin_lambda = lambda;
    pred_x = +0.000135404 + 102.533 * begin_dx + -6.98437e-06 * begin_y + 0.852921 * begin_x +
             -0.000167247 * begin_y * begin_dx + 0.000124527 * begin_x * begin_dx + -2.71154e-06 * begin_x * begin_y +
             93.3834 * begin_dx * lens_ipow(begin_dy, 2) + 93.9527 * lens_ipow(begin_dx, 3) +
             2.77587 * begin_y * begin_dx * begin_dy + 0.0140524 * lens_ipow(begin_y, 2) * begin_dx +
             1.30552 * begin_x * lens_ipow(begin_dy, 2) + 4.19041 * begin_x * lens_ipow(begin_dx, 2) +
             0.0274398 * begin_x * begin_y * begin_dy + 3.07262e-05 * begin_x * lens_ipow(begin_y, 2) +
             0.0423831 * lens_ipow(begin_x, 2) * begin_dx + 3.40673e-05 * lens_ipow(begin_x, 3) +
             -0.0148531 * begin_x * lens_ipow(begin_lambda, 3) + -0.6378 * begin_dx * lens_ipow(begin_lambda, 4) +
             0.000421551 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dy, 2) +
             0.000503246 * lens_ipow(begin_x, 2) * begin_y * begin_dx * begin_dy +
             0.000148147 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 2) +
             2.40487e-06 * lens_ipow(begin_x, 3) * begin_y * begin_dy +
             -5.91978 * begin_x * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 2) * begin_lambda +
             -0.00269224 * lens_ipow(begin_x, 2) * begin_dx * lens_ipow(begin_lambda, 3) +
             -3385.02 * lens_ipow(begin_dx, 5) * lens_ipow(begin_dy, 2) +
             0.634207 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 2) +
             -14.25 * begin_x * lens_ipow(begin_dy, 6) +
             -9.02734 * begin_x * lens_ipow(begin_dx, 4) * lens_ipow(begin_lambda, 2) +
             5.06585e-09 * begin_x * lens_ipow(begin_y, 5) * begin_dy +
             7.75464e-07 * lens_ipow(begin_x, 5) * lens_ipow(begin_dx, 2) +
             -40423.4 * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 6) +
             0.760605 * begin_x * begin_y * lens_ipow(begin_dx, 4) * begin_dy * lens_ipow(begin_lambda, 2) +
             1.50009e-09 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) +
             -6.29747e-13 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 4) + -1.51622e-13 * lens_ipow(begin_x, 9) +
             -9863.71 * lens_ipow(begin_dx, 7) * lens_ipow(begin_lambda, 4) +
             -7.32537e-14 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 8) * begin_dx +
             7.85724e-05 * lens_ipow(begin_x, 3) * lens_ipow(begin_lambda, 8) +
             1.99145e-07 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 2) * lens_ipow(begin_lambda, 6);
    pred_y = +5.49149e-06 + 102.517 * begin_dy + 0.853298 * begin_y + -0.000190277 * begin_y * begin_dy +
             -2.89618e-06 * lens_ipow(begin_y, 2) + 94.8049 * lens_ipow(begin_dy, 3) +
             95.0505 * lens_ipow(begin_dx, 2) * begin_dy + 4.14295 * begin_y * lens_ipow(begin_dy, 2) +
             1.32585 * begin_y * lens_ipow(begin_dx, 2) + 0.0420256 * lens_ipow(begin_y, 2) * begin_dy +
             3.41119e-05 * lens_ipow(begin_y, 3) + 2.799 * begin_x * begin_dx * begin_dy +
             0.0277656 * begin_x * begin_y * begin_dx + 0.014278 * lens_ipow(begin_x, 2) * begin_dy +
             3.06987e-05 * lens_ipow(begin_x, 2) * begin_y + -0.0174172 * begin_y * lens_ipow(begin_lambda, 3) +
             -0.786573 * begin_dy * lens_ipow(begin_lambda, 4) +
             0.000499806 * begin_x * lens_ipow(begin_y, 2) * begin_dx * begin_dy +
             0.000103374 * lens_ipow(begin_x, 2) * begin_y * lens_ipow(begin_dy, 2) +
             -1290.56 * lens_ipow(begin_dx, 6) * begin_dy +
             0.386246 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 3) +
             1.11921e-06 * lens_ipow(begin_y, 5) * lens_ipow(begin_dy, 2) +
             -0.00518931 * lens_ipow(begin_x, 3) * lens_ipow(begin_dx, 3) * begin_dy +
             1.8857e-06 * lens_ipow(begin_x, 4) * begin_y * lens_ipow(begin_dx, 2) +
             -6.00427 * begin_y * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 3) +
             -138.659 * begin_y * lens_ipow(begin_dx, 4) * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 2) +
             -178.461 * begin_y * lens_ipow(begin_dx, 8) + -0.0702456 * lens_ipow(begin_y, 3) * lens_ipow(begin_dy, 6) +
             -1.49786e-13 * lens_ipow(begin_y, 9) +
             2.60457 * begin_x * begin_y * begin_dx * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 2) +
             -1.38782e-07 * begin_x * lens_ipow(begin_y, 5) * begin_dx * lens_ipow(begin_dy, 2) +
             5.40946e-05 * lens_ipow(begin_x, 2) * begin_y * lens_ipow(begin_lambda, 6) +
             -3.46082e-09 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 2) * begin_dy +
             -6.8529e-13 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 5) +
             4.39957e-11 * lens_ipow(begin_x, 7) * begin_y * begin_dx +
             -9.55573e-12 * lens_ipow(begin_x, 8) * begin_dy +
             -16582.9 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 5) * lens_ipow(begin_lambda, 3) +
             -48491.5 * lens_ipow(begin_dy, 9) * lens_ipow(begin_lambda, 2) +
             0.000152732 * lens_ipow(begin_y, 3) * lens_ipow(begin_lambda, 8) +
             -7.96763e-11 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 4) * begin_dy * lens_ipow(begin_lambda, 2);
    pred_dx =
        +8.37575e-06 + 0.709292 * begin_dx + -8.29286e-07 * begin_y + -0.00384714 * begin_x +
        -0.000739628 * begin_dx * begin_dy + -0.000517432 * lens_ipow(begin_dx, 2) + -1.72183e-05 * begin_y * begin_dx +
        -2.01831e-07 * begin_x * begin_y + 1.76725 * begin_dx * lens_ipow(begin_dy, 2) +
        1.75987 * lens_ipow(begin_dx, 3) + 0.0595432 * begin_y * begin_dx * begin_dy +
        0.000393618 * lens_ipow(begin_y, 2) * begin_dx + 0.0291522 * begin_x * lens_ipow(begin_dy, 2) +
        0.0885705 * begin_x * lens_ipow(begin_dx, 2) + 0.000799802 * begin_x * begin_y * begin_dy +
        -6.90312e-07 * begin_x * begin_y * begin_dx + 3.95807e-06 * begin_x * lens_ipow(begin_y, 2) +
        0.00119166 * lens_ipow(begin_x, 2) * begin_dx + 3.90356e-06 * lens_ipow(begin_x, 3) +
        0.00086089 * begin_y * lens_ipow(begin_dx, 2) * begin_dy + 1.531e-05 * begin_x * begin_y * begin_dx * begin_dy +
        -5.68659e-10 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) + -5.7437e-08 * lens_ipow(begin_x, 3) * begin_dy +
        -0.448288 * begin_dx * lens_ipow(begin_lambda, 4) + -0.00405009 * begin_x * lens_ipow(begin_lambda, 4) +
        0.000233736 * begin_x * begin_y * lens_ipow(begin_dx, 2) * begin_dy +
        3.07865e-06 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dy, 2) +
        -1.47688e-09 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 2) +
        0.00805082 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 2) +
        -1.28989e-12 * begin_x * lens_ipow(begin_y, 6) +
        2.44198e-08 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) +
        -1.29917e-07 * lens_ipow(begin_y, 4) * begin_dx * lens_ipow(begin_lambda, 3) +
        -3.25769e-06 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) * begin_dx * lens_ipow(begin_dy, 2) *
            begin_lambda +
        -2.44649e-07 * lens_ipow(begin_x, 3) * begin_y * begin_dy * lens_ipow(begin_lambda, 4) +
        -3.6936e-07 * lens_ipow(begin_x, 4) * begin_dx * lens_ipow(begin_lambda, 4) +
        -3.69529e-15 * lens_ipow(begin_x, 9) +
        -0.245492 * begin_y * begin_dx * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 5) +
        -0.190532 * begin_x * lens_ipow(begin_dx, 4) * lens_ipow(begin_lambda, 5) +
        2.1333 * begin_dx * lens_ipow(begin_lambda, 10) + 0.0191836 * begin_x * lens_ipow(begin_lambda, 10);
    pred_dy = +2.39491e-06 + 0.717854 * begin_dy + -0.0038435 * begin_y + 5.61584e-07 * begin_x +
              -2.69107e-06 * begin_y * begin_dx + -4.87364e-06 * begin_x * begin_dy +
              -4.26523e-06 * begin_x * begin_dx + 1.78744 * lens_ipow(begin_dy, 3) +
              1.76155 * lens_ipow(begin_dx, 2) * begin_dy + 0.0890976 * begin_y * lens_ipow(begin_dy, 2) +
              0.029127 * begin_y * lens_ipow(begin_dx, 2) + 0.00119911 * lens_ipow(begin_y, 2) * begin_dy +
              3.93176e-06 * lens_ipow(begin_y, 3) + 0.0593271 * begin_x * begin_dx * begin_dy +
              0.000802082 * begin_x * begin_y * begin_dx + -8.07297e-09 * begin_x * lens_ipow(begin_y, 2) +
              0.000391147 * lens_ipow(begin_x, 2) * begin_dy + 3.97282e-06 * lens_ipow(begin_x, 2) * begin_y +
              -0.295031 * begin_dy * lens_ipow(begin_lambda, 3) +
              0.000328168 * begin_y * lens_ipow(begin_dx, 2) * begin_dy +
              -8.40558e-08 * lens_ipow(begin_x, 2) * begin_y * begin_dy +
              -9.91691e-10 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) +
              -3.98705e-10 * lens_ipow(begin_x, 3) * begin_y + -0.00415324 * begin_y * lens_ipow(begin_lambda, 4) +
              -1.66154e-09 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 3) +
              -7.25946e-05 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) * begin_dy +
              -1.33175e-06 * begin_x * lens_ipow(begin_y, 3) * begin_dx * lens_ipow(begin_dy, 2) +
              -2.36134e-07 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) * begin_dy * lens_ipow(begin_lambda, 2) +
              2.24582e-08 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 3) * lens_ipow(begin_dx, 2) +
              1.03762e-08 * lens_ipow(begin_x, 4) * begin_y * lens_ipow(begin_dy, 2) +
              -1.58794e-12 * lens_ipow(begin_x, 6) * begin_y +
              -0.000107297 * begin_x * begin_y * begin_dx * lens_ipow(begin_lambda, 5) +
              -0.163558 * begin_y * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 4) +
              -4.49788e-07 * lens_ipow(begin_y, 4) * begin_dy * lens_ipow(begin_lambda, 4) +
              -227.097 * lens_ipow(begin_dy, 9) * begin_lambda + -6.63539e-15 * lens_ipow(begin_y, 9) * begin_lambda +
              -0.176694 * begin_x * lens_ipow(begin_dx, 3) * begin_dy * lens_ipow(begin_lambda, 5) +
              1.56342 * begin_dy * lens_ipow(begin_lambda, 10) + 0.0198088 * begin_y * lens_ipow(begin_lambda, 10) +
              0.0881476 * begin_x * begin_y * begin_dx * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 4);
    float dx1_domega0[2][2];
    dx1_domega0[0][0] =
        +102.533 + -0.000167247 * begin_y + 0.000124527 * begin_x + 93.3834 * lens_ipow(begin_dy, 2) +
        281.858 * lens_ipow(begin_dx, 2) + 2.77587 * begin_y * begin_dy + 0.0140524 * lens_ipow(begin_y, 2) +
        8.38082 * begin_x * begin_dx + 0.0423831 * lens_ipow(begin_x, 2) + -0.6378 * lens_ipow(begin_lambda, 4) +
        0.000503246 * lens_ipow(begin_x, 2) * begin_y * begin_dy +
        -11.8396 * begin_x * begin_dx * lens_ipow(begin_dy, 2) * begin_lambda +
        -0.00269224 * lens_ipow(begin_x, 2) * lens_ipow(begin_lambda, 3) +
        -16925.1 * lens_ipow(begin_dx, 4) * lens_ipow(begin_dy, 2) +
        1.90262 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 2) +
        -36.1094 * begin_x * lens_ipow(begin_dx, 3) * lens_ipow(begin_lambda, 2) +
        1.55093e-06 * lens_ipow(begin_x, 5) * begin_dx + -121270 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 6) +
        3.04242 * begin_x * begin_y * lens_ipow(begin_dx, 3) * begin_dy * lens_ipow(begin_lambda, 2) +
        3.00019e-09 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 2) * begin_dx +
        -69045.9 * lens_ipow(begin_dx, 6) * lens_ipow(begin_lambda, 4) +
        -7.32537e-14 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 8) + 0.0f;
    dx1_domega0[0][1] = +186.767 * begin_dx * begin_dy + 2.77587 * begin_y * begin_dx + 2.61103 * begin_x * begin_dy +
                        0.0274398 * begin_x * begin_y + 0.000843102 * begin_x * lens_ipow(begin_y, 2) * begin_dy +
                        0.000503246 * lens_ipow(begin_x, 2) * begin_y * begin_dx +
                        0.000296294 * lens_ipow(begin_x, 3) * begin_dy + 2.40487e-06 * lens_ipow(begin_x, 3) * begin_y +
                        -11.8396 * begin_x * lens_ipow(begin_dx, 2) * begin_dy * begin_lambda +
                        -6770.03 * lens_ipow(begin_dx, 5) * begin_dy +
                        1.26841 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) * begin_dy +
                        -85.4999 * begin_x * lens_ipow(begin_dy, 5) + 5.06585e-09 * begin_x * lens_ipow(begin_y, 5) +
                        -242541 * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 5) +
                        0.760605 * begin_x * begin_y * lens_ipow(begin_dx, 4) * lens_ipow(begin_lambda, 2) + 0.0f;
    dx1_domega0[1][0] =
        +190.101 * begin_dx * begin_dy + 2.65171 * begin_y * begin_dx + 2.799 * begin_x * begin_dy +
        0.0277656 * begin_x * begin_y + 0.000499806 * begin_x * lens_ipow(begin_y, 2) * begin_dy +
        -7743.36 * lens_ipow(begin_dx, 5) * begin_dy +
        0.772492 * lens_ipow(begin_y, 2) * begin_dx * lens_ipow(begin_dy, 3) +
        -0.0155679 * lens_ipow(begin_x, 3) * lens_ipow(begin_dx, 2) * begin_dy +
        3.7714e-06 * lens_ipow(begin_x, 4) * begin_y * begin_dx +
        -554.637 * begin_y * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 2) +
        -1427.69 * begin_y * lens_ipow(begin_dx, 7) +
        2.60457 * begin_x * begin_y * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 2) +
        -1.38782e-07 * begin_x * lens_ipow(begin_y, 5) * lens_ipow(begin_dy, 2) +
        -6.92164e-09 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 4) * begin_dx * begin_dy +
        4.39957e-11 * lens_ipow(begin_x, 7) * begin_y +
        -33165.9 * begin_dx * lens_ipow(begin_dy, 5) * lens_ipow(begin_lambda, 3) + 0.0f;
    dx1_domega0[1][1] =
        +102.517 + -0.000190277 * begin_y + 284.415 * lens_ipow(begin_dy, 2) + 95.0505 * lens_ipow(begin_dx, 2) +
        8.28589 * begin_y * begin_dy + 0.0420256 * lens_ipow(begin_y, 2) + 2.799 * begin_x * begin_dx +
        0.014278 * lens_ipow(begin_x, 2) + -0.786573 * lens_ipow(begin_lambda, 4) +
        0.000499806 * begin_x * lens_ipow(begin_y, 2) * begin_dx +
        0.000206748 * lens_ipow(begin_x, 2) * begin_y * begin_dy + -1290.56 * lens_ipow(begin_dx, 6) +
        1.15874 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 2) +
        2.23843e-06 * lens_ipow(begin_y, 5) * begin_dy + -0.00518931 * lens_ipow(begin_x, 3) * lens_ipow(begin_dx, 3) +
        -24.0171 * begin_y * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 3) +
        -277.319 * begin_y * lens_ipow(begin_dx, 4) * begin_dy * lens_ipow(begin_lambda, 2) +
        -0.421474 * lens_ipow(begin_y, 3) * lens_ipow(begin_dy, 5) +
        10.4183 * begin_x * begin_y * begin_dx * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 2) +
        -2.77565e-07 * begin_x * lens_ipow(begin_y, 5) * begin_dx * begin_dy +
        -3.46082e-09 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 2) +
        -9.55573e-12 * lens_ipow(begin_x, 8) +
        -82914.7 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 3) +
        -436424 * lens_ipow(begin_dy, 8) * lens_ipow(begin_lambda, 2) +
        -7.96763e-11 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 4) * lens_ipow(begin_lambda, 2) + 0.0f;
    float invJ[2][2];
    const float invdet = 1.0f / (dx1_domega0[0][0] * dx1_domega0[1][1] - dx1_domega0[0][1] * dx1_domega0[1][0]);
    invJ[0][0] = dx1_domega0[1][1] * invdet;
    invJ[1][1] = dx1_domega0[0][0] * invdet;
    invJ[0][1] = -dx1_domega0[0][1] * invdet;
    invJ[1][0] = -dx1_domega0[1][0] * invdet;
    const float dx1[2] = {out_x - pred_x, out_y - pred_y};
    for (int i = 0; i < 2; i++) {
        dx += invJ[0][i] * dx1[i];
        dy += invJ[1][i] * dx1[i];
    }
    sqr_err = dx1[0] * dx1[0] + dx1[1] * dx1[1];
}
out_dx = pred_dx;
out_dy = pred_dy;
