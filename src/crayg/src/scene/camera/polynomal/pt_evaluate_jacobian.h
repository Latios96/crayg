const float dx00 = +-0.653785 + -4.64643e-06 * y + 0.24179 * lens_ipow(dy, 2) + 0.483653 * lens_ipow(dx, 2) +
                   0.00548671 * y * dy + -0.000142526 * lens_ipow(y, 2) + 0.0157764 * x * dx +
                   -0.000431773 * lens_ipow(x, 2) + -0.0935941 * lens_ipow(lambda, 3) +
                   -6.03188e-08 * x * lens_ipow(y, 2) + -0.0798356 * y * lens_ipow(dx, 2) * dy +
                   0.000656535 * lens_ipow(y, 2) * lens_ipow(dx, 2) + 3.42778e-05 * x * lens_ipow(y, 2) * dx +
                   0.000896338 * lens_ipow(x, 2) * lens_ipow(dy, 2) + 0.00101673 * lens_ipow(x, 2) * lens_ipow(dx, 2) +
                   -0.0934762 * y * lens_ipow(dy, 5) + 1.54787 * x * dx * lens_ipow(dy, 4) +
                   -0.00625431 * y * dy * lens_ipow(lambda, 5) + 2.33734e-10 * lens_ipow(x, 2) * lens_ipow(y, 5) * dy +
                   -3.84065e-08 * lens_ipow(x, 5) * y * dx * dy + 3.65189e-10 * lens_ipow(x, 7) * dx +
                   -0.542725 * x * dx * lens_ipow(dy, 2) * lens_ipow(lambda, 5) +
                   -0.00010272 * x * lens_ipow(y, 2) * dx * lens_ipow(lambda, 5) + 0.440288 * lens_ipow(lambda, 10) +
                   1.02649 * y * lens_ipow(dx, 2) * dy * lens_ipow(lambda, 6) + 0.0f;
const float dx01 = +-2.46041e-05 + -0.000406297 * dx + -4.64643e-06 * x + 0.271375 * dx * dy + 0.00518915 * y * dx +
                   0.00548671 * x * dy + -0.000285051 * x * y + 0.00024542 * y * lens_ipow(dx, 2) +
                   -6.03188e-08 * lens_ipow(x, 2) * y + 1.65906e-05 * lens_ipow(y, 3) * dx +
                   -0.0798356 * x * lens_ipow(dx, 2) * dy + 0.00131307 * x * y * lens_ipow(dx, 2) +
                   3.42778e-05 * lens_ipow(x, 2) * y * dx + -0.000235939 * lens_ipow(y, 3) * dx * lens_ipow(dy, 2) +
                   -0.0934762 * x * lens_ipow(dy, 5) + -0.00625431 * x * dy * lens_ipow(lambda, 5) +
                   7.46661 * y * lens_ipow(dx, 7) + 3.89556e-10 * lens_ipow(x, 3) * lens_ipow(y, 4) * dy +
                   -6.40108e-09 * lens_ipow(x, 6) * dx * dy +
                   -0.00010272 * lens_ipow(x, 2) * y * dx * lens_ipow(lambda, 5) +
                   1.02649 * x * lens_ipow(dx, 2) * dy * lens_ipow(lambda, 6) + 0.0f;
const float dx02 =
    +70.2621 + -0.0235419 * dy + -0.000406297 * y + -19.2784 * lens_ipow(dy, 2) + -59.46 * lens_ipow(dx, 2) +
    0.271375 * y * dy + 0.00259458 * lens_ipow(y, 2) + 0.967305 * x * dx + 0.00788821 * lens_ipow(x, 2) +
    0.00024542 * lens_ipow(y, 2) * dx + 4.14766e-06 * lens_ipow(y, 4) + -0.159671 * x * y * dx * dy +
    0.00131307 * x * lens_ipow(y, 2) * dx + 1.71389e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) +
    0.000677821 * lens_ipow(x, 3) * dx + -5.89847e-05 * lens_ipow(y, 4) * lens_ipow(dy, 2) +
    0.773937 * lens_ipow(x, 2) * lens_ipow(dy, 4) + -2.47424 * lens_ipow(lambda, 8) +
    33888.1 * lens_ipow(dx, 4) * lens_ipow(dy, 2) * lens_ipow(lambda, 2) +
    26.1331 * lens_ipow(y, 2) * lens_ipow(dx, 6) + -6.40108e-09 * lens_ipow(x, 6) * y * dy +
    4.56487e-11 * lens_ipow(x, 8) + -0.271363 * lens_ipow(x, 2) * lens_ipow(dy, 2) * lens_ipow(lambda, 5) +
    -5.136e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(lambda, 5) +
    2.05299 * x * y * dx * dy * lens_ipow(lambda, 6) + 0.0f;
