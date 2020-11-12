import argparse
import os
import sys

from jinja2.nativetypes import NativeEnvironment

HEADER_TEMPLATE = """
#include <ostream>
/** GENERATED START **/
class Private{{class_name}}Base {
 public:
    Private{{class_name}}Base();
    Private{{class_name}}Base({{wrapped_type}} value);
    bool operator==(const Private{{class_name}}Base &rhs) const;
    bool operator!=(const Private{{class_name}}Base &rhs) const;
    bool operator<(const Private{{class_name}}Base &rhs) const;
    bool operator>(const Private{{class_name}}Base &rhs) const;
    bool operator<=(const Private{{class_name}}Base &rhs) const;
    bool operator>=(const Private{{class_name}}Base &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Private{{class_name}}Base &wrapper);
    {{wrapped_type}} to{{wrapped_type_camel_case}}() const;
 private:
    {{wrapped_type}} value;
};
/** GENERATED END **/
class {{class_name}} : public Private{{class_name}}Base {
    using Private{{class_name}}Base::Private{{class_name}}Base;
    // your own methods here..
};
"""

CPP_TEMPLATE = """
#include "{{class_name}}.h"

/** GENERATED START **/
Private{{class_name}}Base::Private{{class_name}}Base(float value) : value(value) {}
bool Private{{class_name}}Base::operator==(const Private{{class_name}}Base &rhs) const {
    return value == rhs.value;
}
bool Private{{class_name}}Base::operator!=(const Private{{class_name}}Base &rhs) const {
    return !(rhs == *this);
}
bool Private{{class_name}}Base::operator<(const Private{{class_name}}Base &rhs) const {
    return value < rhs.value;
}
bool Private{{class_name}}Base::operator>(const Private{{class_name}}Base &rhs) const {
    return rhs < *this;
}
bool Private{{class_name}}Base::operator<=(const Private{{class_name}}Base &rhs) const {
    return !(rhs < *this);
}
bool Private{{class_name}}Base::operator>=(const Private{{class_name}}Base &rhs) const {
    return !(*this < rhs);
}
std::ostream &operator<<(std::ostream &os, const Private{{class_name}}Base &wrapper) {
    os << wrapper.value;
    return os;
}
float Private{{class_name}}Base::to{{wrapped_type_camel_case}}() const {
    return value;
}
Private{{class_name}}Base::Private{{class_name}}Base() = default;
/** GENERATED END **/
"""


def render_template(template_str, data):
    env = NativeEnvironment()
    t = env.from_string(template_str)
    return t.render(data)


def generate_wrapper(class_name, wrapped_type):
    folder = r"M:\workspace\crayg\src\crayg\src\basics"
    header_path = os.path.join(folder, "{}.h".format(class_name))
    cpp_path = os.path.join(folder, "{}.cpp".format(class_name))
    wrapped_type_camel = wrapped_type[0].upper() + wrapped_type[1:]

    with open(header_path, "w") as f:
        f.write(
            render_template(
                HEADER_TEMPLATE,
                dict(
                    class_name=class_name,
                    wrapped_type=wrapped_type,
                    wrapped_type_camel_case=wrapped_type_camel,
                ),
            )
        )
    with open(cpp_path, "w") as f:
        f.write(
            render_template(
                CPP_TEMPLATE,
                dict(
                    class_name=class_name,
                    wrapped_type=wrapped_type,
                    wrapped_type_camel_case=wrapped_type_camel,
                ),
            )
        )


def main(args):
    parser = argparse.ArgumentParser(description="Process some integers.")
    parser.add_argument("class_name", help="Name of the class to generate")
    parser.add_argument("wrapped_type", help="The type that should be wrapped")
    parser.add_argument("folder", help="The folder where .h and .cpp should be located")

    args = parser.parse_args()

    generate_wrapper(args.class_name, args.wrapped_type)


if __name__ == "__main__":
    main(sys.argv)
