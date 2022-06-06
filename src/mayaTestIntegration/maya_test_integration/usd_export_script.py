import pymel.core as pm
from pxr import Usd, UsdRender, Gf


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

        self._write_render_settings(path)

    def _write_render_settings(self, path):
        stage = Usd.Stage.Open(path)

        usdRenderSettings = UsdRender.Settings.Define(stage, "/Render/settings")

        width = pm.ls("defaultResolution")[0].width.get()
        height = pm.ls("defaultResolution")[0].height.get()
        usdRenderSettings.GetResolutionAttr().Set(Gf.Vec2i(width, height))

        stage.Save()
