import pymel.core as pm
import maya.OpenMaya as om

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

        point = self._obj.getCenterOfInterestPoint(space='world')
        obj_dict['centerOfInterest'] = [point[0], point[1], point[2]]
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


class TriangleMeshWriter(TransformableWriter):

    def __init__(self, obj):
        super(TriangleMeshWriter, self).__init__(obj)
        self._mesh = self._obj.getShape().__apimfn__()

    def write(self):
        obj_dict = super(TriangleMeshWriter, self).write()
        obj_dict['type'] = 'TriangleMesh'

        self._write_points(obj_dict)
        self._write_face_indexes(obj_dict)
        
        return obj_dict

    def _write_face_indexes(self, obj_dict):
        mayaFaceIndexes = om.MIntArray()

        face_indexes = []

        for i in range(self._mesh.numPolygons()):
            self._mesh.getPolygonVertices(i, mayaFaceIndexes)
            for i in range(mayaFaceIndexes.length()):
                face_indexes.append(mayaFaceIndexes[i])

        obj_dict['faceIndexes'] = face_indexes

    def _write_points(self, obj_dict):
        points = om.MFloatPointArray()
        self._mesh.getPoints(points)
        points_list = []
        for i in range(points.length()):
            points_list.append([points[i][0], points[i][1], points[i][2]])

        obj_dict['points'] = points_list
        





def all_spheres():
    return pm.ls("pSphere*", type='transform')


def all_point_lights():
    return [x.parent(0) for x in pm.ls(type='light')]


def all_ground_planes():
    return pm.ls("groundplane*", type='transform')


def render_cam():
    return pm.ls("render_cam", type='transform')[0]


def all_meshes():
    meshes = pm.ls(type='mesh')
    meshes = map(lambda x: x.parent(0), meshes)
    return meshes

collector_writer = {
    all_point_lights: PointLightWriter,
    all_meshes: TriangleMeshWriter
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



main()