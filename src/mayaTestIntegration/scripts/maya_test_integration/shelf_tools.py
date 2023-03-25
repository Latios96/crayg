import os

from utils.shelf import Shelf
from utils.gui_only import maya_gui_only


class CraygTestIntegrationShelf(Shelf):
    def build(self):
        root = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))

        self.add_button(
            label="Tests Inspector",
            icon=os.path.join(root, "xbmlangpath", "CraygTestExplorer.png"),
            annotation="Open Crayg Tests Inspector",
            command="import maya_test_integration;maya_test_integration.show()",
        )

        self.add_button(
            label="Add Crayg Extra Attributes",
            icon=os.path.join(root, "xbmlangpath", "craygCameraAttributes.png"),
            annotation="Add Crayg Extra Attributes to selected cameras",
            command="from utils import crayg_camera_utils;crayg_camera_utils.add_crayg_extra_attributes_to_selected_cameras()",
        )


@maya_gui_only("loading of Crayg Test Integration shelf")
def load_shelf():
    CraygTestIntegrationShelf("Crayg_Test_Integration")
