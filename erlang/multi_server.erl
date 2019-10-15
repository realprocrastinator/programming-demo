% book excercise https://www.oreilly.com/library/view/erlang-programming/9780596803940/ch04.html0i


-module(multi_server).
-export([server/2]).
-export([run/2]).
-export([start/2]).
-export([init/1]).


%-----------------------------------------------------------------------
% init the linked ring and star all servers
init(Num) ->
    Ring = run([],Num),
    io:fwrite("here start pocess\n"),
    link_ring(Ring),
    link_last(Ring), % link last with the first
    io:fwrite("linked ring complete\n"),

    Ref = counters:new(1,[atomics]), % creae a counter
    % counters:add(Ref,1,1), % add 1 to the counter

    start(Ring,Ref).


%-----------------------------------------------------------------------
% start server with Num of server process
start(Ring,Ref) -> 
    receive
        {insert,{Name,Address}} ->
            % get the counter the Pid of the server
            lists:nth((counters:get(Ref,1) + 1) rem 3,Ring) ! {self(),insert,{Name,Address}},
            start(Ring,Ref);
        {delete,Name} -> 
            lists:nth(countes:get(Ref,1) rem 3,Ring) ! {self(),delete,Name,0},
            start(Ring,Ref);
        {look,Name} -> 
            lists:nth(counters:get(Ref,1) rem 3,Ring) ! {self(),look,Name,0},
            start(Ring,Ref);
        print ->
            io:fwrite("Received print\n"),
            print_all(Ring),
            start(Ring,Ref);
        stop -> 
            stop_all(Ring)
    end.
%-----------------------------------------------------------------------
% Data is a list of {name,address}
server(Data,Next) ->
    Counter = 3, % length of the loop ring for full search
    receive
        {From,insert,{Name,Address}} ->
            From ! ok,
            server([{Name,Address}|Data],Next); % update database and keep running
        {From,delete, Name,Count} -> 
            Address = look_up(Name,Data),
            if 
                Count == Counter -> % did a full search already
                    false,
                    server(Data,Next);
                Address == false ->
                    % if not found in this server need to goes to next
                    Next ! {self(),delete,Name,Count + 1};
                true->
                    %io:fwrite("delete address is :~p\n",[Name,Address]),
                    From ! ok, % reply to client successful deletion
                    server(delete_add(Name,Data),Next) % update the current state of the data
            end;
        {From,look,Name,Count} -> 
            Address = look_up(Name,Data),
            if 
                Count == Counter -> % did a full search already
                    false,
                    server(Data,Next);
                Address == false ->
                    % if not found in this server need to goes to next
                    Next ! {self(),look,Name,Count + 1};
                true->
                    io:fwrite("~p address is :~p\n",[Name,Address]),
                    From ! Address,
                    server(Data,Next)
            end;
        {_,next,Next} -> % update the next server to this one
            server(Data,Next);
        print ->
            print_add(Data),
            server(Data,Next);
        stop ->
            true
    end.
%-----------------------------------------------------------------------
% util functions
% print all data base address in Ring
print_all([]) ->
    io:fwrite("\n");
print_all([H|_]) ->
    H ! print.

% stop all data base address in Ring
stop_all([]) ->
    io:fwrite("All server stopped \n");
stop_all([H|_]) ->
    H ! stop.

% ring is a list of server process id 
run(Ring,Num) when Num ==  0->
    Ring;
run(Ring,Num) when Num > 0->
    Node = spawn(multi_server,server,[[{erik,1},{david,2}],1]),
    run([Node|Ring],Num-1).

% link all server process as a ring
link_ring(L) when length(L) == 1 ->
   true; 
link_ring([H|T]) when length(T) > 0 ->
    [H2|T2] = T,
    H ! {self(),next,H2},
    link_ring(T).

% link last to the first
link_last(L) ->
    lists:nth(length(L),L) ! {self(),next,lists:nth(1,L)}.

% delete the tuple associated name in the Data 
delete_add(Name,[{Name,_}|T]) ->
    T;
delete_add(Name,[H|T]) ->
    [H|delete_add(Name,T)].

% give a name look up address associated with the name
% return the address if exists else return false
look_up(Name,[{Name,Address}|_]) -> 
    Address;
look_up(_,[]) -> 
    false;
look_up(Name,[_|T]) ->
    look_up(Name,T).

% print all data base addresses
print_add([]) ->
    io:fwrite("\n");
print_add([{Name,Address}|T]) ->
    io:fwrite("~p:~p\n",[Name,Address]),
    print_add(T).





