CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCC 03.f
CCC
CCC Purpose:  emulate suspected behavior of [RSLogix Emulate500] when
CCC           it multiplies two 16-bit INTEGER words with overflow:  the
CCC           words are moved into REALs; the REALs are multiplied;
CCC           the REAL product is extracted modulo 65536.
CCC
CCC           Since 32-bit REALs maintain only the most significant 24
CCC           bits of precision, up to at least five of the least
CCC           significant bits may be lost in this process
CCC
CCC Call the MUL16 subroutine below with several values, expected output:
CCC
CCC gfortran 03.f -o 03
CCC ./03
CCC        20077      -20423  20077 -20423  -6587  -6592  -6592.00000         -5
CCC       -32767      -32767 -32767 -32767 -32767 -32768  -32768.0000         -1
CCC       -32765      -32767 -32765 -32767 -32765 -32768  -32768.0000         -3
CCC       -32761      -32767 -32761 -32767 -32761 -32768  -32768.0000         -7
CCC       -32753      -32767 -32753 -32767 -32753 -32768  -32768.0000        -15
CCC       -32737      -32767 -32737 -32767 -32737 -32768  -32768.0000        -31
CCC       -32705      -32767 -32705 -32767 -32705 -32704  -32704.0000          1
CCC       -32641      -32767 -32641 -32767 -32641 -32640  -32640.0000          1
CCC       -32513      -32767 -32513 -32767 -32513 -32512  -32512.0000          1
CCC
CCC          ij4         jj4    ii2   jj2     ki2    Li2          kr4     Li2-ki2
CCC        input       input   =ij4  =jj4 ii2*ji2  =REAL         REAL      error
CCC                                       correct <----incorrect---->
CCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      implicitnone

      integer i
      integer j
      integer*4 ij4 / 20077/
      integer*4 jj4 /-20423/

      call mul16(20077,-20423)

      j = 2
      jj4 = -32767
      do i=1,8
        ij4 = -32769 + j
        call mul16(ij4,jj4)
        j = j + j
      enddo
      end

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      subroutine mul16(ij4,jj4)
      implicitnone

C     Two 32-bit INTEGER arguments:  multiplicand; multiplier

      integer*4 ij4
      integer*4 jj4

C     Three 16-bit INTEGERs:  multiplicand; multiplier; product

      integer*2 ii2
      integer*2 ji2
      integer*2 ki2

C     Three 32-bit REALs:  multiplicand; multiplier; product

      real*4 ir4
      real*4 jr4
      real*4 kr4

C     A 16-bit INTEGER to receive the REAL product

      integer*2 Li2
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

C     Move input arguments from 32-bit to 16-bit INTEGERs

      ii2 =  ij4
      ji2 =  jj4

C     Perform the 16-bit INTEGER multiplication; constrain the result
C     to the 15-bit range [-32768:0)

      ki2 = ii2 * ji2
      if (ki2.gt.-1) ki2 = ki2 + (-32768)

C     Perform the suspected behavior of [RSLogix Emulate500]
C     1) Move 16-bit INTEGER multiplicand and multiplier to REALs
C     2) Perform multiplication of REALs, modul0 65536
C     3) Move real back to INTEGER Li2
C     4) Constrain value to [-32768:0)

      ir4 = ii2
      jr4 = ji2
      kr4 = mod(ir4 * jr4,65536.0)
      Li2 = kr4
      if (Li2.gt.-1) Li2 = Li2 + (-32768)

C     4) Constrain REAL value to [-32768:0)

      if (kr4.lt.-32768.0) kr4 = kr4 + 65536.0
      if (kr4.ge.0.0) kr4 = kr4 - 32768.0

C     Output results and error (delta between INT*INT and REAL*REAL)

      print*, ij4,jj4, ii2,ji2, ki2, Li2, kr4, Li2-ki2

      return
      end
