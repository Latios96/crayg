const float out_x = +70.3096 * dx + -0.658805 * x + -20.0375 * dx * lens_ipow(dy, 2) + -17.8493 * lens_ipow(dx, 3) +
                    0.221743 * y * dx * dy + 0.283672 * x * lens_ipow(dy, 2) + 0.609974 * x * lens_ipow(dx, 2) +
                    0.00536721 * x * y * dy + -0.000144522 * x * lens_ipow(y, 2) + 0.00859828 * lens_ipow(x, 2) * dx +
                    -0.000144025 * lens_ipow(x, 3) + -0.0502307 * x * lens_ipow(lambda, 3) +
                    9.73595e-06 * lens_ipow(y, 4) * dx + -0.0336152 * x * y * lens_ipow(dx, 2) * dy +
                    1.29678e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * dx;
const float out_y = +70.3766 * dy + -0.65779 * y + -16.9516 * lens_ipow(dy, 3) + -19.6674 * lens_ipow(dx, 2) * dy +
                    0.646441 * y * lens_ipow(dy, 2) + 0.280535 * y * lens_ipow(dx, 2) +
                    0.00893061 * lens_ipow(y, 2) * dy + -0.000143324 * lens_ipow(y, 3) + 0.257125 * x * dx * dy +
                    0.00513652 * x * y * dx + -0.000146077 * lens_ipow(x, 2) * y +
                    -0.0560978 * y * lens_ipow(lambda, 3) + 1.15985e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * dy +
                    1.02352e-05 * lens_ipow(x, 4) * dy + -3.05027 * dy * lens_ipow(lambda, 7);
const float out_dx =
    +-0.257381 * dx + -0.0118022 * x + 0.184211 * dx * lens_ipow(dy, 2) + 0.212232 * lens_ipow(dx, 3) +
    0.00163911 * y * dx * dy + 2.46505e-05 * lens_ipow(y, 2) * dx + 0.000122219 * x * lens_ipow(dy, 2) +
    0.00258839 * x * lens_ipow(dx, 2) + 7.98505e-07 * x * lens_ipow(y, 2) + 2.98673e-05 * lens_ipow(x, 2) * dx +
    9.01927e-07 * lens_ipow(x, 3) + -0.00674536 * dx * lens_ipow(lambda, 3) + 0.000152439 * x * lens_ipow(lambda, 3) +
    -2.51387e-06 * lens_ipow(x, 2) * y * dx * dy + 1.79472e-12 * lens_ipow(x, 3) * lens_ipow(y, 4);
const float out_dy = +-0.257642 * dy + -0.0118052 * y + 0.220318 * lens_ipow(dy, 3) + 0.215099 * lens_ipow(dx, 2) * dy +
                     0.00281329 * y * lens_ipow(dy, 2) + 0.000212576 * y * lens_ipow(dx, 2) +
                     3.24999e-05 * lens_ipow(y, 2) * dy + 9.11281e-07 * lens_ipow(y, 3) + 0.00236499 * x * dx * dy +
                     2.01213e-05 * lens_ipow(x, 2) * dy + 8.79804e-07 * lens_ipow(x, 2) * y +
                     -0.00681009 * dy * lens_ipow(lambda, 3) + 0.00015235 * y * lens_ipow(lambda, 3) +
                     -1.80386e-06 * x * lens_ipow(y, 2) * dx * dy + 1.8924e-12 * lens_ipow(x, 4) * lens_ipow(y, 3);
const float out_transmittance = +0.111279 + 0.000136385 * dx + 1.25563e-06 * y + -0.0316754 * lens_ipow(dy, 2) +
                                -0.0338861 * lens_ipow(dx, 2) + -0.00075927 * y * dy + -5.09383e-06 * lens_ipow(y, 2) +
                                -0.000728847 * x * dx + -4.94424e-06 * lens_ipow(x, 2) +
                                0.140932 * lens_ipow(lambda, 3) + -6.05174e-05 * lens_ipow(y, 2) * lens_ipow(dy, 2) +
                                -9.65441e-05 * x * y * dx * dy + -8.29435e-09 * lens_ipow(x, 2) * lens_ipow(y, 2) +
                                -1.80327e-07 * lens_ipow(x, 4) * lens_ipow(dx, 2) + -0.398661 * lens_ipow(lambda, 8);
