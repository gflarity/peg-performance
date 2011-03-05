#About
This repository contains the source code for solving the 15-Hole Peg Soltaire game in a number of different programming languages. It is based off the code that Jonathan Fuerth wrote for his presentation on Java/HotSpot performance. You will find that presentation [here](https://sites.google.com/site/torontojava/2010-slides-and-notes-1/2010-02-21slides-javaperformance.pdf).

*Spoiler alert*

His results showed that Java under the HotSpot VM is faster than everything else provided including C. However, what interests me the most is that JavaScript under V8 comes in second once you use proper prototypical inherentence. That's right, Java > JavaScript > C for this test. 

Of course there are caveats. The C code provided by the project being reviewed follows an Object Oriented style. It is certainly possible to optimize this code further using a more procedural style with less memory allocation. But then this style of coding should be adapted to the other languages presented as well. Further more I'd argue that maintaining code written in this matter difficult and expensive. Regardless, I whole heartedly encourge you submit pull requests with these new versions in separate directories based on the style/technique used.


#License
BSD



