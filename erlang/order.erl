-module(order).
-export([get_msg/0]).

get_msg() ->
    receive
        foo ->
            io:fwrite("Get Foo\n") 
    end,
    receive
       bar -> 
            io:fwrite("Get bar\n") 
    end.

