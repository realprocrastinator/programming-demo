% erlang tutorial
%https://www.youtube.com/watch?v=IEhwc2q1zG4
%https://www.youtube.com/watch?v=-MEFHv2Uji4

% sytanx
help(). % commend help
C=3.
{A,B}={(45+9),C+1}. % assign tuples

io:fwrite("hello world\n").

pwd(). % print cwd

% IO format control seq
% http://erlang.org/doc/man/io.html#format-1
% https://riptutorial.com/erlang/example/12868/common-control-sequences-in-format-strings



% ----------------------------------------------------------
% functions
% Function definition (in a module)
-module(math).
-export([factorial/1]).
% this calculates factorial
factorial(0) -> 
    1; % OR
factorial(N) -> 
    io:format("factorial ~w~n", [N]), % AND
    N * factorial(N-1). % END

% 2> math:factorial(5).
% 120

% Function Evaluation Rules:
% ➜ Clauses scanned until a match is found
% ➜ All varibales in function head are bound
% ➜ Variables are local to each clause
% ➜ Body evaluated sequentially

% anonomous function
% fun means function keyword X is param , -> after is func body
F = fun(X) -> 2*X end.
F(4).

% Easiest way to think about it:
% ➜ , is AND
% ➜ ; is OR
% ➜ . is END

% lists is moodel sort is function name
lists:sort([4,5,6,1]).

% concat string
H = fun(X) -> string:concat("Hello ", X) end.

% string representation
C = "hello"
C=[104,101,108,108,111,32]. % hello
C=[$h,$e,$l,$l] % hello

% operator
4 =/= 4. % false 4 not equal 4

% erlang built in functions
date()
time()
length([1,2,3,4,5])
size({a,b,c})
atom_to_list(an_atom)
list_to_tuple([1,2,3,4])
integer_to_list(2234)
tuple_to_list({})

% special functions
% Apply the function Func in the module Mod to the arguments in the list Args.
apply(Mod, Func, Args).
apply(lists1,min_max,[[4,1,7,3,9,10]]). %{1, 10}

% ----------------------------------------------------------
% Process
% Creates a new process that evaluates the given function with
% the given arguments
Pid = spawn(Mod, Func, Args).

% Message Passing:
% A does: sends a message {A, hello, you} to process B
B ! {self(), hello, you}
% In order to receive the message B does:
receive
    {From, Msg1, Msg2} -> ...
end

% Processing messages:
% ➜ queue messages in arrival order
% ➜ test each message against all receive clauses – until match
% ➜ wait for more messages if no match
% no matching message would be put back in the que

% Selective Message Reception:
% A: C!foo
% B: C!bar
% C:
receive
    foo -> true
end,
receive
    bar -> true
end
% foo is received before bar no matter what order they were sent
% in (or how they were queued).
% will try to find the first match before continue to the second receive
% if bar is sent first, not match and would be put back into the que 
% until foo is matched then bar would be received


% Timeouts:
% Wait a given amount of time (milliseconds)
sleep(T) ->
    receive
    after
        T -> true % after T times return true
    end.

% wait forever
suspend() ->
    receive
    after
        infinity -> true % wait permenantly
    end.

% 0 is special
flush() ->
    receive
        Any -> flush()
    after
        0 -> true % flush until msg que is empty and then return
end.

% 0 means:
% ➜ Check message buffer
% ➜ If empty execute the given code (true)
% ----------------------------------------------------------
% Closure
% Values of bound variables are passed along in messages
-module(closures).
-export([do_send/4, do_receive/0]).

do_send(Dest, A, B, C) ->
    Dest ! {msg, fun(D) ->
        % values bounded with var A , B .. are passed along with messaage
        io:format("A: ~s, B: ~s, C: ~s, D: ~s~n", [A, B, C, D]) end}. 
do_receive() ->
    receive
        {msg, F} -> F("woohoo")
    end.

% 1> B = spawn(fun() -> closures:do_receive() end).
% 2> closures:do_send(B, "hello", "there", "friend")
% ----------------------------------------------------------
% output
io:format(FormatString, ArgList)
1> io:format("Hello world!~n", []).
Hello world!
2> io:format("arg1:~w, arg2:~w, arg3:~w", [1,2,5]).
arg1:1, arg2:2, arg3:5ok

% ----------------------------------------------------------
% control flow

% guarded function clauses
factorial(N) when N > 0 ->
    N * factorial(N - 1);
factorial(0) -> 1.

% example of guard
is_number(X) - X is a number
is_atom(X) - X is an atom
is_tuple(X) - X is a tuple
is_list(X) - X is a list
number(X)	- X is a number
integer(X)	- X is an integer
float(X)	- X is a float
atom(X)		- X is an atom
tuple(X)	- X is a tuple
list(X)		- X is a list

