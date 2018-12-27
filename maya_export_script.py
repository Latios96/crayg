import pymel.core as pm
import maya.OpenMaya as om
import maya.api.OpenMaya as om2

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
        self._mesh = self._obj.getShape()

    def write(self):
        obj_dict = super(TriangleMeshWriter, self).write()
        obj_dict['type'] = 'TriangleMesh'

        pm.select(self._mesh)
        selection = om2.MGlobal.getActiveSelectionList()
        mesh = om2.MFnMesh(selection.getDependNode(0))
        all_points = mesh.getPoints()

        faceIt = om2.MItMeshPolygon(selection.getDependNode(0))

        crayg_points = [[x[0], x[1], x[2]] for x in all_points]
        face_indexes = []
        while not faceIt.isDone():
            faceIt.next(faceIt)
            num_triangles =  faceIt.numTriangles()
            for i in range(num_triangles):
                points, indexes = faceIt.getTriangle(i)
                face_indexes.extend(indexes)
        print crayg_points
        print face_indexes
        obj_dict['points'] = crayg_points
        obj_dict['faceIndexes'] = face_indexes

        return obj_dict


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
            if obj.visibility.get():
                writer = Writer(obj)
                scene_objects.append(writer.write())

    cam = render_cam()
    camera_writer = CameraWriter(cam)
    scene['Camera'] = camera_writer.write()

    with open('/home/jan/workspace/crayg/maya_scene.json', 'w') as f:
        json.dump(scene, f, indent=4)



main()