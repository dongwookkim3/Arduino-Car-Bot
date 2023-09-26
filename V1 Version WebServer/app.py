import os
from flask import Flask, render_template
import firebase_admin
from firebase_admin import credentials, firestore
# Firebase 연결 필요
cred = credentials.Certificate("path/to/your/firebase-credentials.json")
firebase_admin.initialize_app(cred)
db = firestore.client()
app = Flask(__name__)
@app.route("/")

def index():
    return render_template("index.html")
@app.route("/button/<button_name>")

def button(button_name):
    if button_name == "Run":
        update_mode(1)
    elif button_name == "Left":
        update_mode(2)
    elif button_name == "Back":
        update_mode(3)
    elif button_name == "Right":
        update_mode(4)
    elif button_name == "Stop":
        update_mode(5)
    return "Button clicked: " + button_name

def update_mode(value):
    mode_ref = db.collection("Mode").document("mode_doc")
    mode_ref.update({"value": value})

if __name__ == "__main__":
    app.run(debug=True)