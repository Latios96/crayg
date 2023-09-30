import os
from Deadline.Plugins import *
from Deadline.Scripting import *


def GetDeadlinePlugin():
    return CraygPlugin()


def CleanupDeadlinePlugin(deadlinePlugin):
    deadlinePlugin.Cleanup()


class CraygPlugin(DeadlinePlugin):
    def __init__(self):
        self.InitializeProcessCallback += self.InitializeProcess
        self.RenderExecutableCallback += self.RenderExecutable
        self.RenderArgumentCallback += self.RenderArgument

    def Cleanup(self):
        del self.InitializeProcessCallback
        del self.RenderExecutableCallback
        del self.RenderArgumentCallback

    def InitializeProcess(self):
        self.PluginType = PluginType.Simple
        self.StdoutHandling = True
        self.AddStdoutHandlerCallback(
            r"\[info\] (.*) done by ([0-9]+)%"
        ).HandleCallback += self.handleStdOutProgress

    def RenderExecutable(self):
        return self.GetPluginInfoEntry("CraygExecutable")

    def RenderArgument(self):
        scene = self.GetPluginInfoEntry("Scene")
        output_directory = self.GetJob().GetJobInfoKeyValue("OutputDirectory0")
        output_filename = self.GetJob().GetJobInfoKeyValue("OutputFilename0")
        output = os.path.join(output_directory, output_filename)
        renderArguments = "-s {} -o {}".format(scene, output)

        camera = self.GetPluginInfoEntryWithDefault("Camera", None)
        if camera:
            renderArguments += " --camera {}".format(camera)

        variant_selection = self.GetPluginInfoEntryWithDefault("VariantSelection", None)
        if variant_selection:
            renderArguments += " {}".format(variant_selection)

        integrator_settings = self.GetPluginInfoEntryWithDefault(
            "IntegratorSettings", None
        )
        if integrator_settings:
            renderArguments += " {}".format(integrator_settings)

        resolution = self.GetPluginInfoEntryWithDefault("Resolution", None)
        if resolution:
            renderArguments += " --resolution={}".format(resolution)

        max_samples = self.GetPluginInfoEntryWithDefault("MaxSamples", None)
        if max_samples:
            renderArguments += " --maxSamples={}".format(max_samples)

        integrator = self.GetPluginInfoEntryWithDefault("Integrator", None)
        if integrator:
            renderArguments += " --integrator={}".format(integrator)

        intersector = self.GetPluginInfoEntryWithDefault("Intersector", None)
        if intersector:
            renderArguments += " --integrator={}".format(intersector)

        bucket_sequence = self.GetPluginInfoEntryWithDefault("BucketSequence", None)
        if bucket_sequence:
            renderArguments += " --bucketSequence={}".format(bucket_sequence)

        bucket_sampler_type = self.GetPluginInfoEntryWithDefault(
            "BucketSamplerType", None
        )
        if bucket_sampler_type:
            renderArguments += " --bucketSamplerType={}".format(bucket_sampler_type)

        adaptive_max_error = self.GetPluginInfoEntryWithDefault(
            "AdaptiveMaxError", None
        )
        if adaptive_max_error:
            renderArguments += " --adaptiveMaxError={}".format(adaptive_max_error)

        use_spectral_lensing = self.GetPluginInfoEntryWithDefault(
            "UseSpectralLensing", None
        )
        if use_spectral_lensing:
            renderArguments += " --useSpectralLensing"

        return renderArguments

    def handleStdOutProgress(self):
        task_name = self.GetRegexMatch(1)
        progress = self.GetRegexMatch(2)

        self.SetStatusMessage(self.GetRegexMatch(1))

        if task_name == "Rendering":
            self.SetProgress(float(self.GetRegexMatch(2)))
