"""
Usage:

  python parse_gng_data_run_anderson_darling.py < Compact_AOI_Test.L5X

Expected results for Compact_AOI_Test.L5X*

  {'mean': 0.00107577450613001, 'stddev': 0.9750078972656193}
  {'anderson': AndersonResult(statistic=0.24714887810432629
  , critical_values=array([0.574, 0.653, 0.784, 0.914, 1.088])
  , significance_level=array([15. , 10. ,  5. ,  2.5,  1. ]))
  }

* MD5 checksum = e585178251072c8bb8bae02bf7d2960eA)


Sample of data from Compact_AOI_Test.L5X:

  [...]
  <Array DataType="REAL" Dimensions="1000" Radix="Float">^M
  <Element Index="[0]" Value="-0.3287957"/>^M
  <Element Index="[1]" Value="-0.43335447"/>^M
  <Element Index="[2]" Value="0.5401235"/>^M
  <Element Index="[3]" Value="0.97914433"/>^M
  <Element Index="[4]" Value="0.124257356"/>^M
  [...]
  <Element Index="[998]" Value="1.5655007"/>
  <Element Index="[999]" Value="-1.1983824"/>
  </Array>


"""

import re
import os
import sys
import numpy

do_debug = 'DEBUG' in os.environ

### Regular exprsion fo
rgx_start = re.compile('^<Array DataType="REAL" Dimensions="1000"')
rgx_end = re.compile('^</Array>')

ct = -1
lt_vals = list()
for rawline in sys.stdin:

  if do_debug: print(dict(ct=ct,rawline=rawline))

  if 0>ct:
    if rgx_start.match(rawline.strip()): ct = 0
    continue

  if rgx_end.match(rawline.strip()): break

  lt_vals.append(float(rawline.split('"')[3]))
  ct += 1

arr = numpy.array(lt_vals)

print(dict(mean=arr.mean(),stddev=arr.std(),count=ct))

try:
  import scipy.stats as ss
except:
  ss = False

if ss: print(dict(anderson=ss.anderson(arr,dist='norm')))
else : print('Anderson-Darling tests are not available via scipy.stats on this system')
