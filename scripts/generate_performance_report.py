import json
import os
from typing import Optional, Dict, List

import requests
import typer


def get_last_run_id(cato_config: Optional[str], last_run_id: Optional[int]) -> int:
    if last_run_id:
        return last_run_id

    with open(os.path.join(cato_config, ".cato_last_run.json")) as f:
        last_run_json = json.load(f)
    last_run_id = last_run_json.get("last_run_id")
    if not last_run_id:
        raise ValueError(".cato_last_run.json does not contain a last run id.")
    return last_run_id


def get_cato_url(cato_config: Optional[str], url: Optional[str]) -> str:
    if url:
        return url
    with open(os.path.join(cato_config, "cato.json")) as f:
        cato_config_data = json.load(f)
    return cato_config_data["serverUrl"]


def get_auth_token(url: str) -> str:
    cato_config_file = os.path.expanduser("~/.cato/config.json")
    if not os.path.exists(cato_config_file):
        raise RuntimeError(f"{cato_config_file} does not exist.")
    with open(cato_config_file) as f:
        cato_config_data = json.load(f)
    api_token = cato_config_data["api_tokens"].get(url)
    if not api_token:
        raise ValueError(f"{cato_config_file} does not contain a token for url {url}")
    return api_token


def get_run_data(run_id: int, url: str, auth_token: str) -> Dict:
    request_url = f"{url}/api/v1/test_results/run/{run_id}"
    print(f"Retrieve run data for id {run_id}")
    response = requests.get(
        request_url, headers={"Authorization": f"Bearer {auth_token}"}
    )
    assert response.ok
    return response.json()


def get_durations_by_name(run_data) -> Dict[str, float]:
    durations_by_name = {}
    for run in run_data:
        durations_by_name[run["name"]] = run["seconds"]
    return durations_by_name


def generate_report_data(baseline_data, last_run_data) -> List:
    baseline_durations_by_name = get_durations_by_name(baseline_data)
    last_run_durations_by_name = get_durations_by_name(last_run_data)
    report_data = [
        [
            "Scene",
            "Baseline",
            "New revision",
        ]
    ]

    for test in baseline_data:
        report_data.append(
            [
                test["name"],
                baseline_durations_by_name[test["name"]],
                last_run_durations_by_name[test["name"]],
            ]
        )

    return report_data


app = typer.Typer()


@app.command(help="Generate cato config for test scense")
def generate_report(
    baseline_id: int,
    last_run_id: Optional[int] = None,
    url: Optional[str] = None,
    cato_config: Optional[str] = os.getcwd(),
):
    last_run_id = get_last_run_id(cato_config, last_run_id)
    url = get_cato_url(cato_config, url)
    auth_token = get_auth_token(url)

    baseline_data = get_run_data(baseline_id, url, auth_token)
    last_run_data = get_run_data(last_run_id, url, auth_token)

    report_data = generate_report_data(baseline_data, last_run_data)

    with open(os.path.join(os.path.dirname(__file__), "report.template.html")) as f:
        html_template = f.read()
    with open("timing_report.html", "w") as f:
        html_vars = {
            "$JSONDATA$": json.dumps(report_data),
            "$BASELINE_RUN_ID$": baseline_id,
            "$NEW_RUN_ID$": last_run_id,
        }
        for key, value in html_vars.items():
            html_template = html_template.replace(key, str(value))
        f.write(html_template)


if __name__ == "__main__":
    app()
