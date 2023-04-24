a.out:main.cpp liba.so libb.so
	g++ main.cpp -L ./ -la -lb -Wl,-rpath=./
	nm -DA liba.so |grep -E "g_int|g_highfre_lock|g_highfreq_map"
	nm -DA libb.so |grep -E "g_int|g_highfre_lock|g_highfreq_map"
	nm -DA a.out |grep -E "g_int|g_highfre_lock|g_highfreq_map"
liba.so: a.cpp c.cpp 
	g++ -shared -fPIC a.cpp c.cpp -o liba.so
libb.so: b.cpp c.cpp
	g++ -shared -fPIC b.cpp c.cpp -o libb.so
clean:
	rm -rf lib*.so a.out

