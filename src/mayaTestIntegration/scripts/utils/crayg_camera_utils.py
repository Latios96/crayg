import pymel.core as pm
from .usd_exported_user_attributes_utils import (
    read_usd_user_exported_attribute,
    write_usd_user_exported_attribute,
)

CRAYG_CAMERA_TYPE_ATTRIBUTE_NAME = "craygCameraType"
CRAYG_LENS_FILE_ATTRIBUTE_NAME = "craygLensFile"


def _find_cameras(objects):
    cameras = []
    for selected_obj in objects:
        if selected_obj.type() == "camera":
            cameras.append(selected_obj)
        else:
            cameras.extend(_find_cameras(selected_obj.getChildren()))
    return cameras


def _add_usd_user_exported_attribute(node, attribute_name, usd_attribute_name=None):
    exported_attributes = read_usd_user_exported_attribute(node)
    usd_attr_name = attribute_name if not usd_attribute_name else usd_attribute_name
    exported_attributes[attribute_name] = {"usdAttrName": usd_attr_name}
    write_usd_user_exported_attribute(node, exported_attributes)


def _add_camera_type_attribute(camera):
    if camera.hasAttr(CRAYG_CAMERA_TYPE_ATTRIBUTE_NAME):
        return
    camera.addAttr(
        CRAYG_CAMERA_TYPE_ATTRIBUTE_NAME,
        attributeType="enum",
        en=":".join(["_", "Pine Hole", "Thin Lens", "Realistic"]),
    )
    camera.craygCameraType.set("Pine Hole")
    _add_usd_user_exported_attribute(
        camera, CRAYG_CAMERA_TYPE_ATTRIBUTE_NAME, "craygLensFileString"
    )


def _add_lens_file_attribute(camera):
    if camera.hasAttr(CRAYG_LENS_FILE_ATTRIBUTE_NAME):
        return
    camera.addAttr(CRAYG_LENS_FILE_ATTRIBUTE_NAME, dt="string", keyable=False)
    _add_usd_user_exported_attribute(camera, CRAYG_LENS_FILE_ATTRIBUTE_NAME)


def _add_attributes_to_camera(camera):
    _add_camera_type_attribute(camera)
    _add_lens_file_attribute(camera)


def add_crayg_extra_attributes_to_selected_cameras():
    selected_cameras = _find_cameras(pm.selected())
    for camera in selected_cameras:
        _add_attributes_to_camera(camera)
