# wow old models

This project is to bring back world of warcraft old models for draenei, night elves.

More support towards Blood elves old models since their files are broken.


I could only provide files for enUS.


For other clients, you need use cascviewer to extract dbfilesclient/creaturedisplayinfoextra.db2 and dbfilesclient/chrraces.db2. Use creaturedisplayinfoextra.exe and chrraces.exe to modify them.


cascview-64

http://www.zezula.net/en/casc/main.html

listfile

https://github.com/bloerwald/LegionFiles


Need to compile source code?
Use mingw-64 (recommend for using https://gcc-mcf.lhmouse.com/ or https://nuwen.net/mingw.html) or Visual studio (require boost library http://www.boost.org/) to compile my C++ code to change them.

For gcc:

g++ -o creaturedisplayinfoextra creaturedisplayinfoextra.cc -O2

g++ -o chrraces chrraces.cc -O2

For visual studio

cl -EHsc -Ox creaturedisplayinfoextra.cc

cl -EHsc -Ox chrraces.cc
