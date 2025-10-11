from flask import Flask, request, jsonify
import pickle
import serial

app = Flask(__name__)

# Load the trained ML model
model = pickle.load(open("model.pkl", "rb"))

# Serial connection to Arduino
ser = serial.Serial('COM3', 9600)  # Replace COM3 with your port

@app.route('/predict', methods=['POST'])
def predict():
    data = request.get_json()
    features = [data['gyro'][0], data['gyro'][1], data['gyro'][2], data['ultrasonic']]
    prediction = model.predict([features])[0]
    ser.write((prediction + '\n').encode())
    return jsonify({'command': prediction})

@app.route('/voice_command', methods=['POST'])
def voice_command():
    data = request.get_json()
    command = data.get("command", "").lower()
    ser.write((command + '\n').encode())
    return jsonify({"status": "success", "received": command})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

