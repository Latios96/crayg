#pragma once

#define CRAYG_EXPAND(x) x

#define CRAYG_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,     \
                        _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
                        _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, \
                        _59, _60, _61, _62, _63, _64, NAME, ...)                                                       \
    NAME

#define CRAYG_FOREACH_VARARG(...)                                                                                      \
    CRAYG_EXPAND(CRAYG_GET_MACRO(                                                                                      \
        __VA_ARGS__, CRAYG_PASTE64, CRAYG_PASTE63, CRAYG_PASTE62, CRAYG_PASTE61, CRAYG_PASTE60, CRAYG_PASTE59,         \
        CRAYG_PASTE58, CRAYG_PASTE57, CRAYG_PASTE56, CRAYG_PASTE55, CRAYG_PASTE54, CRAYG_PASTE53, CRAYG_PASTE52,       \
        CRAYG_PASTE51, CRAYG_PASTE50, CRAYG_PASTE49, CRAYG_PASTE48, CRAYG_PASTE47, CRAYG_PASTE46, CRAYG_PASTE45,       \
        CRAYG_PASTE44, CRAYG_PASTE43, CRAYG_PASTE42, CRAYG_PASTE41, CRAYG_PASTE40, CRAYG_PASTE39, CRAYG_PASTE38,       \
        CRAYG_PASTE37, CRAYG_PASTE36, CRAYG_PASTE35, CRAYG_PASTE34, CRAYG_PASTE33, CRAYG_PASTE32, CRAYG_PASTE31,       \
        CRAYG_PASTE30, CRAYG_PASTE29, CRAYG_PASTE28, CRAYG_PASTE27, CRAYG_PASTE26, CRAYG_PASTE25, CRAYG_PASTE24,       \
        CRAYG_PASTE23, CRAYG_PASTE22, CRAYG_PASTE21, CRAYG_PASTE20, CRAYG_PASTE19, CRAYG_PASTE18, CRAYG_PASTE17,       \
        CRAYG_PASTE16, CRAYG_PASTE15, CRAYG_PASTE14, CRAYG_PASTE13, CRAYG_PASTE12, CRAYG_PASTE11, CRAYG_PASTE10,       \
        CRAYG_PASTE9, CRAYG_PASTE8, CRAYG_PASTE7, CRAYG_PASTE6, CRAYG_PASTE5, CRAYG_PASTE4, CRAYG_PASTE3,              \
        CRAYG_PASTE2, CRAYG_PASTE1)(__VA_ARGS__))
#define CRAYG_PASTE2(func, v1) func(v1)
#define CRAYG_PASTE3(func, v1, v2) CRAYG_PASTE2(func, v1) CRAYG_PASTE2(func, v2)
#define CRAYG_PASTE4(func, v1, v2, v3) CRAYG_PASTE2(func, v1) CRAYG_PASTE3(func, v2, v3)
#define CRAYG_PASTE5(func, v1, v2, v3, v4) CRAYG_PASTE2(func, v1) CRAYG_PASTE4(func, v2, v3, v4)
#define CRAYG_PASTE6(func, v1, v2, v3, v4, v5) CRAYG_PASTE2(func, v1) CRAYG_PASTE5(func, v2, v3, v4, v5)
#define CRAYG_PASTE7(func, v1, v2, v3, v4, v5, v6) CRAYG_PASTE2(func, v1) CRAYG_PASTE6(func, v2, v3, v4, v5, v6)
#define CRAYG_PASTE8(func, v1, v2, v3, v4, v5, v6, v7) CRAYG_PASTE2(func, v1) CRAYG_PASTE7(func, v2, v3, v4, v5, v6, v7)
#define CRAYG_PASTE9(func, v1, v2, v3, v4, v5, v6, v7, v8)                                                             \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE8(func, v2, v3, v4, v5, v6, v7, v8)
#define CRAYG_PASTE10(func, v1, v2, v3, v4, v5, v6, v7, v8, v9)                                                        \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE9(func, v2, v3, v4, v5, v6, v7, v8, v9)
#define CRAYG_PASTE11(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)                                                   \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE10(func, v2, v3, v4, v5, v6, v7, v8, v9, v10)
#define CRAYG_PASTE12(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)                                              \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE11(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)
#define CRAYG_PASTE13(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)                                         \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE12(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)
#define CRAYG_PASTE14(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)                                    \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE13(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)
#define CRAYG_PASTE15(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)                               \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE14(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)
#define CRAYG_PASTE16(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)                          \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE15(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)
#define CRAYG_PASTE17(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)                     \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE16(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)
#define CRAYG_PASTE18(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17)                \
    CRAYG_PASTE2(func, v1) CRAYG_PASTE17(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17)
