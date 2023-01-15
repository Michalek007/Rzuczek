# REST-API-Template

**Complete Flask application template, with useful plugins.**

It contains:
* user authentication with Jason Web Token
* database created using SQLAlchemy
* CRUD functionality for notes and computer performance
* task scheduler with APScheduler
* tests for api metods with pytest

## Requirements

Python 3.8+, pipenv

## Installation

First, clone this repository.

    $ git clone https://github.com/Michalek007/REST-API-template.git

After, install virtual environment with all necessary packages to run:

    $ python -m pipenv install

All configuration is in: `configuration.py`

## Application development

To activate virtual environment in terminal run:
    
    $ ".venv\Scripts\activate.bat"

Then if you want to install new package use this command:
    
    $ pipenv install <package_name>