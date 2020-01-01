
GNG_DATA=Gaussian_number_generator.htm

LEAVE_DUPS=LEAVE_DUPS=

run:
	$(LEAVE_DUPS) python parse_gng_data_micro_logix_run_anderson_darling.py < $(GNG_DATA)

run_skip_dups:
	make -f $(firstword $(MAKEFILE_LIST)) LEAVE_DUPS=