length(X) == 3	- X is a list of length 3
size(X) == 2	- X is a tuple of size 2.

X > Y + Z	- X is > Y + Z
X == Y		- X is equal to Y
X =:= Y		- X is exactly equal to Y
                  (i.e. 1 == 1.0 succeeds but
		   1 =:= 1.0 fails)

% Case and If:
case X of
    {yes, _} -> ...;
    {no, _} -> ...;
    _Else -> ...
end,
...
if
    is_integer(X) -> ...;
    is_tuple(X) -> ...;
    true -> ...
end,
...
% ----------------------------------------------------------
% tuple
element(3,{abc,def,ghi,jkl}). % get the third element in the tuple
% insert into the third place and replace the element on that index
setelement(3,{abc,def,ghi,jkl},mno).% {abc,def,mno,jkl} 
% tuple comparision
{abc,def} == {abc,mno} % false
% ----------------------------------------------------------
% compile and run code
1> c(hello). % compile the module given the file name
{ok,hello}
2> hello:hello_word(). % call the function defined in the module
hello word
% ----------------------------------------------------------
% list
% list can be dynamically sized while tuple can store only fix number of items

[4,5,"good time",{3,4,"too"}]

[1,2,3] ++ [3,4]. % [1,2,3,3,4]
[a,b,c] ++ [c,d]. % [a,b,c,c,d]

[a,b,c] -- [d,e]. % [a,b,c]
[a,b,c] -- [c,d,e]. % [a,b]

% process from right to left with [a,b,c] -- [a,b]
[a,b,c] -- [a,b] --[c]. % [c]

hd([a,b,c]). % a return the head of the list
tl([a,b,c]). % [b,c] return the rest of the list except the head 

L = [a,b,c].
L2 = [aa|L]. % [aa,a,b,c] append to the head of the list
[H|T] = L2.  % unpack the head and tail of the L2

% list within a list
[1|[2,[3,4]]]. % [1,2,[3,4]]
% single list using recursion 
[1|[2|[3,4]]]. % [1,2,3,4]
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Recursion and List Traversal:
len([H|T]) -> 1 + len(T);
len([]) -> 0.

% map each element 2 times 
double_list([H|T]) -> [2*H|double_list(T)];
double_list([]) -> [].

% find H in the list
member(H, [H|_]) -> true;
member(H, [_|T]) -> member(H, T);
member(_, []) -> false.

% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% list comp
List = [ X || X <- L, Filter ]
% the list of 1/X such that X is each element from List and 
% X is greater than 0
Y = [ 1/X || X <- List, X > 0]

% useful function for list
lists:filter(fun(E) -> E rem 2 == 0 end, List). % lists:filter(Pred,List)
lists:map(fun(E) -> E * 2 end, List). % lists:map(func,List)
lists:flatten([[1,2,3],[4,5,6],[[7,8], 9, [10]]]). % flateen the nexted list
lists:unzip([{1,a}, {2,b}, {3,c}]). % {[1,2,3],[a,b,c]}
lists:zip([1,2,3],[a,b,c]). % [{1,a},{2,b},{3,c}].

lists:member(X,L). % return true or false depend if x in L

% some useful lib
%➜ io: read, write, format, etc.
%➜ lists: append, concat, flatten, reverse, sort, member, etc.
%➜ string: len, equal, concat, substr, strip, etc.
%➜ dict: new, find, store, fetch, update, etc.
%➜ math: sin, cos, tan, exp, log, pow, sqrt, etc.


% assign each element in the list to M and times 4 to form a list
[4*M || M <- [1,2,3]]. % [4,8,12]


Hwy = [{hwy12, 45},{hwy67,55},{hwy112,65},{hwy125,75}].
% [operaation || unpack , condition1,condition2]
[{H,Speed -5} || {H,Speed} <- Hwy, Speed >= 55]. % [{hwy67,50},{hwy112,60},{hwy125,70}]
[{H,Speed -5} || {H,Speed} <- Hwy, Speed >= 55, Speed < 75].

% when processing two list , cartision product
[A-B || A <- [5,10], B <-[10,15]]. % [-5,-10,0,-5]

CityLocation = [{newyork,us},{la,us},{paris,france},{toronto,cananda},{vacouver,canada}].
%[{newyork,us},
% {la,us},
% {paris,france},
% {toronto,cananda},
% {vacouver,canada}]
UsCities = [C || {C,us} <- CityLocation]. % [newyork,la] pattern match

% tuple does not have head but list does have head

