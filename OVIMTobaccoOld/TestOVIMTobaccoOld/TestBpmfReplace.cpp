#include "UnitTest++/UnitTest++.h"
#include "../bpmfReplace.h"
#include< string>

TEST(ISCombinationCorrect)
{
	string str1,str2="";

	str1="1jum"; //�t������
	convert2LegalBPMF(str1, str2);
	CHECK_EQUAL(str2,"1m"); // �t��?

	str1="lu"; //����
	convert2LegalBPMF(str1, str2);
	CHECK_EQUAL(str2,"ul"); // ����?

	str1="t"; //��
	convert2LegalBPMF(str1, str2);
	CHECK_EQUAL(str2,"t"); // ��?

	str1="1u0,"; //�t������
	convert2LegalBPMF(str1, str2);
	CHECK_EQUAL(str2,"1u,"); // �t����?

	str1="504"; //������
	convert2LegalBPMF(str1, str2);
	CHECK_EQUAL(str2,"504"); // ������?
}

int main()
{
	return UnitTest::RunAllTests();
}