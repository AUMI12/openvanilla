#include <cxxtest/TestSuite.h>
#include "LanguageModel.h"

using namespace std;

class TestLanguageModel : public CxxTest::TestSuite 
{
public:
	void testGetLogProb(void)
	{
		string gram = "�U�B ��";
		cerr << gram << " logprob: " << lm_.getLogProb(gram) << endl;
		
		gram = "�U�B��";
		cerr << gram << " logprob: " << lm_.getLogProb(gram) << endl;
		
		gram = "�U�B";
		cerr << gram << " logprob: " << lm_.getLogProb(gram) << endl;
		
		gram = "�B��";
		cerr << gram << " logprob: " << lm_.getLogProb(gram) << endl;
		
		gram = "�U";
		cerr << gram << " logprob: " << lm_.getLogProb(gram) << endl;
		
		gram = "�B";
		cerr << gram << " logprob: " << lm_.getLogProb(gram) << endl;
		
		gram = "��";
		cerr << gram << " logprob: " << lm_.getLogProb(gram) << endl;
	}
	
	void testGetBackOff(void)
	{
		string gram = "�U�B ��";
		cerr << gram << " back-off: " << lm_.getBackOff(gram) << endl;
		
		gram = "�U�B��";
		cerr << gram << " back-off: " << lm_.getBackOff(gram) << endl;
		
		gram = "�U�B";
		cerr << gram << " back-off: " << lm_.getBackOff(gram) << endl;
		
		gram = "�B��";
		cerr << gram << " back-off: " << lm_.getBackOff(gram) << endl;
		
		gram = "�U";
		cerr << gram << " back-off: " << lm_.getBackOff(gram) << endl;
		
		gram = "�B";
		cerr << gram << " back-off: " << lm_.getBackOff(gram) << endl;
		
		gram = "��";
		cerr << gram << " back-off: " << lm_.getBackOff(gram) << endl;
	}
	
private:
	LanguageModel lm_;
};