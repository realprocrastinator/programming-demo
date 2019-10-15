
% Definitions
Link A bi-directional propagation path for exit signals.
Exit Signal - Transmit process termination information.
Error trapping - The ability of a process to process exit signals as if they were messages.

When a process crashes (e.g. failure of a BIF or a pattern match) 
Exit Signals are sent to all processes to which the failing process is currently linked.

% rules for proprogating errors
The rule for propagating errors is: If the process which receives an exit signal, 
caused by an error, is not trapping exits then the process dies
and sends exit signals to all its linked processes.


% trap exit signals
% P1 -> P2(trap exit) -> P3
% if P1 exit from an error and signal P2, P2 can trap the error and not
% proprogate the error to P3

receive
    {'EXIT', P1, Why} ->
	... exit signals ...
    {P3, Msg} ->
	... normal messages ...
end

% exit signal proprogation semantic
-When a process terminates it sends an exit signal, either normal or non-normal,
to the processes in its link set.

-A process which is not trapping exit signals (a normal process) dies 
if it receives a non-normal exit signal. When it dies it sends 
a non-normal exit signal to the processes in its link set.

-A process which is trapping exit signals converts all incoming exit signals 
to conventional messages which it can receive in a receive statement.

-Errors in BIFs or pattern matching errors send automatic exit signals 
to the link set of the process where the error occured.


% Primitives For Exit Signal Handling
link(Pid) 
- Set a bi-directional link between the current process and the process Pid

process_flag(trap_exit, true) 
- Set the current process to convert exit signals to exit messages,
these messages can then be received in a normal receive statement.

exit(Reason) 
- Terminates the process and generates an exit signal where the process 
termination information is Reason.


% Robust server +++++++++++++++++++++++++++++++++++++
% client sent request to allocate and free resources for a given process
% client could died before sending out the free request to release the resources
% therefore this method is not robust

% Free is a list of unreserved resources.
% Allocated is a list of pairs {Resource, Pid}
top(Free, Allocated) -> % take an current state of what is free and what has been allocated
    receive
        {Pid, alloc} -> % receive request to allocate resources for a given process
            top_alloc(Free, Allocated, Pid);
        {Pid ,{release, Resource}} ->
            Allocated1 = delete({Resource,Pid},Allocated),
        	    top([Resource|Free], Allocated1)
    end.

% of no free resources avialble reply no to process
top_alloc([], Allocated, Pid) ->
    Pid ! no, 
    top([], Allocated);

% if there is resources avialble reply with the resources
% and adjust the current state of free resources and allocated
top_alloc([Resource|Free], Allocated, Pid) ->
    Pid ! {yes, Resource}, 
    top(Free, [{Resource,Pid}|Allocated]).

% Robust server end+++++++++++++++++++++++++++++++++++++

% when the client get allocated a resources but crashed before it is able to release the
% resources , the server will release the resources for this client by linking its process
% so that when the client crash the server can get is exit message and release the resources
% Robust server Error recover+++++++++++++++++++++++++++++++++++++
top_recover_alloc([], Allocated, Pid) ->
    Pid ! no,
    top_recover([], Allocated);

top_recover_alloc([Resource|Free], Allocated, Pid) ->
    %% No need to unlink.
    Pid ! {yes, Resource},
    link(Pid), % link the client to the server to get its exit message
    top_recover(Free, [{Resource,Pid}|Allocated]).

top_recover(Free, Allocated) ->
    receive
	{Pid , alloc} ->
	    top_recover_alloc(Free, Allocated, Pid);
	{Pid, {release, Resource}} ->
	    unlink(Pid), % when client release the resources unlink client process
 	    Allocated1 = delete({Resource, Pid}, Allocated),
	    top_recover([Resource|Free], Allocated1);
	{'EXIT', Pid, Reason} -> % when client process crash before release resources
	    %% No need to unlink.
	    Resource = lookup(Pid, Allocated), % find resources that this client hold
	    Allocated1 = delete({Resource, Pid}, Allocated), % deallocate resources of this lcient
	    top_recover([Resource|Free], Allocated1)
    end.

% utility functions
delete(H, [H|T]) ->
    T;
delete(X, [H|T]) ->
    [H|delete(X, T)].

lookup(Pid, [{Resource,Pid}|_]) ->
    Resource;
lookup(Pid, [_|Allocated]) ->
    lookup(Pid, Allocated).

% Robust server Error recover end+++++++++++++++++++++++++++++++++++++


