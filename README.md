# Mathematics-Expressions-Parsing
Answer to an exercise in BuildYourOwnLisp

Answer to the last Bonus Mark in link below: 

http://www.buildyourownlisp.com/chapter6_parsing

# How to use the binaries?
Binaries are built with Cygwin on Windows. All the required .dlls are in the bin folder.

    lispy> 1 + ( 21 / 45 )
    >
    regex
    expr|number|regex:1:1 '1'
    operator|char:1:3 '+'
    expr|>
      char:1:5 '('
      expr|number|regex:1:7 '21'
      operator|char:1:10 '/'
      expr|number|regex:1:12 '45'
      char:1:15 ')'
    regex
    lispy>
