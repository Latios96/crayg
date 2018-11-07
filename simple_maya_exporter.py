import pymel.core as pm
import json

def get_pos(obj):
    return [obj.translateX.get(),
            obj.translateY.get(),obj.translateZ.get()]

scene_objects = []

for sphere in pm.ls("pSphere*", type='transform'):
    plant_dict = {}
    plant_dict['position'] = get_pos(sphere)
    plant_dict['radius'] = 1.0
    plant_dict['type'] = 'Sphere'
    scene_objects.append(plant_dict)

for light in pm.ls(type='light'):
    light = light.parent(0)
    light_dict = {}
    light_dict['position'] = get_pos(light)
    light_dict['intensity'] = light.intensity.get()
    light_dict['type'] = 'Light'
    scene_objects.append(light_dict)

for plane in pm.ls("groundplane*", type='transform'):
    plant_dict = {}
    plant_dict['position'] = get_pos(plane)
    plant_dict['type'] = 'GroundPlane'
    scene_objects.append(plant_dict)

cam = pm.ls("render_cam", type='transform')[0]

camera = {}
camera['position'] = get_pos(cam)
up_vector = cam.upDirection()
camera['userUpVector'] = [up_vector[0], up_vector[1], up_vector[2]]
point = cam.getCenterOfInterestPoint(space='world')
camera['centerOfInterest'] = [point[0], point[1], point[2]]
camera['type'] = 'Camera'

scene = {}
scene['SceneObjects'] = scene_objects
scene['Camera'] = camera

with open('/Users/Jan/workspace/crayg/example_scenes/maya_scene.json', 'w') as f:
    json.dump(scene, f, indent=4)