const float dx03 = +-0.0235419 * dx + -38.5568 * dx * dy + 0.271375 * y * dx + 0.483579 * x * dy + 0.00548671 * x * y +
                   -0.0798356 * x * y * lens_ipow(dx, 2) + 0.000597558 * lens_ipow(x, 3) * dy +
                   -0.000117969 * lens_ipow(y, 4) * dx * dy + -0.467381 * x * y * lens_ipow(dy, 4) +
                   3.09575 * lens_ipow(x, 2) * dx * lens_ipow(dy, 3) + -0.00625431 * x * y * lens_ipow(lambda, 5) +
                   13555.3 * lens_ipow(dx, 5) * dy * lens_ipow(lambda, 2) +
                   7.79113e-11 * lens_ipow(x, 3) * lens_ipow(y, 5) + -6.40108e-09 * lens_ipow(x, 6) * y * dx +
                   -0.542725 * lens_ipow(x, 2) * dx * dy * lens_ipow(lambda, 5) +
                   1.02649 * x * y * lens_ipow(dx, 2) * lens_ipow(lambda, 6) + 0.0f;
const float dx04 = +-0.280782 * x * lens_ipow(lambda, 2) + -0.0312715 * x * y * dy * lens_ipow(lambda, 4) +
                   -19.7939 * dx * lens_ipow(lambda, 7) + 13555.3 * lens_ipow(dx, 5) * lens_ipow(dy, 2) * lambda +
                   -1.35681 * lens_ipow(x, 2) * dx * lens_ipow(dy, 2) * lens_ipow(lambda, 4) +
                   -0.0002568 * lens_ipow(x, 2) * lens_ipow(y, 2) * dx * lens_ipow(lambda, 4) +
                   4.40288 * x * lens_ipow(lambda, 9) + 6.15897 * x * y * lens_ipow(dx, 2) * dy * lens_ipow(lambda, 5) +
                   0.0f;
const float dx10 = +-2.06877e-06 * y + 0.314697 * dx * dy + 0.00535997 * y * dx + -2.17044e-07 * lens_ipow(y, 2) +
                   0.00545406 * x * dy + -0.000283801 * x * y + 0.00192792 * x * y * lens_ipow(dy, 2) +
                   3.74789e-05 * x * lens_ipow(y, 2) * dy + 1.55724e-05 * lens_ipow(x, 3) * dy +
                   -0.000212531 * lens_ipow(x, 3) * lens_ipow(dx, 2) * dy +
                   -0.00550353 * y * dx * lens_ipow(lambda, 5) + -1.9655e-05 * lens_ipow(y, 4) * lens_ipow(dx, 3) * dy +
                   12.3214 * x * lens_ipow(dy, 7) + 2.9018e-05 * x * lens_ipow(y, 3) * lens_ipow(dx, 4) +
                   -0.00618519 * lens_ipow(x, 2) * y * dx * lens_ipow(dy, 4) +
                   1.73832e-10 * lens_ipow(x, 2) * lens_ipow(y, 5) * dx + 2.44321e-10 * lens_ipow(x, 6) * y * dx +
                   -13.0414 * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 5) +
                   -4.99187e-05 * x * lens_ipow(y, 2) * dy * lens_ipow(lambda, 5) + 0.0f;
