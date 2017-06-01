# xdomain
Extends primitive (number) data types formaly by '+-Infinity' and 'Undefined'. XDomain is a header-only class and supplies the following operations: +,-,\*,/,++,--,+=,-=,/=,*=,<,>,==,<=,>=,!=,=. Furthermore standard IO-Operation << and >> are implemented as well (>> only for the XDatatypes, see blow)

## Setup
Copy the File 'XDomain.h' into your Project and include it:
<blockquote>
<p>#include"XDomain.h"</p>
</blockquote>

## XDatatypes
XDomain may work with other datatypes, but by default it supports int, long, long long, float, double, long double. For other datatypes >> is not implemented, (yet?).
For the sake of simplicity XDomain provides some shorthand notation for the supplied datatypes:

        XDomain<int>                    |       int
        XDomain<long>                   |       Xlong
        XDomain<long long>              |       Xlonglong
        XDomain<float>                  |       Xfloat
        XDomain<double>                 |       Xdouble
        XDomain<long double>            |       Xlongdouble

## Examples

### Example 1
        #include "XDomain.h"
        
        int main() {
          Xint pos = POS_INF;
          Xint neg = NEG_INF;
          std::cout << pos << "\n" << neg;
          /*Output:
          +INF
          -INF
          */
          return 0;
        }

### Example 2
        #include "XDomain.h"
        
        int main() {
          Xint val = -1;
          Xint neg = NEG_INF;
          Xint res = val*neg;
          std::cout << res;
          /*Output:
          +INF
          */
          return 0;
        }
        
### Example 3
      #include "XDomain.h"
        
        int main() {
          Xint val = 342;
          Xint zero = 0;
          Xint inf = val/zero;
          std::cout << inf;
          /*Output:
          +INF
          */
          return 0;
        }

## Contributors
chtoli (Christian Linz)
