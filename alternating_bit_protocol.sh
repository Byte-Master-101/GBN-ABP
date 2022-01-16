clang alternating_bit_protocol.c -o alternating_bit_protocol &&
chmod +x ./alternating_bit_protocol &&
./alternating_bit_protocol
# printf "10\n0\n0\n5\n0\n" | ./go_back_n
# printf "200\n0\n0.3\n1\n" | ./go_back_n
# printf "200\n0\n0.01\n5\n" | ./go_back_n
# printf "200\n0\n0.00\n5\n" | ./go_back_n
# printf "50\n0\n0\n5\n" | ./go_back_n

# message count, loss prob, corrupt prob, avg time, trace