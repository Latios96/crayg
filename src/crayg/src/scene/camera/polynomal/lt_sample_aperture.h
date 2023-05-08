// input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture
// output: [x,y,dx,dy] point and direction on sensor
#ifndef DEBUG_LOG
#define DEBUG_LOG
#endif
float view[3] = {scene_x, scene_y, scene_z + lens_outer_pupil_curvature_radius};
normalise(view);
int error = 0;
if (1 || view[2] >= lens_field_of_view) {
    const float eps = 1e-8;
    float sqr_err = 1e30, sqr_ap_err = 1e30;
    float prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
    for (int k = 0; k < 100 && (sqr_err > eps || sqr_ap_err > eps) && error == 0; k++) {
        prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
        const float begin_x = x;
        const float begin_y = y;
        const float begin_dx = dx;
        const float begin_dy = dy;
        const float begin_lambda = lambda;
        const float pred_ap[2] = {
            +0.000135404 + 102.533 * begin_dx + -6.98437e-06 * begin_y + 0.852921 * begin_x +
                -0.000167247 * begin_y * begin_dx + 0.000124527 * begin_x * begin_dx +
                -2.71154e-06 * begin_x * begin_y + 93.3834 * begin_dx * lens_ipow(begin_dy, 2) +
                93.9527 * lens_ipow(begin_dx, 3) + 2.77587 * begin_y * begin_dx * begin_dy +
                0.0140524 * lens_ipow(begin_y, 2) * begin_dx + 1.30552 * begin_x * lens_ipow(begin_dy, 2) +
                4.19041 * begin_x * lens_ipow(begin_dx, 2) + 0.0274398 * begin_x * begin_y * begin_dy +
                3.07262e-05 * begin_x * lens_ipow(begin_y, 2) + 0.0423831 * lens_ipow(begin_x, 2) * begin_dx +
                3.40673e-05 * lens_ipow(begin_x, 3) + -0.0148531 * begin_x * lens_ipow(begin_lambda, 3) +
                -0.6378 * begin_dx * lens_ipow(begin_lambda, 4) +
                0.000421551 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dy, 2) +
                0.000503246 * lens_ipow(begin_x, 2) * begin_y * begin_dx * begin_dy +
                0.000148147 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 2) +
                2.40487e-06 * lens_ipow(begin_x, 3) * begin_y * begin_dy +
                -5.91978 * begin_x * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 2) * begin_lambda +
                -0.00269224 * lens_ipow(begin_x, 2) * begin_dx * lens_ipow(begin_lambda, 3) +
                -3385.02 * lens_ipow(begin_dx, 5) * lens_ipow(begin_dy, 2) +
                0.634207 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 2) +
                -14.25 * begin_x * lens_ipow(begin_dy, 6) +
                -9.02734 * begin_x * lens_ipow(begin_dx, 4) * lens_ipow(begin_lambda, 2) +
                5.06585e-09 * begin_x * lens_ipow(begin_y, 5) * begin_dy +
                7.75464e-07 * lens_ipow(begin_x, 5) * lens_ipow(begin_dx, 2) +
                -40423.4 * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 6) +
                0.760605 * begin_x * begin_y * lens_ipow(begin_dx, 4) * begin_dy * lens_ipow(begin_lambda, 2) +
                1.50009e-09 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) +
                -6.29747e-13 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 4) + -1.51622e-13 * lens_ipow(begin_x, 9) +
                -9863.71 * lens_ipow(begin_dx, 7) * lens_ipow(begin_lambda, 4) +
                -7.32537e-14 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 8) * begin_dx +
                7.85724e-05 * lens_ipow(begin_x, 3) * lens_ipow(begin_lambda, 8) +
                1.99145e-07 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 2) * lens_ipow(begin_lambda, 6),
            +5.49149e-06 + 102.517 * begin_dy + 0.853298 * begin_y + -0.000190277 * begin_y * begin_dy +
                -2.89618e-06 * lens_ipow(begin_y, 2) + 94.8049 * lens_ipow(begin_dy, 3) +
                95.0505 * lens_ipow(begin_dx, 2) * begin_dy + 4.14295 * begin_y * lens_ipow(begin_dy, 2) +
                1.32585 * begin_y * lens_ipow(begin_dx, 2) + 0.0420256 * lens_ipow(begin_y, 2) * begin_dy +
                3.41119e-05 * lens_ipow(begin_y, 3) + 2.799 * begin_x * begin_dx * begin_dy +
                0.0277656 * begin_x * begin_y * begin_dx + 0.014278 * lens_ipow(begin_x, 2) * begin_dy +
                3.06987e-05 * lens_ipow(begin_x, 2) * begin_y + -0.0174172 * begin_y * lens_ipow(begin_lambda, 3) +
                -0.786573 * begin_dy * lens_ipow(begin_lambda, 4) +
                0.000499806 * begin_x * lens_ipow(begin_y, 2) * begin_dx * begin_dy +
                0.000103374 * lens_ipow(begin_x, 2) * begin_y * lens_ipow(begin_dy, 2) +
                -1290.56 * lens_ipow(begin_dx, 6) * begin_dy +
                0.386246 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 3) +
                1.11921e-06 * lens_ipow(begin_y, 5) * lens_ipow(begin_dy, 2) +
                -0.00518931 * lens_ipow(begin_x, 3) * lens_ipow(begin_dx, 3) * begin_dy +
                1.8857e-06 * lens_ipow(begin_x, 4) * begin_y * lens_ipow(begin_dx, 2) +
                -6.00427 * begin_y * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 3) +
                -138.659 * begin_y * lens_ipow(begin_dx, 4) * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 2) +
                -178.461 * begin_y * lens_ipow(begin_dx, 8) +
                -0.0702456 * lens_ipow(begin_y, 3) * lens_ipow(begin_dy, 6) + -1.49786e-13 * lens_ipow(begin_y, 9) +
                2.60457 * begin_x * begin_y * begin_dx * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 2) +
                -1.38782e-07 * begin_x * lens_ipow(begin_y, 5) * begin_dx * lens_ipow(begin_dy, 2) +
                5.40946e-05 * lens_ipow(begin_x, 2) * begin_y * lens_ipow(begin_lambda, 6) +
                -3.46082e-09 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 2) * begin_dy +
                -6.8529e-13 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 5) +
                4.39957e-11 * lens_ipow(begin_x, 7) * begin_y * begin_dx +
                -9.55573e-12 * lens_ipow(begin_x, 8) * begin_dy +
                -16582.9 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 5) * lens_ipow(begin_lambda, 3) +
                -48491.5 * lens_ipow(begin_dy, 9) * lens_ipow(begin_lambda, 2) +
                0.000152732 * lens_ipow(begin_y, 3) * lens_ipow(begin_lambda, 8) +
                -7.96763e-11 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 4) * begin_dy * lens_ipow(begin_lambda, 2)};
        const float delta_ap[] = {ap_x - pred_ap[0], ap_y - pred_ap[1]};
        sqr_ap_err = delta_ap[0] * delta_ap[0] + delta_ap[1] * delta_ap[1];
        float dx1_domega0[2][2];
        dx1_domega0[0][0] =
            +102.533 + -0.000167247 * begin_y + 0.000124527 * begin_x + 93.3834 * lens_ipow(begin_dy, 2) +
            281.858 * lens_ipow(begin_dx, 2) + 2.77587 * begin_y * begin_dy + 0.0140524 * lens_ipow(begin_y, 2) +
            8.38082 * begin_x * begin_dx + 0.0423831 * lens_ipow(begin_x, 2) + -0.6378 * lens_ipow(begin_lambda, 4) +
            0.000503246 * lens_ipow(begin_x, 2) * begin_y * begin_dy +
            -11.8396 * begin_x * begin_dx * lens_ipow(begin_dy, 2) * begin_lambda +
            -0.00269224 * lens_ipow(begin_x, 2) * lens_ipow(begin_lambda, 3) +
            -16925.1 * lens_ipow(begin_dx, 4) * lens_ipow(begin_dy, 2) +
            1.90262 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 2) +
            -36.1094 * begin_x * lens_ipow(begin_dx, 3) * lens_ipow(begin_lambda, 2) +
            1.55093e-06 * lens_ipow(begin_x, 5) * begin_dx + -121270 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 6) +
            3.04242 * begin_x * begin_y * lens_ipow(begin_dx, 3) * begin_dy * lens_ipow(begin_lambda, 2) +
            3.00019e-09 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 2) * begin_dx +
            -69045.9 * lens_ipow(begin_dx, 6) * lens_ipow(begin_lambda, 4) +
            -7.32537e-14 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 8) + 0.0f;
        dx1_domega0[0][1] =
            +186.767 * begin_dx * begin_dy + 2.77587 * begin_y * begin_dx + 2.61103 * begin_x * begin_dy +
            0.0274398 * begin_x * begin_y + 0.000843102 * begin_x * lens_ipow(begin_y, 2) * begin_dy +
            0.000503246 * lens_ipow(begin_x, 2) * begin_y * begin_dx + 0.000296294 * lens_ipow(begin_x, 3) * begin_dy +
            2.40487e-06 * lens_ipow(begin_x, 3) * begin_y +
            -11.8396 * begin_x * lens_ipow(begin_dx, 2) * begin_dy * begin_lambda +
            -6770.03 * lens_ipow(begin_dx, 5) * begin_dy +
            1.26841 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) * begin_dy +
            -85.4999 * begin_x * lens_ipow(begin_dy, 5) + 5.06585e-09 * begin_x * lens_ipow(begin_y, 5) +
            -242541 * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 5) +
            0.760605 * begin_x * begin_y * lens_ipow(begin_dx, 4) * lens_ipow(begin_lambda, 2) + 0.0f;
        dx1_domega0[1][0] =
            +190.101 * begin_dx * begin_dy + 2.65171 * begin_y * begin_dx + 2.799 * begin_x * begin_dy +
            0.0277656 * begin_x * begin_y + 0.000499806 * begin_x * lens_ipow(begin_y, 2) * begin_dy +
            -7743.36 * lens_ipow(begin_dx, 5) * begin_dy +
            0.772492 * lens_ipow(begin_y, 2) * begin_dx * lens_ipow(begin_dy, 3) +
            -0.0155679 * lens_ipow(begin_x, 3) * lens_ipow(begin_dx, 2) * begin_dy +
            3.7714e-06 * lens_ipow(begin_x, 4) * begin_y * begin_dx +
            -554.637 * begin_y * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 2) +
            -1427.69 * begin_y * lens_ipow(begin_dx, 7) +
            2.60457 * begin_x * begin_y * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 2) +
            -1.38782e-07 * begin_x * lens_ipow(begin_y, 5) * lens_ipow(begin_dy, 2) +
            -6.92164e-09 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 4) * begin_dx * begin_dy +
            4.39957e-11 * lens_ipow(begin_x, 7) * begin_y +
            -33165.9 * begin_dx * lens_ipow(begin_dy, 5) * lens_ipow(begin_lambda, 3) + 0.0f;
        dx1_domega0[1][1] =
            +102.517 + -0.000190277 * begin_y + 284.415 * lens_ipow(begin_dy, 2) + 95.0505 * lens_ipow(begin_dx, 2) +
            8.28589 * begin_y * begin_dy + 0.0420256 * lens_ipow(begin_y, 2) + 2.799 * begin_x * begin_dx +
            0.014278 * lens_ipow(begin_x, 2) + -0.786573 * lens_ipow(begin_lambda, 4) +
            0.000499806 * begin_x * lens_ipow(begin_y, 2) * begin_dx +
            0.000206748 * lens_ipow(begin_x, 2) * begin_y * begin_dy + -1290.56 * lens_ipow(begin_dx, 6) +
            1.15874 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 2) +
            2.23843e-06 * lens_ipow(begin_y, 5) * begin_dy +
            -0.00518931 * lens_ipow(begin_x, 3) * lens_ipow(begin_dx, 3) +
            -24.0171 * begin_y * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 3) +
            -277.319 * begin_y * lens_ipow(begin_dx, 4) * begin_dy * lens_ipow(begin_lambda, 2) +
            -0.421474 * lens_ipow(begin_y, 3) * lens_ipow(begin_dy, 5) +
            10.4183 * begin_x * begin_y * begin_dx * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 2) +
            -2.77565e-07 * begin_x * lens_ipow(begin_y, 5) * begin_dx * begin_dy +
            -3.46082e-09 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 2) +
            -9.55573e-12 * lens_ipow(begin_x, 8) +
            -82914.7 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 3) +
            -436424 * lens_ipow(begin_dy, 8) * lens_ipow(begin_lambda, 2) +
            -7.96763e-11 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 4) * lens_ipow(begin_lambda, 2) + 0.0f;
        float invApJ[2][2];
        const float invdetap = 1.0f / (dx1_domega0[0][0] * dx1_domega0[1][1] - dx1_domega0[0][1] * dx1_domega0[1][0]);
        invApJ[0][0] = dx1_domega0[1][1] * invdetap;
        invApJ[1][1] = dx1_domega0[0][0] * invdetap;
        invApJ[0][1] = -dx1_domega0[0][1] * invdetap;
        invApJ[1][0] = -dx1_domega0[1][0] * invdetap;
        for (int i = 0; i < 2; i++) {
            dx += invApJ[0][i] * delta_ap[i];
            dy += invApJ[1][i] * delta_ap[i];
        }
        out[0] = +0.000254046 + 70.2621 * begin_dx + -2.46041e-05 * begin_y + -0.653785 * begin_x +
                 -0.0235419 * begin_dx * begin_dy + -0.000406297 * begin_y * begin_dx +
                 -4.64643e-06 * begin_x * begin_y + -19.2784 * begin_dx * lens_ipow(begin_dy, 2) +
                 -19.82 * lens_ipow(begin_dx, 3) + 0.271375 * begin_y * begin_dx * begin_dy +
                 0.00259458 * lens_ipow(begin_y, 2) * begin_dx + 0.24179 * begin_x * lens_ipow(begin_dy, 2) +
                 0.483653 * begin_x * lens_ipow(begin_dx, 2) + 0.00548671 * begin_x * begin_y * begin_dy +
                 -0.000142526 * begin_x * lens_ipow(begin_y, 2) + 0.00788821 * lens_ipow(begin_x, 2) * begin_dx +
                 -0.000143924 * lens_ipow(begin_x, 3) + 0.00012271 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) +
                 -0.0935941 * begin_x * lens_ipow(begin_lambda, 3) +
                 -3.01594e-08 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) +
                 4.14766e-06 * lens_ipow(begin_y, 4) * begin_dx +
                 -0.0798356 * begin_x * begin_y * lens_ipow(begin_dx, 2) * begin_dy +
                 0.000656535 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) +
                 1.71389e-05 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) * begin_dx +
                 0.000298779 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 2) +
                 0.000338911 * lens_ipow(begin_x, 3) * lens_ipow(begin_dx, 2) +
                 -5.89847e-05 * lens_ipow(begin_y, 4) * begin_dx * lens_ipow(begin_dy, 2) +
                 -0.0934762 * begin_x * begin_y * lens_ipow(begin_dy, 5) +
                 0.773937 * lens_ipow(begin_x, 2) * begin_dx * lens_ipow(begin_dy, 4) +
                 -0.00625431 * begin_x * begin_y * begin_dy * lens_ipow(begin_lambda, 5) +
                 -2.47424 * begin_dx * lens_ipow(begin_lambda, 8) +
                 6777.63 * lens_ipow(begin_dx, 5) * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 2) +
                 3.73331 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 7) +
                 7.79113e-11 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 5) * begin_dy +
                 -6.40108e-09 * lens_ipow(begin_x, 6) * begin_y * begin_dx * begin_dy +
                 4.56487e-11 * lens_ipow(begin_x, 8) * begin_dx +
                 -0.271363 * lens_ipow(begin_x, 2) * begin_dx * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 5) +
                 -5.136e-05 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) * begin_dx * lens_ipow(begin_lambda, 5) +
                 0.440288 * begin_x * lens_ipow(begin_lambda, 10) +
                 1.02649 * begin_x * begin_y * lens_ipow(begin_dx, 2) * begin_dy * lens_ipow(begin_lambda, 6);
        out[1] = +0.000211899 + 70.217 * begin_dy + -0.00131007 * begin_dx + -0.654816 * begin_y +
                 0.0249627 * begin_dx * begin_dy + -4.52947e-06 * lens_ipow(begin_y, 2) +
                 -2.06877e-06 * begin_x * begin_y + -15.978 * lens_ipow(begin_dy, 3) +
                 -18.8599 * lens_ipow(begin_dx, 2) * begin_dy + 0.66145 * begin_y * lens_ipow(begin_dy, 2) +
                 0.288328 * begin_y * lens_ipow(begin_dx, 2) + 0.0101163 * lens_ipow(begin_y, 2) * begin_dy +
                 -0.000131314 * lens_ipow(begin_y, 3) + 0.314697 * begin_x * begin_dx * begin_dy +
                 0.00535997 * begin_x * begin_y * begin_dx + -2.17044e-07 * begin_x * lens_ipow(begin_y, 2) +
                 0.00272703 * lens_ipow(begin_x, 2) * begin_dy + -0.000141901 * lens_ipow(begin_x, 2) * begin_y +
                 -0.0993725 * begin_y * lens_ipow(begin_lambda, 3) +
                 0.000963962 * lens_ipow(begin_x, 2) * begin_y * lens_ipow(begin_dy, 2) +
                 1.87395e-05 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) * begin_dy +
                 3.89311e-06 * lens_ipow(begin_x, 4) * begin_dy +
                 -0.0193591 * lens_ipow(begin_y, 2) * begin_dy * lens_ipow(begin_lambda, 4) +
                 -5.31328e-05 * lens_ipow(begin_x, 4) * lens_ipow(begin_dx, 2) * begin_dy +
                 -1.35534e-07 * lens_ipow(begin_y, 5) * lens_ipow(begin_lambda, 3) +
                 -0.00550353 * begin_x * begin_y * begin_dx * lens_ipow(begin_lambda, 5) +
                 -2.27579 * begin_dy * lens_ipow(begin_lambda, 8) +
                 407.064 * lens_ipow(begin_dx, 4) * begin_dy * lens_ipow(begin_lambda, 4) +
                 2.25478e-11 * lens_ipow(begin_y, 8) * begin_dy +
                 -1.9655e-05 * begin_x * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 3) * begin_dy +
                 6.1607 * lens_ipow(begin_x, 2) * lens_ipow(begin_dy, 7) +
                 1.4509e-05 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 3) * lens_ipow(begin_dx, 4) +
                 -0.00206173 * lens_ipow(begin_x, 3) * begin_y * begin_dx * lens_ipow(begin_dy, 4) +
                 5.7944e-11 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 5) * begin_dx +
                 3.4903e-11 * lens_ipow(begin_x, 7) * begin_y * begin_dx +
                 -13.0414 * begin_x * begin_dx * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 5) +
                 -2.49594e-05 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) * begin_dy * lens_ipow(begin_lambda, 5) +
                 -1071.33 * lens_ipow(begin_dy, 5) * lens_ipow(begin_lambda, 6) +
                 0.561402 * begin_y * lens_ipow(begin_lambda, 10) +
                 -6.76315 * begin_y * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 8);
        out[2] = +1.05262e-06 + -0.257738 * begin_dx + -8.81348e-08 * begin_y + -0.0118191 * begin_x +
                 -0.000115592 * begin_dx * begin_dy + -2.15491e-06 * begin_y * begin_dx +
                 8.31513e-07 * begin_x * begin_dx + 0.232364 * begin_dx * lens_ipow(begin_dy, 2) +
                 0.240032 * lens_ipow(begin_dx, 3) + 0.00303916 * begin_y * begin_dx * begin_dy +
                 2.81591e-05 * lens_ipow(begin_y, 2) * begin_dx + 0.000690185 * begin_x * lens_ipow(begin_dy, 2) +
                 0.0039607 * begin_x * lens_ipow(begin_dx, 2) + 2.02434e-05 * begin_x * begin_y * begin_dy +
                 8.81861e-07 * begin_x * lens_ipow(begin_y, 2) + 4.65422e-05 * lens_ipow(begin_x, 2) * begin_dx +
                 8.94173e-07 * lens_ipow(begin_x, 3) + -0.00738288 * begin_dx * lens_ipow(begin_lambda, 3) +
                 0.000265839 * begin_x * lens_ipow(begin_lambda, 3) +
                 -0.000209262 * begin_x * begin_y * lens_ipow(begin_dx, 2) * begin_dy +
                 -9.16879e-07 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dy, 2) +
                 -7.43012e-06 * lens_ipow(begin_x, 2) * begin_y * begin_dx * begin_dy +
                 -4.00891e-08 * lens_ipow(begin_x, 3) * begin_y * begin_dy +
                 -7.59538e-05 * begin_x * begin_y * begin_dy * lens_ipow(begin_lambda, 4) +
                 -0.000162533 * lens_ipow(begin_x, 2) * begin_dx * lens_ipow(begin_lambda, 4) +
                 3.33057e-09 * lens_ipow(begin_x, 5) * lens_ipow(begin_dy, 2) +
                 -0.0112075 * begin_y * begin_dx * begin_dy * lens_ipow(begin_lambda, 5) +
                 0.0721126 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 4) +
                 8.39134e-06 * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 5) +
                 -0.0354275 * begin_x * lens_ipow(begin_dx, 2) * lens_ipow(begin_lambda, 6) +
                 -3.30717e-09 * begin_x * lens_ipow(begin_y, 5) * lens_ipow(begin_dx, 2) * begin_dy +
                 6.03832e-15 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 4) +
                 -5.11682 * begin_dx * lens_ipow(begin_dy, 4) * lens_ipow(begin_lambda, 5) +
                 -12.3137 * lens_ipow(begin_dx, 5) * lens_ipow(begin_lambda, 6) + 658.794 * lens_ipow(begin_dx, 11) +
                 -0.00243157 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 3) * lens_ipow(begin_lambda, 6) +
                 -0.00104482 * begin_x * lens_ipow(begin_lambda, 10) +
                 -0.00339056 * lens_ipow(begin_x, 2) * begin_dx * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 6) +
                 -4.71681e-05 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 6) +
                 -3.54124e-09 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 2) * lens_ipow(begin_lambda, 6);
        out[3] = +1.15543e-06 + -0.258097 * begin_dy + -0.0118279 * begin_y + -1.35996e-06 * begin_y * begin_dy +
                 -1.53951e-08 * lens_ipow(begin_x, 2) + 0.244621 * lens_ipow(begin_dy, 3) +
                 0.239714 * lens_ipow(begin_dx, 2) * begin_dy + 0.00440131 * begin_y * lens_ipow(begin_dy, 2) +
                 0.000853338 * begin_y * lens_ipow(begin_dx, 2) + 5.55721e-05 * lens_ipow(begin_y, 2) * begin_dy +
                 9.19063e-07 * lens_ipow(begin_y, 3) + 0.00344002 * begin_x * begin_dx * begin_dy +
                 1.51788e-05 * begin_x * begin_y * begin_dx + 2.21063e-05 * lens_ipow(begin_x, 2) * begin_dy +
                 9.66176e-07 * lens_ipow(begin_x, 2) * begin_y + -0.00565525 * begin_dy * lens_ipow(begin_lambda, 3) +
                 0.000293436 * begin_y * lens_ipow(begin_lambda, 3) +
                 7.11113e-05 * begin_x * begin_y * lens_ipow(begin_dx, 3) +
                 -2.17036e-06 * begin_x * lens_ipow(begin_y, 2) * begin_dx * begin_dy +
                 14.9837 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 5) +
                 -0.000232937 * lens_ipow(begin_y, 2) * begin_dy * lens_ipow(begin_lambda, 4) +
                 -0.00012057 * begin_x * begin_y * begin_dx * lens_ipow(begin_lambda, 4) +
                 9.71525e-07 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * begin_dy +
                 -1.28308e-06 * lens_ipow(begin_x, 3) * begin_y * begin_dx * lens_ipow(begin_dy, 2) +
                 -0.014953 * begin_x * begin_dx * begin_dy * lens_ipow(begin_lambda, 5) +
                 -7.18392e-07 * lens_ipow(begin_x, 2) * begin_y * lens_ipow(begin_lambda, 5) +
                 406.921 * lens_ipow(begin_dx, 6) * lens_ipow(begin_dy, 3) +
                 -0.0438216 * begin_y * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 6) +
                 -0.0120327 * begin_y * lens_ipow(begin_dx, 2) * lens_ipow(begin_lambda, 6) +
                 7.71629e-08 * lens_ipow(begin_y, 5) * lens_ipow(begin_dx, 4) + 1.45693e-15 * lens_ipow(begin_y, 9) +
                 9.93437e-06 * lens_ipow(begin_x, 4) * lens_ipow(begin_dy, 5) +
                 6.17162e-15 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 5) +
                 -13.6236 * lens_ipow(begin_dy, 5) * lens_ipow(begin_lambda, 6) + 713.085 * lens_ipow(begin_dy, 11) +
                 -21.6029 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 6) +
                 -13.9192 * lens_ipow(begin_dx, 4) * begin_dy * lens_ipow(begin_lambda, 6) +
                 -0.000519216 * begin_y * lens_ipow(begin_lambda, 10) +
                 -4.50146e-09 * lens_ipow(begin_y, 5) * lens_ipow(begin_lambda, 6) +
                 -0.00283106 * lens_ipow(begin_x, 2) * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 6);
        float pred_out_cs[7] = {0.0f};
        lens_sphereToCs(out, out + 2, pred_out_cs, pred_out_cs + 3, -lens_outer_pupil_curvature_radius,
                        lens_outer_pupil_curvature_radius);
        float view[3] = {scene_x - pred_out_cs[0], scene_y - pred_out_cs[1], scene_z - pred_out_cs[2]};
        normalise(view);
        float out_new[5];
        lens_csToSphere(pred_out_cs, view, out_new, out_new + 2, -lens_outer_pupil_curvature_radius,
                        lens_outer_pupil_curvature_radius);
        const float delta_out[] = {out_new[2] - out[2], out_new[3] - out[3]};
        sqr_err = delta_out[0] * delta_out[0] + delta_out[1] * delta_out[1];
        float domega2_dx0[2][2];
        domega2_dx0[0][0] =
            +-0.0118191 + 8.31513e-07 * begin_dx + 0.000690185 * lens_ipow(begin_dy, 2) +
            0.0039607 * lens_ipow(begin_dx, 2) + 2.02434e-05 * begin_y * begin_dy +
            8.81861e-07 * lens_ipow(begin_y, 2) + 9.30843e-05 * begin_x * begin_dx +
            2.68252e-06 * lens_ipow(begin_x, 2) + 0.000265839 * lens_ipow(begin_lambda, 3) +
            -0.000209262 * begin_y * lens_ipow(begin_dx, 2) * begin_dy +
            -9.16879e-07 * lens_ipow(begin_y, 2) * lens_ipow(begin_dy, 2) +
            -1.48602e-05 * begin_x * begin_y * begin_dx * begin_dy +
            -1.20267e-07 * lens_ipow(begin_x, 2) * begin_y * begin_dy +
            -7.59538e-05 * begin_y * begin_dy * lens_ipow(begin_lambda, 4) +
            -0.000325066 * begin_x * begin_dx * lens_ipow(begin_lambda, 4) +
            1.66529e-08 * lens_ipow(begin_x, 4) * lens_ipow(begin_dy, 2) +
            -0.0354275 * lens_ipow(begin_dx, 2) * lens_ipow(begin_lambda, 6) +
            -3.30717e-09 * lens_ipow(begin_y, 5) * lens_ipow(begin_dx, 2) * begin_dy +
            3.01916e-14 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 4) + -0.00104482 * lens_ipow(begin_lambda, 10) +
            -0.00678111 * begin_x * begin_dx * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 6) +
            -0.000141504 * lens_ipow(begin_x, 2) * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 6) +
            -1.06237e-08 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) * lens_ipow(begin_lambda, 6) + 0.0f;
        domega2_dx0[0][1] = +-8.81348e-08 + -2.15491e-06 * begin_dx + 0.00303916 * begin_dx * begin_dy +
                            5.63182e-05 * begin_y * begin_dx + 2.02434e-05 * begin_x * begin_dy +
                            1.76372e-06 * begin_x * begin_y +
                            -0.000209262 * begin_x * lens_ipow(begin_dx, 2) * begin_dy +
                            -1.83376e-06 * begin_x * begin_y * lens_ipow(begin_dy, 2) +
                            -7.43012e-06 * lens_ipow(begin_x, 2) * begin_dx * begin_dy +
                            -4.00891e-08 * lens_ipow(begin_x, 3) * begin_dy +
                            -7.59538e-05 * begin_x * begin_dy * lens_ipow(begin_lambda, 4) +
                            -0.0112075 * begin_dx * begin_dy * lens_ipow(begin_lambda, 5) +
                            0.144225 * begin_y * lens_ipow(begin_dx, 3) * lens_ipow(begin_dy, 4) +
                            3.35653e-05 * lens_ipow(begin_y, 3) * lens_ipow(begin_dx, 5) +
                            -1.65359e-08 * begin_x * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 2) * begin_dy +
                            2.41533e-14 * lens_ipow(begin_x, 5) * lens_ipow(begin_y, 3) +
                            -0.00486313 * begin_y * lens_ipow(begin_dx, 3) * lens_ipow(begin_lambda, 6) +
                            -7.08248e-09 * lens_ipow(begin_x, 3) * begin_y * lens_ipow(begin_lambda, 6) + 0.0f;
        domega2_dx0[1][0] = +-3.07902e-08 * begin_x + 0.00344002 * begin_dx * begin_dy +
                            1.51788e-05 * begin_y * begin_dx + 4.42126e-05 * begin_x * begin_dy +
                            1.93235e-06 * begin_x * begin_y + 7.11113e-05 * begin_y * lens_ipow(begin_dx, 3) +
                            -2.17036e-06 * lens_ipow(begin_y, 2) * begin_dx * begin_dy +
                            -0.00012057 * begin_y * begin_dx * lens_ipow(begin_lambda, 4) +
                            1.94305e-06 * begin_x * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) * begin_dy +
                            -3.84924e-06 * lens_ipow(begin_x, 2) * begin_y * begin_dx * lens_ipow(begin_dy, 2) +
                            -0.014953 * begin_dx * begin_dy * lens_ipow(begin_lambda, 5) +
                            -1.43678e-06 * begin_x * begin_y * lens_ipow(begin_lambda, 5) +
                            3.97375e-05 * lens_ipow(begin_x, 3) * lens_ipow(begin_dy, 5) +
                            2.46865e-14 * lens_ipow(begin_x, 3) * lens_ipow(begin_y, 5) +
                            -0.00566213 * begin_x * lens_ipow(begin_dy, 3) * lens_ipow(begin_lambda, 6) + 0.0f;
        domega2_dx0[1][1] =
            +-0.0118279 + -1.35996e-06 * begin_dy + 0.00440131 * lens_ipow(begin_dy, 2) +
            0.000853338 * lens_ipow(begin_dx, 2) + 0.000111144 * begin_y * begin_dy +
            2.75719e-06 * lens_ipow(begin_y, 2) + 1.51788e-05 * begin_x * begin_dx +
            9.66176e-07 * lens_ipow(begin_x, 2) + 0.000293436 * lens_ipow(begin_lambda, 3) +
            7.11113e-05 * begin_x * lens_ipow(begin_dx, 3) + -4.34072e-06 * begin_x * begin_y * begin_dx * begin_dy +
            -0.000465874 * begin_y * begin_dy * lens_ipow(begin_lambda, 4) +
            -0.00012057 * begin_x * begin_dx * lens_ipow(begin_lambda, 4) +
            1.94305e-06 * lens_ipow(begin_x, 2) * begin_y * lens_ipow(begin_dx, 2) * begin_dy +
            -1.28308e-06 * lens_ipow(begin_x, 3) * begin_dx * lens_ipow(begin_dy, 2) +
            -7.18392e-07 * lens_ipow(begin_x, 2) * lens_ipow(begin_lambda, 5) +
            -0.0438216 * lens_ipow(begin_dy, 2) * lens_ipow(begin_lambda, 6) +
            -0.0120327 * lens_ipow(begin_dx, 2) * lens_ipow(begin_lambda, 6) +
            3.85815e-07 * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 4) + 1.31124e-14 * lens_ipow(begin_y, 8) +
            3.08581e-14 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 4) + -0.000519216 * lens_ipow(begin_lambda, 10) +
            -2.25073e-08 * lens_ipow(begin_y, 4) * lens_ipow(begin_lambda, 6) + 0.0f;
        float invJ[2][2];
        const float invdet = 1.0f / (domega2_dx0[0][0] * domega2_dx0[1][1] - domega2_dx0[0][1] * domega2_dx0[1][0]);
        invJ[0][0] = domega2_dx0[1][1] * invdet;
        invJ[1][1] = domega2_dx0[0][0] * invdet;
        invJ[0][1] = -domega2_dx0[0][1] * invdet;
        invJ[1][0] = -domega2_dx0[1][0] * invdet;
        for (int i = 0; i < 2; i++) {
            x += invJ[0][i] * delta_out[i];
            y += invJ[1][i] * delta_out[i];
        }
        if (sqr_err > prev_sqr_err) {
            error |= 1;
        }
        if (sqr_ap_err > prev_sqr_ap_err) {
            error |= 2;
        }
        if (out[0] != out[0]) {
            error |= 4;
        }
        if (out[1] != out[1]) {
            error |= 8;
        }
        DEBUG_LOG;
        // reset error code for first few iterations.
        if (k < 10) {
            error = 0;
        }
    }
} else {
    error = 128;
}
if (out[0] * out[0] + out[1] * out[1] > lens_outer_pupil_radius * lens_outer_pupil_radius) {
    error |= 16;
}
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if (error == 0) {
    out[4] =
        +0.047879 + 0.200766 * begin_lambda + -3.09921e-06 * begin_dx + 1.67701e-07 * begin_y + -1.46101e-07 * begin_x +
        -0.0293784 * lens_ipow(begin_dy, 2) + -0.0292605 * lens_ipow(begin_dx, 2) + -0.000296007 * begin_y * begin_dy +
        -2.94687e-06 * lens_ipow(begin_y, 2) + -0.000278623 * begin_x * begin_dx +
        -3.10662e-06 * lens_ipow(begin_x, 2) + -0.161495 * lens_ipow(begin_lambda, 3) +
        -1.43246e-05 * begin_x * begin_dx * begin_dy + 0.349993 * lens_ipow(begin_dx, 2) * lens_ipow(begin_dy, 2) +
        -0.0187968 * begin_y * lens_ipow(begin_dy, 3) + -0.000397756 * lens_ipow(begin_y, 2) * lens_ipow(begin_dy, 2) +
        -3.08e-06 * lens_ipow(begin_y, 3) * begin_dy + -0.00989688 * begin_x * begin_dx * lens_ipow(begin_dy, 2) +
        -0.0179809 * begin_x * lens_ipow(begin_dx, 3) + -0.000393196 * begin_x * begin_y * begin_dx * begin_dy +
        -2.14123e-06 * begin_x * lens_ipow(begin_y, 2) * begin_dx +
        -0.00039069 * lens_ipow(begin_x, 2) * lens_ipow(begin_dx, 2) +
        -2.26345e-06 * lens_ipow(begin_x, 2) * begin_y * begin_dy +
        -2.02248e-08 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 2) + -2.98378e-06 * lens_ipow(begin_x, 3) * begin_dx +
        -3.59086 * lens_ipow(begin_dy, 6) + -2.37733 * lens_ipow(begin_dx, 6) +
        -0.216174 * begin_y * lens_ipow(begin_dx, 4) * begin_dy +
        -2.18891e-07 * lens_ipow(begin_y, 4) * lens_ipow(begin_dx, 2) + -2.09708e-11 * lens_ipow(begin_y, 6) +
        3.83099e-12 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 4) +
        -3.09074e-07 * lens_ipow(begin_x, 4) * lens_ipow(begin_dy, 2) +
        -3.60437e-11 * lens_ipow(begin_x, 6) * begin_lambda +
        -226.248 * lens_ipow(begin_dx, 6) * lens_ipow(begin_dy, 2) +
        -7.43453e-10 * lens_ipow(begin_x, 2) * lens_ipow(begin_y, 4) * lens_ipow(begin_dy, 2) +
        -5.39325e-10 * lens_ipow(begin_x, 4) * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 2) +
        -2.20558e-11 * lens_ipow(begin_y, 6) * lens_ipow(begin_lambda, 3) +
        -4722.7 * lens_ipow(begin_dx, 4) * lens_ipow(begin_dy, 6) +
        -0.165618 * lens_ipow(begin_y, 2) * lens_ipow(begin_dx, 8) + 0.278312 * lens_ipow(begin_lambda, 11);
} else {
    out[4] = 0.0f;
}
