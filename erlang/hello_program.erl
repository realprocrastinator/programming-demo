-module(hello_program).
-export([hello/0]).

hello() ->
    receive % message sent to the program e.g. Pid ! john 
        {FromPID, Who} ->
            case Who of % if else as case
                john -> FromPID!"Hello John.";
                andrew -> FromPID!"Hello Andrew.";
                daniel -> FromPID!"Hello Daniel.";
                _ -> FromPID!"Unknown selection."
        end, % of case 
    hello() % recursion instead of loop
end. % end of hello()



%1> Pid = spawn(fun hello_program:hello/0).
%<0.80.0>
%2> Pid ! john.
%john
%3> Pid ! {self(),john}.
%{<0.78.0>,john}
%4> Pid ! {self(),john},
%4> receive
%4> Response -> Response
%4> end.
%"Hello John."
