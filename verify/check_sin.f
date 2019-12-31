CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C Calculate 32-bit polynomial-based approximations for sine, and compare
C those results to that of the intrinsic SIN function
C
C Arguments
C
C           Y  REAL*4; input; sine argument, radians
c      TRUSIN  REAL*4; output; of intrinsic SIN(Y) function
C      CHBSIN  REAL*4; output; of Chebyshev-as-polynomial approximation
C      TAYSIN  REAL*4; output; of Taylor series approximation
C      ULPSIN  REAL*4; output; of Chebyshev-ish approximation
C   ERRSIN(3)  REAL*4; output; errors wrt TRUSIN of CHB/TAY/ULPSIN
C
C Other resources:
C
C   https://www.ams.org/journals/mcom/1980-34-149/S0025-5718-1980-0551302-5/S0025-5718-1980-0551302-5.pdf
C
      subroutine check_sin(y,trusin,chbsin,taysin,ulpsin,errsin)
      implicitnone
      real*4 y
      real*4 trusin
      real*4 chbsin
      real*4 taysin
      real*4 ulpsin
      real*4 errsin(3)

C     Not used here:
C     Cf. https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19720010958.pdf
C
C     real*4 P00 / -.1666288040e0 /
C     real*4 P01 / .8150604487e-2 /
C     chbsin = y * (1 + (y2 * (P00 + (y2 * P01))))

C     Cf. https://stackoverflow.com/questions/345085/how-do-trigonometric-functions-work/
      real*4 C1 / .9999966  /
      real*4 C3 / -.16664824 /
      real*4 C5 / .00830629 /
      real*4 C7 / -.00018363 /

C     Cf. http://mooooo.ooo/chebyshev-sine-approximation/,
C     "Approximating sin(x) to 5 ULP with Chebyshev polynomials"

      real*4 ULP(6) /-0.10132118,        0.0066208798
     &              ,-0.00017350505,     0.0000025222919
     &              ,-0.000000023317787, 0.00000000013291342
     &              /
      real*4 ULP_pi_major /3.1415927/
      real*4 ULP_pi_minor /-0.00000008742278/

C     Intermediate values
      integer*4 i
      real*4 y2
      real*4 denom
      real*4 taytrm

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

C     Use intrinsic function as "truth"
      trusin = sin(y)

C     Argument squared
      y2 = y*y

C     Chebyshev-based polynomial

      chbsin = y * (C1 + (y2 * (C3 + (y2 * (C5 + (y2 * C7))))))
      errsin(1) = chbsin - trusin

C     Taylor series

      taysin = y
      taytrm = y
      do i=3,11,2
        taytrm = taytrm * y2 / ((1.0-i)*i)
        taysin = taysin + taytrm
      enddo
      errsin(2) = taysin - trusin

C     Cf. http://mooooo.ooo/chebyshev-sine-approximation/,

      ulpsin = 0.0
      do i=6,1,-1
        ulpsin = (ulpsin * y2) + ULP(i)
      enddo
      ulpsin = (y - ULP_pi_major - ULP_pi_minor)
     &       * (y + ULP_pi_major + ULP_pi_minor)
     &       * ulpsin * y
C     ulpsin = ulpsin * y
      errsin(3) = ulpsin - trusin
      end

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C Main program

      implicitnone
      real*4 trusin
      real*4 chbsin
      real*4 taysin
      real*4 ulpsin
      real*4 errsin(3)

C [i] is integer counter, degrees
C [rpd] is the conversion factor from degrees to radians

      integer i
      real*4 rpd

CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

C     Calculate conversion factor

      rpd = datan(1d0) / 45d0

C     Loop over all integer angles in range [-90:+90] ([-PI/2:+PI/2])
C     - Call check_sin with each angle converted to radians
C     - Print results

      do i=-90,90,1
        call check_sin(i*rpd,trusin,chbsin,taysin,ulpsin,errsin)
        print*,i,trusin,chbsin,taysin,ulpsin,errsin
      enddo
      end
