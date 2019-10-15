

% scope of variables
% Variables in a clause exist between the point where the variable is 
% first bound and the last textual reference to the variable.
1...	f(X) -> % X first bound
2...		Y = g(X),
3...		h(Y, X),
4...		p(Y), % X resources can be reclaimed from here
5...		f(12).


% if/receive/case scope
f(X) ->
    case g(X) of
	    true -> A = h(X), B = 7; % A B becomes defined if branch true is evaluated
	    false -> B = 6 % only B is defined
    end,
    ...,
    h(A),% A is not defined if false branch is evaluated


% catch and throw
-module(try).
-export([foo/1]).

foo(1) -> hello;
foo(2) -> throw({myerror, abc});
foo(3) -> tuple_to_list(a);
foo(4) -> exit({myExit, 222}).

% catch try:foo(1) evaluates to hello.
% catch try:foo(2) evaluates to {myError,abc}.
% catch try:foo(3) evaluates to {`EXIT',badarg}.
% catch try:foo(4) evaluates to {`EXIT',{myExit,222}}.
% catch try:foo(5) evaluates to {`EXIT',function_clause}.


% using catch and throw 
f(X) ->
    case catch func(X) of
	{'EXIT', Why} ->
            ... error in BIF ....
            ........ BUG............
	{exception1, Args} ->
            ... planned exception ....
	Normal ->
            .... normal case ....
    end.

func(X) ->
    ...
func(X) ->
   bar(X),
   ...
...
bar(X) ->
   throw({exception1, ...}).



% reference
% Ref = make_ref(),
% They can be compared for equality.
% the system guarantees that no two references created by different calls to make_ref will ever match
% The guarantee is not 100% - but differs from 100% by an insignificantly small amount :-).

ask(Server, Question) ->
    Ref = make_ref(), % create unique reference ID for the client
    Server ! {self(), Ref, Question},
    receive
        {Ref, Answer} ->
	    Answer
    end.

server(Data) ->
    receive
	{From, Ref, Question} ->
            Reply = func(Question, Data),
            From ! {Ref, Reply},
            server(Data);
	...
    end.

% space optimisation
% Note that we canot Evaluate '+' until both its arguments are known.
% This formulation of sum(X) evaluates in space O(length(X)).
sum([H|T]) ->
    H + sum(T);
sum([]) ->
    0.

% The second is a tail recursive which makes use of an accumulator Acc:
% use constance space
sum(X) ->
    sum(X, 0).

sum([H|T], Acc) ->
   sum(T, H + Acc);
sum([], Acc) ->
    Acc.

% Each process has a local store called the "Process Dictionary". 
% The following BIFs are used to manipulate the process dictionary:
get() % returns the entire process dictionary.
get(Key) % returns the item associated with Key (Key is any Erlang data structure), or, returns the special atom undefined if no value is associated with Key.
put(Key, Value) % associate Value with Key. Returns the old value associated with Key, or, undefined if no such association exists.
erase() % erases the entire process dictionary. Returns the entire process diction before it was erased.
erase(Key) % erases the value associated with Key. Returns the old value associated with Key, or, undefined if no such association exists.
get_keys(Value) % returns a list of all keys whose associated value is Value.








