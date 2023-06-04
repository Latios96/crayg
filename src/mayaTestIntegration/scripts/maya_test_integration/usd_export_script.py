import pymel.core as pm
from pxr import Usd, UsdRender, Gf, UsdGeom, Sdf


class UsdExporter:
    def export(self, path):
        if not pm.pluginInfo("mayaUsdPlugin", query=True, loaded=True):
            pm.loadPlugin("mayaUsdPlugin")

        pm.mayaUSDExport(
            file=path,
            defaultMeshScheme="none",
            convertMaterialsTo="UsdPreviewSurface",
            renderableOnly=True,
        )

        self._post_export_usd_edits(path)

    def _post_export_usd_edits(self, path):
        stage = Usd.Stage.Open(path)

        self._write_render_settings(stage)
        self._convert_lens_file_paths(stage)

        stage.Save()

    def _write_render_settings(self, stage):
        usdRenderSettings = UsdRender.Settings.Define(stage, "/Render/settings")

        width = pm.ls("defaultResolution")[0].width.get()
        height = pm.ls("defaultResolution")[0].height.get()
        usdRenderSettings.GetResolutionAttr().Set(Gf.Vec2i(width, height))

    def _convert_lens_file_paths(self, stage):
        for prim in stage.TraverseAll():
            if not UsdGeom.Camera(prim):
                continue
            craygLensFileAttr = prim.GetAttribute("craygLensFileString")
            if not craygLensFileAttr:
                continue

            craygLensFile = craygLensFileAttr.Get()
            craygLensFileAttr = prim.CreateAttribute(
                "craygLensFile", Sdf.ValueTypeNames.Asset
            )
            craygLensFileAttr.Set(craygLensFile)
