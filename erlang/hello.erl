-module(hello). % modeual name same as file name
    -export([hello_word/0]). % [func_name/num_params]
    % not like the inline function there is end
    hello_word() -> io:fwrite("hello word\n"). % function of the module

    



