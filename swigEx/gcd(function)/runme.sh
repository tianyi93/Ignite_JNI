swig -c++ -java example.i 
cl /c /I"C:\Program Files\Java\jdk-13.0.2\include" /I"C:\Program Files\Java\jdk-13.0.2\include\win32" "example.c" "example_wrap.c"
/LD .\example.obj .\example_wrap.obj 
javac runme.java 
java runme  