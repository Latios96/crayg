import os

import sass

HEADER_TEMPLATE = """#ifndef CRAYG_SRC_STANDALONEGUI_STYLESHEET_H_
#define CRAYG_SRC_STANDALONEGUI_STYLESHEET_H_

/*
THIS FILE IS GENERATED, DO NOT EDIT DIRECTLY!
*/

const char * STYLESHEET = R"(
{}
)";

#endif //CRAYG_SRC_STANDALONEGUI_STYLESHEET_H_

"""


def main():
    source_path = os.path.join(os.path.dirname(__file__), "stylesheet.scss")
    target_path = os.path.join(os.path.dirname(__file__), "Stylesheet.h")
    with open(source_path) as f:
        source = f.read()

    compiled = sass.compile(string=source)

    header = HEADER_TEMPLATE.format(compiled)
    with open(target_path, "w") as f:
        f.write(header)


if __name__ == '__main__':
    main()
