
FC=gfortran

STDERR=/dev/null

EXES=check_sin 02 01

run: $(EXES:%=run_%)

run_check_sin: check_sin
	./$< | tee check_sin_results.txt | tail

run_%: %
	./$<

check_sin: check_sin.f Makefile
	$(FC) $< -o $@

02: 02.c Makefile
	$(CC) $< -o $@

01: 01.c Makefile
	( gcc 01.c -o 01 2>$(STDERR) && echo QSucceeded with plain buildQ | tr Q \\n ) \
	|| ( echo QFailed plain buildQ | tr Q \\n && false ) \
	|| ( gcc -D__HELPER_01__ 01.c -o 01 2>$(STDERR) && echo Succeeded with modified buildQ | tr Q \\n ) \
	|| ( echo Failed modified buildQ | tr Q \\n && false )

clean:
	$(RM) 01 02 check_sin *.exe *.exe.stackdump