% type converstion to list
string:to_integer("23").% {23,[]}
erlang:list_to_integer("23"). % 23
erlang:list_to_float("23.23").% 23.23
erlang:integer_to_list(23).% "23"
Blist = erlang:atom_to_list(something). % "something"
hd(Blist). % 115
% ----------------------------------------------------------
% message passing
% receive never fails. The execution is suspended, possibly indefinitely,
% until a message arrives that matches one of the patterns and with a true guard sequence.

receive
    Pattern1 [when GuardSeq1] ->
        Body1;
    ...;
    PatternN [when GuardSeqN] ->
        BodyN
end


% ----------------------------------------------------------
% Exceptions

% There are three kinds of exceptions in Erlang: errors, throws and exits.
% They all have different uses (kind of):

% erlang:error(Reason)
% Calling erlang:error(Reason) will end the execution in the current 
% process and include a stack trace of the last functions called with 
% their arguments when you catch it. These are the kind of exceptions that 
% provoke the run-time errors above.

% exit
% internal exit/1 or external exit/2

% throw
% expect the programmer to handle the excpetion as control flow


% ----------------------------------------------------------
% error handling
% Try - Catch:

% A process is said to terminate normally, if the exit reason is the atom normal.
% A process with no more code to execute terminates normally.


% http://erlang.org/doc/reference_manual/expressions.html#operator-precedence
try Exprs of
    % same mananer as case of
    Pattern1 [when GuardSeq1] -> % the result of the evaluat the expression
        Body1;
    ...;
    PatternN [when GuardSeqN] ->
        BodyN
catch 
    % if the expression throw exceptions will be catched here
    % if no type is specified throw is assumed
    Class1:ExceptionPattern1[:Stacktrace] [when ExceptionGuardSeq1] ->
        ExceptionBody1;
    ...;
    ClassN:ExceptionPatternN[:Stacktrace] [when ExceptionGuardSeqN] ->
        ExceptionBodyN

% AfterBody is evaluated after either Body or ExceptionBody, 
% no matter which one. The evaluated value of AfterBody is lost;
% the return value of the try expression is the same with an after section as without.
after
    AfterBody % always gets run like final in Java
end

% e.g.start ---------------------------
sword(1) -> throw(slice);
sword(2) -> erlang:error(cut_arm);
sword(3) -> exit(cut_leg);
sword(4) -> throw(punch);
sword(5) -> exit(cross_bridge).

black_knight(Attack) when is_function(Attack, 0) ->
    try Attack() of
        _ -> "None shall pass."
    catch
        throw:slice -> "It is but a scratch.";
        error:cut_arm -> "I've had worse.";
        exit:cut_leg -> "Come on you pansy!";
        _:_ -> "Just a flesh wound." % catch all exceptin of any type
    end.

% e.g.end ---------------------------
catch_error(N) ->
    try error_func(N) of
        % if success excute error_func(N) return result
        {ok, Ret} -> io:format("SUCCES: ~w~n", [Ret])
    catch
        % if function call fail catch exception  
        throw:Err -> io:format("THROW: ~w~n", [Err]);
        exit:Err -> io:format("EXIT: ~w~n", [Err]);
        error:Err -> io:format("ERROR: ~w~n", [Err])
    after
        io:format("All Done~n")
    end.



error_func(1) -> throw(woops);
error_func(2) -> exit(woops);
error_func(3) -> erlang:error(woops);
error_func(N) -> {ok, N}.


% ----------------------------------------------------------
% link
% link , link(Pid) will link the current process to the process with the Pid
% provided , so that when the process die , it will send out the special message
% to the current process , and current process will die as well
% if a process depend on other process and error ocurrs we should better
% kill the process 

% restart the process
% System processes are basically normal processes, except they can convert
% exit signals to regular messages. This is done by calling process_flag(trap_exit, true) 
% in a running process.

% Trap Exit:
% When a process is trapping exits, it does not terminate when an exit signal is received. 
% Instead, the signal is transformed into a message {'EXIT',FromPid,Reason}, 
% which is put into the mailbox of the process, just like a regular message.
% An exception to the above is if the exit reason is kill, that is if exit(Pid,kill)
% has been called. This unconditionally terminates the process, 
% regardless of if it is trapping exit signals.


% process_flag(trap_exit, true)
% When a process is trapping exits, it does not terminate when an exit signal is received.
% Instead, the signal is transformed into a message {'EXIT',FromPid,Reason}, 
% which is put into the mailbox of the process, just like a regular message.

% An exception to the above is if the exit reason is kill, that is if exit(Pid,kill) has been called.
% This unconditionally terminates the process, regardless of if it is trapping exit signals.


