#!/bin/bash

bin/Programme &> ./test/res_test/test01.txt
result=$(diff ./test/res_test/test01.txt ./test/files_test/test01.txt)

if [ $? -eq 0 ]
then
        echo "Test 1  OK"
else
        echo "Test 1 NOK"
        
fi

bin/Programme --same-language &> ./test/res_test/test02.txt
result=$(diff ./test/res_test/test02.txt ./test/files_test/test02.txt)

if [ $? -eq 0 ]
then
        echo "Test 2  OK"
else
        echo "Test 2 NOK"
        
fi

bin/Programme --same-language can &> ./test/res_test/test03.txt
result=$(diff ./test/res_test/test03.txt ./test/files_test/test03.txt)

if [ $? -eq 0 ]
then
        echo "Test 3 OK"
else
        echo "Test 3 NOK"
        
fi

bin/Programme --same-language can 123 &> ./test/res_test/test04.txt
result=$(diff ./test/res_test/test04.txt ./test/files_test/test04.txt)

if [ $? -eq 0 ]
then
        echo "Test 4  OK"
else
        echo "Test 4 NOK"
        
fi

bin/Programme --country can &> ./test/res_test/test05.txt
result=$(diff ./test/res_test/test05.txt ./test/files_test/test05.txt)

if [ $? -eq 0 ]
then
        echo "Test 5  OK"
else
        echo "Test 5 NOK"
        
fi

bin/Programme --country 123 &> ./test/res_test/test06.txt
result=$(diff ./test/res_test/test06.txt ./test/files_test/test06.txt)

if [ $? -eq 0 ]
then
        echo "Test 6  OK"
else
        echo "Test 6 NOK"
        
fi

bin/Programme --country &> ./test/res_test/test07.txt
result=$(diff ./test/res_test/test07.txt ./test/files_test/test07.txt)

if [ $? -eq 0 ]
then
        echo "Test 7  OK"
else
        echo "Test 7 NOK"
        
fi

bin/Programme --region &> ./test/res_test/test08.txt
result=$(diff ./test/res_test/test08.txt ./test/files_test/test08.txt)

if [ $? -eq 0 ]
then
        echo "Test 8  OK"
else
        echo "Test 8 NOK"
        
fi

bin/Programme --region 123213 &> ./test/res_test/test09.txt
result=$(diff ./test/res_test/test09.txt ./test/files_test/test09.txt)

if [ $? -eq 0 ]
then
        echo "Test 9  OK"
else
        echo "Test 9 NOK"
        
fi

bin/Programme --region America &> ./test/res_test/test10.txt
result=$(diff ./test/res_test/test10.txt ./test/files_test/test10.txt)

if [ $? -eq 0 ]
then
        echo "Test 10  OK"
else
        echo "Test 10 NOK"
        
fi

bin/Programme --region Africas &> ./test/res_test/test11.txt
result=$(diff ./test/res_test/test11.txt ./test/files_test/test11.txt)

if [ $? -eq 0 ]
then
        echo "Test 11  OK"
else
        echo "Test 11 NOK"
        
fi

bin/Programme --region Asia &> ./test/res_test/test12.txt
result=$(diff ./test/res_test/test12.txt ./test/files_test/test12.txt)

if [ $? -eq 0 ]
then
        echo "Test 12  OK"
else
        echo "Test 12 NOK"
        
fi

bin/Programme --region Europe &> ./test/res_test/test13.txt
result=$(diff ./test/res_test/test13.txt ./test/files_test/test13.txt)

if [ $? -eq 0 ]
then
        echo "Test 13  OK"
else
        echo "Test 13 NOK"
        
fi

bin/Programme --region Oceania &> ./test/res_test/test14.txt
result=$(diff ./test/res_test/test14.txt ./test/files_test/test14.txt)

if [ $? -eq 0 ]
then
        echo "Test 14  OK"
else
        echo "Test 14 NOK"
        
fi

bin/Programme --same-borders chn mng rus &> ./test/res_test/test15.txt
result=$(diff ./test/res_test/test15.txt ./test/files_test/test15.txt)

if [ $? -eq 0 ]
then
        echo "Test 15  OK"
