from flask import url_for
from conftest import app


def test_delete_params(client):
    with app.app_context():
        url = url_for('delete_params',
                      id=1000000)
    response = client.delete(url).json
    assert response['message'] == 'There are no parameters with that id'


def test_delete_note(client):
    with app.app_context():
        url = url_for('delete_note',
                      id=1000000)
    response = client.delete(url).json
    assert response['message'] == 'There is no note with that id'


def test_params(client):
    with app.app_context():
        url = url_for('params',
                      id=1000000)
    response = client.get(url).json
    assert response['message'] == 'There are no parameters with that id'


def test_notes(client):
    with app.app_context():
        url = url_for('notes',
                      id=1000000)
    response = client.get(url).json
    assert response['message'] == 'There is no note with that id'
