const float out_x =
    +0.000254046 + 70.2621 * dx + -2.46041e-05 * y + -0.653785 * x + -0.0235419 * dx * dy + -0.000406297 * y * dx +
    -4.64643e-06 * x * y + -19.2784 * dx * lens_ipow(dy, 2) + -19.82 * lens_ipow(dx, 3) + 0.271375 * y * dx * dy +
    0.00259458 * lens_ipow(y, 2) * dx + 0.24179 * x * lens_ipow(dy, 2) + 0.483653 * x * lens_ipow(dx, 2) +
    0.00548671 * x * y * dy + -0.000142526 * x * lens_ipow(y, 2) + 0.00788821 * lens_ipow(x, 2) * dx +
    -0.000143924 * lens_ipow(x, 3) + 0.00012271 * lens_ipow(y, 2) * lens_ipow(dx, 2) +
    -0.0935941 * x * lens_ipow(lambda, 3) + -3.01594e-08 * lens_ipow(x, 2) * lens_ipow(y, 2) +
    4.14766e-06 * lens_ipow(y, 4) * dx + -0.0798356 * x * y * lens_ipow(dx, 2) * dy +
    0.000656535 * x * lens_ipow(y, 2) * lens_ipow(dx, 2) + 1.71389e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * dx +
    0.000298779 * lens_ipow(x, 3) * lens_ipow(dy, 2) + 0.000338911 * lens_ipow(x, 3) * lens_ipow(dx, 2) +
    -5.89847e-05 * lens_ipow(y, 4) * dx * lens_ipow(dy, 2) + -0.0934762 * x * y * lens_ipow(dy, 5) +
    0.773937 * lens_ipow(x, 2) * dx * lens_ipow(dy, 4) + -0.00625431 * x * y * dy * lens_ipow(lambda, 5) +
    -2.47424 * dx * lens_ipow(lambda, 8) + 6777.63 * lens_ipow(dx, 5) * lens_ipow(dy, 2) * lens_ipow(lambda, 2) +
    3.73331 * lens_ipow(y, 2) * lens_ipow(dx, 7) + 7.79113e-11 * lens_ipow(x, 3) * lens_ipow(y, 5) * dy +
    -6.40108e-09 * lens_ipow(x, 6) * y * dx * dy + 4.56487e-11 * lens_ipow(x, 8) * dx +
    -0.271363 * lens_ipow(x, 2) * dx * lens_ipow(dy, 2) * lens_ipow(lambda, 5) +
    -5.136e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * dx * lens_ipow(lambda, 5) + 0.440288 * x * lens_ipow(lambda, 10) +
    1.02649 * x * y * lens_ipow(dx, 2) * dy * lens_ipow(lambda, 6);
const float out_y =
    +0.000211899 + 70.217 * dy + -0.00131007 * dx + -0.654816 * y + 0.0249627 * dx * dy +
    -4.52947e-06 * lens_ipow(y, 2) + -2.06877e-06 * x * y + -15.978 * lens_ipow(dy, 3) +
    -18.8599 * lens_ipow(dx, 2) * dy + 0.66145 * y * lens_ipow(dy, 2) + 0.288328 * y * lens_ipow(dx, 2) +
    0.0101163 * lens_ipow(y, 2) * dy + -0.000131314 * lens_ipow(y, 3) + 0.314697 * x * dx * dy +
    0.00535997 * x * y * dx + -2.17044e-07 * x * lens_ipow(y, 2) + 0.00272703 * lens_ipow(x, 2) * dy +
    -0.000141901 * lens_ipow(x, 2) * y + -0.0993725 * y * lens_ipow(lambda, 3) +
    0.000963962 * lens_ipow(x, 2) * y * lens_ipow(dy, 2) + 1.87395e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * dy +
    3.89311e-06 * lens_ipow(x, 4) * dy + -0.0193591 * lens_ipow(y, 2) * dy * lens_ipow(lambda, 4) +
    -5.31328e-05 * lens_ipow(x, 4) * lens_ipow(dx, 2) * dy + -1.35534e-07 * lens_ipow(y, 5) * lens_ipow(lambda, 3) +
    -0.00550353 * x * y * dx * lens_ipow(lambda, 5) + -2.27579 * dy * lens_ipow(lambda, 8) +
    407.064 * lens_ipow(dx, 4) * dy * lens_ipow(lambda, 4) + 2.25478e-11 * lens_ipow(y, 8) * dy +
    -1.9655e-05 * x * lens_ipow(y, 4) * lens_ipow(dx, 3) * dy + 6.1607 * lens_ipow(x, 2) * lens_ipow(dy, 7) +
    1.4509e-05 * lens_ipow(x, 2) * lens_ipow(y, 3) * lens_ipow(dx, 4) +
    -0.00206173 * lens_ipow(x, 3) * y * dx * lens_ipow(dy, 4) + 5.7944e-11 * lens_ipow(x, 3) * lens_ipow(y, 5) * dx +
    3.4903e-11 * lens_ipow(x, 7) * y * dx + -13.0414 * x * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 5) +
    -2.49594e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * dy * lens_ipow(lambda, 5) +
    -1071.33 * lens_ipow(dy, 5) * lens_ipow(lambda, 6) + 0.561402 * y * lens_ipow(lambda, 10) +
    -6.76315 * y * lens_ipow(dy, 2) * lens_ipow(lambda, 8);