const float dx11 = +-0.654816 + -9.05895e-06 * y + -2.06877e-06 * x + 0.66145 * lens_ipow(dy, 2) +
                   0.288328 * lens_ipow(dx, 2) + 0.0202326 * y * dy + -0.000393941 * lens_ipow(y, 2) +
                   0.00535997 * x * dx + -4.34089e-07 * x * y + -0.000141901 * lens_ipow(x, 2) +
                   -0.0993725 * lens_ipow(lambda, 3) + 0.000963962 * lens_ipow(x, 2) * lens_ipow(dy, 2) +
                   3.74789e-05 * lens_ipow(x, 2) * y * dy + -0.0387183 * y * dy * lens_ipow(lambda, 4) +
                   -6.77669e-07 * lens_ipow(y, 4) * lens_ipow(lambda, 3) + -0.00550353 * x * dx * lens_ipow(lambda, 5) +
                   1.80382e-10 * lens_ipow(y, 7) * dy + -7.86202e-05 * x * lens_ipow(y, 3) * lens_ipow(dx, 3) * dy +
                   4.3527e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(dx, 4) +
                   -0.00206173 * lens_ipow(x, 3) * dx * lens_ipow(dy, 4) +
                   2.8972e-10 * lens_ipow(x, 3) * lens_ipow(y, 4) * dx + 3.4903e-11 * lens_ipow(x, 7) * dx +
                   -4.99187e-05 * lens_ipow(x, 2) * y * dy * lens_ipow(lambda, 5) + 0.561402 * lens_ipow(lambda, 10) +
                   -6.76315 * lens_ipow(dy, 2) * lens_ipow(lambda, 8) + 0.0f;
const float dx12 = +-0.00131007 + 0.0249627 * dy + -37.7198 * dx * dy + 0.576657 * y * dx + 0.314697 * x * dy +
                   0.00535997 * x * y + -0.000106266 * lens_ipow(x, 4) * dx * dy +
                   -0.00550353 * x * y * lens_ipow(lambda, 5) + 1628.25 * lens_ipow(dx, 3) * dy * lens_ipow(lambda, 4) +
                   -5.89651e-05 * x * lens_ipow(y, 4) * lens_ipow(dx, 2) * dy +
                   5.80359e-05 * lens_ipow(x, 2) * lens_ipow(y, 3) * lens_ipow(dx, 3) +
                   -0.00206173 * lens_ipow(x, 3) * y * lens_ipow(dy, 4) +
                   5.7944e-11 * lens_ipow(x, 3) * lens_ipow(y, 5) + 3.4903e-11 * lens_ipow(x, 7) * y +
                   -13.0414 * x * lens_ipow(dy, 3) * lens_ipow(lambda, 5) + 0.0f;
const float dx13 = +70.217 + 0.0249627 * dx + -47.9341 * lens_ipow(dy, 2) + -18.8599 * lens_ipow(dx, 2) +
                   1.3229 * y * dy + 0.0101163 * lens_ipow(y, 2) + 0.314697 * x * dx + 0.00272703 * lens_ipow(x, 2) +
                   0.00192792 * lens_ipow(x, 2) * y * dy + 1.87395e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) +
                   3.89311e-06 * lens_ipow(x, 4) + -0.0193591 * lens_ipow(y, 2) * lens_ipow(lambda, 4) +
                   -5.31328e-05 * lens_ipow(x, 4) * lens_ipow(dx, 2) + -2.27579 * lens_ipow(lambda, 8) +
                   407.064 * lens_ipow(dx, 4) * lens_ipow(lambda, 4) + 2.25478e-11 * lens_ipow(y, 8) +
                   -1.9655e-05 * x * lens_ipow(y, 4) * lens_ipow(dx, 3) + 43.1249 * lens_ipow(x, 2) * lens_ipow(dy, 6) +
                   -0.00824692 * lens_ipow(x, 3) * y * dx * lens_ipow(dy, 3) +
                   -39.1241 * x * dx * lens_ipow(dy, 2) * lens_ipow(lambda, 5) +
                   -2.49594e-05 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(lambda, 5) +
                   -5356.67 * lens_ipow(dy, 4) * lens_ipow(lambda, 6) + -13.5263 * y * dy * lens_ipow(lambda, 8) + 0.0f;
