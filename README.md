**This is my first c project.**
***
# renfl (REName FiLes)
Rename files that don't respect decimal places

This project born of necessity to rename files of family pictures. 
Example:
---
*before (A mess to view this on GNU/Linux)*
```
ubatuba_beach-2010-07-02-1.jpg
ubatuba_beach-2010-07-02-2.jpg
...
ubatuba_beach-2010-07-02-9.jpg
ubatuba_beach-2010-07-02-10.jpg
ubatuba_beach-2010-07-02-11.jpg
ubatuba_beach-2010-07-02-12.jpg
ubatuba_beach-2010-07-02-13.jpg
...
```
*after*
```
ubatuba_beach-2010-07-02-01.jpg
ubatuba_beach-2010-07-02-02.jpg
...
ubatuba_beach-2010-07-02-09.jpg
ubatuba_beach-2010-07-02-10.jpg
ubatuba_beach-2010-07-02-11.jpg
ubatuba_beach-2010-07-02-12.jpg
ubatuba_beach-2010-07-02-13.jpg
...
```
***
How to use
---
```
renfl [options] <file-1.*> [file-2.*] ...
  -p, --pretend               shows what could be done but it does't.
  -r, --regex 'REGEX'         change regular expression.
  -z, --decimal-places n      'n'umber of decimal places. Default is 2.
  -V, --version               shows version and exit.
  -h, --help                  show this help and exit.
```
### Default REGEX:
`'.*-[1-9]?[1-9]?[0-9]\.[[:alpha:]].*'`

It's match with *arq-1.jpg*, *ArQ2-12.png*, *anyname54-42-128.gif* and *abc-001.jpg*, for example.