else
        echo "Test 15 NOK"
        
fi


bin/Programme --same-borders mex can &> ./test/res_test/test16.txt
result=$(diff ./test/res_test/test16.txt ./test/files_test/test16.txt)

if [ $? -eq 0 ]
then
        echo "Test 16  OK"
else
        echo "Test 16 NOK"
        
fi

bin/Programme --same-borders can &> ./test/res_test/test17.txt
result=$(diff ./test/res_test/test17.txt ./test/files_test/test17.txt)

if [ $? -eq 0 ]
then
        echo "Test 17  OK"
else
        echo "Test 17 NOK"
        
fi

bin/Programme --region oceania &> ./test/res_test/test18.txt
result=$(diff -q ./test/res_test/test18.txt ./test/files_test/test18.txt)

if [ $? -eq 0 ]
then
        echo "Test 18  OK"
else
        echo "Test 18 NOK"
        echo $result
        
fi




bin/Programme --region oceania --show-languages &> ./test/res_test/test19.txt
result=$(diff -q ./test/res_test/test19.txt ./test/files_test/test19.txt)

if [ $? -eq 0 ]
then
        echo "Test 19  OK"
else
        echo "Test 19 NOK"
        echo $result
        
fi

bin/Programme --region oceania --show-capital &> ./test/res_test/test20.txt
result=$(diff -q ./test/res_test/test20.txt ./test/files_test/test20.txt)

if [ $? -eq 0 ]
then
        echo "Test 20  OK"
else
        echo "Test 20 NOK"
        echo $result
        
fi

bin/Programme --region oceania --show-borders &> ./test/res_test/test21.txt
result=$(diff -q ./test/res_test/test21.txt ./test/files_test/test21.txt)

if [ $? -eq 0 ]
then
        echo "Test 21  OK"
else
        echo "Test 21 NOK"
        echo $result
        
fi

bin/Programme --region oceania --show-borders &> ./test/res_test/test22.txt
result=$(diff -q ./test/res_test/test22.txt ./test/files_test/test22.txt)

if [ $? -eq 0 ]
then
        echo "Test 22  OK"
else
        echo "Test 22 NOK"
        echo $result
        
fi

bin/Programme --region oceania --show-capital --show-languages &> ./test/res_test/test23.txt
result=$(diff -q ./test/res_test/test23.txt ./test/files_test/test23.txt)

if [ $? -eq 0 ]
then
        echo "Test 23 OK"
else
        echo "Test 23 NOK"
        echo $result
        
fi

bin/Programme --region oceania --show-capital --show-languages --show-borders &> ./test/res_test/test24.txt
result=$(diff -q ./test/res_test/test24.txt ./test/files_test/test24.txt)

if [ $? -eq 0 ]
then
        echo "Test 24  OK"
else
        echo "Test 24 NOK"
        echo $result
        
fi

bin/Programme --country can --show-languages --show-capital &> ./test/res_test/test25.txt
result=$(diff -q ./test/res_test/test25.txt ./test/files_test/test25.txt)

if [ $? -eq 0 ]
then
        echo "Test 25  OK"
else
        echo "Test 25NOK"
        echo $result
        
fi

bin/Programme --country vut --show-capital &> ./test/res_test/test26.txt
result=$(diff -q ./test/res_test/test26.txt ./test/files_test/test26.txt)

if [ $? -eq 0 ]
then
        echo "Test 26  OK"
else
        echo "Test 26 NOK"
        echo $result
        
fi

bin/Programme --country can --show-languages --show-capital &> ./test/res_test/test27.txt
result=$(diff -q ./test/res_test/test27.txt ./test/files_test/test27.txt)

if [ $? -eq 0 ]
then
        echo "Test 27  OK"
else
        echo "Test 27 NOK"
        echo $result
        
fi

bin/Programme --country vut --show-capital &> ./test/res_test/test28.txt
result=$(diff -q ./test/res_test/test28.txt ./test/files_test/test28.txt)

if [ $? -eq 0 ]
then
        echo "Test 28  OK"
else
        echo "Test 28 NOK"
        echo $result
        
fi



