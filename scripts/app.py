'''
The main python file, no need to modify, used to bring up other python scripts
Format: app.py -s [py_scripts]
'''
import argparse
import time

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--script", "-s", nargs='+', default=[], help="startup script(s)")
    opt = parser.parse_args()
    for script in opt.script:
        print(f"running startup script: '{script}'")
        exec(open(script).read())

    # TODO: stop it from stopping. std::future?
    while True:
        time.sleep(100000)
