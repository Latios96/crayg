import os
from dataclasses import dataclass
from typing import List


@dataclass
class TestScene:
    name: str
    path: str

    def _resolve_path(self, extension: str):
        return os.path.join(self.path, self.name + extension)

    @property
    def maya_scene_path(self):
        return self._resolve_path(".ma")

    @property
    def reference_image_path(self):
        return self._resolve_path(".png")

    @property
    def usda_path(self):
        return self._resolve_path(".usda")


@dataclass
class Suite:
    name: str
    path: str
    tests: List[TestScene]


class SceneRepository:
    def __init__(self, root):
        self._root = root

    def list_suites(self) -> List[Suite]:
        suites = []
        for suite_name in filter(
                lambda x: os.path.isdir(os.path.join(self._root, x)), os.listdir(self._root)
        ):
            suites.append(
                Suite(
                    name=suite_name,
                    path=os.path.join(self._root, suite_name),
                    tests=self.list_tests(suite_name),
                )
            )
        return suites

    def list_tests(self, suite_name) -> List[TestScene]:
        tests = []
        suite_path = os.path.join(self._root, suite_name)
        for test_name in filter(
                lambda x: os.path.isdir(os.path.join(suite_path, x)), os.listdir(suite_path)
        ):
            tests.append(
                TestScene(
                    name=str(test_name), path=os.path.join(suite_path, str(test_name))
                )
            )
        return tests

    def add_new_suite(self, suite_name):
        suite_path = os.path.join(self._root, suite_name)
        if not os.path.exists(suite_path):
            os.makedirs(suite_path)

    def add_new_test(self, suite, test_name):
        test_path = os.path.join(suite.path, test_name)
        if not os.path.exists(test_path):
            os.makedirs(test_path)
        return TestScene(name=test_name, path=os.path.join(suite.path, test_name))
