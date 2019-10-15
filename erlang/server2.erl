-module(address).
-export([add_address/1]).


Pid = spawn(address,server,[]).

% client API 
add_address({Name,Address}) ->
    Pid ! {self(), insert,{Name,Address}}.



% Data is a list of {name,address}
server(Data) ->
    receive
        {From,insert,{Name,Address}} ->
            From ! ok,
            server([{Name,Address}|Data]); % update database and keep running
        {From,delete, Name} -> 
            From ! ok, % reply to client successful deletion
            server(delete_add(Name,Data)); % update the current state of the data
        {From,look,Name} -> 
            Address = look_up(Name,Data),
            io:fwrite("~p address is :~p\n",[Name,Address]),
            From ! Address,
            server(Data);
        print ->
            print_add(Data),
            server(Data);
        stop ->
            true
    end.

% util functions
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







