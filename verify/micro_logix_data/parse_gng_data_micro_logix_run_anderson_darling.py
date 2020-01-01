"""
Purpose:  verify that Gaussian-distribution random number data in
          file GNG_save_data_view_halted.htm are indeed normal


Usage:

  make

    OR

  python parse_gng_data_run_anderson_darling.py < Compact_AOI_Test.L5X


Expected results for GNG_save_data_view_halted.htm

{'mean': -0.07299352643229169, 'stddev': 1.0703175443958814, 'count': 768}
{'anderson': AndersonResult(statistic=9.080452969401904
           , critical_values=array([0.573, 0.653, 0.783, 0.913, 1.086])
           , significance_level=array([15. , 10. ,  5. ,  2.5,  1. ]))
           }

* MD5 checksum = e3888dd6dd950002ab92d0454ae0c103


Sample of data from GNG_save_data_view_halted.htm:

  [...]
<p>F9:0         0.5433941    -0.4559816    -0.1928478    -0.2416197     0.4358808 </p>
<p>F9:5         -1.261506    -0.9924026    -0.9243795     -1.031823      1.581378 </p>
<p>F9:10        0.4258973      2.285063      1.851425    -0.5542648    -0.1174393 </p>
  [...]
<p>F10:0       -0.3779179      1.828362     -1.547203     0.3377873      1.608895 </p>
<p>F10:5      -0.05709658    -0.5159178     -2.453258     -1.126848    -0.7740583 </p>
<p>F10:10      -0.3145958     -1.042118     0.7537348      1.193819    0.02235698 </p>
  [...]
<p>F10:245    -0.05709658    -0.5159178     -2.453258     -1.126848    -0.7740583 </p>
<p>F10:250     -0.3145958     -1.042118     0.7537348      1.193819    0.02235698 </p>
<p>F10:255       1.110291 </p>
  [...]
<p>F12:0        -1.277109     0.2198334     0.8934317    -0.2225185     0.3156725 </p>
<p>F12:5         2.588002     -1.387783    -0.2768764     0.4505051    -0.1924003 </p>
<p>F12:10       -1.180793    -0.5080417     -1.310705    -0.9500581    -0.2449654 </p>
<p>F12:250      -1.180793    -0.5080417     -1.310705    -0.9500581    -0.2449654 </p>
<p>F12:255      0.9243801 </p>
  [...]
"""

import re
import os
import sys
import numpy

do_debug = 'DEBUG' in os.environ
skip_dups = 'SKIP_DUPS' in os.environ

def read_data(fin):

  ### Regular expressions for start and end of data
  ### - Assume gaussian data are only data in file with a dimension
  ###   greater than 99

  rgx = re.compile('^<p>F(9|10|11|12):\d+ .*\d +</p>$')


  ct = 0
  lt_vals = list()

  ### Loop over lines in STDIN

  for rawline in fin:

    if do_debug: print(dict(ct=ct,rawline=rawline))

    ### If matching line is found, parse it

    if rgx.match(rawline.strip()):

      lt_vals.extend(rawline.strip().split()[1:-1])
      ct = len(lt_vals)

  ### Optionally remove duplicates, then convert the list to a numpy
  ### array; print the mean and std. dev.

  if skip_dups: lt_vals = list(set(lt_vals))

  return numpy.array(list(map(float,lt_vals)))


if "__main__" == __name__:

  arr = read_data(sys.stdin)
  ct = len(arr)
  print(dict(mean=arr.mean(),stddev=arr.std(),count=ct))

  ### Try to import scipy.stats, to get the Anderson-Darling tests

  try:
    import scipy.stats as ss
  except:
    ss = False

  ### Run the Anderson-Darling normality tests

  if ss: print(dict(anderson=ss.anderson(arr,dist='norm')))
  else : print('Anderson-Darling tests are not available via scipy.stats on this system')