const float dx14 = +-0.298117 * y * lens_ipow(lambda, 2) + -0.0774366 * lens_ipow(y, 2) * dy * lens_ipow(lambda, 3) +
                   -4.06602e-07 * lens_ipow(y, 5) * lens_ipow(lambda, 2) +
                   -0.0275177 * x * y * dx * lens_ipow(lambda, 4) + -18.2063 * dy * lens_ipow(lambda, 7) +
                   1628.25 * lens_ipow(dx, 4) * dy * lens_ipow(lambda, 3) +
                   -65.2068 * x * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 4) +
                   -0.000124797 * lens_ipow(x, 2) * lens_ipow(y, 2) * dy * lens_ipow(lambda, 4) +
                   -6428.01 * lens_ipow(dy, 5) * lens_ipow(lambda, 5) + 5.61402 * y * lens_ipow(lambda, 9) +
                   -54.1052 * y * lens_ipow(dy, 2) * lens_ipow(lambda, 7) + 0.0f;
const float dx20 =
    +-0.0118191 + 8.31513e-07 * dx + 0.000690185 * lens_ipow(dy, 2) + 0.0039607 * lens_ipow(dx, 2) +
    2.02434e-05 * y * dy + 8.81861e-07 * lens_ipow(y, 2) + 9.30843e-05 * x * dx + 2.68252e-06 * lens_ipow(x, 2) +
    0.000265839 * lens_ipow(lambda, 3) + -0.000209262 * y * lens_ipow(dx, 2) * dy +
    -9.16879e-07 * lens_ipow(y, 2) * lens_ipow(dy, 2) + -1.48602e-05 * x * y * dx * dy +
    -1.20267e-07 * lens_ipow(x, 2) * y * dy + -7.59538e-05 * y * dy * lens_ipow(lambda, 4) +
    -0.000325066 * x * dx * lens_ipow(lambda, 4) + 1.66529e-08 * lens_ipow(x, 4) * lens_ipow(dy, 2) +
    -0.0354275 * lens_ipow(dx, 2) * lens_ipow(lambda, 6) + -3.30717e-09 * lens_ipow(y, 5) * lens_ipow(dx, 2) * dy +
    3.01916e-14 * lens_ipow(x, 4) * lens_ipow(y, 4) + -0.00104482 * lens_ipow(lambda, 10) +
    -0.00678111 * x * dx * lens_ipow(dy, 2) * lens_ipow(lambda, 6) +
    -0.000141504 * lens_ipow(x, 2) * lens_ipow(dy, 2) * lens_ipow(lambda, 6) +
    -1.06237e-08 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(lambda, 6) + 0.0f;
const float dx21 =
    +-8.81348e-08 + -2.15491e-06 * dx + 0.00303916 * dx * dy + 5.63182e-05 * y * dx + 2.02434e-05 * x * dy +
    1.76372e-06 * x * y + -0.000209262 * x * lens_ipow(dx, 2) * dy + -1.83376e-06 * x * y * lens_ipow(dy, 2) +
    -7.43012e-06 * lens_ipow(x, 2) * dx * dy + -4.00891e-08 * lens_ipow(x, 3) * dy +
    -7.59538e-05 * x * dy * lens_ipow(lambda, 4) + -0.0112075 * dx * dy * lens_ipow(lambda, 5) +
    0.144225 * y * lens_ipow(dx, 3) * lens_ipow(dy, 4) + 3.35653e-05 * lens_ipow(y, 3) * lens_ipow(dx, 5) +
    -1.65359e-08 * x * lens_ipow(y, 4) * lens_ipow(dx, 2) * dy + 2.41533e-14 * lens_ipow(x, 5) * lens_ipow(y, 3) +
    -0.00486313 * y * lens_ipow(dx, 3) * lens_ipow(lambda, 6) +
    -7.08248e-09 * lens_ipow(x, 3) * y * lens_ipow(lambda, 6) + 0.0f;
