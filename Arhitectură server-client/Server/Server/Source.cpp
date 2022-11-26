#include "Users.h"
#include "Quizzes.h"
#include "NumericalQuestions.h"


int main()
{
	const std::string db_file = "numericalQuestions.sqlite";
	NumericalQuestionStorage numericalQuestDb = createNumericalQuestionStorage(db_file);
	numericalQuestDb.sync_schema();
	auto initQuestionsCount = numericalQuestDb.count<NumericalQuestion>();
	if (initQuestionsCount == 0)
		populateNumericalQuestionStorage(numericalQuestDb);

	std::vector<crow::json::wvalue> numericalQuest_json;
	for (const auto& quest : numericalQuestDb.iterate<NumericalQuestion>())
	{
		numericalQuest_json.push_back(crow::json::wvalue{
			{"id", quest.id},
			{"question", quest.question},
			{"answer", quest.answer}
			});
	}

}