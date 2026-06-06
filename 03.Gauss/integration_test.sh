#!/bin/bash

status=true

# ---------------------------------------------------
echo "Подготовка тестовых данных..."

cat <<EOF > test_input.csv
A,B,C
2,1,5
1,-3,-1
EOF

cat <<EOF > expected_output.csv
x
2
1
EOF

./gauss test_input.csv > actual_output.csv

if cmp -s expected_output.csv actual_output.csv; then
  echo "Integration test ok!"
else
  echo "Integration test failed!" >&2
  status=false
fi

rm test_input.csv expected_output.csv actual_output.csv
# ---------------------------------------------------

$status