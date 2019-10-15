
% c(address).
% Pid = spawn(address,server,[[{erik,10},{david,11}]]).

-module(client).
-export([run/2]).
-export([request/2]).


request(Request,Pid) ->
    case Request of
        {insert,{Name,Address}} ->
            Pid ! {self(),insert,{Name,Address}};
        {delete,Name} ->
            Pid ! {self(),delete,Name};
        {look,Name} -> 
            Pid ! {self(),look,Name};
        print ->
            Pid ! print;
        stop ->
            Pid ! stop;
        _Else ->
            io:fwrite("Request not valid!\n")
    end,
    % sleep for 5 ms and make the same request again
    sleep(5),
    request(Request,Pid).

% run Num of process client at the same time
run(Pid,Num) when Num == 0->
    true;
run(Pid,Num) when Num > 0->
    _ = spawn(client,request,[print,Pid]),
    %io:fwrite("start client process\n"),
    run(Pid,Num-1).

sleep(T) ->
    receive
    after
        T -> true
    end.