const float out_dx =
    +1.05262e-06 + -0.257738 * dx + -8.81348e-08 * y + -0.0118191 * x + -0.000115592 * dx * dy + -2.15491e-06 * y * dx +
    8.31513e-07 * x * dx + 0.232364 * dx * lens_ipow(dy, 2) + 0.240032 * lens_ipow(dx, 3) + 0.00303916 * y * dx * dy +
    2.81591e-05 * lens_ipow(y, 2) * dx + 0.000690185 * x * lens_ipow(dy, 2) + 0.0039607 * x * lens_ipow(dx, 2) +
    2.02434e-05 * x * y * dy + 8.81861e-07 * x * lens_ipow(y, 2) + 4.65422e-05 * lens_ipow(x, 2) * dx +
    8.94173e-07 * lens_ipow(x, 3) + -0.00738288 * dx * lens_ipow(lambda, 3) + 0.000265839 * x * lens_ipow(lambda, 3) +
    -0.000209262 * x * y * lens_ipow(dx, 2) * dy + -9.16879e-07 * x * lens_ipow(y, 2) * lens_ipow(dy, 2) +
    -7.43012e-06 * lens_ipow(x, 2) * y * dx * dy + -4.00891e-08 * lens_ipow(x, 3) * y * dy +
    -7.59538e-05 * x * y * dy * lens_ipow(lambda, 4) + -0.000162533 * lens_ipow(x, 2) * dx * lens_ipow(lambda, 4) +
    3.33057e-09 * lens_ipow(x, 5) * lens_ipow(dy, 2) + -0.0112075 * y * dx * dy * lens_ipow(lambda, 5) +
    0.0721126 * lens_ipow(y, 2) * lens_ipow(dx, 3) * lens_ipow(dy, 4) +
    8.39134e-06 * lens_ipow(y, 4) * lens_ipow(dx, 5) + -0.0354275 * x * lens_ipow(dx, 2) * lens_ipow(lambda, 6) +
    -3.30717e-09 * x * lens_ipow(y, 5) * lens_ipow(dx, 2) * dy + 6.03832e-15 * lens_ipow(x, 5) * lens_ipow(y, 4) +
    -5.11682 * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 5) + -12.3137 * lens_ipow(dx, 5) * lens_ipow(lambda, 6) +
    658.794 * lens_ipow(dx, 11) + -0.00243157 * lens_ipow(y, 2) * lens_ipow(dx, 3) * lens_ipow(lambda, 6) +
    -0.00104482 * x * lens_ipow(lambda, 10) +
    -0.00339056 * lens_ipow(x, 2) * dx * lens_ipow(dy, 2) * lens_ipow(lambda, 6) +
    -4.71681e-05 * lens_ipow(x, 3) * lens_ipow(dy, 2) * lens_ipow(lambda, 6) +
    -3.54124e-09 * lens_ipow(x, 3) * lens_ipow(y, 2) * lens_ipow(lambda, 6);
