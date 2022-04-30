#!minishell
# simple command & global + arguments & history
/bin/ls
/bin/pwd
/bin/invalidcommand
/
//
/bin
/bin/

     
		     

/crash
# echo
echo "hello, world!"
echo "print1" "print2"
echo "print1""nospace"
echo -n "dash-n"
echo ""
echo
echo "\n"
echo "1""2" "3"
echo 'single quotes'
echo '2x' 'single quotes ' "+ double!"
echo "'single in double'"
echo '"double in single"'
echo "'\"double in single in double\"'"
echo "this \"is\" text"
echo no_quotes space"nospace but quotes"
# !!!!! exit
# return value of a process
/bin/ls
echo $?
/bin/invalidcommand
echo $?
echo $?
bin/pwd
echo $?$?
echo $? $? $?
# !!!!! signals
# double & single quotes
echo "cat lol.c | cat > lol.c"
cat nothing
cat "nothing"
echo 'cat lol.c | cat > lol.c'
echo ''
echo '$USER'
echo "$USER"
echo "$$USER"
echo "$$$USER"
echo '$USER'
echo '$$USER'
echo '$$$USER'
echo '$USER\\\--'
echo "$USER\\\--"
# env
env
env 1
env _
env stop
env $PATH
env PATH
env '?'
env "!?"
# export
export test
export test2=withvalue
export test3="value+double quotes"
export test4='value+single quotes'
export test5novalue
export test6==equalequal
export test7=123456
export test8=1234"5678"
export test9="double"'single'
export test10='single"double inside"'"double outside"
export RNG="PLUS VALUE"
export _UNDERSCORE
export FAIL#=somevalue
export @nothing
export
export test="new value"
export test2=evenmorevalue
export test3='new single'
export test4
# !!!!! change existing env vars
# !!! the order of env will be different
export
# unset
unset test2
unset test4
unset test6
export
unset invalidvar
unset "thisdoesnotexist"
unset 'doesnotexist'
# !!!!! unset something system
export
# cd
cd
cd $HOME
ls
cd /usr/local
ls
cd 
cd thisdoesnotexist
cd ./././././././.
ls
cd ././././././././
ls
cd
ls
mkdir test_dir
cd test_dir/../test_dir/..
ls
cd $HOME/test_dir
ls
cd ./..
ls
cd
# pwd
pwd
cd test_dir
pwd
pwd extra_input
pwd        
     pwd     
rmdir test_dir
# relative path !!!!!
cd
cd minishell/git/
ls src/builtins/../builtins/../../libft/./../src/
# environment path
ls -a
# !!!!! unset $PATH & check order of checks
# redirection + pipes
cd
cd minishell/git
cat minishell.c | grep "main"
cat minishell.c | grep "main" > test1.txt
cat test1.txt
< test1.txt grep "main"
< test1.txt | grep "main"
< test1.txt wc -l > out1 > out2 >> append3 > out4
< test1.txt wc -l > out1 > out2 >> append3 > out4
cat out4
echo "file content" > test2.txt
wc -c < test1.txt < test2.txt
cat minishell.c | grep "main" > test1.txt | wc -l < test1.txt > tmp > test3.txt
cat test1.txt
echo "additional content" >> test3.txt
cat test3.txt
cat minishell.c|grep "main"
cat minishell.c|grep "main">test2.txt
cat test2.txt
cat minishell.c | thisdoesnotexist | echo "huhu"
thisdoesnotexist | echo "hello!?"
# !!!!! here_doc
# environment vairbales
echo $USER
echo $PATH
echo $$
echo $USER$USER
echo $USER $USER
echo       $USER        $USER       
cd $HOME/minishell/git
rm append3
rm out1
rm out2
rm out4
rm test1.txt
rm test2.txt
rm test3.txt
rm tmp
