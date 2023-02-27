from qtpy import QtWidgets, QtGui, QtCore
from qtpy.QtWidgets import QTreeWidget, QTreeWidgetItem

from .abstract_handler import AbstractHandler
from .scene_repository import SceneRepository


class TestScenesInspectorWidget(QtWidgets.QWidget):
    def __init__(
        self,
        scene_repository: SceneRepository,
        maya_handler: AbstractHandler,
        parent=None,
    ):
        super(TestScenesInspectorWidget, self).__init__(parent)
        self._scene_repository = scene_repository
        self._maya_handler = maya_handler

        self.setWindowTitle("Test Scenes Inspector")
        self.resize(500, 700)
        self.setWindowFlags(QtCore.Qt.Window)

        self._layout = QtWidgets.QVBoxLayout()
        self.setLayout(self._layout)
        self._init_tree_view()
        self._layout.addWidget(self._tree_view)
        self._btns_layout = QtWidgets.QHBoxLayout()
        self._btn_save = QtWidgets.QPushButton("Save")
        self._btn_save.clicked.connect(self._save_clicked)
        self._btns_layout.addWidget(self._btn_save)
        self._btn_open = QtWidgets.QPushButton("Open")
        self._btn_open.clicked.connect(self._open_clicked)
        self._btns_layout.addWidget(self._btn_open)
        self._layout.addLayout(self._btns_layout)
        self._populate()
        self._enable_or_disable_buttons(False)
        self._tree_view.setContextMenuPolicy(QtCore.Qt.CustomContextMenu)
        self._tree_view.customContextMenuRequested.connect(self._open_menu)

    def _init_tree_view(self):
        self._tree_view = QTreeWidget()
        self._tree_view.setColumnCount(1)
        self._tree_view.setHeaderLabels(["Name"])
        self._tree_view.setStyleSheet(
            "QTreeView::item { height: 50px } QTreeView {icon-size: 50px;}"
        )
        self._tree_view.itemSelectionChanged.connect(self._selection_changed)

    def _populate(self):
        items = []
        selected_suite_item = None
        selected_test_item = None
        for suite in self._scene_repository.list_suites():
            suite_item = QTreeWidgetItem([suite.name])
            suite_item.setData(0, 50, suite)
            for test in suite.tests:
                test_item = QTreeWidgetItem([test.name])
                test_item.setIcon(0, QtGui.QIcon(test.reference_image_path))
                test_item.setData(0, 50, suite)
                test_item.setData(0, 60, test)
                suite_item.addChild(test_item)
                if self._maya_handler.is_current_test(test):
                    selected_suite_item = suite_item
                    selected_test_item = test_item
            items.append(suite_item)

        self._tree_view.clear()
        self._tree_view.insertTopLevelItems(0, items)
        if selected_suite_item and selected_test_item:
            selected_suite_item.setExpanded(True)
            selected_test_item.setSelected(True)

    def _selection_changed(self):
        self._enable_or_disable_buttons(bool(self._tree_view.selectedItems()))

    def _enable_or_disable_buttons(self, state):
        self._btn_save.setEnabled(state)
        self._btn_open.setEnabled(state)

    @property
    def _current_suite(self):
        return self._tree_view.selectedItems()[0].data(0, 50)

    @property
    def _current_test(self):
        return self._tree_view.selectedItems()[0].data(0, 60)

    def _open_menu(self, position):
        menu = QtWidgets.QMenu()
        menu.addAction(self.tr("Add new Suite"), self._add_new_suite)
        indexes = self._tree_view.selectedIndexes()
        if len(indexes) > 0:
            menu.addAction(self.tr("Add new Test"), self._add_new_test)

        menu.exec_(self._tree_view.viewport().mapToGlobal(position))

    def _add_new_suite(self):
        text, ok = QtWidgets.QInputDialog().getText(
            self, "Enter Suite Name", "Suite name:", QtWidgets.QLineEdit.Normal
        )
        if ok and text:
            self._scene_repository.add_new_suite(text)
            self._populate()

    def _add_new_test(self):
        text, ok = QtWidgets.QInputDialog().getText(
            self, "Enter Test Name", "Test name:", QtWidgets.QLineEdit.Normal
        )
        if ok and text:
            test = self._scene_repository.add_new_test(self._current_suite, text)
            self._populate()
            msgBox = QtWidgets.QMessageBox()
            msgBox.setWindowTitle("Use current scene?")
            msgBox.setText(
                "Use the current scene as new test file or create empty test?"
            )

            create_empty_test = msgBox.addButton(
                "Create empty test", QtWidgets.QMessageBox.AcceptRole
            )
            save_current_button = msgBox.addButton(
                "Save current scene as new test", QtWidgets.QMessageBox.AcceptRole
            )
            cancel_button = msgBox.addButton("Cancel", QtWidgets.QMessageBox.RejectRole)

            ret = msgBox.exec_()
            if msgBox.clickedButton() == cancel_button:
                return
            elif msgBox.clickedButton() == create_empty_test:
                self._maya_handler.create_empty_test(test)
            elif msgBox.clickedButton() == save_current_button:
                self._maya_handler.save_as_new(test)

    def _save_clicked(self):
        self._maya_handler.save(self._current_test)

    def _open_clicked(self):
        self._maya_handler.open(self._current_test)