trapper(N) ->
    % if received child process terminate ,exit signal will not terminate 
    % but to receive the signal as normal message , this mechanisim allows
    % process to restart the terminated process 
    process_flag(trap_exit, true), 
    Pid = spawn(fun() -> exiter(N) end),
    link(Pid),
    receive
        {’EXIT’, Pid, Why} -> io:format("~w exited with ~w~n", [Pid, Why])
    end.

exiter(1) -> exit(1);
exiter(2) -> 1/0;
exiter(N) -> true.



% ----------------------------------------------------------
% shell commands
b() - bindings. See all variable bindings.

f() - forget. Forget all variable bindings.

f(Var) - forget. Forget the binding of variable
X. This can ONLY be used as a command to
the shell - NOT in the body of a function!

e(n) - evaluate. Evaluate the n:th command
in history.

e(-1) - Evaluate the previous command.
% ----------------------------------------------------------
% ets
% ets:new/2 takes a Name and a list of options
% opltions
% ---------
% Type = set|ordered_set|bag|duplicated_bag
% Access = private|protected|public
% named_table: for the name specified to connect to the table
% {keypos,Position}: Position takes int from 1 to N specify which of the tuple element should be
%                    used as the primary key for the table,default is position 1 
ets:new(tableName,[set,named_table,])

% insert, could insernt a single tuple or list of tuples
ets:insert(Table,ObjectOrObjects). % overwrite existing duplicate key
% adding more objects with keys already existing in the table (for bag and duplicate_bag),
% false is returned if is set and duplicate key already exits
ets:new_insert(Table,ObjectOrObjects). 

ets:lookup(Table,key). % will return a list of tuples that match
% return return only the fields or list of fields specified in the Pos 
ets:lookup_element(Table, Key, Pos) -> Elem 

ets:delte(Table,key).

% e.g.
1> ets:new(ingredients,[set,named_table]).
ingredients
2> ets:insert(ingredients,{bacon,greate}).
true
3> ets:lookup(ingredients,bacon).
[{bacon,greate}]
4> ets:insert(ingredients,[{bacon,awesome},{cabbage,alright}]).
true
5> ets:lookup(ingredients,bacon). % since table as set, will overwrite the same key
[{bacon,awesome}]
6> ets:lookup(ingredients,cabbage).
[{cabbage,alright}]
7> ets:delete(ingredients,cabbage).
true
8> ets:lookup(ingredients,cabbage).
[]

% traversing a table using ordered_set
Res1 = ets:first(ingredients).
Res2 = ets:next(ingredients,Res1).
Res3 = ets:next(ingredients,Res2).
Resn = ets:last(ingredients).
Res4 = ets:prev(ingredients,ets:last(ingredients)).
Res4 = ets:prev(ingredients,ets:first(ingredients)). % '$end_of_table'
Res4 = ets:last(ingredients,ets:last(ingredients)). % '$end_of_table'
% ----------------------------------------------------------
% match
% find record that first filed is atom items, first field and last field
% should be the same, third filed does not care
% match will return all the normal variable in order
% $2 can be the same as $1
% match_object/2 would return the whole obeject
ets:match(table,{items,'$1','$2','_','$1'}).% [[a,b],[b,c]]
ets:match_object(table,{items,'$1','$2','_','$1'}).% [{},{}]

% delete all items in the table
delete_all_objects(Tab) -> true
% ----------------------------------------------------------
% ordict
D0 = orddict:new(). % create a new ordered dict

% update(Key, Fun, Initial, Orddict1) -> Orddict2
update(Key, fun (Old) -> Old ++ [Val] end, [Val], D).

% increment the value associated with the key by the Increment
% if the key does not exits ,key will be created with init value of Increment
update_counter(Key, Increment, Orddict1) -> Orddict2

% Stores a Key-Value pair in a dictionary. 
% If the Key already exists in Orddict1, the associated value is replaced by Value.
store(Key, Value, Orddict1) -> Orddict2

% Appends a new Value to the current list of values associated with Key.
% An exception is generated if the initial value associated with Key is not a list of values.
append(Key, Value, Orddict1) -> Orddict2

% Returns the value associated with Key in dictionary Orddict. 
% This function assumes that the Key is present in the dictionary.
% An exception is generated if Key is not in the dictionary.
fetch(Key, Orddict) -> Value

%Types
%List = [{Key, Value}]
%Orddict = orddict(Key, Value)
from_list(List) -> Orddict

find(Key, Orddict) -> {ok, Value} | error.
% ----------------------------------------------------------
% set
L = ordsets:new().

ordsets:add_element(Element, Ordset1) -> Ordset2.

% if the list is empty will still return empty list
ordsets:del_element(_element(Element, Ordset1) -> Ordset2.

ordsers:is_element(Element, Ordset) -> boolean()

% ----------------------------------------------------------
% list
delete(Elem, List1) -> List2. %if the element not in the list will return the original list


