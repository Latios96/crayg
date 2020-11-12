import dataclasses
from dataclasses import dataclass
from typing import List

import CppHeaderParser
from jinja2.nativetypes import NativeEnvironment

HEADER_TEMPLATE = """
{% for include in includes %}
#include {{include}}
{% endfor %}

class {{class_name}} {
  public:
    {{class_name}}() = default;
    {{class_name}}(
    
    {% for property in properties %}
    {{property.type}} {{property.name}}{% if not loop.last %},{% endif %}
    {% endfor %});
    
  private:
    {% for property in properties %}
        {{property.type}} {{property.name}};
    {% endfor %}
};
"""
CPP_TEMPLATE = """
#include "{{class_name}}.h"

{{class_name}}::{{class_name}}({% for property in properties %}
    {{property.type}} {{property.name}}{% if not loop.last %},{% endif %}
    {% endfor %})
    : {% for property in properties %}
    {{property.name}}({{property.name}}){% if not loop.last %},{% endif %}
    {% endfor %} {}
"""


def render_template(template, lombok_cls):
    env = NativeEnvironment()
    t = env.from_string(template)
    result = t.render(lombok_cls)
    return "\n".join([ll.rstrip() for ll in result.splitlines() if ll.strip()])


def main():
    header = CppHeaderParser.CppHeader(r"M:\workspace\crayg\src\crayg\src\basics\LombokTest.h")

    properties = []
    class_name = ""
    for cls_name, cls in header.classes.items():
        class_name = cls['name']
        for p in cls['properties']['private']:
            properties.append(dict(name=p['name'], type=p['type']))
        break

    lombok_cls = dict(class_name=class_name, properties=properties, includes=header.includes)

    generated_header = render_template(HEADER_TEMPLATE, lombok_cls)
    generated_cpp = render_template(CPP_TEMPLATE, lombok_cls)

    with open(r"M:\workspace\crayg\src\crayg\src\basics\{}.h".format(class_name), "w") as f:
        f.write(generated_header)

    with open(r"M:\workspace\crayg\src\crayg\src\basics\{}.cpp".format(class_name), "w") as f:
        f.write(generated_cpp)

    # constructor
    # getter
    # tostring
    #


if __name__ == '__main__':
    main()
