    Purpose:  Use the Anderson-Darling normality test to say whether
              the null hypothesis, that the  data in file
              Gaussian_number_generator.htm are normal, can be
              rejected; the answer is no at the all significance levels,
              and above.


    Usage:

      make

        OR

      parse_gng_data_micro_logix_run_anderson_darling.py < Gaussian_number_generator.htm


    Expected results for Gaussian_number_generator.htm*:

    {'mean': -0.05062467600058594, 'stddev': 1.0232606678082843, 'count': 1024}
    {'anderson': AndersonResult(statistic=0.12682977233043857
               , critical_values=array([0.574, 0.653, 0.784, 0.914, 1.088])
               , significance_level=array([15. , 10. ,  5. ,  2.5,  1. ]))
               }

    * MD5 checksum = 9ecb5ce3ac770a2016fdb6d3e3e6d59a



    The data in Gaussian_number_generator.htm were extracted from 

      ../../plc_programs/MicroLogix/Gaussian_number_generator.pdf
