all:
	g++ -I third_party/mpc/ prompt.cc -lreadline  ./third_party/mpc/build/libmpc.so
