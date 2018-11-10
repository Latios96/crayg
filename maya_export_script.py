import pymel.core as pm
import json

def get_pos(obj):
    return [obj.translateX.get(),
            obj.translateY.get(), obj.translateZ.get()]

class AbstractWriter(object):
    def __init__(self, obj):
        self._obj = obj

    def write(self):
        raise NotImplementedError()


class TransformableWriter(AbstractWriter):
    def write(self):
        obj_dict = {}
        obj_dict['position'] = [self._obj.translateX.get(),
                                self._obj.translateY.get(), self._obj.translateZ.get()]
        return obj_dict


class SphereWriter(TransformableWriter):
    def write(self):
        obj_dict = super(SphereWriter, self).write()
        obj_dict['radius'] = 1.0
        obj_dict['type'] = 'Sphere'
        return obj_dict


class PointLightWriter(TransformableWriter):
    def write(self):
        obj_dict = super(PointLightWriter, self).write()
        obj_dict['intensity'] = self._obj.intensity.get()
        obj_dict['type'] = 'Light'
        return obj_dict

class CameraWriter(TransformableWriter):
    def write(self):
        obj_dict = super(CameraWriter, self).write()

        up_vector = self._obj.upDirection()
        obj_dict['userUpVector'] = [up_vector[0], up_vector[1], up_vector[2]]

        aim = pm.ls(self._obj.name()+"*aim", type='transform')[0]

        obj_dict['centerOfInterest'] = get_pos(aim)
        obj_dict['type'] = 'Camera'
        obj_dict['focalLength'] = self._obj.focalLength.get()

        film_back_inch = self._obj.horizontalFilmAperture.get()
        filmBack_mm = film_back_inch * 2.54 * 10
        obj_dict['filmbackSize'] = filmBack_mm

        return obj_dict

class GroundPlaneWriter(TransformableWriter):
    def write(self):
        obj_dict = super(GroundPlaneWriter, self).write()
        obj_dict['type'] = 'GroundPlane'
        return obj_dict


def all_spheres():
    return pm.ls("pSphere*", type='transform')


def all_point_lights():
    return [x.parent(0) for x in pm.ls(type='light')]

def all_ground_planes():
    return pm.ls("groundplane*", type='transform')

def render_cam():
    return pm.ls("render_cam", type='transform')[0]

collector_writer = {
    all_spheres : SphereWriter,
    all_point_lights: PointLightWriter,
    all_ground_planes: GroundPlaneWriter,
}



def main():
    scene = {}
    scene_objects = []
    scene['SceneObjects'] = scene_objects

    for collector, Writer in collector_writer.iteritems():
        for obj in collector():
            writer = Writer(obj)
            scene_objects.append(writer.write())

    cam = render_cam()
    camera_writer = CameraWriter(cam)
    scene['Camera'] = camera_writer.write()

    with open('/Users/Jan/workspace/crayg/maya_scene.json', 'w') as f:
        json.dump(scene, f, indent=4)

if __name__ == '__main__':
    main()