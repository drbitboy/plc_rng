
FC=gfortran

STDERR=/dev/null

EXES=ln_check sin_check 01 02_15bitlcg 02_31bitlcg

run: $(EXES:%=run_%)

run_ln_check: ln_check
	./$< | tee ln_check_results.txt | tail

run_sin_check: sin_check
	./$< | tee sin_check_results.txt | tail

run_%: %
	./$<

ln_check: ln_check.f Makefile
	$(FC) $< -o $@

sin_check: sin_check.f Makefile
	$(FC) $< -o $@

02_15bitlcg: 02.c Makefile
	$(CC) $< -o $@

02_31bitlcg: 02.c Makefile
	$(CC) -DBIT31 $< -o $@

01: 01.c Makefile
	( gcc 01.c -o 01 2>$(STDERR) && echo QSucceeded with plain buildQ | tr Q \\n ) \
	|| ( echo QFailed plain buildQ | tr Q \\n && false ) \
	|| ( gcc -D__HELPER_01__ 01.c -o 01 2>$(STDERR) && echo Succeeded with modified buildQ | tr Q \\n ) \
	|| ( echo Failed modified buildQ | tr Q \\n && false )

clean:
	$(RM) $(EXES) *.exe *.exe.stackdump
