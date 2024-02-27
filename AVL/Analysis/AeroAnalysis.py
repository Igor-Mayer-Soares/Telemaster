# Aerodynamics Analysis Tool
# Author: Igor Mayer Soares
# Aeronautics Institute of Technology - ITA
# igor.soares@ga.ita.br

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import re

if __name__ == "__main__":
    # Read the CSV file
    df      = pd.read_csv('AeroData.csv')
    
    alpha   = np.array([-10,-5,0,5,10,15])
    beta    = np.array([-10,-5,5,10])

    alpha_var = df.filter(regex=f'^A', axis=1).to_numpy()
    beta_var  = df.filter(regex=f'^B', axis=1).to_numpy()
    Coeffs    = df.filter(regex=f'^Variable', axis=1)

# Longitudinal Coefficients
CDde_vec  = alpha_var[4]
CLa_vec   = alpha_var[6]
CLde_vec  = alpha_var[9]
CLq_vec   = alpha_var[12]
Cma_vec   = alpha_var[30]
Cmde_vec  = alpha_var[33]
Cmq_vec   = alpha_var[36]

# Lateral Coefficients
CDda_vec  = beta_var[3]
CDdr_vec  = beta_var[5]
CYb_vec   = beta_var[15]
CYda_vec  = beta_var[16]
CYdr_vec  = beta_var[18]
CYp_vec   = beta_var[19]
CYr_vec   = beta_var[21]
Clb_vec   = beta_var[23]
Clda_vec  = beta_var[24]
Cldr_vec  = beta_var[26]
Clp_vec   = beta_var[27]
Clr_vec   = beta_var[29]
Cnb_vec   = beta_var[39]
Cnda_vec  = beta_var[40]
Cndr_vec  = beta_var[42]
Cnp_vec   = beta_var[43]
Cnr_vec   = beta_var[45]

# Interpolation
CDde = str(np.poly1d(np.polyfit(alpha,CDde_vec,2))).replace('x', '*alpha').replace('alpha','pow(alpha,2)',1)
CLa  = str(np.poly1d(np.polyfit(alpha,CLa_vec,2))).replace('x','*alpha').replace('alpha','pow(alpha,2)',1)
CLde = str(np.poly1d(np.polyfit(alpha,CLde_vec,2))).replace('x','*alpha').replace('alpha','pow(alpha,2)',1)
CLq  = str(np.poly1d(np.polyfit(alpha,CLq_vec,2))).replace('x','*alpha').replace('alpha','pow(alpha,2)',1)
Cma  = str(np.poly1d(np.polyfit(alpha,Cma_vec,2))).replace('x','*alpha').replace('alpha','pow(alpha,2)',1)
Cmde = str(np.poly1d(np.polyfit(alpha,Cmde_vec,2))).replace('x','*alpha').replace('alpha','pow(alpha,2)',1)
Cmq  = str(np.poly1d(np.polyfit(alpha,Cmq_vec,2))).replace('x','*alpha').replace('alpha','pow(alpha,2)',1)

CDda = str(np.poly1d(np.polyfit(beta,CDda_vec,2))).replace('x','*beta').replace('beta','pow(beta,2)',1)
CDdr = str(np.poly1d(np.polyfit(beta,CDdr_vec,2))).replace('x','*beta').replace('beta','pow(beta,2)',1)
CYb  = str(np.poly1d(np.polyfit(beta,CYb_vec,1))).replace('x','*beta')
CYda = str(np.poly1d(np.polyfit(beta,CYda_vec,1))).replace('x','*beta')
CYdr = str(np.poly1d(np.polyfit(beta,CYdr_vec,1))).replace('x','*beta')
CYp  = str(np.poly1d(np.polyfit(beta,CYp_vec,1))).replace('x','*beta')
CYr  = str(np.poly1d(np.polyfit(beta,CYr_vec,1))).replace('x','*beta')
Clb  = str(np.poly1d(np.polyfit(beta,Clb_vec,1))).replace('x','*beta')
Clda = str(np.poly1d(np.polyfit(beta,Clda_vec,1))).replace('x','*beta')
Cldr = str(np.poly1d(np.polyfit(beta,Cldr_vec,1))).replace('x','*beta')
Clp  = str(np.poly1d(np.polyfit(beta,Clp_vec,1))).replace('x','*beta')
Clr  = str(np.poly1d(np.polyfit(beta,Clr_vec,1))).replace('x','*beta')
Cnb  = str(np.poly1d(np.polyfit(beta,Cnb_vec,1))).replace('x','*beta')
Cnda = str(np.poly1d(np.polyfit(beta,Cnda_vec,1))).replace('x','*beta')
Cndr = str(np.poly1d(np.polyfit(beta,Cndr_vec,1))).replace('x','*beta')
Cnp  = str(np.poly1d(np.polyfit(beta,Cnp_vec,1))).replace('x','*beta')
Cnr  = str(np.poly1d(np.polyfit(beta,Cnr_vec,1))).replace('x','*beta')

print(CYda)

