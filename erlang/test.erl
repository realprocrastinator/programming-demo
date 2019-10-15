-module(test).
-export([main/0]).

main() ->
    L = [1,2,3],
    lists:nth(1,L).
