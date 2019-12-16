#include "InputDataParser.h"

namespace algorithm
{
types::InputData InputDataParser::parseData(const Ui::GenAlgorithmClass& ui)
{
    types::InputData inputData{};

    inputData.populationSize = ui.textEditPopulationSize->toPlainText().toInt();
    inputData.generationCount = ui.textEditGenerationCount->toPlainText().toInt();
    inputData.strategyPercent = ui.textEditStrategyPercent->toPlainText().toInt();
    inputData.selectionMethod = parseSelectionMethod(ui);
    inputData.selectionParameter = ui.textEditSelectionParam->toPlainText().toInt();
    inputData.crossoverMethod = parseCrossoverMethod(ui);
    inputData.crossoverProbability = ui.textEditCrossoverProbability->toPlainText().toInt();
    inputData.mutationMethod = parseMutationMethod(ui);
    inputData.mutationProbability = ui.textEditMutationProbability->toPlainText().toInt();
    inputData.centerX = ui.textEditCenterX->toPlainText().toFloat();
    inputData.centerY = ui.textEditCenterY->toPlainText().toFloat();
    inputData.radius = ui.textEditRadius->toPlainText().toFloat();

    return inputData;
}
types::SelectionMethods InputDataParser::parseSelectionMethod(const Ui::GenAlgorithmClass& ui)
{
    if (ui.radioButtonMS1->isChecked())
        return types::SelectionMethods::BEST_ONES;
    else if (ui.radioButtonMS2->isChecked())
        return types::SelectionMethods::ROULETTE_WHEEL;
    else
        return types::SelectionMethods::TOURNAMEN;
}
types::Crossovers InputDataParser::parseCrossoverMethod(const Ui::GenAlgorithmClass& ui)
{
    if (ui.radioButtonRecomb1->isChecked())
        return types::Crossovers::ARITHMETIC;
    else
        return types::Crossovers::HEURISTIC;
}
types::Mutations InputDataParser::parseMutationMethod(const Ui::GenAlgorithmClass& ui)
{
    if (ui.radioButtonMutation1->isChecked())
        return types::Mutations::UNIFORM;
    else
        return types::Mutations::INDEX_CHANGE;
}
}
