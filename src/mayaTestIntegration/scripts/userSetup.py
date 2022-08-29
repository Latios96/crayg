import maya.cmds as cmds

cmds.evalDeferred(
    "from maya_test_integration import shelf_tools;shelf_tools.load_shelf()"
)
