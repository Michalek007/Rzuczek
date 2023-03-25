from flask import render_template, url_for, request, redirect, jsonify, flash
from flask_jwt_extended import create_access_token, jwt_required, get_jwt_identity
from flask_jwt_extended import set_access_cookies, unset_jwt_cookies
from app import app, bcrypt
from database import *


@app.route("/", methods=['POST', 'GET'])
def base():
    return render_template('base.html')


@app.route('/register/', methods=['GET', 'POST'])
def register():
    if request.method == 'GET':
        return render_template('register.html')

    username = request.form['login']
    test = User.query.filter_by(username=username).first()
    if test:
        return jsonify(message='That username is taken!'), 409
    else:
        pin = request.form['password']
        pw_hash = bcrypt.generate_password_hash(pin)
        user = User(username=username, pw_hash=pw_hash)
        db.session.add(user)
        db.session.commit()
        return jsonify(message='User created successfully.'), 201


@app.route('/login/', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')

    if request.is_json:
        username = request.json['login']
        password = request.json['password']
    else:
        username = request.form['login']
        password = request.form['password']
    test = User.query.filter_by(username=username).first()
    if test:
        test_user = User.query.filter_by(username=username).first()
        if bcrypt.check_password_hash(test_user.pw_hash, password):
            access_token = create_access_token(identity=username)
            resp = jsonify({'login': True})
            set_access_cookies(resp, access_token)
            return jsonify(message='Login succeeded', access_token=access_token), 201
        else:
            return jsonify(message='Wrong password'), 401
    else:
        return jsonify(message='There is no account with that username'), 401


@app.route('/logout', methods=['POST'])
def logout():
    resp = jsonify({'logout': True})
    unset_jwt_cookies(resp)
    return resp, 200


@app.route("/protected", methods=["GET"])
@jwt_required()
def protected():
    # Access the identity of the current user with get_jwt_identity
    current_user = get_jwt_identity()
    return jsonify(logged_in=current_user), 200


@app.route('/users/<int:id>/', methods=['GET'])
@app.route('/users/', methods=['GET'])
def users(id: int = None):
    if id is None:
        users_list = User.query.all()
        return jsonify(users=users_schema.dump(users_list))
    user = User.query.filter_by(id=id).first()
    if user:
        return jsonify(user=user_schema.dump(user))
    else:
        return jsonify(message='There is no user with that id'), 404


@app.route('/params/<int:id>/', methods=['GET'])
@app.route('/params', methods=['GET'])
def params(id: int = None):
    if id is None:
        parameters = Parameters.query.all()
        return jsonify(performance=parameters_schema.dump(parameters))
    parameters = Parameters.query.filter_by(id=id).first()
    if parameters:
        return jsonify(performance=parameters_schema.dump(parameters))
    else:
        return jsonify(message='There are no parameters with that id'), 404


@app.route('/delete_params/<int:id>/', methods=['DELETE'])
def delete_params(id):
    parameters = Parameters.query.filter_by(id=id).first()
    if parameters:
        db.session.delete(parameters)
        db.session.commit()
        return jsonify(message='You deleted parameters from ' + parameters.date + ' !'), 202
    else:
        return jsonify(message='There are no parameters with that id'), 404


@app.route('/parameters/', methods=['GET'])
def parameters():
    temp = request.args.get("temp")
    press = request.args.get("press")
    absl = request.args.get("absl")
    print(temp)
    print(press)
    print(absl)

    params = Parameters(temp=temp, press=press, absl=absl)
    db.session.add(params)
    db.session.commit()

    return jsonify(message='Parameters added successfully'), 200


@app.route('/robot/', methods=['GET'])
def robot():
    return render_template('robot.html')
