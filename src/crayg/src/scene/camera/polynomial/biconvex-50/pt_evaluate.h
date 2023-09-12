const float out_x = +49.7078 * dx + 0.89527 * x + 8.36908 * dx * lens_ipow(dy, 2) + 0.464516 * y * dx * dy +
                    0.00410206 * lens_ipow(y, 2) * dx + 0.169605 * x * lens_ipow(dx, 2) +
                    -2.62942e-05 * x * lens_ipow(y, 2) + -4.07919e-05 * lens_ipow(x, 3) + 7.05755 * lens_ipow(dx, 5) +
                    0.00760541 * lens_ipow(y, 2) * lens_ipow(dx, 3) + 0.0107435 * x * lens_ipow(lambda, 4) +
                    -0.0387684 * x * lens_ipow(dy, 4) + 0.000450626 * lens_ipow(x, 2) * y * dx * dy +
                    -0.000248314 * lens_ipow(x, 3) * lens_ipow(dy, 2) +
                    4.14043 * lens_ipow(dx, 3) * lens_ipow(lambda, 3);
const float out_y = +49.6917 * dy + 0.895203 * y + 8.48469 * lens_ipow(dx, 2) * dy + 0.173927 * y * lens_ipow(dy, 2) +
                    -4.10589e-05 * lens_ipow(y, 3) + 0.468195 * x * dx * dy + 0.00409844 * lens_ipow(x, 2) * dy +
                    -2.77126e-05 * lens_ipow(x, 2) * y + 3.79805 * lens_ipow(dy, 3) * lens_ipow(lambda, 2) +
                    5.97245 * lens_ipow(dy, 5) + 0.0119631 * y * lens_ipow(lambda, 4) +
                    -0.0369276 * y * lens_ipow(dx, 4) + -0.000248372 * lens_ipow(y, 3) * lens_ipow(dx, 2) +
                    0.000451026 * x * lens_ipow(y, 2) * dx * dy + 0.0075787 * lens_ipow(x, 2) * lens_ipow(dy, 3);
const float out_dx = +-1.25299e-05 + -0.0545382 * dx + -0.0210216 * x + -0.817715 * dx * lens_ipow(dy, 2) +
                     -1.38715 * lens_ipow(dx, 3) + -0.0107629 * y * dx * dy + -0.000166064 * lens_ipow(y, 2) * dx +
                     -0.0507578 * x * lens_ipow(dx, 2) + 8.4374e-05 * x * y * dy + -0.000959254 * lens_ipow(x, 2) * dx +
                     -6.75859e-06 * lens_ipow(x, 3) + 0.117828 * dx * lens_ipow(lambda, 3) +
                     0.524728 * lens_ipow(dx, 3) * lens_ipow(dy, 2) + 0.00313876 * x * lens_ipow(lambda, 4) +
                     -0.0240882 * x * lens_ipow(dy, 6);
const float out_dy =
    +-0.0792853 * dy + -0.0214779 * y + -0.77405 * lens_ipow(dy, 3) + -0.516556 * lens_ipow(dx, 2) * dy +
    -0.00983703 * y * lens_ipow(dy, 2) + 4.31745e-07 * lens_ipow(y, 3) + 7.36362e-05 * x * y * dx +
    -6.22975e-05 * lens_ipow(x, 2) * dy + 0.119743 * dy * lens_ipow(lambda, 3) + 0.00318903 * y * lens_ipow(lambda, 4) +
    -0.00141323 * lens_ipow(y, 2) * lens_ipow(dx, 2) * dy + 0.00231072 * x * y * dx * lens_ipow(dy, 2) +
    -1.14811e-06 * lens_ipow(x, 2) * lens_ipow(y, 2) * dy + -1.36629e-08 * lens_ipow(x, 2) * lens_ipow(y, 3) +
    -5.08188e-05 * lens_ipow(y, 3) * lens_ipow(dx, 4);
const float out_transmittance =
    +0.913025 + -0.0144258 * lens_ipow(dy, 2) + -0.0327269 * lens_ipow(dx, 2) + -4.68829e-06 * lens_ipow(y, 2) +
    -0.00096816 * x * dx + -1.05349e-05 * lens_ipow(x, 2) + 0.030971 * lens_ipow(lambda, 3) +
    -3.84808e-06 * lens_ipow(y, 3) * dy + 0.000114119 * x * y * dx * dy +
    -4.45442e-08 * lens_ipow(x, 2) * lens_ipow(y, 2) + -0.321741 * lens_ipow(dy, 6) +
    -1.15905 * lens_ipow(dx, 4) * lens_ipow(dy, 2) + -1.44124e-10 * lens_ipow(y, 6) +
    1.98384e-07 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(dx, 2) + -0.0896903 * lens_ipow(lambda, 8);
