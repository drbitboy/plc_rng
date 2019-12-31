    Purpose:  verify whether Gaussian-distribution random number data in
              file GNG_save_data_view_halted.htm are normal; the answer
              is no


    Usage:

      make

        OR
      parse_gng_data_micro_logix_run_anderson_darling.py < GNG_save_data_view_halted.htm


    Expected results for GNG_save_data_view_halted.htm

    {'mean': -0.07299352643229169, 'stddev': 1.0703175443958814, 'count': 768}
    {'anderson': AndersonResult(statistic=9.080452969401904
               , critical_values=array([0.573, 0.653, 0.783, 0.913, 1.086])
               , significance_level=array([15. , 10. ,  5. ,  2.5,  1. ]))
               }

    * MD5 checksum = e3888dd6dd950002ab92d0454ae0c103
