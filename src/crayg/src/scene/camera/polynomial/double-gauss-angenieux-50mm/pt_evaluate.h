const float out_x = +-0.0101956 + 21.817 * dx + 1.23905 * x + -1.41886 * dx * lens_ipow(dy, 2) +
                    -1.14917 * lens_ipow(dx, 3) + -0.246188 * y * dx * dy + -0.0224788 * lens_ipow(y, 2) * dx +
                    0.0846106 * x * lens_ipow(dy, 2) + 0.00254238 * x * lens_ipow(y, 2) + 0.00278876 * lens_ipow(x, 3) +
                    0.00317472 * x * y * lens_ipow(dy, 3) + 0.00739961 * x * y * lens_ipow(dx, 2) * dy +
                    -0.000945135 * lens_ipow(x, 3) * lens_ipow(dx, 2) + 3.91708e-05 * lens_ipow(x, 3) * y * dy +
                    4.04422e-08 * lens_ipow(x, 7);
const float out_y = +21.7541 * dy + 1.27805 * y + -1.14128 * lens_ipow(dy, 3) + -1.32295 * lens_ipow(dx, 2) * dy +
                    0.103466 * y * lens_ipow(dx, 2) + 0.00198639 * lens_ipow(y, 3) + -0.224642 * x * dx * dy +
                    -0.0212428 * lens_ipow(x, 2) * dy + 0.00194813 * lens_ipow(x, 2) * y +
                    -0.000938438 * lens_ipow(y, 3) * lens_ipow(dy, 2) + 0.00740129 * x * y * dx * lens_ipow(dy, 2) +
                    0.00337081 * x * y * lens_ipow(dx, 3) + 9.1416e-05 * x * lens_ipow(y, 3) * dx +
                    5.17535e-08 * lens_ipow(y, 7) + 1.61124e-07 * lens_ipow(x, 2) * lens_ipow(y, 5);
const float out_dx =
    +0.184448 * dx + -0.023333 * x + -0.0472156 * dx * lens_ipow(dy, 2) + -0.0483812 * lens_ipow(dx, 3) +
    0.000158695 * lens_ipow(y, 2) * dx + -0.000451094 * x * y * dy + -9.41197e-06 * x * lens_ipow(y, 2) +
    -0.000112629 * lens_ipow(x, 2) * dx + 0.017559 * dx * lens_ipow(lambda, 3) + -0.000228287 * x * lens_ipow(dy, 4) +
    -0.000868077 * x * lens_ipow(dx, 2) * lens_ipow(dy, 2) + 0.00101776 * lens_ipow(dx, 5) * lens_ipow(dy, 2) +
    0.000455778 * lens_ipow(dx, 7) + -9.00973e-05 * y * dx * lens_ipow(dy, 5) +
    1.3889e-05 * lens_ipow(y, 2) * lens_ipow(dx, 3) * lens_ipow(dy, 2);
const float out_dy =
    +0.119091 * dy + -0.0268749 * y + 0.0110949 * y * lens_ipow(dy, 2) + 0.00248404 * y * lens_ipow(dx, 2) +
    0.000835661 * lens_ipow(y, 2) * dy + 0.0102833 * x * dx * dy + 0.000792168 * lens_ipow(x, 2) * dy +
    1.12217e-07 * lens_ipow(y, 5) + 0.00037484 * x * y * dx * lens_ipow(dy, 2) +
    8.26884e-05 * x * y * lens_ipow(dx, 3) + -9.22611e-05 * lens_ipow(x, 2) * lens_ipow(dy, 3) +
    2.48855e-07 * lens_ipow(x, 2) * lens_ipow(y, 3) + 1.38883e-07 * lens_ipow(x, 4) * y +
    1.37158e-05 * lens_ipow(y, 2) * lens_ipow(dy, 5) + 4.03928e-07 * lens_ipow(x, 4) * lens_ipow(dx, 2) * dy;
const float out_transmittance =
    +0.662794 + 9.23725e-05 * x + -0.0122777 * lens_ipow(dy, 2) + -0.0106307 * lens_ipow(dx, 2) +
    -5.82511e-05 * lens_ipow(y, 2) + 4.07648e-05 * lens_ipow(x, 2) + 0.0726327 * lens_ipow(lambda, 3) +
    -0.000689457 * y * lens_ipow(dy, 3) + -0.000645001 * x * lens_ipow(dx, 3) + 0.000186892 * x * y * dx * dy +
    -6.93553e-08 * lens_ipow(x, 2) * lens_ipow(y, 4) + -4.46682e-06 * lens_ipow(x, 3) * dx * lens_ipow(dy, 2) +
    -5.39349e-08 * lens_ipow(x, 4) * lens_ipow(y, 2) + -2.2056e-08 * lens_ipow(x, 6) + -8.99421e-11 * lens_ipow(y, 8);
