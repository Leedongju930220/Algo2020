//string이 약한데 다른 함수 더 파악하고 구조보기
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

int main() {
	string s1 = "Leedongju";
	string s2 = "Lee dong ju";
	string s3;

	cout << s1 << endl;
	cout << s2 << endl;

	cout << "s1사이즈 " << s1.size() << endl;
	cout << "s2사이즈 " << s2.size() << endl;
	cout << "s2 length" << s2.length() << endl;
	cout << "s1의 4번째 인자 " << s1.at(3) << endl;
	cout << "s2의 4번째 인자는 공백 " << s2.at(3) << endl;
	cout << "s2의 4번째가 공백이면 1출력 " << ((s2.at(3) == ' ') ? 1 : 0)<< endl;
	printf("오퍼레이터 사용\n");
	cout << "s1의 4번째 인자 " << s1[3] << endl;  // at은 범위를 한번 체크해서 더 안전하지만 좀 느림

	cout << "s3에 a 3개 넣기 " << s3.append(3, 'a') << endl;
	cout << "s3에 b 3개 할당 " << s3.assign(3, 'b') << endl;

	cout << "s3의 0부터 2개 지우기 " << s3.erase(0, 2) << endl;
	cout << "s3의 첫번째에 c넣기 " << s3.insert(0, "c") << endl;

	cout << "s1의 두번째부터 반환 substr() " << s1.substr(1) << endl;  // 1부터 출력한다



	return 0;
}
