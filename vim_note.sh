#==========================================================================================
#configuration
#vim config for ubuntu
https://coderoncode.com/tools/2017/04/16/vim-the-perfect-ide.html

#download the color scheme find it from .vim the bundle where all the colors are
#copy the color folder under .vim a
#in .vimrc 
set colorsheme = yourcolor

#vim syntax check 
#set the hight of the windo same as error msg height 
function! SyntasticCheckHook(errors)
    if !empty(a:errors)
        let g:syntastic_loc_list_height = min([len(a:errors), 10])
    endif
endfunction

#key mapping
<C-r>=, or Ctrl+R= is used to insert the result of an expression at the cursor.
<C-r>, without =, allows you to insert the content of any register at the cursor while staying in insert mode:


#==========================================================================================
#functionanlity
#---------------------------------------------------------------
#Tagbar
#Generate ctag goes to your dir and run
ctags -R ./

:TagbarOpen #to ope tagbar
:TagbarClose
:TagbarOpen f #to set focus on the tagbar
:TagbarToggle #to toggle close and open the tagbar


#goes to the root dir of the project generate c tags recursivley
#http://zalas.eu/jumping-to-a-class-function-and-variable-definitions-in-vim-with-exuberant-ctags/
#https://medium.freecodecamp.org/make-your-vim-smarter-using-ctrlp-and-ctags-846fc12178a4
ctags -R --languages=php .
ctrl-] #takes you to the declaration of a keyword your cursor is currently over. Jump is made so it doesn't matter in which file it is defined. Keyword is put on the tag stack.
ctrl-t# takes you a step back in the tag stack.
2ctrl-] #take you to the first one
4ctrl-t #travel back up several times
vim -t fucntion_name 

#map the CtrlPtag for \.
nnoremap <leader>. :CtrlPTag<cr>
#select the ctage that you wish to open
ctrl + v #open in vertical split window
ctrl + x #open horizontal in split window
ctrl + t #open in  a new tag
#ctrl +r switch to regex mode
ctrl + r 
#switch between mode
ctrl + b /f
ctrl + d #swich to file name search


:ts or :tselect shows the list
:tn or :tnext goes to the next tag in that list
:tp or :tprev goes to the previous tag in that list
:tf or :tfirst goes to the first tag of the list
:tl or :tlast goes to the last tag of the list
:tags #show tags that you have traversed



#---------------------------------------------------------------
#tabs
#https://medium.freecodecamp.org/learn-linux-vim-basic-features-19134461ab85
tabedit file1   #will open file in a new tan within the same window
tabedit file2 

gt #switch to then ext tab
gT #swtch to the previous tab
2gt #switch the specific tab
tabs #check all the tabs

#---------------------------------------------------------------
#substitiutions
https://www.linux.com/learn/vim-tips-basics-search-and-replace
:%s/search/replace/gc #c will check each replace one by one
:8,10 s/search/replace/gc #will search replace 8 and 10 only

#---------------------------------------------------------------
#go to statement
gd #will take you to the local declaration.
gD #will take you to the global declaration.
g* #search for the word under the cursor (like *, but g* on 'rain' will find words like 'rainbow').
g #same as g* but in backward direction.
gg #goes to the first line in the buffer (or provide a count before the command for a specific line).
G #goes to the last line (or provide a count before the command for a specific line).
[i #display the definition of a variable
[d #display the definition of a macro
[I #display alll lines that contains the variable


#---------------------------------------------------------------
#map short cut for the toggle of the Tagbar
#Mapping space for Tagbar open and close
nmap <silent> <Space> :TagbarOpenAutoClose <CR> #space for opening the tagbar


#Neardtree command
#in the Neardtree bar and then press s.t. you can manipulate file without leaving vim
m

#open files in a new tab, select file in the near bar and then press
t
#to switch betwen tags 
gt


# Mapping n for neard tree
map <silent> <C-n> :NERDTreeToggle <CR>  #control n to toggle neard tree

#==========================================================================================

#==========================================================================================
