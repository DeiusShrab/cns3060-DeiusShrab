Project 2 - cat

==========

Jacob Christensen

The way I did the line number option is you need to specify it for each file e.g. 'cat1 -n file1 -n file2'. If you don't give the option for a file it's not numbered, and if you finish with the option e.g. 'cat1 -n file1 file2 -n' then it processes all the arguments, then begins numbering stdin
It also places a newline between each input for readability
