'''
Start the threads in cpp
'''
import Workers
import time

Workers.background_run_taskA()
Workers.background_run_pubC()
Workers.background_run_subD()