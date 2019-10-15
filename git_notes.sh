

git clone <url>

HEAD~                            #the parent of the current head

#The reset command overwrites these three trees in a specific order, stopping when you tell it to:
#Move the branch HEAD points to (stop here if --soft)
#Make the Index look like HEAD (stop here unless --hard)
#Make the Working Directory look like the Index

#only the repo points to the commit and now can do some amend to that repo
git reset --soft                 #wills top at where the head and the branch points to the commit and stop
#You rolled back to before you ran all your git add and git commit commands
gti reset --mix                  #will stop at where the head and branch points to the commit and index updated
#cwd will cahnge as well , so cwd , index, repo will all roll back to that commit
#could destroy file in the cwd , since it force overwrite files in the cwd
git reset --hard <commit hash>   #will restore back to any previous commit
git reset --hard origin/master   #will restore the parent commit of the curr commit
git checkout -b                  #will create the branck and checkout to that branch
git push <URL> branch            #will push the current commit to the repo address

git ls-files                    #what index looks like
git reflog                      #show the head update log
