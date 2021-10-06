import json
import os
import pprint


def ensure_remote(remotes, name, url):
    filtered_remotes = list(filter(lambda remote: remote["name"] == name, remotes))
    remote_exists = bool(filtered_remotes)

    if remote_exists:
        remote = filtered_remotes[0]
        remotes.remove(remote)
    remotes.insert(0, {"name": name, "url": url, "verify_ssl": True})


def main():
    config_path = os.path.expanduser("~/.conan/remotes.json")
    with open(config_path) as f:
        remotes = json.load(f)["remotes"]

    ensure_remote(
        remotes,
        "framebffr",
        "https://frmbffr.com/artifactory/api/conan/conantest",
    )

    print(pprint.pformat(remotes))

    with open(config_path, "w") as f:
        json.dump({"remotes": remotes}, f, indent=4)


if __name__ == "__main__":
    main()
