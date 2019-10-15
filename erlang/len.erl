-module(len).
-export([len/1]).

len([H|T]) ->
    1 + len(H|T);
len([]) ->
    0.

