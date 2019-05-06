import json
import logging
import constants as c
import os

def update_with_path(filepath, input_dict):
    """ updates the 200E and 200W file path by making it a full path """
    for key in [c._200E_KEY, c._200W_KEY]:
        input_dict[c.SOURCE_FILES_KEY][key] = os.path.abspath(
                os.path.join(filepath, input_dict[c.SOURCE_FILES_KEY][key]))

    return input_dict

def parse_input_file(filename):
    """
        parse the input file; update paths as necessary
    """

    logging.info("parsing input file: {}".format(filename))
    with open(filename, 'r') as f:
        input_dict = json.loads(f.read())
    
    filepath = os.path.dirname(filename)
    input_dict = update_with_path(filepath, input_dict)

    return input_dict
