CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCC 03.f
CCC
CCC Purpose:  emulate suspected behavior of [RSLogix Emulate500] when
CCC           it multiplies two 16-bit INTEGER words with overflow:  the
CCC           words are moved into REALs; the REALs are multiplied;
CCC           the REAL product is extracted modulo 65,536.
CCC
CCC           Since 32-bit REALs maintain only the most significant 24
CCC           bits of precision, up to at least five of the least
CCC           significant bits may be lost in this process
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      subroutine mul16(ij2,jj2)
      implicitnone

      integer ij2
      integer jj2

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

C     Perform the 16-bit INTEGER multiplication; constrain the result
C     to the 15-bit range [-32,768:0)

      ii2 =  ij2
      ji2 =  jj2

      ki2 = ii2 * ji2
      if (ki2.gt.-1) ki2 = ki2 + (-32768)

C     Perform the suspected behavior of [RSLogix Emulate500]
C     1) Move 15-bit INTEGER multiplicand and multiplier to REALs
C     2) Perform multiplication of REALs, modul0 65,536
C     3) Move real back to INTEGER Li2, constrain value to [-32,768:0)

      ir4 = ii2
      jr4 = ji2
      kr4 = mod(ir4 * jr4,65536.0)

      Li2 = kr4
      if (Li2.gt.-1) Li2 = Li2 + (-32768)

C     4) Constrain REAL value to [-32,768:0)

      if (kr4.lt.-32768.0) kr4 = kr4 + 65536.0
      if (kr4.ge.0.0) kr4 = kr4 - 32768.0

C     Output results and any error

      print*, ij2,jj2, ii2,ji2, ki2, Li2, kr4, Li2-ki2

      return
      end

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      implicitnone
      integer i,j
      call mul16(20077,-20423)
      j = 2
      do i=1,8
        call mul16(-32768+j-1,-32767)
        j = j + j
      enddo
      end