const float dx22 = +-0.257738 + -0.000115592 * dy + -2.15491e-06 * y + 8.31513e-07 * x + 0.232364 * lens_ipow(dy, 2) +
                   0.720096 * lens_ipow(dx, 2) + 0.00303916 * y * dy + 2.81591e-05 * lens_ipow(y, 2) +
                   0.00792141 * x * dx + 4.65422e-05 * lens_ipow(x, 2) + -0.00738288 * lens_ipow(lambda, 3) +
                   -0.000418525 * x * y * dx * dy + -7.43012e-06 * lens_ipow(x, 2) * y * dy +
                   -0.000162533 * lens_ipow(x, 2) * lens_ipow(lambda, 4) + -0.0112075 * y * dy * lens_ipow(lambda, 5) +
                   0.216338 * lens_ipow(y, 2) * lens_ipow(dx, 2) * lens_ipow(dy, 4) +
                   4.19567e-05 * lens_ipow(y, 4) * lens_ipow(dx, 4) + -0.0708551 * x * dx * lens_ipow(lambda, 6) +
                   -6.61434e-09 * x * lens_ipow(y, 5) * dx * dy + -5.11682 * lens_ipow(dy, 4) * lens_ipow(lambda, 5) +
                   -61.5683 * lens_ipow(dx, 4) * lens_ipow(lambda, 6) + 7246.73 * lens_ipow(dx, 10) +
                   -0.0072947 * lens_ipow(y, 2) * lens_ipow(dx, 2) * lens_ipow(lambda, 6) +
                   -0.00339056 * lens_ipow(x, 2) * lens_ipow(dy, 2) * lens_ipow(lambda, 6) + 0.0f;
const float dx23 =
    +-0.000115592 * dx + 0.464729 * dx * dy + 0.00303916 * y * dx + 0.00138037 * x * dy + 2.02434e-05 * x * y +
    -0.000209262 * x * y * lens_ipow(dx, 2) + -1.83376e-06 * x * lens_ipow(y, 2) * dy +
    -7.43012e-06 * lens_ipow(x, 2) * y * dx + -4.00891e-08 * lens_ipow(x, 3) * y +
    -7.59538e-05 * x * y * lens_ipow(lambda, 4) + 6.66114e-09 * lens_ipow(x, 5) * dy +
    -0.0112075 * y * dx * lens_ipow(lambda, 5) + 0.28845 * lens_ipow(y, 2) * lens_ipow(dx, 3) * lens_ipow(dy, 3) +
    -3.30717e-09 * x * lens_ipow(y, 5) * lens_ipow(dx, 2) + -20.4673 * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 5) +
    -0.00678111 * lens_ipow(x, 2) * dx * dy * lens_ipow(lambda, 6) +
    -9.43362e-05 * lens_ipow(x, 3) * dy * lens_ipow(lambda, 6) + 0.0f;
const float dx24 =
    +-0.0221486 * dx * lens_ipow(lambda, 2) + 0.000797518 * x * lens_ipow(lambda, 2) +
    -0.000303815 * x * y * dy * lens_ipow(lambda, 3) + -0.000650133 * lens_ipow(x, 2) * dx * lens_ipow(lambda, 3) +
    -0.0560376 * y * dx * dy * lens_ipow(lambda, 4) + -0.212565 * x * lens_ipow(dx, 2) * lens_ipow(lambda, 5) +
    -25.5841 * dx * lens_ipow(dy, 4) * lens_ipow(lambda, 4) + -73.8819 * lens_ipow(dx, 5) * lens_ipow(lambda, 5) +
    -0.0145894 * lens_ipow(y, 2) * lens_ipow(dx, 3) * lens_ipow(lambda, 5) + -0.0104482 * x * lens_ipow(lambda, 9) +
    -0.0203433 * lens_ipow(x, 2) * dx * lens_ipow(dy, 2) * lens_ipow(lambda, 5) +
    -0.000283009 * lens_ipow(x, 3) * lens_ipow(dy, 2) * lens_ipow(lambda, 5) +
    -2.12474e-08 * lens_ipow(x, 3) * lens_ipow(y, 2) * lens_ipow(lambda, 5) + 0.0f;
