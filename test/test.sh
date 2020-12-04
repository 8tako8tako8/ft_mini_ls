#!bin/bash
ls -1tr > x.txt
mv x.txt ..
./ft_mini_ls > x.txt
mv x.txt y.txt
mv y.txt ..
cd ..
diff x.txt y.txt
rm x.txt y.txt
