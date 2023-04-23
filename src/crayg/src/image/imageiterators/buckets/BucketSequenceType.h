#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_BUCKETSEQUENCETYPE_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_BUCKETSEQUENCETYPE_H_

#include <fmt/format.h>
#include <magic_enum.hpp>

namespace crayg {

enum class BucketSequenceType { LINE_BY_LINE = 1, SPIRAL = 2 };

}

template <> struct fmt::formatter<crayg::BucketSequenceType> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext> auto format(crayg::BucketSequenceType const &integratorType, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), magic_enum::enum_name(integratorType));
    };
};

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEITERATORS_BUCKETS_BUCKETSEQUENCETYPE_H_