const float dx30 =
    +-3.07902e-08 * x + 0.00344002 * dx * dy + 1.51788e-05 * y * dx + 4.42126e-05 * x * dy + 1.93235e-06 * x * y +
    7.11113e-05 * y * lens_ipow(dx, 3) + -2.17036e-06 * lens_ipow(y, 2) * dx * dy +
    -0.00012057 * y * dx * lens_ipow(lambda, 4) + 1.94305e-06 * x * lens_ipow(y, 2) * lens_ipow(dx, 2) * dy +
    -3.84924e-06 * lens_ipow(x, 2) * y * dx * lens_ipow(dy, 2) + -0.014953 * dx * dy * lens_ipow(lambda, 5) +
    -1.43678e-06 * x * y * lens_ipow(lambda, 5) + 3.97375e-05 * lens_ipow(x, 3) * lens_ipow(dy, 5) +
    2.46865e-14 * lens_ipow(x, 3) * lens_ipow(y, 5) + -0.00566213 * x * lens_ipow(dy, 3) * lens_ipow(lambda, 6) + 0.0f;
const float dx31 =
    +-0.0118279 + -1.35996e-06 * dy + 0.00440131 * lens_ipow(dy, 2) + 0.000853338 * lens_ipow(dx, 2) +
    0.000111144 * y * dy + 2.75719e-06 * lens_ipow(y, 2) + 1.51788e-05 * x * dx + 9.66176e-07 * lens_ipow(x, 2) +
    0.000293436 * lens_ipow(lambda, 3) + 7.11113e-05 * x * lens_ipow(dx, 3) + -4.34072e-06 * x * y * dx * dy +
    -0.000465874 * y * dy * lens_ipow(lambda, 4) + -0.00012057 * x * dx * lens_ipow(lambda, 4) +
    1.94305e-06 * lens_ipow(x, 2) * y * lens_ipow(dx, 2) * dy + -1.28308e-06 * lens_ipow(x, 3) * dx * lens_ipow(dy, 2) +
    -7.18392e-07 * lens_ipow(x, 2) * lens_ipow(lambda, 5) + -0.0438216 * lens_ipow(dy, 2) * lens_ipow(lambda, 6) +
    -0.0120327 * lens_ipow(dx, 2) * lens_ipow(lambda, 6) + 3.85815e-07 * lens_ipow(y, 4) * lens_ipow(dx, 4) +
    1.31124e-14 * lens_ipow(y, 8) + 3.08581e-14 * lens_ipow(x, 4) * lens_ipow(y, 4) +
    -0.000519216 * lens_ipow(lambda, 10) + -2.25073e-08 * lens_ipow(y, 4) * lens_ipow(lambda, 6) + 0.0f;
const float dx32 =
    +0.479427 * dx * dy + 0.00170668 * y * dx + 0.00344002 * x * dy + 1.51788e-05 * x * y +
    0.000213334 * x * y * lens_ipow(dx, 2) + -2.17036e-06 * x * lens_ipow(y, 2) * dy + 29.9674 * dx * lens_ipow(dy, 5) +
    -0.00012057 * x * y * lens_ipow(lambda, 4) + 1.94305e-06 * lens_ipow(x, 2) * lens_ipow(y, 2) * dx * dy +
    -1.28308e-06 * lens_ipow(x, 3) * y * lens_ipow(dy, 2) + -0.014953 * x * dy * lens_ipow(lambda, 5) +
    2441.53 * lens_ipow(dx, 5) * lens_ipow(dy, 3) + -0.0240655 * y * dx * lens_ipow(lambda, 6) +
    3.08652e-07 * lens_ipow(y, 5) * lens_ipow(dx, 3) + -43.2057 * dx * lens_ipow(dy, 3) * lens_ipow(lambda, 6) +
    -55.6767 * lens_ipow(dx, 3) * dy * lens_ipow(lambda, 6) + 0.0f;