const float out_dy =
    +1.15543e-06 + -0.258097 * dy + -0.0118279 * y + -1.35996e-06 * y * dy + -1.53951e-08 * lens_ipow(x, 2) +
    0.244621 * lens_ipow(dy, 3) + 0.239714 * lens_ipow(dx, 2) * dy + 0.00440131 * y * lens_ipow(dy, 2) +
    0.000853338 * y * lens_ipow(dx, 2) + 5.55721e-05 * lens_ipow(y, 2) * dy + 9.19063e-07 * lens_ipow(y, 3) +
    0.00344002 * x * dx * dy + 1.51788e-05 * x * y * dx + 2.21063e-05 * lens_ipow(x, 2) * dy +
    9.66176e-07 * lens_ipow(x, 2) * y + -0.00565525 * dy * lens_ipow(lambda, 3) +
    0.000293436 * y * lens_ipow(lambda, 3) + 7.11113e-05 * x * y * lens_ipow(dx, 3) +
    -2.17036e-06 * x * lens_ipow(y, 2) * dx * dy + 14.9837 * lens_ipow(dx, 2) * lens_ipow(dy, 5) +
    -0.000232937 * lens_ipow(y, 2) * dy * lens_ipow(lambda, 4) + -0.00012057 * x * y * dx * lens_ipow(lambda, 4) +
    9.71525e-07 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(dx, 2) * dy +
    -1.28308e-06 * lens_ipow(x, 3) * y * dx * lens_ipow(dy, 2) + -0.014953 * x * dx * dy * lens_ipow(lambda, 5) +
    -7.18392e-07 * lens_ipow(x, 2) * y * lens_ipow(lambda, 5) + 406.921 * lens_ipow(dx, 6) * lens_ipow(dy, 3) +
    -0.0438216 * y * lens_ipow(dy, 2) * lens_ipow(lambda, 6) +
    -0.0120327 * y * lens_ipow(dx, 2) * lens_ipow(lambda, 6) + 7.71629e-08 * lens_ipow(y, 5) * lens_ipow(dx, 4) +
    1.45693e-15 * lens_ipow(y, 9) + 9.93437e-06 * lens_ipow(x, 4) * lens_ipow(dy, 5) +
    6.17162e-15 * lens_ipow(x, 4) * lens_ipow(y, 5) + -13.6236 * lens_ipow(dy, 5) * lens_ipow(lambda, 6) +
    713.085 * lens_ipow(dy, 11) + -21.6029 * lens_ipow(dx, 2) * lens_ipow(dy, 3) * lens_ipow(lambda, 6) +
    -13.9192 * lens_ipow(dx, 4) * dy * lens_ipow(lambda, 6) + -0.000519216 * y * lens_ipow(lambda, 10) +
    -4.50146e-09 * lens_ipow(y, 5) * lens_ipow(lambda, 6) +
    -0.00283106 * lens_ipow(x, 2) * lens_ipow(dy, 3) * lens_ipow(lambda, 6);
const float out_transmittance =
    +0.047879 + 0.200766 * lambda + -3.09921e-06 * dx + 1.67701e-07 * y + -1.46101e-07 * x +
    -0.0293784 * lens_ipow(dy, 2) + -0.0292605 * lens_ipow(dx, 2) + -0.000296007 * y * dy +
    -2.94687e-06 * lens_ipow(y, 2) + -0.000278623 * x * dx + -3.10662e-06 * lens_ipow(x, 2) +
    -0.161495 * lens_ipow(lambda, 3) + -1.43246e-05 * x * dx * dy + 0.349993 * lens_ipow(dx, 2) * lens_ipow(dy, 2) +
    -0.0187968 * y * lens_ipow(dy, 3) + -0.000397756 * lens_ipow(y, 2) * lens_ipow(dy, 2) +
    -3.08e-06 * lens_ipow(y, 3) * dy + -0.00989688 * x * dx * lens_ipow(dy, 2) + -0.0179809 * x * lens_ipow(dx, 3) +
    -0.000393196 * x * y * dx * dy + -2.14123e-06 * x * lens_ipow(y, 2) * dx +
    -0.00039069 * lens_ipow(x, 2) * lens_ipow(dx, 2) + -2.26345e-06 * lens_ipow(x, 2) * y * dy +
    -2.02248e-08 * lens_ipow(x, 2) * lens_ipow(y, 2) + -2.98378e-06 * lens_ipow(x, 3) * dx +
    -3.59086 * lens_ipow(dy, 6) + -2.37733 * lens_ipow(dx, 6) + -0.216174 * y * lens_ipow(dx, 4) * dy +
    -2.18891e-07 * lens_ipow(y, 4) * lens_ipow(dx, 2) + -2.09708e-11 * lens_ipow(y, 6) +
    3.83099e-12 * lens_ipow(x, 2) * lens_ipow(y, 4) + -3.09074e-07 * lens_ipow(x, 4) * lens_ipow(dy, 2) +
    -3.60437e-11 * lens_ipow(x, 6) * lambda + -226.248 * lens_ipow(dx, 6) * lens_ipow(dy, 2) +
    -7.43453e-10 * lens_ipow(x, 2) * lens_ipow(y, 4) * lens_ipow(dy, 2) +
    -5.39325e-10 * lens_ipow(x, 4) * lens_ipow(y, 2) * lens_ipow(dx, 2) +
    -2.20558e-11 * lens_ipow(y, 6) * lens_ipow(lambda, 3) + -4722.7 * lens_ipow(dx, 4) * lens_ipow(dy, 6) +
    -0.165618 * lens_ipow(y, 2) * lens_ipow(dx, 8) + 0.278312 * lens_ipow(lambda, 11);
