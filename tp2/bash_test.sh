#!/bin/bash

rm test/files_test/*.*
echo "clean test"
bin/Programme &> test/files_test/test01.txt
bin/Programme --same-language &> test/files_test/test02.txt
bin/Programme --same-language can &> test/files_test/test03.txt
bin/Programme --same-language can 123 &> test/files_test/test04.txt
bin/Programme --country can &> test/files_test/test05.txt
bin/Programme --country 123 &> test/files_test/test06.txt
bin/Programme --country &> test/files_test/test07.txt
bin/Programme --region &> test/files_test/test08.txt
bin/Programme --region 123213 &> test/files_test/test09.txt
bin/Programme --region America &> test/files_test/test10.txt
bin/Programme --region Africas &> test/files_test/test11.txt
bin/Programme --region Asia &> test/files_test/test12.txt
bin/Programme --region Europe &> test/files_test/test13.txt
bin/Programme --region Oceania &> test/files_test/test14.txt
bin/Programme --same-borders chn mng rus &> test/files_test/test15.txt
bin/Programme --same-borders mex can &> test/files_test/test16.txt
bin/Programme --same-borders can &> test/files_test/test17.txt
bin/Programme --region oceania &> test/files_test/test18.txt
bin/Programme --region oceania --show-languages &> test/files_test/test19.txt
bin/Programme --region oceania --show-capital &> test/files_test/test20.txt
bin/Programme --region oceania --show-borders &> test/files_test/test21.txt
bin/Programme --region oceania --show-borders &> test/files_test/test22.txt
bin/Programme --region oceania --show-capital --show-languages &> test/files_test/test23.txt
bin/Programme --region oceania --show-capital --show-languages --show-borders &> test/files_test/test24.txt
bin/Programme --country can --show-languages --show-capital &> test/files_test/test25.txt
bin/Programme --country vut --show-capital &> test/files_test/test26.txt
bin/Programme --country can --show-languages --show-capital &> test/files_test/test27.txt
bin/Programme --country vut --show-capital &> test/files_test/test28.txt
echo "new test created"