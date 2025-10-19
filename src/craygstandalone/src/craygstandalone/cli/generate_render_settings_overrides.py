from dataclasses import dataclass

import jinja2

HEADER_TEMPLATE_STR = """#pragma once

#include "basics/Resolution.h"
#include "crayg/scene/RenderSettings.h"
#include "utils/DtoUtils.h"
#include <fmt/std.h>
#include <optional>

namespace crayg {

CRAYG_DTO_2(IntegratorSettingsOverride, std::string, settingName, IntegratorSettingsValue, value);

struct CliRenderSettingsOverride {
{% for member in members %}
    std::optional<{{member.type}}> {{member.name}};
{% endfor %}
    std::vector<IntegratorSettingsOverride> integratorSettingsOverrides;

    RenderSettings resolveOverrides(const RenderSettings &renderSettings) const;

    bool hasAnyOverrides() const;

    std::string reportOverrides() const;
};

}

"""

CPP_TEMPLATE = """#include "CliRenderSettingsOverride.h"
#include "Logger.h"
#include <boost/algorithm/string/join.hpp>
#include <fmt/std.h>

namespace crayg {

RenderSettings crayg::CliRenderSettingsOverride::resolveOverrides(const RenderSettings &renderSettings) const {
    RenderSettings resolvedRenderSettings;

    if (!hasAnyOverrides()) {
        return renderSettings;
    }
    crayg::Logger::info("Applying rendersetting overrides: {}", reportOverrides());
{% for member in members %}
    {% if member.name == 'regionToRender' %}
        resolvedRenderSettings.{{member.name}} =  {{member.name}}.has_value() ? *{{member.name}} : renderSettings.{{member.name}};
    {% else %}
        resolvedRenderSettings.{{member.name}} = {{member.name}}.value_or(renderSettings.{{member.name}});
    {% endif %}
{% endfor %}
    
    for (auto &override : integratorSettingsOverrides) {
        resolvedRenderSettings.integratorSettings.settings[override.settingName] = override.value;
    }
    return resolvedRenderSettings;
}

bool CliRenderSettingsOverride::hasAnyOverrides() const {
    return {{ members|join('|| ', attribute='name') }} || (!integratorSettingsOverrides.empty());
}

std::string CliRenderSettingsOverride::reportOverrides() const {
    std::vector<std::string> report;

{% for member in members %}
    if ({{member.name}}) {
        report.push_back(fmt::format("{{member.name}} -> {}", *{{member.name}}));
    }
{% endfor %}

    if (!integratorSettingsOverrides.empty()) {
        for (auto &override : integratorSettingsOverrides) {
            report.push_back(fmt::format(R"({} -> {})", override.settingName, override.value));
        }
    }
    return boost::algorithm::join(report, ", ");
}

}
"""


@dataclass
class RenderSettingsMember:
    type: str
    name: str


def render_template(members, template_str, target_path):
    header_template = jinja2.Template(
        template_str, trim_blocks=True, lstrip_blocks=True
    )
    with open(target_path, "w") as f:
        f.write(header_template.render(members=members))


def main():
    members = [
        RenderSettingsMember("Resolution", "resolution"),
        RenderSettingsMember("int", "maxSamples"),
        RenderSettingsMember("IntegratorType", "integratorType"),
        RenderSettingsMember("IntersectorType", "intersectorType"),
        RenderSettingsMember("TileSequenceType", "tileSequenceType"),
        RenderSettingsMember("TileSamplerType", "tileSamplerType"),
        RenderSettingsMember("float", "adaptiveMaxError"),
        RenderSettingsMember("int", "samplesPerAdaptivePass"),
        RenderSettingsMember("bool", "useSpectralLensing"),
        RenderSettingsMember("RegionToRender", "regionToRender"),
    ]

    render_template(members, HEADER_TEMPLATE_STR, "CliRenderSettingsOverride.h")
    render_template(members, CPP_TEMPLATE, "CliRenderSettingsOverride.cpp")


if __name__ == "__main__":
    main()
