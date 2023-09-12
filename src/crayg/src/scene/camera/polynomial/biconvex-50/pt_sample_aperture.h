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
    pred_x = +49.6894 * begin_dx + 0.895043 * begin_x + 8.56386 * begin_dx * lens_ipow(begin_dy, 2) +
             0.473012 * begin_y * begin_dx * begin_dy + 0.00420829 * lens_ipow(begin_y, 2) * begin_dx +
             0.178553 * begin_x * lens_ipow(begin_dx, 2) + -2.60061e-05 * begin_x * lens_ipow(begin_y, 2) +
             -4.20088e-05 * lens_ipow(begin_x, 3) + 3.8804 * lens_ipow(begin_dx, 3) * lens_ipow(begin_lambda, 2) +
             6.4618 * lens_ipow(begin_dx, 5) + 0.00727611 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) +
             0.0119543 * begin_x * lens_ipow(begin_lambda, 4) + -0.0407309 * begin_x * lens_ipow(begin_dy, 4) +
             0.000434605 * lens_ipow(begin_x, 2) * begin_y * begin_dx * begin_dy +
             -0.000241293 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 2);
    pred_y = +49.7071 * begin_dy + 0.89527 * begin_y + 8.40158 * lens_ipow(begin_dx, 2) * begin_dy +
             0.165609 * begin_y * lens_ipow(begin_dy, 2) + -3.97145e-05 * lens_ipow(begin_y, 3) +
             0.463878 * begin_x * begin_dx * begin_dy + 0.00402577 * lens_ipow(begin_x, 2) * begin_dy +
             -2.79967e-05 * lens_ipow(begin_x, 2) * begin_y + 6.65385 * lens_ipow(begin_dy, 5) +
             0.0108364 * begin_y * lens_ipow(begin_lambda, 4) + -0.0356258 * begin_y * lens_ipow(begin_dx, 4) +
             -0.000261449 * lens_ipow(begin_y, 3) * lens_ipow(begin_dx, 2) +
             0.000477929 * begin_x * lens_ipow(begin_y, 2) * begin_dx * begin_dy +
             0.00809116 * lens_ipow(begin_x, 2) * lens_ipow(begin_dy, 3) +
             4.06683 * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 3);
    pred_dx = +-1.07266e-05 + -0.0447245 * begin_dx + 3.23967e-06 * begin_y + -0.0208243 * begin_x +
              -0.78039 * begin_dx * lens_ipow(begin_dy, 2) + -1.43581 * lens_ipow(begin_dx, 3) +
              -0.0132514 * begin_y * begin_dx * begin_dy + -0.00027477 * lens_ipow(begin_y, 2) * begin_dx +
              -0.0531856 * begin_x * lens_ipow(begin_dx, 2) + -4.74574e-05 * begin_x * begin_y * begin_dy +
              -7.72987e-06 * begin_x * lens_ipow(begin_y, 2) + -0.0011298 * lens_ipow(begin_x, 2) * begin_dx +
              -1.31644e-05 * lens_ipow(begin_x, 3) + 0.126725 * begin_dx * lens_ipow(begin_lambda, 3) +
              0.00342885 * begin_x * lens_ipow(begin_lambda, 4);
    pred_dy = +1.43924e-05 + -0.0439133 * begin_dy + -0.0208112 * begin_y + -1.44178 * lens_ipow(begin_dy, 3) +
              -0.794887 * lens_ipow(begin_dx, 2) * begin_dy + -0.0531875 * begin_y * lens_ipow(begin_dy, 2) +
              -0.00112906 * lens_ipow(begin_y, 2) * begin_dy + -1.3191e-05 * lens_ipow(begin_y, 3) +
              -0.0114748 * begin_x * begin_dx * begin_dy + -0.000245368 * lens_ipow(begin_x, 2) * begin_dy +
              -6.95919e-06 * lens_ipow(begin_x, 2) * begin_y + 0.128054 * begin_dy * lens_ipow(begin_lambda, 3) +
              0.168296 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 3) +
              0.00346268 * begin_y * lens_ipow(begin_lambda, 4) +
              -1.72979e-07 * begin_x * lens_ipow(begin_y, 3) * lens_ipow(begin_dx, 3);
    float dx1_domega0[2][2];
    dx1_domega0[0][0] = +49.6894 + 8.56386 * lens_ipow(begin_dy, 2) + 0.473012 * begin_y * begin_dy +
                        0.00420829 * lens_ipow(begin_y, 2) + 0.357107 * begin_x * begin_dx +
                        11.6412 * lens_ipow(begin_dx, 2) * lens_ipow(begin_lambda, 2) +
                        32.309 * lens_ipow(begin_dx, 4) + 0.0218283 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) +
                        0.000434605 * lens_ipow(begin_x, 2) * begin_y * begin_dy + 0.0f;
    dx1_domega0[0][1] = +17.1277 * begin_dx * begin_dy + 0.473012 * begin_y * begin_dx +
                        -0.162924 * begin_x * lens_ipow(begin_dy, 3) +
                        0.000434605 * lens_ipow(begin_x, 2) * begin_y * begin_dx +
                        -0.000482586 * lens_ipow(begin_x, 3) * begin_dy + 0.0f;
    dx1_domega0[1][0] = +16.8032 * begin_dx * begin_dy + 0.463878 * begin_x * begin_dy +
                        -0.142503 * begin_y * lens_ipow(begin_dx, 3) + -0.000522899 * lens_ipow(begin_y, 3) * begin_dx +
                        0.000477929 * begin_x * lens_ipow(begin_y, 2) * begin_dy + 0.0f;
    dx1_domega0[1][1] = +49.7071 + 8.40158 * lens_ipow(begin_dx, 2) + 0.331217 * begin_y * begin_dy +
                        0.463878 * begin_x * begin_dx + 0.00402577 * lens_ipow(begin_x, 2) +
                        33.2692 * lens_ipow(begin_dy, 4) + 0.000477929 * begin_x * lens_ipow(begin_y, 2) * begin_dx +
                        0.0242735 * lens_ipow(begin_x, 2) * lens_ipow(begin_dy, 2) +
                        12.2005 * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 3) + 0.0f;
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
