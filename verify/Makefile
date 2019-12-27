
run: 01
	./$<
	@make clean 2>/dev/null

01: 01.c Makefile
	( gcc 01.c -o 01 2>/dev/null && echo QSucceeded with plain buildQ | tr Q \\n ) \
	|| ( echo QFailed plain buildQ | tr Q \\n && false ) \
	|| ( gcc -D__HELPER_01__ 01.c -o 01 2>/dev/null && echo Succeeded with modified buildQ | tr Q \\n ) \
	|| ( echo Failed modified buildQ | tr Q \\n && false )

clean:
	$(RM) 01 01.exe
