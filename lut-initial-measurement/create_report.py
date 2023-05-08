import json
from pprint import pprint


def average_files(files):
    data = None
    for f in files:
        with open(f) as d:
            json_data = json.load(d)
            if data is None:
                data = json_data
                continue
        for i, test in enumerate(data):
            test["seconds"] += json_data[i]["seconds"]

    for i, test in enumerate(data):
        data[i]["seconds"] = data[i]["seconds"] / len(files)
    return data


def get_test_by_scene_name_and_lens(tests, scene_name, lens_name):
    for test in tests:
        if (
            scene_name.lower() in test["testIdentifier"].lower()
            and lens_name.lower() in test["testIdentifier"].lower()
        ):
            return test
    raise ValueError(f"No test with scene name {scene_name} and lens name {lens_name}")


def get_test_duration_by_scene_name_and_lens(tests, scene_name, lens_name):
    return get_test_by_scene_name_and_lens(tests, scene_name, lens_name)["seconds"]


def generate_report_data(baseline_data, new_revision_data):
    reports = []
    for scene in ["OpenChess", "StormTrooper"]:
        data = {}
        reports.append(data)
        data["name"] = scene
        data["data"] = [
            [
                "Lens Type",
                "Baseline",
                "With Ray LUT",
            ]
        ]
        data["data"].append(
            [
                "Thin Lens",
                get_test_duration_by_scene_name_and_lens(
                    baseline_data, scene, "thin_lens"
                ),
                get_test_duration_by_scene_name_and_lens(
                    new_revision_data, scene, "thin_lens"
                ),
            ]
        )
        data["data"].append(
            [
                "Canon 70mm (34 Elemente)",
                get_test_duration_by_scene_name_and_lens(baseline_data, scene, "canon"),
                get_test_duration_by_scene_name_and_lens(
                    new_revision_data, scene, "canon"
                ),
            ]
        )
        data["data"].append(
            [
                "Angenieux (15 Elemente)",
                get_test_duration_by_scene_name_and_lens(
                    baseline_data, scene, "Angenieux"
                ),
                get_test_duration_by_scene_name_and_lens(
                    new_revision_data, scene, "Angenieux"
                ),
            ]
        )
    return reports


def generate_report(report_data):
    template = """
    <html>
<head>
    <title>Benchmarks</title>
    <meta charset="UTF-8">
    <style type="text/css">
        body {
            margin: 40px auto;
            font-family: Arial;
            font-size: 14px;
            color: #333;
            max-width: 90%;
        }

        a {
            text-decoration: none;
            color: #06b;
        }
    </style>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script>
        google.charts.load('current', {'packages': ['line', 'bar']});
        google.charts.setOnLoadCallback(drawCharts);

        function drawChart(chartsContainer,scene) {
            var data = google.visualization.arrayToDataTable(scene.data)

            var options = {
                chart: {
                    title: scene.name,

                }, pointsVisible: true,
                pointSize: 2.5,
                height: 500,
            };

            elem = document.createElement('div');
            elem.id = scene.sceneName;
            chartsContainer.appendChild(elem)

            var chart = new google.charts.Bar(elem);

            chart.draw(data, google.charts.Bar.convertOptions(options));
        }

        function drawCharts() {
            var chartsContainer = document.getElementById("charts");
            var jsonData = $JSON_DATA$

            jsonData.forEach((scene) => {
                drawChart(chartsContainer,scene)
            })
        }
    </script>
</head>
<body>
<h1>Benchmarks</h1>
<div id="charts">

</div>
</body>
</html>
"""
    with open("report.html", "w") as f:
        f.write(template.replace("$JSON_DATA$", json.dumps(report_data)))


def main():
    baseline_files = ["baseline-1.json", "baseline-2.json", "baseline-3.json"]
    baseline = average_files(baseline_files)
    new_revision_files = [
        "new-revision-1.json",
        "new-revision-2.json",
        "new-revision-3.json",
    ]
    new_revision = average_files(new_revision_files)
    charts_data = generate_report_data(baseline, new_revision)
    generate_report(charts_data)


if __name__ == "__main__":
    main()
