import pandas as pd
import re
import os
from glob import glob

def read_txt_file(filename):
    filepath = os.path.join(os.getcwd(), filename)
    with open(filepath, 'r') as file:
        content = file.read()
    return content

def extract_requested_variables(content, requested_variables):
    variables = re.findall(r'(\S+)\s*=\s*([\d\.\-]+)', content)
    requested_data = {key: float(value) for key, value in variables if key in requested_variables}
    return requested_data

def save_to_csv(data, csv_filename):
    if os.path.exists(csv_filename):
        existing_data = pd.read_csv(csv_filename, index_col=0)
        existing_data = existing_data.join(pd.DataFrame(data), how='outer')  # Use outer join to handle missing values
        existing_data.to_csv(csv_filename)
    else:
        pd.DataFrame(data).to_csv(csv_filename, index=False)

if __name__ == "__main__":
    requested_variables = ['CLa', 'CYa', 'Cla', 'Cma', 'Cna', 'CLb', 'CYb', 'Clb', 'Cmb', 'Cnb',
                            'CLp', 'CYp', 'Clp', 'Cmp', 'Cnp', 'CLq', 'CYq', 'Clq', 'Cmq', 'Cnq',
                            'CLr', 'CYr', 'Clr', 'Cmr', 'Cnr', 'CLd01', 'CYd01', 'Cld01', 'Cmd01',
                            'Cnd01', 'CDffd01', 'CLd02', 'CYd02', 'Cld02', 'Cmd02', 'Cnd02',
                            'CDffd02', 'CLd03', 'CYd03', 'Cld03', 'Cmd03', 'Cnd03', 'CDffd03', 'Xnp']

    st_files = glob('*.st')  # Find all .st files in the current directory

    all_data = {}

    for st_file in st_files:
        file_content = read_txt_file(st_file)
        requested_data = extract_requested_variables(file_content, requested_variables)
        all_data[st_file[:-3]] = requested_data

    save_to_csv(all_data, 'AeroData.csv')
