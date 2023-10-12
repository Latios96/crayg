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
    pred_x = +28.7256 * begin_dx + 0.221514 * begin_x + -15.1286 * begin_dx * lens_ipow(begin_dy, 2) +
             -15.103 * lens_ipow(begin_dx, 3) + -0.0734388 * begin_y * begin_dx * begin_dy +
             -0.0773746 * begin_x * lens_ipow(begin_dy, 2) + -0.131944 * begin_x * lens_ipow(begin_dx, 2) +
             0.00270523 * begin_x * begin_y * begin_dy + -0.00043966 * lens_ipow(begin_x, 3) +
             0.0834472 * begin_x * lens_ipow(begin_lambda, 3) + 2.30494 * begin_dx * lens_ipow(begin_lambda, 4) +
             -0.00102373 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) +
             -1.58691e-06 * begin_x * lens_ipow(begin_y, 4) +
             -2.23514e-06 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 2) +
             7.9889e-08 * lens_ipow(begin_x, 6) * begin_dx;
    pred_y = +28.5221 * begin_dy + 0.197862 * begin_y + -14.656 * lens_ipow(begin_dy, 3) +
             -14.2193 * lens_ipow(begin_dx, 2) * begin_dy + -0.107517 * begin_y * lens_ipow(begin_dy, 2) +
             -0.0755957 * begin_y * lens_ipow(begin_dx, 2) + 0.00428518 * lens_ipow(begin_y, 2) * begin_dy +
             0.00233892 * begin_x * begin_y * begin_dx + 0.00167777 * lens_ipow(begin_x, 2) * begin_dy +
             0.0837174 * begin_y * lens_ipow(begin_lambda, 3) + 2.30932 * begin_dy * lens_ipow(begin_lambda, 4) +
             -1.45325e-06 * lens_ipow(begin_y, 5) + 0.029529 * begin_x * begin_y * begin_dx * lens_ipow(begin_dy, 2) +
             -2.76836e-06 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 3) +
             -1.41127e-06 * lens_ipow(begin_x, 4) * begin_y;
    pred_dx = +0.389626 * begin_dx + -0.0309208 * begin_x + -0.488906 * begin_dx * lens_ipow(begin_dy, 2) +
              -0.484043 * lens_ipow(begin_dx, 3) + -0.021755 * begin_y * begin_dx * begin_dy +
              0.000102066 * lens_ipow(begin_y, 2) * begin_dx + -0.0115242 * begin_x * lens_ipow(begin_dy, 2) +
              -0.0340224 * begin_x * lens_ipow(begin_dx, 2) + 0.000382964 * begin_x * begin_y * begin_dy +
              -2.54761e-05 * begin_x * lens_ipow(begin_y, 2) + 0.000459736 * lens_ipow(begin_x, 2) * begin_dx +
              -3.30396e-05 * lens_ipow(begin_x, 3) + 0.00483934 * begin_x * lens_ipow(begin_lambda, 3) +
              -1.86096e-10 * begin_x * lens_ipow(begin_y, 6) +
              -4.58538e-10 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 2);
    pred_dy = +0.389275 * begin_dy + -0.0310328 * begin_y + -0.484466 * lens_ipow(begin_dy, 3) +
              -0.480634 * lens_ipow(begin_dx, 2) * begin_dy + -0.0339828 * begin_y * lens_ipow(begin_dy, 2) +
              -0.0114333 * begin_y * lens_ipow(begin_dx, 2) + 0.000459221 * lens_ipow(begin_y, 2) * begin_dy +
              -3.23005e-05 * lens_ipow(begin_y, 3) + -0.0215647 * begin_x * begin_dx * begin_dy +
              0.000386583 * begin_x * begin_y * begin_dx + 0.000106723 * lens_ipow(begin_x, 2) * begin_dy +
              -2.49652e-05 * lens_ipow(begin_x, 2) * begin_y + 0.00498791 * begin_y * lens_ipow(begin_lambda, 3) +
              -5.07116e-10 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 5) +
              -1.81027e-10 * lens_ipow(begin_x, 6) * begin_y;
    float dx1_domega0[2][2];
    dx1_domega0[0][0] =
        +28.7256 + -15.1286 * lens_ipow(begin_dy, 2) + -45.309 * lens_ipow(begin_dx, 2) +
        -0.0734388 * begin_y * begin_dy + -0.263888 * begin_x * begin_dx + 2.30494 * lens_ipow(begin_lambda, 4) +
        -0.00204746 * begin_x * lens_ipow(begin_y, 2) * begin_dx + 7.9889e-08 * lens_ipow(begin_x, 6) + 0.0f;
    dx1_domega0[0][1] = +-30.2572 * begin_dx * begin_dy + -0.0734388 * begin_y * begin_dx +
                        -0.154749 * begin_x * begin_dy + 0.00270523 * begin_x * begin_y + 0.0f;
    dx1_domega0[1][0] = +-28.4385 * begin_dx * begin_dy + -0.151191 * begin_y * begin_dx +
                        0.00233892 * begin_x * begin_y + 0.029529 * begin_x * begin_y * lens_ipow(begin_dy, 2) + 0.0f;
    dx1_domega0[1][1] = +28.5221 + -43.9681 * lens_ipow(begin_dy, 2) + -14.2193 * lens_ipow(begin_dx, 2) +
                        -0.215034 * begin_y * begin_dy + 0.00428518 * lens_ipow(begin_y, 2) +
                        0.00167777 * lens_ipow(begin_x, 2) + 2.30932 * lens_ipow(begin_lambda, 4) +
                        0.059058 * begin_x * begin_y * begin_dx * begin_dy + 0.0f;
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
