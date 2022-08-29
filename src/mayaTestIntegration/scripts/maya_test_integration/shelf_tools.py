import os

from utils.shelf import Shelf
from utils.gui_only import maya_gui_only


class CraygTestIntegrationShelf(Shelf):
    def build(self):
        root = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))

        self.addButton(
            label="Tests Inspector",
            icon=os.path.join(root, "xbmlangpath", "CraygTestExplorer.png"),
            annotation="Open Crayg Tests Inspector",
            command="import maya_test_integration;maya_test_integration.show()",
        )


@maya_gui_only("loading of Crayg Test Integration shelf")
def load_shelf():
    CraygTestIntegrationShelf("Crayg_Test_Integration")
