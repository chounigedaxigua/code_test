// Compiler: MSVC 19.29.30038.1
// C++ Standard: C++17
#include <iostream>
#include <future>
using namespace std;
void count_big_number() {
	// C++14标准中，可以在数字中间加上单
	// 引号 ' 来分隔数字，使其可读性更强
	for (int i = 0; i <= 10'0000'0000; i++);
}
int main() {
	future<void> fut = async(launch::async, count_big_number);
	cout << "Please wait" << flush;
	// 每次等待1秒
	while (fut.wait_for(chrono::seconds(1)) != future_status::ready)
		cout << '.' << flush;
	cout << endl << "Finished!" << endl;
	return 0;
}
