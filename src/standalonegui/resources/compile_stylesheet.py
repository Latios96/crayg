import os
import sys
import time

import sass
from watchdog.observers.polling import PollingObserver as Observer
from watchdog.events import FileSystemEventHandler

SOURCE_PATH = os.path.join(os.path.dirname(__file__), "stylesheet.scss")
TARGET_PATH = os.path.join(os.path.dirname(__file__), "stylesheet.css")


def compile():
    with open(SOURCE_PATH) as f:
        source = f.read()

    compiled = sass.compile(string=source)

    with open(TARGET_PATH, "w") as f:
        f.write(compiled)

    print("Compilation finished")


def watch_changes():
    class EventHandler(FileSystemEventHandler):
        def on_any_event(self, event):
            compile()

    observer = Observer()
    event_handler = EventHandler()
    observer.schedule(event_handler, SOURCE_PATH)
    observer.start()
    try:
        while True:
            time.sleep(0.2)
    finally:
        observer.stop()
        observer.join()


def main():
    compile()
    if "--watch" in sys.argv:
        watch_changes()


if __name__ == "__main__":
    main()
