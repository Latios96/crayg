import json
import os
import pprint
import subprocess


def check_conan_output(cmd):
    print(" ".join(cmd))
    env = os.environ.copy()
    if env.get("PYTHONPATH"):
        env.pop("PYTHONPATH")
    return subprocess.check_output(cmd, env=env)


def call_conan(cmd):
    print(" ".join(cmd))
    env = os.environ.copy()
    if env.get("PYTHONPATH"):
        env.pop("PYTHONPATH")
    subprocess.call(cmd, env=env)


if __name__ == "__main__":
    script_location = __file__
    conanfile_location = os.path.dirname(os.path.dirname(script_location))
    conanfile = os.path.join(conanfile_location, "conanfile.txt")

    cmd = ["conan", "info", conanfile, "--json", "--only", "requires"]
    info = check_conan_output(cmd)
    data = json.loads(info)
    package_requirements = list(map(lambda x: x.get("requires"), data))

    all_requirements = set()
    for packages in package_requirements:
        if packages:
            for package in packages:
                all_requirements.add(package)

    print(pprint.pformat(all_requirements))
    for requirement in all_requirements:
        cmd = ["conan", "upload", requirement, "--all", "--confirm", "-r=framebffr", "--parallel"]
        call_conan(cmd)
