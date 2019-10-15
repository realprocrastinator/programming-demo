% functional programming
https://www.youtube.com/watch?v=wJq86IXkFdQ

% counter
https://medium.com/@voluntas/erlang-otp-22-counters-モジュール-666981497f07
http://erlang.org/doc/man/counters.html#new-2

% Ref = counters_ref()
% new(Size, Opts) -> counters_ref()
% Size = integer() >= 1
% Opts = [Opt]
% Opt = atomics | write_concurrency
Ref = counters: new(10,[atomics]). % {atomics,#Ref<0.863907172.3089760260.166490>}
counters:get(Ref,1). % 0  return the first counter in the array
counters:put(Ref,1,2).% put 2 at counter 1 
counters:add(Ref,1,2).% increase the first counter by 2
counters:sub(Ref,1,2).% subtract the first counter by 2


% Anonymous Function
fun(Arg1) -> 
        Expression1, ...;
   (Arg2) ->
        Expression2,...,Expression3
end.

% lists module
% examples
% http://erlang.org/doc/programming_examples/funs.html
% list doc
% http://erlang.org/doc/man/lists.html
%
lists:seq(1,10). % [1,2,3,4,5,6,7,8,9,10]
lists:reverse(L). 
lists:nth(3,L). % acess the 3rd element of the list
ists:nthtail(4,[1,2,3,4,5,6,7,8,9,10]). % [5,6,7,8,9,10]

lists:append([[1, 2, 3], [a, b], [4, 5, 6]]). % [1,2,3,a,b,4,5,6] 
lists:append([1,2,3], [99]). % [1,2,3,99]
lists:concat([doc, '/', file, '.', 3]). % "doc/file.3"
lists:join(x, [a,b,c]). % [a,x,b,x,c]

% return a copy of the list where first matching elemnt
% is deleted if there is 
lists:delete(Element,L). 

% drop the element while the predicate Evaluate as true
lists:dropwhile(fun(X) -> X > 3 end,[200,500,45,5,3,45,6]). % [3,45,6]
lists:takewhile(fun(X) -> X > 3 end,[200,500,45,5,3,45,6]). % [200,500,45,5]
% plits the list L into the two sublists {L1, L2}, 
% where L = takewhile(P, L) and L2 = dropwhile(P, L):
% {[200,500,45,5],[3,45,6]}
lists:splitwith(fun(X) -> X > 3 end, [200,500,45,5,3,45,6]).
% partition the list into two parts first part with predicate evaluate to true
% second part to false
lists:partition(fun(A) -> A rem 2 == 1 end, [1,2,3,4,5,6,7]). % {[1,3,5,7],[2,4,6]}

lists:filter(fun(X) -> X rem 2 == 0 end,lists:seq(1,10)). % [2,4,6,8,10]
lists:map(fun(X) -> X * 2 end,lists:seq(1,10)). % [2,4,6,8,10,12,14,16,18,20]
lists:foldl(fun(X, Sum) -> length(X) + Sum end, 0, ["I","like","Erlang"]). % 11
lists:foldr(...) % like foldl but traversing list in reverse order


lists:flatmap(fun(X)->[X,X] end, [a,b,c]). % [a,a,b,b,c,c]
lists:flatten([1,2,3,[4,5,[6,7]]]). % [1,2,3,4,5,6,7]
lists:flatten([1,2,3,[4,5,[6,7]]],[99,100]). % [1,2,3,4,5,6,7,99,100]
flatlength(DeepList) -> integer() >= 0 % same as length(flatten(DeepList))

% mapfoldl will perform map and fold at the same time , take predicate that takes
% two argument one for map and one for fold , and return the independent result
% from map and fold into a tuple
Upper =  fun(X) when $a =< X,  X =< $z -> X + $A - $a;(X) ->X end.
lists:mapfoldl(fun(Word, Sum) -> {Upper(Word), Sum + length(Word)} end, 0, ["I","LIKE","ERLANG"]).
% {["I","LIKE","ERLANG"],11}

% do operation on each element of the list
% function returns okay ,so only use its side effects
lists:foreach(fun(H) -> io:format("~p~n",[H]) end, L).
lists:foreach(fun(Pid) -> Pid ! M end, L)

lists:any(fun(X) -> X > 3 end, [1,2,3,12,5]). % true
lists:all(fun(X) -> X rem 2 == 0 end,[2,4,6,8]). % true

% keymap will apply function map the the sepcified nth element in each tuple
% and return a copy of the newly mapped list
Fun = fun(Atom) -> atom_to_list(Atom) end.
lists:keymap(Fun, 2, [{name,jane,22},{name,lizzie,20},{name,lydia,15}]).
% [{name,"jane",22},{name,"lizzie",20},{name,"lydia",15}]
% if the element of the specified index of each tuple in the list match the key return true
lists:keymember("jane",2,[{name,"jane",22},{name,"lizzie",20},{name,"lydia",15}]). % true
% search if the specified key of the index within each tuple exists
% if exits return the tuple ,else return false
lists:keysearch("jane",2,[{name,"jane",22},{name,"lizzie",20},{name,"lydia",15}]). 
% {value,{name,"jane",22}} 
