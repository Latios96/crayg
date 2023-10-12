const float out_x = +49.7612 * dx + -0.416008 * x + -20.2966 * dx * lens_ipow(dy, 2) + -20.226 * lens_ipow(dx, 3) +
                    0.0759534 * y * dx * dy + 0.00561853 * lens_ipow(y, 2) * dx + 0.248678 * x * lens_ipow(dy, 2) +
                    0.280714 * x * lens_ipow(dx, 2) + 0.00553397 * x * y * dy + -0.00119513 * x * lens_ipow(y, 2) +
                    0.0116887 * lens_ipow(x, 2) * dx + -0.00124886 * lens_ipow(x, 3) +
                    0.190817 * x * lens_ipow(lambda, 3) + -0.00154305 * lens_ipow(x, 2) * y * dx * dy +
                    -1.50715e-06 * lens_ipow(x, 3) * lens_ipow(y, 2);
const float out_y = +49.7256 * dy + -0.426628 * y + -20.1544 * lens_ipow(dy, 3) + -20.1594 * lens_ipow(dx, 2) * dy +
                    0.31218 * y * lens_ipow(dy, 2) + 0.273585 * y * lens_ipow(dx, 2) +
                    0.0129475 * lens_ipow(y, 2) * dy + -0.00120052 * lens_ipow(y, 3) + 0.0602065 * x * dx * dy +
                    0.00752746 * x * y * dx + 0.00608451 * lens_ipow(x, 2) * dy + -0.000947214 * lens_ipow(x, 2) * y +
                    0.194105 * y * lens_ipow(lambda, 3) + -2.35017e-06 * lens_ipow(x, 2) * lens_ipow(y, 3) +
                    -3.76172e-09 * lens_ipow(x, 6) * y;
const float out_dx = +-0.611978 * dx + -0.0146939 * x + 0.174374 * dx * lens_ipow(dy, 2) + 0.273016 * lens_ipow(dx, 3) +
                     2.13592e-05 * lens_ipow(y, 2) * dx + -0.0023621 * x * lens_ipow(dy, 2) +
                     -8.77444e-05 * x * y * dy + 1.35003e-05 * x * lens_ipow(y, 2) +
                     -2.06958e-05 * lens_ipow(x, 2) * dx + 1.57003e-05 * lens_ipow(x, 3) +
                     -0.00251882 * x * lens_ipow(lambda, 3) + 4.12322e-05 * lens_ipow(x, 2) * y * dx * dy +
                     6.04821e-11 * x * lens_ipow(y, 6) + 1.70456e-10 * lens_ipow(x, 5) * lens_ipow(y, 2) +
                     -2.15665e-09 * lens_ipow(x, 6) * dx;
const float out_dy = +-0.612625 * dy + -0.0146229 * y + 0.273186 * lens_ipow(dy, 3) + 0.355011 * lens_ipow(dx, 2) * dy +
                     -0.00469558 * y * lens_ipow(dx, 2) + -7.97939e-06 * lens_ipow(y, 2) * dy +
                     1.50862e-05 * lens_ipow(y, 3) + 0.0039708 * x * dx * dy + -0.000126811 * x * y * dx +
                     1.34875e-05 * lens_ipow(x, 2) * y + -0.0024975 * y * lens_ipow(lambda, 3) +
                     -2.54143e-09 * lens_ipow(y, 6) * dy + 1.77666e-10 * lens_ipow(x, 2) * lens_ipow(y, 5) +
                     -4.37761e-09 * lens_ipow(x, 4) * lens_ipow(y, 2) * dy + 6.23102e-11 * lens_ipow(x, 6) * y;
const float out_transmittance = +0.423291 + -0.0450698 * lens_ipow(dy, 2) + -0.0408977 * lens_ipow(dx, 2) +
                                -0.000779391 * y * dy + -2.19592e-05 * lens_ipow(y, 2) + -0.00101761 * x * dx +
                                -1.79361e-05 * lens_ipow(x, 2) + 0.190101 * lens_ipow(lambda, 3) +
                                3.66881e-06 * lens_ipow(x, 3) * dx + -0.39286 * lens_ipow(dy, 6) +
                                -1.91044 * lens_ipow(dx, 4) * lens_ipow(dy, 2) + -0.363741 * lens_ipow(dx, 6) +
                                4.88735e-08 * lens_ipow(x, 2) * lens_ipow(y, 3) * dy +
                                3.38805e-08 * lens_ipow(x, 3) * lens_ipow(y, 2) * dx + -0.548128 * lens_ipow(lambda, 8);
