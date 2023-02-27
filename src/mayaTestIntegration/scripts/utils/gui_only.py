import maya.OpenMaya


def maya_gui_only(name_of_action):
    def decorator(func):
        is_gui_mode = (
            maya.OpenMaya.MGlobal.mayaState() == maya.OpenMaya.MGlobal.kInteractive
        )

        if not is_gui_mode:
            print("Running in Batch mode, {} skipped".format(name_of_action))
            return

        print("{}..".format(name_of_action))
        func()
        print("{} done!".format(name_of_action))

    return decorator
