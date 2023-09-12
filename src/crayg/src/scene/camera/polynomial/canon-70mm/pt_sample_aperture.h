float pred_x;
float pred_y;
float pred_dx;
float pred_dy;
float sqr_err = FLT_MAX;
for (int k = 0; k < 5 && sqr_err > 1e-4f; k++) {
    const float begin_x = x + dist * dx;
    const float begin_y = y + dist * dy;
    const float begin_dx = dx;
    const float begin_dy = dy;
    const float begin_lambda = lambda;
    pred_x = +102.467 * begin_dx + 0.852655 * begin_x + 94.5096 * begin_dx * lens_ipow(begin_dy, 2) +
             94.7143 * lens_ipow(begin_dx, 3) + 2.78969 * begin_y * begin_dx * begin_dy +
             0.0139346 * lens_ipow(begin_y, 2) * begin_dx + 1.2798 * begin_x * lens_ipow(begin_dy, 2) +
             4.10316 * begin_x * lens_ipow(begin_dx, 2) + 0.0266678 * begin_x * begin_y * begin_dy +
             2.81286e-05 * begin_x * lens_ipow(begin_y, 2) + 0.0412151 * lens_ipow(begin_x, 2) * begin_dx +
             2.92058e-05 * lens_ipow(begin_x, 3) + -0.00835731 * begin_x * lens_ipow(begin_lambda, 3) +
             0.000196603 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 2) +
             2.94055e-06 * lens_ipow(begin_x, 3) * begin_y * begin_dy;
    pred_y = +-0.000174628 + 102.533 * begin_dy + 0.853148 * begin_y + 94.7853 * lens_ipow(begin_dy, 3) +
             94.3186 * lens_ipow(begin_dx, 2) * begin_dy + 4.1052 * begin_y * lens_ipow(begin_dy, 2) +
             1.31295 * begin_y * lens_ipow(begin_dx, 2) + 0.041232 * lens_ipow(begin_y, 2) * begin_dy +
             3.01237e-05 * lens_ipow(begin_y, 3) + 2.78718 * begin_x * begin_dx * begin_dy +
             0.02717 * begin_x * begin_y * begin_dx + 0.0139147 * lens_ipow(begin_x, 2) * begin_dy +
             2.77991e-05 * lens_ipow(begin_x, 2) * begin_y + -0.0117117 * begin_y * lens_ipow(begin_lambda, 3) +
             -0.607626 * begin_dy * lens_ipow(begin_lambda, 4);
    pred_dx = +0.708337 * begin_dx + -0.00359556 * begin_x + 1.14375 * begin_dx * lens_ipow(begin_dy, 2) +
              1.58949 * lens_ipow(begin_dx, 3) + 0.0448383 * begin_y * begin_dx * begin_dy +
              0.000271905 * lens_ipow(begin_y, 2) * begin_dx + 0.0212368 * begin_x * lens_ipow(begin_dy, 2) +
              0.0827453 * begin_x * lens_ipow(begin_dx, 2) + 0.000595757 * begin_x * begin_y * begin_dy +
              0.00111599 * lens_ipow(begin_x, 2) * begin_dx + 2.44064e-06 * lens_ipow(begin_x, 3) +
              -0.20643 * begin_dx * lens_ipow(begin_lambda, 4) + -0.00184705 * begin_x * lens_ipow(begin_lambda, 4) +
              1.31555e-06 * begin_x * begin_y * lens_ipow(begin_dx, 2) * begin_dy +
              1.10687e-08 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 2);
    pred_dy = +0.704065 * begin_dy + -0.00394979 * begin_y + 1.80193 * lens_ipow(begin_dy, 3) +
              1.78184 * lens_ipow(begin_dx, 2) * begin_dy + 0.0887928 * begin_y * lens_ipow(begin_dy, 2) +
              0.029351 * begin_y * lens_ipow(begin_dx, 2) + 0.00118281 * lens_ipow(begin_y, 2) * begin_dy +
              3.80181e-06 * lens_ipow(begin_y, 3) + 0.0589025 * begin_x * begin_dx * begin_dy +
              0.000791992 * begin_x * begin_y * begin_dx + 0.000381524 * lens_ipow(begin_x, 2) * begin_dy +
              3.76906e-06 * lens_ipow(begin_x, 2) * begin_y + -0.162087 * begin_dy * lens_ipow(begin_lambda, 3) +
              -0.00187709 * begin_y * lens_ipow(begin_lambda, 4) +
              -6.22445e-10 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 3);
    float dx1_domega0[2][2];
    dx1_domega0[0][0] = +102.467 + 94.5096 * lens_ipow(begin_dy, 2) + 284.143 * lens_ipow(begin_dx, 2) +
                        2.78969 * begin_y * begin_dy + 0.0139346 * lens_ipow(begin_y, 2) +
                        8.20632 * begin_x * begin_dx + 0.0412151 * lens_ipow(begin_x, 2) + 0.0f;
    dx1_domega0[0][1] = +189.019 * begin_dx * begin_dy + 2.78969 * begin_y * begin_dx + 2.5596 * begin_x * begin_dy +
                        0.0266678 * begin_x * begin_y + 0.000393206 * lens_ipow(begin_x, 3) * begin_dy +
                        2.94055e-06 * lens_ipow(begin_x, 3) * begin_y + 0.0f;
    dx1_domega0[1][0] = +188.637 * begin_dx * begin_dy + 2.6259 * begin_y * begin_dx + 2.78718 * begin_x * begin_dy +
                        0.02717 * begin_x * begin_y + 0.0f;
    dx1_domega0[1][1] = +102.533 + 284.356 * lens_ipow(begin_dy, 2) + 94.3186 * lens_ipow(begin_dx, 2) +
                        8.2104 * begin_y * begin_dy + 0.041232 * lens_ipow(begin_y, 2) + 2.78718 * begin_x * begin_dx +
                        0.0139147 * lens_ipow(begin_x, 2) + -0.607626 * lens_ipow(begin_lambda, 4) + 0.0f;
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
