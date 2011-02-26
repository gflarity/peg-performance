#About
This repository contains the source code for solving the 15-Hole Peg Soltaire game in a number of different programming languages. It is based off the code Jonathan Fuerth wrote for his presentation on Java/HotSpot performance. You will find that presentation here -> https://sites.google.com/site/torontojava/2010-slides-and-notes-1/2010-02-21slides-javaperformance.pdf. 

*Spoiler alert*

His results showed that Java under the HotSpot VM is faster than C, which is considerably faster than everything else. Jonathan recently ran his tests again and I was excited to hear that javascript/Chrome/V8 performance has improved considerably in the last year.  Namely, it was 17x slower than Java/HotSpot and therefore faster than everything else except C and Java/HotSpot. My goal is thus to modify the source so it's simple to run the JavaScript source under node.js, then track the results with each release of node.js other time. My hypothesis is that the performance of JavaScript/nodejs/V8 is going to reach and even eclipse the performance of the HotSpot VM eventually. 

#License
BSD



