
% if in process1 we do
Pid2 = spawn(Mod, Func, Args)
% Pid2 is only known to process1

% self() - returns the Process Identity (Pid) of the process executing this function.
% From and Msg become bound when the message is received. Messages can carry data.

% process A send message to Process B
B ! {self(),{digits,[1,2,6]}}.
% B receive message from A
receive % message can be selectively unpacked
    {A,{digits,D}}-> % Var A and D become bound when received the message
        analyse(D);
end.

% echo example+++++++++++++++++
-module(echo).
-export([go/0, loop/0]).

go() ->
	Pid2 = spawn(echo, loop, []),
	Pid2 ! {self(), hello},
	receive
		{Pid2, Msg} ->
			io:format("P1 ~w~n",[Msg])
	end,
	Pid2 ! stop.

loop() ->
	receive
		{From, Msg} ->
			From ! {self(), Msg},
			loop();
		stop ->
			true
	end.
% echo example end+++++++++++++++++

% selective messge passing +++++++++++++++++
get_msg() ->
    receive 
        foo -> % block until receive foo
            io:fwrite("Get Foo\n") 
    end, 
    receive % after receiving foo block until receive bar
       bar -> 
            io:fwrite("Get bar\n") 
    end.
% selective messge passing end+++++++++++++++++



% Register process
% register(Alias, Pid) Registers the process Pid with the name Alias.

% server client
-module(myserver).

server(Data) ->
	receive
		{From,{request,X}} ->
			{R, Data1} = fn(X, Data),
			From ! {myserver,{reply, R}},
			server(Data1)
	end.

-export([request/1]).

request(Req) ->
	myserver ! {self(),{request,Req}},
	receive
		{myserver,{reply,Rep}} ->
			Rep
	end.


% time out
% if recieve foo within Time ms do action1
% else do action2
receive 
    foo -> 
        Action1;
after
    Time -> 
        Action2
end.

% sleep would suspend the process for T ms
sleep(T) ->
	receive
	after
		T ->
			true
	end.

% suspend the process indefinitely
suspend() ->
	receive
	after
		infinity ->
			true
	end.

% alarm
% set What to itself after T ms
set_alarm(T, What) ->
	spawn(timer, set, [self(),T,What]).

% send given message to the given process
% after T times 
set(Pid, T, Alarm) ->
	receive
	after
		T ->
			Pid ! Alarm
	end.

% receive the alarm that being set
receive
	Msg ->
		... ;
end

% flush the message buffer
flush() ->
	receive
		Any -> % receive message will be flushed out of the message queuqe
			flush()
	after
		0 -> % 0 indciates message buffer empty
			true
	end.


