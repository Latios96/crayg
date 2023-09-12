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
    pred_x = +-0.00729624 + 22.6897 * begin_dx + 1.26799 * begin_x + -1.18359 * begin_dx * lens_ipow(begin_dy, 2) +
             -0.844977 * lens_ipow(begin_dx, 3) + -0.132427 * begin_y * begin_dx * begin_dy +
             -0.0203777 * lens_ipow(begin_y, 2) * begin_dx + 0.00252336 * begin_x * lens_ipow(begin_y, 2) +
             0.00323653 * lens_ipow(begin_x, 3) +
             -0.000175169 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dy, 2) +
             -0.001536 * lens_ipow(begin_x, 2) * begin_y * begin_dx * begin_dy +
             0.000382944 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 2) +
             -7.17055e-05 * lens_ipow(begin_y, 3) * begin_dx * lens_ipow(begin_dy, 3) +
             2.87441e-05 * begin_x * lens_ipow(begin_y, 3) * lens_ipow(begin_dx, 2) * begin_dy +
             1.72794e-05 * lens_ipow(begin_x, 4) * lens_ipow(begin_dx, 3);
    pred_y = +22.8882 * begin_dy + 1.39876 * begin_y + -0.921188 * lens_ipow(begin_dy, 3) +
             -0.979192 * lens_ipow(begin_dx, 2) * begin_dy + 0.0719054 * begin_y * lens_ipow(begin_dx, 2) +
             -0.00332359 * lens_ipow(begin_y, 2) * begin_dy + 0.0158332 * begin_x * begin_y * begin_dx +
             -0.0144999 * lens_ipow(begin_x, 2) * begin_dy + 1.47434e-05 * lens_ipow(begin_y, 5) +
             0.0115042 * begin_x * begin_y * begin_dx * lens_ipow(begin_dy, 2) +
             -0.00080131 * lens_ipow(begin_x, 2) * lens_ipow(begin_dy, 3) +
             0.00512969 * lens_ipow(begin_x, 2) * lens_ipow(begin_dx, 2) * begin_dy +
             2.52633e-05 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 3) +
             1.59124e-05 * lens_ipow(begin_x, 4) * begin_y +
             2.25647e-05 * lens_ipow(begin_y, 4) * lens_ipow(begin_dy, 3);
    pred_dx =
        +-0.000217131 + 0.465729 * begin_dx + -0.0087797 * begin_x + -0.0542714 * begin_dx * lens_ipow(begin_dy, 2) +
        -0.0563203 * lens_ipow(begin_dx, 3) + 4.12022e-05 * begin_x * lens_ipow(begin_y, 2) +
        3.59583e-05 * lens_ipow(begin_x, 3) + 0.0302448 * begin_dx * lens_ipow(begin_lambda, 3) +
        -9.26452e-06 * lens_ipow(begin_y, 3) * begin_dx * begin_dy +
        7.34074e-06 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 2) +
        0.00171834 * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 4) + -2.69469e-05 * begin_x * lens_ipow(begin_dy, 6) +
        -0.000181179 * begin_x * lens_ipow(begin_dx, 4) * lens_ipow(begin_dy, 2) +
        -9.86389e-05 * begin_x * lens_ipow(begin_dx, 6) +
        -4.21007e-06 * lens_ipow(begin_x, 2) * begin_y * lens_ipow(begin_dx, 3) * begin_dy;
    pred_dy = +0.468543 * begin_dy + -0.00903868 * begin_y + -0.0572403 * lens_ipow(begin_dy, 3) +
              -0.0562668 * lens_ipow(begin_dx, 2) * begin_dy + 3.93044e-05 * lens_ipow(begin_y, 3) +
              -9.32849e-06 * lens_ipow(begin_x, 2) * begin_dy + 3.94987e-05 * lens_ipow(begin_x, 2) * begin_y +
              0.0302217 * begin_dy * lens_ipow(begin_lambda, 3) +
              5.3996e-06 * lens_ipow(begin_y, 3) * lens_ipow(begin_dx, 2) +
              0.0010812 * lens_ipow(begin_dx, 4) * lens_ipow(begin_dy, 3) +
              -0.000101146 * begin_y * lens_ipow(begin_dy, 6) +
              4.06579e-05 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 3) +
              -9.94881e-05 * begin_x * lens_ipow(begin_dx, 5) * begin_dy +
              1.97925e-05 * begin_x * begin_y * begin_dx * lens_ipow(begin_dy, 4) +
              -3.99546e-06 * lens_ipow(begin_x, 3) * begin_dx * lens_ipow(begin_dy, 3);
    float dx1_domega0[2][2];
    dx1_domega0[0][0] = +22.6897 + -1.18359 * lens_ipow(begin_dy, 2) + -2.53493 * lens_ipow(begin_dx, 2) +
                        -0.132427 * begin_y * begin_dy + -0.0203777 * lens_ipow(begin_y, 2) +
                        -0.001536 * lens_ipow(begin_x, 2) * begin_y * begin_dy +
                        -7.17055e-05 * lens_ipow(begin_y, 3) * lens_ipow(begin_dy, 3) +
                        5.74883e-05 * begin_x * lens_ipow(begin_y, 3) * begin_dx * begin_dy +
                        5.18383e-05 * lens_ipow(begin_x, 4) * lens_ipow(begin_dx, 2) + 0.0f;
    dx1_domega0[0][1] = +-2.36718 * begin_dx * begin_dy + -0.132427 * begin_y * begin_dx +
                        -0.000350339 * begin_x * lens_ipow(begin_y, 2) * begin_dy +
                        -0.001536 * lens_ipow(begin_x, 2) * begin_y * begin_dx +
                        0.000765888 * lens_ipow(begin_x, 3) * begin_dy +
                        -0.000215117 * lens_ipow(begin_y, 3) * begin_dx * lens_ipow(begin_dy, 2) +
                        2.87441e-05 * begin_x * lens_ipow(begin_y, 3) * lens_ipow(begin_dx, 2) + 0.0f;
    dx1_domega0[1][0] = +-1.95838 * begin_dx * begin_dy + 0.143811 * begin_y * begin_dx +
                        0.0158332 * begin_x * begin_y + 0.0115042 * begin_x * begin_y * lens_ipow(begin_dy, 2) +
                        0.0102594 * lens_ipow(begin_x, 2) * begin_dx * begin_dy + 0.0f;
    dx1_domega0[1][1] = +22.8882 + -2.76356 * lens_ipow(begin_dy, 2) + -0.979192 * lens_ipow(begin_dx, 2) +
                        -0.00332359 * lens_ipow(begin_y, 2) + -0.0144999 * lens_ipow(begin_x, 2) +
                        0.0230084 * begin_x * begin_y * begin_dx * begin_dy +
                        -0.00240393 * lens_ipow(begin_x, 2) * lens_ipow(begin_dy, 2) +
                        0.00512969 * lens_ipow(begin_x, 2) * lens_ipow(begin_dx, 2) +
                        6.76941e-05 * lens_ipow(begin_y, 4) * lens_ipow(begin_dy, 2) + 0.0f;
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
