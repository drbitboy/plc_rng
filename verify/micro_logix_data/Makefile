
GNG_DATA=Gaussian_number_generator.htm

SKIP_DUPS=

run:
	$(SKIP_DUPS) python parse_gng_data_micro_logix_run_anderson_darling.py < $(GNG_DATA)

run_skip_dups:
	make -f $(firstword $(MAKEFILE_LIST)) SKIP_DUPS=SKIP_DUPS=

