import sys
from qtpy.QtWidgets import QApplication
import maya_test_integration
from maya_test_integration.abstract_handler import AbstractHandler

if __name__ == "__main__":
    app = QApplication(sys.argv)

    widget = maya_test_integration.show(
        handler=AbstractHandler(), use_maya_parent=False
    )

    sys.exit(app.exec())
