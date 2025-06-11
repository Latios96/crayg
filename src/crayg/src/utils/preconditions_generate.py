from dataclasses import dataclass
from typing import List


@dataclass
class Check:
    name: str
    args: List[str]
    condition: str
    message: str

    @property
    def args_str(self):
        return ", ".join(self.args)


def main():
    checks = [
        Check(
            name="NOT_NULLPTR",
            args=["ptr"],
            condition="ptr != nullptr",
            message='fmt::format("{} should not be nullptr!", #ptr)',
        ),
        Check(
            name="IS_VALID_INDEX",
            args=["index", "size"],
            condition="(index >= 0 && index < size)",
            message='fmt::format("Index {} is out of range: {}, size is {}!",#index, index, size)',
        ),
        Check(
            name="EQUALS",
            args=["actual", "expected"],
            condition="actual == expected",
            message='fmt::format("Expected {} to be {}, was {}!", #actual, expected, actual)',
        ),
        Check(
            name="NOT_EQUALS",
            args=["actual", "notExpected"],
            condition="actual != notExpected",
            message='fmt::format("Expected {} not to be {}, was {}!", #actual, notExpected, actual)',
        ),
        Check(
            name="GREATER_OR_EQUALS",
            args=["actual, expected"],
            condition="(actual >= expected)",
            message='fmt::format("Expected {} to be greater or equals than {}, was!", #actual, expected, actual)',
        ),
        Check(
            name="GREATER_THAN",
            args=["actual, expected"],
            condition="(actual > expected)",
            message='fmt::format("Expected {} to be greater than {}, was {}!", #actual, expected, actual)',
        ),
        Check(
            name="LESS_OR_EQUALS",
            args=["actual, expected"],
            condition="(actual <= expected)",
            message='fmt::format("Expected {} to be less or equals than {}, was!", #actual, expected, actual)',
        ),
        Check(
            name="LESS_THAN",
            args=["actual, expected"],
            condition="(actual < expected)",
            message='fmt::format("Expected {} to be less than {}, was {}!", #actual, expected, actual)',
        ),
        Check(
            name="WITHIN_RANGE_INCLUSIVE",
            args=["actual, min, max"],
            condition="(actual >= min && actual <= max)",
            message='fmt::format("Expected {} to be in interval [{},{}], value was {}!", #actual, min, max, actual)',
        ),
        Check(
            name="NOT_WITHIN_RANGE_INCLUSIVE",
            args=["actual, min, max"],
            condition="(actual < min || actual > max)",
            message='fmt::format("Expected {} not to be in interval [{},{}], value was {}!", #actual, min, max, actual)',
        ),
        Check(
            name="WITHIN_RANGE_EXCLUSIVE",
            args=["actual, min, max"],
            condition="(actual > min && actual < max)",
            message='fmt::format("Expected {} to be in interval ]{},{}[, was {}!", #actual, min, max, actual)',
        ),
        Check(
            name="NOT_WITHIN_RANGE_EXCLUSIVE",
            args=["actual, min, max"],
            condition="(actual <= min || actual >= max)",
            message='fmt::format("Expected {} not to be in interval ]{},{}[, was {}!", #actual, min, max, actual)',
        ),
        Check(
            name="IS_NOT_NAN",
            args=["value"],
            condition="(!std::isnan(value))",
            message='fmt::format("{} should not be NaN!", #value)',
        ),
        Check(
            name="HAS_NO_NAN",
            args=["value"],
            condition="(!value.hasNaN())",
            message='fmt::format("{} should not have NaN!", #value)',
        ),
        Check(
            name="STATE",
            args=["actualState", "expectedState"],
            condition="(actualState == expectedState)",
            message='fmt::format("Expected {} to have state {}, was {}!", #actualState, actualState, expectedState)',
        ),
        Check(
            name="OPTIONAL_HAS_VALUE",
            args=["optional"],
            condition="(optional.has_value())",
            message='fmt::format("{} has no value!", #optional)',
        ),
        Check(
            name="IS_NORMALIZED_VECTOR",
            args=["vector"],
            condition="(std::fabs((vector).length() - 1) < 0.001f)",
            message='fmt::format("{} is not unit vector!: {}", #vector, vector)',
        ),
        Check(
            name="IS_EMPTY",
            args=["obj"],
            condition="obj.empty()",
            message='fmt::format("{} should be empty!", #obj)',
        ),
        Check(
            name="IS_NOT_EMPTY",
            args=["obj"],
            condition="(!obj.empty())",
            message='fmt::format("{} should not be empty!", #obj)',
        ),
    ]

    with open("Preconditions.normal.generated.h", "w") as f:
        f.write("// clang-format off\n")
        for check in checks:
            f.write(
                f"#define CRAYG_CHECK_{check.name}({check.args_str}) CRAYG_CHECK_{check.name}_IMPL({check.args_str})\n"
            )
        f.write("// clang-format on\n")

    with open("Preconditions.debug.generated.h", "w") as f:
        f.write("// clang-format off\n")
        for check in checks:
            f.write(
                f"#define CRAYG_CHECKD_{check.name}({check.args_str}) CRAYG_CHECK_{check.name}_IMPL({check.args_str})\n"
            )
        f.write("// clang-format on\n")

    with open("Preconditions.debugdisabled.generated.h", "w") as f:
        f.write("// clang-format off\n")
        for check in checks:
            f.write(
                f"#define CRAYG_CHECKD_{check.name}({check.args_str}) CRAYG_EMPTY_CHECK\n"
            )
        f.write("// clang-format on\n")

    with open("Preconditions.impls.generated.h", "w") as f:
        f.write("// clang-format off\n")
        for check in checks:
            f.write(
                f"#define CRAYG_CHECK_{check.name}_IMPL({check.args_str}) CRAYG_CHECK_OR_THROW({check.condition}, {check.message})\n"
            )
        f.write("// clang-format on\n")


if __name__ == "__main__":
    main()
