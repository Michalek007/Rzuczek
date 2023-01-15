from app import *
from configuration import TestingConfig
import pytest


@pytest.fixture
def client():
    app.config.from_object(TestingConfig)
    with app.test_client() as client:
        yield client