#define CRAYG_PASTE19(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18)           \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE18(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18)
#define CRAYG_PASTE20(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19)      \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE19(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19)
#define CRAYG_PASTE21(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE20(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20)
#define CRAYG_PASTE22(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21)                                                                                             \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE21(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21)
#define CRAYG_PASTE23(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22)                                                                                        \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE22(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22)
#define CRAYG_PASTE24(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23)                                                                                   \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE23(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23)
#define CRAYG_PASTE25(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24)                                                                              \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE24(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24)
#define CRAYG_PASTE26(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25)                                                                         \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE25(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25)
#define CRAYG_PASTE27(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26)                                                                    \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE26(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26)
#define CRAYG_PASTE28(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27)                                                               \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE27(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27)
#define CRAYG_PASTE29(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28)                                                          \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE28(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28)
#define CRAYG_PASTE30(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29)                                                     \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE29(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29)
#define CRAYG_PASTE31(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30)                                                \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE30(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30)
#define CRAYG_PASTE32(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31)                                           \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE31(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31)
#define CRAYG_PASTE33(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32)                                      \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE32(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32)
#define CRAYG_PASTE34(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33)                                 \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE33(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33)
#define CRAYG_PASTE35(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34)                            \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE34(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34)
#define CRAYG_PASTE36(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35)                       \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE35(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35)
#define CRAYG_PASTE37(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36)                  \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE36(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36)
#define CRAYG_PASTE38(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37)             \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE37(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37)
#define CRAYG_PASTE39(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38)        \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE38(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38)
#define CRAYG_PASTE40(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39)   \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE39(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39)
#define CRAYG_PASTE41(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40)                                                                                             \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE40(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40)
#define CRAYG_PASTE42(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41)                                                                                        \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE41(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41)
#define CRAYG_PASTE43(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42)                                                                                   \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE42(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42)
#define CRAYG_PASTE44(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43)                                                                              \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE43(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43)
#define CRAYG_PASTE45(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44)                                                                         \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE44(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44)
#define CRAYG_PASTE46(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45)                                                                    \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE45(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45)
#define CRAYG_PASTE47(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46)                                                               \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE46(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46)
#define CRAYG_PASTE48(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47)                                                          \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE47(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47)
#define CRAYG_PASTE49(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48)                                                     \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE48(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48)
#define CRAYG_PASTE50(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49)                                                \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE49(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49)
#define CRAYG_PASTE51(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50)                                           \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE50(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50)
#define CRAYG_PASTE52(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51)                                      \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE51(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51)
#define CRAYG_PASTE53(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52)                                 \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE52(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52)
#define CRAYG_PASTE54(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53)                            \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE53(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53)
#define CRAYG_PASTE55(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54)                       \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE54(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54)
#define CRAYG_PASTE56(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55)                  \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE55(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55)
#define CRAYG_PASTE57(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56)             \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE56(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56)
#define CRAYG_PASTE58(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57)        \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE57(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57)
#define CRAYG_PASTE59(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58)   \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE58(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58)
#define CRAYG_PASTE60(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58,   \
                      v59)                                                                                             \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE59(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59)
#define CRAYG_PASTE61(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58,   \
                      v59, v60)                                                                                        \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE60(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60)
#define CRAYG_PASTE62(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58,   \
                      v59, v60, v61)                                                                                   \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE61(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61)
#define CRAYG_PASTE63(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58,   \
                      v59, v60, v61, v62)                                                                              \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE62(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61,  \
                  v62)
#define CRAYG_PASTE64(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, \
                      v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39,   \
                      v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58,   \
                      v59, v60, v61, v62, v63)                                                                         \
    CRAYG_PASTE2(func, v1)                                                                                             \
    CRAYG_PASTE63(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21,    \
                  v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41,  \
                  v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61,  \
                  v62, v63)