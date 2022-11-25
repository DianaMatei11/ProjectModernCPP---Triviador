#include "NumericalQuestions.h"


void populateStorage(Storage& storage)
{
	std::vector<NumericalQuestion> questionsList = {
		NumericalQuestion{ -1, "Care este lungimea fluviului Volga ?",3530 },
		NumericalQuestion{ -1, "Care este numarul atomic al poloniului?",84 },
		NumericalQuestion{ -1, "Cate limbi sunt considerate oficiale in Africa de Sud?",11 },
		NumericalQuestion{ -1, "Cate zile va avea luna februarie in anul 2072?",29 },

	};
	storage.insert_range(questionsList.begin(), questionsList.end());
}
