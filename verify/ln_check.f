CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C Calculate 32-bit polynomial-based approximations for ln, and compare
C those results to that of the intrinsic LN function
C
C Arguments
C
C          X  REAL*4; input; ln argument, radians
c      TRULN  REAL*4; output; of intrinsic LN(X) function
C      NASLN  REAL*4; output; of NASA polynomial approximation
C      TAYLN  REAL*4; output; of Taylor series approximation
C   ERRLN(2)  REAL*4; output; errors wrt TRULN of NAS/TAYLN
C
      subroutine ln_check(x,xshift,truln,nasln,tayln,errln)
      implicitnone
      real*4 x
      real*4 xshift
      real*4 truln
      real*4 nasln
      real*4 tayln
      real*4 errln(2)

C     Cf. https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19720010958.pdf

      real*4 Q00 /  0.1500045909E+1 /
      real*4 Q01 / -0.9046338042E+0 /

C     Intermediate values
      integer*4 i
      real*4 y
      real*4 y2
      real*4 taytrm
      real*4 ln2
      real*4 sqrt2
      real*4 nln2
      real*4 xshiftlim

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

C     Use intrinsic function as "truth"
      truln = log(x)

      ln2 = log(2.0)
      sqrt2 = sqrt(2.0)
      nln2 = 0.0
      xshift = x

      xshiftlim = sqrt2 / 256.0
      if (xshift.lt.xshiftlim) then
        xshift = xshift * 256.0
        nln2 = nln2 + (8.0 * ln2)
      endif

      xshiftlim = sqrt2 / 16.0
      if (xshift.lt.xshiftlim) then
        xshift = xshift * 16.0
        nln2 = nln2 + (4.0 * ln2)
      endif

      xshiftlim = sqrt2 / 4.0
      if (xshift.lt.xshiftlim) then
        xshift = xshift * 4.0
        nln2 = nln2 + (2.0 * ln2)
      endif

      xshiftlim = sqrt2 / 2.0
      if (xshift.lt.xshiftlim) then
        xshift = xshift * 2.0
        nln2 = nln2 + (1.0 * ln2)
      endif

C     Converted argument, and argument squared
      y = (xshift - 1) / (xshift + 1)
      y2 = y*y

C     Chebyshev-based polynomial

      nasln = (y * (2 + (y2 / (q00 + (q01 * y2)))) - nln2)
      errln(1) = nasln - truln

C     Taylor series

      tayln = -nln2
      taytrm = -1.0
      do i=5,1,-1
        taytrm = ((xshift - 1.0) ** i) / i
        if (mod(i,2).eq.0) taytrm = -taytrm
        tayln = tayln + taytrm
      enddo
      errln(2) = tayln - truln

      end

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C Main program

      implicitnone
      real*4 truln
      real*4 nasln
      real*4 tayln
      real*4 errln(2)

C [i] is integer counter, degrees
C [factor] is the factor per step

      integer i
      real*4 factor
      real*4 x
      real*4 xshift

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

C     Calculate conversion factor

      factor = exp(log(2.0)/40)

C     Loop over all integer angles in range [-90:+90] ([-PI/2:+PI/2])
C     - Call ln_check with each angle converted to radians
C     - Print results

      x = sqrt(2.0) / 2.0
      do i=-20,20,1
        if (i.eq.0) x = 1.0
        call ln_check(x,xshift,truln,nasln,tayln,errln)
        print*,i,x,xshift,truln,nasln,tayln,errln
        x = x * factor
      enddo

      x = 1.0 / 32768.0
      do i=1,16
        call ln_check(x,xshift,truln,nasln,tayln,errln)
        print*,i,x,xshift,truln,nasln,tayln,errln
        call ln_check(sqrt(2.0)*x,xshift,truln,nasln,tayln,errln)
        print*,i,sqrt(2.0)*x,xshift,truln,nasln,tayln,errln
        x = x * 2.0
      enddo
      end
