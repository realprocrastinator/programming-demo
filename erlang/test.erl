-module(test).
-export([start/0, say_something/2,entry/0]).

say_something(What, 0) ->
    done;
say_something(What, Times) ->
    io:format("~p~n", [What]),
    say_something(What, Times - 1).


start() ->
    io:format("Inside function~n"),
    receive
        {From,hey} ->
            Pid1 = spawn(main, say_something, [hello, 3]),
            From !{self(),Pid1},
            io:format("sent newly create process id ~w~n",[Pid1]),
            start();
        {stop} ->
            true
    end.
    

entry() ->
    Pid = spawn(test,start,[]),
    %Pid = spawn(start),
    io:format("get start pid ~w~n",[Pid]),
    Pid ! {self(),hey},

    receive
        {From,Pid2} ->
            io:format("Received newly create process id ~w~n",[Pid2])
    end,
    Pid ! {stop}.
    %Pid ! {self(),hey}.

