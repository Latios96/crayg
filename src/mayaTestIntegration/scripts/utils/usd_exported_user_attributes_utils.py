import json

EXPORTED_ATTRS_MAYA_ATTR_NAME = "USD_UserExportedAttributesJson"


def read_usd_user_exported_attribute(node):
    if not node.hasAttr(EXPORTED_ATTRS_MAYA_ATTR_NAME):
        return {}
    exported_attributes_value = node.USD_UserExportedAttributesJson.get()
    if not exported_attributes_value:
        return {}
    return json.loads(exported_attributes_value)


def write_usd_user_exported_attribute(node, exported_attributes):
    if not node.hasAttr(EXPORTED_ATTRS_MAYA_ATTR_NAME):
        node.addAttr(EXPORTED_ATTRS_MAYA_ATTR_NAME, dt="string")
    exported_attributes_value = json.dumps(exported_attributes)
    node.USD_UserExportedAttributesJson.set(exported_attributes_value)
