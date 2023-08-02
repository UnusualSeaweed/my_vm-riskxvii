

./vm_riskxvii ./tests/testing_operations.mi > ./tests/testing_operations.txt
diff -w ./tests/testing_operations.out ./tests/testing_operations.txt

./vm_riskxvii ./tests/halt.mi > ./tests/halt.txt
diff -w ./tests/halt.out ./tests/halt.txt

./vm_riskxvii ./tests/another_operation_check.mi > ./tests/another_operation_check.txt
diff -w ./tests/another_operation_check.out ./tests/another_operation_check.txt