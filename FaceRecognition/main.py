import subprocess
import os
import signal
import sys
from flask import Flask, request, jsonify

app = Flask(__name__)
face_recognition_process = None

def train_model():
    train_process = subprocess.Popen(["python", "train_model.py"])
    train_process.wait()

def signal_handler(sig, frame):
    global face_recognition_process
    if face_recognition_process is not None and face_recognition_process.poll() is None:
        face_recognition_process.terminate()
        face_recognition_process.wait()
    print("process stop and train_model")
    #train_model()
    sys.exit(0)


@app.route('/start', methods=['GET'])
def start_stream():
    global face_recognition_process
    if face_recognition_process is None or face_recognition_process.poll() is not None:
        face_recognition_process = subprocess.Popen(["python", "face_recognition.py"])
        return "face_recognition started"
    else:
        return "face_recognition is already running"

@app.route('/stop', methods=['GET'])
def stop_stream():
    global face_recognition_process
    if face_recognition_process is not None and face_recognition_process.poll() is None:
        face_recognition_process.terminate()
        face_recognition_process.wait()
        train_model()
        return "face_recognition stopped"
    else:
        return "face_recognition is not running"

signal.signal(signal.SIGINT, signal_handler)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=6800)