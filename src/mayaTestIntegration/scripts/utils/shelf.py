import maya.cmds as cmds


class Shelf:
    def __init__(self, name, iconPath=""):
        self.name = name

        self.iconPath = iconPath

        self.labelBackground = (0, 0, 0, 0)
        self.labelColour = (0.9, 0.9, 0.9)

        self._cleanOldShelf()
        cmds.setParent(self._parent)
        self.build()

    def build(self):
        raise NotImplementedError()

    def add_button(
            self,
            label,
            icon="commandButton.png",
            command=lambda: None,
            doubleCommand=lambda: None,
            annotation="",
            sourceType="python",
    ):
        cmds.setParent(self._parent)
        if icon:
            icon = self.iconPath + icon
        cmds.shelfButton(
            width=37,
            height=37,
            image=icon,
            command=command,
            label=label,
            annotation=annotation,
            sourceType=sourceType,
        )

    def _cleanOldShelf(self):
        if cmds.shelfLayout(self.name, ex=1):
            if cmds.shelfLayout(self.name, q=1, ca=1):
                for each in cmds.shelfLayout(self.name, q=1, ca=1):
                    cmds.deleteUI(each)
            cmds.deleteUI(self.name)
        self._parent = cmds.shelfLayout(self.name, p="ShelfLayout")