const float dx33 =
    +-0.258097 + -1.35996e-06 * y + 0.733864 * lens_ipow(dy, 2) + 0.239714 * lens_ipow(dx, 2) + 0.00880263 * y * dy +
    5.55721e-05 * lens_ipow(y, 2) + 0.00344002 * x * dx + 2.21063e-05 * lens_ipow(x, 2) +
    -0.00565525 * lens_ipow(lambda, 3) + -2.17036e-06 * x * lens_ipow(y, 2) * dx +
    74.9186 * lens_ipow(dx, 2) * lens_ipow(dy, 4) + -0.000232937 * lens_ipow(y, 2) * lens_ipow(lambda, 4) +
    9.71525e-07 * lens_ipow(x, 2) * lens_ipow(y, 2) * lens_ipow(dx, 2) + -2.56616e-06 * lens_ipow(x, 3) * y * dx * dy +
    -0.014953 * x * dx * lens_ipow(lambda, 5) + 1220.76 * lens_ipow(dx, 6) * lens_ipow(dy, 2) +
    -0.0876433 * y * dy * lens_ipow(lambda, 6) + 4.96718e-05 * lens_ipow(x, 4) * lens_ipow(dy, 4) +
    -68.1178 * lens_ipow(dy, 4) * lens_ipow(lambda, 6) + 7843.94 * lens_ipow(dy, 10) +
    -64.8086 * lens_ipow(dx, 2) * lens_ipow(dy, 2) * lens_ipow(lambda, 6) +
    -13.9192 * lens_ipow(dx, 4) * lens_ipow(lambda, 6) +
    -0.00849319 * lens_ipow(x, 2) * lens_ipow(dy, 2) * lens_ipow(lambda, 6) + 0.0f;
const float dx34 =
    +-0.0169658 * dy * lens_ipow(lambda, 2) + 0.000880308 * y * lens_ipow(lambda, 2) +
    -0.000931747 * lens_ipow(y, 2) * dy * lens_ipow(lambda, 3) + -0.00048228 * x * y * dx * lens_ipow(lambda, 3) +
    -0.0747652 * x * dx * dy * lens_ipow(lambda, 4) + -3.59196e-06 * lens_ipow(x, 2) * y * lens_ipow(lambda, 4) +
    -0.26293 * y * lens_ipow(dy, 2) * lens_ipow(lambda, 5) + -0.0721964 * y * lens_ipow(dx, 2) * lens_ipow(lambda, 5) +
    -81.7413 * lens_ipow(dy, 5) * lens_ipow(lambda, 5) +
    -129.617 * lens_ipow(dx, 2) * lens_ipow(dy, 3) * lens_ipow(lambda, 5) +
    -83.5151 * lens_ipow(dx, 4) * dy * lens_ipow(lambda, 5) + -0.00519216 * y * lens_ipow(lambda, 9) +
    -2.70087e-08 * lens_ipow(y, 5) * lens_ipow(lambda, 5) +
    -0.0169864 * lens_ipow(x, 2) * lens_ipow(dy, 3) * lens_ipow(lambda, 5) + 0.0f;
const float dx40 = +-1.46101e-07 + -0.000278623 * dx + -6.21325e-06 * x + -1.43246e-05 * dx * dy +
                   -0.00989688 * dx * lens_ipow(dy, 2) + -0.0179809 * lens_ipow(dx, 3) + -0.000393196 * y * dx * dy +
                   -2.14123e-06 * lens_ipow(y, 2) * dx + -0.00078138 * x * lens_ipow(dx, 2) + -4.5269e-06 * x * y * dy +
                   -4.04496e-08 * x * lens_ipow(y, 2) + -8.95135e-06 * lens_ipow(x, 2) * dx +
                   7.66199e-12 * x * lens_ipow(y, 4) + -1.23629e-06 * lens_ipow(x, 3) * lens_ipow(dy, 2) +
                   -2.16262e-10 * lens_ipow(x, 5) * lambda + -1.48691e-09 * x * lens_ipow(y, 4) * lens_ipow(dy, 2) +
                   -2.1573e-09 * lens_ipow(x, 3) * lens_ipow(y, 2) * lens_ipow(dx, 2) + 0.0f;
