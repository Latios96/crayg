import os.path

from .scene_repository import SceneRepository
from .test_scenes_inspector_widget import TestScenesInspectorWidget


def _get_tests_root_folder():
    path = __file__
    for i in range(4):
        path = os.path.dirname(path)
    return os.path.join(path, "crayg", "integrationTests")


def show(handler=None, use_maya_parent=True):
    scene_repository = SceneRepository(_get_tests_root_folder())
    if not handler:
        from .maya_handler import MayaHandler

        handler = MayaHandler()
    parent = None
    if use_maya_parent:
        from shiboken2 import wrapInstance
        from maya import OpenMayaUI
        from PySide2 import QtWidgets

        ptr = OpenMayaUI.MQtUtil.mainWindow()
        parent = wrapInstance(int(ptr), QtWidgets.QMainWindow)

    widget = TestScenesInspectorWidget(scene_repository, handler, parent=parent)
    widget.show()
    return widget
