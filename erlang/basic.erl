


% control flow if
fine() ->
    if  % if any of the following case would be true 
        1=:=1 ->
            works;
        1 =:= 2; 1 =:= 1 ->
            works;
        true ->  % else the rest case
            always_run
    end.

compare(X, Y) ->
    Result = if
        X > Y -> greater;
        X == Y -> equal;
        X < Y -> less
    end,
    io:format("~p is ~p than ~p ~n", [X, Result, Y]).

% case of
beach(Temperature) ->
    case Temperature of
        {cel,N} when N >= 20 , N <= 45 ->
            'favarable';
        {kelvin,N} when N >=293, N <=318 ->
            'not bad';
        _ ->
            'avoid beach'
    end.


