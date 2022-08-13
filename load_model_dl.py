from flask import Flask
from flask_cors import CORS, cross_origin
from flask import request
import tensorflow as tf


sess = tf.Session()
graph = tf.get_default_graph()


app = Flask(__name__)   # init flask
CORS(app)               #apply flask CORS
app.config['CORS_HEADERS'] = 'Content-Type'

@app.route('/face_regconition', methods=['POST'])
@cross_origin(origins='*')
def face_regconition():
    face_img = request.form.get("input_img")
    with sess.as_default():
        with graph.as_default():
            name = face_model.predict(face_img)
    return name

if __name__ =='__main__':

    app.run(host='0.0.0.0', port='9999')