import pymel.core as pm

from .abstract_handler import AbstractHandler
from .usd_export_script import UsdExporter


class MayaHandler(AbstractHandler):
    def open(self, test):
        pm.loadScene(test.maya_scene_path)

    def save(self, test):
        pm.saveAs(test.maya_scene_path, type="mayaAscii")
        UsdExporter().export(test.usda_path)

    def create_empty_test(self, test):
        pm.newFile(force=True)
        pm.saveAs(test.maya_scene_path, type="mayaAscii")

    def save_as_new(self, test):
        pm.saveAs(test.maya_scene_path, type="mayaAscii")