const float dx41 = +1.67701e-07 + -0.000296007 * dy + -5.89373e-06 * y + -0.0187968 * lens_ipow(dy, 3) +
                   -0.000795512 * y * lens_ipow(dy, 2) + -9.24e-06 * lens_ipow(y, 2) * dy + -0.000393196 * x * dx * dy +
                   -4.28245e-06 * x * y * dx + -2.26345e-06 * lens_ipow(x, 2) * dy +
                   -4.04496e-08 * lens_ipow(x, 2) * y + -0.216174 * lens_ipow(dx, 4) * dy +
                   -8.75565e-07 * lens_ipow(y, 3) * lens_ipow(dx, 2) + -1.25825e-10 * lens_ipow(y, 5) +
                   1.5324e-11 * lens_ipow(x, 2) * lens_ipow(y, 3) +
                   -2.97381e-09 * lens_ipow(x, 2) * lens_ipow(y, 3) * lens_ipow(dy, 2) +
                   -1.07865e-09 * lens_ipow(x, 4) * y * lens_ipow(dx, 2) +
                   -1.32335e-10 * lens_ipow(y, 5) * lens_ipow(lambda, 3) + -0.331237 * y * lens_ipow(dx, 8) + 0.0f;
const float dx42 =
    +-3.09921e-06 + -0.058521 * dx + -0.000278623 * x + -1.43246e-05 * x * dy + 0.699987 * dx * lens_ipow(dy, 2) +
    -0.00989688 * x * lens_ipow(dy, 2) + -0.0539427 * x * lens_ipow(dx, 2) + -0.000393196 * x * y * dy +
    -2.14123e-06 * x * lens_ipow(y, 2) + -0.00078138 * lens_ipow(x, 2) * dx + -2.98378e-06 * lens_ipow(x, 3) +
    -14.264 * lens_ipow(dx, 5) + -0.864698 * y * lens_ipow(dx, 3) * dy + -4.37783e-07 * lens_ipow(y, 4) * dx +
    -1357.49 * lens_ipow(dx, 5) * lens_ipow(dy, 2) + -1.07865e-09 * lens_ipow(x, 4) * lens_ipow(y, 2) * dx +
    -18890.8 * lens_ipow(dx, 3) * lens_ipow(dy, 6) + -1.32495 * lens_ipow(y, 2) * lens_ipow(dx, 7) + 0.0f;
const float dx43 = +-0.0587568 * dy + -0.000296007 * y + -1.43246e-05 * x * dx + 0.699987 * lens_ipow(dx, 2) * dy +
                   -0.0563903 * y * lens_ipow(dy, 2) + -0.000795512 * lens_ipow(y, 2) * dy +
                   -3.08e-06 * lens_ipow(y, 3) + -0.0197938 * x * dx * dy + -0.000393196 * x * y * dx +
                   -2.26345e-06 * lens_ipow(x, 2) * y + -21.5451 * lens_ipow(dy, 5) + -0.216174 * y * lens_ipow(dx, 4) +
                   -6.18147e-07 * lens_ipow(x, 4) * dy + -452.497 * lens_ipow(dx, 6) * dy +
                   -1.48691e-09 * lens_ipow(x, 2) * lens_ipow(y, 4) * dy +
                   -28336.2 * lens_ipow(dx, 4) * lens_ipow(dy, 5) + 0.0f;
const float dx44 = +0.200766 + -0.484486 * lens_ipow(lambda, 2) + -3.60437e-11 * lens_ipow(x, 6) +
                   -6.61674e-11 * lens_ipow(y, 6) * lens_ipow(lambda, 2) + 3.06143 * lens_ipow(lambda, 10) + 0.0f;
