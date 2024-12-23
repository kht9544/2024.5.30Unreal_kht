import cv2
from flask import Flask, Response

app = Flask(__name__)
camera = cv2.VideoCapture(0)
camera.set(cv2.CAP_PROP_FRAME_WIDTH, 600)
camera.set(cv2.CAP_PROP_FRAME_HEIGHT, 400)

def generate_frames():
    while True:
        success, frame = camera.read()
        if not success:
            print("Error reading frame from camera")
            break
        ret, buffer = cv2.imencode('.jpg', frame)
        if not ret:
            break
        yield(b'--frame\r\n'
              b'Content-Type: image/jpeg\r\n\r\n' + buffer.tobytes() + b'\r\n')
        
@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)
